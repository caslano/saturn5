//  Copyright (c) 2006-7 John Maddock
//  Copyright (c) 2021 Matt Borland
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_CONFIG_HPP
#define BOOST_MATH_TOOLS_CONFIG_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/is_standalone.hpp>

#ifndef BOOST_MATH_STANDALONE
#include <boost/config.hpp>

#else // Things from boost/config that are required, and easy to replicate

#define BOOST_PREVENT_MACRO_SUBSTITUTION
#define BOOST_MATH_NO_REAL_CONCEPT_TESTS
#define BOOST_MATH_NO_DISTRIBUTION_CONCEPT_TESTS
#define BOOST_MATH_NO_LEXICAL_CAST

// Since Boost.Multiprecision is in active development some tests do not fully cooperate yet.
#define BOOST_MATH_NO_MP_TESTS

#if (__cplusplus > 201400L || _MSVC_LANG > 201400L)
#define BOOST_CXX14_CONSTEXPR constexpr
#else
#define BOOST_CXX14_CONSTEXPR
#define BOOST_NO_CXX14_CONSTEXPR
#endif // BOOST_CXX14_CONSTEXPR

#if (__cplusplus > 201700L || _MSVC_LANG > 201700L)
#define BOOST_IF_CONSTEXPR if constexpr

// Clang on mac provides the execution header with none of the functionality. TODO: Check back on this
// https://en.cppreference.com/w/cpp/compiler_support "Standardization of Parallelism TS"
#if !__has_include(<execution>) || (defined(__APPLE__) && defined(__clang__))
#define BOOST_NO_CXX17_HDR_EXECUTION
#endif
#else
#define BOOST_IF_CONSTEXPR if
#define BOOST_NO_CXX17_IF_CONSTEXPR
#define BOOST_NO_CXX17_HDR_EXECUTION
#endif

#if __cpp_lib_gcd_lcm >= 201606L
#define BOOST_MATH_HAS_CXX17_NUMERIC
#endif

#define BOOST_JOIN(X, Y) BOOST_DO_JOIN(X, Y)
#define BOOST_DO_JOIN(X, Y) BOOST_DO_JOIN2(X,Y)
#define BOOST_DO_JOIN2(X, Y) X##Y

#define BOOST_STRINGIZE(X) BOOST_DO_STRINGIZE(X)
#define BOOST_DO_STRINGIZE(X) #X

#ifdef BOOST_DISABLE_THREADS // No threads, do nothing
// Detect thread support via STL implementation
#elif defined(__has_include)
#  if !__has_include(<thread>) || !__has_include(<mutex>) || !__has_include(<future>) || !__has_include(<atomic>)
#     define BOOST_DISABLE_THREADS
#  else
#     define BOOST_HAS_THREADS
#  endif 
#else
#  define BOOST_HAS_THREADS // The default assumption is that the machine has threads
#endif // Thread Support

#ifdef BOOST_DISABLE_THREADS
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif // BOOST_DISABLE_THREADS

#endif // BOOST_MATH_STANDALONE

#include <algorithm>  // for min and max
#include <limits>
#include <cmath>
#include <climits>
#include <cfloat>
#if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__))
#  include <math.h>
#endif

#include <boost/math/tools/user.hpp>

#if (defined(__NetBSD__) || defined(__EMSCRIPTEN__)\
   || (defined(__hppa) && !defined(__OpenBSD__)) || (defined(__NO_LONG_DOUBLE_MATH) && (DBL_MANT_DIG != LDBL_MANT_DIG))) \
   && !defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
//#  define BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#endif

