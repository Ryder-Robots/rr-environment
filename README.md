# rr-environment
drivers for raspberry 4B

## Quick Build

```
rm -fR build && cmake -S . -B build && cmake --build build
```

## Install Dlib Library

```
rm -fR build;mkdir build; cd build; cmake .. ; cmake --build .
sudo cmake --install .
```

## Create library
```
sudo apt install ffmpeg
sudo apt-get install libopenblas-dev liblapack-dev 

rm -rf _builds _install build && \
cmake -H. -B_builds/shared -DBUILD_SHARED_LIBS=ON -DDLIB_NO_GUI_SUPPORT=ON -DCMAKE_INSTALL_PREFIX="`pwd`/_install/" 
```

to install

```
cmake --build _builds/shared --target install
```