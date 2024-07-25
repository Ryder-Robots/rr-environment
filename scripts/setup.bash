#!/bin/bash

echo "installing required dev packages"
sudo apt-get install cmake
sudo apt install ffmpeg
sudo apt-get install libopenblas-dev liblapack-dev 
sudo apt install libjxl-dev
sudo apt install libavdevice-dev libavfilter-dev libavformat-dev
sudo apt install libavcodec-dev libswresample-dev libswscale-dev
sudo apt install libavutil-dev
sudo apt-get install lldb