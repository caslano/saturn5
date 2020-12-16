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
    #if defined(BOOST_INTEL)
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
        BOOST_STATIC_CONSTEXPR bool                                                 is_specialized           = true;
        static                 boost::math::cstdfloat::detail::float_internal128_t  (min) () BOOST_NOEXCEPT  { return BOOST_CSTDFLOAT_FLOAT128_MIN; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  (max) () BOOST_NOEXCEPT  { return BOOST_CSTDFLOAT_FLOAT128_MAX; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  lowest() BOOST_NOEXCEPT  { return -(max)(); }
        BOOST_STATIC_CONSTEXPR int                                                  digits                   = 113;
        BOOST_STATIC_CONSTEXPR int                                                  digits10                 = 33;
        BOOST_STATIC_CONSTEXPR int                                                  max_digits10             = 36;
        BOOST_STATIC_CONSTEXPR bool                                                 is_signed                = true;
        BOOST_STATIC_CONSTEXPR bool                                                 is_integer               = false;
        BOOST_STATIC_CONSTEXPR bool                                                 is_exact                 = false;
        BOOST_STATIC_CONSTEXPR int                                                  radix                    = 2;
        static                 boost::math::cstdfloat::detail::float_internal128_t  epsilon    ()            { return BOOST_CSTDFLOAT_FLOAT128_EPS; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  round_error()            { return BOOST_FLOAT128_C(0.5); }
        BOOST_STATIC_CONSTEXPR int                                                  min_exponent             = -16381;
        BOOST_STATIC_CONSTEXPR int                                                  min_exponent10           = static_cast<int>((min_exponent * 301L) / 1000L);
        BOOST_STATIC_CONSTEXPR int                                                  max_exponent             = +16384;
        BOOST_STATIC_CONSTEXPR int                                                  max_exponent10           = static_cast<int>((max_exponent * 301L) / 1000L);
        BOOST_STATIC_CONSTEXPR bool                                                 has_infinity             = true;
        BOOST_STATIC_CONSTEXPR bool                                                 has_quiet_NaN            = true;
        BOOST_STATIC_CONSTEXPR bool                                                 has_signaling_NaN        = false;
        BOOST_STATIC_CONSTEXPR float_denorm_style                                   has_denorm               = denorm_present;
        BOOST_STATIC_CONSTEXPR bool                                                 has_denorm_loss          = false;
        static                 boost::math::cstdfloat::detail::float_internal128_t  infinity     ()          { return BOOST_FLOAT128_C(1.0) / BOOST_FLOAT128_C(0.0); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  quiet_NaN    ()          { return -(::BOOST_CSTDFLOAT_FLOAT128_SQRT(BOOST_FLOAT128_C(-1.0))); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  signaling_NaN()          { return BOOST_FLOAT128_C(0.0); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  denorm_min   ()          { return BOOST_CSTDFLOAT_FLOAT128_DENORM_MIN; }
        BOOST_STATIC_CONSTEXPR bool                                                 is_iec559                = true;
        BOOST_STATIC_CONSTEXPR bool                                                 is_bounded               = true;
        BOOST_STATIC_CONSTEXPR bool                                                 is_modulo                = false;
        BOOST_STATIC_CONSTEXPR bool                                                 traps                    = false;
        BOOST_STATIC_CONSTEXPR bool                                                 tinyness_before          = false;
        BOOST_STATIC_CONSTEXPR float_round_style                                    round_style              = round_to_nearest;
      };
    } // namespace std

  #endif // Not BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT (i.e., the user would like to have libquadmath support)

#endif // BOOST_MATH_CSTDFLOAT_LIMITS_2014_01_09_HPP_


/* cstdfloat_limits.hpp
2A8cAA4BB4FDwRFgCXgQ+CNwNDgcHA+eAJ4E9gFPUfsU8BBwIXgouAQ8HLwWPAK8HTwSvA88CnwVPAZ8AzwO/Fzi8d8i1/207u9rQm+Rl+n8dZr2x2n6Jvh0cLa+2T4XnOG3O3+Pqnuj1Y3o6mYmSFf0DXRvReSN7m98nztRvV99fztwf27wve36b20H39UeNcb6jra+od2wnvCDmPBb2Ek79P1rjP/OdRVmGSb0tnX4TWvzjnUJZrLqF1eD6Bjr29Txb1LvwKjOcYPvT+u706p/bN6Y9t+XFj3kTaDtPekyTBUm8H50UFfZvA+9eXz4TejG34PehRk+wn8D2rz7HH7zWd97Dus12952tr/jnPF8knnL+VWwMf3nkaoDHXyDeQ2mRvWia8EtmHUn0QYxb2HSJvJmOmYUZgZmGWYDZhPmHUzayU360k2/pl/Tr+nX9Gv6Nf2afk2/pl/Tr+m3O78fTP+/rHyP6P/noB9zaAn8rDKPN4u8SL8pnrC13Atwa+BegLyoI78lmI6YeZiRMEBq33bj9ejK+k236JIY+Ym/Q2+X19C4lEe9vU6OeWZQN+RD8e9r41kHwwqtq7LrNv4+tDb5eyNb9bH4H8eZdKZV3k/DB2SOKxBIiukKblG5tpsLRB5E3N7CzZNFqvWoI5zL8t2MpAHpzVIi0RxeqGyeFJNFuk3fyQ7I7c2Le6f2b97Xu+GfozKxWZlFjv60PPR3EPS0hSEik9WWUI3JFnll3lbLHDctN9y0LG16STm4bfHlhQLlgOyK5JkywL00Tnd1fbImTvU0DsScA101+QrfMUFzSkj+lLC2tmNrK9Am3lagtbUVa7uA1iIzapejh7ZRXaSw3Hww7gqhn1VRpbQFAdqCEO3ZBaJLWTVfaYsCtEUB2mBbC8ourRP//FDbtOjd7ca7ut+mnXlu2Ra5tjy7npCUSYW4U07qVgRSHrhRHr7uq7bJCSn13wJ5H9otgTapo2O4fk2/fEtoW9FuXFsb1bjchPV5g3kN6rVUpCrPOPD+8qgS/tnmGhnu0mnlpadPKp8FT7DB8TRd6PNsaSUuSx+x9acAbXOjI1phxvsW4tfSyMt1Fnsk4XeZw20lLdhWQuUySu+ornHr2vaD4OGUS3G9cqmSwJK3JOlLYvfTvOgdyY2tXDQu7S91YamgWNhrNKytnDSs6pRIWG2zsfCXSPiW1rEo+O2KpLr6nBroq1Ml7DDL2GQLW1oZ1E+qkrAtrGMVYe3zsob9mebZb1cHCH2ydRwrtrYr+zgWLC99d2F+hepH5qiM9wHy7bucaZTQeU6abYyzx6Ml79F3CdB3UfqGxtruAdruSmsbawu1Tg4V/5+5DxL6PScNPuBop8ptJvLevUz4JfC9W5t4e9UvJ34iVWrksaeI/y5KfZCzihq+0xlj5LGnSJmMZaUUkTTvCMnZ+++HT5M4Frvt0Ca4gdb9DKaNOxjeeZLRtzpX4uob6Nuzjf7TGAl/kxvo90a34CDxe5IcZ8PzH+zcp2up7XE6qXW1maPrrnIJs46xty/pSbXIiGutBcbciRJmIW1rqJFxv/IdHWN0zGkh9heddqRlEnk8zTkAuaBkpedeIPFvb+qkom68YBE/yOiL+fqOM4tEoMs3Mo5lB2W5reMYyD9tdZwxcpF1bloGzINGj1HHhcBcWOG5a3/XuVDd6MfqlmcZLwvix0v5TpGZW7Q/qXuXgLuWtMTR3TKX9grNpbhJO5NvaVtlDSj1Tdvw3MwbClV1NCbfO42bfjV0L8XzWSqzEeGudXAWOJpxffLfA+P6rBkzykvr5mZvYHBVv7WbtvVKoZ0Y2Yf6P5f2vRHzLqYV9x8dhsmRt4k0Tr4=
*/