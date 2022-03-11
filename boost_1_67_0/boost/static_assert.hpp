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

#ifdef __BORLANDC__
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
template<int x> struct static_assert_test{};

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