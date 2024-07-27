#!/bin/bash

PASSWORD=${1}

apt-get install -y git sudo openssh-server cmake gcc g++ \
  libopenblas-dev liblapack-dev ffmpeg pkg-config \
  libavdevice-dev libavfilter-dev libavformat-dev \
  libavcodec-dev libswresample-dev libswscale-dev \
  libavutil-dev 

useradd -p ${PASSWORD} -m aaron
usermod -aG sudo aaron
chown aaron /tmp/id_rsa 
su aaron -c "mkdir /home/aaron/.ssh"
su aaron -c "cp /tmp/config /home/aaron/.ssh/"
su aaron -c "cp /tmp/id_rsa  /home/aaron/.ssh/"
su aaron -c "chmod -R 700  /home/aaron/.ssh"

su aaron -c "cd /home/aaron && git clone git@github.com:Ryder-Robots/rr-environment.git"

su aaron -c "cd /home/aaron && \
  git clone https://github.com/davisking/dlib.git &&
  cd dlib && mkdir build; cd build; cmake .. ; cmake --build ."
cd /home/aaron/dlib/build && cmake --install .
