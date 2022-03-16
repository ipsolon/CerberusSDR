"""
:module: cerb_waveform_from_ila.py

:author: Michael Clark <mclark@ipsolonresearch.com>

:since:  March 2022

:about:
Reads the AXI-S ADC/DAC ILA data from a CSV formatted file,
and plots the waveform.

:license:
Copyright (C) 2022 Ipsolon Research, Inc
All rights reserved.
"""
import numpy as np
import csv, re, struct
from scipy.fftpack import fft, fftfreq, fftshift
import matplotlib.pyplot as plt
from pathlib import Path, PureWindowsPath

def get_power_spectrum(x, Fs = 1):
    N = len(x)
    yf = fft(x)/N
    xf = fftfreq(N, 1/Fs)
    xf = fftshift(xf)
    yf = fftshift(yf)
    yf_db = 20*np.log10(np.abs(yf) + 1e-10)
    return yf_db, xf

# plot ouptut power spectrum
def plot_power_spectrum(x, Fs=1, axis = None):
    if not axis:
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)

    P, F = get_power_spectrum(x, Fs)

    ax.plot(F, P, color='r')
    ax.grid()
    ax.set_ylabel('Power (dB)')
    ax.set_xlabel('Frequency (MHz)')
    ax.set_title('Output Power Spectrum')

def plot_cmplx_waveform(x, Fs=1, slice=1000):
    fig, ax = plt.subplots(2)
    fig.suptitle('Complex Waveform')
    ax[0].plot(np.real(x[0:slice]))
    ax[0].set(xlabel='Samples', ylabel='Amplitude', title='Real Waveform')
    ax[0].grid()
    ax[1].plot(np.imag(x[0:slice]))
    ax[1].set(xlabel='Samples', ylabel='Amplitude', title='Imag Waveform')
    ax[1].grid()

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
    fn = 'rfdc_adc_ila_data.csv'
    #fn = 'rfdc_dac_ila_data.csv'
    fs = 500e6

    iq = parse_ila_csv_file(fn)

    plot_cmplx_waveform(iq, fs/1e6)
    plot_power_spectrum(iq, fs/1e6)
    plt.show(block=True)




