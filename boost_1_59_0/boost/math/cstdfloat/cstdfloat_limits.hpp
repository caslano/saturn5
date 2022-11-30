///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Implement quadruple-precision std::numeric_limits<> support.

#ifndef BOOST_MATH_CSTDFLOAT_LIMITS_2014_01_09_HPP_
  #define BOOST_MATH_CSTDFLOAT_LIMITS_2014_01_09_HPP_

  #include <boost/math/cstdfloat/cstdfloat_types.hpp>

#if defined(__GNUC__) && defined(BOOST_MATH_USE_FLOAT128)
//
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma diagnostic ignored work :(
//
#pragma GCC system_header
#endif

  #if defined(BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T) && defined(BOOST_MATH_USE_FLOAT128) && !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT)

    #include <limits>

    // Define the name of the global quadruple-precision function to be used for
    // calculating quiet_NaN() in the specialization of std::numeric_limits<>.
    #if defined(__INTEL_COMPILER)
      #define BOOST_CSTDFLOAT_FLOAT128_SQRT   __sqrtq
    #elif defined(__GNUC__)
      #define BOOST_CSTDFLOAT_FLOAT128_SQRT   sqrtq
    #endif

    // Forward declaration of the quadruple-precision square root function.
    extern "C" boost::math::cstdfloat::detail::float_internal128_t BOOST_CSTDFLOAT_FLOAT128_SQRT(boost::math::cstdfloat::detail::float_internal128_t) throw();

    namespace std
    {
      template<>
      class numeric_limits<boost::math::cstdfloat::detail::float_internal128_t>
      {
      public:
        static constexpr bool                                                 is_specialized           = true;
        static                 boost::math::cstdfloat::detail::float_internal128_t  (min) () noexcept  { return BOOST_CSTDFLOAT_FLOAT128_MIN; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  (max) () noexcept  { return BOOST_CSTDFLOAT_FLOAT128_MAX; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  lowest() noexcept  { return -(max)(); }
        static constexpr int                                                  digits                   = 113;
        static constexpr int                                                  digits10                 = 33;
        static constexpr int                                                  max_digits10             = 36;
        static constexpr bool                                                 is_signed                = true;
        static constexpr bool                                                 is_integer               = false;
        static constexpr bool                                                 is_exact                 = false;
        static constexpr int                                                  radix                    = 2;
        static                 boost::math::cstdfloat::detail::float_internal128_t  epsilon    ()            { return BOOST_CSTDFLOAT_FLOAT128_EPS; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  round_error()            { return BOOST_FLOAT128_C(0.5); }
        static constexpr int                                                  min_exponent             = -16381;
        static constexpr int                                                  min_exponent10           = static_cast<int>((min_exponent * 301L) / 1000L);
        static constexpr int                                                  max_exponent             = +16384;
        static constexpr int                                                  max_exponent10           = static_cast<int>((max_exponent * 301L) / 1000L);
        static constexpr bool                                                 has_infinity             = true;
        static constexpr bool                                                 has_quiet_NaN            = true;
        static constexpr bool                                                 has_signaling_NaN        = false;
        static constexpr float_denorm_style                                   has_denorm               = denorm_present;
        static constexpr bool                                                 has_denorm_loss          = false;
        static                 boost::math::cstdfloat::detail::float_internal128_t  infinity     ()          { return BOOST_FLOAT128_C(1.0) / BOOST_FLOAT128_C(0.0); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  quiet_NaN    ()          { return -(::BOOST_CSTDFLOAT_FLOAT128_SQRT(BOOST_FLOAT128_C(-1.0))); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  signaling_NaN()          { return BOOST_FLOAT128_C(0.0); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  denorm_min   ()          { return BOOST_CSTDFLOAT_FLOAT128_DENORM_MIN; }
        static constexpr bool                                                 is_iec559                = true;
        static constexpr bool                                                 is_bounded               = true;
        static constexpr bool                                                 is_modulo                = false;
        static constexpr bool                                                 traps                    = false;
        static constexpr bool                                                 tinyness_before          = false;
        static constexpr float_round_style                                    round_style              = round_to_nearest;
      };
    } // namespace std

  #endif // Not BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT (i.e., the user would like to have libquadmath support)

#endif // BOOST_MATH_CSTDFLOAT_LIMITS_2014_01_09_HPP_


/* cstdfloat_limits.hpp
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
*/