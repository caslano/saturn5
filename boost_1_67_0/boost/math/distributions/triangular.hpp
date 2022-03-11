//  Copyright John Maddock 2006, 2007.
//  Copyright Paul A. Bristow 2006, 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_TRIANGULAR_HPP
#define BOOST_STATS_TRIANGULAR_HPP

// http://mathworld.wolfram.com/TriangularDistribution.html
// Note that the 'constructors' defined by Wolfram are difference from those here,
// for example
// N[variance[triangulardistribution{1, +2}, 1.5], 50] computes 
// 0.041666666666666666666666666666666666666666666666667
// TriangularDistribution{1, +2}, 1.5 is the analog of triangular_distribution(1, 1.5, 2)

// http://en.wikipedia.org/wiki/Triangular_distribution

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/constants/constants.hpp>

#include <utility>

namespace boost{ namespace math
{
  namespace detail
  {
    template <class RealType, class Policy>
    inline bool check_triangular_lower(
      const char* function,
      RealType lower,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(lower))
      { // Any finite value is OK.
        return true;
      }
      else
      { // Not finite: infinity or NaN.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Lower parameter is %1%, but must be finite!", lower, pol);
        return false;
      }
    } // bool check_triangular_lower(

    template <class RealType, class Policy>
    inline bool check_triangular_mode(
      const char* function,
      RealType mode,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(mode))
      { // any finite value is OK.
        return true;
      }
      else
      { // Not finite: infinity or NaN.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Mode parameter is %1%, but must be finite!", mode, pol);
        return false;
      }
    } // bool check_triangular_mode(

