
/*
(c) 2019-2020 by dbj.org   -- LICENSE DBJ -- https://dbj.org/license_dbj/
*/

#ifdef DBJ_USE_WIN32_ALLOC
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#define NOMINMAX
#define STRICT 1
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
/*
 Now here is the secret sauce secret ingredient:
 On windows machine these are faster vs crt malloc/free. Proven and measured.
 PPL.H -- Disclaimer: yes I know about parrallel maloc and free.
 I also know about:  https://stackoverflow.com/a/34326909
*/

// char * buf = DBJ_CALLOC(0xFF, char)
#define DBJ_CALLOC(S_,T_) HeapAlloc(GetProcessHeap(), 0, S_ * sizeof(T_))

// char * buf = (char*)DBJ_MALLOC(0xFF)
#define DBJ_MALLOC( S_) HeapAlloc(GetProcessHeap(), 0, S_)

#define DBJ_FREE(P_) HeapFree(GetProcessHeap(), 0, (void*)P_)

#else // ! DBJ_USE_WIN32_ALLOC

/// standard allocation
/// be advised clang can do some serious magic 
/// while optimizing these calls

#define DBJ_CALLOC(S_,T_) calloc( S_ , sizeof(T_))
#define DBJ_MALLOC(S_)malloc( S_ )
#define DBJ_FREE(P_) free(P_)

#endif // ! DBJ_USE_WIN32_ALLOC

// #include <EASTL/internal/config.h>
#include <EASTL/allocator.h>

namespace dbj {
#ifndef EASTL_USER_DEFINED_ALLOCATOR	

		//#if EASTL_NAME_ENABLED
		//	const char* const heap::name{ EASTL_NAME_VAL(EASTL_ALLOCATOR_DEFAULT_NAME) } ;
		//#endif

// this is a default implementation
// if you think it is feasible to change it, please do

void* heap::allocate(size_t size_  , int /*flags_ = 0 */) noexcept 
{
	return DBJ_MALLOC( size_) ;
}
void  heap::deallocate(void* pointer_  , size_t size_ ) noexcept
{
	DBJ_FREE(pointer_);
}
void* heap::allocate_aligned(size_t size_, size_t alignment_ , size_t /*offset*/, int /*flags = 0 */ ) noexcept
{
	return DBJ_MALLOC( size_) ;
}
void  heap::deallocate_aligned(void* pointer_ , size_t /*size_*/ ) noexcept
{
	DBJ_FREE(pointer_);
}

#endif  // EASTL_USER_DEFINED_ALLOCATOR	
}// dbj