/* Contents of DLLDefines.h from the CMake documentation */
#ifndef _TREL_DLLDEFINES_H_
#define _TREL_DLLDEFINES_H_

/* Cmake will define TREL_EXPORTS on Windows when it
configures to build a shared library. If you are going to use
another build system on windows or create the Visual Studio
projects by hand you need to define TREL_EXPORTS when
building a DLL on windows.
*/
/* We are using the Visual Studio Compiler and building Shared libraries */

#if defined (_WIN32)
  #if defined(TREL_EXPORTS)
    #define  TREL_EXPORT __declspec(dllexport)
  #else
    #define  TREL_EXPORT /*__declspec(dllimport)  Didn't allow for STATIC compilation */ 
  #endif /* TREL_EXPORTS */
#else /* defined (_WIN32) */
 #define TREL_EXPORT
#endif

#endif /* _TREL_DLLDEFINES_H_ */
