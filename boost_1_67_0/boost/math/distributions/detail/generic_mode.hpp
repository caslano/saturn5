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

   boost::uintmax_t max_iter = policies::get_max_root_iterations<policy_type>();

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

   boost::uintmax_t max_iter = policies::get_max_root_iterations<policy_type>();

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