//  Copyright John Maddock 2007.
//  Copyright Paul A. Bristow 2007, 2009
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_PARETO_HPP
#define BOOST_STATS_PARETO_HPP

// http://en.wikipedia.org/wiki/Pareto_distribution
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3661.htm
// Also:
// Weisstein, Eric W. "Pareto Distribution."
// From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/ParetoDistribution.html
// Handbook of Statistical Distributions with Applications, K Krishnamoorthy, ISBN 1-58488-635-8, Chapter 23, pp 257 - 267.
// Caution KK's a and b are the reverse of Mathworld!

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/special_functions/powm1.hpp>

#include <utility> // for BOOST_CURRENT_VALUE?

namespace boost
{
  namespace math
  {
    namespace detail
    { // Parameter checking.
      template <class RealType, class Policy>
      inline bool check_pareto_scale(
        const char* function,
        RealType scale,
        RealType* result, const Policy& pol)
      {
        if((boost::math::isfinite)(scale))
        { // any > 0 finite value is OK.
          if (scale > 0)
          {
            return true;
          }
          else
          {
            *result = policies::raise_domain_error<RealType>(
              function,
              "Scale parameter is %1%, but must be > 0!", scale, pol);
            return false;
          }
        }
        else
        { // Not finite.
          *result = policies::raise_domain_error<RealType>(
            function,
            "Scale parameter is %1%, but must be finite!", scale, pol);
          return false;
        }
      } // bool check_pareto_scale

      template <class RealType, class Policy>
      inline bool check_pareto_shape(
        const char* function,
        RealType shape,
        RealType* result, const Policy& pol)
      {
        if((boost::math::isfinite)(shape))
        { // Any finite value > 0 is OK.
          if (shape > 0)
          {
            return true;
          }
          else
          {
            *result = policies::raise_domain_error<RealType>(
              function,
              "Shape parameter is %1%, but must be > 0!", shape, pol);
            return false;
          }
        }
        else
        { // Not finite.
          *result = policies::raise_domain_error<RealType>(
            function,
            "Shape parameter is %1%, but must be finite!", shape, pol);
          return false;
        }
      } // bool check_pareto_shape(

      template <class RealType, class Policy>
      inline bool check_pareto_x(
        const char* function,
        RealType const& x,
        RealType* result, const Policy& pol)
      {
        if((boost::math::isfinite)(x))
        { //
          if (x > 0)
          {
            return true;
          }
          else
          {
            *result = policies::raise_domain_error<RealType>(
              function,
              "x parameter is %1%, but must be > 0 !", x, pol);
            return false;
          }
        }
        else
        { // Not finite..
          *result = policies::raise_domain_error<RealType>(
            function,
            "x parameter is %1%, but must be finite!", x, pol);
          return false;
        }
      } // bool check_pareto_x

      template <class RealType, class Policy>
      inline bool check_pareto( // distribution parameters.
        const char* function,
        RealType scale,
        RealType shape,
        RealType* result, const Policy& pol)
      {
        return check_pareto_scale(function, scale, result, pol)
           && check_pareto_shape(function, shape, result, pol);
      } // bool check_pareto(

    } // namespace detail

    template <class RealType = double, class Policy = policies::policy<> >
    class pareto_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      pareto_distribution(RealType l_scale = 1, RealType l_shape = 1)
        : m_scale(l_scale), m_shape(l_shape)
      { // Constructor.
        RealType result = 0;
        detail::check_pareto("boost::math::pareto_distribution<%1%>::pareto_distribution", l_scale, l_shape, &result, Policy());
      }

      RealType scale()const
      { // AKA Xm and Wolfram b and beta
        return m_scale;
      }

      RealType shape()const
      { // AKA k and Wolfram a and alpha
        return m_shape;
      }
    private:
      // Data members:
      RealType m_scale;  // distribution scale (xm) or beta
      RealType m_shape;  // distribution shape (k) or alpha
    };

