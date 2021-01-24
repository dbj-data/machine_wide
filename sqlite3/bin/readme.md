
- [1. To use sqlite3](#1-to-use-sqlite3)
- [2. To build using the sqlite3.lib from here in your projects](#2-to-build-using-the-sqlite3lib-from-here-in-your-projects)


## 1. To use sqlite3

Basically sqlite3.dll has to be on the path. Or alternatively in the same folder with the executable.

To manage path's on your Windows machine we recommend: [RED (Rapid Environment Editor)](https://www.rapidee.com/en/about)

On this machine:
> **DBJ_SQLITE3=D:\MACHINE_WIDE\sqlite3\bin;**

- This is where sqlite3.dll is
- This is where sqlite3.lib is

- Please add it to the PATH user environment variable

## 2. To build using the sqlite3.lib from here in your projects

1. add `/LIBPATH:d:/machine_wide/sqlite3/bin` after the `/link` switch on the cl.exe command line
   1. same is for clang-cl.exe
2. add `sqlite3.lib` to the list of input files

Example from some VSCode `.vscode/.tasks.json` file

```cpp
/* can use the full path here if required */
"command": "clang-cl.exe",
    "args": [
"/W3",
"/TC", 
/* Treat all source files as C */
/* this does not work: "/std:c11", */
/* but this does */ 
"/clang:-std=c11", 
"/DWINVER=0x0A00",
"/D_WIN32_WINNT=0x0A00",
/* NOTE: sqlite3 requires utf-8 by default */
"/utf-8", 
"/Id:/machine_wide",
"/MTd", 
/* static runtime lib */ 
/* "/Zi", include this for debug builds */
/* current VSCode file */
"${file}",
/* notice how this is found by  looking into the /LIBPATH: */
"sqlite3.lib",
/* could not make clang-cl understand /Fe: */
/* also place it as the last arg before /link */
"/o${fileDirname}\\bin\\${fileBasenameNoExtension}.exe",
"/link",
"/VERSION:0.2", 
"/SUBSYSTEM:CONSOLE" ,
"/LIBPATH:d:/machine_wide/sqlite3/bin"
],
```

Make sure clang-cl.exe location is added to the path. Location example form this machine:

`D:/PROD/programs/Microsoft Visual Studio/2019/Community/VC/Tools/Llvm/x64/bin/`

Alternatively can do the full path in the `tasks.json` file, for the command value. 

Due to `"/Id:/machine_wide"` above, one will include the sqlite like so:

```cpp
#include <sqlite3/sqlite3.h>
```