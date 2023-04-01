# @version 0.0.1
# CMake allows for a wide range of platforms and IDEs/build tools
# This project structure was designed with Win32 and UNIX like OS in mind
# Some terminal arguments should allow for specific builds with make
# cmake -DCMAKE_BUILD_TYPE=Debug path/to/source
# cmake -DCMAKE_BUILD_TYPE=Release path/to/source

# Probably works on 3.12, hasn't been tested yet
CMAKE_MINIMUM_REQUIRED (VERSION 3.13.4)
# Declaring the project name, version and description
PROJECT (structure_test VERSION 0.0.1 DESCRIPTION "Basic structure for compilation of libraries")

# Developer can choose between Dynamic and Static libraries
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)

# Developer can choose to build the CLI testapp
OPTION (BUILD_CLI_TESTAPP "Build testapp" ON)

# Used to generate header with macros for the library
INCLUDE (GenerateExportHeader)

# Decide which LIB_TYPE is to be used for the build
IF (BUILD_SHARED_LIBS)
  SET (LIB_TYPE SHARED)
ELSE (BUILD_SHARED_LIBS)
  SET (LIB_TYPE STATIC)
ENDIF (BUILD_SHARED_LIBS)

# Create a target for the library
ADD_LIBRARY (TREL ${LIB_TYPE} "src/design_func.c" 
							  "src/engine.c" 
							  "src/rendimientos.c" 
							  "src/comp_area.c" 
							  "src/comp_tiempo.c"
							  "src/design_resist.c"
							  "src/val_termod.c"
							  "src/rocket.c"
			                                  "src/height_sim.c")

# Specify the directory to contain header files
INCLUDE_DIRECTORIES ("include")

# Determine the need for linking the math library
IF (NOT MSVC)
    TARGET_LINK_LIBRARIES (TREL PRIVATE m)
ENDIF (NOT MSVC)

IF (MSVC)
    # warning level 4 and all warnings as errors
    TARGET_COMPILE_OPTIONS(TREL PRIVATE /W4 /WX)
ELSE (MSVC)
    # most warnings all treated as errors
    TARGET_COMPILE_OPTIONS(TREL PRIVATE -Wall -Wextra -pedantic -Werror)
ENDIF (MSVC)

# Specify arguments to be used in the export header
GENERATE_EXPORT_HEADER (TREL
	BASE_NAME TREL
	EXPORT_MACRO_NAME TREL_EXPORT
	EXPORT_FILE_NAME TREL_Export.h
	STATIC_DEFINE TREL_BUILT_AS_STATIC
)

# Compile flags for the library
SET_TARGET_PROPERTIES (TREL PROPERTIES COMPILE_FLAGS -DLIB_STATIC_DEFINE)

# Additional function calls for building the testapp
IF (BUILD_CLI_TESTAPP)
	# Adding an executable to test the library
	ADD_EXECUTABLE (testapp "main.c")
	# Declaring a link between the executable and the library
	TARGET_LINK_LIBRARIES (testapp TREL)
	#target_link_libraries(testapp PRIVATE )
	target_include_directories(testapp PUBLIC "include")
	# Additional arguments for the excecutable compilation
	TARGET_COMPILE_FEATURES (testapp PUBLIC c_std_99)
ENDIF (BUILD_CLI_TESTAPP)
