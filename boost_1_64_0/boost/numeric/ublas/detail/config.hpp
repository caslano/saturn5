//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_CONFIG_
#define _BOOST_UBLAS_CONFIG_

#include <cassert>
#include <cstddef>
#include <algorithm>
#include <limits>

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

// C++11
#if defined(__cplusplus) && __cplusplus >= 201103L

#define BOOST_UBLAS_CPP_GE_2011

#elif BOOST_MSVC >= 1800

#define BOOST_UBLAS_CPP_GE_2011

#else

#undef BOOST_UBLAS_CPP_GE_2011 // Make sure no one defined it

#endif

// Microsoft Visual C++
#if defined (BOOST_MSVC) && ! defined (BOOST_STRICT_CONFIG)

// Version 7.1
#if BOOST_MSVC == 1310
// One of these workarounds is needed for MSVC 7.1 AFAIK
// (thanks to John Maddock and Martin Lauer).
#if !(defined(BOOST_UBLAS_NO_NESTED_CLASS_RELATION) || defined(BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION))
#define BOOST_UBLAS_NO_NESTED_CLASS_RELATION
#endif

#endif

#endif


// GNU Compiler Collection
#if defined (__GNUC__) && ! defined (BOOST_STRICT_CONFIG)

#if __GNUC__ >= 4 || (__GNUC__ >= 3 && __GNUC_MINOR__ >= 4)
// Specified by ABI definition see GCC bug id 9982
#define BOOST_UBLAS_USEFUL_ARRAY_PLACEMENT_NEW
#endif

#if __GNUC__ < 3
#define BOOST_UBLAS_UNSUPPORTED_COMPILER 1
#endif

#endif


// Intel Compiler
#if defined (BOOST_INTEL) && ! defined (BOOST_STRICT_CONFIG)

#if defined (BOOST_INTEL_LINUX) && (BOOST_INTEL_LINUX >= 800)
// By inspection of compiler results
#define BOOST_UBLAS_USEFUL_ARRAY_PLACEMENT_NEW
#endif

#if (BOOST_INTEL < 700)
#define BOOST_UBLAS_UNSUPPORTED_COMPILER 1
#endif

// Define swap for index_pair and triple.
#if (BOOST_INTEL <= 800)
namespace boost { namespace numeric { namespace ublas {
    template<class C, class IC>
    class indexed_iterator;

    template<class V>
    class index_pair;
    template<class M>
    class index_triple;
}}}

namespace std {
    template<class V>
    inline
    void swap (boost::numeric::ublas::index_pair<V> i1, boost::numeric::ublas::index_pair<V> i2) {
        i1.swap (i2);
    }
    template<class M>
    inline
    void swap (boost::numeric::ublas::index_triple<M> i1, boost::numeric::ublas::index_triple<M> i2) {
        i1.swap (i2);
    }
    // iter_swap also needed for ICC on Itanium?
    template<class C, class IC>
    inline
    void iter_swap (boost::numeric::ublas::indexed_iterator<C, IC> it1,
                    boost::numeric::ublas::indexed_iterator<C, IC> it2) {
        swap (*it1, *it2);
    }
}
#endif

#endif


// Comeau compiler - thanks to Kresimir Fresl
#if defined (__COMO__) && ! defined (BOOST_STRICT_CONFIG)

// Missing std::abs overloads for float types in <cmath> are in <cstdlib>
#if defined(__LIBCOMO__) && (__LIBCOMO_VERSION__ <= 31)
#include <cstdlib>
#endif

#endif

// PGI compiler
#ifdef __PGIC__
#define BOOST_UBLAS_UNSUPPORTED_COMPILER 0
#endif

//  HP aCC C++ compiler
#if defined (__HP_aCC) && ! defined (BOOST_STRICT_CONFIG)
#  if (__HP_aCC >= 60000 )
#    define BOOST_UBLAS_USEFUL_ARRAY_PLACEMENT_NEW
#endif
#endif


//  SGI MIPSpro C++ compiler
#if defined (__sgi) && ! defined (BOOST_STRICT_CONFIG)

// Missing std::abs overloads for float types in <cmath> are in <cstdlib>
// This test should be library version specific.
#include <cstdlib>

#if __COMPILER_VERSION >=650
// By inspection of compiler results - thanks to Peter Schmitteckert
#define BOOST_UBLAS_USEFUL_ARRAY_PLACEMENT_NEW
#endif

#endif


// Metrowerks Codewarrior
#if defined (__MWERKS__) && ! defined (BOOST_STRICT_CONFIG)

// 8.x
#if __MWERKS__ <= 0x3003
#define BOOST_UBLAS_UNSUPPORTED_COMPILER 1
#endif

#endif


