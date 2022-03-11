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