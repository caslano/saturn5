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
      boost::uintmax_t& max_iter)
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
   boost::uintmax_t count = max_iter - 1;
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

#ifdef BOOST_MSVC
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

#ifdef BOOST_MSVC
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
      boost::uintmax_t& max_iter)
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
      boost::uintmax_t& max_iter)
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
      boost::uintmax_t& max_iter)
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
      boost::uintmax_t& max_iter)
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
      boost::uintmax_t& max_iter)
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
      boost::uintmax_t& max_iter)
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
MBP21PLvB4tgfy3/AaqHchpcC0+HG+AgeAccAu+FQ+FjcBj8ORwFX9DrvALHwV/B8fBjOEH1js7S+pmo9XIe7Aunw0thBrwBzoG3w7nwPjgPPgxHqz7RcPgWnA9/BRfAj2E+/AYuhLUpv0WwHhwOk+AI2ALOhOlwFhwMz4bFUU5l67L6XRbr+ux/3Nrs39k7E8CoijMAv91NQsKGkIQQ7hCOcAqES24M4b6joiBXyAUEAgQSEDyp4lkUtKh4FhUtIir1tmJra6toraWtVqyotLUtKlVKreLZfvvvv5OXxyQkilrbfTp8eXPt3MebmX9evDLgHLgy8LWv0T75jxgncUPgqLXazA2Br2S9dhT+2tdssbMhcNzXbffFB2pcu920IfC1r98mP3b81nB3bAh8beu461mP3YHaE12XjT7RJ/pEn+gTfaJP9PlGnq9n/V/Ot39p+f+h9f8rXPL8B/r1/lOUT8+YVGSwlzqpaj0jD5Hr00bkThqdH/7G2FBl67JmYL4J9xf7jzuJ/HuX/cwoflrPgZpvvWPEvIFZA5gs77dy7tp6nh7/vDJ4ioxfi8RsgZE/Nk/e1zl+TmOcW+3MeGlBfw1DKhwg9n7kPh9+Ym8xV7lzYv6oRa6P/b550in0bdecTfWc2zX58L7uw/gRqg3qLtTJzYhjY/tdARi75KEXlrtlCEwQN9c4a+zymvFT083IDlhl1m1OFrMrSKVUe5o39qb5UrNWfImYdcEs2ayBFoteJd9YJlplJc0T8wrO4qRhHjkLX25kQc0R83OcQsp4kpEnwhqKS5aIylPnnHXVWetp9ZSPIbLVNR2Tqsm4J22qybfgtzXvxmjeTVNZ9uzBx8fwt+UfhM5cJ1fl3WlTxp8++pRTR0yqusCAA/VUTQmPWYMza0JZ4nacL4F/p6BuIxw9fNZ6xe9YZFFpnowVsz6s4vlNGV4jem3d8stM+R8tZmfqO7JLUnySSuc5k1OOBPgt4hpHABP9FXFxiYGGcbGJ/mBwVHA0b8H4YFKcPzGmQVxMor9Boj+2Xv8HY4MVcc0DgbjUxPgEvIltGBcTSA79keBUa3NM2dgqYf0J5/mSrW1KE/hDsfOEtY34jZgtNG3EM/J+leMnPb7jBL1thCmz14i9l0V2uKedMPVou9h5lPvpU7A1JaVWOWCmvTBrQWYNJsdf8zd9+1pLzd/67d/Ka16bmZvoR//lkW+s2rnw8AlbEj8qbjPr5388fmfM67tGYl/jqf8aSX3XhOxrJDWvhdjXTuq/FnK8zox/YMpbuO6ulnKqaySRflTHAKs9ayTJukbSDDaCzWEK7AdF1h0cAFvB4bANvBZ20m/evXTtIRveq+7ug33go7AvfFL1D8Ntpo+R8m3CehPK0TOeLeEZsKue6ewJZ8N+cA6cCAt0zSQfng4L4XRYBGfDYrgMzofL1f0qWArPgovgRrgYfg8ugbfDMniXvOvZ7Uj7q+3/as/Z7QGafkNgEA6FSTAPJsNhsD08CWbBHNhd37PhCIgS/YlwDMyDY+Gp6s80OB7OgxNgOZwEK3TNYCWcDM/V98v1fb2+d9c1hT4wD/aFIf0xqj9Z9XPqeL969E716J3q7jvVD/CdOvHdoHPCu9Hv1dHnf+/5eub/y4oqS47P/H9DllN195Oujcc6VRzSjH9c8/+pI6eNnhaZfRaJbD/X3LHANifBvXeOWWidT6o9Iyurd+qxZWUlVbsHp8AzXys0d1uZ7xue+H2ESXJN8Ste6YnfarsMYk+4n693uFdXC+eMwNHhfCSdsUVN4azgqir33NEeTnXvc82fim35gL16yOjyxL17PeI+QOOueabfR4rtcs3MHKj+Y/z67oM=
*/