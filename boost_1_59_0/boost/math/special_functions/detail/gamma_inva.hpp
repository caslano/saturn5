//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This is not a complete header file, it is included by gamma.hpp
// after it has defined it's definitions.  This inverts the incomplete
// gamma functions P and Q on the first parameter "a" using a generic
// root finding algorithm (TOMS Algorithm 748).
//

#ifndef BOOST_MATH_SP_DETAIL_GAMMA_INVA
#define BOOST_MATH_SP_DETAIL_GAMMA_INVA

#ifdef _MSC_VER
#pragma once
#endif

#include <cstdint>
#include <boost/math/tools/toms748_solve.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
struct gamma_inva_t
{
   gamma_inva_t(T z_, T p_, bool invert_) : z(z_), p(p_), invert(invert_) {}
   T operator()(T a)
   {
      return invert ? p - boost::math::gamma_q(a, z, Policy()) : boost::math::gamma_p(a, z, Policy()) - p;
   }
private:
   T z, p;
   bool invert;
};

template <class T, class Policy>
T inverse_poisson_cornish_fisher(T lambda, T p, T q, const Policy& pol)
{
   BOOST_MATH_STD_USING
   // mean:
   T m = lambda;
   // standard deviation:
   T sigma = sqrt(lambda);
   // skewness
   T sk = 1 / sigma;
   // kurtosis:
   // T k = 1/lambda;
   // Get the inverse of a std normal distribution:
   T x = boost::math::erfc_inv(p > q ? 2 * q : 2 * p, pol) * constants::root_two<T>();
   // Set the sign:
   if(p < 0.5)
      x = -x;
   T x2 = x * x;
   // w is correction term due to skewness
   T w = x + sk * (x2 - 1) / 6;
   /*
   // Add on correction due to kurtosis.
   // Disabled for now, seems to make things worse?
   //
   if(lambda >= 10)
      w += k * x * (x2 - 3) / 24 + sk * sk * x * (2 * x2 - 5) / -36;
   */
   w = m + sigma * w;
   return w > tools::min_value<T>() ? w : tools::min_value<T>();
}

template <class T, class Policy>
T gamma_inva_imp(const T& z, const T& p, const T& q, const Policy& pol)
{
   BOOST_MATH_STD_USING  // for ADL of std lib math functions
   //
   // Special cases first:
   //
   if(p == 0)
   {
      return policies::raise_overflow_error<T>("boost::math::gamma_p_inva<%1%>(%1%, %1%)", 0, Policy());
   }
   if(q == 0)
   {
      return tools::min_value<T>();
   }
   //
   // Function object, this is the functor whose root
   // we have to solve:
   //
   gamma_inva_t<T, Policy> f(z, (p < q) ? p : q, (p < q) ? false : true);
   //
   // Tolerance: full precision.
   //
   tools::eps_tolerance<T> tol(policies::digits<T, Policy>());
   //
   // Now figure out a starting guess for what a may be, 
   // we'll start out with a value that'll put p or q
   // right bang in the middle of their range, the functions
   // are quite sensitive so we should need too many steps
   // to bracket the root from there:
   //
   T guess;
   T factor = 8;
   if(z >= 1)
   {
      //
      // We can use the relationship between the incomplete 
      // gamma function and the poisson distribution to
      // calculate an approximate inverse, for large z
      // this is actually pretty accurate, but it fails badly
      // when z is very small.  Also set our step-factor according
      // to how accurate we think the result is likely to be:
      //
      guess = 1 + inverse_poisson_cornish_fisher(z, q, p, pol);
      if(z > 5)
      {
         if(z > 1000)
            factor = 1.01f;
         else if(z > 50)
            factor = 1.1f;
         else if(guess > 10)
            factor = 1.25f;
         else
            factor = 2;
         if(guess < 1.1)
            factor = 8;
      }
   }
   else if(z > 0.5)
   {
      guess = z * 1.2f;
   }
   else
   {
      guess = -0.4f / log(z);
   }
   //
   // Max iterations permitted:
   //
   std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
   //
   // Use our generic derivative-free root finding procedure.
   // We could use Newton steps here, taking the PDF of the
   // Poisson distribution as our derivative, but that's
   // even worse performance-wise than the generic method :-(
   //
   std::pair<T, T> r = bracket_and_solve_root(f, guess, factor, false, tol, max_iter, pol);
   if(max_iter >= policies::get_max_root_iterations<Policy>())
      return policies::raise_evaluation_error<T>("boost::math::gamma_p_inva<%1%>(%1%, %1%)", "Unable to locate the root within a reasonable number of iterations, closest approximation so far was %1%", r.first, pol);
   return (r.first + r.second) / 2;
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   gamma_p_inva(T1 x, T2 p, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   if(p == 0)
   {
      policies::raise_overflow_error<result_type>("boost::math::gamma_p_inva<%1%>(%1%, %1%)", 0, Policy());
   }
   if(p == 1)
   {
      return tools::min_value<result_type>();
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::gamma_inva_imp(
         static_cast<value_type>(x), 
         static_cast<value_type>(p), 
         static_cast<value_type>(1 - static_cast<value_type>(p)), 
         pol), "boost::math::gamma_p_inva<%1%>(%1%, %1%)");
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   gamma_q_inva(T1 x, T2 q, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   if(q == 1)
   {
      policies::raise_overflow_error<result_type>("boost::math::gamma_q_inva<%1%>(%1%, %1%)", 0, Policy());
   }
   if(q == 0)
   {
      return tools::min_value<result_type>();
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::gamma_inva_imp(
         static_cast<value_type>(x), 
         static_cast<value_type>(1 - static_cast<value_type>(q)), 
         static_cast<value_type>(q), 
         pol), "boost::math::gamma_q_inva<%1%>(%1%, %1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   gamma_p_inva(T1 x, T2 p)
{
   return boost::math::gamma_p_inva(x, p, policies::policy<>());
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type
   gamma_q_inva(T1 x, T2 q)
{
   return boost::math::gamma_q_inva(x, q, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SP_DETAIL_GAMMA_INVA




/* gamma_inva.hpp
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
*/