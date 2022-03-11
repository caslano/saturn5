//  Copyright John Maddock 2006.
//  Copyright Paul A. Bristow 2006, 2012, 2017.
//  Copyright Thomas Mang 2012.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_STUDENTS_T_HPP
#define BOOST_STATS_STUDENTS_T_HPP

// http://en.wikipedia.org/wiki/Student%27s_t_distribution
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3664.htm

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/beta.hpp> // for ibeta(a, b, x).
#include <boost/math/special_functions/digamma.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/normal.hpp> 

#include <utility>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

namespace boost { namespace math {

template <class RealType = double, class Policy = policies::policy<> >
class students_t_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   students_t_distribution(RealType df) : df_(df)
   { // Constructor.
      RealType result;
      detail::check_df_gt0_to_inf( // Checks that df > 0 or df == inf.
         "boost::math::students_t_distribution<%1%>::students_t_distribution", df_, &result, Policy());
   } // students_t_distribution

   RealType degrees_of_freedom()const
   {
      return df_;
   }

   // Parameter estimation:
   static RealType find_degrees_of_freedom(
      RealType difference_from_mean,
      RealType alpha,
      RealType beta,
      RealType sd,
      RealType hint = 100);

private:
   // Data member:
   RealType df_;  // degrees of freedom is a real number > 0 or +infinity.
};

typedef students_t_distribution<double> students_t; // Convenience typedef for double version.

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const students_t_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
  // Now including infinity.
   using boost::math::tools::max_value;
   //return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>());
   return std::pair<RealType, RealType>(((::std::numeric_limits<RealType>::is_specialized & ::std::numeric_limits<RealType>::has_infinity) ? -std::numeric_limits<RealType>::infinity() : -max_value<RealType>()), ((::std::numeric_limits<RealType>::is_specialized & ::std::numeric_limits<RealType>::has_infinity) ? +std::numeric_limits<RealType>::infinity() : +max_value<RealType>()));
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const students_t_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
  // Now including infinity.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   //return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>());
   return std::pair<RealType, RealType>(((::std::numeric_limits<RealType>::is_specialized & ::std::numeric_limits<RealType>::has_infinity) ? -std::numeric_limits<RealType>::infinity() : -max_value<RealType>()), ((::std::numeric_limits<RealType>::is_specialized & ::std::numeric_limits<RealType>::has_infinity) ? +std::numeric_limits<RealType>::infinity() : +max_value<RealType>()));
}

