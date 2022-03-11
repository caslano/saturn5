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

#include <boost/math/tools/toms748_solve.hpp>
#include <boost/cstdint.hpp>

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
   boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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