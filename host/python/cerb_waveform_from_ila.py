"""
:module: cerb_waveform_from_ila.py

:author: Michael Clark <mclark@ipsolonresearch.com>

:since:  March 2022

:about:
Reads the AXI-S ADC/DAC ILA data from a CSV formatted file,
and plots the waveform.This is expected to be used with
the Cerberus-RFDC FPGA build as part of the Petalinux BSP.

:license:
Copyright (C) 2022 Ipsolon Research, Inc
All rights reserved.
"""
import numpy as np
import csv, re, struct
from utils import plot_cmplx_waveform, plot_power_spectrum
import matplotlib.pyplot as plt

def parse_ila_csv_file(fn, fs = 500e6, dataWidth=16, sampsPerCycle=2):
    wv = []
    with open(fn, newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        header1 = next(reader)
        header2 = next(reader)
        tdata_idx = [i for i, s in enumerate(header1) if 'tdata' in s.lower()]
        for row in reader:
            fmt = ''.join(2 * sampsPerCycle * ["."])  # parse 16-bit words
            samples_hex = re.findall(fmt, row[tdata_idx[0]])
            samples_hex.reverse()
            samps = []
            for word in samples_hex:
                cmplx_bytes = bytes.fromhex(word)
                s = struct.unpack('>h', cmplx_bytes)
                samps += [float(s[0]) / 2**15]

            wv.append(complex(samps[0], samps[1]))
            wv.append(complex(samps[2], samps[3]))

    return np.asarray(wv)


if __name__ == '__main__':
    fn = 'data/rfdc_adc_ila_data.csv'
    #fn = 'data/rfdc_dac_ila_data.csv'
    fs_mhz = 500.0

    iq = parse_ila_csv_file(fn)
    plot_cmplx_waveform(iq)
    plot_power_spectrum(iq, fs_mhz)
    plt.show(block=True)




