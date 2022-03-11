//  Copyright (c) 2006-7 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_CONFIG_HPP
#define BOOST_MATH_TOOLS_CONFIG_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/predef/architecture/x86.h>
#include <boost/cstdint.hpp> // for boost::uintmax_t
#include <boost/detail/workaround.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <algorithm>  // for min and max
#include <boost/config/no_tr1/cmath.hpp>
#include <climits>
#include <cfloat>
#if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__))
#  include <math.h>
#endif
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  include <limits>
#endif

#include <boost/math/tools/user.hpp>

#if (defined(__CYGWIN__) || defined(__FreeBSD__) || defined(__NetBSD__) \
   || (defined(__hppa) && !defined(__OpenBSD__)) || (defined(__NO_LONG_DOUBLE_MATH) && (DBL_MANT_DIG != LDBL_MANT_DIG))) \
   && !defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
#  define BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#endif
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
//
// Borland post 5.8.2 uses Dinkumware's std C lib which
// doesn't have true long double precision.  Earlier
// versions are problematic too:
//
#  define BOOST_MATH_NO_REAL_CONCEPT_TESTS
#  define BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#  define BOOST_MATH_CONTROL_FP _control87(MCW_EM,MCW_EM)
#  include <float.h>
#endif
#ifdef __IBMCPP__
//
// For reasons I don't understand, the tests with IMB's compiler all
// pass at long double precision, but fail with real_concept, those tests
// are disabled for now.  (JM 2012).
#  define BOOST_MATH_NO_REAL_CONCEPT_TESTS
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

#if defined(BOOST_MSVC) && !defined(_WIN32_WCE)
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

#if defined(__CYGWIN__) || defined(__HP_aCC) || defined(BOOST_INTEL) \
  || defined(BOOST_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY) \
  || (defined(__GNUC__) && !defined(BOOST_MATH_USE_C99))\
  || defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
#  define BOOST_MATH_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY
#endif

#if BOOST_WORKAROUND(__SUNPRO_CC, <= 0x590)

#  include "boost/type.hpp"
#  include "boost/non_type.hpp"

#  define BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(t)         boost::type<t>* = 0
#  define BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(t)    boost::type<t>*
#  define BOOST_MATH_EXPLICIT_TEMPLATE_NON_TYPE(t, v)  boost::non_type<t, v>* = 0
#  define BOOST_MATH_EXPLICIT_TEMPLATE_NON_TYPE_SPEC(t, v)  boost::non_type<t, v>*

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


#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)
//
// Define if constants too large for a float cause "bad"
// values to be stored in the data, rather than infinity
// or a suitably large value.
//
#  define BOOST_MATH_BUGGY_LARGE_FLOAT_CONSTANTS
#endif
//
// Tune performance options for specific compilers:
//
#ifdef BOOST_MSVC
#  define BOOST_MATH_POLY_METHOD 2
#if BOOST_MSVC <= 1900
#  define BOOST_MATH_RATIONAL_METHOD 1
#else
#  define BOOST_MATH_RATIONAL_METHOD 2
#endif
#if BOOST_MSVC > 1900
#  define BOOST_MATH_INT_TABLE_TYPE(RT, IT) RT
#  define BOOST_MATH_INT_VALUE_SUFFIX(RV, SUF) RV##.0L
#endif

#elif defined(BOOST_INTEL)
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

#if defined(BOOST_NO_LONG_LONG) && !defined(BOOST_MATH_INT_TABLE_TYPE)
#  define BOOST_MATH_INT_TABLE_TYPE(RT, IT) RT
#  define BOOST_MATH_INT_VALUE_SUFFIX(RV, SUF) RV##.0L
#endif

//
// constexpr support, early GCC implementations can't cope so disable
// constexpr for them:
//
#if !defined(__clang__) && defined(__GNUC__)
#if (__GNUC__ * 100 + __GNUC_MINOR__) < 490
#  define BOOST_MATH_DISABLE_CONSTEXPR
#endif
#endif

#ifdef BOOST_MATH_DISABLE_CONSTEXPR
#  define BOOST_MATH_CONSTEXPR
#else
#  define BOOST_MATH_CONSTEXPR BOOST_CONSTEXPR
#endif

