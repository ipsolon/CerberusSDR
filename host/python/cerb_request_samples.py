"""
:module: cerb_request_samples.py

:author: Michael Clark <mclark@ipsolonresearch.com>

:since:  March 2022

:about:
Implement a remote SSH connection that executes the rx_samples_to_file
application on the Cerberus SDR, retrieves the waveform file and
plots the results. This is expected to be used with the Cerberus-DMA
FPGA build as part of the Petalinux BSP.

:license:
Copyright (C) 2022 Ipsolon Research, Inc
All rights reserved.
"""
import os
import numpy as np
from ssh import SSH
from pathlib import Path
from utils import plot_cmplx_waveform, plot_power_spectrum, plot_inst_frequency
import matplotlib.pyplot as plt

def cerb_request_samples(ip, nsamps=2**16, cwgen_freq_hz=50e6, cwgen_ampl_scale=0):
    """ Requests IQ Samples and configures the AXI CWGEN IP """
    ssh = SSH(ip)

    fn = 'rx_samples_to_file.cfile'
    cmd = 'rx_samples_to_file'
    cmd += " --file=" + fn
    cmd += " --nsamps=" + str(int(nsamps))
    cmd += " --cwgen-freq=" + str(cwgen_freq_hz)
    cmd += " --cwgen-ampl=" + str(int(cwgen_ampl_scale))

    resp = ssh.user_cmd(cmd)
    if not resp or resp.find("Done") == -1:
        print(cmd + '\n' + str(resp))
        raise Exception("failed to acquired samples")

    P = Path(__file__).resolve()
    local = os.path.join(P.parent, fn)
    remote = ssh.current_directory() + '/' + fn

    ok = ssh.retrieve_file(remote, local)
    ssh.rm(remote)
    if not ok:
        raise Exception("failed to retrieve file")

    wv = np.fromfile(local, dtype='complex64')
    os.remove(local)
    return wv

if __name__ == '__main__':

    iq = cerb_request_samples(ip="10.21.154.71")
    plot_cmplx_waveform(iq, nsamps=len(iq))
    plot_power_spectrum(iq)
    plot_inst_frequency(iq)
    plt.show(block=True)