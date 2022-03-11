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
#include <boost/config/no_tr1/cmath.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

#include <utility>

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

#ifdef BOOST_MSVC
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