template <class RealType, class Policy>
inline RealType pdf(const students_t_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_FPU_EXCEPTION_GUARD
   BOOST_MATH_STD_USING  // for ADL of std functions.

   RealType error_result;
   if(false == detail::check_x_not_NaN(
      "boost::math::pdf(const students_t_distribution<%1%>&, %1%)", x, &error_result, Policy()))
      return error_result;
   RealType df = dist.degrees_of_freedom();
   if(false == detail::check_df_gt0_to_inf( // Check that df > 0 or == +infinity.
      "boost::math::pdf(const students_t_distribution<%1%>&, %1%)", df, &error_result, Policy()))
      return error_result;

   RealType result;
   if ((boost::math::isinf)(x))
   { // - or +infinity.
     result = static_cast<RealType>(0);
     return result;
   }
   RealType limit = policies::get_epsilon<RealType, Policy>();
   // Use policies so that if policy requests lower precision, 
   // then get the normal distribution approximation earlier.
   limit = static_cast<RealType>(1) / limit; // 1/eps
   // for 64-bit double 1/eps = 4503599627370496
   if (df > limit)
   { // Special case for really big degrees_of_freedom > 1 / eps 
     // - use normal distribution which is much faster and more accurate.
     normal_distribution<RealType, Policy> n(0, 1); 
     result = pdf(n, x);
   }
   else
   { // 
     RealType basem1 = x * x / df;
     if(basem1 < 0.125)
     {
        result = exp(-boost::math::log1p(basem1, Policy()) * (1+df) / 2);
     }
     else
     {
        result = pow(1 / (1 + basem1), (df + 1) / 2);
     }
     result /= sqrt(df) * boost::math::beta(df / 2, RealType(0.5f), Policy());
   }
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const students_t_distribution<RealType, Policy>& dist, const RealType& x)
{
   RealType error_result;
   // degrees_of_freedom > 0 or infinity check:
   RealType df = dist.degrees_of_freedom();
   if (false == detail::check_df_gt0_to_inf(  // Check that df > 0 or == +infinity.
     "boost::math::cdf(const students_t_distribution<%1%>&, %1%)", df, &error_result, Policy()))
   {
     return error_result;
   }
   // Check for bad x first.
   if(false == detail::check_x_not_NaN(
      "boost::math::cdf(const students_t_distribution<%1%>&, %1%)", x, &error_result, Policy()))
   { 
      return error_result;
   }
   if (x == 0)
   { // Special case with exact result.
     return static_cast<RealType>(0.5);
   }
   if ((boost::math::isinf)(x))
   { // x == - or + infinity, regardless of df.
     return ((x < 0) ? static_cast<RealType>(0) : static_cast<RealType>(1));
   }

   RealType limit = policies::get_epsilon<RealType, Policy>();
   // Use policies so that if policy requests lower precision, 
   // then get the normal distribution approximation earlier.
   limit = static_cast<RealType>(1) / limit; // 1/eps
   // for 64-bit double 1/eps = 4503599627370496
   if (df > limit)
   { // Special case for really big degrees_of_freedom > 1 / eps (perhaps infinite?)
     // - use normal distribution which is much faster and more accurate.
     normal_distribution<RealType, Policy> n(0, 1); 
     RealType result = cdf(n, x);
     return result;
   }
   else
   { // normal df case.
     //
     // Calculate probability of Student's t using the incomplete beta function.
     // probability = ibeta(degrees_of_freedom / 2, 1/2, degrees_of_freedom / (degrees_of_freedom + t*t))
     //
     // However when t is small compared to the degrees of freedom, that formula
     // suffers from rounding error, use the identity formula to work around
     // the problem:
     //
     // I[x](a,b) = 1 - I[1-x](b,a)
     //
     // and:
     //
     //     x = df / (df + t^2)
     //
     // so:
     //
     // 1 - x = t^2 / (df + t^2)
     //
     RealType x2 = x * x;
     RealType probability;
     if(df > 2 * x2)
     {
        RealType z = x2 / (df + x2);
        probability = ibetac(static_cast<RealType>(0.5), df / 2, z, Policy()) / 2;
     }
     else
     {
        RealType z = df / (df + x2);
        probability = ibeta(df / 2, static_cast<RealType>(0.5), z, Policy()) / 2;
     }
     return (x > 0 ? 1   - probability : probability);
  }
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const students_t_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING // for ADL of std functions
   //
   // Obtain parameters:
   RealType probability = p;
 
   // Check for domain errors:
   RealType df = dist.degrees_of_freedom();
   static const char* function = "boost::math::quantile(const students_t_distribution<%1%>&, %1%)";
   RealType error_result;
   if(false == (detail::check_df_gt0_to_inf( // Check that df > 0 or == +infinity.
      function, df, &error_result, Policy())
         && detail::check_probability(function, probability, &error_result, Policy())))
      return error_result;
   // Special cases, regardless of degrees_of_freedom.
   if (probability == 0)
      return -policies::raise_overflow_error<RealType>(function, 0, Policy());
   if (probability == 1)
     return policies::raise_overflow_error<RealType>(function, 0, Policy());
   if (probability == static_cast<RealType>(0.5))
     return 0;  //
   //
#if 0
   // This next block is disabled in favour of a faster method than
   // incomplete beta inverse, but code retained for future reference:
   //
   // Calculate quantile of Student's t using the incomplete beta function inverse:
   probability = (probability > 0.5) ? 1 - probability : probability;
   RealType t, x, y;
   x = ibeta_inv(degrees_of_freedom / 2, RealType(0.5), 2 * probability, &y);
   if(degrees_of_freedom * y > tools::max_value<RealType>() * x)
      t = tools::overflow_error<RealType>(function);
   else
      t = sqrt(degrees_of_freedom * y / x);
   //
   // Figure out sign based on the size of p:
   //
   if(p < 0.5)
      t = -t;

   return t;
#endif
   //
   // Depending on how many digits RealType has, this may forward
   // to the incomplete beta inverse as above.  Otherwise uses a
   // faster method that is accurate to ~15 digits everywhere
   // and a couple of epsilon at double precision and in the central 
   // region where most use cases will occur...
   //
   return boost::math::detail::fast_students_t_quantile(df, probability, Policy());
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<students_t_distribution<RealType, Policy>, RealType>& c)
{
   return cdf(c.dist, -c.param);
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<students_t_distribution<RealType, Policy>, RealType>& c)
{
   return -quantile(c.dist, c.param);
}

