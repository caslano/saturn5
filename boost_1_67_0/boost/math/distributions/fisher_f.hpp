// Copyright John Maddock 2006.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_FISHER_F_HPP
#define BOOST_MATH_DISTRIBUTIONS_FISHER_F_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/beta.hpp> // for incomplete beta.
#include <boost/math/distributions/complement.hpp> // complements
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks
#include <boost/math/special_functions/fpclassify.hpp>

#include <utility>

namespace boost{ namespace math{

template <class RealType = double, class Policy = policies::policy<> >
class fisher_f_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   fisher_f_distribution(const RealType& i, const RealType& j) : m_df1(i), m_df2(j)
   {
      static const char* function = "fisher_f_distribution<%1%>::fisher_f_distribution";
      RealType result;
      detail::check_df(
         function, m_df1, &result, Policy());
      detail::check_df(
         function, m_df2, &result, Policy());
   } // fisher_f_distribution

   RealType degrees_of_freedom1()const
   {
      return m_df1;
   }
   RealType degrees_of_freedom2()const
   {
      return m_df2;
   }

private:
   //
   // Data members:
   //
   RealType m_df1;  // degrees of freedom are a real number.
   RealType m_df2;  // degrees of freedom are a real number.
};

typedef fisher_f_distribution<double> fisher_f;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const fisher_f_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const fisher_f_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>());
}

