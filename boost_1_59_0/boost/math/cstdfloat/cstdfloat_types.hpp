///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Implement the types for floating-point typedefs having specified widths.

#ifndef BOOST_MATH_CSTDFLOAT_TYPES_2014_01_09_HPP_
  #define BOOST_MATH_CSTDFLOAT_TYPES_2014_01_09_HPP_

  #include <float.h>
  #include <limits>
  #include <boost/math/tools/config.hpp>

  // This is the beginning of the preamble.

  // In this preamble, the preprocessor is used to query certain
  // preprocessor definitions from <float.h>. Based on the results
  // of these queries, an attempt is made to automatically detect
  // the presence of built-in floating-point types having specified
  // widths. These are *thought* to be conformant with IEEE-754,
  // whereby an unequivocal test based on std::numeric_limits<>
  // follows below.

  // In addition, various macros that are used for initializing
  // floating-point literal values having specified widths and
  // some basic min/max values are defined.

  // First, we will pre-load certain preprocessor definitions
  // with a dummy value.

  #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH  0

  #define BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  0
  #define BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  0
  #define BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  0
  #define BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  0
  #define BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE 0

  // Ensure that the compiler has a radix-2 floating-point representation.
  #if (!defined(FLT_RADIX) || ((defined(FLT_RADIX) && (FLT_RADIX != 2))))
    #error The compiler does not support any radix-2 floating-point types required for <boost/cstdfloat.hpp>.
  #endif

  // Check if built-in float is equivalent to float16_t, float32_t, float64_t, float80_t, or float128_t.
  #if(defined(FLT_MANT_DIG) && defined(FLT_MAX_EXP))
    #if  ((FLT_MANT_DIG == 11) && (FLT_MAX_EXP == 16) && (BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT16_NATIVE_TYPE float
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
      #define BOOST_FLOAT16_C(x)  (x ## F)
      #define BOOST_CSTDFLOAT_FLOAT_16_MIN  FLT_MIN
      #define BOOST_CSTDFLOAT_FLOAT_16_MAX  FLT_MAX
    #elif((FLT_MANT_DIG == 24) && (FLT_MAX_EXP == 128) && (BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT32_NATIVE_TYPE float
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
      #define BOOST_FLOAT32_C(x)  (x ## F)
      #define BOOST_CSTDFLOAT_FLOAT_32_MIN  FLT_MIN
      #define BOOST_CSTDFLOAT_FLOAT_32_MAX  FLT_MAX
    #elif((FLT_MANT_DIG == 53) && (FLT_MAX_EXP == 1024) && (BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT64_NATIVE_TYPE float
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
      #define BOOST_FLOAT64_C(x)  (x ## F)
      #define BOOST_CSTDFLOAT_FLOAT_64_MIN  FLT_MIN
      #define BOOST_CSTDFLOAT_FLOAT_64_MAX  FLT_MAX
    #elif((FLT_MANT_DIG == 64) && (FLT_MAX_EXP == 16384) && (BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT80_NATIVE_TYPE float
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
      #define BOOST_FLOAT80_C(x)  (x ## F)
      #define BOOST_CSTDFLOAT_FLOAT_80_MIN  FLT_MIN
      #define BOOST_CSTDFLOAT_FLOAT_80_MAX  FLT_MAX
    #elif((FLT_MANT_DIG == 113) && (FLT_MAX_EXP == 16384) && (BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT128_NATIVE_TYPE float
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
      #define BOOST_FLOAT128_C(x)  (x ## F)
      #define BOOST_CSTDFLOAT_FLOAT_128_MIN  FLT_MIN
      #define BOOST_CSTDFLOAT_FLOAT_128_MAX  FLT_MAX
    #endif
  #endif

  // Check if built-in double is equivalent to float16_t, float32_t, float64_t, float80_t, or float128_t.
  #if(defined(DBL_MANT_DIG) && defined(DBL_MAX_EXP))
    #if  ((DBL_MANT_DIG == 11) && (DBL_MAX_EXP == 16) && (BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT16_NATIVE_TYPE double
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
      #define BOOST_FLOAT16_C(x)  (x)
      #define BOOST_CSTDFLOAT_FLOAT_16_MIN  DBL_MIN
      #define BOOST_CSTDFLOAT_FLOAT_16_MAX  DBL_MAX
    #elif((DBL_MANT_DIG == 24) && (DBL_MAX_EXP == 128) && (BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT32_NATIVE_TYPE double
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
      #define BOOST_FLOAT32_C(x)  (x)
      #define BOOST_CSTDFLOAT_FLOAT_32_MIN  DBL_MIN
      #define BOOST_CSTDFLOAT_FLOAT_32_MAX  DBL_MAX
    #elif((DBL_MANT_DIG == 53) && (DBL_MAX_EXP == 1024) && (BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT64_NATIVE_TYPE double
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
      #define BOOST_FLOAT64_C(x)  (x)
      #define BOOST_CSTDFLOAT_FLOAT_64_MIN  DBL_MIN
      #define BOOST_CSTDFLOAT_FLOAT_64_MAX  DBL_MAX
    #elif((DBL_MANT_DIG == 64) && (DBL_MAX_EXP == 16384) && (BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT80_NATIVE_TYPE double
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
      #define BOOST_FLOAT80_C(x)  (x)
      #define BOOST_CSTDFLOAT_FLOAT_80_MIN  DBL_MIN
      #define BOOST_CSTDFLOAT_FLOAT_80_MAX  DBL_MAX
    #elif((DBL_MANT_DIG == 113) && (DBL_MAX_EXP == 16384) && (BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
      #define BOOST_CSTDFLOAT_FLOAT128_NATIVE_TYPE double
      #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
      #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
      #undef  BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
      #define BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
      #define BOOST_FLOAT128_C(x)  (x)
      #define BOOST_CSTDFLOAT_FLOAT_128_MIN  DBL_MIN
      #define BOOST_CSTDFLOAT_FLOAT_128_MAX  DBL_MAX
    #endif
  #endif

  // Disable check long double capability even if supported by compiler since some math runtime
  // implementations are broken for long double.
  #ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
    // Check if built-in long double is equivalent to float16_t, float32_t, float64_t, float80_t, or float128_t.
    #if(defined(LDBL_MANT_DIG) && defined(LDBL_MAX_EXP))
      #if  ((LDBL_MANT_DIG == 11) && (LDBL_MAX_EXP == 16) && (BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 0))
        #define BOOST_CSTDFLOAT_FLOAT16_NATIVE_TYPE long double
        #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
        #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 16
        #undef  BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE
        #define BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  1
        #define BOOST_FLOAT16_C(x)  (x ## L)
        #define BOOST_CSTDFLOAT_FLOAT_16_MIN  LDBL_MIN
        #define BOOST_CSTDFLOAT_FLOAT_16_MAX  LDBL_MAX
      #elif((LDBL_MANT_DIG == 24) && (LDBL_MAX_EXP == 128) && (BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 0))
        #define BOOST_CSTDFLOAT_FLOAT32_NATIVE_TYPE long double
        #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
        #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 32
        #undef  BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE
        #define BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  1
        #define BOOST_FLOAT32_C(x)  (x ## L)
        #define BOOST_CSTDFLOAT_FLOAT_32_MIN  LDBL_MIN
        #define BOOST_CSTDFLOAT_FLOAT_32_MAX  LDBL_MAX
      #elif((LDBL_MANT_DIG == 53) && (LDBL_MAX_EXP == 1024) && (BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 0))
        #define BOOST_CSTDFLOAT_FLOAT64_NATIVE_TYPE long double
        #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
        #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
        #undef  BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
        #define BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  1
        #define BOOST_FLOAT64_C(x)  (x ## L)
        #define BOOST_CSTDFLOAT_FLOAT_64_MIN  LDBL_MIN
        #define BOOST_CSTDFLOAT_FLOAT_64_MAX  LDBL_MAX
      #elif((LDBL_MANT_DIG == 64) && (LDBL_MAX_EXP == 16384) && (BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 0))
        #define BOOST_CSTDFLOAT_FLOAT80_NATIVE_TYPE long double
        #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
        #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 80
        #undef  BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
        #define BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  1
        #define BOOST_FLOAT80_C(x)  (x ## L)
        #define BOOST_CSTDFLOAT_FLOAT_80_MIN  LDBL_MIN
        #define BOOST_CSTDFLOAT_FLOAT_80_MAX  LDBL_MAX
      #elif((LDBL_MANT_DIG == 113) && (LDBL_MAX_EXP == 16384) && (BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
        #define BOOST_CSTDFLOAT_FLOAT128_NATIVE_TYPE long double
        #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
        #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
        #undef  BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
        #define BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
        #define BOOST_FLOAT128_C(x)  (x ## L)
        #define BOOST_CSTDFLOAT_FLOAT_128_MIN  LDBL_MIN
        #define BOOST_CSTDFLOAT_FLOAT_128_MAX  LDBL_MAX
      #endif
    #endif
  #endif

  // Check if quadruple-precision is supported. Here, we are checking
  // for the presence of __float128 from GCC's quadmath.h or _Quad
  // from ICC's /Qlong-double flag). To query these, we use the
  // BOOST_MATH_USE_FLOAT128 pre-processor definition from
  // <boost/math/tools/config.hpp>.

  #if (BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0) && defined(BOOST_MATH_USE_FLOAT128) && !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT)

    // Specify the underlying name of the internal 128-bit floating-point type definition.
    namespace boost { namespace math { namespace cstdfloat { namespace detail {
    #if defined(__GNUC__)
      typedef __float128      float_internal128_t;
    #elif defined(__INTEL_COMPILER)
      typedef _Quad           float_internal128_t;
    #else
      #error "Sorry, the compiler is neither GCC, nor Intel, I don't know how to configure <boost/cstdfloat.hpp>."
    #endif
    } } } } // boost::math::cstdfloat::detail

    #define BOOST_CSTDFLOAT_FLOAT128_NATIVE_TYPE boost::math::cstdfloat::detail::float_internal128_t
    #undef  BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
    #define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 128
    #undef  BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
    #define BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE  1
    #define BOOST_FLOAT128_C(x)  (x ## Q)
    #define BOOST_CSTDFLOAT_FLOAT128_MIN  3.36210314311209350626267781732175260e-4932Q
    #define BOOST_CSTDFLOAT_FLOAT128_MAX  1.18973149535723176508575932662800702e+4932Q
    #define BOOST_CSTDFLOAT_FLOAT128_EPS  1.92592994438723585305597794258492732e-0034Q
    #define BOOST_CSTDFLOAT_FLOAT128_DENORM_MIN  6.475175119438025110924438958227646552e-4966Q

  #endif // Not BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT (i.e., the user would like to have libquadmath support)

  // This is the end of the preamble, and also the end of the
  // sections providing support for the C++ standard library
  // for quadruple-precision.

  // Now we use the results of the queries that have been obtained
  // in the preamble (far above) for the final type definitions in
  // the namespace boost.

  // Make sure that the compiler has any floating-point type(s) whatsoever.
  #if (   (BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE  == 0)  \
       && (BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE  == 0)  \
       && (BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE  == 0)  \
       && (BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE  == 0)  \
       && (BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 0))
    #error The compiler does not support any of the floating-point types required for <boost/cstdfloat.hpp>.
  #endif

  // The following section contains the various min/max macros
  // for the *leastN and *fastN types.

  #if(BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 1)
    #define BOOST_FLOAT_FAST16_MIN   BOOST_CSTDFLOAT_FLOAT_16_MIN
    #define BOOST_FLOAT_LEAST16_MIN  BOOST_CSTDFLOAT_FLOAT_16_MIN
    #define BOOST_FLOAT_FAST16_MAX   BOOST_CSTDFLOAT_FLOAT_16_MAX
    #define BOOST_FLOAT_LEAST16_MAX  BOOST_CSTDFLOAT_FLOAT_16_MAX
  #endif

  #if(BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 1)
    #define BOOST_FLOAT_FAST32_MIN   BOOST_CSTDFLOAT_FLOAT_32_MIN
    #define BOOST_FLOAT_LEAST32_MIN  BOOST_CSTDFLOAT_FLOAT_32_MIN
    #define BOOST_FLOAT_FAST32_MAX   BOOST_CSTDFLOAT_FLOAT_32_MAX
    #define BOOST_FLOAT_LEAST32_MAX  BOOST_CSTDFLOAT_FLOAT_32_MAX
  #endif

  #if(BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 1)
    #define BOOST_FLOAT_FAST64_MIN   BOOST_CSTDFLOAT_FLOAT_64_MIN
    #define BOOST_FLOAT_LEAST64_MIN  BOOST_CSTDFLOAT_FLOAT_64_MIN
    #define BOOST_FLOAT_FAST64_MAX   BOOST_CSTDFLOAT_FLOAT_64_MAX
    #define BOOST_FLOAT_LEAST64_MAX  BOOST_CSTDFLOAT_FLOAT_64_MAX
  #endif

  #if(BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 1)
    #define BOOST_FLOAT_FAST80_MIN   BOOST_CSTDFLOAT_FLOAT_80_MIN
    #define BOOST_FLOAT_LEAST80_MIN  BOOST_CSTDFLOAT_FLOAT_80_MIN
    #define BOOST_FLOAT_FAST80_MAX   BOOST_CSTDFLOAT_FLOAT_80_MAX
    #define BOOST_FLOAT_LEAST80_MAX  BOOST_CSTDFLOAT_FLOAT_80_MAX
  #endif

  #if(BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 1)
    #define BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T

    #define BOOST_FLOAT_FAST128_MIN   BOOST_CSTDFLOAT_FLOAT_128_MIN
    #define BOOST_FLOAT_LEAST128_MIN  BOOST_CSTDFLOAT_FLOAT_128_MIN
    #define BOOST_FLOAT_FAST128_MAX   BOOST_CSTDFLOAT_FLOAT_128_MAX
    #define BOOST_FLOAT_LEAST128_MAX  BOOST_CSTDFLOAT_FLOAT_128_MAX
  #endif

  // The following section contains the various min/max macros
  // for the *floatmax types.

  #if  (BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 16)
    #define BOOST_FLOATMAX_C(x) BOOST_FLOAT16_C(x)
    #define BOOST_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_16_MIN
    #define BOOST_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_16_MAX
  #elif(BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 32)
    #define BOOST_FLOATMAX_C(x) BOOST_FLOAT32_C(x)
    #define BOOST_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_32_MIN
    #define BOOST_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_32_MAX
  #elif(BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 64)
    #define BOOST_FLOATMAX_C(x) BOOST_FLOAT64_C(x)
    #define BOOST_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_64_MIN
    #define BOOST_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_64_MAX
  #elif(BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 80)
    #define BOOST_FLOATMAX_C(x) BOOST_FLOAT80_C(x)
    #define BOOST_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_80_MIN
    #define BOOST_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_80_MAX
  #elif(BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 128)
    #define BOOST_FLOATMAX_C(x) BOOST_FLOAT128_C(x)
    #define BOOST_FLOATMAX_MIN  BOOST_CSTDFLOAT_FLOAT_128_MIN
    #define BOOST_FLOATMAX_MAX  BOOST_CSTDFLOAT_FLOAT_128_MAX
  #else
    #error The maximum available floating-point width for <boost/cstdfloat.hpp> is undefined.
  #endif

  // And finally..., we define the floating-point typedefs having
  // specified widths. The types are defined in the namespace boost.

  // For simplicity, the least and fast types are type defined identically
  // as the corresponding fixed-width type. This behavior may, however,
  // be modified when being optimized for a given compiler implementation.

  // In addition, a clear assessment of IEEE-754 conformance is carried out
  // using compile-time assertion.

  namespace boost
  {
    #if(BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE == 1)
      typedef BOOST_CSTDFLOAT_FLOAT16_NATIVE_TYPE float16_t;
      typedef boost::float16_t float_fast16_t;
      typedef boost::float16_t float_least16_t;

      static_assert(std::numeric_limits<boost::float16_t>::is_iec559    == true, "boost::float16_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float16_t>::radix        ==    2, "boost::float16_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float16_t>::digits       ==   11, "boost::float16_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float16_t>::max_exponent ==   16, "boost::float16_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");

      #undef BOOST_CSTDFLOAT_FLOAT_16_MIN
      #undef BOOST_CSTDFLOAT_FLOAT_16_MAX
    #endif

    #if(BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 1)
      typedef BOOST_CSTDFLOAT_FLOAT32_NATIVE_TYPE float32_t;
      typedef boost::float32_t float_fast32_t;
      typedef boost::float32_t float_least32_t;

      static_assert(std::numeric_limits<boost::float32_t>::is_iec559    == true, "boost::float32_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float32_t>::radix        ==    2, "boost::float32_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float32_t>::digits       ==   24, "boost::float32_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float32_t>::max_exponent ==  128, "boost::float32_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");

      #undef BOOST_CSTDFLOAT_FLOAT_32_MIN
      #undef BOOST_CSTDFLOAT_FLOAT_32_MAX
    #endif

#if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && defined(__SUNPRO_CC)
#undef BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
#define BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE 0
#undef BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE
#define BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE 0
#undef BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
#define BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH 64
#endif

    #if(BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE == 1)
      typedef BOOST_CSTDFLOAT_FLOAT64_NATIVE_TYPE float64_t;
      typedef boost::float64_t float_fast64_t;
      typedef boost::float64_t float_least64_t;

      static_assert(std::numeric_limits<boost::float64_t>::is_iec559    == true, "boost::float64_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float64_t>::radix        ==    2, "boost::float64_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float64_t>::digits       ==   53, "boost::float64_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float64_t>::max_exponent == 1024, "boost::float64_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");

      #undef BOOST_CSTDFLOAT_FLOAT_64_MIN
      #undef BOOST_CSTDFLOAT_FLOAT_64_MAX
    #endif

    #if(BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 1)
      typedef BOOST_CSTDFLOAT_FLOAT80_NATIVE_TYPE float80_t;
      typedef boost::float80_t float_fast80_t;
      typedef boost::float80_t float_least80_t;

      static_assert(std::numeric_limits<boost::float80_t>::is_iec559    ==  true, "boost::float80_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float80_t>::radix        ==     2, "boost::float80_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float80_t>::digits       ==    64, "boost::float80_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float80_t>::max_exponent == 16384, "boost::float80_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");

      #undef BOOST_CSTDFLOAT_FLOAT_80_MIN
      #undef BOOST_CSTDFLOAT_FLOAT_80_MAX
    #endif

    #if(BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE == 1)
      typedef BOOST_CSTDFLOAT_FLOAT128_NATIVE_TYPE float128_t;
      typedef boost::float128_t float_fast128_t;
      typedef boost::float128_t float_least128_t;

      #if defined(BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T) && defined(BOOST_MATH_USE_FLOAT128) && !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT)
      // This configuration does not *yet* support std::numeric_limits<boost::float128_t>.
      // Support for std::numeric_limits<boost::float128_t> is added in the detail
      // file <boost/math/cstdfloat/cstdfloat_limits.hpp>.
      #else
      static_assert(std::numeric_limits<boost::float128_t>::is_iec559    ==  true, "boost::float128_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float128_t>::radix        ==     2, "boost::float128_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float128_t>::digits       ==   113, "boost::float128_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      static_assert(std::numeric_limits<boost::float128_t>::max_exponent == 16384, "boost::float128_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      #endif

      #undef BOOST_CSTDFLOAT_FLOAT_128_MIN
      #undef BOOST_CSTDFLOAT_FLOAT_128_MAX
    #endif

    #if  (BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH ==  16)
      typedef boost::float16_t  floatmax_t;
    #elif(BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH ==  32)
      typedef boost::float32_t  floatmax_t;
    #elif(BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH ==  64)
      typedef boost::float64_t  floatmax_t;
    #elif(BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH ==  80)
      typedef boost::float80_t  floatmax_t;
    #elif(BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH == 128)
      typedef boost::float128_t floatmax_t;
    #else
      #error The maximum available floating-point width for <boost/cstdfloat.hpp> is undefined.
    #endif

    #undef BOOST_CSTDFLOAT_HAS_FLOAT16_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_HAS_FLOAT64_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE
    #undef BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE

    #undef BOOST_CSTDFLOAT_MAXIMUM_AVAILABLE_WIDTH
  }
  // namespace boost

#endif // BOOST_MATH_CSTDFLOAT_BASE_TYPES_2014_01_09_HPP_


/* cstdfloat_types.hpp
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
*/