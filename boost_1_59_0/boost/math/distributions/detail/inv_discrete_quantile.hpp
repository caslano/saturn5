//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_DETAIL_INV_DISCRETE_QUANTILE
#define BOOST_MATH_DISTRIBUTIONS_DETAIL_INV_DISCRETE_QUANTILE

#include <algorithm>

namespace boost{ namespace math{ namespace detail{

//
// Functor for root finding algorithm:
//
template <class Dist>
struct distribution_quantile_finder
{
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;

   distribution_quantile_finder(const Dist d, value_type p, bool c)
      : dist(d), target(p), comp(c) {}

   value_type operator()(value_type const& x)
   {
      return comp ? value_type(target - cdf(complement(dist, x))) : value_type(cdf(dist, x) - target);
   }

private:
   Dist dist;
   value_type target;
   bool comp;
};
//
// The purpose of adjust_bounds, is to toggle the last bit of the
// range so that both ends round to the same integer, if possible.
// If they do both round the same then we terminate the search
// for the root *very* quickly when finding an integer result.
// At the point that this function is called we know that "a" is
// below the root and "b" above it, so this change can not result
// in the root no longer being bracketed.
//
template <class Real, class Tol>
void adjust_bounds(Real& /* a */, Real& /* b */, Tol const& /* tol */){}

template <class Real>
void adjust_bounds(Real& /* a */, Real& b, tools::equal_floor const& /* tol */)
{
   BOOST_MATH_STD_USING
   b -= tools::epsilon<Real>() * b;
}

template <class Real>
void adjust_bounds(Real& a, Real& /* b */, tools::equal_ceil const& /* tol */)
{
   BOOST_MATH_STD_USING
   a += tools::epsilon<Real>() * a;
}

template <class Real>
void adjust_bounds(Real& a, Real& b, tools::equal_nearest_integer const& /* tol */)
{
   BOOST_MATH_STD_USING
   a += tools::epsilon<Real>() * a;
   b -= tools::epsilon<Real>() * b;
}
//
// This is where all the work is done:
//
template <class Dist, class Tolerance>
typename Dist::value_type 
   do_inverse_discrete_quantile(
      const Dist& dist,
      const typename Dist::value_type& p,
      bool comp,
      typename Dist::value_type guess,
      const typename Dist::value_type& multiplier,
      typename Dist::value_type adder,
      const Tolerance& tol,
      std::uintmax_t& max_iter)
{
   typedef typename Dist::value_type value_type;
   typedef typename Dist::policy_type policy_type;

   static const char* function = "boost::math::do_inverse_discrete_quantile<%1%>";

   BOOST_MATH_STD_USING

   distribution_quantile_finder<Dist> f(dist, p, comp);
   //
   // Max bounds of the distribution:
   //
   value_type min_bound, max_bound;
   boost::math::tie(min_bound, max_bound) = support(dist);

   if(guess > max_bound)
      guess = max_bound;
   if(guess < min_bound)
      guess = min_bound;

   value_type fa = f(guess);
   std::uintmax_t count = max_iter - 1;
   value_type fb(fa), a(guess), b =0; // Compiler warning C4701: potentially uninitialized local variable 'b' used

   if(fa == 0)
      return guess;

   //
   // For small expected results, just use a linear search:
   //
   if(guess < 10)
   {
      b = a;
      while((a < 10) && (fa * fb >= 0))
      {
         if(fb <= 0)
         {
            a = b;
            b = a + 1;
            if(b > max_bound)
               b = max_bound;
            fb = f(b);
            --count;
            if(fb == 0)
               return b;
            if(a == b)
               return b; // can't go any higher!
         }
         else
         {
            b = a;
            a = (std::max)(value_type(b - 1), value_type(0));
            if(a < min_bound)
               a = min_bound;
            fa = f(a);
            --count;
            if(fa == 0)
               return a;
            if(a == b)
               return a;  //  We can't go any lower than this!
         }
      }
   }
   //
   // Try and bracket using a couple of additions first, 
   // we're assuming that "guess" is likely to be accurate
   // to the nearest int or so:
   //
   else if(adder != 0)
   {
      //
      // If we're looking for a large result, then bump "adder" up
      // by a bit to increase our chances of bracketing the root:
      //
      //adder = (std::max)(adder, 0.001f * guess);
      if(fa < 0)
      {
         b = a + adder;
         if(b > max_bound)
            b = max_bound;
      }
      else
      {
         b = (std::max)(value_type(a - adder), value_type(0));
         if(b < min_bound)
            b = min_bound;
      }
      fb = f(b);
      --count;
      if(fb == 0)
         return b;
      if(count && (fa * fb >= 0))
      {
         //
         // We didn't bracket the root, try 
         // once more:
         //
         a = b;
         fa = fb;
         if(fa < 0)
         {
            b = a + adder;
            if(b > max_bound)
               b = max_bound;
         }
         else
         {
            b = (std::max)(value_type(a - adder), value_type(0));
            if(b < min_bound)
               b = min_bound;
         }
         fb = f(b);
         --count;
      }
      if(a > b)
      {
         using std::swap;
         swap(a, b);
         swap(fa, fb);
      }
   }
   //
   // If the root hasn't been bracketed yet, try again
   // using the multiplier this time:
   //
   if((boost::math::sign)(fb) == (boost::math::sign)(fa))
   {
      if(fa < 0)
      {
         //
         // Zero is to the right of x2, so walk upwards
         // until we find it:
         //
         while(((boost::math::sign)(fb) == (boost::math::sign)(fa)) && (a != b))
         {
            if(count == 0)
               return policies::raise_evaluation_error(function, "Unable to bracket root, last nearest value was %1%", b, policy_type());
            a = b;
            fa = fb;
            b *= multiplier;
            if(b > max_bound)
               b = max_bound;
            fb = f(b);
            --count;
            BOOST_MATH_INSTRUMENT_CODE("a = " << a << " b = " << b << " fa = " << fa << " fb = " << fb << " count = " << count);
         }
      }
      else
      {
         //
         // Zero is to the left of a, so walk downwards
         // until we find it:
         //
         while(((boost::math::sign)(fb) == (boost::math::sign)(fa)) && (a != b))
         {
            if(fabs(a) < tools::min_value<value_type>())
            {
               // Escape route just in case the answer is zero!
               max_iter -= count;
               max_iter += 1;
               return 0;
            }
            if(count == 0)
               return policies::raise_evaluation_error(function, "Unable to bracket root, last nearest value was %1%", a, policy_type());
            b = a;
            fb = fa;
            a /= multiplier;
            if(a < min_bound)
               a = min_bound;
            fa = f(a);
            --count;
            BOOST_MATH_INSTRUMENT_CODE("a = " << a << " b = " << b << " fa = " << fa << " fb = " << fb << " count = " << count);
         }
      }
   }
   max_iter -= count;
   if(fa == 0)
      return a;
   if(fb == 0)
      return b;
   if(a == b)
      return b;  // Ran out of bounds trying to bracket - there is no answer!
   //
   // Adjust bounds so that if we're looking for an integer
   // result, then both ends round the same way:
   //
   adjust_bounds(a, b, tol);
   //
   // We don't want zero or denorm lower bounds:
   //
   if(a < tools::min_value<value_type>())
      a = tools::min_value<value_type>();
   //
   // Go ahead and find the root:
   //
   std::pair<value_type, value_type> r = toms748_solve(f, a, b, fa, fb, tol, count, policy_type());
   max_iter += count;
   BOOST_MATH_INSTRUMENT_CODE("max_iter = " << max_iter << " count = " << count);
   return (r.first + r.second) / 2;
}
//
// Some special routine for rounding up and down:
// We want to check and see if we are very close to an integer, and if so test to see if
// that integer is an exact root of the cdf.  We do this because our root finder only
// guarantees to find *a root*, and there can sometimes be many consecutive floating
// point values which are all roots.  This is especially true if the target probability
// is very close 1.
//
template <class Dist>
inline typename Dist::value_type round_to_floor(const Dist& d, typename Dist::value_type result, typename Dist::value_type p, bool c)
{
   BOOST_MATH_STD_USING
   typename Dist::value_type cc = ceil(result);
   typename Dist::value_type pp = cc <= support(d).second ? c ? cdf(complement(d, cc)) : cdf(d, cc) : 1;
   if(pp == p)
      result = cc;
   else
      result = floor(result);
   //
   // Now find the smallest integer <= result for which we get an exact root:
   //
   while(result != 0)
   {
      cc = result - 1;
      if(cc < support(d).first)
         break;
      pp = c ? cdf(complement(d, cc)) : cdf(d, cc);
      if(pp == p)
         result = cc;
      else if(c ? pp > p : pp < p)
         break;
      result -= 1;
   }

   return result;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#endif

template <class Dist>
inline typename Dist::value_type round_to_ceil(const Dist& d, typename Dist::value_type result, typename Dist::value_type p, bool c)
{
   BOOST_MATH_STD_USING
   typename Dist::value_type cc = floor(result);
   typename Dist::value_type pp = cc >= support(d).first ? c ? cdf(complement(d, cc)) : cdf(d, cc) : 0;
   if(pp == p)
      result = cc;
   else
      result = ceil(result);
   //
   // Now find the largest integer >= result for which we get an exact root:
   //
   while(true)
   {
      cc = result + 1;
      if(cc > support(d).second)
         break;
      pp = c ? cdf(complement(d, cc)) : cdf(d, cc);
      if(pp == p)
         result = cc;
      else if(c ? pp < p : pp > p)
         break;
      result += 1;
   }

   return result;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
//
// Now finally are the public API functions.
// There is one overload for each policy,
// each one is responsible for selecting the correct
// termination condition, and rounding the result
// to an int where required.
//
template <class Dist>
inline typename Dist::value_type 
   inverse_discrete_quantile(
      const Dist& dist,
      typename Dist::value_type p,
      bool c,
      const typename Dist::value_type& guess,
      const typename Dist::value_type& multiplier,
      const typename Dist::value_type& adder,
      const policies::discrete_quantile<policies::real>&,
      std::uintmax_t& max_iter)
{
   if(p > 0.5)
   {
      p = 1 - p;
      c = !c;
   }
   typename Dist::value_type pp = c ? 1 - p : p;
   if(pp <= pdf(dist, 0))
      return 0;
   return do_inverse_discrete_quantile(
      dist, 
      p, 
      c,
      guess, 
      multiplier, 
      adder, 
      tools::eps_tolerance<typename Dist::value_type>(policies::digits<typename Dist::value_type, typename Dist::policy_type>()),
      max_iter);
}

template <class Dist>
inline typename Dist::value_type 
   inverse_discrete_quantile(
      const Dist& dist,
      const typename Dist::value_type& p,
      bool c,
      const typename Dist::value_type& guess,
      const typename Dist::value_type& multiplier,
      const typename Dist::value_type& adder,
      const policies::discrete_quantile<policies::integer_round_outwards>&,
      std::uintmax_t& max_iter)
{
   typedef typename Dist::value_type value_type;
   BOOST_MATH_STD_USING
   typename Dist::value_type pp = c ? 1 - p : p;
   if(pp <= pdf(dist, 0))
      return 0;
   //
   // What happens next depends on whether we're looking for an 
   // upper or lower quantile:
   //
   if(pp < 0.5f)
      return round_to_floor(dist, do_inverse_discrete_quantile(
         dist, 
         p, 
         c,
         (guess < 1 ? value_type(1) : (value_type)floor(guess)), 
         multiplier, 
         adder, 
         tools::equal_floor(),
         max_iter), p, c);
   // else:
   return round_to_ceil(dist, do_inverse_discrete_quantile(
      dist, 
      p, 
      c,
      (value_type)ceil(guess), 
      multiplier, 
      adder, 
      tools::equal_ceil(),
      max_iter), p, c);
}

template <class Dist>
inline typename Dist::value_type 
   inverse_discrete_quantile(
      const Dist& dist,
      const typename Dist::value_type& p,
      bool c,
      const typename Dist::value_type& guess,
      const typename Dist::value_type& multiplier,
      const typename Dist::value_type& adder,
      const policies::discrete_quantile<policies::integer_round_inwards>&,
      std::uintmax_t& max_iter)
{
   typedef typename Dist::value_type value_type;
   BOOST_MATH_STD_USING
   typename Dist::value_type pp = c ? 1 - p : p;
   if(pp <= pdf(dist, 0))
      return 0;
   //
   // What happens next depends on whether we're looking for an 
   // upper or lower quantile:
   //
   if(pp < 0.5f)
      return round_to_ceil(dist, do_inverse_discrete_quantile(
         dist, 
         p, 
         c,
         ceil(guess), 
         multiplier, 
         adder, 
         tools::equal_ceil(),
         max_iter), p, c);
   // else:
   return round_to_floor(dist, do_inverse_discrete_quantile(
      dist, 
      p, 
      c,
      (guess < 1 ? value_type(1) : floor(guess)), 
      multiplier, 
      adder, 
      tools::equal_floor(),
      max_iter), p, c);
}

template <class Dist>
inline typename Dist::value_type 
   inverse_discrete_quantile(
      const Dist& dist,
      const typename Dist::value_type& p,
      bool c,
      const typename Dist::value_type& guess,
      const typename Dist::value_type& multiplier,
      const typename Dist::value_type& adder,
      const policies::discrete_quantile<policies::integer_round_down>&,
      std::uintmax_t& max_iter)
{
   typedef typename Dist::value_type value_type;
   BOOST_MATH_STD_USING
   typename Dist::value_type pp = c ? 1 - p : p;
   if(pp <= pdf(dist, 0))
      return 0;
   return round_to_floor(dist, do_inverse_discrete_quantile(
      dist, 
      p, 
      c,
      (guess < 1 ? value_type(1) : floor(guess)), 
      multiplier, 
      adder, 
      tools::equal_floor(),
      max_iter), p, c);
}

template <class Dist>
inline typename Dist::value_type 
   inverse_discrete_quantile(
      const Dist& dist,
      const typename Dist::value_type& p,
      bool c,
      const typename Dist::value_type& guess,
      const typename Dist::value_type& multiplier,
      const typename Dist::value_type& adder,
      const policies::discrete_quantile<policies::integer_round_up>&,
      std::uintmax_t& max_iter)
{
   BOOST_MATH_STD_USING
   typename Dist::value_type pp = c ? 1 - p : p;
   if(pp <= pdf(dist, 0))
      return 0;
   return round_to_ceil(dist, do_inverse_discrete_quantile(
      dist, 
      p, 
      c,
      ceil(guess), 
      multiplier, 
      adder, 
      tools::equal_ceil(),
      max_iter), p, c);
}

template <class Dist>
inline typename Dist::value_type 
   inverse_discrete_quantile(
      const Dist& dist,
      const typename Dist::value_type& p,
      bool c,
      const typename Dist::value_type& guess,
      const typename Dist::value_type& multiplier,
      const typename Dist::value_type& adder,
      const policies::discrete_quantile<policies::integer_round_nearest>&,
      std::uintmax_t& max_iter)
{
   typedef typename Dist::value_type value_type;
   BOOST_MATH_STD_USING
   typename Dist::value_type pp = c ? 1 - p : p;
   if(pp <= pdf(dist, 0))
      return 0;
   //
   // Note that we adjust the guess to the nearest half-integer:
   // this increase the chances that we will bracket the root
   // with two results that both round to the same integer quickly.
   //
   return round_to_floor(dist, do_inverse_discrete_quantile(
      dist, 
      p, 
      c,
      (guess < 0.5f ? value_type(1.5f) : floor(guess + 0.5f) + 0.5f), 
      multiplier, 
      adder, 
      tools::equal_nearest_integer(),
      max_iter) + 0.5f, p, c);
}

}}} // namespaces

#endif // BOOST_MATH_DISTRIBUTIONS_DETAIL_INV_DISCRETE_QUANTILE


/* inv_discrete_quantile.hpp
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
*/