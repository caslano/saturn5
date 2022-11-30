//  (C) Copyright John Maddock 2000.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/static_assert for documentation.

/*
 Revision history:
   02 August 2000
      Initial version.
*/

#ifndef BOOST_STATIC_ASSERT_HPP
#define BOOST_STATIC_ASSERT_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <cstddef> //for std::size_t

#if defined(__GNUC__) && !defined(__GXX_EXPERIMENTAL_CXX0X__)
//
// This is horrible, but it seems to be the only we can shut up the
// "anonymous variadic macros were introduced in C99 [-Wvariadic-macros]"
// warning that get spewed out otherwise in non-C++11 mode.
//
#pragma GCC system_header
#endif

#ifndef BOOST_NO_CXX11_STATIC_ASSERT
#  ifndef BOOST_NO_CXX11_VARIADIC_MACROS
#     define BOOST_STATIC_ASSERT_MSG( ... ) static_assert(__VA_ARGS__)
#  else
#     define BOOST_STATIC_ASSERT_MSG( B, Msg ) static_assert( B, Msg )
#  endif
#else
#     define BOOST_STATIC_ASSERT_MSG( B, Msg ) BOOST_STATIC_ASSERT( B )
#endif

#ifdef BOOST_BORLANDC
//
// workaround for buggy integral-constant expression support:
#define BOOST_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS
#endif

#if defined(__GNUC__) && (__GNUC__ == 3) && ((__GNUC_MINOR__ == 3) || (__GNUC_MINOR__ == 4))
// gcc 3.3 and 3.4 don't produce good error messages with the default version:
#  define BOOST_SA_GCC_WORKAROUND
#endif

//
// If the compiler issues warnings about old C style casts,
// then enable this:
//
#if defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 4)))
#  ifndef BOOST_NO_CXX11_VARIADIC_MACROS
#     define BOOST_STATIC_ASSERT_BOOL_CAST( ... ) ((__VA_ARGS__) != 0)
#  else
#     define BOOST_STATIC_ASSERT_BOOL_CAST( x ) ((x) != 0)
#  endif
#else
#  ifndef BOOST_NO_CXX11_VARIADIC_MACROS
#     define BOOST_STATIC_ASSERT_BOOL_CAST( ... ) (bool)(__VA_ARGS__)
#  else
#     define BOOST_STATIC_ASSERT_BOOL_CAST(x) (bool)(x)
#  endif
#endif

#ifndef BOOST_NO_CXX11_STATIC_ASSERT
#  ifndef BOOST_NO_CXX11_VARIADIC_MACROS
#     define BOOST_STATIC_ASSERT( ... ) static_assert(__VA_ARGS__, #__VA_ARGS__)
#  else
#     define BOOST_STATIC_ASSERT( B ) static_assert(B, #B)
#  endif
#else

namespace boost{

// HP aCC cannot deal with missing names for template value parameters
template <bool x> struct STATIC_ASSERTION_FAILURE;

template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };

// HP aCC cannot deal with missing names for template value parameters
template<std::size_t x> struct static_assert_test{};

}

//
// Implicit instantiation requires that all member declarations be
// instantiated, but that the definitions are *not* instantiated.
//
// It's not particularly clear how this applies to enum's or typedefs;
// both are described as declarations [7.1.3] and [7.2] in the standard,
// however some compilers use "delayed evaluation" of one or more of
// these when implicitly instantiating templates.  We use typedef declarations
// by default, but try defining BOOST_USE_ENUM_STATIC_ASSERT if the enum
// version gets better results from your compiler...
//
// Implementation:
// Both of these versions rely on sizeof(incomplete_type) generating an error
// message containing the name of the incomplete type.  We use
// "STATIC_ASSERTION_FAILURE" as the type name here to generate
// an eye catching error message.  The result of the sizeof expression is either
// used as an enum initialiser, or as a template argument depending which version
// is in use...
// Note that the argument to the assert is explicitly cast to bool using old-
// style casts: too many compilers currently have problems with static_cast
// when used inside integral constant expressions.
//
#if !defined(BOOST_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS)

#if defined(BOOST_MSVC) && defined(BOOST_NO_CXX11_VARIADIC_MACROS)
#define BOOST_STATIC_ASSERT( B ) \
   typedef ::boost::static_assert_test<\
      sizeof(::boost::STATIC_ASSERTION_FAILURE< BOOST_STATIC_ASSERT_BOOL_CAST ( B ) >)>\
         BOOST_JOIN(boost_static_assert_typedef_, __COUNTER__)
