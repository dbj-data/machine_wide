<h1> MACHINE_WIDE is W.I.P. </h1>

![jester](media/jester_box_cpp_exception.png)


> **2021 APR** note: Two headed  code organization: DBJ_C and DBJ_CPP are to be on the logical top of includes. That job has just started today.


> DBJ_C and DBJ_CPP are not git subsystems, we just clone them under the common folder that we call "machine wide". 


> Realization is: GIT subsystems are more trouble than worth. If and then, subsystem delete command would exist that might be a signal git subsystems are eminently usable. Let us repeat:

> We are moving away from git subsystems


> **2021 FEB** note: MS STL can be built and used in a so called "kernel" mode. That is a *"big deal"*. That means non standard C++ and non standard std lib, are delivered and maintained by Microsoft.
> 
> No C++ exceptions, and no RTTI
> "kernel" mode does not require using the cl.exe `/kernel` switch. 
> `CPP_UNWIND` is undefined if cl.exe switch `/DNO_EXCEPTIONS=1` is used
> Also keywords: `try`,`throw` and `switch` are rendered non-existent
> [RTTI](https://docs.microsoft.com/en-us/cpp/build/reference/gr-enable-run-time-type-information?view=msvc-160) is switched off by using `/GR-` cl.exe switch

> Quick Start Note: For full foreign repos, if they are not SubModules, please go to their GitHub locations. Usually, here is just a source, used in Windows only builds. 
> For building we use only Visual Studio as IDE and clang-cl as a compiler. For every other "MACHINE_WIDE" stuff, if there are lib's or dll's they are in `~\MACHINE_WIDE\lib`. 
> 
> Perhaps you might add it to your `/LIBPATH`. For happy Visual Studio building (clang-cl or cl) please place your lib's after the `/linker` switch.



#### DBJ_MACHINE_WIDE

- We are aiming for this to be the only user environment variable one might need to use DBJ stuff, "machine wide". 
  - Please set it now to your machine location of the "machine_wide" repo.
  - ours is: `D:\\machine_wide;`
  - Important: notice the semicolon at the end of it.
  - above is location from our DEVL machines
    - If your machines does not have the D drive, you might use the `subst` command to "make fake" `D:` drive
      - Perfectly legal and useful.
- Please add it to the PATH user environment variable

#### `<devl drive>:MACHINE_WIDE\lib;`

- This is where sqlite3.dll is, sqlite3.lib is, etc.
- Please add it to the `/LIBPATH` in your project setup.


## Back to the Common

- Thus that is where "machine wide" includes are.
- Opposite to the "single header" philosophy. Here we are following the "common headers" philosophy
  - The common "stuff" is not repeated "all around the place", in all the "single headers"

### Cluster of projects

Wherever appropriate the Git sub-modules are used 

1. the users/customers clone/pull all the common stuff they need in one go 
   1. from one place on their machines or one server
2. developers have a single place to manage

### The Management

- The development also happens here and that means a lot of cruft. Potentially.

- Be careful not to develop in the master branch
- Be careful to use the master branch when including

## Why or Why Not is something in here

It all depends how fast "something" in the code, has proven itself. Everything goes through [dbj-bench](https://github.com/dbj-data/dbj-bench) before being accepted.

dbj-bench is built with Visual Studio and it has pretty wide variety of builds. That is not simple. Again the sole purpose is to try and develop very precise benchmarking.

## We need to talk about WIL

[WIL](https://github.com/microsoft/wil) is a treasure trove for anyone using all sorts of realy important WIndows API's. In some pleaces it is using reallu low level legacy stuf (MS RPC), or complex stuff (COM).

WIL is also very revealing on what MSFT top programers think of many thigs you also think about. Like for example `stl.h`. Therefore take some time and think whayt is NOT inside and what is inside.

But "things" will be definitely and regularly "nicked" from WIL and transformed to some dbj win32 internals.