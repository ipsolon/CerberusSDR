"""
:module: utils.py

:author: Michael Clark <mclark@ipsolonresearch.com>

:since:  March 2022

:about:
Implement general-purposes utility functions.

:license:
Copyright (C) 2022 Ipsolon Research, Inc
All rights reserved.
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft, fftfreq, fftshift

def get_power_spectrum(x, Fs=1):
    N = len(x)
    yf = fft(x)/N
    xf = fftfreq(N, 1/Fs)
    xf = fftshift(xf)
    yf = fftshift(yf)
    yf_db = 20*np.log10(np.abs(yf) + 1e-10)
    return yf_db, xf

def plot_cmplx_waveform(x, nsamps=1000):
    """ plot the complex time waveform """
    fig, ax = plt.subplots(2)
    fig.suptitle('Complex Waveform')

    if len(x) < nsamps:
        nsamps = len(x)

    ax[0].plot(np.real(x[0:nsamps]))
    ax[0].set(xlabel='Samples', ylabel='Amplitude', title='Real Waveform')
    ax[0].grid()
    ax[1].plot(np.imag(x[0:nsamps]))
    ax[1].set(xlabel='Samples', ylabel='Amplitude', title='Imag Waveform')
    ax[1].grid()

def plot_power_spectrum(sig, fs=500.0):
    """ plot power spectrum """
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    P, F = get_power_spectrum(sig, fs)
    ax.plot(F, P, color='r')
    ax.grid()
    ax.set_ylabel('Power (dB)')
    ax.set_xlabel('Frequency (MHz)')
    ax.set_title('Output Power Spectrum')
