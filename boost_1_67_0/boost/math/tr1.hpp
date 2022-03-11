// Copyright John Maddock 2008.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TR1_HPP
#define BOOST_MATH_TR1_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <math.h> // So we can check which std C lib we're using

#ifdef __cplusplus

#include <boost/config.hpp>
#include <boost/static_assert.hpp>

namespace boost{ namespace math{ namespace tr1{ extern "C"{

#else

#define BOOST_PREVENT_MACRO_SUBSTITUTION /**/

#endif // __cplusplus

// we need to import/export our code only if the user has specifically
// asked for it by defining either BOOST_ALL_DYN_LINK if they want all boost
// libraries to be dynamically linked, or BOOST_MATH_TR1_DYN_LINK
// if they want just this one to be dynamically liked:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_MATH_TR1_DYN_LINK)
// export if this is our own source, otherwise import:
#ifdef BOOST_MATH_TR1_SOURCE
# define BOOST_MATH_TR1_DECL BOOST_SYMBOL_EXPORT
#else
# define BOOST_MATH_TR1_DECL BOOST_SYMBOL_IMPORT
#endif  // BOOST_MATH_TR1_SOURCE
#else
#  define BOOST_MATH_TR1_DECL
#endif  // DYN_LINK
//
// Set any throw specifications on the C99 extern "C" functions - these have to be
// the same as used in the std lib if any.
//
#if defined(__GLIBC__) && defined(__THROW)
#  define BOOST_MATH_C99_THROW_SPEC __THROW
#else
#  define BOOST_MATH_C99_THROW_SPEC
#endif

//
// Now set up the libraries to link against:
//
#if !defined(BOOST_MATH_TR1_NO_LIB) && !defined(BOOST_MATH_TR1_SOURCE) \
   && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus)
#  define BOOST_LIB_NAME boost_math_c99
#  if defined(BOOST_MATH_TR1_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
#endif
#if !defined(BOOST_MATH_TR1_NO_LIB) && !defined(BOOST_MATH_TR1_SOURCE) \
   && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus)
#  define BOOST_LIB_NAME boost_math_c99f
#  if defined(BOOST_MATH_TR1_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
#endif
#if !defined(BOOST_MATH_TR1_NO_LIB) && !defined(BOOST_MATH_TR1_SOURCE) \
   && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus) \
   && !defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
#  define BOOST_LIB_NAME boost_math_c99l
#  if defined(BOOST_MATH_TR1_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
#endif
#if !defined(BOOST_MATH_TR1_NO_LIB) && !defined(BOOST_MATH_TR1_SOURCE) \
   && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus)
#  define BOOST_LIB_NAME boost_math_tr1
#  if defined(BOOST_MATH_TR1_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
#endif
#if !defined(BOOST_MATH_TR1_NO_LIB) && !defined(BOOST_MATH_TR1_SOURCE) \
   && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus)
#  define BOOST_LIB_NAME boost_math_tr1f
#  if defined(BOOST_MATH_TR1_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
#endif
#if !defined(BOOST_MATH_TR1_NO_LIB) && !defined(BOOST_MATH_TR1_SOURCE) \
   && !defined(BOOST_ALL_NO_LIB) && defined(__cplusplus) \
   && !defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
#  define BOOST_LIB_NAME boost_math_tr1l
#  if defined(BOOST_MATH_TR1_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
#endif

#if !(defined(BOOST_INTEL) && defined(__APPLE__)) && !(defined(__FLT_EVAL_METHOD__) && !defined(__cplusplus))
#if !defined(FLT_EVAL_METHOD)
typedef float float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == -1
typedef float float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 0
typedef float float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 1
typedef double float_t;
typedef double double_t;
#else
typedef long double float_t;
typedef long double double_t;
#endif
#endif

