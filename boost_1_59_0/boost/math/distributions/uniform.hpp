//  Copyright John Maddock 2006.
//  Copyright Paul A. Bristow 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// TODO deal with infinity as special better - or remove.
//

#ifndef BOOST_STATS_UNIFORM_HPP
#define BOOST_STATS_UNIFORM_HPP

// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3668.htm
// http://mathworld.wolfram.com/UniformDistribution.html
// http://documents.wolfram.com/calculationcenter/v2/Functions/ListsMatrices/Statistics/UniformDistribution.html
// http://en.wikipedia.org/wiki/Uniform_distribution_%28continuous%29

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>

#include <utility>

namespace boost{ namespace math
{
  namespace detail
  {
    template <class RealType, class Policy>
    inline bool check_uniform_lower(
      const char* function,
      RealType lower,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(lower))
      { // any finite value is OK.
        return true;
      }
      else
      { // Not finite.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Lower parameter is %1%, but must be finite!", lower, pol);
        return false;
      }
    } // bool check_uniform_lower(

    template <class RealType, class Policy>
    inline bool check_uniform_upper(
      const char* function,
      RealType upper,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(upper))
      { // Any finite value is OK.
        return true;
      }
      else
      { // Not finite.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Upper parameter is %1%, but must be finite!", upper, pol);
        return false;
      }
    } // bool check_uniform_upper(