//
// noexcept support:
//
#ifndef BOOST_NO_CXX11_NOEXCEPT
#ifndef BOOST_NO_CXX11_HDR_TYPE_TRAITS
#include <type_traits>
#  define BOOST_MATH_NOEXCEPT(T) noexcept(std::is_floating_point<T>::value)
#  define BOOST_MATH_IS_FLOAT(T) (std::is_floating_point<T>::value)
#else
#include <boost/type_traits/is_floating_point.hpp>
#  define BOOST_MATH_NOEXCEPT(T) noexcept(boost::is_floating_point<T>::value)
#  define BOOST_MATH_IS_FLOAT(T) (boost::is_floating_point<T>::value)
#endif
#else
#  define BOOST_MATH_NOEXCEPT(T)
#  define BOOST_MATH_IS_FLOAT(T) false
#endif

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
#if defined(_GLIBCXX_USE_FLOAT128) && defined(BOOST_GCC) && !defined(__STRICT_ANSI__) \
   && !defined(BOOST_MATH_DISABLE_FLOAT128) || defined(BOOST_MATH_USE_FLOAT128)
//
// Only enable this when the compiler really is GCC as clang and probably 
// intel too don't support __float128 yet :-(
//
#ifndef BOOST_MATH_USE_FLOAT128
#  define BOOST_MATH_USE_FLOAT128
#endif

#  if defined(BOOST_INTEL) && defined(BOOST_INTEL_CXX_VERSION) && (BOOST_INTEL_CXX_VERSION >= 1310) && defined(__GNUC__)
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
   static const bool value = boost::is_integral<T>::value
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
      || (std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_integer)
#endif
      ;
};

}

}} // namespace boost namespace math

#ifdef __GLIBC_PREREQ
#  if __GLIBC_PREREQ(2,14)
#     define BOOST_MATH_HAVE_FIXED_GLIBC
#  endif
#endif

#if ((defined(__linux__) && !defined(__UCLIBC__) && !defined(BOOST_MATH_HAVE_FIXED_GLIBC)) || defined(__QNX__) || defined(__IBMCPP__)) && !defined(BOOST_NO_FENV_H)
//
// This code was introduced in response to this glibc bug: http://sourceware.org/bugzilla/show_bug.cgi?id=2445
// Basically powl and expl can return garbage when the result is small and certain exception flags are set
// on entrance to these functions.  This appears to have been fixed in Glibc 2.14 (May 2011).
// Much more information in this message thread: https://groups.google.com/forum/#!topic/boost-list/ZT99wtIFlb4
//

   #include <boost/detail/fenv.hpp>

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
#  define BOOST_MATH_INSTRUMENT_VARIABLE(name) BOOST_MATH_INSTRUMENT_CODE(BOOST_STRINGIZE(name) << " = " << name)

#else

#  define BOOST_MATH_INSTRUMENT_CODE(x)
#  define BOOST_MATH_INSTRUMENT_VARIABLE(name)

#endif

//
// Thread local storage:
//
#if !defined(BOOST_NO_CXX11_THREAD_LOCAL) && !defined(BOOST_INTEL)
#  define BOOST_MATH_THREAD_LOCAL thread_local
#else
#  define BOOST_MATH_THREAD_LOCAL
#endif

//
// Can we have constexpr tables?
//
#if (!defined(BOOST_NO_CXX11_HDR_ARRAY) && !defined(BOOST_NO_CXX14_CONSTEXPR)) || BOOST_WORKAROUND(BOOST_MSVC, >= 1910)
#define BOOST_MATH_HAVE_CONSTEXPR_TABLES
#define BOOST_MATH_CONSTEXPR_TABLE_FUNCTION constexpr
#else
#define BOOST_MATH_CONSTEXPR_TABLE_FUNCTION
#endif


#endif // BOOST_MATH_TOOLS_CONFIG_HPP