// C99 Functions:
double BOOST_MATH_TR1_DECL boost_acosh BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_acoshf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_acoshl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_asinh BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_asinhf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_asinhl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_atanh BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_atanhf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_atanhl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_cbrtf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_cbrtl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_copysign BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_copysignf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_copysignl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_erf BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_erff BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_erfl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_erfc BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_erfcf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_erfcl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#if 0
double BOOST_MATH_TR1_DECL boost_exp2 BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_exp2f BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_exp2l BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#endif
double BOOST_MATH_TR1_DECL boost_expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_expm1f BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_expm1l BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#if 0
double BOOST_MATH_TR1_DECL boost_fdim BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_fdimf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_fdiml BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;
double BOOST_MATH_TR1_DECL boost_fma BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y, double z) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_fmaf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y, float z) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_fmal BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y, long double z) BOOST_MATH_C99_THROW_SPEC;
#endif
double BOOST_MATH_TR1_DECL boost_fmax BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_fmaxf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_fmaxl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_fmin BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_fminf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_fminl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_hypot BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_hypotf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_hypotl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;
#if 0
int BOOST_MATH_TR1_DECL boost_ilogb BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
int BOOST_MATH_TR1_DECL boost_ilogbf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
int BOOST_MATH_TR1_DECL boost_ilogbl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#endif
double BOOST_MATH_TR1_DECL boost_lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_lgammaf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_lgammal BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#ifdef BOOST_HAS_LONG_LONG
#if 0
::boost::long_long_type BOOST_MATH_TR1_DECL boost_llrint BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
::boost::long_long_type BOOST_MATH_TR1_DECL boost_llrintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
::boost::long_long_type BOOST_MATH_TR1_DECL boost_llrintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#endif
::boost::long_long_type BOOST_MATH_TR1_DECL boost_llround BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
::boost::long_long_type BOOST_MATH_TR1_DECL boost_llroundf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
::boost::long_long_type BOOST_MATH_TR1_DECL boost_llroundl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#endif
double BOOST_MATH_TR1_DECL boost_log1p BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_log1pf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_log1pl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#if 0
double BOOST_MATH_TR1_DECL log2 BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL log2f BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL log2l BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL logb BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL logbf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL logbl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
long BOOST_MATH_TR1_DECL lrint BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
long BOOST_MATH_TR1_DECL lrintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long BOOST_MATH_TR1_DECL lrintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#endif
long BOOST_MATH_TR1_DECL boost_lround BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
long BOOST_MATH_TR1_DECL boost_lroundf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long BOOST_MATH_TR1_DECL boost_lroundl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#if 0
double BOOST_MATH_TR1_DECL nan BOOST_PREVENT_MACRO_SUBSTITUTION(const char *str) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL nanf BOOST_PREVENT_MACRO_SUBSTITUTION(const char *str) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL nanl BOOST_PREVENT_MACRO_SUBSTITUTION(const char *str) BOOST_MATH_C99_THROW_SPEC;
double BOOST_MATH_TR1_DECL nearbyint BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL nearbyintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL nearbyintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#endif
double BOOST_MATH_TR1_DECL boost_nextafter BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_nextafterf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_nextafterl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_nexttoward BOOST_PREVENT_MACRO_SUBSTITUTION(double x, long double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_nexttowardf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, long double y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_nexttowardl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;
#if 0
double BOOST_MATH_TR1_DECL boost_remainder BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_remainderf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_remainderl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;
double BOOST_MATH_TR1_DECL boost_remquo BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y, int *pquo) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_remquof BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y, int *pquo) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_remquol BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y, int *pquo) BOOST_MATH_C99_THROW_SPEC;
double BOOST_MATH_TR1_DECL boost_rint BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_rintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_rintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#endif
double BOOST_MATH_TR1_DECL boost_round BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_roundf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_roundl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;
#if 0
double BOOST_MATH_TR1_DECL boost_scalbln BOOST_PREVENT_MACRO_SUBSTITUTION(double x, long ex) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_scalblnf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, long ex) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_scalblnl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long ex) BOOST_MATH_C99_THROW_SPEC;
double BOOST_MATH_TR1_DECL boost_scalbn BOOST_PREVENT_MACRO_SUBSTITUTION(double x, int ex) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_scalbnf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, int ex) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_scalbnl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, int ex) BOOST_MATH_C99_THROW_SPEC;
#endif
double BOOST_MATH_TR1_DECL boost_tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_tgammaf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_tgammal BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

double BOOST_MATH_TR1_DECL boost_trunc BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_truncf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_truncl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.1] associated Laguerre polynomials:
double BOOST_MATH_TR1_DECL boost_assoc_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_assoc_laguerref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_assoc_laguerrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.2] associated Legendre functions:
double BOOST_MATH_TR1_DECL boost_assoc_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_assoc_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_assoc_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.3] beta function:
double BOOST_MATH_TR1_DECL boost_beta BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_betaf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_betal BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.4] (complete) elliptic integral of the first kind:
double BOOST_MATH_TR1_DECL boost_comp_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(double k) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_comp_ellint_1f BOOST_PREVENT_MACRO_SUBSTITUTION(float k) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_comp_ellint_1l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.5] (complete) elliptic integral of the second kind:
double BOOST_MATH_TR1_DECL boost_comp_ellint_2 BOOST_PREVENT_MACRO_SUBSTITUTION(double k) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_comp_ellint_2f BOOST_PREVENT_MACRO_SUBSTITUTION(float k) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_comp_ellint_2l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.6] (complete) elliptic integral of the third kind:
double BOOST_MATH_TR1_DECL boost_comp_ellint_3 BOOST_PREVENT_MACRO_SUBSTITUTION(double k, double nu) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_comp_ellint_3f BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float nu) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_comp_ellint_3l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double nu) BOOST_MATH_C99_THROW_SPEC;
#if 0
// [5.2.1.7] confluent hypergeometric functions:
double BOOST_MATH_TR1_DECL conf_hyperg BOOST_PREVENT_MACRO_SUBSTITUTION(double a, double c, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL conf_hypergf BOOST_PREVENT_MACRO_SUBSTITUTION(float a, float c, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL conf_hypergl BOOST_PREVENT_MACRO_SUBSTITUTION(long double a, long double c, long double x) BOOST_MATH_C99_THROW_SPEC;
#endif
// [5.2.1.8] regular modified cylindrical Bessel functions:
double BOOST_MATH_TR1_DECL boost_cyl_bessel_i BOOST_PREVENT_MACRO_SUBSTITUTION(double nu, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_cyl_bessel_if BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_cyl_bessel_il BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.9] cylindrical Bessel functions (of the first kind):
double BOOST_MATH_TR1_DECL boost_cyl_bessel_j BOOST_PREVENT_MACRO_SUBSTITUTION(double nu, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_cyl_bessel_jf BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_cyl_bessel_jl BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.10] irregular modified cylindrical Bessel functions:
double BOOST_MATH_TR1_DECL boost_cyl_bessel_k BOOST_PREVENT_MACRO_SUBSTITUTION(double nu, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_cyl_bessel_kf BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_cyl_bessel_kl BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.11] cylindrical Neumann functions BOOST_MATH_C99_THROW_SPEC;
// cylindrical Bessel functions (of the second kind):
double BOOST_MATH_TR1_DECL boost_cyl_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(double nu, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_cyl_neumannf BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_cyl_neumannl BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.12] (incomplete) elliptic integral of the first kind:
double BOOST_MATH_TR1_DECL boost_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(double k, double phi) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_ellint_1f BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float phi) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_ellint_1l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double phi) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.13] (incomplete) elliptic integral of the second kind:
double BOOST_MATH_TR1_DECL boost_ellint_2 BOOST_PREVENT_MACRO_SUBSTITUTION(double k, double phi) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_ellint_2f BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float phi) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_ellint_2l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double phi) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.14] (incomplete) elliptic integral of the third kind:
double BOOST_MATH_TR1_DECL boost_ellint_3 BOOST_PREVENT_MACRO_SUBSTITUTION(double k, double nu, double phi) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_ellint_3f BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float nu, float phi) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_ellint_3l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double nu, long double phi) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.15] exponential integral:
double BOOST_MATH_TR1_DECL boost_expint BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_expintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_expintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.16] Hermite polynomials:
double BOOST_MATH_TR1_DECL boost_hermite BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_hermitef BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_hermitel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x) BOOST_MATH_C99_THROW_SPEC;

