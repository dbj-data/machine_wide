# Todo

## Try to rediscover how you where doing COM in C++ only; with no IDL

- [COM Clients and Servers](https://docs.microsoft.com/en-us/windows/win32/com/com-clients-and-servers)
- [Defining COM Interfaces](https://docs.microsoft.com/en-us/windows/win32/com/defining-com-interfaces)
  - https://stackoverflow.com/questions/6509032/how-to-define-implementation-of-a-com-coclass

- Start [here](https://docs.microsoft.com/en-us/cpp/windows/attributes/coclass?view=msvc-160), probably
    - also informative: https://limbioliong.wordpress.com/2011/10/23/the-significance-of-the-com-coclass/
- [Compiler COM Support](https://docs.microsoft.com/en-us/cpp/cpp/compiler-com-support?view=msvc-160) seems to be designed for consuming the results of the [#import](https://docs.microsoft.com/en-us/cpp/preprocessor/hash-import-directive-cpp?view=msvc-160) directive
  - and that seems to require type library
  - [comdef.h](https://docs.microsoft.com/en-us/cpp/cpp/compiler-com-support-classes?view=msvc-160) is certainly the place to start from
    - [__uuidof Operator](https://docs.microsoft.com/en-us/cpp/cpp/uuidof-operator?view=msvc-160) seems promising
- [#import page](https://docs.microsoft.com/en-us/cpp/preprocessor/hash-import-directive-cpp?view=msvc-160) is a treasure trove, where the solution lies
  - one IDL with one co_class should be created and used and then generated headers examined.

## [@corob_msft](https://github.com/corob-msft) claims SEH and comdef are working together "accidentaly"

- investigate https://docs.microsoft.com/en-us/cpp/cpp/set-com-error-handler?view=msvc-160

## clang std switch is very powerfull

```
note: use 'c89', 'c90', or 'iso9899:1990' for 'ISO C 1990' standard
note: use 'iso9899:199409' for 'ISO C 1990 with amendment 1' standard
note: use 'gnu89' or 'gnu90' for 'ISO C 1990 with GNU extensions' standard
note: use 'c99' or 'iso9899:1999' for 'ISO C 1999' standard
note: use 'gnu99' for 'ISO C 1999 with GNU extensions' standard
note: use 'c11' or 'iso9899:2011' for 'ISO C 2011' standard
note: use 'gnu11' for 'ISO C 2011 with GNU extensions' standard
note: use 'c17', 'iso9899:2017', 'c18', or 'iso9899:2018' for 'ISO C 2017' standard
note: use 'gnu17' or 'gnu18' for 'ISO C 2017 with GNU extensions' standard
note: use 'c2x' for 'Working Draft for ISO C2x' standard
note: use 'gnu2x' for 'Working Draft for ISO C2x with GNU extensions' standard
```