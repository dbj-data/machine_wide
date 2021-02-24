#pragma once
/* (c) 2019-2020 by dbj.org   -- LICENSE DBJ -- https://dbj.org/license_dbj/ */


#define VT100_ESC "\x1b["

#define VT100_RESET VT100_ESC "0m"
#define VT100_BOLD VT100_ESC "1m"
#define VT100_INVERSE VT100_ESC "7m"
#define VT100_ULINE VT100_ESC "4m"

#define VT100_LIGHT_GRAY VT100_ESC "90m"
#define VT100_LIGHT_BLUE VT100_ESC "94m"
#define VT100_LIGHT_CYAN VT100_ESC "36m"
#define VT100_LIGHT_YELLOW VT100_ESC "33m"
#define VT100_LIGHT_GREEN VT100_ESC "32m"
#define VT100_LIGHT_RED VT100_ESC "31m"
#define VT100_LIGHT_MAGENTA VT100_ESC "35m"

#if 0

#undef DBJ_EXP_
#undef DBJ_EXP
#define DBJ_EXP_(x) x
#define DBJ_EXP(x) DBJ_EXP_(x)


#undef DBJ_STRINGIZE_
#undef DBJ_STRINGIZE
#define DBJ_STRINGIZE_(x) #x
#define DBJ_STRINGIZE(x) DBJ_STRINGIZE_(x)


#undef  DBJ_PERROR 
#ifdef _DEBUG
#define DBJ_PERROR (perror(__FILE__ " # " DBJ_STRINGIZE(__LINE__))) 
#else
#define DBJ_PERROR
#endif // _DEBUG

#define SX(fmt_, x_) fprintf(stderr, "\n%s " fmt_, #x_, (x_))

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#endif // 0

// the mandatory user delivered alloc / dealloc functions
#include "mandatory.h"

#include <stdio.h>
#include <time.h>

#undef DBJ_PROMPT
#define DBJ_PROMPT(P_, S_) printf("\n" VT100_INVERSE "  %-36s" VT100_RESET VT100_ULINE "%24s" VT100_RESET  , P_, S_)

#undef DBJ_SHOW_
#define DBJ_SHOW(X_) DBJ_PROMPT(#X_, X_)

#undef DBJ_PROLOG
#define DBJ_PROLOG printf("\n\n" VT100_LIGHT_CYAN VT100_INVERSE "%-60s" VT100_RESET, __FUNCSIG__ )

extern "C" {

	enum { buffy_data_count = 0xFF + 0xFF };

	typedef struct buffy {
		char data[buffy_data_count];
	} buffy;

	inline buffy int_to_buff( const char * fmt_, long arg_  ) {
		buffy retval = { {0} }; // no memset necessary
		sprintf_s(retval.data, buffy_data_count, fmt_, arg_ );
		return retval;
	}

	inline buffy double_to_buff( const char * fmt_, double arg_  ) {
		buffy retval = { {0} }; // no memset necessary
		sprintf_s(retval.data, buffy_data_count, fmt_, arg_ );
		return retval;
	}
}