#if 0
// [5.2.1.17] hypergeometric functions:
double BOOST_MATH_TR1_DECL hyperg BOOST_PREVENT_MACRO_SUBSTITUTION(double a, double b, double c, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL hypergf BOOST_PREVENT_MACRO_SUBSTITUTION(float a, float b, float c, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL hypergl BOOST_PREVENT_MACRO_SUBSTITUTION(long double a, long double b, long double c,
long double x) BOOST_MATH_C99_THROW_SPEC;
#endif

// [5.2.1.18] Laguerre polynomials:
double BOOST_MATH_TR1_DECL boost_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_laguerref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_laguerrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.19] Legendre polynomials:
double BOOST_MATH_TR1_DECL boost_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.20] Riemann zeta function:
double BOOST_MATH_TR1_DECL boost_riemann_zeta BOOST_PREVENT_MACRO_SUBSTITUTION(double) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_riemann_zetaf BOOST_PREVENT_MACRO_SUBSTITUTION(float) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_riemann_zetal BOOST_PREVENT_MACRO_SUBSTITUTION(long double) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.21] spherical Bessel functions (of the first kind):
double BOOST_MATH_TR1_DECL boost_sph_bessel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_sph_besself BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_sph_bessell BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.22] spherical associated Legendre functions:
double BOOST_MATH_TR1_DECL boost_sph_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, double theta) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_sph_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, float theta) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_sph_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, long double theta) BOOST_MATH_C99_THROW_SPEC;

// [5.2.1.23] spherical Neumann functions BOOST_MATH_C99_THROW_SPEC;
// spherical Bessel functions (of the second kind):
double BOOST_MATH_TR1_DECL boost_sph_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, double x) BOOST_MATH_C99_THROW_SPEC;
float BOOST_MATH_TR1_DECL boost_sph_neumannf BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x) BOOST_MATH_C99_THROW_SPEC;
long double BOOST_MATH_TR1_DECL boost_sph_neumannl BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x) BOOST_MATH_C99_THROW_SPEC;

#ifdef __cplusplus

}}}}  // namespaces

#include <boost/math/tools/promotion.hpp>

namespace boost{ namespace math{ namespace tr1{
//
// Declare overload of the functions which forward to the
// C interfaces:
//
// C99 Functions:
inline double acosh BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_acosh BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float acoshf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_acoshf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double acoshl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_acoshl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float acosh BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::acoshf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double acosh BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::acoshl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type acosh BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::acosh BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

inline double asinh BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_asinh BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float asinhf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_asinhf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double asinhl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_asinhl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float asinh BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::asinhf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double asinh BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::asinhl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type asinh BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::asinh BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

inline double atanh BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_atanh BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float atanhf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_atanhf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double atanhl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_atanhl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float atanh BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::atanhf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double atanh BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::atanhl(x); }
template <class T>
inline typename tools::promote_args<T>::type atanh BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::atanh BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

inline double cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float cbrtf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_cbrtf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double cbrtl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_cbrtl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::cbrtf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::cbrtl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

inline double copysign BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y)
{ return boost::math::tr1::boost_copysign BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float copysignf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::boost_copysignf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double copysignl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::boost_copysignl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float copysign BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::copysignf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double copysign BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::copysignl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type copysign BOOST_PREVENT_MACRO_SUBSTITUTION(T1 x, T2 y)
{ return boost::math::tr1::copysign BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(x), static_cast<typename tools::promote_args<T1, T2>::type>(y)); }

inline double erf BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_erf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float erff BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_erff BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double erfl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_erfl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float erf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::erff BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double erf BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::erfl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type erf BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::erf BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

inline double erfc BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_erfc BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float erfcf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_erfcf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double erfcl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_erfcl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float erfc BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::erfcf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double erfc BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::erfcl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type erfc BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::erfc BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

#if 0
double exp2 BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
float exp2f BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
long double exp2l BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);
#endif

inline float expm1f BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_expm1f BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline double expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double expm1l BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_expm1l BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::expm1f BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::expm1l BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

