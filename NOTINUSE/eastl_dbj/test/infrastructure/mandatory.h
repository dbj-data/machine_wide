#pragma once

/* (c) 2019-2020 by dbj.org   -- LICENSE DBJ -- https://dbj.org/license_dbj/ */
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdlib.h>
#include <malloc.h>

#ifndef EASTL_USER_DEFINED_ALLOCATOR
// 
// 
//          
inline void* __cdecl operator new[](size_t size, char const*, int, unsigned int, char const*, int)
{
	return calloc(size, sizeof(char));
}

// this is aligned allocation
// vector et. all do require this
// string does not
inline void* __cdecl operator new[](size_t size, size_t alignment, unsigned __int64, char const*, int, unsigned int, char const*, int)
{
	return _aligned_malloc(size, alignment);
	// return calloc(size, sizeof(char));
}
#endif // ! EASTL_USER_DEFINED_ALLOCATOR




