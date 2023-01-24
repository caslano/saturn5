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
39MfreilOfTT8NKi4a88g/iAuPvYbf+f+Xe+cm3m1uxBa5baD5UgZiB8YH+661xvz+S9yS+8mzvp1+8LQhBHEPXZGnVTzxdO12Xs63m2+ot/HDuH2ILwNT372KTCTyMi0/fkvnWi+taCRxFvEP7srx1/Wz9B7Ui+q+WT0Qf+eKICMQhxR0P9TK/FK+YVLL6vIvbBP2vSFiAuIcof/t3glB4vrUl/jlw9dk/UfAViFSJu1nNrXol8fFNayoE7P7ojaevQrxG/sJrywx2ztr0x8GfXomdP/j42cuOPryKmIfZIRb8NOX7iuqGqG57cl9f4oTkEcQ7hS/qxddXMTesfyWyYOe+PMzO/vw6xD+Gy8Mu3v6+Z903fjB1DWhb/kX1Sg3iIuK+yZ+SAGv2W84uum5X60j9L39uEGInwh/s2PvntM8efV98Q/tXv3fZVv464ifAXv3HXwP5HlTPVTz80ZdWPx86lII4ifO4fezJYM/9fo1WP3Pm++a6rUm5EPEXEq4ixfXF07r6aRS9N2T/hlmPnr0OMRfg/vnBpSi/94/9b+GS/PqPS7tHtQ9xF3NdYPOL6vk9cWK155MDqsLueUd6MWIy4X7oz5N7nvhz770XPbv0hOnLf9DOIz4g4KwP+6Y67/f07Mw4nOb6qqdv1JWI2woczqJ2+hziO8I/r3g6O2I24Z9itHRwxGnEnYkX/RxqCy88vvslc/mfT
*/