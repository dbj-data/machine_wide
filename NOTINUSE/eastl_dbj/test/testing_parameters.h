#pragma once
/*
the hammer:

declare vector of strings
 loop outer_loop_size times
    loop inner_test_loop_size_ times
        add to vector an string of size N

 roadmap: parameters to be in an ini file
*/
namespace {

constexpr size_t ONE_MILLION = 1000000;

// we know relese builds are faster vs debug builds
// we compare the speed of MS STL vs EASTL relative to each other
// we do not want to wait to debug builds for a lot of seconds
#ifdef _DEBUG
constexpr size_t inner_test_loop_size_ = ONE_MILLION / 3 ;
constexpr size_t outer_loop_size{ 3 };
#else // NDEBUG
constexpr size_t inner_test_loop_size_ = ONE_MILLION * 2 ;
constexpr size_t outer_loop_size{ 10 };
#endif // NDEBUG

} // ns

