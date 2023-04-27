# Manual building TREL
This isn't the recommended way of compiling TREL, so it's highly discouraged, however, if your system doesn't have CMake for some reason, this **old** instructions are left as a draft to what you might need to do

## Using only GCC and make
In case you want to stay away from CMake, this should work for all Unix like systems, but it isn't the recommended route

### Compiling the shared object from a subdirectory build
```
mkdir build
cd build
gcc -c -Wall -Wextra -pedantic -Werror -fpic ../src/*.c -I../include/
gcc -shared -o libTREL.so ./*.o
rm *.o
```
### Building main.c and linking to the lib from the build subdirectory
```
gcc -o app ../main.c -Wall -Wextra -pedantic -Werror -I../include/ -L. -lTREL -lm
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```

## Using only GCC and make (MINGW)
In case you can't use (or don't want to use) WSL, this is the less Unix-y way of doing it in Windows

### Compiling the shared object from a subdirectory build
```
md build && cd build
gcc -c -Wall -Wextra -pedantic -Werror -fpic ../src/*.c -I../include/
gcc -shared -o libTREL.dll ./*.o
del *.o
```
### Building main.c and linking to the lib from the build subdirectory
```
gcc -o app ../main.c -Wall -Wextra -pedantic -Werror -I../include/ -L. -lTREL -lm
```