//
// Parameter estimation follows:
//
namespace detail{
//
// Functors for finding degrees of freedom:
//
template <class RealType, class Policy>
struct sample_size_func
{
   sample_size_func(RealType a, RealType b, RealType s, RealType d)
      : alpha(a), beta(b), ratio(s*s/(d*d)) {}

   RealType operator()(const RealType& df)
   {
      if(df <= tools::min_value<RealType>())
      { // 
         return 1;
      }
      students_t_distribution<RealType, Policy> t(df);
      RealType qa = quantile(complement(t, alpha));
      RealType qb = quantile(complement(t, beta));
      qa += qb;
      qa *= qa;
      qa *= ratio;
      qa -= (df + 1);
      return qa;
   }
   RealType alpha, beta, ratio;
};

}  // namespace detail

template <class RealType, class Policy>
RealType students_t_distribution<RealType, Policy>::find_degrees_of_freedom(
      RealType difference_from_mean,
      RealType alpha,
      RealType beta,
      RealType sd,
      RealType hint)
{
   static const char* function = "boost::math::students_t_distribution<%1%>::find_degrees_of_freedom";
   //
   // Check for domain errors:
   //
   RealType error_result;
   if(false == detail::check_probability(
      function, alpha, &error_result, Policy())
         && detail::check_probability(function, beta, &error_result, Policy()))
      return error_result;

   if(hint <= 0)
      hint = 1;

   detail::sample_size_func<RealType, Policy> f(alpha, beta, sd, difference_from_mean);
   tools::eps_tolerance<RealType> tol(policies::digits<RealType, Policy>());
   boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
   std::pair<RealType, RealType> r = tools::bracket_and_solve_root(f, hint, RealType(2), false, tol, max_iter, Policy());
   RealType result = r.first + (r.second - r.first) / 2;
   if(max_iter >= policies::get_max_root_iterations<Policy>())
   {
      return policies::raise_evaluation_error<RealType>(function, "Unable to locate solution in a reasonable time:"
         " either there is no answer to how many degrees of freedom are required"
         " or the answer is infinite.  Current best guess is %1%", result, Policy());
   }
   return result;
}

template <class RealType, class Policy>
inline RealType mode(const students_t_distribution<RealType, Policy>& /*dist*/)
{
  // Assume no checks on degrees of freedom are useful (unlike mean).
   return 0; // Always zero by definition.
}

template <class RealType, class Policy>
inline RealType median(const students_t_distribution<RealType, Policy>& /*dist*/)
{
   // Assume no checks on degrees of freedom are useful (unlike mean).
   return 0; // Always zero by definition.
}

// See section 5.1 on moments at  http://en.wikipedia.org/wiki/Student%27s_t-distribution

template <class RealType, class Policy>
inline RealType mean(const students_t_distribution<RealType, Policy>& dist)
{  // Revised for https://svn.boost.org/trac/boost/ticket/7177
   RealType df = dist.degrees_of_freedom();
   if(((boost::math::isnan)(df)) || (df <= 1) ) 
   { // mean is undefined for moment <= 1!
      return policies::raise_domain_error<RealType>(
      "boost::math::mean(students_t_distribution<%1%> const&, %1%)",
      "Mean is undefined for degrees of freedom < 1 but got %1%.", df, Policy());
      return std::numeric_limits<RealType>::quiet_NaN();
   }
   return 0;
} // mean

template <class RealType, class Policy>
inline RealType variance(const students_t_distribution<RealType, Policy>& dist)
{ // http://en.wikipedia.org/wiki/Student%27s_t-distribution
  // Revised for https://svn.boost.org/trac/boost/ticket/7177
  RealType df = dist.degrees_of_freedom();
  if ((boost::math::isnan)(df) || (df <= 2))
  { // NaN or undefined for <= 2.
     return policies::raise_domain_error<RealType>(
      "boost::math::variance(students_t_distribution<%1%> const&, %1%)",
      "variance is undefined for degrees of freedom <= 2, but got %1%.",
      df, Policy());
    return std::numeric_limits<RealType>::quiet_NaN(); // Undefined.
  }
  if ((boost::math::isinf)(df))
  { // +infinity.
    return 1;
  }
  RealType limit = policies::get_epsilon<RealType, Policy>();
  // Use policies so that if policy requests lower precision, 
  // then get the normal distribution approximation earlier.
  limit = static_cast<RealType>(1) / limit; // 1/eps
  // for 64-bit double 1/eps = 4503599627370496
  if (df > limit)
  { // Special case for really big degrees_of_freedom > 1 / eps.
    return 1;
  }
  else
  {
    return df / (df - 2);
  }
} // variance

