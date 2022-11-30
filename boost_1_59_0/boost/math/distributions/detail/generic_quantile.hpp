//  Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTIBUTIONS_DETAIL_GENERIC_QUANTILE_HPP
#define BOOST_MATH_DISTIBUTIONS_DETAIL_GENERIC_QUANTILE_HPP

namespace boost{ namespace math{ namespace detail{

template <class Dist>
struct generic_quantile_finder
{
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;

   generic_quantile_finder(const Dist& d, value_type t, bool c)
      : dist(d), target(t), comp(c) {}

   value_type operator()(const value_type& x)
   {
      return comp ?
         value_type(target - cdf(complement(dist, x)))
         : value_type(cdf(dist, x) - target);
   }

private:
   Dist dist;
   value_type target;
   bool comp;
};

template <class T, class Policy>
inline T check_range_result(const T& x, const Policy& pol, const char* function)
{
   if((x >= 0) && (x < tools::min_value<T>()))
      return policies::raise_underflow_error<T>(function, 0, pol);
   if(x <= -tools::max_value<T>())
      return -policies::raise_overflow_error<T>(function, 0, pol);
   if(x >= tools::max_value<T>())
      return policies::raise_overflow_error<T>(function, 0, pol);
   return x;
}

template <class Dist>
typename Dist::value_type generic_quantile(const Dist& dist, const typename Dist::value_type& p, const typename Dist::value_type& guess, bool comp, const char* function)
{
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;
   typedef typename policies::normalise<
      policy_type, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   //
   // Special cases first:
   //
   if(p == 0)
   {
      return comp
      ? check_range_result(range(dist).second, forwarding_policy(), function)
      : check_range_result(range(dist).first, forwarding_policy(), function);
   }
   if(p == 1)
   {
      return !comp
      ? check_range_result(range(dist).second, forwarding_policy(), function)
      : check_range_result(range(dist).first, forwarding_policy(), function);
   }

   generic_quantile_finder<Dist> f(dist, p, comp);
   tools::eps_tolerance<value_type> tol(policies::digits<value_type, forwarding_policy>() - 3);
   std::uintmax_t max_iter = policies::get_max_root_iterations<forwarding_policy>();
   std::pair<value_type, value_type> ir = tools::bracket_and_solve_root(
      f, guess, value_type(2), true, tol, max_iter, forwarding_policy());
   value_type result = ir.first + (ir.second - ir.first) / 2;
   if(max_iter >= policies::get_max_root_iterations<forwarding_policy>())
   {
      return policies::raise_evaluation_error<value_type>(function, "Unable to locate solution in a reasonable time:"
         " either there is no answer to quantile"
         " or the answer is infinite.  Current best guess is %1%", result, forwarding_policy());
   }
   return result;
}

}}} // namespaces

#endif // BOOST_MATH_DISTIBUTIONS_DETAIL_GENERIC_QUANTILE_HPP


/* generic_quantile.hpp
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
*/