// Detect other compilers with serious defects - override by defineing BOOST_UBLAS_UNSUPPORTED_COMPILER=0
#ifndef BOOST_UBLAS_UNSUPPORTED_COMPILER
#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) || defined(BOOST_NO_SFINAE) || defined(BOOST_NO_STDC_NAMESPACE)
#define BOOST_UBLAS_UNSUPPORTED_COMPILER 1
#endif
#endif

// Cannot continue with an unsupported compiler
#if defined(BOOST_UBLAS_UNSUPPORTED_COMPILER) && (BOOST_UBLAS_UNSUPPORTED_COMPILER != 0)
#error Your compiler and/or configuration is unsupported by this verions of uBLAS. Define BOOST_UBLAS_UNSUPPORTED_COMPILER=0 to override this message. Boost 1.32.0 includes uBLAS with support for many older compilers.
#endif



// Enable performance options in RELEASE mode
#if defined (NDEBUG) || defined (BOOST_UBLAS_NDEBUG)

#ifndef BOOST_UBLAS_INLINE
#define BOOST_UBLAS_INLINE inline
#endif

// Do not check sizes!
#define BOOST_UBLAS_USE_FAST_SAME

// NO runtime error checks with BOOST_UBLAS_CHECK macro
#ifndef BOOST_UBLAS_CHECK_ENABLE
#define BOOST_UBLAS_CHECK_ENABLE 0
#endif

// NO type compatibility numeric checks
#ifndef BOOST_UBLAS_TYPE_CHECK
#define BOOST_UBLAS_TYPE_CHECK 0
#endif


// Disable performance options in DEBUG mode
#else

#ifndef BOOST_UBLAS_INLINE
#define BOOST_UBLAS_INLINE
#endif

// Enable runtime error checks with BOOST_UBLAS_CHECK macro. Check bounds etc
#ifndef BOOST_UBLAS_CHECK_ENABLE
#define BOOST_UBLAS_CHECK_ENABLE 1
#endif

// Type compatibiltity numeric checks
#ifndef BOOST_UBLAS_TYPE_CHECK
#define BOOST_UBLAS_TYPE_CHECK 1
#endif

#endif


/*
 * Type compatibility checks
 *  Control type compatibility numeric runtime checks for non dense matrices.
 *  Require additional storage and complexity
 */
#if BOOST_UBLAS_TYPE_CHECK
template <class Dummy>
struct disable_type_check
{
    static bool value;
};
template <class Dummy>
bool disable_type_check<Dummy>::value = false;
#endif
#ifndef BOOST_UBLAS_TYPE_CHECK_EPSILON
#define BOOST_UBLAS_TYPE_CHECK_EPSILON (type_traits<real_type>::type_sqrt (std::numeric_limits<real_type>::epsilon ()))
#endif
#ifndef BOOST_UBLAS_TYPE_CHECK_MIN
#define BOOST_UBLAS_TYPE_CHECK_MIN (type_traits<real_type>::type_sqrt ( (std::numeric_limits<real_type>::min) ()))
#endif


/*
 * General Configuration
 */

// Proxy shortcuts overload the alreadly heavily over used operator ()
//#define BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS

// In order to simplify debugging is is possible to simplify expression template
// so they are restricted to a single operation
// #define BOOST_UBLAS_SIMPLE_ET_DEBUG

// Use invariant hoisting.
// #define BOOST_UBLAS_USE_INVARIANT_HOISTING

// Use Duff's device in element access loops
// #define BOOST_UBLAS_USE_DUFF_DEVICE

// Choose evaluation method for dense vectors and matrices
#if !(defined(BOOST_UBLAS_USE_INDEXING) || defined(BOOST_UBLAS_USE_ITERATING))
#define BOOST_UBLAS_USE_INDEXING
#endif
// #define BOOST_UBLAS_ITERATOR_THRESHOLD 0

// Use indexed iterators - unsupported implementation experiment
// #define BOOST_UBLAS_USE_INDEXED_ITERATOR

// Alignment of bounded_array type
#ifndef BOOST_UBLAS_BOUNDED_ARRAY_ALIGN
#define BOOST_UBLAS_BOUNDED_ARRAY_ALIGN
#endif

// Enable different sparse element proxies
#ifndef BOOST_UBLAS_NO_ELEMENT_PROXIES
// Sparse proxies prevent reference invalidation problems in expressions such as:
// a [1] = a [0] = 1        Thanks to Marc Duflot for spotting this.
// #define BOOST_UBLAS_STRICT_MAP_ARRAY
#define BOOST_UBLAS_STRICT_VECTOR_SPARSE
#define BOOST_UBLAS_STRICT_MATRIX_SPARSE
// Hermitian matrices use element proxies to allow assignment to conjugate triangle
#define BOOST_UBLAS_STRICT_HERMITIAN
#endif