template <class RealType, class Policy>
inline RealType skewness(const students_t_distribution<RealType, Policy>& dist)
{
    RealType df = dist.degrees_of_freedom();
   if( ((boost::math::isnan)(df)) || (dist.degrees_of_freedom() <= 3))
   { // Undefined for moment k = 3.
      return policies::raise_domain_error<RealType>(
         "boost::math::skewness(students_t_distribution<%1%> const&, %1%)",
         "Skewness is undefined for degrees of freedom <= 3, but got %1%.",
         dist.degrees_of_freedom(), Policy());
      return std::numeric_limits<RealType>::quiet_NaN();
   }
   return 0; // For all valid df, including infinity.
} // skewness

template <class RealType, class Policy>
inline RealType kurtosis(const students_t_distribution<RealType, Policy>& dist)
{
   RealType df = dist.degrees_of_freedom();
   if(((boost::math::isnan)(df)) || (df <= 4))
   { // Undefined or infinity for moment k = 4.
      return policies::raise_domain_error<RealType>(
       "boost::math::kurtosis(students_t_distribution<%1%> const&, %1%)",
       "Kurtosis is undefined for degrees of freedom <= 4, but got %1%.",
        df, Policy());
        return std::numeric_limits<RealType>::quiet_NaN(); // Undefined.
   }
   if ((boost::math::isinf)(df))
   { // +infinity.
     return 3;
   }
   RealType limit = policies::get_epsilon<RealType, Policy>();
   // Use policies so that if policy requests lower precision, 
   // then get the normal distribution approximation earlier.
   limit = static_cast<RealType>(1) / limit; // 1/eps
   // for 64-bit double 1/eps = 4503599627370496
   if (df > limit)
   { // Special case for really big degrees_of_freedom > 1 / eps.
     return 3;
   }
   else
   {
     //return 3 * (df - 2) / (df - 4); re-arranged to
     return 6 / (df - 4) + 3;
   }
} // kurtosis

template <class RealType, class Policy>
inline RealType kurtosis_excess(const students_t_distribution<RealType, Policy>& dist)
{
   // see http://mathworld.wolfram.com/Kurtosis.html

   RealType df = dist.degrees_of_freedom();
   if(((boost::math::isnan)(df)) || (df <= 4))
   { // Undefined or infinity for moment k = 4.
     return policies::raise_domain_error<RealType>(
       "boost::math::kurtosis_excess(students_t_distribution<%1%> const&, %1%)",
       "Kurtosis_excess is undefined for degrees of freedom <= 4, but got %1%.",
      df, Policy());
     return std::numeric_limits<RealType>::quiet_NaN(); // Undefined.
   }
   if ((boost::math::isinf)(df))
   { // +infinity.
     return 0;
   }
   RealType limit = policies::get_epsilon<RealType, Policy>();
   // Use policies so that if policy requests lower precision, 
   // then get the normal distribution approximation earlier.
   limit = static_cast<RealType>(1) / limit; // 1/eps
   // for 64-bit double 1/eps = 4503599627370496
   if (df > limit)
   { // Special case for really big degrees_of_freedom > 1 / eps.
     return 0;
   }
   else
   {
     return 6 / (df - 4);
   }
}

template <class RealType, class Policy>
inline RealType entropy(const students_t_distribution<RealType, Policy>& dist)
{
   using std::log;
   using std::sqrt;
   RealType v = dist.degrees_of_freedom();
   RealType vp1 = (v+1)/2;
   RealType vd2 = v/2;

   return vp1*(digamma(vp1) - digamma(vd2)) + log(sqrt(v)*beta(vd2, RealType(1)/RealType(2)));
}

} // namespace math
} // namespace boost

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_STUDENTS_T_HPP

/* students_t.hpp
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
*/