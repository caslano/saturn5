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

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

#include <utility>
#include <cmath>

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

#ifdef __cpp_deduction_guides
template <class RealType>
exponential_distribution(RealType)->exponential_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

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

#ifdef _MSC_VER
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