#if 0
double fdim BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y);
float fdimf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y);
long double fdiml BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y);
double fma BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y, double z);
float fmaf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y, float z);
long double fmal BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y, long double z);
#endif
inline double fmax BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y)
{ return boost::math::tr1::boost_fmax BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float fmaxf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::boost_fmaxf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double fmaxl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::boost_fmaxl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float fmax BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::fmaxf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double fmax BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::fmaxl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type fmax BOOST_PREVENT_MACRO_SUBSTITUTION(T1 x, T2 y)
{ return boost::math::tr1::fmax BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(x), static_cast<typename tools::promote_args<T1, T2>::type>(y)); }

inline double fmin BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y)
{ return boost::math::tr1::boost_fmin BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float fminf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::boost_fminf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double fminl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::boost_fminl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float fmin BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::fminf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double fmin BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::fminl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type fmin BOOST_PREVENT_MACRO_SUBSTITUTION(T1 x, T2 y)
{ return boost::math::tr1::fmin BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(x), static_cast<typename tools::promote_args<T1, T2>::type>(y)); }

inline float hypotf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::boost_hypotf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline double hypot BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y)
{ return boost::math::tr1::boost_hypot BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double hypotl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::boost_hypotl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float hypot BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::hypotf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double hypot BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::hypotl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type hypot BOOST_PREVENT_MACRO_SUBSTITUTION(T1 x, T2 y)
{ return boost::math::tr1::hypot BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(x), static_cast<typename tools::promote_args<T1, T2>::type>(y)); }

#if 0
int ilogb BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
int ilogbf BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
int ilogbl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);
#endif

inline float lgammaf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_lgammaf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline double lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double lgammal BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_lgammal BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::lgammaf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::lgammal BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

#ifdef BOOST_HAS_LONG_LONG
#if 0
::boost::long_long_type llrint BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
::boost::long_long_type llrintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
::boost::long_long_type llrintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);
#endif

inline ::boost::long_long_type llroundf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_llroundf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline ::boost::long_long_type llround BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_llround BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline ::boost::long_long_type llroundl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_llroundl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline ::boost::long_long_type llround BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::llroundf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline ::boost::long_long_type llround BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::llroundl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline ::boost::long_long_type llround BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return llround BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<double>(x)); }
#endif

inline float log1pf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_log1pf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline double log1p BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_log1p BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double log1pl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_log1pl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float log1p BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::log1pf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double log1p BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::log1pl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type log1p BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::log1p BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }
#if 0
double log2 BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
float log2f BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
long double log2l BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);

double logb BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
float logbf BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
long double logbl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);
long lrint BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
long lrintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
long lrintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);
#endif
inline long lroundf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_lroundf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long lround BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_lround BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long lroundl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_lroundl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long lround BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::lroundf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long lround BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::lroundl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
long lround BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::lround BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<double>(x)); }
#if 0
double nan BOOST_PREVENT_MACRO_SUBSTITUTION(const char *str);
float nanf BOOST_PREVENT_MACRO_SUBSTITUTION(const char *str);
long double nanl BOOST_PREVENT_MACRO_SUBSTITUTION(const char *str);
double nearbyint BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
float nearbyintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
long double nearbyintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);
#endif
inline float nextafterf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::boost_nextafterf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline double nextafter BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y)
{ return boost::math::tr1::boost_nextafter BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double nextafterl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::boost_nextafterl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float nextafter BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::nextafterf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double nextafter BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::nextafterl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type nextafter BOOST_PREVENT_MACRO_SUBSTITUTION(T1 x, T2 y)
{ return boost::math::tr1::nextafter BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(x), static_cast<typename tools::promote_args<T1, T2>::type>(y)); }

inline float nexttowardf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::boost_nexttowardf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline double nexttoward BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y)
{ return boost::math::tr1::boost_nexttoward BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double nexttowardl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::boost_nexttowardl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float nexttoward BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::nexttowardf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double nexttoward BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::nexttowardl BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type nexttoward BOOST_PREVENT_MACRO_SUBSTITUTION(T1 x, T2 y)
{ return static_cast<typename tools::promote_args<T1, T2>::type>(boost::math::tr1::nexttoward BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(x), static_cast<long double>(y))); }
#if 0
double remainder BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y);
float remainderf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y);
long double remainderl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y);
double remquo BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y, int *pquo);
float remquof BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y, int *pquo);
long double remquol BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y, int *pquo);
double rint BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
float rintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
long double rintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);
#endif
inline float roundf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_roundf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline double round BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_round BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double roundl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_roundl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float round BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::roundf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double round BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::roundl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type round BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::round BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }
#if 0
double scalbln BOOST_PREVENT_MACRO_SUBSTITUTION(double x, long ex);
float scalblnf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, long ex);
long double scalblnl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long ex);
double scalbn BOOST_PREVENT_MACRO_SUBSTITUTION(double x, int ex);
float scalbnf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, int ex);
long double scalbnl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, int ex);
#endif
inline float tgammaf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_tgammaf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline double tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double tgammal BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_tgammal BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::tgammaf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::tgammal BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

inline float truncf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_truncf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline double trunc BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_trunc BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double truncl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_truncl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float trunc BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::truncf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double trunc BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::truncl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type trunc BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::trunc BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

