# rr-environment
drivers for raspberry 4B

## Create Docker image

```
docker build -t rrobot .
docker run --rm -it -p 22:22 rrobot 
ssh aaron@192.168.1.13
```

## Quick Build

```
rm -fR build && cmake -S . -B build && cmake --build build
```

## Install Dlib Library

```
git clone https://github.com/davisking/dlib.git
cd dlib
rm -fR build;mkdir build; cd build; cmake .. ; cmake --build .
sudo cmake --install .
```

## Create library
```
sudo apt-get install cmake
sudo apt install ffmpeg
sudo apt-get install libopenblas-dev liblapack-dev 
sudo apt install libjxl-dev
sudo apt install libavdevice-dev libavfilter-dev libavformat-dev
sudo apt install libavcodec-dev libswresample-dev libswscale-dev
sudo apt install libavutil-dev

# Download wiringPi (soon to be deprecated but someone is still maintaining it for the moment)
# https://github.com/WiringPi/WiringPi/releases

sudo apt-get install wiringpi

rm -rf _builds _install build && \
cmake -H. -B_builds/shared -DBUILD_SHARED_LIBS=ON -DDLIB_NO_GUI_SUPPORT=ON -DCMAKE_INSTALL_PREFIX="`pwd`/_install/" 
```

to install

```
cmake --build _builds/shared --target install
```
