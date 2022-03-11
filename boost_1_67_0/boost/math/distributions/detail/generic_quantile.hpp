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
   boost::uintmax_t max_iter = policies::get_max_root_iterations<forwarding_policy>();
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