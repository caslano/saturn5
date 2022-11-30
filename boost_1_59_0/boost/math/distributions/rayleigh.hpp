//  Copyright Paul A. Bristow 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_rayleigh_HPP
#define BOOST_STATS_rayleigh_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

#include <utility>
#include <cmath>

namespace boost{ namespace math{

namespace detail
{ // Error checks:
  template <class RealType, class Policy>
  inline bool verify_sigma(const char* function, RealType sigma, RealType* presult, const Policy& pol)
  {
     if((sigma <= 0) || (!(boost::math::isfinite)(sigma)))
     {
        *presult = policies::raise_domain_error<RealType>(
           function,
           "The scale parameter \"sigma\" must be > 0 and finite, but was: %1%.", sigma, pol);
        return false;
     }
     return true;
  } // bool verify_sigma

  template <class RealType, class Policy>
  inline bool verify_rayleigh_x(const char* function, RealType x, RealType* presult, const Policy& pol)
  {
     if((x < 0) || (boost::math::isnan)(x))
     {
        *presult = policies::raise_domain_error<RealType>(
           function,
           "The random variable must be >= 0, but was: %1%.", x, pol);
        return false;
     }
     return true;
  } // bool verify_rayleigh_x
} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class rayleigh_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   rayleigh_distribution(RealType l_sigma = 1)
      : m_sigma(l_sigma)
   {
      RealType err;
      detail::verify_sigma("boost::math::rayleigh_distribution<%1%>::rayleigh_distribution", l_sigma, &err, Policy());
   } // rayleigh_distribution

   RealType sigma()const
   { // Accessor.
     return m_sigma;
   }

private:
   RealType m_sigma;
}; // class rayleigh_distribution

typedef rayleigh_distribution<double> rayleigh;

#ifdef __cpp_deduction_guides
template <class RealType>
rayleigh_distribution(RealType)->rayleigh_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const rayleigh_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), std::numeric_limits<RealType>::has_infinity ? std::numeric_limits<RealType>::infinity() : max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const rayleigh_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>());
}

template <class RealType, class Policy>
inline RealType pdf(const rayleigh_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std function exp.

   RealType sigma = dist.sigma();
   RealType result = 0;
   static const char* function = "boost::math::pdf(const rayleigh_distribution<%1%>&, %1%)";
   if(false == detail::verify_sigma(function, sigma, &result, Policy()))
   {
      return result;
   }
   if(false == detail::verify_rayleigh_x(function, x, &result, Policy()))
   {
      return result;
   }
   if((boost::math::isinf)(x))
   {
      return 0;
   }
   RealType sigmasqr = sigma * sigma;
   result = x * (exp(-(x * x) / ( 2 * sigmasqr))) / sigmasqr;
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const rayleigh_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   RealType result = 0;
   RealType sigma = dist.sigma();
   static const char* function = "boost::math::cdf(const rayleigh_distribution<%1%>&, %1%)";
   if(false == detail::verify_sigma(function, sigma, &result, Policy()))
   {
      return result;
   }
   if(false == detail::verify_rayleigh_x(function, x, &result, Policy()))
   {
      return result;
   }
   result = -boost::math::expm1(-x * x / ( 2 * sigma * sigma), Policy());
   return result;
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const rayleigh_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   RealType result = 0;
   RealType sigma = dist.sigma();
   static const char* function = "boost::math::quantile(const rayleigh_distribution<%1%>&, %1%)";
   if(false == detail::verify_sigma(function, sigma, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 0)
   {
      return 0;
   }
   if(p == 1)
   {
     return policies::raise_overflow_error<RealType>(function, 0, Policy());
   }
   result = sqrt(-2 * sigma * sigma * boost::math::log1p(-p, Policy()));
   return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<rayleigh_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   RealType result = 0;
   RealType sigma = c.dist.sigma();
   static const char* function = "boost::math::cdf(const rayleigh_distribution<%1%>&, %1%)";
   if(false == detail::verify_sigma(function, sigma, &result, Policy()))
   {
      return result;
   }
   RealType x = c.param;
   if(false == detail::verify_rayleigh_x(function, x, &result, Policy()))
   {
      return result;
   }
   RealType ea = x * x / (2 * sigma * sigma);
   // Fix for VC11/12 x64 bug in exp(float):
   if (ea >= tools::max_value<RealType>())
      return 0;
   result =  exp(-ea);
   return result;
} // cdf complement

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<rayleigh_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions, log & sqrt.

   RealType result = 0;
   RealType sigma = c.dist.sigma();
   static const char* function = "boost::math::quantile(const rayleigh_distribution<%1%>&, %1%)";
   if(false == detail::verify_sigma(function, sigma, &result, Policy()))
   {
      return result;
   }
   RealType q = c.param;
   if(false == detail::check_probability(function, q, &result, Policy()))
   {
      return result;
   }
   if(q == 1)
   {
      return 0;
   }
   if(q == 0)
   {
     return policies::raise_overflow_error<RealType>(function, 0, Policy());
   }
   result = sqrt(-2 * sigma * sigma * log(q));
   return result;
} // quantile complement