// Define to configure special settings for reference returning members
// #define BOOST_UBLAS_REFERENCE_CONST_MEMBER
// #define BOOST_UBLAS_PROXY_CONST_MEMBER


// Include type declerations and functions
#include <boost/numeric/ublas/fwd.hpp>
#include <boost/numeric/ublas/detail/definitions.hpp>


#endif


/* config.hpp
nBsnend2VLW5iqP5LcIPwM8O/ARSsLYmW7+/1Dx+kYZ9sfHBvBkS/Cyp/K83bpc1TDGagySgEAlo1OSMBubY4aPRWpCgk4n07pxjk5UiGINDusOv2xvPDL9+zo0j6mrbXJdpLsa7mA7JO/qXM9/izxt6tAyRjlUT/nnUrM6HW0zR/8HB5ushvSPNBwCq9F/OIIWMF4CyFHNAKwt0tWw+5vZp8yf4fMbNaWrHoZNitbx2yt+S04VHIYnQZlfyN2jXz/MxZ8BaWKk8bkHzl2l+hUNZOMOdLhK28BXvLR0y/LwxxtvyWZu1GblFKTMoxNy8uEnJSV6VRNG1few3vTeE779H1MG0n3GDahkfzp2Pv07nL8a9Em10RSdV+Kv0D/D0pAj2CGaZgtuCKaBYb34swJ85JYgxMQMV5ojwG2eGBoE66nKZhCsZDw/Bdg8TGXLkRY0H1RHiv+tpdXmrqGkK2JuKswM2KJrLe9FcLkRzqXhLczFGyXT9iRLUBTbLE8jTC/D+c3H8+mMpIl2BGrQKamEGramEIstYlEjdXAt9jtYsAsFqZGwHfczORVzqL2Ubwp5G4t5tHZ9zX4q+8rpiSVMAU3bHuXJKA52vu23N0Z5BTsXQEi6FtmmV4jvlYbJQ3Vbi81cc8/Dur1FWEJTiUFsQLetUPcrh4fiPtW3KslOf5YFeyWeyF8LZ1+HeeIsfu+2u1T24DoOB0uZHtOMbslJy7ZRQ+P5sY7jw3haCDyUp3ieOclL84gTeSsRbtT4/5vRyOK3Uq2jgQv6ZzskwrNbPzWQnmIlQnLthC0Hot42CzbieKimpSv3RMRxIJRinw5ByW4CU3Bsz77VL8J+Dgeyjy1yozTXOTykq+iNncyCqRqeYpV+XxRTwZOHiGNUPX6qorn8KjiUhndUREFu/Bdp7+1Db8WhtDejl7DG2I6acreYx6XKTdwpil7RmqZdfqvWrx1gZP8d801wI5ewCVS5XyUZ6bs7Vf30eJg11HosZ0juaiU1MX42RPk0ufgsn4BvwJ3VYLvdGcJFNqP7JSzDw9mld41BecJQVWB4L9zMMNxOcvUYKZQ5dHr6pwBYqxZJ5o5riDpfZY27bTIi7WVnAFMrCP3JTQSQXsy2U7mJ5/7o23OE0E/VAkVlVZ0yF6q1U/ZrhQH9xNM1pb1qus3z/AhU98MFYWv+YQRpggI8Lq8pwzo4JspzOlQL/xvmsOmvlqlqXOIbD8crhv74X+s/5ZD/hcJM5DvIJVnMAxM3oace+xPgveE/1tL+/Gf+e5Um8Xyc7LJJ+ecd8HviKG1r7HTJI7y6Wu+Q3ndcwMuDDY4hcggfeq9bh+ijzFk1n62CwK707m/vVdbD7+DPdDr7tZLYbhIgnPBmm0KbklHccKklc7mq1vOZd16S4Dhu2FDlxh36TSmtnsXfnI87dSHDmTec3zI9L8DiV4PebCRZJh46nWkfN1OYmphqX2LBHrMwRuJj/XcwNZ86H/fo1+Zw+IH6Eg1yJMxzxF+tiZ7fk75Szd/zyqNEaXZLbTsmt40rvzoK2cntkcKTRVXjYe8v3eIpsyrjDEYfECdNKbQGSfbckpPAo2B1Te/1tn0GuMEFzNQ6XIS3kU8MZDFb/JXy0P7hgg32qI3RR+Ojfg3Nkr3S6PXQWVg7B4g0ljqnTHaGhmAcH8zaUOKdOdwbHNUxXRK0Qoo5XRP1dOst0PAh7VV0X751LjegKFxuCDNS+qrBmJinf/jjfdyjfOfANz8LU+aePIuCLvS88w6rJO1Qx7Xb2BQuwfEhvuEGlphigh9NZTeG8qV3c2WB/o7LfIvbXGvbCoKjBM16GMKm0y6u8O3NQKBSVUvhM8H0BmVk=
*/