# define NO_MACRO_EXPAND /**/
// C99 macros defined as C++ templates
template<class T> bool signbit NO_MACRO_EXPAND(T x)
{ BOOST_STATIC_ASSERT(sizeof(T) == 0); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL signbit<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL signbit<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL signbit<long double> NO_MACRO_EXPAND(long double x);

template<class T> int fpclassify NO_MACRO_EXPAND(T x)
{ BOOST_STATIC_ASSERT(sizeof(T) == 0); return false; } // must not be instantiated
template<> int BOOST_MATH_TR1_DECL fpclassify<float> NO_MACRO_EXPAND(float x);
template<> int BOOST_MATH_TR1_DECL fpclassify<double> NO_MACRO_EXPAND(double x);
template<> int BOOST_MATH_TR1_DECL fpclassify<long double> NO_MACRO_EXPAND(long double x);

template<class T> bool isfinite NO_MACRO_EXPAND(T x)
{ BOOST_STATIC_ASSERT(sizeof(T) == 0); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL isfinite<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL isfinite<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL isfinite<long double> NO_MACRO_EXPAND(long double x);

template<class T> bool isinf NO_MACRO_EXPAND(T x)
{ BOOST_STATIC_ASSERT(sizeof(T) == 0); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL isinf<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL isinf<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL isinf<long double> NO_MACRO_EXPAND(long double x);

template<class T> bool isnan NO_MACRO_EXPAND(T x)
{ BOOST_STATIC_ASSERT(sizeof(T) == 0); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL isnan<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL isnan<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL isnan<long double> NO_MACRO_EXPAND(long double x);

template<class T> bool isnormal NO_MACRO_EXPAND(T x)
{ BOOST_STATIC_ASSERT(sizeof(T) == 0); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL isnormal<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL isnormal<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL isnormal<long double> NO_MACRO_EXPAND(long double x);

#undef NO_MACRO_EXPAND   
   
// [5.2.1.1] associated Laguerre polynomials:
inline float assoc_laguerref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, float x)
{ return boost::math::tr1::boost_assoc_laguerref BOOST_PREVENT_MACRO_SUBSTITUTION(n, m, x); }
inline double assoc_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, double x)
{ return boost::math::tr1::boost_assoc_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(n, m, x); }
inline long double assoc_laguerrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, long double x)
{ return boost::math::tr1::boost_assoc_laguerrel BOOST_PREVENT_MACRO_SUBSTITUTION(n, m, x); }
inline float assoc_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, float x)
{ return boost::math::tr1::assoc_laguerref BOOST_PREVENT_MACRO_SUBSTITUTION(n, m, x); }
inline long double assoc_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, long double x)
{ return boost::math::tr1::assoc_laguerrel BOOST_PREVENT_MACRO_SUBSTITUTION(n, m, x); }
template <class T> 
inline typename tools::promote_args<T>::type assoc_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, unsigned m, T x)
{ return boost::math::tr1::assoc_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(n, m, static_cast<typename tools::promote_args<T>::type>(x)); }

// [5.2.1.2] associated Legendre functions:
inline float assoc_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, float x)
{ return boost::math::tr1::boost_assoc_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, x); }
inline double assoc_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, double x)
{ return boost::math::tr1::boost_assoc_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, x); }
inline long double assoc_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, long double x)
{ return boost::math::tr1::boost_assoc_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, x); }
inline float assoc_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, float x)
{ return boost::math::tr1::assoc_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, x); }
inline long double assoc_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, long double x)
{ return boost::math::tr1::assoc_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, x); }
template <class T>
inline typename tools::promote_args<T>::type assoc_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, T x)
{ return boost::math::tr1::assoc_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, static_cast<typename tools::promote_args<T>::type>(x)); }

// [5.2.1.3] beta function:
inline float betaf BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::boost_betaf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline double beta BOOST_PREVENT_MACRO_SUBSTITUTION(double x, double y)
{ return boost::math::tr1::boost_beta BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double betal BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::boost_betal BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline float beta BOOST_PREVENT_MACRO_SUBSTITUTION(float x, float y)
{ return boost::math::tr1::betaf BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
inline long double beta BOOST_PREVENT_MACRO_SUBSTITUTION(long double x, long double y)
{ return boost::math::tr1::betal BOOST_PREVENT_MACRO_SUBSTITUTION(x, y); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type beta BOOST_PREVENT_MACRO_SUBSTITUTION(T2 x, T1 y)
{ return boost::math::tr1::beta BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(x), static_cast<typename tools::promote_args<T1, T2>::type>(y)); }

// [5.2.1.4] (complete) elliptic integral of the first kind:
inline float comp_ellint_1f BOOST_PREVENT_MACRO_SUBSTITUTION(float k)
{ return boost::math::tr1::boost_comp_ellint_1f BOOST_PREVENT_MACRO_SUBSTITUTION(k); }
inline double comp_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(double k)
{ return boost::math::tr1::boost_comp_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(k); }
inline long double comp_ellint_1l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k)
{ return boost::math::tr1::boost_comp_ellint_1l BOOST_PREVENT_MACRO_SUBSTITUTION(k); }
inline float comp_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(float k)
{ return boost::math::tr1::comp_ellint_1f BOOST_PREVENT_MACRO_SUBSTITUTION(k); }
inline long double comp_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(long double k)
{ return boost::math::tr1::comp_ellint_1l BOOST_PREVENT_MACRO_SUBSTITUTION(k); }
template <class T>
inline typename tools::promote_args<T>::type comp_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(T k)
{ return boost::math::tr1::comp_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(k)); }

