///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_2F0_HPP
#define BOOST_MATH_HYPERGEOMETRIC_2F0_HPP

#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/detail/hypergeometric_series.hpp>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/hermite.hpp>
#include <boost/math/tools/fraction.hpp>

namespace boost { namespace math { namespace detail {

   template <class T>
   struct hypergeometric_2F0_cf
   {
      //
      // We start this continued fraction at b on index -1
      // and treat the -1 and 0 cases as special cases.
      // We do this to avoid adding the continued fraction result
      // to 1 so that we can accurately evaluate for small results
      // as well as large ones.  See  http://functions.wolfram.com/07.31.10.0002.01
      //
      T a1, a2, z;
      int k;
      hypergeometric_2F0_cf(T a1_, T a2_, T z_) : a1(a1_), a2(a2_), z(z_), k(-2) {}
      typedef std::pair<T, T> result_type;

      result_type operator()()
      {
         ++k;
         if (k <= 0)
            return std::make_pair(z * a1 * a2, 1);
         return std::make_pair(-z * (a1 + k) * (a2 + k) / (k + 1), 1 + z * (a1 + k) * (a2 + k) / (k + 1));
      }
   };

   template <class T, class Policy>
   T hypergeometric_2F0_cf_imp(T a1, T a2, T z, const Policy& pol, const char* function)
   {
      using namespace boost::math;
      hypergeometric_2F0_cf<T> evaluator(a1, a2, z);
      boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
      T cf = tools::continued_fraction_b(evaluator, policies::get_epsilon<T, Policy>(), max_iter);
      policies::check_series_iterations<T>(function, max_iter, pol);
      return cf;
   }


   template <class T, class Policy>
   inline T hypergeometric_2F0_imp(T a1, T a2, const T& z, const Policy& pol, bool asymptotic = false)
   {
      //
      // The terms in this series go to infinity unless one of a1 and a2 is a negative integer.
      //
      using std::swap;
      BOOST_MATH_STD_USING

      static const char* const function = "boost::math::hypergeometric_2F0<%1%,%1%,%1%>(%1%,%1%,%1%)";

      if (z == 0)
         return 1;

      bool is_a1_integer = (a1 == floor(a1));
      bool is_a2_integer = (a2 == floor(a2));

      if (!asymptotic && !is_a1_integer && !is_a2_integer)
         return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
      if (!is_a1_integer || (a1 > 0))
      {
         swap(a1, a2);
         swap(is_a1_integer, is_a2_integer);
      }
      //
      // At this point a1 must be a negative integer:
      //
      if(!asymptotic && (!is_a1_integer || (a1 > 0)))
         return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
      //
      // Special cases first:
      //
      if (a1 == 0)
         return 1;
      if ((a1 == a2 - 0.5f) && (z < 0))
      {
         // http://functions.wolfram.com/07.31.03.0083.01
         int n = static_cast<int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-2 * a1)));
         T smz = sqrt(-z);
         return pow(2 / smz, -n) * boost::math::hermite(n, 1 / smz);
      }

      if (is_a1_integer && is_a2_integer)
      {
         if ((a1 < 1) && (a2 <= a1))
         {
            const unsigned int n = static_cast<unsigned int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-a1)));
            const unsigned int m = static_cast<unsigned int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-a2 - n)));

            return (pow(z, T(n)) * boost::math::factorial<T>(n, pol)) *
               boost::math::laguerre(n, m, -(1 / z), pol);
         }
         else if ((a2 < 1) && (a1 <= a2))
         {
            // function is symmetric for a1 and a2
            const unsigned int n = static_cast<unsigned int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-a2)));
            const unsigned int m = static_cast<unsigned int>(static_cast<boost::uintmax_t>(boost::math::lltrunc(-a1 - n)));

            return (pow(z, T(n)) * boost::math::factorial<T>(n, pol)) *
               boost::math::laguerre(n, m, -(1 / z), pol);
         }
      }

      if ((a1 * a2 * z < 0) && (a2 < -5) && (fabs(a1 * a2 * z) > 0.5))
      {
         // Series is alternating and maybe divergent at least for the first few terms
         // (until a2 goes positive), try the continued fraction:
         return hypergeometric_2F0_cf_imp(a1, a2, z, pol, function);
      }

      return detail::hypergeometric_2F0_generic_series(a1, a2, z, pol);
   }

} // namespace detail

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type hypergeometric_2F0(T1 a1, T2 a2, T3 z, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::hypergeometric_2F0_imp<value_type>(
         static_cast<value_type>(a1),
         static_cast<value_type>(a2),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_2F0<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type hypergeometric_2F0(T1 a1, T2 a2, T3 z)
{
   return hypergeometric_2F0(a1, a2, z, policies::policy<>());
}


  } } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_HPP

