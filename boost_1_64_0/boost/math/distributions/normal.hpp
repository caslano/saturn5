//  Copyright John Maddock 2006, 2007.
//  Copyright Paul A. Bristow 2006, 2007.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_NORMAL_HPP
#define BOOST_STATS_NORMAL_HPP

// http://en.wikipedia.org/wiki/Normal_distribution
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3661.htm
// Also:
// Weisstein, Eric W. "Normal Distribution."
// From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/NormalDistribution.html

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/erf.hpp> // for erf/erfc.
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>

#include <utility>

namespace boost{ namespace math{

template <class RealType = double, class Policy = policies::policy<> >
class normal_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   normal_distribution(RealType l_mean = 0, RealType sd = 1)
      : m_mean(l_mean), m_sd(sd)
   { // Default is a 'standard' normal distribution N01.
     static const char* function = "boost::math::normal_distribution<%1%>::normal_distribution";

     RealType result;
     detail::check_scale(function, sd, &result, Policy());
     detail::check_location(function, l_mean, &result, Policy());
   }

   RealType mean()const
   { // alias for location.
      return m_mean;
   }

   RealType standard_deviation()const
   { // alias for scale.
      return m_sd;
   }

   // Synonyms, provided to allow generic use of find_location and find_scale.
   RealType location()const
   { // location.
      return m_mean;
   }
   RealType scale()const
   { // scale.
      return m_sd;
   }

private:
   //
   // Data members:
   //
   RealType m_mean;  // distribution mean or location.
   RealType m_sd;    // distribution standard deviation or scale.
}; // class normal_distribution

typedef normal_distribution<double> normal;

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const normal_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
  if (std::numeric_limits<RealType>::has_infinity)
  { 
     return std::pair<RealType, RealType>(-std::numeric_limits<RealType>::infinity(), std::numeric_limits<RealType>::infinity()); // - to + infinity.
  }
  else
  { // Can only use max_value.
    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + max value.
  }
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const normal_distribution<RealType, Policy>& /*dist*/)
{ // This is range values for random variable x where cdf rises from 0 to 1, and outside it, the pdf is zero.
  if (std::numeric_limits<RealType>::has_infinity)
  { 
     return std::pair<RealType, RealType>(-std::numeric_limits<RealType>::infinity(), std::numeric_limits<RealType>::infinity()); // - to + infinity.
  }
  else
  { // Can only use max_value.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(-max_value<RealType>(),  max_value<RealType>()); // - to + max value.
  }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class RealType, class Policy>
inline RealType pdf(const normal_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = dist.standard_deviation();
   RealType mean = dist.mean();

   static const char* function = "boost::math::pdf(const normal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_location(function, mean, &result, Policy()))
   {
      return result;
   }
   if((boost::math::isinf)(x))
   {
     return 0; // pdf + and - infinity is zero.
   }
   // Below produces MSVC 4127 warnings, so the above used instead.
   //if(std::numeric_limits<RealType>::has_infinity && abs(x) == std::numeric_limits<RealType>::infinity())
   //{ // pdf + and - infinity is zero.
   //  return 0;
   //}
   if(false == detail::check_x(function, x, &result, Policy()))
   {
      return result;
   }

   RealType exponent = x - mean;
   exponent *= -exponent;
   exponent /= 2 * sd * sd;

   result = exp(exponent);
   result /= sd * sqrt(2 * constants::pi<RealType>());

   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const normal_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = dist.standard_deviation();
   RealType mean = dist.mean();
   static const char* function = "boost::math::cdf(const normal_distribution<%1%>&, %1%)";
   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_location(function, mean, &result, Policy()))
   {
      return result;
   }
   if((boost::math::isinf)(x))
   {
     if(x < 0) return 0; // -infinity
     return 1; // + infinity
   }
   // These produce MSVC 4127 warnings, so the above used instead.
   //if(std::numeric_limits<RealType>::has_infinity && x == std::numeric_limits<RealType>::infinity())
   //{ // cdf +infinity is unity.
   //  return 1;
   //}
   //if(std::numeric_limits<RealType>::has_infinity && x == -std::numeric_limits<RealType>::infinity())
   //{ // cdf -infinity is zero.
   //  return 0;
   //}
   if(false == detail::check_x(function, x, &result, Policy()))
   {
     return result;
   }
   RealType diff = (x - mean) / (sd * constants::root_two<RealType>());
   result = boost::math::erfc(-diff, Policy()) / 2;
   return result;
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const normal_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = dist.standard_deviation();
   RealType mean = dist.mean();
   static const char* function = "boost::math::quantile(const normal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, p, &result, Policy()))
      return result;

   result= boost::math::erfc_inv(2 * p, Policy());
   result = -result;
   result *= sd * constants::root_two<RealType>();
   result += mean;
   return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<normal_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = c.dist.standard_deviation();
   RealType mean = c.dist.mean();
   RealType x = c.param;
   static const char* function = "boost::math::cdf(const complement(normal_distribution<%1%>&), %1%)";

   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   if((boost::math::isinf)(x))
   {
     if(x < 0) return 1; // cdf complement -infinity is unity.
     return 0; // cdf complement +infinity is zero
   }
   // These produce MSVC 4127 warnings, so the above used instead.
   //if(std::numeric_limits<RealType>::has_infinity && x == std::numeric_limits<RealType>::infinity())
   //{ // cdf complement +infinity is zero.
   //  return 0;
   //}
   //if(std::numeric_limits<RealType>::has_infinity && x == -std::numeric_limits<RealType>::infinity())
   //{ // cdf complement -infinity is unity.
   //  return 1;
   //}
   if(false == detail::check_x(function, x, &result, Policy()))
      return result;

   RealType diff = (x - mean) / (sd * constants::root_two<RealType>());
   result = boost::math::erfc(diff, Policy()) / 2;
   return result;
} // cdf complement

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<normal_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = c.dist.standard_deviation();
   RealType mean = c.dist.mean();
   static const char* function = "boost::math::quantile(const complement(normal_distribution<%1%>&), %1%)";
   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   RealType q = c.param;
   if(false == detail::check_probability(function, q, &result, Policy()))
      return result;
   result = boost::math::erfc_inv(2 * q, Policy());
   result *= sd * constants::root_two<RealType>();
   result += mean;
   return result;
} // quantile