#elif defined(BOOST_MSVC)
#define BOOST_STATIC_ASSERT(...) \
   typedef ::boost::static_assert_test<\
      sizeof(::boost::STATIC_ASSERTION_FAILURE< BOOST_STATIC_ASSERT_BOOL_CAST (__VA_ARGS__) >)>\
         BOOST_JOIN(boost_static_assert_typedef_, __COUNTER__)
#elif (defined(BOOST_INTEL_CXX_VERSION) || defined(BOOST_SA_GCC_WORKAROUND))  && defined(BOOST_NO_CXX11_VARIADIC_MACROS)
// agurt 15/sep/02: a special care is needed to force Intel C++ issue an error 
// instead of warning in case of failure
# define BOOST_STATIC_ASSERT( B ) \
    typedef char BOOST_JOIN(boost_static_assert_typedef_, __LINE__) \
        [ ::boost::STATIC_ASSERTION_FAILURE< BOOST_STATIC_ASSERT_BOOL_CAST( B ) >::value ]
#elif (defined(BOOST_INTEL_CXX_VERSION) || defined(BOOST_SA_GCC_WORKAROUND))  && !defined(BOOST_NO_CXX11_VARIADIC_MACROS)
// agurt 15/sep/02: a special care is needed to force Intel C++ issue an error 
// instead of warning in case of failure
# define BOOST_STATIC_ASSERT(...) \
    typedef char BOOST_JOIN(boost_static_assert_typedef_, __LINE__) \
        [ ::boost::STATIC_ASSERTION_FAILURE< BOOST_STATIC_ASSERT_BOOL_CAST( __VA_ARGS__ ) >::value ]
#elif defined(__sgi)
// special version for SGI MIPSpro compiler
#define BOOST_STATIC_ASSERT( B ) \
   BOOST_STATIC_CONSTANT(bool, \
     BOOST_JOIN(boost_static_assert_test_, __LINE__) = ( B )); \
   typedef ::boost::static_assert_test<\
     sizeof(::boost::STATIC_ASSERTION_FAILURE< \
       BOOST_JOIN(boost_static_assert_test_, __LINE__) >)>\
         BOOST_JOIN(boost_static_assert_typedef_, __LINE__)
#elif BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
// special version for CodeWarrior <= 8.x
#define BOOST_STATIC_ASSERT( B ) \
   BOOST_STATIC_CONSTANT(int, \
     BOOST_JOIN(boost_static_assert_test_, __LINE__) = \
       sizeof(::boost::STATIC_ASSERTION_FAILURE< BOOST_STATIC_ASSERT_BOOL_CAST( B ) >) )
#else
// generic version
#  ifndef BOOST_NO_CXX11_VARIADIC_MACROS
#     define BOOST_STATIC_ASSERT( ... ) \
         typedef ::boost::static_assert_test<\
            sizeof(::boost::STATIC_ASSERTION_FAILURE< BOOST_STATIC_ASSERT_BOOL_CAST( __VA_ARGS__ ) >)>\
               BOOST_JOIN(boost_static_assert_typedef_, __LINE__) BOOST_ATTRIBUTE_UNUSED
#  else
#     define BOOST_STATIC_ASSERT( B ) \
         typedef ::boost::static_assert_test<\
            sizeof(::boost::STATIC_ASSERTION_FAILURE< BOOST_STATIC_ASSERT_BOOL_CAST( B ) >)>\
               BOOST_JOIN(boost_static_assert_typedef_, __LINE__) BOOST_ATTRIBUTE_UNUSED
#  endif
#endif

#else
// alternative enum based implementation:
#  ifndef BOOST_NO_CXX11_VARIADIC_MACROS
#    define BOOST_STATIC_ASSERT( ... ) \
         enum { BOOST_JOIN(boost_static_assert_enum_, __LINE__) \
            = sizeof(::boost::STATIC_ASSERTION_FAILURE< (bool)( __VA_ARGS__ ) >) }
#  else
#    define BOOST_STATIC_ASSERT(B) \
         enum { BOOST_JOIN(boost_static_assert_enum_, __LINE__) \
            = sizeof(::boost::STATIC_ASSERTION_FAILURE< (bool)( B ) >) }
#  endif
#endif
#endif // defined(BOOST_NO_CXX11_STATIC_ASSERT)

#endif // BOOST_STATIC_ASSERT_HPP



/* static_assert.hpp
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
*/