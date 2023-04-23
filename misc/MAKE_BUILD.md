# Make building TREL
When using Make the process should be fairly straightforward, the latest release of TREL will always be tested with GNU Linux, at least in a Debian 11+ distro, however, CMake's generated Makefile should be compatible with many OSes.

## Release
Do this if you only need TREL to run simulations
```
mkdir Release && cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Debug
Do this if you want to test and contribute code to TREl, allowing debug symbols to be bundled in the executable, **expect lower performance than Release** due to the lack of compiler optimizations
```
mkdir Debug && cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```
