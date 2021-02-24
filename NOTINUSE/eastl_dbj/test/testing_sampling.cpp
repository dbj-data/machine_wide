
#include "infrastructure/dbj_common.h"
#include "testing_parameters.h"

#include <string>
#include <vector>

#include <EASTL/internal/config.h>
#include "EASTL/string.h"
#include "EASTL/vector.h"


//-------------------------------------------------------------------

struct test_data final 
{
	constexpr static const char * small_string {
		"Hello"
	};
	constexpr static const char * big_string {
		"Hello young fellow from the shallow, why are you so mellow?"
			" Perhaps thy friend is a badfellow?"
	};

	static constexpr const char * at (size_t idx_ ) noexcept 
	{
		if (idx_ > 0 )
			return big_string;
		return small_string;
	}
};
//-------------------------------------------------------------------
extern "C" {
	typedef struct rezult_struct_
	{ 
      double eastl_rezult ; 
	  double std_rezult ; 
	} rezult_struct ;
}

template < size_t inner_loop_length, unsigned specimen_index_ >
static rezult_struct performance_test() noexcept
{
	constexpr const char* str_specimen_ = test_data::at(specimen_index_) ;

	// constexpr size_t str_specimen_size_  = sizeof(str_specimen_) ;

	auto test_loop = [&](auto str_specimen, auto vec_of_strings ) {

		auto seconds_ = [](double E_, double S_) 
		    constexpr ->double
		{
			return ((E_)-(S_)) / (CLOCKS_PER_SEC);
		};

		clock_t start = clock();
		for (size_t i = 0; i < inner_loop_length; ++i)
		{
			vec_of_strings.push_back(str_specimen);
		}
		clock_t end = clock();

		return seconds_(end, start) ;
	}; // test_loop

return rezult_struct 
{ 
	test_loop(
		eastl::string{ str_specimen_ },
		eastl::vector<eastl::string>{}
	) , 
	test_loop(
		std::string{ str_specimen_ },
		std::vector<std::string>{}
	)

} ; // eof struct making

} // performance_test

  //-------------------------------------------------------------------

extern "C"  int testing_sampling(const int argc, char** argv)
{
	printf(VT100_LIGHT_BLUE); DBJ_PROMPT( " " , " " ); 
	printf(VT100_LIGHT_BLUE); DBJ_PROMPT( "DBJ CORE EASTL2020" , "(c) 2020 dbj@dbj.org" );
	printf(VT100_LIGHT_BLUE); DBJ_PROMPT( " " , "dbj.org/license_dbj" );
	                          DBJ_PROMPT( " " , " " );

#if _HAS_EXCEPTIONS
	DBJ_PROMPT("_HAS_EXCEPTIONS == ", "1");
#else
	DBJ_PROMPT("_HAS_EXCEPTIONS == ", "0");
#endif

#if EASTL_EXCEPTIONS_ENABLED
	DBJ_PROMPT("EASTL_EXCEPTIONS_ENABLED == ", "1");
#else
	DBJ_PROMPT("EASTL_EXCEPTIONS_ENABLED == ", "0");
#endif

#ifdef __clang__
	DBJ_PROMPT("__clang_", __VERSION__);
#else
	DBJ_PROMPT("_MSC_FULL_VER", int_to_buff("%d", _MSC_FULL_VER).data);
#endif

	DBJ_PROMPT("__cplusplus", int_to_buff("%d", __cplusplus).data);
	DBJ_SHOW(__TIMESTAMP__);

#ifdef _DEBUG
	DBJ_PROMPT("_DEBUG", "debug build");
#else
	DBJ_PROMPT("NDEBUG", "release build");
#endif

	DBJ_PROMPT(" ", " ");
	DBJ_PROMPT("Testing"," vector<string>");
	DBJ_PROMPT("Outer loop size (millions)", int_to_buff("%3d", outer_loop_size ).data );
	DBJ_PROMPT("Inner loop size (millions)", double_to_buff("%3.3f", inner_test_loop_size_ / ONE_MILLION ).data );
	DBJ_PROMPT("2 x Outer loop Inner loop", "append string" );
	DBJ_PROMPT(" ", " ");
	DBJ_PROMPT("Two test strings used", "size");
	DBJ_PROMPT("String 0 ", int_to_buff("%lu", strlen(test_data::at(0) )).data);
	DBJ_PROMPT("String 1 ", int_to_buff("%lu", strlen(test_data::at(1) )).data);

	double total_eastl = 0;
	double total_std   = 0;

	for (size_t k = 0 ; k < outer_loop_size; ++k ) {
		auto r_0 = performance_test<inner_test_loop_size_, 0>();

		total_eastl += r_0.eastl_rezult;
		total_std   += r_0.std_rezult;

		auto r_1 = performance_test<inner_test_loop_size_, 1>();

		total_eastl += r_1.eastl_rezult;
		total_std   += r_1.std_rezult;
	}
	DBJ_PROMPT("Rezults per inner loop","(seconds on average)");
	printf(VT100_LIGHT_RED );
	DBJ_PROMPT("EASTL        rezult ", double_to_buff("%f", total_eastl / outer_loop_size ).data );
	DBJ_PROMPT("STD STL      rezult ", double_to_buff("%f", total_std / outer_loop_size ).data );
	DBJ_PROMPT("Done ...", "");
	printf("\n");

	return EXIT_SUCCESS;
}


#if 0
#ifdef __cpp_deduction_guides
#include <EASTL/array.h>
// Also works with DBJ EASTL 2020
// Requires C++17 or better
static void test_eastl_deduction_guides() {
	{
		eastl::array a = { 1,2,3,4 };
		eastl::vector v = { 1,2,3,4 };

		(void(a));
		(void(v));
	}
}
#endif // __cpp_deduction_guides
#endif // 0