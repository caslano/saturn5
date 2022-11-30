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
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
*/