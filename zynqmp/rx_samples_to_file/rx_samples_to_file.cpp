//!*********************************************************************
//! @file rx_samples_to_file.cpp
//!
//! @author Michael Clark <mclark@ipsolonresearch.com>
//!
//! @date March, 2022
//!
//! @brief
//! Requests IQ samples from the Cerberus SDR device driver. This
//! application is expected to be used by the Cerberus-DMA FPGA
//! build as part of the Petalinux BSP.
//!
//! THe Xilinx DMA IP is connected to the RFDC ADC[0] channel. The ADC
//! channel's sample rate is 500MHz and center frequency of 250MHz.
//!
//! Copyright (C) 2022 Ipsolon Research, Inc
//! All rights reserved.
//!*********************************************************************
#include <math.h>
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <sys/ioctl.h>

namespace po = boost::program_options;
typedef std::complex<int16_t>       cmplx_wire_t;
typedef std::complex<float>         cmplx_sample_t;
typedef std::vector<cmplx_wire_t>   cmplx_wire_vec_t;
typedef std::vector<cmplx_sample_t> cmplx_sample_vec_t;

#define CERB_IQ_SCALE   (1.0f / 32768.0f)
#define CERB_MAX_IQ_CNT (1 << 20)
#define CERB_SDR_DEV    "/dev/cerberus-sdr"
#define CERB_DMA_DEV    "/dev/cerb_dmarx_ch0"

// globals
po::variables_map   m_opts;
std::string         m_file_def = "samples_to_file.cfile";
size_t              m_nsamps = 65536;
double              m_freq_hz = 10e6;
size_t              m_ampl_scale = 1;

//!******************************************************
//! @brief
//! Handles command line options
//!
//!******************************************************
int init_options(int argc, char *argv[])
{
    po::options_description desc("Command Line Options");
    desc.add_options()
        ("help,h",     "help message")
        ("file,f",     po::value<std::string>(&m_file_def)->default_value(m_file_def),  "Output complex waveform filename (cfile)")
        ("nsamps,n",   po::value<size_t>(&m_nsamps)->default_value(m_nsamps),           "Requested number of complex samples (< 2^20) ")
        ("cwgen-freq", po::value<double>(&m_freq_hz)->default_value(m_freq_hz),         "CW Generator baseband frequency in Hz")
        ("cwgen-ampl", po::value<size_t>(&m_ampl_scale)->default_value(m_ampl_scale),   "CW Generator power-of-2 amplitude scale")
    ;

    po::store( po::parse_command_line(argc, argv, desc), m_opts);
    if (m_opts.count("help")){
        std::cout << "Usage: options_description [options]\n";
        std::cout << desc;
        return 0;
    }

    try {
        po::notify(m_opts);
    }
    catch (std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 0;
    }

    return 1;
}

//!**************************************************
//! @brief
//! Sets the device enable state.
//!
//!**************************************************
bool cwgen_configure( double freq_hz, double phase, size_t ampl_scale )
{
    typedef struct __attribute__((__packed__)) {
        uint32_t     mute;       // not supported
        uint32_t     freq_word;
        uint32_t     phase_word;
        uint32_t     ampl_scale;
    } cerb_cwgen_t;
    #define CERB_IOCTL_CWGEN     _IOW('C', 2, struct cerberus_cwgen_t*)

    int32_t freq_word  = std::round(freq_hz / 500e6 * 65536);
    int32_t phase_word = std::round(phase / (2*M_PI) * 65536);
    cerb_cwgen_t msg = {
        0,
        static_cast<uint32_t>(freq_word),
        static_cast<uint32_t>(phase_word),
        static_cast<uint32_t>(ampl_scale & 0x1F),
    };

    // perform IQ capture (fs=500MHz)
    int fd = open(CERB_SDR_DEV, O_RDWR | O_SYNC);
    if( fd < 0 ) {
        printf("error: failed to open DMA device.. aborting\n");
        return false;
    }

    int rc = ioctl(fd, CERB_IOCTL_CWGEN, (void*)&msg);
    if( rc < 0 ){
        printf("failed to call [CERB_IOCTL_CWGEN] => [%d]\n", rc);
        return false;
    }
    return true;
}

//!******************************************************
//! @brief
//! Performs a single DMA request
//!
//!******************************************************
bool request( uint8_t* buffer, ssize_t req_bytes )
{
    // open DMA channel
    int fd = open(CERB_DMA_DEV, O_RDWR | O_SYNC);
    if( fd < 0 ) {
        printf("error: failed to open DMA device.. aborting\n");
        return false;
    }

    ssize_t pos = 0;
    while( req_bytes > 0 )
    {
        ssize_t rc = ::read(fd, &buffer[pos], req_bytes);
        if( !rc ){
            printf("warn: dma timeout\n");
            close(fd);
            return false;
        }
        else if( rc < 0 ){
            printf("error: dma error [%s]\n", strerror(errno));
            close(fd);
            return false;
        }
        req_bytes -= rc;
        pos += rc;
    }

    close(fd);
    printf("dma request completed: [%ld] bytes received\n", pos);
    return true;
}

//!******************************************************
//! @brief
//! Main entry point
//!
//!******************************************************
int main(int argc, char *argv[])
{
    if( !init_options(argc, argv) ) {
        return 1;
    }

    if( !cwgen_configure( m_freq_hz, 0, m_ampl_scale) ){
        printf("error: failed to configure CWGEN... aborting\n");
        return 1;
    }

    if( !m_nsamps ) {
        printf("Done\n");
        return 0;
    }
    else if( m_nsamps > CERB_MAX_IQ_CNT ) {
        printf("warn: number of requested samples exceeded\n");
        m_nsamps = CERB_MAX_IQ_CNT;
    }

    // alloc memory
    cmplx_wire_vec_t wire(m_nsamps);
    size_t req_bytes = (m_nsamps << 2); // 32-bit complex samples

    // perform IQ capture (fs=500MHz)
    if( !request( reinterpret_cast<uint8_t*>(&wire[0]), req_bytes) ) {
        printf("error: dma requested failed.. aborting\n");
        return 1;
    }

    // data type conversion
    cmplx_sample_vec_t samples(m_nsamps);
    for (size_t k = 0; k < m_nsamps; k++) {
        samples[k] = std::complex<float>(static_cast<float>(wire[k].real()) * CERB_IQ_SCALE,
                                         static_cast<float>(wire[k].imag()) * CERB_IQ_SCALE);
    }

    // write to file
    std::ofstream fout(m_file_def.c_str(), std::ios::binary);
    if( !fout.is_open() ){
        printf("failed to open file [%s]\n", m_file_def.c_str());
        return 1;
    }
    fout.write((char*)&samples[0], samples.size()*sizeof(samples[0]));

    printf("Done\n");
    return 0;
}
