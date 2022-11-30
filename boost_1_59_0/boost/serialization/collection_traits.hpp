#ifndef BOOST_SERIALIZATION_COLLECTION_TRAITS_HPP
#define BOOST_SERIALIZATION_COLLECTION_TRAITS_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// collection_traits.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// This header assigns a level implemenation trait to a collection type
// for all primitives.  It is needed so that archives which are meant to be
// portable don't write class information in the archive.  Since, not all
// compiles recognize the same set of primitive types, the possibility
// exists for archives to be non-portable if class information for primitive
// types is included.  This is addressed by the following macros.
#include <boost/config.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>
#include <climits> // ULONG_MAX
#include <boost/serialization/level.hpp>

#define BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(T, C)          \
template<>                                                          \
struct implementation_level< C < T > > {                            \
    typedef mpl::integral_c_tag tag;                                \
    typedef mpl::int_<object_serializable> type;                    \
    BOOST_STATIC_CONSTANT(int, value = object_serializable);        \
};                                                                  \
/**/

#if defined(BOOST_NO_CWCHAR) || defined(BOOST_NO_INTRINSIC_WCHAR_T)
    #define BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER_WCHAR(C)
#else
    #define BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER_WCHAR(C)   \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(wchar_t, C)        \
    /**/
#endif

#if defined(BOOST_HAS_LONG_LONG)
    #define BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER_INT64(C)    \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(boost::long_long_type, C)  \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(boost::ulong_long_type, C) \
    /**/
#else
    #define BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER_INT64(C)
#endif

#define BOOST_SERIALIZATION_COLLECTION_TRAITS(C)                     \
    namespace boost { namespace serialization {                      \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(bool, C)            \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(char, C)            \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(signed char, C)     \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(unsigned char, C)   \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(signed int, C)      \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(unsigned int, C)    \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(signed long, C)     \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(unsigned long, C)   \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(float, C)           \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(double, C)          \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(unsigned short, C)  \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER(signed short, C)    \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER_INT64(C)            \
    BOOST_SERIALIZATION_COLLECTION_TRAITS_HELPER_WCHAR(C)            \
    } }                                                              \
    /**/

#endif // BOOST_SERIALIZATION_COLLECTION_TRAITS

/* collection_traits.hpp
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
*/