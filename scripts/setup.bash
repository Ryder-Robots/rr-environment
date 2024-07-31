#!/bin/bash
set -e

USERNAME=${1}
PASSWORD=${2}

apt-get install -y git sudo openssh-server cmake gcc g++ gdb bzip2 \
  libopenblas-dev liblapack-dev ffmpeg pkg-config \
  libavdevice-dev libavfilter-dev libavformat-dev \
  libavcodec-dev libswresample-dev libswscale-dev \
  libavutil-dev gpg code net-tools

apt-get install -y /tmp/wiringpi_3.6_arm64.deb


# Set up git username
git config --global user.name "Aaron SPiteri"
git config --global user.email "azzmosphere@gmail.com"

useradd -m -p $(echo "${PASSWORD}" | openssl passwd -1 -stdin) ${USERNAME} > /dev/null 2>&1
usermod -aG sudo ${USERNAME}

chown ${USERNAME} /tmp/id_rsa 
su ${USERNAME} -c "mkdir /home/aaron/.ssh"
su ${USERNAME} -c "cp /tmp/config /home/aaron/.ssh/"
su ${USERNAME} -c "cp /tmp/id_rsa  /home/aaron/.ssh/"
su ${USERNAME} -c "cp /tmp/id_rsa.pub /home/aaron/.ssh/"
su ${USERNAME} -c "chmod -R 700  /home/aaron/.ssh"
su ${USERNAME} -c "git config --global user.name 'Aaron Spiteri' && git config --global user.email 'azzmosphere@gmail.com.au'"
su ${USERNAME} -c "cd /home/aaron && git clone git@github.com:Ryder-Robots/rr-environment.git"

su ${USERNAME} -c "cd /home/aaron && \
  git clone https://github.com/davisking/dlib.git &&
  cd dlib && mkdir build; cd build; cmake .. ; cmake --build ."
cd /home/${USERNAME}/dlib/build && cmake --install .

# Setup VSCODE extensions
VS_CODE_IGNORE_EXT=1
if VS_CODE_IGNORE_EXT -ne 1; then
for ex in crugthew.c-cpp-linter \
  franneck94.c-cpp-runner \
  ms-vscode.cmake-tools \
  ms-vscode.cpptools \
  ms-vscode.cpptools-extension-pack \
  ms-vscode.cpptools-themes \
  twxs.cmake \
  vadimcn.vscode-lldb; do
  su ${USERNAME} -c "code  --install-extension ${ex}"
done
fi

