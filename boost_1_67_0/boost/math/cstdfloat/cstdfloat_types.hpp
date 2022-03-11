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
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
*/