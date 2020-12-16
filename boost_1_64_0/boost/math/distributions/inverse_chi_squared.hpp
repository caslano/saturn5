// Copyright John Maddock 2010.
// Copyright Paul A. Bristow 2010.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_INVERSE_CHI_SQUARED_HPP
#define BOOST_MATH_DISTRIBUTIONS_INVERSE_CHI_SQUARED_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp> // for incomplete beta.
#include <boost/math/distributions/complement.hpp> // for complements.
#include <boost/math/distributions/detail/common_error_handling.hpp> // for error checks.
#include <boost/math/special_functions/fpclassify.hpp> // for isfinite

// See http://en.wikipedia.org/wiki/Scaled-inverse-chi-square_distribution
// for definitions of this scaled version.
// See http://en.wikipedia.org/wiki/Inverse-chi-square_distribution
// for unscaled version.

// http://reference.wolfram.com/mathematica/ref/InverseChiSquareDistribution.html
// Weisstein, Eric W. "Inverse Chi-Squared Distribution." From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/InverseChi-SquaredDistribution.html

#include <utility>

namespace boost{ namespace math{

namespace detail
{
  template <class RealType, class Policy>
  inline bool check_inverse_chi_squared( // Check both distribution parameters.
        const char* function,
        RealType degrees_of_freedom, // degrees_of_freedom (aka nu).
        RealType scale,  // scale (aka sigma^2)
        RealType* result,
        const Policy& pol)
  {
     return check_scale(function, scale, result, pol)
       && check_df(function, degrees_of_freedom,
       result, pol);
  } // bool check_inverse_chi_squared
} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class inverse_chi_squared_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   inverse_chi_squared_distribution(RealType df, RealType l_scale) : m_df(df), m_scale (l_scale)
   {
      RealType result;
      detail::check_df(
         "boost::math::inverse_chi_squared_distribution<%1%>::inverse_chi_squared_distribution",
         m_df, &result, Policy())
         && detail::check_scale(
"boost::math::inverse_chi_squared_distribution<%1%>::inverse_chi_squared_distribution",
         m_scale, &result,  Policy());
   } // inverse_chi_squared_distribution constructor 

   inverse_chi_squared_distribution(RealType df = 1) : m_df(df)
   {
      RealType result;
      m_scale = 1 / m_df ; // Default scale = 1 / degrees of freedom (Wikipedia definition 1).
      detail::check_df(
         "boost::math::inverse_chi_squared_distribution<%1%>::inverse_chi_squared_distribution",
         m_df, &result, Policy());
   } // inverse_chi_squared_distribution

   RealType degrees_of_freedom()const
   {
      return m_df; // aka nu
   }
   RealType scale()const
   {
      return m_scale;  // aka xi
   }

   // Parameter estimation:  NOT implemented yet.
   //static RealType find_degrees_of_freedom(
   //   RealType difference_from_variance,
   //   RealType alpha,
   //   RealType beta,
   //   RealType variance,
   //   RealType hint = 100);

private:
   // Data members:
   RealType m_df;  // degrees of freedom are treated as a real number.
   RealType m_scale;  // distribution scale.

}; // class chi_squared_distribution

typedef inverse_chi_squared_distribution<double> inverse_chi_squared;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const inverse_chi_squared_distribution<RealType, Policy>& /*dist*/)
{  // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // 0 to + infinity.
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const inverse_chi_squared_distribution<RealType, Policy>& /*dist*/)
{  // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   return std::pair<RealType, RealType>(static_cast<RealType>(0), tools::max_value<RealType>()); // 0 to + infinity.
}

