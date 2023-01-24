// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2015 - 2017 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_DETAIL_OPTIONAL_CONFIG_AJK_28JAN2015_HPP
#define BOOST_OPTIONAL_DETAIL_OPTIONAL_CONFIG_AJK_28JAN2015_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if (defined BOOST_NO_CXX11_RVALUE_REFERENCES) || (defined BOOST_OPTIONAL_CONFIG_NO_RVALUE_REFERENCES)
# define BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
#endif

#if BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION,<=700)
// AFAICT only Intel 7 correctly resolves the overload set
// that includes the in-place factory taking functions,
// so for the other icc versions, in-place factory support
// is disabled
# define BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT
#endif

#if BOOST_WORKAROUND(__BORLANDC__, <= 0x551)
// BCB (5.5.1) cannot parse the nested template struct in an inplace factory.
# define BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT
#endif

#if !defined(BOOST_OPTIONAL_NO_INPLACE_FACTORY_SUPPORT) \
    && defined BOOST_BCB_PARTIAL_SPECIALIZATION_BUG
// BCB (up to 5.64) has the following bug:
//   If there is a member function/operator template of the form
//     template<class Expr> mfunc( Expr expr ) ;
//   some calls are resolved to this even if there are other better matches.
//   The effect of this bug is that calls to converting ctors and assignments
//   are incorrectly sink to this general catch-all member function template as shown above.
# define BOOST_OPTIONAL_WEAK_OVERLOAD_RESOLUTION
#endif

#if !defined(BOOST_NO_MAY_ALIAS)
// GCC since 3.3 and some other compilers have may_alias attribute that helps to alleviate
// optimizer issues with regard to violation of the strict aliasing rules. The optional< T >
// storage type is marked with this attribute in order to let the compiler know that it will
// alias objects of type T and silence compilation warnings.
# define BOOST_OPTIONAL_DETAIL_USE_ATTRIBUTE_MAY_ALIAS
#endif

#if (defined(_MSC_VER) && _MSC_VER <= 1800)
// on MSCV 2013 and earlier an unwanted temporary is created when you assign from
// a const lvalue of integral type. Thus we bind not to the original address but
// to a temporary. 
# define BOOST_OPTIONAL_CONFIG_NO_PROPER_ASSIGN_FROM_CONST_INT
#endif

#if (defined __GNUC__) && (!defined BOOST_INTEL_CXX_VERSION) && (!defined __clang__)
// On some GCC versions an unwanted temporary is created when you copy-initialize
// from a const lvalue of integral type. Thus we bind not to the original address but
// to a temporary.

# if (__GNUC__ < 4)
#  define BOOST_OPTIONAL_CONFIG_NO_PROPER_CONVERT_FROM_CONST_INT
# endif

# if (__GNUC__ == 4 && __GNUC_MINOR__ <= 5)
#  define BOOST_OPTIONAL_CONFIG_NO_PROPER_CONVERT_FROM_CONST_INT
# endif

# if (__GNUC__ == 5 && __GNUC_MINOR__ < 2)
#  define BOOST_OPTIONAL_CONFIG_NO_PROPER_CONVERT_FROM_CONST_INT
# endif

# if (__GNUC__ == 5 && __GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ == 0)
#  define BOOST_OPTIONAL_CONFIG_NO_PROPER_CONVERT_FROM_CONST_INT
# endif

#endif // defined(__GNUC__)

#if (defined __GNUC__) && (!defined BOOST_NO_CXX11_RVALUE_REFERENCES)
// On some initial rvalue reference implementations GCC does it in a strange way,
// preferring perfect-forwarding constructor to implicit copy constructor.

# if (__GNUC__ == 4 && __GNUC_MINOR__ == 4)
#  define BOOST_OPTIONAL_CONFIG_NO_LEGAL_CONVERT_FROM_REF
# endif

