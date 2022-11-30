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

#if BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x551)
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
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
*/