// [5.2.1.5]  (complete) elliptic integral of the second kind:
inline float comp_ellint_2f(float k)
{ return boost::math::tr1::boost_comp_ellint_2f(k); }
inline double comp_ellint_2(double k)
{ return boost::math::tr1::boost_comp_ellint_2(k); }
inline long double comp_ellint_2l(long double k)
{ return boost::math::tr1::boost_comp_ellint_2l(k); }
inline float comp_ellint_2(float k)
{ return boost::math::tr1::comp_ellint_2f(k); }
inline long double comp_ellint_2(long double k)
{ return boost::math::tr1::comp_ellint_2l(k); }
template <class T>
inline typename tools::promote_args<T>::type comp_ellint_2(T k)
{ return boost::math::tr1::comp_ellint_2(static_cast<typename tools::promote_args<T>::type> BOOST_PREVENT_MACRO_SUBSTITUTION(k)); }

// [5.2.1.6]  (complete) elliptic integral of the third kind:
inline float comp_ellint_3f(float k, float nu)
{ return boost::math::tr1::boost_comp_ellint_3f(k, nu); }
inline double comp_ellint_3(double k, double nu)
{ return boost::math::tr1::boost_comp_ellint_3(k, nu); }
inline long double comp_ellint_3l(long double k, long double nu)
{ return boost::math::tr1::boost_comp_ellint_3l(k, nu); }
inline float comp_ellint_3(float k, float nu)
{ return boost::math::tr1::comp_ellint_3f(k, nu); }
inline long double comp_ellint_3(long double k, long double nu)
{ return boost::math::tr1::comp_ellint_3l(k, nu); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type comp_ellint_3(T1 k, T2 nu)
{ return boost::math::tr1::comp_ellint_3(static_cast<typename tools::promote_args<T1, T2>::type> BOOST_PREVENT_MACRO_SUBSTITUTION(k), static_cast<typename tools::promote_args<T1, T2>::type> BOOST_PREVENT_MACRO_SUBSTITUTION(nu)); }

#if 0
// [5.2.1.7] confluent hypergeometric functions:
double conf_hyperg BOOST_PREVENT_MACRO_SUBSTITUTION(double a, double c, double x);
float conf_hypergf BOOST_PREVENT_MACRO_SUBSTITUTION(float a, float c, float x);
long double conf_hypergl BOOST_PREVENT_MACRO_SUBSTITUTION(long double a, long double c, long double x);
#endif

// [5.2.1.8] regular modified cylindrical Bessel functions:
inline float cyl_bessel_if BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x)
{ return boost::math::tr1::boost_cyl_bessel_if BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline double cyl_bessel_i BOOST_PREVENT_MACRO_SUBSTITUTION(double nu, double x)
{ return boost::math::tr1::boost_cyl_bessel_i BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline long double cyl_bessel_il BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x)
{ return boost::math::tr1::boost_cyl_bessel_il BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline float cyl_bessel_i BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x)
{ return boost::math::tr1::cyl_bessel_if BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline long double cyl_bessel_i BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x)
{ return boost::math::tr1::cyl_bessel_il BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type cyl_bessel_i BOOST_PREVENT_MACRO_SUBSTITUTION(T1 nu, T2 x)
{ return boost::math::tr1::cyl_bessel_i BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(nu), static_cast<typename tools::promote_args<T1, T2>::type>(x)); }

// [5.2.1.9] cylindrical Bessel functions (of the first kind):
inline float cyl_bessel_jf BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x)
{ return boost::math::tr1::boost_cyl_bessel_jf BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline double cyl_bessel_j BOOST_PREVENT_MACRO_SUBSTITUTION(double nu, double x)
{ return boost::math::tr1::boost_cyl_bessel_j BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline long double cyl_bessel_jl BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x)
{ return boost::math::tr1::boost_cyl_bessel_jl BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline float cyl_bessel_j BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x)
{ return boost::math::tr1::cyl_bessel_jf BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline long double cyl_bessel_j BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x)
{ return boost::math::tr1::cyl_bessel_jl BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type cyl_bessel_j BOOST_PREVENT_MACRO_SUBSTITUTION(T1 nu, T2 x)
{ return boost::math::tr1::cyl_bessel_j BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(nu), static_cast<typename tools::promote_args<T1, T2>::type>(x)); }

// [5.2.1.10] irregular modified cylindrical Bessel functions:
inline float cyl_bessel_kf BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x)
{ return boost::math::tr1::boost_cyl_bessel_kf BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline double cyl_bessel_k BOOST_PREVENT_MACRO_SUBSTITUTION(double nu, double x)
{ return boost::math::tr1::boost_cyl_bessel_k BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline long double cyl_bessel_kl BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x)
{ return boost::math::tr1::boost_cyl_bessel_kl BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline float cyl_bessel_k BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x)
{ return boost::math::tr1::cyl_bessel_kf BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline long double cyl_bessel_k BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x)
{ return boost::math::tr1::cyl_bessel_kl BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type cyl_bessel_k BOOST_PREVENT_MACRO_SUBSTITUTION(T1 nu, T2 x)
{ return boost::math::tr1::cyl_bessel_k BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type> BOOST_PREVENT_MACRO_SUBSTITUTION(nu), static_cast<typename tools::promote_args<T1, T2>::type>(x)); }

// [5.2.1.11] cylindrical Neumann functions;
// cylindrical Bessel functions (of the second kind):
inline float cyl_neumannf BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x)
{ return boost::math::tr1::boost_cyl_neumannf BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline double cyl_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(double nu, double x)
{ return boost::math::tr1::boost_cyl_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline long double cyl_neumannl BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x)
{ return boost::math::tr1::boost_cyl_neumannl BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline float cyl_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(float nu, float x)
{ return boost::math::tr1::cyl_neumannf BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
inline long double cyl_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(long double nu, long double x)
{ return boost::math::tr1::cyl_neumannl BOOST_PREVENT_MACRO_SUBSTITUTION(nu, x); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type cyl_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(T1 nu, T2 x)
{ return boost::math::tr1::cyl_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(nu), static_cast<typename tools::promote_args<T1, T2>::type>(x)); }

// [5.2.1.12] (incomplete) elliptic integral of the first kind:
inline float ellint_1f BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float phi)
{ return boost::math::tr1::boost_ellint_1f BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
inline double ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(double k, double phi)
{ return boost::math::tr1::boost_ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
inline long double ellint_1l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double phi)
{ return boost::math::tr1::boost_ellint_1l BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
inline float ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float phi)
{ return boost::math::tr1::ellint_1f BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
inline long double ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double phi)
{ return boost::math::tr1::ellint_1l BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(T1 k, T2 phi)
{ return boost::math::tr1::ellint_1 BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(k), static_cast<typename tools::promote_args<T1, T2>::type>(phi)); }

// [5.2.1.13] (incomplete) elliptic integral of the second kind:
inline float ellint_2f BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float phi)
{ return boost::math::tr1::boost_ellint_2f BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
inline double ellint_2 BOOST_PREVENT_MACRO_SUBSTITUTION(double k, double phi)
{ return boost::math::tr1::boost_ellint_2 BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
inline long double ellint_2l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double phi)
{ return boost::math::tr1::boost_ellint_2l BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
inline float ellint_2 BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float phi)
{ return boost::math::tr1::ellint_2f BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
inline long double ellint_2 BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double phi)
{ return boost::math::tr1::ellint_2l BOOST_PREVENT_MACRO_SUBSTITUTION(k, phi); }
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_2 BOOST_PREVENT_MACRO_SUBSTITUTION(T1 k, T2 phi)
{ return boost::math::tr1::ellint_2 BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2>::type>(k), static_cast<typename tools::promote_args<T1, T2>::type>(phi)); }

// [5.2.1.14] (incomplete) elliptic integral of the third kind:
inline float ellint_3f BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float nu, float phi)
{ return boost::math::tr1::boost_ellint_3f BOOST_PREVENT_MACRO_SUBSTITUTION(k, nu, phi); }
inline double ellint_3 BOOST_PREVENT_MACRO_SUBSTITUTION(double k, double nu, double phi)
{ return boost::math::tr1::boost_ellint_3 BOOST_PREVENT_MACRO_SUBSTITUTION(k, nu, phi); }
inline long double ellint_3l BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double nu, long double phi)
{ return boost::math::tr1::boost_ellint_3l BOOST_PREVENT_MACRO_SUBSTITUTION(k, nu, phi); }
inline float ellint_3 BOOST_PREVENT_MACRO_SUBSTITUTION(float k, float nu, float phi)
{ return boost::math::tr1::ellint_3f BOOST_PREVENT_MACRO_SUBSTITUTION(k, nu, phi); }
inline long double ellint_3 BOOST_PREVENT_MACRO_SUBSTITUTION(long double k, long double nu, long double phi)
{ return boost::math::tr1::ellint_3l BOOST_PREVENT_MACRO_SUBSTITUTION(k, nu, phi); }
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type ellint_3 BOOST_PREVENT_MACRO_SUBSTITUTION(T1 k, T2 nu, T3 phi)
{ return boost::math::tr1::ellint_3 BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T1, T2, T3>::type>(k), static_cast<typename tools::promote_args<T1, T2, T3>::type>(nu), static_cast<typename tools::promote_args<T1, T2, T3>::type>(phi)); }