#ifdef __IBMCPP__
//
// For reasons I don't understand, the tests with IMB's compiler all
// pass at long double precision, but fail with real_concept, those tests
// are disabled for now.  (JM 2012).
#ifndef BOOST_MATH_NO_REAL_CONCEPT_TESTS
#  define BOOST_MATH_NO_REAL_CONCEPT_TESTS
#endif // BOOST_MATH_NO_REAL_CONCEPT_TESTS
#endif
#ifdef sun
// Any use of __float128 in program startup code causes a segfault  (tested JM 2015, Solaris 11).
#  define BOOST_MATH_DISABLE_FLOAT128
#endif
#ifdef __HAIKU__
//
// Not sure what's up with the math detection on Haiku, but linking fails with
// float128 code enabled, and we don't have an implementation of __expl, so
// disabling long double functions for now as well.
#  define BOOST_MATH_DISABLE_FLOAT128
#  define BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#endif
#if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)) && ((LDBL_MANT_DIG == 106) || (__LDBL_MANT_DIG__ == 106)) && !defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
//
// Darwin's rather strange "double double" is rather hard to
// support, it should be possible given enough effort though...
//
#  define BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#endif
#if !defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS) && (LDBL_MANT_DIG == 106) && (LDBL_MIN_EXP > DBL_MIN_EXP)
//
// Generic catch all case for gcc's "double-double" long double type.
// We do not support this as it's not even remotely IEEE conforming:
//
#  define BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#endif
#if defined(unix) && defined(__INTEL_COMPILER) && (__INTEL_COMPILER <= 1000) && !defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
//
// Intel compiler prior to version 10 has sporadic problems
// calling the long double overloads of the std lib math functions:
// calling ::powl is OK, but std::pow(long double, long double) 
// may segfault depending upon the value of the arguments passed 
// and the specific Linux distribution.
//
// We'll be conservative and disable long double support for this compiler.
//
// Comment out this #define and try building the tests to determine whether
// your Intel compiler version has this issue or not.
//
#  define BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#endif
#if defined(unix) && defined(__INTEL_COMPILER)
//
// Intel compiler has sporadic issues compiling std::fpclassify depending on
// the exact OS version used.  Use our own code for this as we know it works
// well on Intel processors:
//
#define BOOST_MATH_DISABLE_STD_FPCLASSIFY
#endif

#if defined(_MSC_VER) && !defined(_WIN32_WCE)
   // Better safe than sorry, our tests don't support hardware exceptions:
#  define BOOST_MATH_CONTROL_FP _control87(MCW_EM,MCW_EM)
#endif

#ifdef __IBMCPP__
#  define BOOST_MATH_NO_DEDUCED_FUNCTION_POINTERS
#endif

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901))
#  define BOOST_MATH_USE_C99
#endif

#if (defined(__hpux) && !defined(__hppa))
#  define BOOST_MATH_USE_C99
#endif

#if defined(__GNUC__) && defined(_GLIBCXX_USE_C99)
#  define BOOST_MATH_USE_C99
#endif

#if defined(_LIBCPP_VERSION) && !defined(_MSC_VER)
#  define BOOST_MATH_USE_C99
#endif

#if defined(__CYGWIN__) || defined(__HP_aCC) || defined(__INTEL_COMPILER) \
  || defined(BOOST_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY) \
  || (defined(__GNUC__) && !defined(BOOST_MATH_USE_C99))\
  || defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
#  define BOOST_MATH_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY
#endif

#if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x590)

namespace boost { namespace math { namespace tools { namespace detail {
template <typename T>
struct type {};

template <typename T, T n>
struct non_type {};
}}}} // Namespace boost, math tools, detail

#  define BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(t)              boost::math::tools::detail::type<t>* = 0
#  define BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(t)         boost::math::tools::detail::type<t>*
#  define BOOST_MATH_EXPLICIT_TEMPLATE_NON_TYPE(t, v)       boost::math::tools::detail::non_type<t, v>* = 0
#  define BOOST_MATH_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)  boost::math::tools::detail::non_type<t, v>*

#  define BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(t)         \
             , BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(t)
#  define BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(t)    \
             , BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(t, v)  \
             , BOOST_MATH_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)  \
             , BOOST_MATH_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)

#else

// no workaround needed: expand to nothing

#  define BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(t)
#  define BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define BOOST_MATH_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define BOOST_MATH_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)

#  define BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(t)
#  define BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE_SPEC(t)
#  define BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(t, v)
#  define BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)


#endif // __SUNPRO_CC

#if (defined(__SUNPRO_CC) || defined(__hppa) || defined(__GNUC__)) && !defined(BOOST_MATH_SMALL_CONSTANT)
// Sun's compiler emits a hard error if a constant underflows,
// as does aCC on PA-RISC, while gcc issues a large number of warnings:
#  define BOOST_MATH_SMALL_CONSTANT(x) 0.0
#else
#  define BOOST_MATH_SMALL_CONSTANT(x) x
#endif

//
// Tune performance options for specific compilers:
//
#ifdef _MSC_VER
#  define BOOST_MATH_POLY_METHOD 2
#if _MSC_VER <= 1900
#  define BOOST_MATH_RATIONAL_METHOD 1
#else
#  define BOOST_MATH_RATIONAL_METHOD 2
#endif
#if _MSC_VER > 1900
#  define BOOST_MATH_INT_TABLE_TYPE(RT, IT) RT
#  define BOOST_MATH_INT_VALUE_SUFFIX(RV, SUF) RV##.0L
#endif

#elif defined(__INTEL_COMPILER)
#  define BOOST_MATH_POLY_METHOD 2
#  define BOOST_MATH_RATIONAL_METHOD 1

