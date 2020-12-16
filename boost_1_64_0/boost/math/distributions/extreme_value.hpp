//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_EXTREME_VALUE_HPP
#define BOOST_STATS_EXTREME_VALUE_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/config/no_tr1/cmath.hpp>

//
// This is the maximum extreme value distribution, see
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366g.htm
// and http://mathworld.wolfram.com/ExtremeValueDistribution.html
// Also known as a Fisher-Tippett distribution, a log-Weibull
// distribution or a Gumbel distribution.

#include <utility>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

namespace boost{ namespace math{

namespace detail{
//
// Error check:
//
template <class RealType, class Policy>
inline bool verify_scale_b(const char* function, RealType b, RealType* presult, const Policy& pol)
{
   if((b <= 0) || !(boost::math::isfinite)(b))
   {
      *presult = policies::raise_domain_error<RealType>(
         function,
         "The scale parameter \"b\" must be finite and > 0, but was: %1%.", b, pol);
      return false;
   }
   return true;
}

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class extreme_value_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   extreme_value_distribution(RealType a = 0, RealType b = 1)
      : m_a(a), m_b(b)
   {
      RealType err;
      detail::verify_scale_b("boost::math::extreme_value_distribution<%1%>::extreme_value_distribution", b, &err, Policy());
      detail::check_finite("boost::math::extreme_value_distribution<%1%>::extreme_value_distribution", a, &err, Policy());
   } // extreme_value_distribution

   RealType location()const { return m_a; }
   RealType scale()const { return m_b; }

private:
   RealType m_a, m_b;
};

typedef extreme_value_distribution<double> extreme_value;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(
      std::numeric_limits<RealType>::has_infinity ? -std::numeric_limits<RealType>::infinity() : -max_value<RealType>(), 
      std::numeric_limits<RealType>::has_infinity ? std::numeric_limits<RealType>::infinity() : max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(-max_value<RealType>(),  max_value<RealType>());
}

template <class RealType, class Policy>
inline RealType pdf(const extreme_value_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::pdf(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if((boost::math::isinf)(x))
      return 0.0f;
   if(0 == detail::check_x(function, x, &result, Policy()))
      return result;
   RealType e = (a - x) / b;
   if(e < tools::log_max_value<RealType>())
      result = exp(e) * exp(-exp(e)) / b;
   // else.... result *must* be zero since exp(e) is infinite...
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const extreme_value_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)";

   if((boost::math::isinf)(x))
      return x < 0 ? 0.0f : 1.0f;
   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_x("boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)", x, &result, Policy()))
      return result;

   result = exp(-exp((a-x)/b));

   return result;
} // cdf

template <class RealType, class Policy>
RealType quantile(const extreme_value_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::quantile(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 0)
      return -policies::raise_overflow_error<RealType>(function, 0, Policy());
   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = a - log(-log(p)) * b;

   return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<extreme_value_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)";

   if((boost::math::isinf)(c.param))
      return c.param < 0 ? 1.0f : 0.0f;
   RealType a = c.dist.location();
   RealType b = c.dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_x(function, c.param, &result, Policy()))
      return result;

   result = -boost::math::expm1(-exp((a-c.param)/b), Policy());

   return result;
}

template <class RealType, class Policy>
RealType quantile(const complemented2_type<extreme_value_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::quantile(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = c.dist.location();
   RealType b = c.dist.scale();
   RealType q = c.param;
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, q, &result, Policy()))
      return result;

   if(q == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());
   if(q == 1)
      return -policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = a - log(-boost::math::log1p(-q, Policy())) * b;

   return result;
}

template <class RealType, class Policy>
inline RealType mean(const extreme_value_distribution<RealType, Policy>& dist)
{
   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b("boost::math::mean(const extreme_value_distribution<%1%>&)", b, &result, Policy()))
      return result;
   if (0 == detail::check_finite("boost::math::mean(const extreme_value_distribution<%1%>&)", a, &result, Policy()))
      return result;
   return a + constants::euler<RealType>() * b;
}