template <class RealType, class Policy>
RealType pdf(const inverse_chi_squared_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions.
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();
   RealType error_result;

   static const char* function = "boost::math::pdf(const inverse_chi_squared_distribution<%1%>&, %1%)";

   if(false == detail::check_inverse_chi_squared
     (function, df, scale, &error_result, Policy())
     )
   { // Bad distribution.
      return error_result;
   }
   if((x < 0) || !(boost::math::isfinite)(x))
   { // Bad x.
      return policies::raise_domain_error<RealType>(
         function, "inverse Chi Square parameter was %1%, but must be >= 0 !", x, Policy());
   }

   if(x == 0)
   { // Treat as special case.
     return 0;
   }
   // Wikipedia scaled inverse chi sq (df, scale) related to inv gamma (df/2, df * scale /2) 
   // so use inverse gamma pdf with shape = df/2, scale df * scale /2 
   // RealType shape = df /2; // inv_gamma shape
   // RealType scale = df * scale/2; // inv_gamma scale
   // RealType result = gamma_p_derivative(shape, scale / x, Policy()) * scale / (x * x);
   RealType result = df * scale/2 / x;
   if(result < tools::min_value<RealType>())
      return 0; // Random variable is near enough infinite.
   result = gamma_p_derivative(df/2, result, Policy()) * df * scale/2;
   if(result != 0) // prevent 0 / 0,  gamma_p_derivative -> 0 faster than x^2
      result /= (x * x);
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const inverse_chi_squared_distribution<RealType, Policy>& dist, const RealType& x)
{
   static const char* function = "boost::math::cdf(const inverse_chi_squared_distribution<%1%>&, %1%)";
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();
   RealType error_result;

   if(false ==
       detail::check_inverse_chi_squared(function, df, scale, &error_result, Policy())
     )
   { // Bad distribution.
      return error_result;
   }
   if((x < 0) || !(boost::math::isfinite)(x))
   { // Bad x.
      return policies::raise_domain_error<RealType>(
         function, "inverse Chi Square parameter was %1%, but must be >= 0 !", x, Policy());
   }
   if (x == 0)
   { // Treat zero as a special case.
     return 0;
   }
   // RealType shape = df /2; // inv_gamma shape,
   // RealType scale = df * scale/2; // inv_gamma scale,
   // result = boost::math::gamma_q(shape, scale / x, Policy()); // inverse_gamma code.
   return boost::math::gamma_q(df / 2, (df * (scale / 2)) / x, Policy());
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const inverse_chi_squared_distribution<RealType, Policy>& dist, const RealType& p)
{
   using boost::math::gamma_q_inv;
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();

   static const char* function = "boost::math::quantile(const inverse_chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false == detail::check_df(
         function, df, &error_result, Policy())
         && detail::check_probability(
            function, p, &error_result, Policy()))
   {
      return error_result;
   }
   if(false == detail::check_probability(
            function, p, &error_result, Policy()))
   {
      return error_result;
   }
   // RealType shape = df /2; // inv_gamma shape,
   // RealType scale = df * scale/2; // inv_gamma scale,
   // result = scale / gamma_q_inv(shape, p, Policy());
      RealType result = gamma_q_inv(df /2, p, Policy());
      if(result == 0)
         return policies::raise_overflow_error<RealType, Policy>(function, "Random variable is infinite.", Policy());
      result = df * (scale / 2) / result;
      return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<inverse_chi_squared_distribution<RealType, Policy>, RealType>& c)
{
   using boost::math::gamma_q_inv;
   RealType const& df = c.dist.degrees_of_freedom();
   RealType const& scale = c.dist.scale();
   RealType const& x = c.param;
   static const char* function = "boost::math::cdf(const inverse_chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false == detail::check_df(
         function, df, &error_result, Policy()))
   {
      return error_result;
   }
   if (x == 0)
   { // Treat zero as a special case.
     return 1;
   }
   if((x < 0) || !(boost::math::isfinite)(x))
   {
      return policies::raise_domain_error<RealType>(
         function, "inverse Chi Square parameter was %1%, but must be > 0 !", x, Policy());
   }
   // RealType shape = df /2; // inv_gamma shape,
   // RealType scale = df * scale/2; // inv_gamma scale,
   // result = gamma_p(shape, scale/c.param, Policy()); use inv_gamma.

   return gamma_p(df / 2, (df * scale/2) / x, Policy()); // OK
} // cdf(complemented

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<inverse_chi_squared_distribution<RealType, Policy>, RealType>& c)
{
   using boost::math::gamma_q_inv;

   RealType const& df = c.dist.degrees_of_freedom();
   RealType const& scale = c.dist.scale();
   RealType const& q = c.param;
   static const char* function = "boost::math::quantile(const inverse_chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false == detail::check_df(function, df, &error_result, Policy()))
   {
      return error_result;
   }
   if(false == detail::check_probability(function, q, &error_result, Policy()))
   {
      return error_result;
   }
   // RealType shape = df /2; // inv_gamma shape,
   // RealType scale = df * scale/2; // inv_gamma scale,
   // result = scale / gamma_p_inv(shape, q, Policy());  // using inv_gamma.
   RealType result = gamma_p_inv(df/2, q, Policy());
   if(result == 0)
      return policies::raise_overflow_error<RealType, Policy>(function, "Random variable is infinite.", Policy());
   result = (df * scale / 2) / result;
   return result;
} // quantile(const complement

