"""
:module: ssh.py

:author: Michael Clark <mclark@ipsolonresearch.com>

:since:  March 2022

:about:
Implements remote system calls using paramiko SSH

:license:
Copyright (C) 2022 Ipsolon Research, Inc
All rights reserved.
"""
import paramiko
import datetime
import paramiko.channel as channel
from pathlib import Path, PureWindowsPath, PurePosixPath

class SSH:
    PRE_CMD = ''
    DEBUG = False

    def __init__(self, ip, user='root', pwd='root'):
        self._ip = ip
        self._user = user
        self._pwd = pwd
        self._stdin = None
        self._stdout = None
        self._stderr = None
        self._ssh = paramiko.SSHClient()
        self._ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self._ssh.connect(ip, username=user, password=pwd)

    def __del__(self):
        self.disconnect()

    def disconnect(self):
        if self._ssh:
            self._ssh.close()


    def user_cmd(self, cmd, timeout=2):
        """ Executes a command as sudo user """
        cmd = self.PRE_CMD + cmd

        if self.DEBUG:
            print(cmd)

        self._stdin, self._stdout, self._stderr = self._ssh.exec_command(cmd, timeout=timeout, get_pty=True)
        try:
            ret = self._stdout.read().decode('utf8')
        except Exception as e:
            ret = None

        try:
            errc = self._stderr.read()
            if errc:
                print(errc)
        except Exception as e:
            pass

        return ret

    def mkdir(self, path):
        """ Creates a new directory relative to the home directory """
        cmd = 'mkdir ' + str(path)
        ret = self.user_cmd(cmd)
        return ret

    def which(self, exe):
        """ Creates a new directory relative to the home directory """
        cmd = 'which ' + exe
        ret = self.user_cmd(cmd)
        return ret.strip().decode('utf8')

    def time(self):
        """ Gets the current date/time from the remote machine """
        cmd = 'date +%s'
        ret = self.user_cmd(cmd)
        return datetime.datetime.fromtimestamp(float(ret))

    def dir_exists(self, _dir):
        """ Determines if a directory exists """
        if isinstance(_dir, Path):
            _dir = PurePosixPath(_dir)
        cmd = "[ -d " + str(_dir) + " ] && echo OK"
        ret = self.user_cmd(cmd)
        return "OK" in ret

    def file_exists(self, fn):
        """ Determines if a file exists """
        if isinstance(fn, Path):
            fn = PurePosixPath(fn)

        cmd = "[ -f " + str(fn) + " ] && echo OK"
        ret = self.user_cmd(cmd)
        return "OK" in ret

    def rm(self, path):
        """ Removes a directory """
        cmd = 'rm -r ' + path
        ret = self.user_cmd(cmd)
        return ret

    def current_directory(self):
        """ Removes a directory """
        cmd = 'echo $PWD'
        ret = self.user_cmd(cmd)
        return ret.strip()

    def home_directory(self):
        """ Removes a directory """
        cmd = 'echo $HOME'
        ret = self.user_cmd(cmd)
        return ret.strip()

    def send_file(self, local, remote):
        """ Send a file between the host and remote """
        if isinstance(remote, Path):
            remote = PurePosixPath(remote)

        ret = False
        try:
            sftp = self._ssh.open_sftp()
            sftp.put(str(local), str(remote))
            sftp.close()
            ret = True
        except Exception as e:
            print(str(e))

        return ret

    def retrieve_file(self, remote, local):
        """ Send a file between the host and remote """
        ret = False
        try:
            sftp = self._ssh.open_sftp()
            sftp.get(str(remote), str(local))
            sftp.close()
            ret = True
        except Exception as e:
            print(str(e))

        return ret

    def cd(self, path):
        """ Change directory """
        cmd = 'cd ' + path
        ret = self.user_cmd(cmd)
        return ret


