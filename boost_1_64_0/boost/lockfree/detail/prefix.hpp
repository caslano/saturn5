//  Copyright (C) 2009, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_PREFIX_HPP_INCLUDED
#define BOOST_LOCKFREE_PREFIX_HPP_INCLUDED

/* this file defines the following macros:
   BOOST_LOCKFREE_CACHELINE_BYTES: size of a cache line
   BOOST_LOCKFREE_PTR_COMPRESSION: use tag/pointer compression to utilize parts
                                   of the virtual address space as tag (at least 16bit)
*/

#if defined(__s390__) || defined(__s390x__)
    #define BOOST_LOCKFREE_CACHELINE_BYTES 256
#elif defined(powerpc) || defined(__powerpc__) || defined(__ppc__)
    #define BOOST_LOCKFREE_CACHELINE_BYTES 128
#else
    #define BOOST_LOCKFREE_CACHELINE_BYTES 64
#endif

#include <boost/predef.h>

#if BOOST_ARCH_X86_64 || defined (__aarch64__)
#define BOOST_LOCKFREE_PTR_COMPRESSION 1
#endif

#endif /* BOOST_LOCKFREE_PREFIX_HPP_INCLUDED */

/* prefix.hpp
HsfBHg3ZyZu7+HdRci8AHH1BCrMj4ndIc1cQqxGQJWkYLfjoegM2/1DRww+sg4kHDkSwRwatbF7EfK9JTS5MAkriDrGqbpefOV475ueEHArpyY9ABtHm76UnzermxiTQ/idpyegh3+N+CA302PzFrtcdbCpqwyIIlLW9k6hC5YktkA1Soi1RkJNUD/cJklu5AIxJXDRAEOTzlMt4nnYE+GvMqueo05SuKwCpLsw7DasoSNdDRfaQS8sbAHbETJK4NUMVZNUgAL6ZLz7OnuwIflBEn4neV/ye/euBPWO2+3Vr69572YMryysZ/zV9Vdl4YMALttLLO0Opcp2GUqGQnnFh3oKhB+JPZvYrwL+tYMaIzVt30p8D6OHBWy2gu1u/qtYbe+khlI/cZqm9lv1+wYJQk0GZjpuUT5p2zzLicEhBdbk94nJc0ywe5g4TlX+67rRaD37GiqLiif5Z6c7hk09NB1eeaHWG439T50ksgYB82xuqkvt00ant1lfeAld656RE876L+10ORdsuJeoHtoRh9M6GnN6rHX0KpRFmBpvJPUpG0EZgIl+dgQ==
*/