template <class RealType, class Policy>
inline RealType mean(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{ // Mean of inverse Chi-Squared distribution.
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();

   static const char* function = "boost::math::mean(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 2)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a mode for degrees of freedom > 2, but got degrees of freedom = %1%.",
         df, Policy());
  return (df * scale) / (df - 2);
} // mean

template <class RealType, class Policy>
inline RealType variance(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{ // Variance of inverse Chi-Squared distribution.
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();
   static const char* function = "boost::math::variance(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 4)
   {
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a variance for degrees of freedom > 4, but got degrees of freedom = %1%.",
         df, Policy());
   }
   return 2 * df * df * scale * scale / ((df - 2)*(df - 2) * (df - 4));
} // variance

template <class RealType, class Policy>
inline RealType mode(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{ // mode is not defined in Mathematica.
  // See Discussion section http://en.wikipedia.org/wiki/Talk:Scaled-inverse-chi-square_distribution
  // for origin of the formula used below.

   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();
   static const char* function = "boost::math::mode(const inverse_chi_squared_distribution<%1%>&)";
   if(df < 0)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a mode for degrees of freedom >= 0, but got degrees of freedom = %1%.",
         df, Policy());
   return (df * scale) / (df + 2);
}

//template <class RealType, class Policy>
//inline RealType median(const inverse_chi_squared_distribution<RealType, Policy>& dist)
//{ // Median is given by Quantile[dist, 1/2]
//   RealType df = dist.degrees_of_freedom();
//   if(df <= 1)
//      return tools::domain_error<RealType>(
//         BOOST_CURRENT_FUNCTION,
//         "The inverse_Chi-Squared distribution only has a median for degrees of freedom >= 0, but got degrees of freedom = %1%.",
//         df);
//   return df;
//}
// Now implemented via quantile(half) in derived accessors.

template <class RealType, class Policy>
inline RealType skewness(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING // For ADL
   RealType df = dist.degrees_of_freedom();
   static const char* function = "boost::math::skewness(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 6)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a skewness for degrees of freedom > 6, but got degrees of freedom = %1%.",
         df, Policy());

   return 4 * sqrt (2 * (df - 4)) / (df - 6);  // Not a function of scale.
}

template <class RealType, class Policy>
inline RealType kurtosis(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{
   RealType df = dist.degrees_of_freedom();
   static const char* function = "boost::math::kurtosis(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 8)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a kurtosis for degrees of freedom > 8, but got degrees of freedom = %1%.",
         df, Policy());

   return kurtosis_excess(dist) + 3;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{
   RealType df = dist.degrees_of_freedom();
   static const char* function = "boost::math::kurtosis(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 8)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a kurtosis excess for degrees of freedom > 8, but got degrees of freedom = %1%.",
         df, Policy());

   return 12 * (5 * df - 22) / ((df - 6 )*(df - 8));  // Not a function of scale.
}

//
// Parameter estimation comes last:
//

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_DISTRIBUTIONS_INVERSE_CHI_SQUARED_HPP