// [5.2.1.15] exponential integral:
inline float expintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_expintf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline double expint BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_expint BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double expintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_expintl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline float expint BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::expintf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long double expint BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::expintl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline typename tools::promote_args<T>::type expint BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
{ return boost::math::tr1::expint BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(x)); }

// [5.2.1.16] Hermite polynomials:
inline float hermitef BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x)
{ return boost::math::tr1::boost_hermitef BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline double hermite BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, double x)
{ return boost::math::tr1::boost_hermite BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline long double hermitel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x)
{ return boost::math::tr1::boost_hermitel BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline float hermite BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x)
{ return boost::math::tr1::hermitef BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline long double hermite BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x)
{ return boost::math::tr1::hermitel BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
template <class T>
inline typename tools::promote_args<T>::type hermite BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, T x)
{ return boost::math::tr1::hermite BOOST_PREVENT_MACRO_SUBSTITUTION(n, static_cast<typename tools::promote_args<T>::type>(x)); }

#if 0
// [5.2.1.17] hypergeometric functions:
double hyperg BOOST_PREVENT_MACRO_SUBSTITUTION(double a, double b, double c, double x);
float hypergf BOOST_PREVENT_MACRO_SUBSTITUTION(float a, float b, float c, float x);
long double hypergl BOOST_PREVENT_MACRO_SUBSTITUTION(long double a, long double b, long double c,
long double x);
#endif

