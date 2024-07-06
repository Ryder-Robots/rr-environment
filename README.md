# rr-environment
drivers for raspberry 4B


```
rm -rf _builds _install
cmake -H. -B_builds/shared -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX="`pwd`/_install/rrenvironment"
cmake --build _builds/shared --target install

```