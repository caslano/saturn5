//  Copyright Thijs van den Berg, 2008.
//  Copyright John Maddock 2008.
//  Copyright Paul A. Bristow 2008, 2014.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This module implements the Laplace distribution.
// Weisstein, Eric W. "Laplace Distribution." From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/LaplaceDistribution.html
// http://en.wikipedia.org/wiki/Laplace_distribution
//
// Abramowitz and Stegun 1972, p 930
// http://www.math.sfu.ca/~cbm/aands/page_930.htm

#ifndef BOOST_STATS_LAPLACE_HPP
#define BOOST_STATS_LAPLACE_HPP

#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/constants/constants.hpp>
#include <limits>

namespace boost{ namespace math{

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable:4127) // conditional expression is constant
#endif

template <class RealType = double, class Policy = policies::policy<> >
class laplace_distribution
{
public:
   // ----------------------------------
   // public Types
   // ----------------------------------
   typedef RealType value_type;
   typedef Policy policy_type;

   // ----------------------------------
   // Constructor(s)
   // ----------------------------------
   laplace_distribution(RealType l_location = 0, RealType l_scale = 1)
      : m_location(l_location), m_scale(l_scale)
   {
      RealType result;
      check_parameters("boost::math::laplace_distribution<%1%>::laplace_distribution()", &result);
   }


   // ----------------------------------
   // Public functions
   // ----------------------------------

   RealType location() const
   {
      return m_location;
   }

   RealType scale() const
   {
      return m_scale;
   }

   bool check_parameters(const char* function, RealType* result) const
   {
         if(false == detail::check_scale(function, m_scale, result, Policy())) return false;
         if(false == detail::check_location(function, m_location, result, Policy())) return false;
         return true;
   }

private:
   RealType m_location;
   RealType m_scale;
}; // class laplace_distribution

//
// Convenient type synonym for double.
typedef laplace_distribution<double> laplace;

#ifdef __cpp_deduction_guides
template <class RealType>
laplace_distribution(RealType)->laplace_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
laplace_distribution(RealType,RealType)->laplace_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

//
// Non-member functions.
template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const laplace_distribution<RealType, Policy>&)
{
   if (std::numeric_limits<RealType>::has_infinity)
  {  // Can use infinity.
     return std::pair<RealType, RealType>(-std::numeric_limits<RealType>::infinity(), std::numeric_limits<RealType>::infinity()); // - to + infinity.
  }
  else
  { // Can only use max_value.
    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + max value.
  }

}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const laplace_distribution<RealType, Policy>&)
{
  if (std::numeric_limits<RealType>::has_infinity)
  { // Can Use infinity.
     return std::pair<RealType, RealType>(-std::numeric_limits<RealType>::infinity(), std::numeric_limits<RealType>::infinity()); // - to + infinity.
  }
  else
  { // Can only use max_value.
    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + max value.
  }
}

template <class RealType, class Policy>
inline RealType pdf(const laplace_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   // Checking function argument
   RealType result = 0;
   const char* function = "boost::math::pdf(const laplace_distribution<%1%>&, %1%))";

   // Check scale and location.
   if (false == dist.check_parameters(function, &result)) return result;
   // Special pdf values.
   if((boost::math::isinf)(x))
   {
      return 0; // pdf + and - infinity is zero.
   }
   if (false == detail::check_x(function, x, &result, Policy())) return result;

   // General case
   RealType scale( dist.scale() );
   RealType location( dist.location() );

   RealType exponent = x - location;
   if (exponent>0) exponent = -exponent;
   exponent /= scale;

   result = exp(exponent);
   result /= 2 * scale;

   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const laplace_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // For ADL of std functions.

   RealType result = 0;
   // Checking function argument.
   const char* function = "boost::math::cdf(const laplace_distribution<%1%>&, %1%)";
   // Check scale and location.
   if (false == dist.check_parameters(function, &result)) return result;

   // Special cdf values:
   if((boost::math::isinf)(x))
   {
     if(x < 0) return 0; // -infinity.
     return 1; // + infinity.
   }
   if (false == detail::check_x(function, x, &result, Policy())) return result;

   // General cdf  values
   RealType scale( dist.scale() );
   RealType location( dist.location() );

   if (x < location)
   {
      result = exp( (x-location)/scale )/2;
   }
   else
   {
      result = 1 - exp( (location-x)/scale )/2;
   }
   return result;
} // cdf


