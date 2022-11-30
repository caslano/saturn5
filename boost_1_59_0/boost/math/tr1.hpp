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

#include <boost/math/tools/is_standalone.hpp>
#include <boost/math/tools/assert.hpp>

namespace boost{ namespace math{ namespace tr1{ extern "C"{

#endif // __cplusplus

#ifndef BOOST_PREVENT_MACRO_SUBSTITUTION
#define BOOST_PREVENT_MACRO_SUBSTITUTION /**/
#endif

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
// Not compatible with standalone mode
//
#ifndef BOOST_MATH_STANDALONE
#include <boost/config.hpp>
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
#else // Standalone mode
#  if defined(_MSC_VER) && !defined(BOOST_ALL_NO_LIB)
#    pragma message("Auto linking of TR1 is not supported in standalone mode")
#  endif
#endif // BOOST_MATH_STANDALONE

#if !(defined(__INTEL_COMPILER) && defined(__APPLE__)) && !(defined(__FLT_EVAL_METHOD__) && !defined(__cplusplus))
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

long long BOOST_MATH_TR1_DECL boost_llround BOOST_PREVENT_MACRO_SUBSTITUTION(double x) BOOST_MATH_C99_THROW_SPEC;
long long BOOST_MATH_TR1_DECL boost_llroundf BOOST_PREVENT_MACRO_SUBSTITUTION(float x) BOOST_MATH_C99_THROW_SPEC;
long long BOOST_MATH_TR1_DECL boost_llroundl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x) BOOST_MATH_C99_THROW_SPEC;

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
long long llrint BOOST_PREVENT_MACRO_SUBSTITUTION(double x);
long long llrintf BOOST_PREVENT_MACRO_SUBSTITUTION(float x);
long long llrintl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x);
#endif

inline long long llroundf BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::boost_llroundf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long long llround BOOST_PREVENT_MACRO_SUBSTITUTION(double x)
{ return boost::math::tr1::boost_llround BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long long llroundl BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::boost_llroundl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long long llround BOOST_PREVENT_MACRO_SUBSTITUTION(float x)
{ return boost::math::tr1::llroundf BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
inline long long llround BOOST_PREVENT_MACRO_SUBSTITUTION(long double x)
{ return boost::math::tr1::llroundl BOOST_PREVENT_MACRO_SUBSTITUTION(x); }
template <class T>
inline long long llround BOOST_PREVENT_MACRO_SUBSTITUTION(T x)
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
{ static_assert(sizeof(T) == 0, "Undefined behavior; this template should never be instantiated"); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL signbit<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL signbit<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL signbit<long double> NO_MACRO_EXPAND(long double x);

template<class T> int fpclassify NO_MACRO_EXPAND(T x)
{ static_assert(sizeof(T) == 0, "Undefined behavior; this template should never be instantiated"); return false; } // must not be instantiated
template<> int BOOST_MATH_TR1_DECL fpclassify<float> NO_MACRO_EXPAND(float x);
template<> int BOOST_MATH_TR1_DECL fpclassify<double> NO_MACRO_EXPAND(double x);
template<> int BOOST_MATH_TR1_DECL fpclassify<long double> NO_MACRO_EXPAND(long double x);

template<class T> bool isfinite NO_MACRO_EXPAND(T x)
{ static_assert(sizeof(T) == 0, "Undefined behavior; this template should never be instantiated"); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL isfinite<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL isfinite<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL isfinite<long double> NO_MACRO_EXPAND(long double x);

template<class T> bool isinf NO_MACRO_EXPAND(T x)
{ static_assert(sizeof(T) == 0, "Undefined behavior; this template should never be instantiated"); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL isinf<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL isinf<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL isinf<long double> NO_MACRO_EXPAND(long double x);

template<class T> bool isnan NO_MACRO_EXPAND(T x)
{ static_assert(sizeof(T) == 0, "Undefined behavior; this template should never be instantiated"); return false; } // must not be instantiated
template<> bool BOOST_MATH_TR1_DECL isnan<float> NO_MACRO_EXPAND(float x);
template<> bool BOOST_MATH_TR1_DECL isnan<double> NO_MACRO_EXPAND(double x);
template<> bool BOOST_MATH_TR1_DECL isnan<long double> NO_MACRO_EXPAND(long double x);

template<class T> bool isnormal NO_MACRO_EXPAND(T x)
{ static_assert(sizeof(T) == 0, "Undefined behavior; this template should never be instantiated"); return false; } // must not be instantiated
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