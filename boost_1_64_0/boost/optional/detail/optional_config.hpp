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
mdzic9l/hyoraxqTCD/7iGebc87CutteYFy+VfuZbCUTW1Pv8R7h/v14+lFtXza43Ynfa7eP4DGcO649CSJT4vb4H3nH322kP2voc835rz3+DqobWfdwj7GlXoLLH7c6ftIk96zmW/v80kS6Qc6mPmKbfeiDjwbqRJ7peroU9M7R6YMmaPcv6jOcrVB9UM9f60zx0XxlK89m9xh6rnbTxq5MiC2pkR5WiB5Rv2JND64vCdO9fmW+Cuo+VxzcFqseM+coy1sDMJO+SJsNINZWgb2YdbTZ65b7LIrz7O+s7Z6iJOKsNepcqTz722rzGVaYfha59ybp53Pg23t57XSaA+/KWuow7kTfVbu/iPv8z3npHyW+XZROnPVPlPN9phe1ebjsGXWfrx4TWKeort2csR6hjI+i8u/JdsYi/9RlXNlVxlk6wU6b7KjDedaaQvxP5N4dImkLCZrfOOF+qO0rWPqbxp+bj5ed1vsR/4puE92B3axl/c7a/3HnfIa4LYfbtvqsxZzZ0R3V/bD+sMgYX5xyk7tPHHVDexQ93/dJmwrIaL6xhS4C7fZSnr1cufffXHTM3XUsexndd+XoM//SLmO+NQl7lEwrg3Vwirq76rjTLmU7UvCHXwexC2Zs/jVLR05maP8P2MPVOQbbJ3uwnHDb63Gu067EXNqVsx+dGFx9aJa2b6LbSoTj3rWHLMIVRqIOQ97X6x3eIgfy7F5+Qt8P6dm/utMxWY+lJmW40/GCto8MHru4/BYO7GkeO2HYkLGDVE6SXPvCZ2l399sj+H+xbWu7os6zRNsttQch13Ntf9699FNz1w/ma3eL7H6k5E47xHXWbMrkDHb7yD7XQLmv1+4n2D6kIN9d+47jQNku1W7n2fm/R+v0F7VPmPPFE6xGYobQaLOCdnnWIfN/h9WZIyRqN++wG6uLMXP5i7HOWe47GZzy3qDtw1x9QYZKb8D+Pm1fSO91/og2euWC7FnOyt0DvQ2zj1DOHug7nT3QYncJZfZAZ+XuQZbwyn1tvhnJDmV/YnQ1vCdEBfUR4va+r5390luix7k2fKuwKmGXjgrsk37O9X1/sV+K2mH8qw3WkXp3tGz4zp+unEBc90WPJZ5Iv6XzuhLz4+541koaxe6ixIE/Z1N5pHvvtVOObb5xvldfSqXFp8wv4bcc5ou1ebK+zEb7EbsW35i98HjwzSmVG2ZhCXMa9l/ospwzTfnpgD4rEN60QHju98/tbuD9sxpj/nni2ue9ZBwje8Bpjc75GsfM1U+4z36p9p8g7d+9v6LNRRlAOYmQd2bZrzp9phnDOBeD3cidUPjN915MBxFoc/O1fXOrofedUPgPvlvsmmNIcZsrx9e/A/Hv34lJWoO/k5F3/9aPJkC2SFst1RgQ3qHuVMstt/SMYZOmZ2ZJnxS0t7iV/m56+deU+0z/P6yxgWf7rzqMFt77uILKVvoQwltLeLYOb6Xf6VOsk/r8V+7dGdo+jdNG5eRbybR17eaUXZVVnddQgzlbMge1DuX0iQe1v92+WOtRX1CdSbrc41NJl57oVJHnaKIOY7K/BlK/0Y6z2vjirHd8RazfYGF/gtXOHxdcx+6wnTxrGdcCrvO9S43RdNj3BPIdqvUxwc+24LRKeHm/43zolB5fed3/KP7dz9VMFYBOyx7SkqTjnul3xsyFtP6sr6D1gs/rPkh3eOY0apb+4FMp8Z+s/X9HndWxhrBysp7516vY6rxK3Th3r2wj/rpaP8Sf53nrmqdX0vaD/cV51qywC1ln7cn6+VhKtxodNaGb8ekA7baqfwC7C66iavm2W3/6CuuyG2rSSjUPGjluiPmW0n4Zb5fTYck+OglrmS7Th6w=
*/