template <class RealType, class Policy>
inline RealType quantile(const laplace_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING // for ADL of std functions.

   // Checking function argument
   RealType result = 0;
   const char* function = "boost::math::quantile(const laplace_distribution<%1%>&, %1%)";
   if (false == dist.check_parameters(function, &result)) return result;
   if(false == detail::check_probability(function, p, &result, Policy())) return result;

   // Extreme values of p:
   if(p == 0)
   {
      result = policies::raise_overflow_error<RealType>(function,
        "probability parameter is 0, but must be > 0!", Policy());
      return -result; // -std::numeric_limits<RealType>::infinity();
   }
  
   if(p == 1)
   {
      result = policies::raise_overflow_error<RealType>(function,
        "probability parameter is 1, but must be < 1!", Policy());
      return result; // std::numeric_limits<RealType>::infinity();
   }
   // Calculate Quantile
   RealType scale( dist.scale() );
   RealType location( dist.location() );

   if (p - 0.5 < 0.0)
      result = location + scale*log( static_cast<RealType>(p*2) );
   else
      result = location - scale*log( static_cast<RealType>(-p*2 + 2) );

   return result;
} // quantile


template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<laplace_distribution<RealType, Policy>, RealType>& c)
{
   // Calculate complement of cdf.
   BOOST_MATH_STD_USING // for ADL of std functions

   RealType scale = c.dist.scale();
   RealType location = c.dist.location();
   RealType x = c.param;
   RealType result = 0;

   // Checking function argument.
   const char* function = "boost::math::cdf(const complemented2_type<laplace_distribution<%1%>, %1%>&)";

   // Check scale and location.
   //if(false == detail::check_scale(function, scale, result, Policy())) return false;
   //if(false == detail::check_location(function, location, result, Policy())) return false;
    if (false == c.dist.check_parameters(function, &result)) return result;

   // Special cdf values.
   if((boost::math::isinf)(x))
   {
     if(x < 0) return 1; // cdf complement -infinity is unity.
     return 0; // cdf complement +infinity is zero.
   }
   if(false == detail::check_x(function, x, &result, Policy()))return result;

   // Cdf interval value.
   if (-x < -location)
   {
      result = exp( (-x+location)/scale )/2;
   }
   else
   {
      result = 1 - exp( (-location+x)/scale )/2;
   }
   return result;
} // cdf complement


template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<laplace_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions.

   // Calculate quantile.
   RealType scale = c.dist.scale();
   RealType location = c.dist.location();
   RealType q = c.param;
   RealType result = 0;

   // Checking function argument.
   const char* function = "quantile(const complemented2_type<laplace_distribution<%1%>, %1%>&)";
   if (false == c.dist.check_parameters(function, &result)) return result;
   
   // Extreme values.
   if(q == 0)
   {
       return std::numeric_limits<RealType>::infinity();
   }
   if(q == 1)
   {
       return -std::numeric_limits<RealType>::infinity();
   }
   if(false == detail::check_probability(function, q, &result, Policy())) return result;

   if (0.5 - q < 0.0)
      result = location + scale*log( static_cast<RealType>(-q*2 + 2) );
   else
      result = location - scale*log( static_cast<RealType>(q*2) );


   return result;
} // quantile

template <class RealType, class Policy>
inline RealType mean(const laplace_distribution<RealType, Policy>& dist)
{
   return dist.location();
}

template <class RealType, class Policy>
inline RealType standard_deviation(const laplace_distribution<RealType, Policy>& dist)
{
   return constants::root_two<RealType>() * dist.scale();
}

template <class RealType, class Policy>
inline RealType mode(const laplace_distribution<RealType, Policy>& dist)
{
   return dist.location();
}

template <class RealType, class Policy>
inline RealType median(const laplace_distribution<RealType, Policy>& dist)
{
   return dist.location();
}

template <class RealType, class Policy>
inline RealType skewness(const laplace_distribution<RealType, Policy>& /*dist*/)
{
   return 0;
}

template <class RealType, class Policy>
inline RealType kurtosis(const laplace_distribution<RealType, Policy>& /*dist*/)
{
   return 6;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const laplace_distribution<RealType, Policy>& /*dist*/)
{
   return 3;
}

template <class RealType, class Policy>
inline RealType entropy(const laplace_distribution<RealType, Policy> & dist)
{
   using std::log;
   return log(2*dist.scale()*constants::e<RealType>());
}

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_LAPLACE_HPP



/* laplace.hpp
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
*/