/* hypergeometric_2F0.hpp
N/yYrl7OXzfz10T+lTwmITjuhL8XeO9p4lwrOlhbOO0VeFweau4Fp7DzKnksY0dwXLhLX+gJ3osfpN0tH60Qh7LM71dR/Uc8OELdfzS9wTyWm+dV0X6fgfr58az4Rvgqg19Ppgdcqu/vcPOiHtZjKP7Dv/PYw1z8pzkMn0T7BGaK39F1qf8Wd2bBqbH02S149bXGKU/+wysXjjROt4t3p6uXp9FzxYlBG+krC+GNPfpJ2GVpEt16g3xjfirMTwGdJnMOPePW4Fgxk/9fbVxb4OpnratCZ0p8Xj8n3Jsp3tWyr5lwbclW4/4WHPu5vJJCfxqKH+3Tj1ET/L6xo+utYc/5jl3Y/XnqXT/p58nV57AuHDxno/Up9MWumK9PbmZM8HvrC+Qb98wl8nETf/8n+H3q1erRZfzpd/Z+G3txn4qj3PcHfz9EfLnCdyDv6ZspxiPpaN1C1gMar+9wNX/YZ/wv5H/8p6UfndBzdN5I55kLh9WINyPhqOfZ0Vbj9j69pgJuvdV7XCAen218XqbT8P+WXP62uS09Iz44/zn6Hx7aIxq/U4Ljhvvwv+3i4YdwShd1xePEob6e37iWPwKfPIQfzZKvJqsT4yPJzp/fz9/h6TMuUi86Di+RL1K6yGcZxsn75+uraClTD9yJJzVYX296OBiPNXTIYeytJ5xjf4Fc9ZzabcH5RR/ps5xHz92PT80S98+TtyvkqfvloaidjDP+9hlo6qruewD/7taavu8+Pehc/r65BE/KUA83T9vpSxs2sJ/b44L32Knu+7x4ob+5xvpokWnsUX15VXf5CA4vhatTf+fP+s6Tx/P3TP6y0/po56uj34NXXCOPmLftcdYZ6txKXIdTisx7mXpyrnraoOD5eyygK+uLLlsSF1zH90abVtITrVPZlODvbgiOmexzJvtcNYU/qPfkvocvnYM/bcM/2c3mjuJ1JTzaBY8ZL77ZL2FqB/YI/2TJO5E/1MvpFWni7KBtEetP6QOeQzdtsD4OXpbr+7/sX/ndmXBqhrrfMnX5L8xvP/VGemt2dFyGO29kW3VpGPAD9WR4KfOlGPGMH75Ob/zdOC+lo+TDFT3xzMPgwX7m83w4MTc2OL+Wvp4ob/aiZ+8U/3LUCw6Y3xeieCnBev/WzbtEn+0N+r2ODAfP16Mt3UxcelL9YrC62iy61rf6ynvDC8vld+81t4v3Pdlz/AMv59NX6bjrust/o8Uj759XTlc+R33jTrxogPpOER1rFzyVqA9mHt7zkH44eGLxPLrMFrizGg5sqy4rbubcSWfIoV9bt6M8vY3+tuD9Z/6oj+Uk894OHoIjK+DIoiZ4/knfD7XS591dHWAc+4yu67NLHBhMN19HDzkC3m2rbqhPKK/RPFzBzt6GG/fib/vi2RG9Ilk/Ryr/eSvKZ/VfLOW/U8TvN+nU3i8Rv5k6Cx70787yacXVrfkpfjFJ3E9ilwXqtd63cCq/F0/LonXMEuMdhqtzvDd7WcUvF0X3kblF/n5FfmqvTtwb7sLzZt/sPb8y/x/CA+Ni7JtAzzuBvl4boperV5wvjohHtVP0L77mu7Av+cF3xrEIr6aDzdDv0SNMD7ze+D/ruVrUF7xnfAt+MZEffkY3OgMPGE3XXh2mbwXnl57PzjvKE33hj97G6QM6yg54tkbc/RuPv8n4mZfqBN9rnIcfpcMR39u34oC43qKfDL9IPoJfv6rvik5ed5R+9CJ1gWHwK72uQT/qupLg99sfct/1vjdohZfi4WUZ4n+tPuwhdAbzOTvPPDTBI9G6VKrvDuGNuvl07G+9Xxt28DFdbLrnw+cLxxlnz788Am9txg9j9MFcxN5GwQnqGBsuoCv2wZM=
*/