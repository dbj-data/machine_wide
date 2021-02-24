#pragma once
/*
* (c) 2021 by dbj@dbj.org https://dbj.org/license_dbj
*
* Inspired by  https://github.com/dbj-data/machine_wide/blob/master/slot/packed_array.md
*/

#include <type_traits>

namespace dbj
{
	// repeating here to cut dependancies
	struct no_copy_no_move
	{
	protected:
		explicit no_copy_no_move() noexcept = default;
		virtual ~no_copy_no_move() noexcept = default;
		no_copy_no_move(no_copy_no_move const&) noexcept = delete;
		no_copy_no_move& operator = (no_copy_no_move const&) noexcept = delete;

		no_copy_no_move(no_copy_no_move&&) noexcept = delete;
		no_copy_no_move& operator = (no_copy_no_move&&) noexcept = delete;
	};

	template<
		typename element_type,
		std::enable_if_t<  std::is_default_constructible_v<element_type>, int > = 0
	>
		struct packed_array final
		:private no_copy_no_move
	{
		using type = packed_array;
		using value_type = element_type;
		using id_type = unsigned;

		constexpr static size_t MAX_OBJECTS = 64 * 1024;
		constexpr static size_t INDEX_MASK = 0xffff;
		constexpr static size_t NEW_OBJECT_ID_ADD = 0x10000; // aka (int)65536

		// "special values" are not excatly a good design, I know
		constexpr static id_type invalid_id = (id_type)(-1);

		using ushort = unsigned short;

		// aka Slot aka Handle aka Index
		// author of packed array is not exposing the handle but the id_type of the handle
		// that confuses the design slightly
		// but simplifies the implementation and makes it more resilient
		// carrying arround id_type aka unsigned int imposes no performance 
		// or complexity penalty
		struct Handle final
		{
			id_type id{};
			ushort index{};
			ushort next{};

			// do not add anything but data in here as that 
			// will make it not a trivial structure aka "not a pod"
			// and that will provoke compiler to generate large hidden scafolding
		};


		unsigned num_objects_{};


		unsigned size() const noexcept {
			return num_objects_;
		};
		// native arrays of Objects are somewhat troublesome in C++
		// this effectively requires Objects to be trivially constructible
		value_type objects_[MAX_OBJECTS]{};
		Handle handles_[MAX_OBJECTS]{};
		ushort freelist_enqueue_{};
		ushort freelist_dequeue_{};

		explicit packed_array() noexcept
		{
			num_objects_ = 0;
			for (unsigned i = 0; i < MAX_OBJECTS; ++i)
			{
				// MSVC use of designated initializers requires at least '/std:c++latest'
				handles_[i] = Handle{ /*.id =*/ i, /*.index =*/ ushort(0), /*.next =*/ ushort(i + 1) };
			}
			freelist_dequeue_ = 0;
			freelist_enqueue_ = MAX_OBJECTS - 1;
		}

		// this effectivley means id is in the range 
		bool valid_id(id_type id) const noexcept {

			// also covers the invalid_id case 
			// as it is effectively max size_t
			// and we do not allow MAX_OBJECTS to be that big
			// above we have explained id is just a indexes
			// into the internal native arrays in here
			if (
				(id >= 0) && (id < MAX_OBJECTS)
				)
				return true;

			return false;
		}

		// this effectively means Id is in the range AND
		// it point to something meaningfull
		bool has(id_type id) noexcept
		{
			// va the original design this allso slows 
			// down things considerably
			if (valid_id(id)) {
				// how do we know if handle is valid?
				Handle& in = handles_[id & INDEX_MASK];
				return in.id == id && in.index != USHRT_MAX;
			}
			return false;
		}

		// what here?
		// what is "invalid object" ?
		// this is an ugly hack
		inline static const value_type invalid_object{};

		bool is_object_valid(value_type const& specimen_) const noexcept
		{
			return (&specimen_ != &invalid_object);
		}

		value_type& lookup(id_type id) noexcept
		{
			if (has(id)) {
				return objects_[handles_[id & INDEX_MASK].index];
			}
			return const_cast<value_type&>(invalid_object);
		}

		// this is effectively allocation from a stack based array
		// we know what type is id_type so we can copy on return 
		// if id_type would be something more complex we 
		// might return by reference
		// 'add' would be nice and chort name 
		// 'new_element' carries more information and is not too long to type
		// in case of overflow we return invalid_id
		id_type new_element() noexcept
		{
			// this is also a release build operation and slows 
			// down the whole thing
			// alternative is to do debug build 
			// check only with assert
			if (false == ((num_objects_ + 1) < MAX_OBJECTS)) return invalid_id;

			Handle& handle_ = handles_[freelist_dequeue_];
			freelist_dequeue_ = handle_.next;
			handle_.id += NEW_OBJECT_ID_ADD;
			handle_.index = num_objects_++;
			value_type& o = objects_[handle_.index];
			return handle_.id;
			//o.id = handle_.id;
			//return o.id;
		}

		// return true if id_type was valid, false otherwise
		// this is a "big deal" and why handles at all
		// if id would be a pointer it would be imppossible
		// to tell if it points to the array in here or  is it
		// "dangling"
		// unfortunately Alex Stepanov STL has no concept of handles
		bool remove(id_type id)
		{
			Handle& handle_ = handles_[id & INDEX_MASK];

			value_type& o = objects_[handle_.index];
			o = objects_[--num_objects_];
			handles_[o.id & INDEX_MASK].index = handle_.index;

			handle_.index = USHRT_MAX;
			handles_[freelist_enqueue_].next = id & INDEX_MASK;
			freelist_enqueue_ = id & INDEX_MASK;

			return true;
		}
	};

} // namespace dbj