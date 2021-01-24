# W.I.P.

![jester](media/jester_box_cpp_exception.png)

#### DBJ_MACHINE_WIDE=D:\MACHINE_WIDE;

- The most important and only user environment variable. 
  - Please set it now to your machine location of the "machine_wide" repo.
  - Important: notice the semicolon at the end of it.
  - above is example from this machine
- Please add it to the PATH user environment variable

#### DBJ_SQLITE3=D:\MACHINE_WIDE\sqlite3\bin;

- This is where sqlite3.dll is
- This is where sqlite3.lib is

- Please add it to the PATH user environment variable


## Back to the Common

- This is where "machine wide" includes are.

- Opposite to the "single header" philosophy.

- "common headers" philosopohy

- The common "stuff" is not repeated all arround in all the "single headers"

### Cluster of projects

Git sub-modules are used 

1. the users/customers clone/pull all the common stuff they need in one go 
   1. from one place on their machines or one server
2. developers have a single place to manage

### The Management

- The development also happens here and that means a lot of cruft. Potentially.

- Be carefull not to develop in the master branch
- Be carefull to use the master branch when including

## Why or Why Not is something in here

It all depoends how fast it has proven itself. Everything goes through [dbj-bench](https://github.com/dbj-data/dbj-bench) before being accepted.

dbj-bench is built with Visual Studio and it has pretty wide variery of builds. Thus it is not simple. Again the sole purpose is to try and develop very precise benchmarking.

# We need to talk about WIL

[WIL](https://github.com/microsoft/wil) is a treasure trove for anyone using all sorts of realy important WIndows API's. In some pleaces it is using reallu low level legacy stuf (MS RPC), or complex stuff (COM).

WIL is also very revealing on what MSFT top programers think of many thigs you also think about. Like for example `stl.h`. Therefore take some time and think whayt is NOT inside and what is inside.

But "things" will be definitely and regularly "nicked" from WIL and transformed to some dbj win32 internals.