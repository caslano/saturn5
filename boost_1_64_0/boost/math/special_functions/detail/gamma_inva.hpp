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
1Kl+x+qLLkdZi3W7oavxvmictfySq1P0iKnVz6px4t6XNSM3iou++jXRKfrV1nr6qJT6vjR2dMrB/E0jScNviL6e0CHsje0q7Gyr0cXLUX3Sr8a/FZ2GrsiX8rfwe7ue7zMSm+fbnsZBTiK4G/1OGBryqjMhv5ffaVcrRybdcpGoe3/+EGLWz+WYWk/8rnDpMDdr+fU8eEV0uYhkTWwNpe2mj0Qprfc90dLsJBFaHxr9Pt3c1W5+39EoUaBNjRwt0d+NoNE3045/wx84Gp0gwji+/EfRsiTieinxH/8EOsdRykzpZ6KRm6kIbcbVyF/MR6xm93nm13gemV2eP7o0t1zJTzml1+E2pmuof3ERm6LqPFk/xPHJCUJde/vPl7RsFnGEcRB0j4pIHsbadEPZ5kVs7nFN7gG/yAEczoxhr/1BPM6Nyf1GlfPxG7TzrrGR2qMnxF486BveMC/jpmC6ZW3ZWambQYaqADHSll0DfqY2Ad/liLaO3NC6f5fj4E9Gd+6N2Tffu2PSoacvr8yunGKzV9rkIOOOScdhhvxSNt9fFLN0kqOi5ntcnaMCfcbo5Lze067yb3GBesd7OxUJ9pXhpBJVZTxgGLcCSV8jYRIujRTqg3VHVxyMny8a4lJM3c1oGFthpF0Js6gsqm71DBusKHj3J8yjkqh3OPelfArb0H1xz6YfZaq6q0fpJM4vHF/kZhl+jP5kGf1u4MC64b7fT/GBTib58opbcMgvqS9hNkUlz6OLWQaFR70jLeESzsxXT1m3nAKkw1axrBQiaeMs4xeijQm7Z1m/EG1MytC+ZYOFSM4AW94vRDg7+VebTo2O2vNjdWduqn9d4xcPAfT7kA6TzvnmZWCbVsvqat9JyXKcZ6gflskNqp36Dg9VcV9WgN3udGKSdiT+l7OMbs/igL6b+YM5k9UrhRkuQy2pSwGO0hJ7o65s9HxPeLv+UOcstpMny5Uj91+ZLBo9VPLlT5bhbkWYStAdCpFiYo85Nrsyy5nyUOlb/mwZPZbcC7mReqPc2PcYc6/yn3zd7SOnbnopX99Z62xsaz+G1g8Khbo39GbGDUr+tIrRSFWftbl5EZeuFSGfxp5/NF01meZYk/r1N8votJsK6Jx2mGe+/qUMw5UQ87WOO/dZvOfcMd3et8S/P4c5PQe3GnbLfTdZMXQj9X1oRH1ykSdapIwGGTdf94OMZ2dphi6kJutoiRMazJ8CjDc/Pg65w4ktZxBV27pMM9on5+ygQsrJxYtY1/YohzltE8Fe/PslA6xrF5X+HWL4RGUtOiv7+MP+6i4Qd6gFWdhRk76qH+SsLTXhB+flc3tK7uQ8Ly/d4YmJH9ElQt9Yu0rmtVAHNO/cc1gO5wMVFmVfKH/XNjbqcXafUUxLc/UkI/XdEpqlmY/sne5up7W5mZEPkzGlanvoHoPGRl706OElZSNdMsjstnY36qQ+bML1w26lt+53E+Kkjbqlz6UTc+qu8MO+zpNy+j5BjMWywFJBdM+z3djVORT0R90PcC2P6bScs9ElxJvXIbIooy3legGdFu0bNTolps7AazdozZydaEhfdymlt5uTcVJD8ufGjj55GIGioe6TUPGgZKC5LKRl/1ZaU6eg9dnsazsMnSDs1tupM2AIAtParZMFIfUfc5LKnXitTZdidNvNSK1H/AfpRQ50afdcWkIyR6Rf+a9lUCJR1saSbuBQKsGVyoajCGYFrl4j96RuWY7jKfUZd5lYVqcJzqHbuOT2V9qt6/SPrHt8fm5HyvNtDcO1ArZn/5BmkphDjvvLPN2//2bmAgFdqq+ap/A5vtdG+saQnmVggrWHINOoOeswFwwxcZvOp23UaeLUOTM=
*/