#!/bin/bash
set -e

PASSWORD=${1}

apt-get install -y git sudo openssh-server cmake gcc g++ gdb bzip2 \
  libopenblas-dev liblapack-dev ffmpeg pkg-config \
  libavdevice-dev libavfilter-dev libavformat-dev \
  libavcodec-dev libswresample-dev libswscale-dev \
  libavutil-dev gpg code

apt-get install -y /tmp/wiringpi_3.6_arm64.deb

# Set up git username
git config --global user.name "Mona Lisa"
git config --global user.email "azzmosphere@gmail.com"

useradd -p ${PASSWORD} -m aaron
usermod -aG sudo aaron
chown aaron /tmp/id_rsa 
su aaron -c "mkdir /home/aaron/.ssh"
su aaron -c "cp /tmp/config /home/aaron/.ssh/"
su aaron -c "cp /tmp/id_rsa  /home/aaron/.ssh/"
su aaron -c "cp /tmp/id_rsa.pub /home/aaron/.ssh/"
su aaron -c "chmod -R 700  /home/aaron/.ssh"
su aaron -c "git config --global user.name 'Aaron Spiteri' && git config --global user.email 'azzmosphere@gmail.com.au'"
su aaron -c "cd /home/aaron && git clone git@github.com:Ryder-Robots/rr-environment.git"

su aaron -c "cd /home/aaron && \
  git clone https://github.com/davisking/dlib.git &&
  cd dlib && mkdir build; cd build; cmake .. ; cmake --build ."
cd /home/aaron/dlib/build && cmake --install .

# Setup VSCODE extensions
for ex in crugthew.c-cpp-linter \
  franneck94.c-cpp-runner \
  ms-vscode.cmake-tools \
  ms-vscode.cpptools \
  ms-vscode.cpptools-extension-pack \
  ms-vscode.cpptools-themes \
  twxs.cmake \
  vadimcn.vscode-lldb; do
  su aaron -c "code  --install-extension ${ex}"
done

