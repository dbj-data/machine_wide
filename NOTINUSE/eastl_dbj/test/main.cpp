/* (c) 2019-2020 by dbj.org   -- LICENSE DBJ -- https://dbj.org/license_dbj/ */

//
// #include "infrastructure/dbj_common.h"

#include "infrastructure/meta.h"
#include "infrastructure/nanoclib.h"
//
extern "C" int testing_sampling(const int argc, char** argv);
//
#ifdef _WIN32
static int program(int argc, char* argv[])
#else
// for non WIN OS-es this is the entry point
int main(int argc, char* argv[])
#endif
{

#if EASTL_EXCEPTIONS_ENABLED
	try {
#endif // EASTL_EXCEPTIONS_ENABLED

		testing_sampling(argc, argv);

#if EASTL_EXCEPTIONS_ENABLED
	}
	catch (std::exception& x_)
	{
		fprintf(stderr, "\nstd::exception \"%s\"", x_.what());
	}
	catch (...)
	{
		fprintf(stderr, "\nUnknown exception ...?");
	}
#endif // EASTL_EXCEPTIONS_ENABLED
return 0 ;
}

/*
WINDOWS and MS STL are using SEH
other OS-es do not
*/
#ifdef _WIN32

#include "infrastructure/win_console.h"
#include "infrastructure/generate_dump.h"

/*
Policy is very simple: 

use /kernel switch or simply do not use any /EH switch
have only one top level function as bellow to catch SE
then generate minidump if SE is raised.

Although this main on Windows works always. With or without
SEH buils. As SEH is intrinsic to Windows.

*/
extern "C"  int main (int argc, char ** argv) 
{
     __try 
    { 
        __try {
			// win_enable_vt_100_and_unicode();
			// ugly hack to enable VT100 on cmd.exe
			system(" ");

			// win_set_console_font(L"Consolas", 18);
			// program is where we might play with
			// C++ exceptions if they happen to
			// be available
			program(argc, argv);
        }
        __finally {
            DBJ_INFO(  ":  __finally block visited");
        }
    }
    __except ( 
        GenerateDump(GetExceptionInformation())
        /* returns 1 aka EXCEPTION_EXECUTE_HANDLER */
      ) 
    { 
        // MS STL "throws" are raised SE's under /kernel builds
        // caught here and nowhere else in the app
         DBJ_ERROR(  ": Structured Exception caught");
        
        DBJ_WARN(  ": %s", 
( dump_last_run.finished_ok == TRUE ? "minidump creation succeeded" : "minidump creation failed" ) 
        );

        if ( dump_last_run.finished_ok ) {
            DBJ_INFO(  ": Dump folder: %s", dump_last_run.dump_folder_name );
            DBJ_INFO(  ": Dump file  : %s", dump_last_run.dump_file_name);
        }
    }

#if defined( _MSC_VER ) && defined( _DEBUG )

#ifdef _KERNEL_MODE
DBJ_INFO(  ": _KERNEL_MODE is defined");
#else // ! _KERNEL_MODE
DBJ_INFO(  ": _KERNEL_MODE is NOT defined");
#endif // !_KERNEL_MODE


#if _HAS_EXCEPTIONS
DBJ_INFO(  ": _HAS_EXCEPTIONS == 1");
#else
DBJ_INFO(  ": _HAS_EXCEPTIONS == 0");
#endif // _HAS_EXCEPTIONS

#if _CPPRTTI 
DBJ_INFO(  ": _CPPRTTI == 1");
#else
DBJ_INFO(  ": _CPPRTTI == 0");
#endif // ! _CPPRTTI

#if _CPPUNWIND 
DBJ_INFO(  ": _CPPUNWIND == 1");
#else // ! _CPPUNWIND 
DBJ_INFO(  ": _CPPUNWIND == 0");
#endif //! _CPPUNWIND 

#endif // _MSC_VER

        DBJ_INFO( ": " DBJ_APP_NAME " " DBJ_APP_VERSION );
        DBJ_INFO(  " ...Leaving... ");

	#ifdef _MSC_VER
	system("@pause");
	#endif // _MSC_VER
	return 42;

} // main

#endif // _WIN32
