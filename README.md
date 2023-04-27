# TECSpace Rocket Engine Library (TREL)
ANSI C89/C90 library for transient simulations of solid propellant rocket engines' performance, easily run simulations for rocket engines or entire rocket systems with just a few lines of code.

## Portability
Given that this library expects to calculate data for rockets in many ways, allowing the same functionality to be easily ported to any high level programming language having the basis at ANSI C (C89/C90) will make the initial effort more scalable as it could even be used to interface straight from embedded systems that gather data and compare it to the one generated in real time from the library, or even using the basic funtions to create an advanced GUI.

## Building the library
The current build method uses CMake, modifying the CMakeLists.txt file allows the user to generate a static or dynamic library by changing `"Build Shared Libraries" ON to OFF` depending on what is desired, just as well as `"Build app" ON` can be toggled to generate the testing app which links automatically to the library.

## Roadmap
Read the [TODO](https://github.com/Coheteria-TECSpace/TREL/blob/dev/TODO.md) and try to
understand what to do just by reading that.
