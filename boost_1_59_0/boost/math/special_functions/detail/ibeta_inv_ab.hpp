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

#include <cstdint>
#include <utility>
#include <boost/math/tools/toms748_solve.hpp>

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
   std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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