    template <class RealType, class Policy>
    inline bool check_uniform_x(
      const char* function,
      RealType const& x,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(x))
      { // Any finite value is OK
        return true;
      }
      else
      { // Not finite..
        *result = policies::raise_domain_error<RealType>(
          function,
          "x parameter is %1%, but must be finite!", x, pol);
        return false;
      }
    } // bool check_uniform_x

    template <class RealType, class Policy>
    inline bool check_uniform(
      const char* function,
      RealType lower,
      RealType upper,
      RealType* result, const Policy& pol)
    {
      if((check_uniform_lower(function, lower, result, pol) == false)
        || (check_uniform_upper(function, upper, result, pol) == false))
      {
        return false;
      }
      else if (lower >= upper) // If lower == upper then 1 / (upper-lower) = 1/0 = +infinity!
      { // upper and lower have been checked before, so must be lower >= upper.
        *result = policies::raise_domain_error<RealType>(
          function,
          "lower parameter is %1%, but must be less than upper!", lower, pol);
        return false;
      }
      else
      { // All OK,
        return true;
      }
    } // bool check_uniform(

  } // namespace detail

  template <class RealType = double, class Policy = policies::policy<> >
  class uniform_distribution
  {
  public:
    typedef RealType value_type;
    typedef Policy policy_type;

    uniform_distribution(RealType l_lower = 0, RealType l_upper = 1) // Constructor.
      : m_lower(l_lower), m_upper(l_upper) // Default is standard uniform distribution.
    {
      RealType result;
      detail::check_uniform("boost::math::uniform_distribution<%1%>::uniform_distribution", l_lower, l_upper, &result, Policy());
    }
    // Accessor functions.
    RealType lower()const
    {
      return m_lower;
    }

    RealType upper()const
    {
      return m_upper;
    }
  private:
    // Data members:
    RealType m_lower;  // distribution lower aka a.
    RealType m_upper;  // distribution upper aka b.
  }; // class uniform_distribution

  typedef uniform_distribution<double> uniform;

  #ifdef __cpp_deduction_guides
  template <class RealType>
  uniform_distribution(RealType)->uniform_distribution<typename boost::math::tools::promote_args<RealType>::type>;
  template <class RealType>
  uniform_distribution(RealType,RealType)->uniform_distribution<typename boost::math::tools::promote_args<RealType>::type>;
  #endif

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> range(const uniform_distribution<RealType, Policy>& /* dist */)
  { // Range of permissible values for random variable x.
     using boost::math::tools::max_value;
     return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + 'infinity'.
     // Note RealType infinity is NOT permitted, only max_value.
  }

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> support(const uniform_distribution<RealType, Policy>& dist)
  { // Range of supported values for random variable x.
     // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
     using boost::math::tools::max_value;
     return std::pair<RealType, RealType>(dist.lower(),  dist.upper());
  }

  template <class RealType, class Policy>
  inline RealType pdf(const uniform_distribution<RealType, Policy>& dist, const RealType& x)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::pdf(const uniform_distribution<%1%>&, %1%)", lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_uniform_x("boost::math::pdf(const uniform_distribution<%1%>&, %1%)", x, &result, Policy()))
    {
      return result;
    }

    if((x < lower) || (x > upper) )
    {
      return 0;
    }
    else
    {
      return 1 / (upper - lower);
    }
  } // RealType pdf(const uniform_distribution<RealType, Policy>& dist, const RealType& x)

  template <class RealType, class Policy>
  inline RealType cdf(const uniform_distribution<RealType, Policy>& dist, const RealType& x)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::cdf(const uniform_distribution<%1%>&, %1%)",lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_uniform_x("boost::math::cdf(const uniform_distribution<%1%>&, %1%)", x, &result, Policy()))
    {
      return result;
    }
    if (x < lower)
    {
      return 0;
    }
    if (x > upper)
    {
      return 1;
    }
    return (x - lower) / (upper - lower); // lower <= x <= upper
  } // RealType cdf(const uniform_distribution<RealType, Policy>& dist, const RealType& x)

  template <class RealType, class Policy>
  inline RealType quantile(const uniform_distribution<RealType, Policy>& dist, const RealType& p)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks
    if(false == detail::check_uniform("boost::math::quantile(const uniform_distribution<%1%>&, %1%)",lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_probability("boost::math::quantile(const uniform_distribution<%1%>&, %1%)", p, &result, Policy()))
    {
      return result;
    }
    if(p == 0)
    {
      return lower;
    }
    if(p == 1)
    {
      return upper;
    }
    return p * (upper - lower) + lower;
  } // RealType quantile(const uniform_distribution<RealType, Policy>& dist, const RealType& p)

  template <class RealType, class Policy>
  inline RealType cdf(const complemented2_type<uniform_distribution<RealType, Policy>, RealType>& c)
  {
    RealType lower = c.dist.lower();
    RealType upper = c.dist.upper();
    RealType x = c.param;
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::cdf(const uniform_distribution<%1%>&, %1%)", lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_uniform_x("boost::math::cdf(const uniform_distribution<%1%>&, %1%)", x, &result, Policy()))
    {
      return result;
    }
    if (x < lower)
    {
      return 1;
    }
    if (x > upper)
    {
      return 0;
    }
    return (upper - x) / (upper - lower);
  } // RealType cdf(const complemented2_type<uniform_distribution<RealType, Policy>, RealType>& c)

  template <class RealType, class Policy>
  inline RealType quantile(const complemented2_type<uniform_distribution<RealType, Policy>, RealType>& c)
  {
    RealType lower = c.dist.lower();
    RealType upper = c.dist.upper();
    RealType q = c.param;
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::quantile(const uniform_distribution<%1%>&, %1%)", lower, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_probability("boost::math::quantile(const uniform_distribution<%1%>&, %1%)", q, &result, Policy()))
    {
       return result;
    }
    if(q == 0)
    {
       return upper;
    }
    if(q == 1)
    {
       return lower;
    }
    return -q * (upper - lower) + upper;
  } // RealType quantile(const complemented2_type<uniform_distribution<RealType, Policy>, RealType>& c)

  template <class RealType, class Policy>
  inline RealType mean(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0;  // of checks.
    if(false == detail::check_uniform("boost::math::mean(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    return (lower + upper ) / 2;
  } // RealType mean(const uniform_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType variance(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::variance(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    return (upper - lower) * ( upper - lower) / 12;
    // for standard uniform = 0.833333333333333333333333333333333333333333;
  } // RealType variance(const uniform_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType mode(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::mode(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    result = lower; // Any value [lower, upper] but arbitrarily choose lower.
    return result;
  }

  template <class RealType, class Policy>
  inline RealType median(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::median(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    return (lower + upper) / 2; //
  }
  template <class RealType, class Policy>
  inline RealType skewness(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_uniform("boost::math::skewness(const uniform_distribution<%1%>&)",lower, upper, &result, Policy()))
    {
      return result;
    }
    return 0;
  } // RealType skewness(const uniform_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType kurtosis_excess(const uniform_distribution<RealType, Policy>& dist)
  {
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType result = 0;  // of checks.
    if(false == detail::check_uniform("boost::math::kurtosis_execess(const uniform_distribution<%1%>&)", lower, upper, &result, Policy()))
    {
      return result;
    }
    return static_cast<RealType>(-6)/5; //  -6/5 = -1.2;
  } // RealType kurtosis_excess(const uniform_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType kurtosis(const uniform_distribution<RealType, Policy>& dist)
  {
    return kurtosis_excess(dist) + 3;
  }

  template <class RealType, class Policy>
  inline RealType entropy(const uniform_distribution<RealType, Policy>& dist)
  {
    using std::log;
    return log(dist.upper() - dist.lower());
  }

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_UNIFORM_HPP




/* uniform.hpp
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
*/