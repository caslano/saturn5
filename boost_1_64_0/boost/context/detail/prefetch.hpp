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
u5BKjZfUN3XXViY2ieQQtI/n/NIBEIGTB8voprPqYO7mmlJys7Eu67hQvo9+szIXAdOUgeDbiQ9F+bVL0OE+YvmcbEO+R07PPrFCx1H5IXmLy6OjjNNWCGjmVIwpNlv1gIHepZVymnUPTcx9i9pXd43jfEIlCpER9w5o/ycGzDYIQkrBhx3xEdX7gYzSTVUOBLqQR6cztzPthYTZauCIKKBrKgVhWHurldjfLOwM3u9lWwHY/Z5TU7RvbijYsBpaFF2D7IuRxD1izc0dSWlzDEHODn1EB6y+mSA/7rQeAAdH0/BzwlXm/IuXh3m/XOB8GFWoXsi9jMYBtoJmi3fZjzlD82MJw8YjRfL3kbbVXbceDGHOSlp0jBgWrW47bhL5P/Pgfwikaz5JoNLDI48Hmg/SJKdjOx+JdZRQrOPxYLFWb2h9GQwVxeiSBK3T8sZz3axtbSdO+Sk2xPc0CxdnAfu4EKwJMu9k4P4bnedmH+lxskbLqVS/7jIOqHh7q145LwaqgtZ6klNQAYahlrQtMSQzNLDEWEQ8sYUOY1m8cA8pVIRqEyS7nZNWsA==
*/