# if (__GNUC__ == 4 && __GNUC_MINOR__ == 5)
#  define BOOST_OPTIONAL_CONFIG_NO_LEGAL_CONVERT_FROM_REF
# endif

#endif // defined(__GNUC__)

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_DECLTYPE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800) && !BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40500) && !defined(__SUNPRO_CC)
  // this condition is a copy paste from is_constructible.hpp
  // I also disable SUNPRO, as it seems not to support type_traits correctly
#else
# define BOOST_OPTIONAL_DETAIL_NO_IS_CONSTRUCTIBLE_TRAIT
#endif

#if defined __SUNPRO_CC
# define BOOST_OPTIONAL_DETAIL_NO_SFINAE_FRIENDLY_CONSTRUCTORS
#elif (defined _MSC_FULL_VER) && (_MSC_FULL_VER < 190023026)
# define BOOST_OPTIONAL_DETAIL_NO_SFINAE_FRIENDLY_CONSTRUCTORS
#elif defined BOOST_GCC && !defined BOOST_GCC_CXX11
# define BOOST_OPTIONAL_DETAIL_NO_SFINAE_FRIENDLY_CONSTRUCTORS
#elif defined BOOST_GCC_VERSION && BOOST_GCC_VERSION < 40800
# define BOOST_OPTIONAL_DETAIL_NO_SFINAE_FRIENDLY_CONSTRUCTORS
#endif


// Detect suport for defaulting move operations
// (some older compilers implement rvalue references,
// defaulted funcitons but move operations are not special members and cannot be defaulted)

#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
# define BOOST_OPTIONAL_DETAIL_NO_DEFAULTED_MOVE_FUNCTIONS
#elif BOOST_WORKAROUND(BOOST_MSVC, < 1900)
# define BOOST_OPTIONAL_DETAIL_NO_DEFAULTED_MOVE_FUNCTIONS
#elif BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40600)
# define BOOST_OPTIONAL_DETAIL_NO_DEFAULTED_MOVE_FUNCTIONS
#endif


#ifdef BOOST_OPTIONAL_CONFIG_NO_DIRECT_STORAGE_SPEC
# define BOOST_OPTIONAL_DETAIL_NO_DIRECT_STORAGE_SPEC
#endif


#endif // header guard

/* optional_config.hpp
ndV8TgA+q9ocUW6us7teN/JtpeZNsl8+/zah6waEXM5UFNXPIQosnyiryR4uvwq8kVua+FU9BWu1b3IfH7njJl61arzlETqpoJmKuY48nejPNxA79KGVz+zVGlRdrX4TYF31pQo3vK0KcHk96W66zXqt9hzXaj3xatR2duZvKzTpY+Kr4Un3QIvvLRKDyFgmGSnbYfiEtCdL0o9h4pI/2rZCkrtr9G1YiGZpI3ZiYK6QGSvqE+pG0DPtK/slxpSl+hi0XtMET0PEAG9U4DfbB9f4VEwjI1B74jtCwuIRlU3sT3gqt7AEiVc7E/jcuc6kwqA9X41t9u31V+lr+HU6b3yVA7S1V8/xCO2iuFupbEa/2+07ztTYjOp/vZI/B019G3bWyaSdHlc5KbZk2RiOGoYXbrwzJvX1MvNwij1g3hHmLVJuRaZeMxM9VBV12O1ZFjkS47XoalXY6Jd/Jf3bEsQraEr7mH1sUvgmgKXv3LYNAP6aLZgmKwx9jvwIUqrEp7yJIa5kGgHmKQ8Z0b5i3nmop1XfWyEKW+LAcEr9op8TE2tQWopm/9wPAEAnD2VcBow17g9+djNtrk66oeTuvFzAq3TCxOwplzGoyWmlKSOwNvCjs0ot5dfE9oTfYNANfjeAEK1y9aAe/KlCDoJa7UVlub9lqzXg8y46/sHSs8Xhfwxnl8CXsMAeCVmMWLZZBz1Vx2QPBSSqATzy
*/