template <class RealType, class Policy>
RealType pdf(const fisher_f_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions
   RealType df1 = dist.degrees_of_freedom1();
   RealType df2 = dist.degrees_of_freedom2();
   // Error check:
   RealType error_result = 0;
   static const char* function = "boost::math::pdf(fisher_f_distribution<%1%> const&, %1%)";
   if(false == (detail::check_df(
         function, df1, &error_result, Policy())
         && detail::check_df(
         function, df2, &error_result, Policy())))
      return error_result;

   if((x < 0) || !(boost::math::isfinite)(x))
   {
      return policies::raise_domain_error<RealType>(
         function, "Random variable parameter was %1%, but must be > 0 !", x, Policy());
   }

   if(x == 0)
   {
      // special cases:
      if(df1 < 2)
         return policies::raise_overflow_error<RealType>(
            function, 0, Policy());
      else if(df1 == 2)
         return 1;
      else
         return 0;
   }

   //
   // You reach this formula by direct differentiation of the
   // cdf expressed in terms of the incomplete beta.
   //
   // There are two versions so we don't pass a value of z
   // that is very close to 1 to ibeta_derivative: for some values
   // of df1 and df2, all the change takes place in this area.
   //
   RealType v1x = df1 * x;
   RealType result;
   if(v1x > df2)
   {
      result = (df2 * df1) / ((df2 + v1x) * (df2 + v1x));
      result *= ibeta_derivative(df2 / 2, df1 / 2, df2 / (df2 + v1x), Policy());
   }
   else
   {
      result = df2 + df1 * x;
      result = (result * df1 - x * df1 * df1) / (result * result);
      result *= ibeta_derivative(df1 / 2, df2 / 2, v1x / (df2 + v1x), Policy());
   }
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const fisher_f_distribution<RealType, Policy>& dist, const RealType& x)
{
   static const char* function = "boost::math::cdf(fisher_f_distribution<%1%> const&, %1%)";
   RealType df1 = dist.degrees_of_freedom1();
   RealType df2 = dist.degrees_of_freedom2();
   // Error check:
   RealType error_result = 0;
   if(false == detail::check_df(
         function, df1, &error_result, Policy())
         && detail::check_df(
         function, df2, &error_result, Policy()))
      return error_result;

   if((x < 0) || !(boost::math::isfinite)(x))
   {
      return policies::raise_domain_error<RealType>(
         function, "Random Variable parameter was %1%, but must be > 0 !", x, Policy());
   }

   RealType v1x = df1 * x;
   //
   // There are two equivalent formulas used here, the aim is
   // to prevent the final argument to the incomplete beta
   // from being too close to 1: for some values of df1 and df2
   // the rate of change can be arbitrarily large in this area,
   // whilst the value we're passing will have lost information
   // content as a result of being 0.999999something.  Better
   // to switch things around so we're passing 1-z instead.
   //
   return v1x > df2
      ? boost::math::ibetac(df2 / 2, df1 / 2, df2 / (df2 + v1x), Policy())
      : boost::math::ibeta(df1 / 2, df2 / 2, v1x / (df2 + v1x), Policy());
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const fisher_f_distribution<RealType, Policy>& dist, const RealType& p)
{
   static const char* function = "boost::math::quantile(fisher_f_distribution<%1%> const&, %1%)";
   RealType df1 = dist.degrees_of_freedom1();
   RealType df2 = dist.degrees_of_freedom2();
   // Error check:
   RealType error_result = 0;
   if(false == (detail::check_df(
            function, df1, &error_result, Policy())
         && detail::check_df(
            function, df2, &error_result, Policy())
         && detail::check_probability(
            function, p, &error_result, Policy())))
      return error_result;

   // With optimizations turned on, gcc wrongly warns about y being used
   // uninitialized unless we initialize it to something:
   RealType x, y(0);

   x = boost::math::ibeta_inv(df1 / 2, df2 / 2, p, &y, Policy());

   return df2 * x / (df1 * y);
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<fisher_f_distribution<RealType, Policy>, RealType>& c)
{
   static const char* function = "boost::math::cdf(fisher_f_distribution<%1%> const&, %1%)";
   RealType df1 = c.dist.degrees_of_freedom1();
   RealType df2 = c.dist.degrees_of_freedom2();
   RealType x = c.param;
   // Error check:
   RealType error_result = 0;
   if(false == detail::check_df(
         function, df1, &error_result, Policy())
         && detail::check_df(
         function, df2, &error_result, Policy()))
      return error_result;

   if((x < 0) || !(boost::math::isfinite)(x))
   {
      return policies::raise_domain_error<RealType>(
         function, "Random Variable parameter was %1%, but must be > 0 !", x, Policy());
   }

   RealType v1x = df1 * x;
   //
   // There are two equivalent formulas used here, the aim is
   // to prevent the final argument to the incomplete beta
   // from being too close to 1: for some values of df1 and df2
   // the rate of change can be arbitrarily large in this area,
   // whilst the value we're passing will have lost information
   // content as a result of being 0.999999something.  Better
   // to switch things around so we're passing 1-z instead.
   //
   return v1x > df2
      ? boost::math::ibeta(df2 / 2, df1 / 2, df2 / (df2 + v1x), Policy())
      : boost::math::ibetac(df1 / 2, df2 / 2, v1x / (df2 + v1x), Policy());
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<fisher_f_distribution<RealType, Policy>, RealType>& c)
{
   static const char* function = "boost::math::quantile(fisher_f_distribution<%1%> const&, %1%)";
   RealType df1 = c.dist.degrees_of_freedom1();
   RealType df2 = c.dist.degrees_of_freedom2();
   RealType p = c.param;
   // Error check:
   RealType error_result = 0;
   if(false == (detail::check_df(
            function, df1, &error_result, Policy())
         && detail::check_df(
            function, df2, &error_result, Policy())
         && detail::check_probability(
            function, p, &error_result, Policy())))
      return error_result;

   RealType x, y;

   x = boost::math::ibetac_inv(df1 / 2, df2 / 2, p, &y, Policy());

   return df2 * x / (df1 * y);
}

template <class RealType, class Policy>
inline RealType mean(const fisher_f_distribution<RealType, Policy>& dist)
{ // Mean of F distribution = v.
   static const char* function = "boost::math::mean(fisher_f_distribution<%1%> const&)";
   RealType df1 = dist.degrees_of_freedom1();
   RealType df2 = dist.degrees_of_freedom2();
   // Error check:
   RealType error_result = 0;
   if(false == detail::check_df(
            function, df1, &error_result, Policy())
         && detail::check_df(
            function, df2, &error_result, Policy()))
      return error_result;
   if(df2 <= 2)
   {
      return policies::raise_domain_error<RealType>(
         function, "Second degree of freedom was %1% but must be > 2 in order for the distribution to have a mean.", df2, Policy());
   }
   return df2 / (df2 - 2);
} // mean

