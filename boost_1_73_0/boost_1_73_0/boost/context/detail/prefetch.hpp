//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_PREFETCH_H
#define BOOST_CONTEXT_DETAIL_PREFETCH_H

#include <cstddef>
#include <cstdint>

#include <boost/config.hpp>
#include <boost/predef.h>

#include <boost/context/detail/config.hpp>

#if BOOST_COMP_INTEL || BOOST_COMP_INTEL_EMULATED
#include <immintrin.h>
#endif

#if BOOST_COMP_MSVC && !defined(_M_ARM) && !defined(_M_ARM64)
#include <mmintrin.h>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

#if BOOST_COMP_GNUC || BOOST_COMP_CLANG
#define BOOST_HAS_PREFETCH 1
BOOST_FORCEINLINE
void prefetch( void * addr) {
    // L1 cache : hint == 1
    __builtin_prefetch( addr, 1, 1);
}
#elif BOOST_COMP_INTEL || BOOST_COMP_INTEL_EMULATED
#define BOOST_HAS_PREFETCH 1
BOOST_FORCEINLINE
void prefetch( void * addr) {
    // L1 cache : hint == _MM_HINT_T0
    _mm_prefetch( (const char *)addr, _MM_HINT_T0);
}
#elif BOOST_COMP_MSVC && !defined(_M_ARM) && !defined(_M_ARM64)
#define BOOST_HAS_PREFETCH 1
BOOST_FORCEINLINE
void prefetch( void * addr) {
    // L1 cache : hint == _MM_HINT_T0
    _mm_prefetch( (const char *)addr, _MM_HINT_T0);
}
#endif

inline
void prefetch_range( void * addr, std::size_t len) {
#if defined(BOOST_HAS_PREFETCH)
    void * vp = addr;
    void * end = reinterpret_cast< void * >(
        reinterpret_cast< uintptr_t >( addr) + static_cast< uintptr_t >( len) );
    while ( vp < end) {
        prefetch( vp);
        vp = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( vp) + static_cast< uintptr_t >( prefetch_stride) );
    }
#endif
}

#undef BOOST_HAS_PREFETCH

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_PREFETCH_H

/* prefetch.hpp
WJ3zrqBwrol7H1YfLMORC4x/Xc9Yv4GjCh3C0Sgv1GIDF/WdKccwT34ylBdeMo/9RepHobUgOAiitw/ZUDQHWtLYeaZ/aG12h95TDtxUtB4iBQIPam0ZOviwX4OAzcZ9s2dDt+gyys0uv0rTBUrxZ0elkmhlqi2moBSci620CAQiJ1rqM1xVMNzmyhkKv3SXQWodm71kKjHxRRyl0TwKEktDm5D3u/tpEXiWU5dWr5Mp9+cvVGQ1U2OUhJVjHZzAXxb8W2QdeBYXbzaM9mcFfSDoX+rkYjMthXDWrB4hIMJMj4Z2njqQcDR9Hf8yCoLoJojmrp6ODbPgCU/L+iTpoeJbPZqej+G8/x/lgV/2fC2SfakVHj2laDe9UGbF87ucU1J3zf7d35ZTMjMD97PrB+5HP/DTleUaK27xBICnIcVeuoxD+OwGS8+KqcKTS5q6vCy6Blb2TtEnUdc0olXaePo87Jcsw+swugmzyDhZL6/FYJRR4nngBkmEe/Vj/NTqfouOxicTHON/qL5/bf0DUEsDBAoAAAAIAC1nSlLUSBQsRgYAANUOAAAxAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9BV1NfU0lHVjQuM1VUBQABtkgkYMVXbW/b
*/