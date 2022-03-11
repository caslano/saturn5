//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This is not a complete header file, it is included by beta.hpp
// after it has defined it's definitions.  This inverts the incomplete
// beta functions ibeta and ibetac on the first parameters "a"
// and "b" using a generic root finding algorithm (TOMS Algorithm 748).
//

#ifndef BOOST_MATH_SP_DETAIL_BETA_INV_AB
#define BOOST_MATH_SP_DETAIL_BETA_INV_AB

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/toms748_solve.hpp>
#include <boost/cstdint.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
struct beta_inv_ab_t
{
   beta_inv_ab_t(T b_, T z_, T p_, bool invert_, bool swap_ab_) : b(b_), z(z_), p(p_), invert(invert_), swap_ab(swap_ab_) {}
   T operator()(T a)
   {
      return invert ? 
         p - boost::math::ibetac(swap_ab ? b : a, swap_ab ? a : b, z, Policy()) 
         : boost::math::ibeta(swap_ab ? b : a, swap_ab ? a : b, z, Policy()) - p;
   }
private:
   T b, z, p;
   bool invert, swap_ab;
};

template <class T, class Policy>
T inverse_negative_binomial_cornish_fisher(T n, T sf, T sfc, T p, T q, const Policy& pol)
{
   BOOST_MATH_STD_USING
   // mean:
   T m = n * (sfc) / sf;
   T t = sqrt(n * (sfc));
   // standard deviation:
   T sigma = t / sf;
   // skewness
   T sk = (1 + sfc) / t;
   // kurtosis:
   T k = (6 - sf * (5+sfc)) / (n * (sfc));
   // Get the inverse of a std normal distribution:
   T x = boost::math::erfc_inv(p > q ? 2 * q : 2 * p, pol) * constants::root_two<T>();
   // Set the sign:
   if(p < 0.5)
      x = -x;
   T x2 = x * x;
   // w is correction term due to skewness
   T w = x + sk * (x2 - 1) / 6;
   //
   // Add on correction due to kurtosis.
   //
   if(n >= 10)
      w += k * x * (x2 - 3) / 24 + sk * sk * x * (2 * x2 - 5) / -36;

   w = m + sigma * w;
   if(w < tools::min_value<T>())
      return tools::min_value<T>();
   return w;
}

template <class T, class Policy>
T ibeta_inv_ab_imp(const T& b, const T& z, const T& p, const T& q, bool swap_ab, const Policy& pol)
{
   BOOST_MATH_STD_USING  // for ADL of std lib math functions
   //
   // Special cases first:
   //
   BOOST_MATH_INSTRUMENT_CODE("b = " << b << " z = " << z << " p = " << p << " q = " << " swap = " << swap_ab);
   if(p == 0)
   {
      return swap_ab ? tools::min_value<T>() : tools::max_value<T>();
   }
   if(q == 0)
   {
      return swap_ab ? tools::max_value<T>() : tools::min_value<T>();
   }
   //
   // Function object, this is the functor whose root
   // we have to solve:
   //
   beta_inv_ab_t<T, Policy> f(b, z, (p < q) ? p : q, (p < q) ? false : true, swap_ab);
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
   T guess = 0;
   T factor = 5;
   //
   // Convert variables to parameters of a negative binomial distribution:
   //
   T n = b;
   T sf = swap_ab ? z : 1-z;
   T sfc = swap_ab ? 1-z : z;
   T u = swap_ab ? p : q;
   T v = swap_ab ? q : p;
   if(u <= pow(sf, n))
   {
      //
      // Result is less than 1, negative binomial approximation
      // is useless....
      //
      if((p < q) != swap_ab)
      {
         guess = (std::min)(T(b * 2), T(1));
      }
      else
      {
         guess = (std::min)(T(b / 2), T(1));
      }
   }
   if(n * n * n * u * sf > 0.005)
      guess = 1 + inverse_negative_binomial_cornish_fisher(n, sf, sfc, u, v, pol);

   if(guess < 10)
   {
      //
      // Negative binomial approximation not accurate in this area:
      //
      if((p < q) != swap_ab)
      {
         guess = (std::min)(T(b * 2), T(10));
      }
      else
      {
         guess = (std::min)(T(b / 2), T(10));
      }
   }
   else
      factor = (v < sqrt(tools::epsilon<T>())) ? 2 : (guess < 20 ? 1.2f : 1.1f);
   BOOST_MATH_INSTRUMENT_CODE("guess = " << guess);
   //
   // Max iterations permitted:
   //
   boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
   std::pair<T, T> r = bracket_and_solve_root(f, guess, factor, swap_ab ? true : false, tol, max_iter, pol);
   if(max_iter >= policies::get_max_root_iterations<Policy>())
      return policies::raise_evaluation_error<T>("boost::math::ibeta_invab_imp<%1%>(%1%,%1%,%1%)", "Unable to locate the root within a reasonable number of iterations, closest approximation so far was %1%", r.first, pol);
   return (r.first + r.second) / 2;
}

} // namespace detail

