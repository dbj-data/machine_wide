
Note: Assumption is you know how to do set the project from your Visual Studio. 

##  To use sqlite3 from "MACHINE_WIDE"

1. At run-time `sqlite3.dll` has to be on the path. 
1. At build-time `sqlite3.lib` has to be on the `/LIBPATH`. 

To manage path's on your Windows machine we recommend: [RED (Rapid Environment Editor)](https://www.rapidee.com/en/about)

1. This folder is where `sqlite3.dll` is and where `sqlite3.lib` is
1. add this folder (for example) to `/LIBPATH:d:/machine_wide/lib` -- that is a command line syntax.
   1. same is for clang-cl.exe builds
2. **After** the `/link` switch on the cl.exe command line add `sqlite3.lib` 

Reminder: To include the `sqlite3.h` in your source you need to have this on your compiler command line: `"/Id:/machine_wide"`, or just add that folder to C/C++ directories using VStudio. After which you can do:
```cpp
#include <sqlite3/sqlite3.h>
```