/* config.hpp
PwuFrAHUmgoArw5aqk5eRas6lPI+lN/QyDucmqFA+Q1UuT87rWE5Z6C/mPfEwqM+BKfRqq4uK+FXI8zR97UpdVeI8fua6x9T+1BoBttgI9xiTCCvmCC8v2Q6IG3PGw3oOCHie7k5L6WWYLFqRUAieSJYIaDaYuL48GV9eRf78EEkqOZtD/vZCgzBN+4P1Me4lgabjih+5e4x/SP1XrF1itP9/lXmJNTnabKmFRKrDtgNBwn1I7Tl3Hxx/eb0eg2eVaGObUB6O3NBvWsdBIaW9arHOfEIsWGyua7uBj7yVFdxj+297XQmmjL5f66d1AG9egwYTTemzzbfNUzXNt+330lu4tBaLux9DtKcjEKWoqNLsHZJAPPUOlRRYyanx35NTS/6IVjbhf2K4iOcpnOjwGmjHGQH6m1vdsmm1vxMtb4J7Ra7i4Wq7RSnKBPxugUoGukVNGn1GQaltZeFkyNLg56pyTfdlafdBFJ9dQqdvx/W6R1auFnMCI5JtxiXFlOtAXtfg9p7CfP0SPsEafncCkBUZ+e/SDDsCdvOSecyoFww8NFtYRALamkRc5N9TLPgQZ8b351e9L16NkQdbHHMe6Ru/oIHO1c05zPZ777yomXt9StstA0I48Rl17z/XaVNnfWsdihERaKIKBau/jpcGM4LFOf0LkZTRbqSOYKEmx8wOmjK5n2/MELBVp9a9cHQXqtYalptI3p3/isL29LNqSxQgO/D+fLBzpiiS6s9TL4AQfmhUiJ1CmL3VQ8Az9M13dm8+E1u4Uo/T5q6P+ivq/Jjlg/oAXB+uyycNSPb+LxOZtTe+n25ltZ8CU/dWbNJIR7Zs6mkIyd2ZRkKX6yyC5XkI3+oGUJmA487+npiuggcRs4rJcd/GM/1Gif3eiDP/X+r94eJu4U7AgC/ML8QaADBr71V6l8/V1FcLj48Xl1ZA20zUzNjQ30rXSE8bVM8Klp5GqpPWubZPWBbAMgtgi+/vj6/2j6YDRjYwE9Nn16/ILqg4F9Q/J3b45CRmx/oXzq9GdepX7q43zvpFRgIFAQcDBICOoq3YQDAvl6mXwI4GAAECBgEZBTxMzoK+/evTYAuYRRxjCYvnCtaGQKrMv92eeITpA13QROxdKqBUB3hlbb351FbtCMMdBJiMlIK8kf69LQMzBws/FyCPMJ8sgLyUooyyvJ/FXS19HUM9ZofmthbmVo4O1n4u926d7YMCAoM8fZjPe9nTvBDXUtTPbsuDikJORklBTUVCw0bKwc7FyePN+jI+NjkxHTUckzlh9WV9bXNjcOt46PTk/Ozy4vEKzLf7j7fARCg0L+pr0/wiAvkH3OP4jg019aE0mV3gREgXnjfrwV5T0iIM/26j6FhU9KDkbHsb6O/z70vnj8euTqxkyMXaD0g/PyC/mbf8L4hQBA6fKG5aftMAPAP9A/jcvxwMC4qXpDigwYijhpGrYjO/jqQqUbgeI1BhqlAzW40XSi2AC/wfj3x1Gcc34QjF/fIPP849jwxtJ/ZPzyq+uwZ4XZ+2JzcfQ9TSUXp/D2P+YgK8d/swzNw+nzLq6wbT8VKF1rx7m4NAnug32fbBA8ASfcstV/5fBQCI3bBnegKI1536ldufmPmOD7EvIQB21GZXIiHDTfioF2UgT7oQy3mmmBvoVywoAGn/SD67lUpbr+PYNpv34gTtgPFwCQH8biHqGJRk87qbznz+3SvJhnz1oRxxCBDlgaYhwWZRqV4DCfBNnrZ1GUUp4k3cAmLo2Mj7wXkrtLetPBRqMOUmRNr80Oi9sS0sIAJPxdLWxzp4mCVDHnY2xQafIPO3DkX1d3dykp2YdHsV4S7NufejAP01G9NEZ8/LZzzADAJdI4YkegXo8tCQBLbDAYIkBI/mFlQGZsxMdHje4rIOLFwKTlru6P0TSyCzTHhi9xzSOy1KuTHgUhR/nVkx1XS5cPTxSGiZcHEXnn6RNDcR15iY6P9d6V3n5ZDffWE6vqfIRrGKYQG6HmgFgm+Z9nxd2KwLLwuNLeclbVg7viXYGZ7LWlRRKUwNQ1vdb6mhJqayyMTQQfLe+MbdrRj4Q5Mk73EZIls4tNGXnIgt4XFe1lWS0i0O4aUGe+O6A9m/GL/D43adfl9GwcGQl8CoC2knpRfOuiAqCBrjTzCOl1sqX1QVwACbET2wEAc0yKHK8AbSoxQfHjoLm8bVAJLlgZ1v6WHTk2EtlCbCb3rGYfoZ1/oLPbwXFw7iNQoEhaUbq4/Uz7rZUMhHNakpd+TRQF9Bv3Qgx9Rnl8jENz14UlNGNbpcdzaLcNdze/3fVMLxOtSqYKfFJ4WUaMsEPKRlVYIcQ8s6Fi1YcDbLM5Gxrbd3Ii3kiO8TRzORONyP0hUrxTXGX1xckBNdJPJXieGrJKdIlclfe4y+7mlICwd3bL5B5bgC9f8EcvK+UzqZpcT2HeWjDziK3r3pHctHptun/xoId9ix7P516qvN16T44oytZZvjaTxv9d+ayarrpr0IpwV9r4sq3MTsUSEuTVXzLe8mqY8fRWy5A/rjYek+AbgQwm4QjdIwhX6wfrLdBeWp2V9d9sy9P8srLhh7jqZQYZTDotmjnQ1iUSnoMk9ACkVSGhZOpoqaNk4LyQ4XD62KyLe+N7h/M0CraBUznbDBRRrTR906/7pldc8QBALlZUO7U9vJ0zciNlGlDmonEbQJUqRgtnAyeTtxTdEsZRVb02mXpfMyW3oaSGzVOvavHcZ6VOOAZ1XAI56TJtH0VTOX7JRot6KtyZEHMgFWslUvtqx31KpVDk4ctJlYuf2zYP7AfgJSQEC+P36enmOebr+iIJdBgOgZhbQTrOplcEK4ll6QRq5hi4Z9TASlb7XSFTBNP0io5dTCmaYZ55Fxhs8GJ3EDE4SsBLQJfE1oAX7jomKA3VMH2xfdhrH3ePEwlMRADHo7WUQhL05E95NQTxUy86AVWAZ66dtHx/fohsyBU+vBgH3ZRzR3DJcZwuX4IsCDj0WF6HjnRYuPzrEv7kD/wNjE+/hN1rB9pNW0M0/VbHMoz+yJWQ3wd1EfdolCBzRARlUbwIlT0nIB/i42jb7pO7V8ntSRm9D2NtLo4ooOM5YdlBfwBDjjtD4DxYkRJpG3+uz7TZ7+z/dlRLftHnqupcrCqHv7c00rwegY8m+GWK+BMR18tnl1kB/xJ8sLq9gXGucffKVbS9dpYdu6aVyHj2VBTNmwpbzQGGqA+gr3CILAOZG0G67izK2stvlr3MOLxfMqsNobXR0IV1R2shRGfuvWKGYX/fAzGP+N6c2N0yr1274FJ1wM3wNhf9uosyKp3PmZqMwP2V7kGpTUKd00gVtos6rE3D5p2Z3AJLIilgIYSUgopgxeWTs8I5Oa+Vycs0T7r/VR4GU/WplgvmKJUw+nxlDcoOWSUcUyltiJD/zYpzeYQstcj6cPKPOnrk5trNKdtQhbtEqefGBRoeaPIwgLiP1wdyCVJh6cYXO7zf5Ql28x2LoyZe7pqQ4hyMk7P9zERoAk/xvykd2eN2PoMamvzriPwsNMi+mRTO/tr7JsjteCne9o/0BkVKE0KkcScxdR/z71i5NRsFtGKVkoee1VQCNkPmjmLpErOZAHALIrZDby6pynPXP99dpnz501qPnr3mC9fYQm0xE6SCyVlB3VG1t3XSWwdDpYrxtAeqxlEH0oOIhe2JUHgGZfbwfGLf1iwpubYnoJ6v3FE6eV5IYqc/tGhHaLEOqHyudgIzH/OaeDiFloeR4VO1Ed1ZuBgWF/gUTH2XSx9YVVSYbj28b5kyNolQU7k6z1a1HtR/dCQknMsd/hil1/1n31jbYzS3H4x+Rf+bTvEM0jU7VwVchHskzopWaikeMryvV576CvLiPX2HFLi+0iys6GAiPWFWET2s4iVkhqtztWep827jBO3uir870Op86sP0PAFyAo3/Vs2+cQQKSuG5k8S2swEUOueHK28gCwI2n6kWyChbXjLN/PmchjY/LZTfbgp7O3OtHNnyKo7OKIjSSkq6Uv+QIdF4fu6O4F5Q4eHpqE+/m01kMOtFtioNGuW4aXOsXeIbV8FFhAdqbA8QGjfR7mV/Mu5MAHq9BC5DVmRCgeoCu1kk/1BwLNbnJzT0NH6NOcRfdoHiNxDYYJ+Y2OMPJqhCjDeKsjoljmWvABji0z8KModae3Nu9EJZV0/JAxdRPVd2yXVuGWh0Wb1zMwdQaRvvH+k6JaKJ1xBCjFtRdyEto4ngqJTyNEAAFPFZX9rho3LY5cLhCft4HcKaK8fGJ18riWoRHuLQiumocerQu30FrnaKblXT1Eqode3M5+zN4+Lo1cOTzs9hvHiuluk8RA/Z3Kb7yM6ry8+tGhtg96MO3TL4axOirJ0HQt4XThW9zwlThlQt21wien/Ziwu+ztc/WPbfeZWswSB43YoDXUe9uv1SxU6RxwN8dRTDQD8ula46vDl22VFHgep+tURY6c1x6l91m2NB7VbclgKW9sK0O/VDBcqJ0LDp8vyChSba5rNALC7rNg278zx4NjIg9xX0378htPWtknIyBOmZ44bkfuZR0403wVOE5J4R5OBRr9Vs3v73Wtpun8hNHpGqejW2awDSl8aLWwVwTxQzUd4TSMK/W8JKAYQhz3LlF0/e5MZrIlJXruBeljkZ2L9LZ5edJj5z3dq83IB0OjAAPui+oPtZzimYfoMBadePheU3xptr7oul52WuU8eu99epd9fF9kyqVAbKaeLbaHDb4tdzMXT1QGNmc0aL9kaS6uvULx2lEzvd7kYn5ktQldkCET20UKpz0Fw07K+KY3MzkbexKDYnklOxNetAyaElB0OD3Al8pSD3sgczsURZ/eZ+OW2J2etgZjeOcSp7YDD/zYCEMKIF1kZrxRX3AnSNqhY7xVxI5OjKdjftuHZMoyS99L+IdyMruO3cIKVg4z4Lg2TdXPfo5OtO9L6Cj62bKkxSLjXTDCHcGgDZpzbNthK1AZ66gCAu1azVshhhDBKSQmTnwgMDLczq4ijTv7/q9t48gwp4ZhT438gMXLqfIB6WVDgWd3OIG5Lu7K//k7h0jI++ZmJyDDrWj+dOt/vijZodCAFe1QcWYCf2BOK7iQHqMiLMHb3qIAH+R4BjLtERhCqYv9Q5Q3ens6hVJLaZ/YXjEGiMRqJgl11pVYhMmvR4W2KRMlWt2e2wUwUF89J0xlhKTeVVyhPm9VoA4YZAOaNqFHpLoIsCwIGUVvv+naTHSLpNkXqWA8A33VoMOEiQ82h1JXo/y7RUfAlBN5x1CnM4gIO/J4ULX/7vt1knsAblZq3GD3gTBsU5VBLvpN4AYZrV3ASVHp1DptRu4WNYIGJj+W5xA1Wj0YEltVENWoHGUIp9Rd5HzOSh2fpiuc7ydnOqQEMMIHjQOGIB3OtdbF+CkNuQkSqqZ2eaERB63ZI+AQTftzd6EtOn3zmk+QoOx0SB0aGIpGV+Rnk8tADJ6CKs2IXpvIkHg9wAkvwaVPgOkwZ31hEP6wSj+Bbu+Utao0w0dxOlX8b1vkIhxIqzbkvYH4bt+c6g9FFF2wxhIweeaCm0BvDNnRAwEtXS2CF1M2N7aXTV2lN87dKx8ypro9EYOWkh4n42iGl6V7hrRLHZY9OIfBWcdsGy75Njenk2MqFoLhx6ZlU5CZhMO/6AsRoojCR0Tw13O0QZWHmPO3d2q0CCvbdvY/Ujrx6btSjg7TxT7pVIQqqu3eAKX2X1A7CZDcve8alY6slBvjnfl6zPtmtQncVf6pydkYPeWp8lPD6bFVbNvrCbcOnijPAyU/msQOds8dzjg9OXbYC6bSK5oC5mSutxM2/5vEBtr8VyVD8cyR+ELV5+u0p4AFRwsS3Q1rtrFN4Jm1ElmCEl4hRaRwL+FU62ZIE1VSduOV4ZVEOuQ63VG6GWy1QJ6BgAQShALStaqO3dz3N+l2wGVXkT6UZ+vSr4Tdjw5tjiGtG7SdfSV4tpw8Toz7XOarvZ7FjkVmijId0fHqO+3H9Hj/fTQnhITKTlp4hJtjo0wIT+AMii4ZTpcnKeW/L5XcislWzfsw96p3z8xS8ps82k9LFxg6+4RY8rjWO3tWm/OrwnoHS/gZwQew31H36zOu03yMhc7HOW79qky+qt2N+jGOi7HCvvW53YMdTVrrHn4NBZxb687VBAyscrfV8TDyGGUXc/xbndoO9FyybIpcdaUeGVWqnZ+/W7OPuYauAjLlPBLMIuRIqNcFkbDVgArFvs87RFZLW0u1WyLhZ4cFq9fDzh9ZMVj1MIAYZajFbc5XJM8mKNohnzeSw4JTOCvPZvs1fyg7R3jMu3o5nn2KRUJGNWI2vZkVOuegVZHV3SjpoP3/bhAUn9dDz721Si4qtIdIiyTyAIlxoubsKShgL/8NQ7uJQLUV7WQbddEmESrBMiyGZbxCe2lkSH1aBgg4Yqt2FHO4W+pUBO71yO4WI6jJXf74WRtbncdXbT2e2g9B+0UQ0rAnR3/5nWeRwtL4gBIGZ74QuoiX+pWX+KXqre7s8BS3aQ7Mpc3dR8O3q75wUS7l9C13BTaBzVQ/GzMVSXhpd5tsV40T17PyxU9JLZ7RN8dSNLHDESZ41bYKWMdg7hhMqGaIXLWoWnOkL2TYWUadpMgYC1Q2XFdUIA/7hJkM6o5YPKdF7RWx8G5Sh79WbuCwHOyY7I8t1o4FQ4lpQiX7bxnYNhn/OYygoX0Ry9sdOaQITR86h9KVolsO8ohvrFfREv2OBTCkN6482/trQGxEKGEwAvkCB3xvTW8AoHq0WfFAAw1wa19js5xOQ0i5HucLgQh0uyyEWnqwWwkCCJ4x6+AHp+/wPY9Na7B3Ia0kvTmDeq2uQMd9mMqjPe6la2G4P4s5UW8ObQ3zXn3N/SBoccgciM5dOh17gNhR6zJm9pClmX2XjafBmGaA64yNo1o7jKYwptPCzzp+9RlgJKSl8RpyUNJJIdCgoGj0ZezM2HvZY6Wrpf5l66qlsaMHlG+k7WI4Ys8DTXVOZ6su+s7pX6lp2XdAKm9Zhh4/LjgOETrW7AQWCC6IHyueuDOADgjQLyzm65eDwZv5MiznydHvodBslupmeqOhYYgAFQq8EzU3QYNs5r/KHSbBtSgT2UvNrB4lV94sgt8IfAuXcALwfryNVCCb0KTjiIREtNiNOzXev6irGLR6GkoaFN2o/ahogyVo2cn5bXI+O/doN60EovuUk35wQbz0FZxuFI6M9vcaEskkHNFNpjvGsMXIh8IviVBBwnqGwZPQkudRzkAlTuYJKR5GlV5Efo8i8w4GGlY7ghzhMu7nPtXZbNNZX5W9dKT2OIWgWi7L30jIJp6iJHaVXhgRvaTq7i62+7Kyk4aXnkGWJLTFWGjqbAWZoDGnhGX8fc0ob6efefyLl4O0l+iOZBoqx+7lPu4grEib49sxvgTn6V+Dk2wp4+1qyEZXmdH+z2p368ZOvxwSoYJv1GVHu5Vi+nvJXenZDFpQQ090JW0uSJ6BvR18fVm+vXoDDS6dBUJDe4eHnif+yT65W9qv4tj9Gy5T58tEefdq6k6zEW0peMlfViw5drTvZttl2k3lo8n9z+8QbTCyOAm4pxc8D0jWqiGyIj8Exz9yomg5KxpSnJ+Y3GzwtW4n/akk4FazgwCKlyYzg9aO/1EzWr4g8K5FNtXOiw0fFwtyx3c3nn3jlZ/CI+TV32wOa0KUP4elxjV3zpq6+ooZf7uh+dM86c3JPEW7CXqeXJSlxAM0IKfRNQP5wIlQFcXLADWAQyUG+GltJW6G3vxcYz8tRy+6FAqUWYz4gdxu5sf5uIJGau0ULqpD3rxDm+nzVFQ0g0v1U38jrE2itBOxRf54/WK/vFr9bPln88dMcHKkTwFKnRj0eT+gYcOkbTCZDrdLNxZQKRAFoFEonhLWvngXyFtpzQExXIW/UukhAs140E0y3YmzHJ79+YONWteWE16b5apYv7ZFSYRlBXznct7ZMOUnVEyKd+bn/DJl8q/gSYcjeS+DCNJCIB2ibJxGudMDM4DirykdVomaQ5yQAIUjyUAgXv3ZwZi7C/Q335aMtgylXn3liBZ+5hDQWOIDC1cfECW6JAVbdyGEsSgdTn6vitJgsowGidc17k6yDhQ+BB/xNuklpseu4/v9xa8be44YxWKYC/SI4G3mqS72Pjpq1lJ0Pvaucf8LS9+Q2M3KwAwxmsVj7fWi64LoWWapGhLeYIYowyU3sJrCWa4KyB0z35jD1Yd0zYMXLYvAXQ0s8+Um+fWYaf6wSdBq1PkeXw1V37cLuzJzXlZfZi4+GwnKCHH/4tVnVOhk7Y+xa5jUBmyiIji/+QCjdQtSquH8brJcY1vvJeOTmj1lv07HPMzPXkrkXszxJ2bKBv/cY1U2gVzDLSag/XjY71eNjYo7WWCV73DEJQeRd36va6skO+rql2ogrN/fM1cLCX8Fg1GIyr07LOzFjS5csD+9iSs8duWI3945xUDvZ56SrFa30rhmYc7ortX6FueGXilC+/PuDfDqK9jXP3W3UCI5TZuq78fQrRPIZYsG3mtCLqlNjrZnzNIm5rzZDm4UZgjdsh1SNVNshLTTEpG4mhXEWLSxa89wRBOXpdJdjROAJeGIzEmgeMxaTqhCBatPn1yK/4am9giOWYugcgyeTHYFd99jxGjbkfwbgdXc7lq26TvRT7MGR3lWNaM998BepzeNrvlQIT6b+saaqD5k2dLfu5V2Ray0V3KG5hZZdGMc2Zs70glxHuaFCWDotSMYzhKvecXXljNvEpM2TraptGlEQwNWUeOS279Daoxij2qin32mptFxqm96ZOtkST4Yelc5z3UrcyZEM9I4sAAgMfsE73Yanitv0Gt81hYcnfsbnryPO6RsHo6xQix5CT1t0ErLGrBiwuvJlSuerR4nKqs//JdtnjfmXdlh2AIi4ISbHPf1rR0cb5dXQCCtom+46lEWUlpudqxDOm37yf4vwgQp857loDe+MzhD/2lHl+5FYjBY3ffy6jXtrSvqKcUYbyxzRmhmXOfGHECJyxcAbXyuOhhW2cQZJ5pSOPpUegKIQfD+5apQhoJFF3z53lwwRS/lMwTdvDHiVYsNOWCvB0Rh7tXgOzOOe5owgXlBObRLPZn8/K7aMjfQwCqdp7e+cc5mfhfJrKdBjhFvntDu1ptxlALzsfTKjYzwuA=
*/