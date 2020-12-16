//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_EXPONENTIAL_HPP
#define BOOST_STATS_EXPONENTIAL_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/config/no_tr1/cmath.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

#include <utility>

namespace boost{ namespace math{

namespace detail{
//
// Error check:
//
template <class RealType, class Policy>
inline bool verify_lambda(const char* function, RealType l, RealType* presult, const Policy& pol)
{
   if((l <= 0) || !(boost::math::isfinite)(l))
   {
      *presult = policies::raise_domain_error<RealType>(
         function,
         "The scale parameter \"lambda\" must be > 0, but was: %1%.", l, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool verify_exp_x(const char* function, RealType x, RealType* presult, const Policy& pol)
{
   if((x < 0) || (boost::math::isnan)(x))
   {
      *presult = policies::raise_domain_error<RealType>(
         function,
         "The random variable must be >= 0, but was: %1%.", x, pol);
      return false;
   }
   return true;
}

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class exponential_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   exponential_distribution(RealType l_lambda = 1)
      : m_lambda(l_lambda)
   {
      RealType err;
      detail::verify_lambda("boost::math::exponential_distribution<%1%>::exponential_distribution", l_lambda, &err, Policy());
   } // exponential_distribution

   RealType lambda()const { return m_lambda; }

private:
   RealType m_lambda;
};

typedef exponential_distribution<double> exponential;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const exponential_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
  if (std::numeric_limits<RealType>::has_infinity)
  { 
    return std::pair<RealType, RealType>(static_cast<RealType>(0), std::numeric_limits<RealType>::infinity()); // 0 to + infinity.
  }
  else
  {
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // 0 to + max
  }
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const exponential_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   using boost::math::tools::min_value;
   return std::pair<RealType, RealType>(min_value<RealType>(),  max_value<RealType>());
   // min_value<RealType>() to avoid a discontinuity at x = 0.
}

template <class RealType, class Policy>
inline RealType pdf(const exponential_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::pdf(const exponential_distribution<%1%>&, %1%)";

   RealType lambda = dist.lambda();
   RealType result = 0;
   if(0 == detail::verify_lambda(function, lambda, &result, Policy()))
      return result;
   if(0 == detail::verify_exp_x(function, x, &result, Policy()))
      return result;
   // Workaround for VC11/12 bug:
   if ((boost::math::isinf)(x))
      return 0;
   result = lambda * exp(-lambda * x);
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const exponential_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::cdf(const exponential_distribution<%1%>&, %1%)";

   RealType result = 0;
   RealType lambda = dist.lambda();
   if(0 == detail::verify_lambda(function, lambda, &result, Policy()))
      return result;
   if(0 == detail::verify_exp_x(function, x, &result, Policy()))
      return result;
   result = -boost::math::expm1(-x * lambda, Policy());

   return result;
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const exponential_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::quantile(const exponential_distribution<%1%>&, %1%)";

   RealType result = 0;
   RealType lambda = dist.lambda();
   if(0 == detail::verify_lambda(function, lambda, &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 0)
      return 0;
   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = -boost::math::log1p(-p, Policy()) / lambda;
   return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<exponential_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::cdf(const exponential_distribution<%1%>&, %1%)";

   RealType result = 0;
   RealType lambda = c.dist.lambda();
   if(0 == detail::verify_lambda(function, lambda, &result, Policy()))
      return result;
   if(0 == detail::verify_exp_x(function, c.param, &result, Policy()))
      return result;
   // Workaround for VC11/12 bug:
   if (c.param >= tools::max_value<RealType>())
      return 0;
   result = exp(-c.param * lambda);

   return result;
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<exponential_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::quantile(const exponential_distribution<%1%>&, %1%)";

   RealType result = 0;
   RealType lambda = c.dist.lambda();
   if(0 == detail::verify_lambda(function, lambda, &result, Policy()))
      return result;

   RealType q = c.param;
   if(0 == detail::check_probability(function, q, &result, Policy()))
      return result;

   if(q == 1)
      return 0;
   if(q == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = -log(q) / lambda;
   return result;
}

template <class RealType, class Policy>
inline RealType mean(const exponential_distribution<RealType, Policy>& dist)
{
   RealType result = 0;
   RealType lambda = dist.lambda();
   if(0 == detail::verify_lambda("boost::math::mean(const exponential_distribution<%1%>&)", lambda, &result, Policy()))
      return result;
   return 1 / lambda;
}

template <class RealType, class Policy>
inline RealType standard_deviation(const exponential_distribution<RealType, Policy>& dist)
{
   RealType result = 0;
   RealType lambda = dist.lambda();
   if(0 == detail::verify_lambda("boost::math::standard_deviation(const exponential_distribution<%1%>&)", lambda, &result, Policy()))
      return result;
   return 1 / lambda;
}

template <class RealType, class Policy>
inline RealType mode(const exponential_distribution<RealType, Policy>& /*dist*/)
{
   return 0;
}

template <class RealType, class Policy>
inline RealType median(const exponential_distribution<RealType, Policy>& dist)
{
   using boost::math::constants::ln_two;
   return ln_two<RealType>() / dist.lambda(); // ln(2) / lambda
}

template <class RealType, class Policy>
inline RealType skewness(const exponential_distribution<RealType, Policy>& /*dist*/)
{
   return 2;
}

template <class RealType, class Policy>
inline RealType kurtosis(const exponential_distribution<RealType, Policy>& /*dist*/)
{
   return 9;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const exponential_distribution<RealType, Policy>& /*dist*/)
{
   return 6;
}

template <class RealType, class Policy>
inline RealType entropy(const exponential_distribution<RealType, Policy>& dist)
{
   using std::log;
   return 1 - log(dist.lambda());
}

} // namespace math
} // namespace boost

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_EXPONENTIAL_HPP

/* exponential.hpp
8rUO5A51/KFVis7mWr6s00Vnc4wKH+pLRacSR5uH6GikrPPV72yt035DxYnT38xXqvy1i2nlK7UW+rKtT3ztVP1vpP5vVedSY2rrkT5DTabL9/4wlVaZbxI6lk+sMtED+aQfve2bh0ZlJ2rrSGrpMejS8eg8XqDkk3Xfma3SzZU6DLbNe5S+i902Wq93ec0179AdTS4prwjoso6y45FKap366uxrKTrM+1Qa8UZ90VNK/jR+daD0E+ljXGNKX0ReunDP3Ur0Rbe3d+mLDLqizAa+90ev2rS6ouDz86UEveao5jAurKGrg7qixj0/ie/WDxnvwSKnn1nvR7C+YCT6D+dzaGOLmsg/iz7sJyljoS5jvc8h/Tw4Xsm/YvWjlp7DG8pNmuH1YkXq3LdKL3Yk/nN8lq0j0vEesXbm14fgr3DpxjgfVt9VrM5tVPquwyn5J/gdDfouKV+twstxn05eE17ntVqlf5rWeT2gji/Gz6+j82op5TlHyazVNoxrUqLXeQ1bE53OK6jfKv2X67feUPqtLjkznu+65wElOx/UNavrbnP9nn5rS9Rv9Q2+l8s3yAy5h+4unfka0ZNcC7PgYtgWXid2hjeIvmWdT94P5T15BuyFX2UHiH4syT4n9of94Ag4EI6Bg2AB3A8eBfNhGRwMK0Q/dhw8CJ4Nh8CL4FC4VI7vhjPhvXAsfBAWwkfgJPgULIYvwhL4MjwafgSPgRtgKfwc+uEXcBr8AU6HP8FjYUsf5YMd4EzYEZ4Ad4Inwl3gSbAnPBn2FT3awXAuHAbPhBPhWbBU5GfCc+BJ8Fx4OjwPXiN6umWip7sHzobL4anwVXgJ/AougDHU/6UwAS6ESaI3S4bzYTa8CLaX8zvCcrg3rIB9YEDatZN+xtEvpH/E4LOlf1yBnM0rg/0geK+HP4t8Bn5VA3q33R16txyYJfq2bLg3bAv7wRzpL+3hONgDTpD4E2Eu9MMdYBXcUfSnneANsIv0l67wA9gNfibpVEs638Hd4E9yPNDTx3n6uEbo425EF7cWvxGfPP3/p5fznOc85znPec5znvOc5zznuaZ2m8P+v2i6v8D+oyns/9vLvn7FY21dip2qbVxQMHViQG/Tp+wEPs5FHyZjAJbssXaZjAEsxG+DAi55pRoDUPrxkYezidJRRYFgakWBmjkLwXUDDxB9fnC8Kk3FzTavFbjSsY8WAT7HuGgK7KPOJxvHRJxxc1TcSeMD4832AyLr2M98yvgZBWpYzTQGjXz9axNsp86f6xxn0Hk+VJ1rTXoc89dx6rgTuqZYld6debb8+MAUf62dRKaSuQCZMSnNOH6TwAdJ7AH8HDI0OSWS9QyapcxZqccC9PoGB7jWN6CeOVb1rMfCcuwwqb9051iY1JN7b7ElYiBxpNiTjMU/hZJrvaGf1NdHUqU+P1LxRmORkGneX97c1ub95cO3tXmP+QbaOuER+2xG2LH7eHU+VZXr81ZqnQrdrr+rtNtpe2bak3aNbn0Kd/u52yrJ3Fb6mg7IXnmj8S3wI/ApXNOFj7jaqiL8NZ2v20u3icTXa4DKXnj6Gja1DXEiv2a1rG7HMNerS7aNKjWFEFnbrsMOX6qvu5rwDYQHx1PX5NYZbw67X1t+aHvA+q4n19iylIEwlS/yShh5lTA7T+STMDufrn1BxU5ogFxz/fFruxFuasfwbWi6vkgj8utrnbFdDG3oku1V0y4yBs/1AV9T5/dCj+7TY6B9keuH749/plXDtlnGdjG0QZKrDZx7iw5MCLO3qNhgOR+eJYHI93mtGuvaW1TGVQ9rwvVjoh1vjXY9mMSffYS/+sR+7706Z9en+5Vfnz215L5b/7lx2GjXfTE=
*/