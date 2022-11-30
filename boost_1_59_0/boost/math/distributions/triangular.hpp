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

  #ifdef __cpp_deduction_guides
  template <class RealType>
  triangular_distribution(RealType)->triangular_distribution<typename boost::math::tools::promote_args<RealType>::type>;
  template <class RealType>
  triangular_distribution(RealType,RealType)->triangular_distribution<typename boost::math::tools::promote_args<RealType>::type>;
  template <class RealType>
  triangular_distribution(RealType,RealType,RealType)->triangular_distribution<typename boost::math::tools::promote_args<RealType>::type>;
  #endif

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