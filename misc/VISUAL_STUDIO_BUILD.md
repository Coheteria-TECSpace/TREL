# MSVC building TREL
The latest release of TREL will **always** be tested for compilation and execution both in Unix and Windows, for the latter, Visual Studio Community 2022 is the officcial IDE, but in theory many other methods are supported

## With MSVC in Visual Studio
Open the directory in VS, let CMake generate the project, then select on *Build project* at the top of VS and then the final build will be created, currently only Debug x64 exists

*CMake adds `/W3` by deffault so some warning for overriding with `/W4` will appear, currently looking for a solution*

# With MSVC for other IDEs/Text editors with Visual Studio avaliable
Guessing you have a `build/`, run cmake from there with `cmake ..`

When the project is built, there will be a `.sln` file which once it's oppened on Visual Studio it will allow to build de project, then leaving the library and app if chosen.
