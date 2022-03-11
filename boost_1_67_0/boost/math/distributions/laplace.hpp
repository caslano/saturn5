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

#ifdef BOOST_MSVC
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

#ifdef BOOST_MSVC
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