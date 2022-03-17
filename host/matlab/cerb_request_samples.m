function iq = cerb_request_samples( ip, nsamps, cwgen_freq_hz, cwgen_ampl_scale )
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DESCRIPTION: 
%   
%    Executes the "rx_samples_to_file" application and retrieves the 
%    waveform file using a remote SSH connection to the Cerberus SDR 
%    platforms.
%
% Copyright (C) 2022 Ipsolon Research, Inc
% All rights reserved.
%

sshfrommatlabinstall;
 
iq  = [];
fn  = 'rx_samples.cfile';

cmd = 'rx_samples_to_file '; % app name
cmd = strcat(cmd, [' --file '       num2str(fn)]);
cmd = strcat(cmd, [' --nsamps '     num2str(floor(nsamps))]); 
cmd = strcat(cmd, [' --cwgen-freq ' num2str(cwgen_freq_hz*1e6)]); 
cmd = strcat(cmd, [' --cwgen-ampl ' num2str(floor(cwgen_ampl_scale))]);

% login and execute command
[ssh]      = sshfrommatlab('root', ip, 'root');
[ssh, ret] = sshfrommatlabissue(ssh, cmd);
if( ~any(contains(ret, 'Done')) )
    sshfrommatlabclose(ssh);
    error('failed to find execute [pfb_samples_to_file] on remote platform');
end

% verify output file exists
[ssh, ret] = sshfrommatlabissue(ssh, ['[[ -f ' fn ' ]] && echo "OK"']);
if( ~contains(ret, 'OK') )
    sshfrommatlabclose(ssh);
    error('failed to find output file');
end

% download file & remove on device
scptomatlab('root', ip, 'root', '.', fn);
sshfrommatlabissue(ssh, ['rm -f ' fn ]);

% get IQ samples from file
fid = fopen(fn);
if fid == -1
  error("failed to load waveform file");
end  
data = fread(fid,inf,'float');
iq   = data(1:2:end-1) + 1i*data(2:2:end);

fclose(fid); delete(fn);
sshfrommatlabclose(ssh);
