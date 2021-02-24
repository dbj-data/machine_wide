<h1>The Design</h1>

- [1. Software Architecture Principles](#1-software-architecture-principles)
  - [1.1. Single OS](#11-single-os)
  - [1.2. Single API](#12-single-api)
  - [1.3. SEH](#13-seh)
  - [1.4. Windows mechanisms and subsystems](#14-windows-mechanisms-and-subsystems)
  - [1.5. Preferred Windows System language circa 2021](#15-preferred-windows-system-language-circa-2021)
    - [1.5.1. Avoid C++ decorations that might "sink the Vasa".](#151-avoid-c-decorations-that-might-sink-the-vasa)
  - [1.6. Single IDE](#16-single-ide)
  - [1.7. MS STL](#17-ms-stl)
    - [1.7.1. Be careful to avoid std lib legacy labyrinth](#171-be-careful-to-avoid-std-lib-legacy-labyrinth)
    - [1.7.2. SEH](#172-seh)
    - [1.7.3. clang-cl](#173-clang-cl)
  - [1.8. ISO C](#18-iso-c)
  - [1.9. Do not develop it if it exist](#19-do-not-develop-it-if-it-exist)
  - [1.10. VALSTAT](#110-valstat)
  - [1.11. Primary Objective](#111-primary-objective)

Platform is the core requirement:

The "Key Stake Holders" have decided the Business will be selling software systems and services to customers using Windows platform and/or Azure Cloud platform.

# 1. Software Architecture Principles 

## 1.1. Single OS

Do not architect or develop "OS agnostic" software on any level, from macro to micro. Platform is fixed and it is Windows 10.

[Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10) is in active development and use. But mainly for Azure Linux customers.

## 1.2. Single API

WIN32. Windows API is WIN32. WIN32 is C API. Undefined C, close to C98.

## 1.3. SEH

Structured Exception Handling is intrinsic to WIN32 (and Windows). Use it.

## 1.4. Windows mechanisms and subsystems

There is a myriad of WIN features subsystems and mechanisms. Investigate and use accordingly.

- Services
- (D)COM(+)
- MS RPC
- WMI
- ADS
- WSH
- MSMQ
- Kernel
- etc...

Legacy:

- ATL
- comdef.h
- ADO
- OLE DB
- ODBC
- etc ...

All works and all in use by a lot of customers. Over last few decades.

## 1.5. Preferred Windows System language circa 2021

Squarely and firmly: C++ . C id and was actively discouraged. Very recently there are some movement in the opposite direction, like C11/C17 official introduction into the cl.exe

### 1.5.1. Avoid C++ decorations that might ["sink the Vasa"](https://www.stroustrup.com/P0977-remember-the-vasa.pdf).

That means basically stick to C++ core language.

- very cautious sprinkling of classes
- no c++ meta programing
- no inheritance
  - template as interface abstraction is encouraged
- no C++ DLL's
- static lib's whenever possible
- no containers everywhere
- no std lib algorithms everywhere

Be pragmatic. Develop (and ask for) consistent set of requirements. Not for snazzy C++ abstractions. 

## 1.6. Single IDE

Visual Studio (always the latest)

VS Code is good editor/IDE for so called "full stack developers". NODE.JS, React, GO, Python, C# and such. It is developed by and geared towards non C++ projects. C/C++ Code extensions works but has a lot of bugs and issues as soon as one tries anything beyond trivial. It is developed by very small team of Type Script developers. Thus it is difficult to communicate with them on non-trivial C++ compilation or development themes.

## 1.7. MS STL

Very fast when compiled in non C++ exceptions mode. No reason to use some other C++ libs collected around the GitHub. For example: MS STL std::vector is almost 50% faster vs EASTL vector. In release non C++ exceptions mode.

### 1.7.1. Be careful to avoid std lib legacy labyrinth

- no <iostream>
- no <system_error>
- no <exception>
- be very economical with std::string
- do not be afraid of mixing into your C++ code, modern ISO C features
  - [VLA](https://gustedt.wordpress.com/2014/09/08/dont-use-fake-matrices/)
  - [compound literals](https://gustedt.wordpress.com/?s=compound+literals)
  - mature and useful numerous `__attribute__(())` extensions

Avoid C++ abstractions for the sake of abstractions.  Apparently the word is now, Windows itself is developed in "C with classes" using cpp files. I think that is a "kindergarten syndrome". Very little experience and very little Architecture.

If you want to get a glimpse of what "grown ups" from MSFT think and how do they develop in C++, look up and study the [WIL](https://github.com/microsoft/wil) library. 

### 1.7.2. SEH

TO the surprise of many MS STL has been designed to work with no C++ exceptions too. In which case it uses SEH. That is: it raises Structured Exceptions.

In the "SEH mode", MS STL compared to EASTL is it seems very fast. 

### 1.7.3. clang-cl

Use always. Contrary to cl.exe it allows for powerful mix and match of C11/17 and ISO C++ in one cpp file. It is part of Visual Studio installation.

## 1.8. ISO C

## 1.9. Do not develop it if it exist

- if it is free and open source then generally yes but
  - that requires time for search and testing
  - sometimes so much time it is more feasible to develop it in house

## 1.10. VALSTAT

Wherever and whenever feasible use `valstat`, call return protocol. It C++ implementation is defined in [P2192R3](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2192r3.pdf).

Here, defined and used in the "top level" headers, aka "dbj".

## 1.11. Primary Objective

Simple Code. Readable Code. Maintainable Code.