#elif defined(__GNUC__)
#if __GNUC__ < 4
#  define BOOST_MATH_POLY_METHOD 3
#  define BOOST_MATH_RATIONAL_METHOD 3
#  define BOOST_MATH_INT_TABLE_TYPE(RT, IT) RT
#  define BOOST_MATH_INT_VALUE_SUFFIX(RV, SUF) RV##.0L
#else
#  define BOOST_MATH_POLY_METHOD 3
#  define BOOST_MATH_RATIONAL_METHOD 3
#endif

#elif defined(__clang__)

#if __clang__ > 6
#  define BOOST_MATH_POLY_METHOD 3
#  define BOOST_MATH_RATIONAL_METHOD 3
#  define BOOST_MATH_INT_TABLE_TYPE(RT, IT) RT
#  define BOOST_MATH_INT_VALUE_SUFFIX(RV, SUF) RV##.0L
#endif

#endif

//
// noexcept support:
//
#include <type_traits>
#define BOOST_MATH_NOEXCEPT(T) noexcept(std::is_floating_point<T>::value)
#define BOOST_MATH_IS_FLOAT(T) (std::is_floating_point<T>::value)

//
// The maximum order of polynomial that will be evaluated 
// via an unrolled specialisation:
//
#ifndef BOOST_MATH_MAX_POLY_ORDER
#  define BOOST_MATH_MAX_POLY_ORDER 20
#endif 
//
// Set the method used to evaluate polynomials and rationals:
//
#ifndef BOOST_MATH_POLY_METHOD
#  define BOOST_MATH_POLY_METHOD 2
#endif 
#ifndef BOOST_MATH_RATIONAL_METHOD
#  define BOOST_MATH_RATIONAL_METHOD 1
#endif 
//
// decide whether to store constants as integers or reals:
//
#ifndef BOOST_MATH_INT_TABLE_TYPE
#  define BOOST_MATH_INT_TABLE_TYPE(RT, IT) IT
#endif
#ifndef BOOST_MATH_INT_VALUE_SUFFIX
#  define BOOST_MATH_INT_VALUE_SUFFIX(RV, SUF) RV##SUF
#endif
//
// And then the actual configuration:
//
#if defined(BOOST_MATH_STANDALONE) && defined(_GLIBCXX_USE_FLOAT128) && defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__) && !defined(__STRICT_ANSI__) \
   && !defined(BOOST_MATH_DISABLE_FLOAT128) && !defined(BOOST_MATH_USE_FLOAT128)
#  define BOOST_MATH_USE_FLOAT128
#elif defined(BOOST_HAS_FLOAT128) && !defined(BOOST_MATH_USE_FLOAT128)
#  define BOOST_MATH_USE_FLOAT128
#endif
#ifdef BOOST_MATH_USE_FLOAT128
//
// Only enable this when the compiler really is GCC as clang and probably 
// intel too don't support __float128 yet :-(
//
#  if defined(__INTEL_COMPILER) && defined(__GNUC__)
#    if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
#      define BOOST_MATH_FLOAT128_TYPE __float128
#    endif
#  elif defined(__GNUC__)
#      define BOOST_MATH_FLOAT128_TYPE __float128
#  endif

#  ifndef BOOST_MATH_FLOAT128_TYPE
#      define BOOST_MATH_FLOAT128_TYPE _Quad
#  endif
#endif
//
// Check for WinCE with no iostream support:
//
#if defined(_WIN32_WCE) && !defined(__SGI_STL_PORT)
#  define BOOST_MATH_NO_LEXICAL_CAST
#endif

//
// Helper macro for controlling the FP behaviour:
//
#ifndef BOOST_MATH_CONTROL_FP
#  define BOOST_MATH_CONTROL_FP
#endif
//
// Helper macro for using statements:
//
#define BOOST_MATH_STD_USING_CORE \
   using std::abs;\
   using std::acos;\
   using std::cos;\
   using std::fmod;\
   using std::modf;\
   using std::tan;\
   using std::asin;\
   using std::cosh;\
   using std::frexp;\
   using std::pow;\
   using std::tanh;\
   using std::atan;\
   using std::exp;\
   using std::ldexp;\
   using std::sin;\
   using std::atan2;\
   using std::fabs;\
   using std::log;\
   using std::sinh;\
   using std::ceil;\
   using std::floor;\
   using std::log10;\
   using std::sqrt;

#define BOOST_MATH_STD_USING BOOST_MATH_STD_USING_CORE

