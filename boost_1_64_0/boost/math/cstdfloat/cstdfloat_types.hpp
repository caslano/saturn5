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
  #include <boost/static_assert.hpp>
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
    #elif defined(BOOST_INTEL)
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

      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float16_t>::is_iec559    == true, "boost::float16_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float16_t>::radix        ==    2, "boost::float16_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float16_t>::digits       ==   11, "boost::float16_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float16_t>::max_exponent ==   16, "boost::float16_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");

      #undef BOOST_CSTDFLOAT_FLOAT_16_MIN
      #undef BOOST_CSTDFLOAT_FLOAT_16_MAX
    #endif

    #if(BOOST_CSTDFLOAT_HAS_FLOAT32_NATIVE_TYPE == 1)
      typedef BOOST_CSTDFLOAT_FLOAT32_NATIVE_TYPE float32_t;
      typedef boost::float32_t float_fast32_t;
      typedef boost::float32_t float_least32_t;

      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float32_t>::is_iec559    == true, "boost::float32_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float32_t>::radix        ==    2, "boost::float32_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float32_t>::digits       ==   24, "boost::float32_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float32_t>::max_exponent ==  128, "boost::float32_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");

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

      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float64_t>::is_iec559    == true, "boost::float64_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float64_t>::radix        ==    2, "boost::float64_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float64_t>::digits       ==   53, "boost::float64_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float64_t>::max_exponent == 1024, "boost::float64_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");

      #undef BOOST_CSTDFLOAT_FLOAT_64_MIN
      #undef BOOST_CSTDFLOAT_FLOAT_64_MAX
    #endif

    #if(BOOST_CSTDFLOAT_HAS_FLOAT80_NATIVE_TYPE == 1)
      typedef BOOST_CSTDFLOAT_FLOAT80_NATIVE_TYPE float80_t;
      typedef boost::float80_t float_fast80_t;
      typedef boost::float80_t float_least80_t;

      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float80_t>::is_iec559    ==  true, "boost::float80_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float80_t>::radix        ==     2, "boost::float80_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float80_t>::digits       ==    64, "boost::float80_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float80_t>::max_exponent == 16384, "boost::float80_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");

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
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float128_t>::is_iec559    ==  true, "boost::float128_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float128_t>::radix        ==     2, "boost::float128_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float128_t>::digits       ==   113, "boost::float128_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
      BOOST_STATIC_ASSERT_MSG(std::numeric_limits<boost::float128_t>::max_exponent == 16384, "boost::float128_t has been detected in <boost/cstdfloat>, but verification with std::numeric_limits fails");
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
VOnsRMbmquDYj59lHAzcZ7BI/I+M5NO2+vAi73T3L7Z5gHisY6DRf/nlu3Xtt5v2i1uFvkOkFdo3BzN2nIem00bMy5g2kVTbXME3wmOYth3ijIIzxf8ENw1OvmW+ILxlLRsY878U/yzrfEHYRu4m03WB5LG5ZY6wfbusvKJqmunzB0nY1ow7H1rnjXDeHfJO7o3e/Qbx7xwJjmmdfN2junxFnnKKkQ0Z5lRSOre7PZF7SzFvZb0r33/VgYurY6Etzgpzt9cFnp+0upXOPUg87UA3tgd1WeyO9PWgZG84mvXLBAp/HR0xelxKSkarZHaG0UX7ZySlefu8QUozg0K43aP5cUr3aNeU5tG09O4pnaJ56fukz0wpyGgRSdk/Wv0lQSOtUvbKyButa3d/7ArPKUYPr4vkawxtPcWM1eF30rysbZf8/Nw9Gn2+se7hwbnB9IW/CM0b7iha/HjnK2dKHF2FeQvML7fQnKDzlnXsN2OyVybdtEyepkzu8MpkUW56l/ROKWkZuW1TkjJS9kpJz9gLCUEtA96S0jKw6LjngOdKGUR5Z26j7K39exHu7CLh6o39BQno8XgRt5XxaPf3QBWOjvvfcg8k7n7/wW0b5UaccfPGZ8ZN+4nqBem4HXe3yH7tVG4nyrmCord3r9geG4vZs3+ru0WIo9F15qYP8WV06611dfD7nn1U5EhCb2S98Ah6aWfy7uAGdPyeY2zcwuj2pdvdOgYHv5Wl42MD+vXQ2s8A8v10if8zzkGsn2dgLnQOtq3BiafBMVXScJvkp9jJ13H/RaF/1omQtx8xp0zF+HrvW4U2zzb+8p3dO1uo2J742QK01vXuIJ1n3xH/jZEehB6HyWL87EA9PE+9JKOJ25dxdCij5NngrRjbel2/ER6nzL2WL0nev3LN+K5t2fPfavXX/qP19SNpR6dRJ4da1qSqI6u0syWuNZTTUc751O011EEPrZ/WH3h+v3PPY7b/EyGa0e7yGOXHYc7j7yXuQL7pp8F7wGmSp8Yp33yTbzZ0R9Nzkv+H+VKUNN7hdFKd3qslLQdEptLe52KO4DsXYr7AZGnZbJWw7d2dtNy4dbnWz/uS5m3kZB/2HAO5l3WAWes/KH4d/fNKSd+QHHNXiBmTbXdBeWQfS/jXSXdPZz9W8ZVOL13T+HEXBepUqpS86b1B4n+A2wcJ+NMpzxvZM7xMX2DNQ970rqvAujhH67qufi4n1UnOVPJ8AON1Syc4TstciZG/Gcdjc8D16r9e/e7Sc62iRu835A1GSatTPmfOtz3nkrHmBzvnUj3P4Npc3LZa5oLtgblgqn77Td8t0IY1zuBdPHrma+YNsycYEpj/cvS7RXVptq73l7d35FcbofwV7xnKWmGHG7yHrrTf9HrzitlLpnwELaNMJWPnwZEWlvlG4wvcbeZqew7OE0rjzyGBsZtiDMxNb/9DqCzzR/A7GjbQ33M8u6R1YeQsQh8RybDOHRoHbnp+E6wLTUONpGEEeinZ1nmBOOx8Dw3/kPgfy+o01TpPEL6Bu+30Ljjxb+YcqLrtn4l9aWQvSmEAY9lkJ91ZgsvtlOxmzBfefOZ2cMYzP1yAWeX2QL+gAF2T453QeGzOLP4kcd4T2ZsWs5IW9HPwPneDsyQSMeNYqZRnW+yxu+3kTj2N40Ippw0W+sDdc4F93aPyzYci/cnDr0nzlZGotjsZk6Th+e1g2D81Lj17mC9xJ5t9wpMS132RQ5wTpY6fbkO5Ye4OrC9/zt8bAvahgfGqZ1bd3yW43aB6qUkJ3Mc6gXT59999SprCd91txS38Huc9uIXvv6vGLfwm7WExt+Jvuv9OxgbtZ+adTsu6Nziu5ATOO8I=
*/