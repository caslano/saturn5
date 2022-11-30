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

    #ifdef __cpp_deduction_guides
    template <class RealType>
    pareto_distribution(RealType)->pareto_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    template <class RealType>
    pareto_distribution(RealType,RealType)->pareto_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    #endif


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