namespace boost{ namespace math{
namespace tools
{

template <class T>
inline T max BOOST_PREVENT_MACRO_SUBSTITUTION(T a, T b, T c) BOOST_MATH_NOEXCEPT(T)
{
   return (std::max)((std::max)(a, b), c);
}

template <class T>
inline T max BOOST_PREVENT_MACRO_SUBSTITUTION(T a, T b, T c, T d) BOOST_MATH_NOEXCEPT(T)
{
   return (std::max)((std::max)(a, b), (std::max)(c, d));
}

} // namespace tools

template <class T>
void suppress_unused_variable_warning(const T&) BOOST_MATH_NOEXCEPT(T)
{
}

namespace detail{

template <class T>
struct is_integer_for_rounding
{
   static constexpr bool value = std::is_integral<T>::value || (std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_integer);
};

}

}} // namespace boost namespace math

#ifdef __GLIBC_PREREQ
#  if __GLIBC_PREREQ(2,14)
#     define BOOST_MATH_HAVE_FIXED_GLIBC
#  endif
#endif

#if ((defined(__linux__) && !defined(__UCLIBC__) && !defined(BOOST_MATH_HAVE_FIXED_GLIBC)) || defined(__QNX__) || defined(__IBMCPP__))
//
// This code was introduced in response to this glibc bug: http://sourceware.org/bugzilla/show_bug.cgi?id=2445
// Basically powl and expl can return garbage when the result is small and certain exception flags are set
// on entrance to these functions.  This appears to have been fixed in Glibc 2.14 (May 2011).
// Much more information in this message thread: https://groups.google.com/forum/#!topic/boost-list/ZT99wtIFlb4
//

#include <cfenv>

#  ifdef FE_ALL_EXCEPT

namespace boost{ namespace math{
   namespace detail
   {
   struct fpu_guard
   {
      fpu_guard()
      {
         fegetexceptflag(&m_flags, FE_ALL_EXCEPT);
         feclearexcept(FE_ALL_EXCEPT);
      }
      ~fpu_guard()
      {
         fesetexceptflag(&m_flags, FE_ALL_EXCEPT);
      }
   private:
      fexcept_t m_flags;
   };

   } // namespace detail
   }} // namespaces

#    define BOOST_FPU_EXCEPTION_GUARD boost::math::detail::fpu_guard local_guard_object;
#    define BOOST_MATH_INSTRUMENT_FPU do{ fexcept_t cpu_flags; fegetexceptflag(&cpu_flags, FE_ALL_EXCEPT); BOOST_MATH_INSTRUMENT_VARIABLE(cpu_flags); } while(0); 

#  else

#    define BOOST_FPU_EXCEPTION_GUARD
#    define BOOST_MATH_INSTRUMENT_FPU

#  endif

#else // All other platforms.
#  define BOOST_FPU_EXCEPTION_GUARD
#  define BOOST_MATH_INSTRUMENT_FPU
#endif

#ifdef BOOST_MATH_INSTRUMENT

#  include <iostream>
#  include <iomanip>
#  include <typeinfo>

#  define BOOST_MATH_INSTRUMENT_CODE(x) \
      std::cout << std::setprecision(35) << __FILE__ << ":" << __LINE__ << " " << x << std::endl;
#  define BOOST_MATH_INSTRUMENT_VARIABLE(name) BOOST_MATH_INSTRUMENT_CODE(#name << " = " << name)

#else

#  define BOOST_MATH_INSTRUMENT_CODE(x)
#  define BOOST_MATH_INSTRUMENT_VARIABLE(name)

#endif

//
// Thread local storage:
//
#ifndef BOOST_DISABLE_THREADS
#  define BOOST_MATH_THREAD_LOCAL thread_local
#else
#  define BOOST_MATH_THREAD_LOCAL 
#endif

//
// Some mingw flavours have issues with thread_local and types with non-trivial destructors
// See https://sourceforge.net/p/mingw-w64/bugs/527/
//
#if (defined(__MINGW32__) && (__GNUC__ < 9) && !defined(__clang__))
#  define BOOST_MATH_NO_THREAD_LOCAL_WITH_NON_TRIVIAL_TYPES
#endif


//
// Can we have constexpr tables?
//
#if (!defined(BOOST_NO_CXX14_CONSTEXPR)) || (defined(_MSC_VER) && _MSC_VER >= 1910)
#define BOOST_MATH_HAVE_CONSTEXPR_TABLES
#define BOOST_MATH_CONSTEXPR_TABLE_FUNCTION constexpr
#else
#define BOOST_MATH_CONSTEXPR_TABLE_FUNCTION
#endif


#endif // BOOST_MATH_TOOLS_CONFIG_HPP





/* config.hpp
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
*/