template <class RealType, class Policy>
inline RealType variance(const fisher_f_distribution<RealType, Policy>& dist)
{ // Variance of F distribution.
   static const char* function = "boost::math::variance(fisher_f_distribution<%1%> const&)";
   RealType df1 = dist.degrees_of_freedom1();
   RealType df2 = dist.degrees_of_freedom2();
   // Error check:
   RealType error_result = 0;
   if(false == detail::check_df(
            function, df1, &error_result, Policy())
         && detail::check_df(
            function, df2, &error_result, Policy()))
      return error_result;
   if(df2 <= 4)
   {
      return policies::raise_domain_error<RealType>(
         function, "Second degree of freedom was %1% but must be > 4 in order for the distribution to have a valid variance.", df2, Policy());
   }
   return 2 * df2 * df2 * (df1 + df2 - 2) / (df1 * (df2 - 2) * (df2 - 2) * (df2 - 4));
} // variance

template <class RealType, class Policy>
inline RealType mode(const fisher_f_distribution<RealType, Policy>& dist)
{
   static const char* function = "boost::math::mode(fisher_f_distribution<%1%> const&)";
   RealType df1 = dist.degrees_of_freedom1();
   RealType df2 = dist.degrees_of_freedom2();
   // Error check:
   RealType error_result = 0;
   if(false == detail::check_df(
            function, df1, &error_result, Policy())
         && detail::check_df(
            function, df2, &error_result, Policy()))
      return error_result;
   if(df2 <= 2)
   {
      return policies::raise_domain_error<RealType>(
         function, "Second degree of freedom was %1% but must be > 2 in order for the distribution to have a mode.", df2, Policy());
   }
   return df2 * (df1 - 2) / (df1 * (df2 + 2));
}

//template <class RealType, class Policy>
//inline RealType median(const fisher_f_distribution<RealType, Policy>& dist)
//{ // Median of Fisher F distribution is not defined.
//  return tools::domain_error<RealType>(BOOST_CURRENT_FUNCTION, "Median is not implemented, result is %1%!", std::numeric_limits<RealType>::quiet_NaN());
//  } // median

// Now implemented via quantile(half) in derived accessors.

template <class RealType, class Policy>
inline RealType skewness(const fisher_f_distribution<RealType, Policy>& dist)
{
   static const char* function = "boost::math::skewness(fisher_f_distribution<%1%> const&)";
   BOOST_MATH_STD_USING // ADL of std names
   // See http://mathworld.wolfram.com/F-Distribution.html
   RealType df1 = dist.degrees_of_freedom1();
   RealType df2 = dist.degrees_of_freedom2();
   // Error check:
   RealType error_result = 0;
   if(false == detail::check_df(
            function, df1, &error_result, Policy())
         && detail::check_df(
            function, df2, &error_result, Policy()))
      return error_result;
   if(df2 <= 6)
   {
      return policies::raise_domain_error<RealType>(
         function, "Second degree of freedom was %1% but must be > 6 in order for the distribution to have a skewness.", df2, Policy());
   }
   return 2 * (df2 + 2 * df1 - 2) * sqrt((2 * df2 - 8) / (df1 * (df2 + df1 - 2))) / (df2 - 6);
}

template <class RealType, class Policy>
RealType kurtosis_excess(const fisher_f_distribution<RealType, Policy>& dist);

template <class RealType, class Policy>
inline RealType kurtosis(const fisher_f_distribution<RealType, Policy>& dist)
{
   return 3 + kurtosis_excess(dist);
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const fisher_f_distribution<RealType, Policy>& dist)
{
   static const char* function = "boost::math::kurtosis_excess(fisher_f_distribution<%1%> const&)";
   // See http://mathworld.wolfram.com/F-Distribution.html
   RealType df1 = dist.degrees_of_freedom1();
   RealType df2 = dist.degrees_of_freedom2();
   // Error check:
   RealType error_result = 0;
   if(false == detail::check_df(
            function, df1, &error_result, Policy())
         && detail::check_df(
            function, df2, &error_result, Policy()))
      return error_result;
   if(df2 <= 8)
   {
      return policies::raise_domain_error<RealType>(
         function, "Second degree of freedom was %1% but must be > 8 in order for the distribution to have a kurtosis.", df2, Policy());
   }
   RealType df2_2 = df2 * df2;
   RealType df1_2 = df1 * df1;
   RealType n = -16 + 20 * df2 - 8 * df2_2 + df2_2 * df2 + 44 * df1 - 32 * df2 * df1 + 5 * df2_2 * df1 - 22 * df1_2 + 5 * df2 * df1_2;
   n *= 12;
   RealType d = df1 * (df2 - 6) * (df2 - 8) * (df1 + df2 - 2);
   return n / d;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_DISTRIBUTIONS_FISHER_F_HPP

/* fisher_f.hpp
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
*/