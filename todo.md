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