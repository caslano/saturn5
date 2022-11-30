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

#ifdef __cpp_deduction_guides
template <class RealType>
fisher_f_distribution(RealType,RealType)->fisher_f_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

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