    template <class RealType, class Policy>
    inline bool check_triangular_upper(
      const char* function,
      RealType upper,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(upper))
      { // any finite value is OK.
        return true;
      }
      else
      { // Not finite: infinity or NaN.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Upper parameter is %1%, but must be finite!", upper, pol);
        return false;
      }
    } // bool check_triangular_upper(

    template <class RealType, class Policy>
    inline bool check_triangular_x(
      const char* function,
      RealType const& x,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(x))
      { // Any finite value is OK
        return true;
      }
      else
      { // Not finite: infinity or NaN.
        *result = policies::raise_domain_error<RealType>(
          function,
          "x parameter is %1%, but must be finite!", x, pol);
        return false;
      }
    } // bool check_triangular_x

    template <class RealType, class Policy>
    inline bool check_triangular(
      const char* function,
      RealType lower,
      RealType mode,
      RealType upper,
      RealType* result, const Policy& pol)
    {
      if ((check_triangular_lower(function, lower, result, pol) == false)
        || (check_triangular_mode(function, mode, result, pol) == false)
        || (check_triangular_upper(function, upper, result, pol) == false))
      { // Some parameter not finite.
        return false;
      }
      else if (lower >= upper) // lower == upper NOT useful.
      { // lower >= upper.
        *result = policies::raise_domain_error<RealType>(
          function,
          "lower parameter is %1%, but must be less than upper!", lower, pol);
        return false;
      }
      else
      { // Check lower <= mode <= upper.
        if (mode < lower)
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "mode parameter is %1%, but must be >= than lower!", lower, pol);
          return false;
        }
        if (mode > upper)
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "mode parameter is %1%, but must be <= than upper!", upper, pol);
          return false;
        }
        return true; // All OK.
      }
    } // bool check_triangular
  } // namespace detail

  template <class RealType = double, class Policy = policies::policy<> >
  class triangular_distribution
  {
  public:
    typedef RealType value_type;
    typedef Policy policy_type;

    triangular_distribution(RealType l_lower = -1, RealType l_mode = 0, RealType l_upper = 1)
      : m_lower(l_lower), m_mode(l_mode), m_upper(l_upper) // Constructor.
    { // Evans says 'standard triangular' is lower 0, mode 1/2, upper 1,
      // has median sqrt(c/2) for c <=1/2 and 1 - sqrt(1-c)/2 for c >= 1/2
      // But this -1, 0, 1 is more useful in most applications to approximate normal distribution,
      // where the central value is the most likely and deviations either side equally likely.
      RealType result;
      detail::check_triangular("boost::math::triangular_distribution<%1%>::triangular_distribution",l_lower, l_mode, l_upper, &result, Policy());
    }
    // Accessor functions.
    RealType lower()const
    {
      return m_lower;
    }
    RealType mode()const
    {
      return m_mode;
    }
    RealType upper()const
    {
      return m_upper;
    }
  private:
    // Data members:
    RealType m_lower;  // distribution lower aka a
    RealType m_mode;  // distribution mode aka c
    RealType m_upper;  // distribution upper aka b
  }; // class triangular_distribution

  typedef triangular_distribution<double> triangular;

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> range(const triangular_distribution<RealType, Policy>& /* dist */)
  { // Range of permissible values for random variable x.
    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>());
  }

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> support(const triangular_distribution<RealType, Policy>& dist)
  { // Range of supported values for random variable x.
    // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
    return std::pair<RealType, RealType>(dist.lower(), dist.upper());
  }

  template <class RealType, class Policy>
  RealType pdf(const triangular_distribution<RealType, Policy>& dist, const RealType& x)
  {
    static const char* function = "boost::math::pdf(const triangular_distribution<%1%>&, %1%)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_triangular_x(function, x, &result, Policy()))
    {
      return result;
    }
    if((x < lower) || (x > upper))
    {
      return 0;
    }
    if (x == lower)
    { // (mode - lower) == 0 which would lead to divide by zero!
      return (mode == lower) ? 2 / (upper - lower) : RealType(0);
    }
    else if (x == upper)
    {
      return (mode == upper) ? 2 / (upper - lower) : RealType(0);
    }
    else if (x <= mode)
    {
      return 2 * (x - lower) / ((upper - lower) * (mode - lower));
    }
    else
    {  // (x > mode)
      return 2 * (upper - x) / ((upper - lower) * (upper - mode));
    }
  } // RealType pdf(const triangular_distribution<RealType, Policy>& dist, const RealType& x)

  template <class RealType, class Policy>
  inline RealType cdf(const triangular_distribution<RealType, Policy>& dist, const RealType& x)
  {
    static const char* function = "boost::math::cdf(const triangular_distribution<%1%>&, %1%)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_triangular_x(function, x, &result, Policy()))
    {
      return result;
    }
    if((x <= lower))
    {
      return 0;
    }
    if (x >= upper)
    {
      return 1;
    }
    // else lower < x < upper
    if (x <= mode)
    {
      return ((x - lower) * (x - lower)) / ((upper - lower) * (mode - lower));
    }
    else
    {
      return 1 - (upper - x) *  (upper - x) / ((upper - lower) * (upper - mode));
    }
  } // RealType cdf(const triangular_distribution<RealType, Policy>& dist, const RealType& x)

  template <class RealType, class Policy>
  RealType quantile(const triangular_distribution<RealType, Policy>& dist, const RealType& p)
  {
    BOOST_MATH_STD_USING  // for ADL of std functions (sqrt).
    static const char* function = "boost::math::quantile(const triangular_distribution<%1%>&, %1%)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks
    if(false == detail::check_triangular(function,lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_probability(function, p, &result, Policy()))
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
    RealType p0 = (mode - lower) / (upper - lower);
    RealType q = 1 - p;
    if (p < p0)
    {
      result = sqrt((upper - lower) * (mode - lower) * p) + lower;
    }
    else if (p == p0)
    {
      result = mode;
    }
    else // p > p0
    {
      result = upper - sqrt((upper - lower) * (upper - mode) * q);
    }
    return result;

  } // RealType quantile(const triangular_distribution<RealType, Policy>& dist, const RealType& q)

  template <class RealType, class Policy>
  RealType cdf(const complemented2_type<triangular_distribution<RealType, Policy>, RealType>& c)
  {
    static const char* function = "boost::math::cdf(const triangular_distribution<%1%>&, %1%)";
    RealType lower = c.dist.lower();
    RealType mode = c.dist.mode();
    RealType upper = c.dist.upper();
    RealType x = c.param;
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_triangular_x(function, x, &result, Policy()))
    {
      return result;
    }
    if (x <= lower)
    {
      return 1;
    }
    if (x >= upper)
    {
      return 0;
    }
    if (x <= mode)
    {
      return 1 - ((x - lower) * (x - lower)) / ((upper - lower) * (mode - lower));
    }
    else
    {
      return (upper - x) *  (upper - x) / ((upper - lower) * (upper - mode));
    }
  } // RealType cdf(const complemented2_type<triangular_distribution<RealType, Policy>, RealType>& c)

  template <class RealType, class Policy>
  RealType quantile(const complemented2_type<triangular_distribution<RealType, Policy>, RealType>& c)
  {
    BOOST_MATH_STD_USING  // Aid ADL for sqrt.
    static const char* function = "boost::math::quantile(const triangular_distribution<%1%>&, %1%)";
    RealType l = c.dist.lower();
    RealType m = c.dist.mode();
    RealType u = c.dist.upper();
    RealType q = c.param; // probability 0 to 1.
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, l, m, u, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_probability(function, q, &result, Policy()))
    {
      return result;
    }
    if(q == 0)
    {
      return u;
    }
    if(q == 1)
    {
      return l;
    }
    RealType lower = c.dist.lower();
    RealType mode = c.dist.mode();
    RealType upper = c.dist.upper();

    RealType p = 1 - q;
    RealType p0 = (mode - lower) / (upper - lower);
    if(p < p0)
    {
      RealType s = (upper - lower) * (mode - lower);
      s *= p;
      result = sqrt((upper - lower) * (mode - lower) * p) + lower;
    }
    else if (p == p0)
    {
      result = mode;
    }
    else // p > p0
    {
      result = upper - sqrt((upper - lower) * (upper - mode) * q);
    }
    return result;
  } // RealType quantile(const complemented2_type<triangular_distribution<RealType, Policy>, RealType>& c)

  template <class RealType, class Policy>
  inline RealType mean(const triangular_distribution<RealType, Policy>& dist)
  {
    static const char* function = "boost::math::mean(const triangular_distribution<%1%>&)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0;  // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return (lower + upper + mode) / 3;
  } // RealType mean(const triangular_distribution<RealType, Policy>& dist)


  template <class RealType, class Policy>
  inline RealType variance(const triangular_distribution<RealType, Policy>& dist)
  {
    static const char* function = "boost::math::mean(const triangular_distribution<%1%>&)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return (lower * lower + upper * upper + mode * mode - lower * upper - lower * mode - upper * mode) / 18;
  } // RealType variance(const triangular_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType mode(const triangular_distribution<RealType, Policy>& dist)
  {
    static const char* function = "boost::math::mode(const triangular_distribution<%1%>&)";
    RealType mode = dist.mode();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular_mode(function, mode, &result, Policy()))
    { // This should never happen!
      return result;
    }
    return mode;
  } // RealType mode

  template <class RealType, class Policy>
  inline RealType median(const triangular_distribution<RealType, Policy>& dist)
  {
    BOOST_MATH_STD_USING // ADL of std functions.
    static const char* function = "boost::math::median(const triangular_distribution<%1%>&)";
    RealType mode = dist.mode();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular_mode(function, mode, &result, Policy()))
    { // This should never happen!
      return result;
    }
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    if (mode >= (upper + lower) / 2)
    {
      return lower + sqrt((upper - lower) * (mode - lower)) / constants::root_two<RealType>();
    }
    else
    {
      return upper - sqrt((upper - lower) * (upper - mode)) / constants::root_two<RealType>();
    }
  } // RealType mode

  template <class RealType, class Policy>
  inline RealType skewness(const triangular_distribution<RealType, Policy>& dist)
  {
    BOOST_MATH_STD_USING  // for ADL of std functions
    using namespace boost::math::constants; // for root_two
    static const char* function = "boost::math::skewness(const triangular_distribution<%1%>&)";

    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == boost::math::detail::check_triangular(function,lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return root_two<RealType>() * (lower + upper - 2 * mode) * (2 * lower - upper - mode) * (lower - 2 * upper + mode) /
      (5 * pow((lower * lower + upper * upper + mode * mode 
        - lower * upper - lower * mode - upper * mode), RealType(3)/RealType(2)));
    // #11768: Skewness formula for triangular distribution is incorrect -  corrected 29 Oct 2015 for release 1.61.
  } // RealType skewness(const triangular_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType kurtosis(const triangular_distribution<RealType, Policy>& dist)
  { // These checks may be belt and braces as should have been checked on construction?
    static const char* function = "boost::math::kurtosis(const triangular_distribution<%1%>&)";
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType mode = dist.mode();
    RealType result = 0;  // of checks.
    if(false == detail::check_triangular(function,lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return static_cast<RealType>(12)/5; //  12/5 = 2.4;
  } // RealType kurtosis_excess(const triangular_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType kurtosis_excess(const triangular_distribution<RealType, Policy>& dist)
  { // These checks may be belt and braces as should have been checked on construction?
    static const char* function = "boost::math::kurtosis_excess(const triangular_distribution<%1%>&)";
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType mode = dist.mode();
    RealType result = 0;  // of checks.
    if(false == detail::check_triangular(function,lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return static_cast<RealType>(-3)/5; // - 3/5 = -0.6
    // Assuming mathworld really means kurtosis excess?  Wikipedia now corrected to match this.
  }

  template <class RealType, class Policy>
  inline RealType entropy(const triangular_distribution<RealType, Policy>& dist)
  {
    using std::log;
    return constants::half<RealType>() + log((dist.upper() - dist.lower())/2);
  }

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_TRIANGULAR_HPP




/* triangular.hpp
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
*/