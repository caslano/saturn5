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
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
*/