template <class RealType, class Policy>
inline RealType mean(const normal_distribution<RealType, Policy>& dist)
{
   return dist.mean();
}

template <class RealType, class Policy>
inline RealType standard_deviation(const normal_distribution<RealType, Policy>& dist)
{
   return dist.standard_deviation();
}

template <class RealType, class Policy>
inline RealType mode(const normal_distribution<RealType, Policy>& dist)
{
   return dist.mean();
}

template <class RealType, class Policy>
inline RealType median(const normal_distribution<RealType, Policy>& dist)
{
   return dist.mean();
}

template <class RealType, class Policy>
inline RealType skewness(const normal_distribution<RealType, Policy>& /*dist*/)
{
   return 0;
}

template <class RealType, class Policy>
inline RealType kurtosis(const normal_distribution<RealType, Policy>& /*dist*/)
{
   return 3;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const normal_distribution<RealType, Policy>& /*dist*/)
{
   return 0;
}

template <class RealType, class Policy>
inline RealType entropy(const normal_distribution<RealType, Policy> & dist)
{
   using std::log;
   RealType arg = constants::two_pi<RealType>()*constants::e<RealType>()*dist.standard_deviation()*dist.standard_deviation();
   return log(arg)/2;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_NORMAL_HPP



/* normal.hpp
eyX7gweKW5/46uado97o+Ogpvh+q8MuSrvt049Tb517dffZdMf0jjwdbW3fu1jya19wFXwtpXtv4r1lzZ89rZcI3PGquSf8+2Un/VvNaqXJucQf926djVwHnWbLmzq9HKLqOFa41d1Nkbcg02BxOh73gTHgBnAXXwdlQwhP9MmgIb66sTZgPe8IFsD+8CE6AOXAyzJXw0rReFWmS8JxrxOJCrA02m8NQGA+TYQt4Ch5GKsX/L8R/S+Sg+H9V1vz8DjaHR2Af+DrsD0/DgfAoHA7fhDnwLZgv9gXwHbgKvg8vhyfgOvgneBWshN+BH8O74SfwXvF/H/wQ7oUfwUfF/Q/F/U/F/SFxfwome/06Jz4dnQo4HInnt2X7k3z+AraCX8J2cr5NB1njlwq/ggPkerBcD5G1fhk24BjoheNhOJwFI+E82FjSHQWvgdPgjXKfrTBG0h0L74Jx8B4YDx+CLSSdCZLORPgz8f88bA3fhO3gezAZfgrbwy9gR0hcrE4wCnaDXWAPOAD2hINgKhwO+8CRcACcBAfCKfBCOAcOhvPgMLgWZsMr4Vy4CY6Cm+FoeCMcA2+GmfABOA4+If5+JP6ehePhYTgBviX2x8X+PTgRfg4nwTCvzz4K2vZN4GTYFk6BPcW+r9j3h1PhNDgNzrHNpZ6c0boHKs2qnrRBTkr9/46sFbwdxsA7YDy8C7aCd8Mu8B7YG+6Cg+BuOBLeL+1gD1wPH4JXwodhhdjfBR+H34VPwEfgU/DH8Gkp9x/BF+Gz8A/wp/AEfA7+BR6EZ+DPYSO734MJ8AXYHr4Ie8Bfwz7wsKR/iX8+Fy6S9t8YmS/p/1zWhgz0+tasDILt4IWwDxwMM+V6FhwGF8AMeBFMh4VyfQpGhMicn8yfVkDb3VmvfGzCXRQcDxPgBLnPRNgfvg+HwWlwMZwJV8NZ8FZ4HN4N34X3ivsH4Hy4Dy6AL4m734m7N8XdOzAfNiVyBfA8WAg7wKWwGyyGY+FxmAVt/7Og7X8uLIWl8BJ4BVwBN8FL4Q1wNXxA/D8i/p8U/8/Ay+ErcC18B66D78Gr4IdwE6TeK//x0PafBPGv6v+1sDvcDAfC6+BgeAOcALfA2fBGOB9uhQthBSyH34Kb4M3wOrgT3gzvgbfBXfAu+F2IWA/Cn8KH4EtwL/wNvBd+LPH8QuJphfjiGQofhTFwP+wBbXf9oe3uQnE3FD4Jx8Kn4Dz4Q3gxfBouhz+C5fDHcD18Fl4DD8Ab4E/gd+BhuAO+Ar8LfwMfhG/C78G34CNy38fhc/AAPAh/B38O34PPwxPwBdgo1BfvZvBd2ALa/lvB1+Eg+A4cK+6yxN0scUd7IFNkTg5WiDSR8bn992fceeCHUK2Vhy1hpbSLU3AA/AROh6elHX4JZ8PP4MXwc7hZzK+DX8Ctcn0K7vTIXI/MgVVAO/xt8k24QJ6Pq+EmuAZeDy+D34Lr4d3wOvgIvAI+rtJHvYYb4XPwKngIboIvwavha/Ba+D68AX4At8IvYQW05Ny2JnAbbAm/A9vC2+H58E44Ed4NZ8BdcCG8Hy6GD8IV8CFYBh+GG+Ej8Gb4JLwXPgX3wR/DV+Bz8AN4EH4CX4ReL2Ml2Aj+GraFL8NO8BXYG74EM+Dv4Dj4OpwHfw9z4VFYBt+BV8P34D3wT3A//DM8CE/CX8GP9BpD+R4Ll8m1c43h36W+eEJ89SUEpsBQmArD4ADYDA6E4XAkjICTYWM4B0bBBbAJVPNmsEj8XQwjYYlcn1LjGPnuJ99KK2Q8HeqpOrcwCubJOHIhTIDfgm1gPuwOC+EEuBhOgUtgCSyCK8T9KrgUroUlcBNcBjfDS+BNcAV8AJbDx+FW+LQ=
*/