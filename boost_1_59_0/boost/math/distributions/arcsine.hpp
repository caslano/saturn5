// boost/math/distributions/arcsine.hpp

// Copyright John Maddock 2014.
// Copyright Paul A. Bristow 2014.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// http://en.wikipedia.org/wiki/arcsine_distribution

// The arcsine Distribution is a continuous probability distribution.
// http://en.wikipedia.org/wiki/Arcsine_distribution
// http://www.wolframalpha.com/input/?i=ArcSinDistribution

// Standard arcsine distribution is a special case of beta distribution with both a & b = one half,
// and 0 <= x <= 1.

// It is generalized to include any bounded support a <= x <= b from 0 <= x <= 1
// by Wolfram and Wikipedia,
// but using location and scale parameters by
// Virtual Laboratories in Probability and Statistics http://www.math.uah.edu/stat/index.html
// http://www.math.uah.edu/stat/special/Arcsine.html
// The end-point version is simpler and more obvious, so we implement that.
// TODO Perhaps provide location and scale functions?


#ifndef BOOST_MATH_DIST_ARCSINE_HPP
#define BOOST_MATH_DIST_ARCSINE_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/complement.hpp> // complements.
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks.
#include <boost/math/constants/constants.hpp>

#include <boost/math/special_functions/fpclassify.hpp> // isnan.

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable: 4702) // Unreachable code,
// in domain_error_imp in error_handling.
#endif

#include <utility>
#include <exception>  // For std::domain_error.

namespace boost
{
  namespace math
  {
    namespace arcsine_detail
    {
      // Common error checking routines for arcsine distribution functions:
      // Duplicating for x_min and x_max provides specific error messages.
      template <class RealType, class Policy>
      inline bool check_x_min(const char* function, const RealType& x, RealType* result, const Policy& pol)
      {
        if (!(boost::math::isfinite)(x))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "x_min argument is %1%, but must be finite !", x, pol);
          return false;
        }
        return true;
      } // bool check_x_min

