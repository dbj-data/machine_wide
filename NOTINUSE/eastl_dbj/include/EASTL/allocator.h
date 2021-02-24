/////////////////////////////////////////////////////////////////////////////
// Copyright (c) Electronic Arts Inc. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef EASTL_ALLOCATOR_H
#define EASTL_ALLOCATOR_H

#include <EASTL/internal/config.h>
#include <stddef.h>
#include <malloc.h>

namespace dbj {

	struct heap /*EA_INHERITANCE_FINAL*/
	{
		// users always provide these four functions
		// thus allocator is a compile time decision
		// notice all four are noexcept
		// locking policy is optional and user provided
		// failure policy is optional and user provided

		static void* allocate(size_t /*size_*/ , int /* flags_ */ = 0 ) noexcept ;
		static void  deallocate(void* /*pointer_*/ , size_t /* size_*/ ) noexcept ;

		static void* allocate_aligned(size_t /*size_*/, size_t /*alignment*/, size_t /*offset*/, int /*flags */ = 0 ) noexcept ;
		static void  deallocate_aligned(void* /*pointer_*/ , size_t /*size_*/ ) noexcept ;

// see dbj_allocator.cpp where we define those methods 
// and where we can alternate at compile time
// between implementations

// the feasibility of this is a moot point 
		#if 1 // EASTL_NAME_ENABLED

			const char* name ; 

			heap(const char* some_name_)
				: name(some_name_)
			{
			}

			heap() : name(EASTL_NAME_VAL(EASTL_ALLOCATOR_DEFAULT_NAME)) {}

			heap& operator = (const dbj::heap& other_ )
			{
				if ( this != &other_ ) 
					this->name = other_.name;
				return *this;
			}

		#endif
	};

} // dbj

namespace eastl
{
	// EASTL requires this ...
	inline bool operator == (dbj::heap const&, dbj::heap const&) { return true;  }
}

namespace eastl
{
	using allocator = dbj::heap;

	/// alloc_flags
	///
	/// Defines allocation flags.
	///
	enum alloc_flags 
	{
		MEM_TEMP = 0, // Low memory, not necessarily actually temporary.
		MEM_PERM = 1  // High memory, for things that won't be unloaded.
	};

extern "C" {

	inline allocator* GetDefaultAllocator()
	{
		// since dbj::heap is statics only struct we can do this
		// that is we do not have to dance with a single instance per process
		// and this does not require locking
		static allocator allocator_;
		return &allocator_;
	}


	inline EASTLAllocatorType* get_default_allocator(const EASTLAllocatorType*)
	{
		// since dbj::heap  is statics only struct we can do this
		// that is we do not have to dance with a single instance per process
		// and this does not require locking
		static allocator allocator_;
		return &allocator_;
	}
}

} // namespace eastl


#endif // Header include guard
















