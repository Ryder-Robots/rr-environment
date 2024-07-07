# rr-environment
drivers for raspberry 4B


```
sudo apt-get install libopenblas-dev liblapack-dev 

rm -rf _builds _install build && \
cmake -H. -B_builds/shared -DBUILD_SHARED_LIBS=ON -DDLIB_NO_GUI_SUPPORT=ON -DCMAKE_INSTALL_PREFIX="`pwd`/_install/" 
```

to install

```
cmake --build _builds/shared --target install
```