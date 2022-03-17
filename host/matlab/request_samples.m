%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DESCRIPTION: 
%   
%    Requests IQ samples from the Cerberus SDR platform.
%
% Copyright (C) 2022 Ipsolon Research, Inc
% All rights reserved.
%
close all;

ip       = '10.21.154.71';  % Cerberus IP address
fs_mhz   = 500;             % ADC sample rate in MHz
nsamps   = 2^13;            % IQ samples to request (<2^20)
cwgen_freq_mhz   = -10;     % CWGEN frequency offset (250MHz + fo)
cwgen_ampl_scale = 0;       % CWGEN amplitude scale (x * 2^-scale)

iq = cerb_request_samples(ip, nsamps, cwgen_freq_mhz, cwgen_ampl_scale);

figure;
subplot(2,1,1); plot(real(iq));
subplot(2,1,2); plot(imag(iq));
title('IQ Waveform');

figure;
N   = length(iq);
Nyq = 1/2 * fs_mhz;
df  = 1/N * fs_mhz;
f   = -Nyq : df : Nyq-df;
G   = fftshift(abs(fft(iq))/N);
P   = 10*log10(G.^2 + 1e-16);
plot(f,P);
title('Power Spectrum');

% look for discontinuities
figure, plot(diff(unwrap(angle(iq))));
title('Change in Phase');