      template <class RealType, class Policy>
      inline bool check_x_max(const char* function, const RealType& x, RealType* result, const Policy& pol)
      {
        if (!(boost::math::isfinite)(x))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "x_max argument is %1%, but must be finite !", x, pol);
          return false;
        }
        return true;
      } // bool check_x_max


      template <class RealType, class Policy>
      inline bool check_x_minmax(const char* function, const RealType& x_min, const RealType& x_max, RealType* result, const Policy& pol)
      { // Check x_min < x_max
        if (x_min >= x_max)
        {
          std::string msg = "x_max argument is %1%, but must be > x_min";
          *result = policies::raise_domain_error<RealType>(
            function,
            msg.c_str(), x_max, pol);
            // "x_max argument is %1%, but must be > x_min !", x_max, pol);
            // "x_max argument is %1%, but must be > x_min %2!", x_max, x_min, pol); would be better. 
            // But would require replication of all helpers functions in /policies/error_handling.hpp for two values,
            // as well as two value versions of raise_error, raise_domain_error and do_format
          return false;
        }
        return true;
      } // bool check_x_minmax

      template <class RealType, class Policy>
      inline bool check_prob(const char* function, const RealType& p, RealType* result, const Policy& pol)
      {
        if ((p < 0) || (p > 1) || !(boost::math::isfinite)(p))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Probability argument is %1%, but must be >= 0 and <= 1 !", p, pol);
          return false;
        }
        return true;
      } // bool check_prob

      template <class RealType, class Policy>
      inline bool check_x(const char* function, const RealType& x_min, const RealType& x_max, const RealType& x, RealType* result, const Policy& pol)
      { // Check x finite and x_min < x < x_max.
        if (!(boost::math::isfinite)(x))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "x argument is %1%, but must be finite !", x, pol);
          return false;
        }
        if ((x < x_min) || (x > x_max))
        {
          // std::cout << x_min << ' ' << x << x_max << std::endl;
          *result = policies::raise_domain_error<RealType>(
            function,
            "x argument is %1%, but must be x_min < x < x_max !", x, pol);
          // For example:
          // Error in function boost::math::pdf(arcsine_distribution<double> const&, double) : x argument is -1.01, but must be x_min < x < x_max !
          // TODO Perhaps show values of x_min and x_max?
          return false;
        }
        return true;
      } // bool check_x

      template <class RealType, class Policy>
      inline bool check_dist(const char* function, const RealType& x_min, const RealType& x_max, RealType* result, const Policy& pol)
      { // Check both x_min and x_max finite, and x_min  < x_max.
        return check_x_min(function, x_min, result, pol)
            && check_x_max(function, x_max, result, pol)
            && check_x_minmax(function, x_min, x_max, result, pol);
      } // bool check_dist

      template <class RealType, class Policy>
      inline bool check_dist_and_x(const char* function, const RealType& x_min, const RealType& x_max, RealType x, RealType* result, const Policy& pol)
      {
        return check_dist(function, x_min, x_max, result, pol)
          && arcsine_detail::check_x(function, x_min, x_max, x, result, pol);
      } // bool check_dist_and_x

      template <class RealType, class Policy>
      inline bool check_dist_and_prob(const char* function, const RealType& x_min, const RealType& x_max, RealType p, RealType* result, const Policy& pol)
      {
        return check_dist(function, x_min, x_max, result, pol)
          && check_prob(function, p, result, pol);
      } // bool check_dist_and_prob

    } // namespace arcsine_detail

    template <class RealType = double, class Policy = policies::policy<> >
    class arcsine_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      arcsine_distribution(RealType x_min = 0, RealType x_max = 1) : m_x_min(x_min), m_x_max(x_max)
      { // Default beta (alpha = beta = 0.5) is standard arcsine with x_min = 0, x_max = 1.
        // Generalized to allow x_min and x_max to be specified.
        RealType result;
        arcsine_detail::check_dist(
          "boost::math::arcsine_distribution<%1%>::arcsine_distribution",
          m_x_min,
          m_x_max,
          &result, Policy());
      } // arcsine_distribution constructor.
      // Accessor functions:
      RealType x_min() const
      {
        return m_x_min;
      }
      RealType x_max() const
      {
        return m_x_max;
      }

    private:
      RealType m_x_min; // Two x min and x max parameters of the arcsine distribution.
      RealType m_x_max;
    }; // template <class RealType, class Policy> class arcsine_distribution

    // Convenient typedef to construct double version.
    typedef arcsine_distribution<double> arcsine;

    #ifdef __cpp_deduction_guides
    template <class RealType>
    arcsine_distribution(RealType)->arcsine_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    template <class RealType>
    arcsine_distribution(RealType, RealType)->arcsine_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    #endif

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const arcsine_distribution<RealType, Policy>&  dist)
    { // Range of permissible values for random variable x.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(static_cast<RealType>(dist.x_min()), static_cast<RealType>(dist.x_max()));
    }

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const arcsine_distribution<RealType, Policy>&  dist)
    { // Range of supported values for random variable x.
      // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
      return std::pair<RealType, RealType>(static_cast<RealType>(dist.x_min()), static_cast<RealType>(dist.x_max()));
    }

    template <class RealType, class Policy>
    inline RealType mean(const arcsine_distribution<RealType, Policy>& dist)
    { // Mean of arcsine distribution .
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      if (false == arcsine_detail::check_dist(
        "boost::math::mean(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      return  (x_min + x_max) / 2;
    } // mean

    template <class RealType, class Policy>
    inline RealType variance(const arcsine_distribution<RealType, Policy>& dist)
    { // Variance of standard arcsine distribution = (1-0)/8 = 0.125.
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();
      if (false == arcsine_detail::check_dist(
        "boost::math::variance(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      return  (x_max - x_min) * (x_max - x_min) / 8;
    } // variance

    template <class RealType, class Policy>
    inline RealType mode(const arcsine_distribution<RealType, Policy>& /* dist */)
    { //There are always [*two] values for the mode, at ['x_min] and at ['x_max], default 0 and 1,
      // so instead we raise the exception domain_error.
      return policies::raise_domain_error<RealType>(
        "boost::math::mode(arcsine_distribution<%1%>&)",
        "The arcsine distribution has two modes at x_min and x_max: "
        "so the return value is %1%.",
        std::numeric_limits<RealType>::quiet_NaN(), Policy());
    } // mode

    template <class RealType, class Policy>
    inline RealType median(const arcsine_distribution<RealType, Policy>& dist)
    { // Median of arcsine distribution (a + b) / 2 == mean.
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();
      RealType result;
      if (false == arcsine_detail::check_dist(
        "boost::math::median(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      return  (x_min + x_max) / 2;
    }

    template <class RealType, class Policy>
    inline RealType skewness(const arcsine_distribution<RealType, Policy>& dist)
    {
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      if (false == arcsine_detail::check_dist(
        "boost::math::skewness(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      return 0;
    } // skewness

    template <class RealType, class Policy>
    inline RealType kurtosis_excess(const arcsine_distribution<RealType, Policy>& dist)
    {
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      if (false == arcsine_detail::check_dist(
        "boost::math::kurtosis_excess(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      result = -3;
      return  result / 2;
    } // kurtosis_excess

    template <class RealType, class Policy>
    inline RealType kurtosis(const arcsine_distribution<RealType, Policy>& dist)
    {
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      if (false == arcsine_detail::check_dist(
        "boost::math::kurtosis(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }

      return 3 + kurtosis_excess(dist);
    } // kurtosis

    template <class RealType, class Policy>
    inline RealType pdf(const arcsine_distribution<RealType, Policy>& dist, const RealType& xx)
    { // Probability Density/Mass Function arcsine.
      BOOST_FPU_EXCEPTION_GUARD
      BOOST_MATH_STD_USING // For ADL of std functions.

      static const char* function = "boost::math::pdf(arcsine_distribution<%1%> const&, %1%)";

      RealType lo = dist.x_min();
      RealType hi = dist.x_max();
      RealType x = xx;

      // Argument checks:
      RealType result = 0; 
      if (false == arcsine_detail::check_dist_and_x(
        function,
        lo, hi, x,
        &result, Policy()))
      {
        return result;
      }
      using boost::math::constants::pi;
      result = static_cast<RealType>(1) / (pi<RealType>() * sqrt((x - lo) * (hi - x)));
      return result;
    } // pdf

    template <class RealType, class Policy>
    inline RealType cdf(const arcsine_distribution<RealType, Policy>& dist, const RealType& x)
    { // Cumulative Distribution Function arcsine.
      BOOST_MATH_STD_USING // For ADL of std functions.

      static const char* function = "boost::math::cdf(arcsine_distribution<%1%> const&, %1%)";

      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      // Argument checks:
      RealType result = 0;
      if (false == arcsine_detail::check_dist_and_x(
        function,
        x_min, x_max, x,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if (x == x_min)
      {
        return 0;
      }
      else if (x == x_max)
      {
        return 1;
      }
      using boost::math::constants::pi;
      result = static_cast<RealType>(2) * asin(sqrt((x - x_min) / (x_max - x_min))) / pi<RealType>();
      return result;
    } // arcsine cdf

    template <class RealType, class Policy>
    inline RealType cdf(const complemented2_type<arcsine_distribution<RealType, Policy>, RealType>& c)
    { // Complemented Cumulative Distribution Function arcsine.
      BOOST_MATH_STD_USING // For ADL of std functions.
      static const char* function = "boost::math::cdf(arcsine_distribution<%1%> const&, %1%)";

      RealType x = c.param;
      arcsine_distribution<RealType, Policy> const& dist = c.dist;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      // Argument checks:
      RealType result = 0;
      if (false == arcsine_detail::check_dist_and_x(
        function,
        x_min, x_max, x,
        &result, Policy()))
      {
        return result;
      }
      if (x == x_min)
      {
        return 0;
      }
      else if (x == x_max)
      {
        return 1;
      }
      using boost::math::constants::pi;
      // Naive version x = 1 - x;
      // result = static_cast<RealType>(2) * asin(sqrt((x - x_min) / (x_max - x_min))) / pi<RealType>();
      // is less accurate, so use acos instead of asin for complement.
      result = static_cast<RealType>(2) * acos(sqrt((x - x_min) / (x_max - x_min))) / pi<RealType>();
      return result;
    } // arcsine ccdf

    template <class RealType, class Policy>
    inline RealType quantile(const arcsine_distribution<RealType, Policy>& dist, const RealType& p)
    { 
      // Quantile or Percent Point arcsine function or
      // Inverse Cumulative probability distribution function CDF.
      // Return x (0 <= x <= 1),
      // for a given probability p (0 <= p <= 1).
      // These functions take a probability as an argument
      // and return a value such that the probability that a random variable x
      // will be less than or equal to that value
      // is whatever probability you supplied as an argument.
      BOOST_MATH_STD_USING // For ADL of std functions.

      using boost::math::constants::half_pi;

      static const char* function = "boost::math::quantile(arcsine_distribution<%1%> const&, %1%)";

      RealType result = 0; // of argument checks:
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();
      if (false == arcsine_detail::check_dist_and_prob(
        function,
        x_min, x_max, p,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if (p == 0)
      {
        return 0;
      }
      if (p == 1)
      {
        return 1;
      }

      RealType sin2hpip = sin(half_pi<RealType>() * p);
      RealType sin2hpip2 = sin2hpip * sin2hpip;
      result = -x_min * sin2hpip2 + x_min + x_max * sin2hpip2;

      return result;
    } // quantile

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<arcsine_distribution<RealType, Policy>, RealType>& c)
    { 
      // Complement Quantile or Percent Point arcsine function.
      // Return the number of expected x for a given
      // complement of the probability q.
      BOOST_MATH_STD_USING // For ADL of std functions.

      using boost::math::constants::half_pi;
      static const char* function = "boost::math::quantile(arcsine_distribution<%1%> const&, %1%)";

      // Error checks:
      RealType q = c.param;
      const arcsine_distribution<RealType, Policy>& dist = c.dist;
      RealType result = 0;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();
      if (false == arcsine_detail::check_dist_and_prob(
        function,
        x_min,
        x_max,
        q,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if (q == 1)
      {
        return 0;
      }
      if (q == 0)
      {
        return 1;
      }
      // Naive RealType p = 1 - q; result = sin(half_pi<RealType>() * p); loses accuracy, so use a cos alternative instead.
      //result = cos(half_pi<RealType>() * q); // for arcsine(0,1)
      //result = result * result;
      // For generalized arcsine:
      RealType cos2hpip = cos(half_pi<RealType>() * q);
      RealType cos2hpip2 = cos2hpip * cos2hpip;
      result = -x_min * cos2hpip2 + x_min + x_max * cos2hpip2;

      return result;
    } // Quantile Complement

  } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#if defined (BOOST_MSVC)
# pragma warning(pop)
#endif

#endif // BOOST_MATH_DIST_ARCSINE_HPP

/* arcsine.hpp
U3U89VT+Dp/9NPd6d9XFBdUl9F6hzg30gcTy3UBrYy1qWojqMo9f5OlibYVT/RoqQee1oDCCToGouUrPLuKcILFhvuzVzLHbhus/AEaAuX/+Bskvm1FyaV41BAP8e1EWfvP8kj01Is9InYeRMUTaMZD/Xr2T//6o/GId8MvlwAmZKLNZdywcGIuUJPyCxsmflRb8lXrBenTB6Vipuj07rjHuGr1jYReuXpACGyfvjZRsvk4eb2/Kn9s7h/yqvKAfG7rAt7RlGKmJehx8B4w4cydp8CffJMW+En6kFfTGr+9+CL8CqdIfEDNCPZ+lLLlr4Sfc6UYD8OduRXrs7QUF/4UON27emJHciu2h/DjZ9DLEX+MqHSP3OQBP02JlGpuTNbGvHOwCzYl0DFCg1J/7B5NapTYWI7Wv0d1v4reMO0r6jodP0AMCB7jnWBr57Zz8O7cukn80qo9829rw8zBM3fl37pTMmV0r9iIDWDz3Xvb/pBfI0mq9umC+lIsaYE68Ly78A0bMAA4lm9ZQ+UYpHROD8WhOMqynmhfwFAiXUPghCIvWsz6daJW820R2lrtt819LtE2lL+GXYUoWv0FTMhV+pE+v4BSYvDxqNka9AVGlzsB3XiOHTpUF9/m/8/Wr0blSOVB4wrsW9JDbI1VehpWHVskfXyNVAl3cGe2FVtliBC+yXjYXXEUrHHyj+1XzVHSaRcdAoLXNYympfS0NywYUq5cahpLlczPayLGQ1Ifn+5UP1GHBf6Fp8bIv1NzIIxidFwBMCb3Jd9iXLp0ArNmMD1hIy6FKqk/Ku0wW/+9uVQP1rEHr7KDXImZj34Ac3X5IwK2aeml5FuGcIfyu9NQAwBAVHmWRlkY/BVYdvkm6F3JJBdHIX7taQb9hlQ2byBWQcmh7DjSBDZetJ/NxF+m2ATTFsmnc39BwLO2B1R7URGkNSlBpE7ly1ui/qPYtlybQevDFZ5U1/06t2BowLJVCQrhZ+mUw0rN560llsA2FFXRoJH2vuQm+GZV+Ml6qMELueqkyF8NLeklbhtNH56w6SSbvSV9HWTcBijR/gWO/DZLDO4BTupnOCrGwCp75I9qYaoO6TAjnmLrCXxBRul2l7RdfsnQuB8o9AM1IrXei4gWRi/25Xa9C97x/kEZh+4/4L8b5pkiD4XtLbZxicJf+lhixtBqLO5O1oIEZjl3BYZX+jSgjzE3nrH1SPyPGiX/lIANNKdxZWo1PeTfBH/9FDQCpTvpzSrvTHQH1VzoigNfiYi2oxX9LOWGYxhzTpBQYEIIZra0Ae68Oe5slMsMf3wGGhHt4dnkvrjT0q8I9ov2o37mgbR5JhZ8nzwUl7cxB4BhtmIqW/qGQZRCkZe3DtC8PojlMCWjJNtYzhRo64u0YSUDz0BHoyCWNb1i01kOwiEHFq+uzh11AuRd34XQH3+a8KzmSTW7gLbMabmy/XnG0oNJ43ToDxQBF8TOIeTrpkbtwKDUMCNTu61C9+a3Y9ezM2ieyOrK9gnDlTXDDQHsWOECEy+6vUm3tjKbwNKkqA/c1+KwUOHJSvAmCvzxOkHf4zpBmU+AMpoR3uTJrydA0KqhVo+UJrVQ6zNSMmZIxk3QMatqKDziH3wbx7f2dN/ovRt5g5S5/m37BROPGfa7NauU/l/HDvRBtW3CLcP6w/9t4bwcxs1wIJguaWjdow/6mu1zlzR18OTwQDwGNN6WgoKC0FERT6LjeJdf5zrnRelqSIsjlLrnW11pp7GVTYSb431V0AY/3LbRg/uAEgPKEZChng99G+NcE5eEHSPgEYDQT2nyN4Regyw7or7EyBf5BCfjDi8BHI/6hQvAr4Z8W/NPma2gpTDKrmifJOCE0H+hfuRkP4UnfZ5IFJE+PmHEX0KO1nWiPL4g/pDLBnHUVctQ+o8Ds0MVReinnEnocCWxv+GsUYqX+KKn6PXoVr/JPv6OVZbneSh8D78y9ItvRWh7v7b5aPWp1asLwCt8UgFBxmfde4Xw5OsL7fih1bVXxiSgaE0pNKCg6JhsLii62GRfXC0w9hqWCkF3h+8K1Rb5K/60QNfsEf4tMkM+qcAUqvTVho9C9TPA3yiDEVyLUi/d5bytu9fYRyk8mw3d3+O6ifBvhuyP/1Ba3+hiUiBS+vv8iMJvMvcZVuGdFiDMLx3Jna7na23G1NhEmukQNw2ktj/MaCxhE+KW4gqAakbm1XOs18CgtxWgRfcqbdb4J/EPjTRUgXaBEQqEWxC5cMHoXqyT8gTaoAcSosxhZwP+L9C8Gv9IBv0ZhhaAkJoI8XA4Sux001Al4EiCxBWPbCM/sLSLi2AForFfzE4AqsfWVCkUX0bC14JNN+Ha6MU2baExzJNqEonLavqz1nRKKmjEHmVxFlsTbE42VCSIiKijnickYlQZBVzLGpWFcOsZlIAZjfBPGSxjPOybXYmyLSFj8T1eRhC24itrwx+jHTnLM3nyVunvd+OEf6LC110+QINdF5ogmSPA3x8VMEk0QxGmjkxSZoPz2CfI36xGmBDh1+wTF8wlSxTTxv5wfR2IbjrgFasYJShORFEAsAC6VN2PXi8EU35c0PQvl68ZL8wMa0GI+PzAXhbHTxOenPGZ+RKU9hG8bwrcF4ySMw0lwSRjXhHGNGAfSeDPNEE7fhGSMp57xCcJpTvlv87OFthZF4CNFp/gOs+FwIoqvHdeSclvVUU37TVNxKwt0Pe7nJ5UX822ofMWVyx71uhNCiv+UBb9sipqqK07k9ZAPUz5aRKYKDKoDnl8EdYV7C6zYTB0I6vKxzZAS9JcBZdN9jcWZ7k7qje6tBAwVm0t5/rchsUa3IoFeBSqr0S1J4MIwFLhyjvdzDnxfUL7ny6Zb/oJHDyTIx4WY1SAw4YmDqy8SBMa/hqJKMwT8uRUJ6EaXyPM9NBwTVH8GCQibIr1zy4vcuYf7RcBQ+6OcGlQ3z7ai0B27z2J8LWaf5W5rzD6L+ocb7LO020IKrNwOsB5dr7rHbrVSHtzLA3oKsvATGSQL34zfvnMo3JV5T6C4/0Al00kGtYpvBIBu54e67MVlvhx7R5rYqTDuDyFDUFduQPDrFqzn4JoqeXMIKgNL6IDfagPqec2knawwqJWji1XDSamcfEDZROPuPT9/j3ztN/cwWO59UEEWKMJn7P6dAIDdUtlZ7jUESzYjIHvNbJdsKgF4s9zbIasjtE7CbQrrUTsL242jT9mtp3y11+1WxB5b5bb132offbR/FlgzNk4H9GgjpO/wiETr+12O7tMktWpRb1Si1NANR+hvvAM9/wbxdnYJOnHZbr3sK/sfOvHbfWgldb+ZA+AQdsDW3oE7cPsLejGI92K3bFr6Avbir0ovulIvzkIvztmt53yf/0+g4Ht3oHR1le7vhboQinfSCTx36q+VybDOdZ+5qaj7YIQg9zW+QDYTkf3HFXxA7wo+luYKLkx3BScmX6O7u9mTejcbxOxaF3sy25153s2+FdlJGNzbBcbAaTR2eZ4QXMGxte5gXgOoZdZhRn8RWc0BBafVJLG8NtHaYlyFh8pY3mX89r+K8vxSrcpY/Cf8sqq9XdElVTSDFvClS1ND54RLgpC2wlu0XOVZ+HiTD7hWbsU6PLdwC+DtZviSPu5HC6MT30BHrPo7RLOxWr4gqK490rg78RPIFpuoFT1uwv8MjMhwaQ6RyX6Xsvn+wp/Qvxuyy9WCvzIZR4Lb1M05Mh42bUbnHzezp2eddmaddmfWvJ3utWbty+myaKgQGq9ndhhb2YJ4poafRUlyBXDZZGuXhWnh71kFAIOJNckwRx3Y3JqksMbBmhFuAvvGOmzhZEGuFMqPawXNUZZ3DiC0IIdDbeEgZ+C0V+ewZnoH4Yf1scveDL9V5euKdHZJ6G71R2o7+n46ALJuTY1dboh0HUQHOmYSAi3DxR4AwD4GvwsFFzseuz1zoz2AdNoA+Jl8CepA6+iPRltPXhpbmipo7tZDTBfcXasDLAZdbJxehLSxoVQ1biFpygWrtCyRdpH01j0LwqiChOyyK5RaNgoYrDasQZy8bj9SIY4ii2uei+om7rl6BFCiQBhosDOt2t921QcqWJyL7ZDGUA7cLXJ58jGPI5gUF7P3bWcX0K8RRtso/ek7pDx66H0PZIg26zK9doU2CH9jqTKnydFC068rxByQPUKbs+pg7UwspbUDIiutPWao/hHQ+IKMDik1kOY3fAwR1Mvmx26hvL8yHYZ0ff+BtLcI/Z39s5JVNXa6yqOmqFbFnwStLvLCT1510Xn8gQJDzlMBvD5mswHX+F96kTbhx5gWWYlcBQ1uJnPJEkoObiUfpoCMfuO6plasw8/9rhj+SE+icYCXuPuWawzn1/RbNg14BlaX4StY9KxNNh18NkrRhJCgJvOBNPtihNR7s5jhw9OYpUE23f9srNWgBR0KTZ2fQQI1Vi8HNeF4adKPsMaOIEl+5tnrbylQ7LdPyFE2og8JyZL9NIYVtgmoaizur+Y+qO02KuYiV2SddI4yjxV46AcemspDjTw0h4d28NB8HtrGQ0t46AMKsULFsUknreMR5LMe0k1Ew561FuIDEP8FTgfIAWd60iyxTSruZ2/Boj1a5ARfFygz4xfuH2vBgh0kEQqWQqFtPSKz+C9ePDKL3kyULSYMxZZyb4LCeG5C985ZDLd5O/nvUvkSMMf+odFZnd+DW7VbTvGT6NnX4D2AiRl0pzgCm9FIZJRNF0I41T+FaYrRXrY2xOt44SqtPloMyrysk2RZUnUnWjwTaPMTNL1dQiiOvQ81+NtkrxBjXbK3RXFkEDOwsIIjd4aohlvQ6bJe2nkZK/mZRXGEyBkgCrusnPzn6xHG/tlfuGxWN+h62ez1v8TIZv8cFCObzf7PjXxgflOmeUKbdYS8MoDxXQi0ejsJnlbp1m9lWQz16BDWiOwI+q4Uf46mq1bQcTyLtVJcbLI9+4FkY/FfeXqK9EMT94TyjAai34LuXWelk01ocWoUPE6tqGl0Wc96rTkztJB58w0yf4ZxoXHJSgFXaJImWUptQbOhV5tVFh6xIa7YqfLqWuP13tvsrVqzGr/V3u74rcVvrddoL9aaQfmO9+rId5ZVhnUxlxNcJ3VEZB7yE1IXZd+Tl9fk7V2U7R4Pv92KsolJZ0r5MD0ghtJE70yBCZFGYswmilnRUbLgvJao+G51xBeAVTmu3+OdEiuFWJzALhnoTBfRi+TrC2jDk/5+lN+fkiH95xLe34J1+mXZWIxCid16xfjMdyqKWaGzrtAu00mzUtAD4oT0KBb0jNOPCWmb2Ag1bg5Ik2Pi/MvUWpW3h2SPiRM809Ra6Q6M0VSS+Q4A/aCDPNNd7JALpNw/QLckww3qufDN9fWc+CZaj32Thk7kHsTTC5UjOC3IkH6BHOFbHOw9rjCxj838ABbu/sGczEcncui4uTkRHRaOXIwF8a6LERDD4L2JAIoVOunhZPQEiunuF220kC0xu4Q0F0CbRpRMAnEAJrooRxG9mJ0OefTyL4ERdRU8NuCfE7LR4Ya5MuR94Q5SkxGplOIr5okTNOX+P2pVyzqLnjFawXOP3sWSEkSPNtGtKXdpyipvuAcf8YEB4QPmGa2LHaX30HztRx+6LNk5+Luc4SuWSGVf00pxsbstgkdIcofmdtRK714baWcDOgZOr3AKnhoxNKJQWvM1ER2XxwmSaaM0+2uaE60bssO8bBLYfkFTK13khvckeZfLv10bOL2yJqyxf6yWa6wjl5UoF9NE/Bbsq6uuc3axxWJt0Snu5nABhEUHejQ6bn2P39hw61yzgH9sUp8L2KnCNmIMxeZGXDRGHteixHGX6cX56ERZS9+jBWWTaYZNZCstInskA/eHZ0pf4owGN2BJqY6+12LN0mdEb0v5UaV7Muhki2QmakM7avlizryp3h413Bub685UpCRbORlmsxNykXPLHqmnosrQoSO2jbotwi92Nbw8cspPursNKUFZnIK/2Hn/NmpC5U3/lxoVw2evYCdAQnWHxqY7WV6aHWR0O+sYNoihcekOdncam6JlnWTTvqcQe+lQxbRfN4o+GzNxWeQjYlfAEgSx2WcrGknYm+1fkab1DS5akY775d6b4ONW/EiAj97wAVyYjcuQ7j1KxDOR9+wXIFNS8XnoXnATAXQJ7p4GN9FU4R0RgGM9XExrFmq0an7IvlIoqsIpv3ZB/ZY/nIUcbdpEdkzE6wScbI4WZX2j23Naqv1Klt2haTpVO2d5hY7/ngZu8O5XCpsYjWwihrksgSw5M/S+pPN0xZ2x+BHcNDYG6pZ0hMx6l0ZrFlkT7de1luu9dyEZgHH/JZsfRUDZCaN2SgElpgtN+bgMVzDJLISm6CUzAMUV1JqbNXTob6R3vFLHRKXE96pIHfbs9jskRM/dqS42JQPjB50EpFiRqjcGcFPLldPDbCz+hHS1JHP45ZwH02CE3x5WRnh3WmSEvB2AhC9b+oFvRy/jDTXy0B9Ez5RU7CT1Z+kl2rNyswrM8lkz0NKJ0gc8p4OXW89Dd/Im/3AYC9Rik0AGkMXWSyt4jtTVHcza1sbudecPa/aww2ijB3Jn6gjkDhimXjqRCF98O0e5tQpo80yirFE/wOv3dA6jceQ83Xvo1YE+EI53eZboBc1wadcV3NHzDpdrfbOcWfscORPTvEZpTyNCpAGVMBFobghPEMAwXyBhu0Ex/7A9dqDEmZFSSdJLWMoz8Zois3gRJXMHqX8iCZfXX1ARkYPSIgQNL3sTgRutp7lqBrR1A/Fgh0UQxN3o+vclArXPIeznGuUWoshFMm24U9eJHMEaELCnYb1I3x0iApwksj3AK1bzgxZuVl2C97dBFVxYBhGEpdDVNlB9cBJute8nZV0a8R+Urqbhko8ot8cj6y6ityTT5u3ka0SJmUU5GgC7m52h65VAFTtjLP4Jt3FfPAtixTaF4HJSLfg3NRG9miwt4TYs6fIZ+M3xY7T3rqKRJP0MKxpJ0tAdaL9spHHsRh9cNJi60Pyzm9/Eg27tAw7TxTiBZcielyfhhm0dXX7wBifvIbpLCI+dcSNrMYHcwWqcbCdBeQ8ffzbUA2DCRKtozjf6M+lw7ZIkMTTvnNM6W2Vcg7fBOKyPtBmfJTaw4CBC3CiEUoOCZ7wWfp/zL0tuUXn7SPf+OgkEleQWaeTBawSeu6WBv13JTb9VyYUvo5UULklW+QqkE1/+KmurI/mUzTdW2glJ6DVYTEgk19FFePySI//DZotK8NQBdKlkKKkUqSBCWFPLDzNDCkF5+JUodNAUUZMajAHVqsN0DuFVjp7+qpntFHu6gvtRWTQWeUJzyoGr8wPJ0x8hI9gF5+BW8tGud5MrmKPEN1oa+hOipvuoyCpJ1trFWqSEA3SPIA9L7KdIyNqyopcAeR3Acwb+hC7eu9uzZUBEOBG/7ocv1uK/Ki/TWReiLPvnDipV0V3I34yBRjy3tjJNaww8BzNetJLzuc7wQXzOAB/I54yBBeQuu9KiMgaQN0hvtKAISPxNZSxeBNVIz2EU4ywvQN/js0W2vo1umpp9r/QkjEMxt+2Rpg0mxwedFB/tjW8g9sR3W6QXN0V6kaD0wpdEPYBC+3TQxq28C3o1dWEvNtupBYGzHqOkuBbusuun
*/