    typedef pareto_distribution<double> pareto; // Convenience to allow pareto(2., 3.);

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const pareto_distribution<RealType, Policy>& /*dist*/)
    { // Range of permissible values for random variable x.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // scale zero to + infinity.
    } // range

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const pareto_distribution<RealType, Policy>& dist)
    { // Range of supported values for random variable x.
      // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(dist.scale(), max_value<RealType>() ); // scale to + infinity.
    } // support

    template <class RealType, class Policy>
    inline RealType pdf(const pareto_distribution<RealType, Policy>& dist, const RealType& x)
    {
      BOOST_MATH_STD_USING  // for ADL of std function pow.
      static const char* function = "boost::math::pdf(const pareto_distribution<%1%>&, %1%)";
      RealType scale = dist.scale();
      RealType shape = dist.shape();
      RealType result = 0;
      if(false == (detail::check_pareto_x(function, x, &result, Policy())
         && detail::check_pareto(function, scale, shape, &result, Policy())))
         return result;
      if (x < scale)
      { // regardless of shape, pdf is zero (or should be disallow x < scale and throw an exception?).
        return 0;
      }
      result = shape * pow(scale, shape) / pow(x, shape+1);
      return result;
    } // pdf

    template <class RealType, class Policy>
    inline RealType cdf(const pareto_distribution<RealType, Policy>& dist, const RealType& x)
    {
      BOOST_MATH_STD_USING  // for ADL of std function pow.
      static const char* function = "boost::math::cdf(const pareto_distribution<%1%>&, %1%)";
      RealType scale = dist.scale();
      RealType shape = dist.shape();
      RealType result = 0;

      if(false == (detail::check_pareto_x(function, x, &result, Policy())
         && detail::check_pareto(function, scale, shape, &result, Policy())))
         return result;

      if (x <= scale)
      { // regardless of shape, cdf is zero.
        return 0;
      }

      // result = RealType(1) - pow((scale / x), shape);
      result = -boost::math::powm1(scale/x, shape, Policy()); // should be more accurate.
      return result;
    } // cdf

    template <class RealType, class Policy>
    inline RealType quantile(const pareto_distribution<RealType, Policy>& dist, const RealType& p)
    {
      BOOST_MATH_STD_USING  // for ADL of std function pow.
      static const char* function = "boost::math::quantile(const pareto_distribution<%1%>&, %1%)";
      RealType result = 0;
      RealType scale = dist.scale();
      RealType shape = dist.shape();
      if(false == (detail::check_probability(function, p, &result, Policy())
           && detail::check_pareto(function, scale, shape, &result, Policy())))
      {
        return result;
      }
      if (p == 0)
      {
        return scale; // x must be scale (or less).
      }
      if (p == 1)
      {
        return policies::raise_overflow_error<RealType>(function, 0, Policy()); // x = + infinity.
      }
      result = scale /
        (pow((1 - p), 1 / shape));
      // K. Krishnamoorthy,  ISBN 1-58488-635-8 eq 23.1.3
      return result;
    } // quantile

    template <class RealType, class Policy>
    inline RealType cdf(const complemented2_type<pareto_distribution<RealType, Policy>, RealType>& c)
    {
       BOOST_MATH_STD_USING  // for ADL of std function pow.
       static const char* function = "boost::math::cdf(const pareto_distribution<%1%>&, %1%)";
       RealType result = 0;
       RealType x = c.param;
       RealType scale = c.dist.scale();
       RealType shape = c.dist.shape();
       if(false == (detail::check_pareto_x(function, x, &result, Policy())
           && detail::check_pareto(function, scale, shape, &result, Policy())))
         return result;

       if (x <= scale)
       { // regardless of shape, cdf is zero, and complement is unity.
         return 1;
       }
       result = pow((scale/x), shape);

       return result;
    } // cdf complement

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<pareto_distribution<RealType, Policy>, RealType>& c)
    {
      BOOST_MATH_STD_USING  // for ADL of std function pow.
      static const char* function = "boost::math::quantile(const pareto_distribution<%1%>&, %1%)";
      RealType result = 0;
      RealType q = c.param;
      RealType scale = c.dist.scale();
      RealType shape = c.dist.shape();
      if(false == (detail::check_probability(function, q, &result, Policy())
           && detail::check_pareto(function, scale, shape, &result, Policy())))
      {
        return result;
      }
      if (q == 1)
      {
        return scale; // x must be scale (or less).
      }
      if (q == 0)
      {
         return policies::raise_overflow_error<RealType>(function, 0, Policy()); // x = + infinity.
      }
      result = scale / (pow(q, 1 / shape));
      // K. Krishnamoorthy,  ISBN 1-58488-635-8 eq 23.1.3
      return result;
    } // quantile complement

    template <class RealType, class Policy>
    inline RealType mean(const pareto_distribution<RealType, Policy>& dist)
    {
      RealType result = 0;
      static const char* function = "boost::math::mean(const pareto_distribution<%1%>&, %1%)";
      if(false == detail::check_pareto(function, dist.scale(), dist.shape(), &result, Policy()))
      {
        return result;
      }
      if (dist.shape() > RealType(1))
      {
        return dist.shape() * dist.scale() / (dist.shape() - 1);
      }
      else
      {
        using boost::math::tools::max_value;
        return max_value<RealType>(); // +infinity.
      }
    } // mean

    template <class RealType, class Policy>
    inline RealType mode(const pareto_distribution<RealType, Policy>& dist)
    {
      return dist.scale();
    } // mode

    template <class RealType, class Policy>
    inline RealType median(const pareto_distribution<RealType, Policy>& dist)
    {
      RealType result = 0;
      static const char* function = "boost::math::median(const pareto_distribution<%1%>&, %1%)";
      if(false == detail::check_pareto(function, dist.scale(), dist.shape(), &result, Policy()))
      {
        return result;
      }
      BOOST_MATH_STD_USING
      return dist.scale() * pow(RealType(2), (1/dist.shape()));
    } // median

    template <class RealType, class Policy>
    inline RealType variance(const pareto_distribution<RealType, Policy>& dist)
    {
      RealType result = 0;
      RealType scale = dist.scale();
      RealType shape = dist.shape();
      static const char* function = "boost::math::variance(const pareto_distribution<%1%>&, %1%)";
      if(false == detail::check_pareto(function, scale, shape, &result, Policy()))
      {
        return result;
      }
      if (shape > 2)
      {
        result = (scale * scale * shape) /
         ((shape - 1) *  (shape - 1) * (shape - 2));
      }
      else
      {
        result = policies::raise_domain_error<RealType>(
          function,
          "variance is undefined for shape <= 2, but got %1%.", dist.shape(), Policy());
      }
      return result;
    } // variance

    template <class RealType, class Policy>
    inline RealType skewness(const pareto_distribution<RealType, Policy>& dist)
    {
      BOOST_MATH_STD_USING
      RealType result = 0;
      RealType shape = dist.shape();
      static const char* function = "boost::math::pdf(const pareto_distribution<%1%>&, %1%)";
      if(false == detail::check_pareto(function, dist.scale(), shape, &result, Policy()))
      {
        return result;
      }
      if (shape > 3)
      {
        result = sqrt((shape - 2) / shape) *
          2 * (shape + 1) /
          (shape - 3);
      }
      else
      {
        result = policies::raise_domain_error<RealType>(
          function,
          "skewness is undefined for shape <= 3, but got %1%.", dist.shape(), Policy());
      }
      return result;
    } // skewness

    template <class RealType, class Policy>
    inline RealType kurtosis(const pareto_distribution<RealType, Policy>& dist)
    {
      RealType result = 0;
      RealType shape = dist.shape();
      static const char* function = "boost::math::pdf(const pareto_distribution<%1%>&, %1%)";
      if(false == detail::check_pareto(function, dist.scale(), shape, &result, Policy()))
      {
        return result;
      }
      if (shape > 4)
      {
        result = 3 * ((shape - 2) * (3 * shape * shape + shape + 2)) /
          (shape * (shape - 3) * (shape - 4));
      }
      else
      {
        result = policies::raise_domain_error<RealType>(
          function,
          "kurtosis_excess is undefined for shape <= 4, but got %1%.", shape, Policy());
      }
      return result;
    } // kurtosis

    template <class RealType, class Policy>
    inline RealType kurtosis_excess(const pareto_distribution<RealType, Policy>& dist)
    {
      RealType result = 0;
      RealType shape = dist.shape();
      static const char* function = "boost::math::pdf(const pareto_distribution<%1%>&, %1%)";
      if(false == detail::check_pareto(function, dist.scale(), shape, &result, Policy()))
      {
        return result;
      }
      if (shape > 4)
      {
        result = 6 * ((shape * shape * shape) + (shape * shape) - 6 * shape - 2) /
          (shape * (shape - 3) * (shape - 4));
      }
      else
      {
        result = policies::raise_domain_error<RealType>(
          function,
          "kurtosis_excess is undefined for shape <= 4, but got %1%.", dist.shape(), Policy());
      }
      return result;
    } // kurtosis_excess

    template <class RealType, class Policy>
    inline RealType entropy(const pareto_distribution<RealType, Policy>& dist)
    {
      using std::log;
      RealType xm = dist.scale();
      RealType alpha = dist.shape();
      return log(xm/alpha) + 1 + 1/alpha;
    }

    } // namespace math
  } // namespace boost

  // This include must be at the end, *after* the accessors
  // for this distribution have been defined, in order to
  // keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_PARETO_HPP



/* pareto.hpp
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
*/