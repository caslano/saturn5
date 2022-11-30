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

#ifdef _MSC_VER
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

#ifdef __cpp_deduction_guides
template <class RealType>
students_t_distribution(RealType)->students_t_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

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
   std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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

#ifdef _MSC_VER
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