/* inverse_chi_squared.hpp
2gJuHYeeH50qizhvlv2xNwX1o4Uqb2d3CnTuTiY00YKZ65xkeI7ycxnjxz2mPCbMyPVgaYWR68GQNbXRdZ9+c3V+ndWTlE+00sz608IK6E9D48YheS3lrI86P5a+B59DJh+hkvfgzUomQex85St7Ffxckmjfh52p+t3mLAPsA1bRcvDj6c5cZUg/n0cb80eey6qY2zBZuBUHypCt2p+sWnuTp+dky75uPP+cQxfhaOd/peRvQOtCfpjLkISpv4EkDPoyHPvDnVIyNc39LoVuPaiKmbFcFbvKFbJcqOQeJt6mYmIsT+I34nul6kOdH845a5I+fb9EhynxDr1fEj/q0r523HB7X+YljnHZ52h7aBtkpUwGOin1wQlMTA/KI/LBe0kPlL1mAh1vohOXvinaEJwyzv3Dv3ktA91GUOcbGO6Zya/MFxa/CWvss8bvd+03Sff7z5V4l7QzXlAyR9njPVbez9J2VVFELqjrUXIfWztD9N3TdTy+U+ej9fvmY2WvJe0Eeh6UvTW1Ql3ckNFu6cqtqr52ri5jH6jzrULjRfKdOsvnlMyHVkvktpFj9nftsca8N5tSV9n9U/6Ce4PtgePSHgjuEbk1IWDuxmzQRuqYctoAl60p3Qawy0EtKQeGNQ5cZVjuI+Xxk9tC59Ge1vbQNTamkB77yAqA7w7SyTWPrAktn9Pn5qr8fFuVy6mmMil+PA65abo/9Jg6dy72pqYyid/I1jUI7t9I+KR3qrLHafu0kHr0YHNLHYOlHh2A+TCTtN4emjZWYJA2rt13LGM58ozPHX4jX0NEZCPWZSUF9bHKX23eXlGq7M1oRljNpe+22vml53mLzNLm0m8bl+iPSy3dZ+v6puMwr6th50EtyYMwZU7F/z1bTtLkzPfnW1jqGC/ty3GYPdyfne58ZxeD0PoOV8e37ZNKfqS5/pO8tfPnMOnO5ZqNVd9xN4PuTI2XKfN5jDLmhTx/Ei/nc3OqtczV5EJ14fkwnno9bW1oGudlL3GXFf1eba9km5vSRzhl19F3qPPJxnKn/Wodh6o/tD45U52v61nJHXvPitZ1Z5HtjpvPqm+qt3W8xwT86/b3KWWfSkricEUGW65yO869qG2dS5gFVrZum42+Q9ZRkO/Xnkq2gcfxDtDPwkrO4YNYDtLfA3nKLVG/F14Ru3yTyrULSEcK3wRtrJFQvXP0ucb2OUO6U0LeGbpfXp1fypsGnbyk4Tbc+ItLS2Lb2vw+kfh2V7JNPd257lGVbmdcfEo/U9QCOcpUE7sMRxe854+rqstx/8TI3zFR5bxjmtzhescYnu04w/skf23o+2SFy77HZX9b213fnm1Kv29+adcNd5Q8N6pBod44lrofb4R/54g/j8iFvnN231HmOwe/FXvnvOF657xheOcMbidr/cic5f6YrzN5Ju90pU/eOq66z5RG/Eb+ztGyYd4tg+8MvluilcwfZCwLMdL9JnadepD7tKctc6RVe+c80ztHyRxHJl2V2dr++Grmd05cBPs2O+rZcO8cFTfii5uKb0i++9tLfSzvnEzMW4RZ4M53eevIuBXOKVf9zrlWyZ9jXhtE8raC75OQdHJNY/zzuwaEBxBwY+FpErE/NP556q1i6JNJkjGBf1fyjX2xPq+uf4qV21FvE1vfY2V5g/XPgbtwp5Til7jJtbhye/w60o17+WMUzXp3xj1xzr9OjRf0nfB63e8k/c1wUl1jOPmYgsENW1/8EUvvQ7x1N3oK2PGshvUsYag6Wt4TjL9S5W02sqTFm0UaFzIS+XNysQljrzI9+1Q+KA3G+sD4J5+VRh/nIEddv0Df/yUqnCpcEbsjDp1xu5Zn5gDfNJ0Z+XQtfaQ=
*/