// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_DETAIL_MODE_HPP
#define BOOST_MATH_DISTRIBUTIONS_DETAIL_MODE_HPP

#include <boost/math/tools/minima.hpp> // function minimization for mode
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/distributions/fwd.hpp>

namespace boost{ namespace math{ namespace detail{

template <class Dist>
struct pdf_minimizer
{
   pdf_minimizer(const Dist& d)
      : dist(d) {}

   typename Dist::value_type operator()(const typename Dist::value_type& x)
   {
      return -pdf(dist, x);
   }
private:
   Dist dist;
};

template <class Dist>
typename Dist::value_type generic_find_mode(const Dist& dist, typename Dist::value_type guess, const char* function, typename Dist::value_type step = 0)
{
   BOOST_MATH_STD_USING
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;
   //
   // Need to begin by bracketing the maxima of the PDF:
   //
   value_type maxval;
   value_type upper_bound = guess;
   value_type lower_bound;
   value_type v = pdf(dist, guess);
   if(v == 0)
   {
      //
      // Oops we don't know how to handle this, or even in which
      // direction we should move in, treat as an evaluation error:
      //
      return policies::raise_evaluation_error(
         function, 
         "Could not locate a starting location for the search for the mode, original guess was %1%", guess, policy_type());
   }
   do
   {
      maxval = v;
      if(step != 0)
         upper_bound += step;
      else
         upper_bound *= 2;
      v = pdf(dist, upper_bound);
   }while(maxval < v);

   lower_bound = upper_bound;
   do
   {
      maxval = v;
      if(step != 0)
         lower_bound -= step;
      else
         lower_bound /= 2;
      v = pdf(dist, lower_bound);
   }while(maxval < v);

   std::uintmax_t max_iter = policies::get_max_root_iterations<policy_type>();

   value_type result = tools::brent_find_minima(
      pdf_minimizer<Dist>(dist), 
      lower_bound, 
      upper_bound, 
      policies::digits<value_type, policy_type>(), 
      max_iter).first;
   if(max_iter >= policies::get_max_root_iterations<policy_type>())
   {
      return policies::raise_evaluation_error<value_type>(
         function, 
         "Unable to locate solution in a reasonable time:"
         " either there is no answer to the mode of the distribution"
         " or the answer is infinite.  Current best guess is %1%", result, policy_type());
   }
   return result;
}
//
// As above,but confined to the interval [0,1]:
//
template <class Dist>
typename Dist::value_type generic_find_mode_01(const Dist& dist, typename Dist::value_type guess, const char* function)
{
   BOOST_MATH_STD_USING
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;
   //
   // Need to begin by bracketing the maxima of the PDF:
   //
   value_type maxval;
   value_type upper_bound = guess;
   value_type lower_bound;
   value_type v = pdf(dist, guess);
   do
   {
      maxval = v;
      upper_bound = 1 - (1 - upper_bound) / 2;
      if(upper_bound == 1)
         return 1;
      v = pdf(dist, upper_bound);
   }while(maxval < v);

   lower_bound = upper_bound;
   do
   {
      maxval = v;
      lower_bound /= 2;
      if(lower_bound < tools::min_value<value_type>())
         return 0;
      v = pdf(dist, lower_bound);
   }while(maxval < v);

   std::uintmax_t max_iter = policies::get_max_root_iterations<policy_type>();

   value_type result = tools::brent_find_minima(
      pdf_minimizer<Dist>(dist), 
      lower_bound, 
      upper_bound, 
      policies::digits<value_type, policy_type>(), 
      max_iter).first;
   if(max_iter >= policies::get_max_root_iterations<policy_type>())
   {
      return policies::raise_evaluation_error<value_type>(
         function, 
         "Unable to locate solution in a reasonable time:"
         " either there is no answer to the mode of the distribution"
         " or the answer is infinite.  Current best guess is %1%", result, policy_type());
   }
   return result;
}

}}} // namespaces

#endif // BOOST_MATH_DISTRIBUTIONS_DETAIL_MODE_HPP

/* generic_mode.hpp
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
*/