template <class RT1, class RT2, class RT3, class Policy>
typename tools::promote_args<RT1, RT2, RT3>::type 
      ibeta_inva(RT1 b, RT2 x, RT3 p, const Policy& pol)
{
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::ibeta_inva<%1%>(%1%,%1%,%1%)";
   if(p == 0)
   {
      return policies::raise_overflow_error<result_type>(function, 0, Policy());
   }
   if(p == 1)
   {
      return tools::min_value<result_type>();
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::ibeta_inv_ab_imp(
         static_cast<value_type>(b), 
         static_cast<value_type>(x), 
         static_cast<value_type>(p), 
         static_cast<value_type>(1 - static_cast<value_type>(p)), 
         false, pol), 
      function);
}

template <class RT1, class RT2, class RT3, class Policy>
typename tools::promote_args<RT1, RT2, RT3>::type 
      ibetac_inva(RT1 b, RT2 x, RT3 q, const Policy& pol)
{
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::ibetac_inva<%1%>(%1%,%1%,%1%)";
   if(q == 1)
   {
      return policies::raise_overflow_error<result_type>(function, 0, Policy());
   }
   if(q == 0)
   {
      return tools::min_value<result_type>();
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::ibeta_inv_ab_imp(
         static_cast<value_type>(b), 
         static_cast<value_type>(x), 
         static_cast<value_type>(1 - static_cast<value_type>(q)), 
         static_cast<value_type>(q), 
         false, pol),
      function);
}

template <class RT1, class RT2, class RT3, class Policy>
typename tools::promote_args<RT1, RT2, RT3>::type 
      ibeta_invb(RT1 a, RT2 x, RT3 p, const Policy& pol)
{
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::ibeta_invb<%1%>(%1%,%1%,%1%)";
   if(p == 0)
   {
      return tools::min_value<result_type>();
   }
   if(p == 1)
   {
      return policies::raise_overflow_error<result_type>(function, 0, Policy());
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::ibeta_inv_ab_imp(
         static_cast<value_type>(a), 
         static_cast<value_type>(x), 
         static_cast<value_type>(p), 
         static_cast<value_type>(1 - static_cast<value_type>(p)), 
         true, pol),
      function);
}

template <class RT1, class RT2, class RT3, class Policy>
typename tools::promote_args<RT1, RT2, RT3>::type 
      ibetac_invb(RT1 a, RT2 x, RT3 q, const Policy& pol)
{
   static const char* function = "boost::math::ibeta_invb<%1%>(%1%, %1%, %1%)";
   typedef typename tools::promote_args<RT1, RT2, RT3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   if(q == 1)
   {
      return tools::min_value<result_type>();
   }
   if(q == 0)
   {
      return policies::raise_overflow_error<result_type>(function, 0, Policy());
   }

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::ibeta_inv_ab_imp(
         static_cast<value_type>(a), 
         static_cast<value_type>(x), 
         static_cast<value_type>(1 - static_cast<value_type>(q)), 
         static_cast<value_type>(q),
         true, pol),
         function);
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
         ibeta_inva(RT1 b, RT2 x, RT3 p)
{
   return boost::math::ibeta_inva(b, x, p, policies::policy<>());
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
         ibetac_inva(RT1 b, RT2 x, RT3 q)
{
   return boost::math::ibetac_inva(b, x, q, policies::policy<>());
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
         ibeta_invb(RT1 a, RT2 x, RT3 p)
{
   return boost::math::ibeta_invb(a, x, p, policies::policy<>());
}

template <class RT1, class RT2, class RT3>
inline typename tools::promote_args<RT1, RT2, RT3>::type 
         ibetac_invb(RT1 a, RT2 x, RT3 q)
{
   return boost::math::ibetac_invb(a, x, q, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SP_DETAIL_BETA_INV_AB




/* ibeta_inv_ab.hpp
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
*/