template <class RealType, class Policy>
inline RealType standard_deviation(const extreme_value_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING // for ADL of std functions.

   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b("boost::math::standard_deviation(const extreme_value_distribution<%1%>&)", b, &result, Policy()))
      return result;
   if(0 == detail::check_finite("boost::math::standard_deviation(const extreme_value_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;
   return constants::pi<RealType>() * b / sqrt(static_cast<RealType>(6));
}

template <class RealType, class Policy>
inline RealType mode(const extreme_value_distribution<RealType, Policy>& dist)
{
   return dist.location();
}

template <class RealType, class Policy>
inline RealType median(const extreme_value_distribution<RealType, Policy>& dist)
{
  using constants::ln_ln_two;
   return dist.location() - dist.scale() * ln_ln_two<RealType>();
}

template <class RealType, class Policy>
inline RealType skewness(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   //
   // This is 12 * sqrt(6) * zeta(3) / pi^3:
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   //
   return static_cast<RealType>(1.1395470994046486574927930193898461120875997958366L);
}

template <class RealType, class Policy>
inline RealType kurtosis(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   return RealType(27) / 5;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   return RealType(12) / 5;
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

#endif // BOOST_STATS_EXTREME_VALUE_HPP

/* extreme_value.hpp
71O46deD+SfHW6v0Owxy+Bvx2+DnSicdJeNph8PW8Ei4AyyAneEE2ANOhD1hEewPJ8MDZRxzOCyFx8Ap0A+nwjNkPPNiWA4Xwgooa+XK85bflHw518ptK+N2HWAK7AgzYSfYHnaGO0O8Gq/rBveFu8C+MBceJuNyYyX8GzhUPyN4DsrvNlfjwjgZL24BB8jvDoTbynhxO7i/1MsBcAQ8WNIt1Pc44kq6W+FHSrrJUp5WMAm2htvDdNgFZkh5toPdZFwyT8Yl+0u43rdQxr3j5Xf0fn8yH2QS/STu2MSIxhAD89zjiMg8+t8ZS8x+bNOOJ+Y9ZhpTNO2jt2WPLXaiP43Ez8bfiF937P93fHFz2P+zcXWTrf+/wTH3/wyx/9+Km0YMTICHc0Nb+ZDeL9u5/r9rbqnZdpG42tbugjRZK1C+mdaoc39i68N1gbThPZL47v22WXPP/B6pZVOd+20fFSi2TN8DrrRZ309/0ynbZ7hWnf/N2on/v8YH7VKfENvTU8nPd/iLeSB9mosXA5JprSL5bmuWcuPDLps89xxTeUel3kLmoW7Uaw/Kd7j+vtDlDXmHNK85t+nfLaN9h9xXvUOW904c3eehFj9sP33r03t8/HzWlvMOuaW8KzblvgY/Ba8juW/cKPZYG/E4tfZfDNwOJsNsuB3cHu4G28BecAjsDTvAwTAXDpd3tNGwE5wGB8Dj4UB4IsyDl8A+8FK4D7wM7g7vgj3FFm8PscXbCa6DXeEGeCCshgfBn+HB8HfJzx/yThdDufJhMzgYJsAh8LB/qS0Waws22TtUmDUDG22XFVwXsKp2LcCI36fM71J6nb8mt9FKvq9x71Ks2fe33qf6zvj/vj95znOe85znPLclus32/d9E6/9/7pj//5qM6/8g63x/jx+RzXfi/fr7v19lYKp7DwC+60PH8q97wJbfyjxGe7/xe17Pf/1Ina+2FvH/WrzMgZN4qTotHWb+3tfzDD9TMp9ZC/j1NVaMUW+g09Fjt8cUzaz5BNe6ikxVphWM+bTi2+Vk5ziuzuM3Kp0PVdkWZ6t5f2WkpPUJsSqNddZsWmuezKvPIOREFR7j1kPo8eHz1Pkct7x7zwM9Tn6YOj+Sb6Z4wg5OWUbY0hi+hShw0laj9PzQ6mSLVIakBGVe0jJ96siki8xvQRlfh6SEZlZYuVz60sZc5OL9SQkJtXJdU0J/Mz8olzjnVbdMG47jOf6C8ydvW/MB2Rzaezecum0k8x7Rqbj0JwkG/UmSQX/SUmQ/r5ENmQO7QAYAO/v4TdhR9GQ5D+rrpPYaiVBPRtywerLd1blkZpPHMku6mUlPRnzjdaWvyW7qfIK2R4hT3+ytTNcDaYW/rlLlOr1ZyZzG2Mm+Rt2apOHu03rtgr7qfHPfXlZzNcP4FXywf8+qORdyjfEbav0C0z4fafB1FaejXhfRUuUbwHEbRx4YLnesyfepipOBDMc6Tn/mhbXVaxZemqH0fFrnRz/UfXAa3qnvi2tgDm73hzadvo+4qn6kv6o9SZar8jE/u3PoOHbf5nXnqV+ZwxoONXreimMKas0EsFhQ9Xd5jlqP45iwa7xqPa++H9Qz/p1zgHPuOWmTZ5W2yuc+ks/ehvn0y/K4lxny6Z/qL5hcXlSEiNx/688vaeg+vmeqLWvHnlxZNtFszyDyjvtY5OUjL7p86dLG/CZh+je1vnZdPWP+5j1RwutrzXvAbHo97jSlx13dukO3n/2V/vnDM/Y41Prw1C1Hj2veWyWcfjf83jwZLe3wa+5Y+MgLT0376bjU5Wk7Jfx4cNPpg5tqL5lNrSf+wTFHl2e9Gmd6w6feI/Tf36g2kncxeQddiW+Lj5N528M=
*/