template <class RealType, class Policy>
inline RealType mean(const rayleigh_distribution<RealType, Policy>& dist)
{
   RealType result = 0;
   RealType sigma = dist.sigma();
   static const char* function = "boost::math::mean(const rayleigh_distribution<%1%>&, %1%)";
   if(false == detail::verify_sigma(function, sigma, &result, Policy()))
   {
      return result;
   }
   using boost::math::constants::root_half_pi;
   return sigma * root_half_pi<RealType>();
} // mean

template <class RealType, class Policy>
inline RealType variance(const rayleigh_distribution<RealType, Policy>& dist)
{
   RealType result = 0;
   RealType sigma = dist.sigma();
   static const char* function = "boost::math::variance(const rayleigh_distribution<%1%>&, %1%)";
   if(false == detail::verify_sigma(function, sigma, &result, Policy()))
   {
      return result;
   }
   using boost::math::constants::four_minus_pi;
   return four_minus_pi<RealType>() * sigma * sigma / 2;
} // variance

template <class RealType, class Policy>
inline RealType mode(const rayleigh_distribution<RealType, Policy>& dist)
{
   return dist.sigma();
}

template <class RealType, class Policy>
inline RealType median(const rayleigh_distribution<RealType, Policy>& dist)
{
   using boost::math::constants::root_ln_four;
   return root_ln_four<RealType>() * dist.sigma();
}

template <class RealType, class Policy>
inline RealType skewness(const rayleigh_distribution<RealType, Policy>& /*dist*/)
{
  // using namespace boost::math::constants;
  return static_cast<RealType>(0.63111065781893713819189935154422777984404221106391L);
  // Computed using NTL at 150 bit, about 50 decimal digits.
  // return 2 * root_pi<RealType>() * pi_minus_three<RealType>() / pow23_four_minus_pi<RealType>();
}

template <class RealType, class Policy>
inline RealType kurtosis(const rayleigh_distribution<RealType, Policy>& /*dist*/)
{
  // using namespace boost::math::constants;
  return static_cast<RealType>(3.2450893006876380628486604106197544154170667057995L);
  // Computed using NTL at 150 bit, about 50 decimal digits.
  // return 3 - (6 * pi<RealType>() * pi<RealType>() - 24 * pi<RealType>() + 16) /
  // (four_minus_pi<RealType>() * four_minus_pi<RealType>());
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const rayleigh_distribution<RealType, Policy>& /*dist*/)
{
  //using namespace boost::math::constants;
  // Computed using NTL at 150 bit, about 50 decimal digits.
  return static_cast<RealType>(0.2450893006876380628486604106197544154170667057995L);
  // return -(6 * pi<RealType>() * pi<RealType>() - 24 * pi<RealType>() + 16) /
  //   (four_minus_pi<RealType>() * four_minus_pi<RealType>());
} // kurtosis

template <class RealType, class Policy>
inline RealType entropy(const rayleigh_distribution<RealType, Policy>& dist)
{
   using std::log;
   return 1 + log(dist.sigma()*constants::one_div_root_two<RealType>()) + constants::euler<RealType>()/2;
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

#endif // BOOST_STATS_rayleigh_HPP

/* rayleigh.hpp
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
*/