// [5.2.1.18] Laguerre polynomials:
inline float laguerref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x)
{ return boost::math::tr1::boost_laguerref BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline double laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, double x)
{ return boost::math::tr1::boost_laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline long double laguerrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x)
{ return boost::math::tr1::boost_laguerrel BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline float laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x)
{ return boost::math::tr1::laguerref BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline long double laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x)
{ return boost::math::tr1::laguerrel BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
template <class T>
inline typename tools::promote_args<T>::type laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, T x)
{ return boost::math::tr1::laguerre BOOST_PREVENT_MACRO_SUBSTITUTION(n, static_cast<typename tools::promote_args<T>::type>(x)); }

// [5.2.1.19] Legendre polynomials:
inline float legendref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, float x)
{ return boost::math::tr1::boost_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(l, x); }
inline double legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, double x)
{ return boost::math::tr1::boost_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(l, x); }
inline long double legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, long double x)
{ return boost::math::tr1::boost_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(l, x); }
inline float legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, float x)
{ return boost::math::tr1::legendref BOOST_PREVENT_MACRO_SUBSTITUTION(l, x); }
inline long double legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, long double x)
{ return boost::math::tr1::legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(l, x); }
template <class T>
inline typename tools::promote_args<T>::type legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, T x)
{ return boost::math::tr1::legendre BOOST_PREVENT_MACRO_SUBSTITUTION(l, static_cast<typename tools::promote_args<T>::type>(x)); }

// [5.2.1.20] Riemann zeta function:
inline float riemann_zetaf BOOST_PREVENT_MACRO_SUBSTITUTION(float z)
{ return boost::math::tr1::boost_riemann_zetaf BOOST_PREVENT_MACRO_SUBSTITUTION(z); }
inline double riemann_zeta BOOST_PREVENT_MACRO_SUBSTITUTION(double z)
{ return boost::math::tr1::boost_riemann_zeta BOOST_PREVENT_MACRO_SUBSTITUTION(z); }
inline long double riemann_zetal BOOST_PREVENT_MACRO_SUBSTITUTION(long double z)
{ return boost::math::tr1::boost_riemann_zetal BOOST_PREVENT_MACRO_SUBSTITUTION(z); }
inline float riemann_zeta BOOST_PREVENT_MACRO_SUBSTITUTION(float z)
{ return boost::math::tr1::riemann_zetaf BOOST_PREVENT_MACRO_SUBSTITUTION(z); }
inline long double riemann_zeta BOOST_PREVENT_MACRO_SUBSTITUTION(long double z)
{ return boost::math::tr1::riemann_zetal BOOST_PREVENT_MACRO_SUBSTITUTION(z); }
template <class T>
inline typename tools::promote_args<T>::type riemann_zeta BOOST_PREVENT_MACRO_SUBSTITUTION(T z)
{ return boost::math::tr1::riemann_zeta BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<typename tools::promote_args<T>::type>(z)); }

// [5.2.1.21] spherical Bessel functions (of the first kind):
inline float sph_besself BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x)
{ return boost::math::tr1::boost_sph_besself BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline double sph_bessel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, double x)
{ return boost::math::tr1::boost_sph_bessel BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline long double sph_bessell BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x)
{ return boost::math::tr1::boost_sph_bessell BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline float sph_bessel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x)
{ return boost::math::tr1::sph_besself BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline long double sph_bessel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x)
{ return boost::math::tr1::sph_bessell BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
template <class T>
inline typename tools::promote_args<T>::type sph_bessel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, T x)
{ return boost::math::tr1::sph_bessel BOOST_PREVENT_MACRO_SUBSTITUTION(n, static_cast<typename tools::promote_args<T>::type>(x)); }

// [5.2.1.22] spherical associated Legendre functions:
inline float sph_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, float theta)
{ return boost::math::tr1::boost_sph_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, theta); }
inline double sph_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, double theta)
{ return boost::math::tr1::boost_sph_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, theta); }
inline long double sph_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, long double theta)
{ return boost::math::tr1::boost_sph_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, theta); }
inline float sph_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, float theta)
{ return boost::math::tr1::sph_legendref BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, theta); }
inline long double sph_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, long double theta)
{ return boost::math::tr1::sph_legendrel BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, theta); }
template <class T>
inline typename tools::promote_args<T>::type sph_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned l, unsigned m, T theta)
{ return boost::math::tr1::sph_legendre BOOST_PREVENT_MACRO_SUBSTITUTION(l, m, static_cast<typename tools::promote_args<T>::type>(theta)); }

// [5.2.1.23] spherical Neumann functions;
// spherical Bessel functions (of the second kind):
inline float sph_neumannf BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x)
{ return boost::math::tr1::boost_sph_neumannf BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline double sph_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, double x)
{ return boost::math::tr1::boost_sph_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline long double sph_neumannl BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x)
{ return boost::math::tr1::boost_sph_neumannl BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline float sph_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, float x)
{ return boost::math::tr1::sph_neumannf BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
inline long double sph_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, long double x)
{ return boost::math::tr1::sph_neumannl BOOST_PREVENT_MACRO_SUBSTITUTION(n, x); }
template <class T>
inline typename tools::promote_args<T>::type sph_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(unsigned n, T x)
{ return boost::math::tr1::sph_neumann BOOST_PREVENT_MACRO_SUBSTITUTION(n, static_cast<typename tools::promote_args<T>::type>(x)); }

}}} // namespaces

#else // __cplusplus

#include <boost/math/tr1_c_macros.ipp>

#endif // __cplusplus

#endif // BOOST_MATH_TR1_HPP


/* tr1.hpp
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
*/