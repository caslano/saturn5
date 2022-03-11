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
3IehrjdZGyixmkZwGOU676dA90JYEhKqPdW2dotfRCy8p3AI14+e6ET+nN9qDpZCHZO5QkCryxj5EDZB+UByLFbwiR6c1RiO/5ZbXNd/bDNiGEVzTK0dw+rcIYt48FOeZbi4vKm6Pr0K5TIrI1UEdCjVGUGe+uARTrTTGHBbaNyBHw+ZxP0uNtjWl8D/p/5suLLPR9OUfVMHdynNklGJy1vwiSvHa56zzL29gk7LdcxcJ3mXvfqRXTV2dek4vZjQmN8m5tYlaXzU7DzYKFwZo48WsSO7EnWsCXkjZ9lCaFokdAQSdsxXJLTEooPP9vVE/AC5lGgm1dZhdrJeH339rdP9VfYhSSTvJPlM0smqt+6y1O9cQoQbY2d9rloUU0iqSoJGTDDdO+ZIidk6JoMD1MWCwitkItn9tKo6l/uQ0I2XYl94e1aAGa2EZiUP8GKWSEgnSufsX05m1CNEpERpQSHkyqd4c6uoVvp34iuVOmrK1HB+5b4DcbnYv/BTWrHwzjvSIzYRnTFQB/bPnyAF8A8RM9OfN4uWjw9glEZ55RYPCxrOxorKWlwXrWa7aKbH5p81fNLrWeKWYlYX/ZgCKjTJPx2kjscqLUlkYxJaYkA6kPOkQqro+RuGM7hO3e6AokeSW4f7SFT5xqvzYJceXLsLZv05DQ6ezACVrkHQJVP5LaptRIQKQyzqZ0U2LMUm+q0yYHOnt8wXQh9vJcqxAJnozKx3540Et55h2F6ODLBSBvv2b4CdWHveRcSPDNmEs6xRjqvt56l2bferpqeFcMhEn4pNNnnDk1vrql71/VkoeF/oH/HS6EkSj1YWZx6uKHid0psJldr+h93vcDsq9Libzthbe1v7+2mDVE1ytFoTSbqxmH2ABhRRKFwXwjeZCVuXfY+l/VOos1EAcWG4ILZ2qlxXIJ3RbjxXYqmDQ6hwjSswED2aTaDlAo81fuPXNpVE1nzSjj06IfAqHEFK2VkLWBMq6Hcu4f5YOU2oCHLnughIU2uWLa6J3OWiznVEKQHQg66TbR4VPZGmOZXk2Z+RzdutOcxYNKFs4WruUzT4uEY0JA3acXV9IOl/4DG89GQn2E7U6jk0upoeAIuS/+0zNNaG+w3dZCg41VtJJQUhTtEDYaogzotSxwPGTIxXUB9F0US2DovmeKvKgOzUzRHKrmBfbEzjBPBGytRfv1wIR2mQVTP9cGMB2gC4iM6I1G7iUkQDF9+JXUDpj7MjYGdkifnzPBCyaIadheZaMhu5iDW/a2mC37ity9swswV4Me2rm8DZeed/W5YDEdwenNTf+GK2yLCQ5OjfxEWmvhIM+Gz+BPkC3p5RPY5zOgDUznDyQqXioUzAMr189ehBb4sTfA+UnWJoa6KD4bJJjP8tWKeS/KczH+2g0jNjN6jyY8f0TPnID4ohBVfppK/eKY0iX4Na2RWeRhMsT5G+VapCnvYp23hN5JCl9rZk4xULmRvCt9gsnfCxJkcRMZMrhcNj0CaEzw2CxyX7vjW1zQmS7ZY2/jJjv6To6NaRJB+8PM0iy62FNZ1g5RR0f43Cq2AOknCYWNDSRUGZVIPMUt8Lv8FMxCZTZbmp9MPn/C6KK7+tsCatcAxDR1rRqBOQKc5UEliUNBAvIHXSaSzhPv+nS6Hry5yqhkSrB2Z3wumW7zAJfBj07Wl8FHeFLlEOH+vf7Q+lr0O7T5j1ag9Xz75A3Jv+jwuWLomrbjfIs70QuAJx73D/VcGpue9qcnsQnjrwP3sMIE+r+i4HWCBcOz9CeHcE2QKcI/RnetCKjpKfGXq+EyPR/Ex8tBEeTSxYtpvz0bVblX/Rx2xPtwbKvHyHunUDTZOWdyhWRguYjgEE521cqRTtaG4FCYXYeQAjOiupYGCG/yZOtEK46YZWDQEBFUHWBzpfbU0HgQhMDsu0VD5Byh4pE4fUKu9K3NIMjJB29w6GdjSJlo+MWEyxv+OjirR/kuY5voEU/vw5/9F+3FCZZ+jtNnVYoHt8SNa7fmwQk39sb/jpU+Q2O1abQ5tPSggcLO0RhtDoj2yy60uJfjc59ZfatVXablFKUP1CAlnagBE4AN/hoMpjCose0PFVSqZiccydUWwo+FwuwYEpdwhCrqGpXb4XrJ4uaP8SGlkG2sIsp84GltJWNJEVZdMafe/2aYJ5zINz4OI1ggNMLGUro4HuYTGw4y7No198NY/M5XMI9LdR77O/+65K3kgLUYQJcqsY3WcLqXhT6u44kGl+5Wh5dqNpv0uszS1hocFq103+Q866LMItLH5SxS9J65IPOPbTp7D1UxWh5UICuUO2o0iXka0miIKVopUNzjvDYsaMftTahodp8XcM1feCU3U0w8YyNj2r9usy3Q8XzsxDI3QRONUBk+rNC6xaHNM9WWMb1+fvVv8K/tcouMnEvnyvTjkvlFakwJtV9/4XNVhxwdmnltX9J+5Jntp730RB8U4A5ssXibKIqAMQtBePcS30itF1y2oY9Yeyte1GCEwOPrsQt7ode9LXeI64YEMjRcA2Ay5l8zwdokSVN3vfpcGaAdNIHLLqvB2i1pexJRQWg4WBjkDPLDi5GsWxla7I1kZXoUPNejjPw0U06kutR8bZ6tb+JqWly/U1aTXbpYdqRm9LufSzaWZDKvHcYTDzrQGh7iW9L7oBBCd0RkpYofWzuWU///fZ05q9i5HBcaP/iunb89vXN4ylptxBWjwWXdt+m4HHGDyXm+dGdhiG3Pd5zx4AFCh9A+lkeZDWDIIlKI+2lpUyEFwtDzc0Ljd8p9BZQQANllnW2d/XWHrs7G7Ni66us+vOBWk1IIvikrbNK+DKPUJmDcBNmlzLq/BRkkfuw7ilOqoNz3O0gQM7FRhjTiWfyjfwbr9a9vtK+QyeDK0IHlDuSmMSMS8d2B52UwpXvxK0fDZpqtnZ+wrTphE4Z812A7cS5jguwFayhscRifVBaF2xS/VRX2U8DWhavRqXWR3zfg8ldqsuu8xrn+rljPYujoy6nTz8CLYMoZGWS56ZvQZC30+dJR+/aIvb7wKNpI/yw63tZdoQZZyGWefT/fII7FUB79QoSo4WzlYSnMdJNBABFJwOifXzlJ7j686vNzPr42BLHAxerDT+FeMmCOaYl4Es6aYm+let8iEWgb4Eh6xHLlHdO1n2Yd2nbdKyXfbFCm/0HY2cri7DaQrL+6qe7s2JmbVdlJsPy59kvMqpHS8p/+sGn5yXhcsZ3xy9RqhnEi7vZlcektrHh/3FjKuBoYjc5kegajO2uUcXMfbPP9Xr22fsW3POJxfYV1suHiMXP88y0B59PitfHhhUR+u9zCRZVl42VrgcWyK5mD1K/Zhr62yO5hMHg2FGZFBd8VqGmzXVGTLaaFKPhpECQyId8JXAlgDjWVD3gBYekV63e8PCBb53XGoZDFM2oAk0A1iUvY/LQNp6C8+KXgw6g1zsolYHQCVCX+Mxt1mpoUZguglGR9Ps2Tdi5ueMuBsUmi1bwhL++29rfKedjj/2VYtNYzqkwnGpCJGxHTLWeSlTZIfFB2ZYu/DPAV+vargH9ws87W829n9KnN1y9rJRVPy/XpNJXi4hP7HmZeQgoOL55NWDVdE1KcZ1ivhuRiGGZ+H5OYownkRk4NhjedlXpzl0L10y85xevV3I72z3N78E9LbusFtrAUM9sTjMgZfesuHW8rK71oO7k53JuaCpzBXU+zzKOQZKsYGMnQG4s2mavgmHxuxGZbw48XXAftibS2BWoCj8gU70L0d/v4gqhznR5jWLLQG1gL+q/Asm3gqafbZzyybIUPPZ2KESGF7PDVlxTlc60CAwAw77yMs7IqsVOE1wRCeXzaS20tXl4PyiA88G9Cdrf3BYkk41fUyDJId9wcJtE2egjdFpQ3zMtU1L2DxrZABd6AO/erBo0Trp9B66d2TMfBznuBt5xBE5qhvusXE7FMTQSt+xHHUZuq+5YTEhC+cddmx61+oJuY2334abMhwgxETXrBvF7sWX/eLbWlzMXqsvlb1e7+2kPbid29xF5lQpUUykUwGlRVQ6eDrgg5jfBvxH7KlFOwzlFQhciz2FF1EUHOYlfixyM1ThwqaSLFTmzOQYmvUX/5GdIZflhRaCRGwb8cS7S6u9XPfQilCp7K2zQBdhIyG5HAcMxBcGCDgj9/yL5cd6uUz7/L5XHWAKOdkw+2vn7LlesbA4baM//MDZGh3CfHTrLQWL0sqW7CUum0cCltYJ8UEYLL9YA3GL+VWA4cLpuoN56/fl33mefDRfWE68aAyC2yJ8Pq9/O23F3PaZSBVASNEpby6l7tM0QllzGa4vFL0hW1lt3xlc19Gf/k+tbbfklUX7D9hx9hshx4qnColZNMikj4l5nX3Q63CDKq4xRlBZBPgOb9wlyKxlMQqb9T/8WbTY9TZLiR/NAa1hpWaA8HkMYlyh5+hvAEJdpVPOAu59S3q/4MJSMuV0yj/mP9yBt5sFRU5vMozUHrsozZXCF5FkEGZ0DGPMCYkAgj5OdZvDUFstmZ4tOktixF33YRDn2R6H013jIPoKbZy5Fn8LFkac6GPgd64CmbufHkkvnnSsMnhltub3pQcz7LYbXyXshQHuCYtTOhyPYSXvUrvHbjkQ2fqbin10KloTRFgLNeBIOICi0PlV5O0292yK62LVYR59lXxd/oxzMqTdJuB2aal+2pjQ6yxQqXhzw0QmsXpCT5dRsdkJu8086dw7iwbXnB+8cyw5b47e2enWFzysJztuZx0Uv7MY/4yR/mGpSYOfNAU6uZK8AQmIdK0FvWiozdbVm5j0kJmumt2jkJ0obkCAkreMBs/q42g47zAse5mFepwbnNlqStBtH6o90SzGE2B1ON4JFMMyG7+xmY+4m+6NKcnCCXonXNExuhH2wG4z6DNZZjbfbPX6aj8S7A75HNZaRjjw5KNHaY1QmNnQPF7g8ntRDySO8XgI/1pPtOr4ti8w3aGskpVcI8HEhNSxVMuJTk0yDu3JqFkRWpzCf/PHNq5MMHBMHBeJhesrNxwpk3s5Vxm9Lolxn9E6EQ2c/TbTaZheS7Jfaqs6ThXDiF7HFi+jSTTyFGKXJp/LPobUpWo+OqfXcWam3puV/LAuhGyYG1m/FQS1X/Fw6H5W8j3G29V3KjtsNxzlrUJC63kYLkXsN3yIyTGyDiy5jQEiDPHpUHbWZD0HH7APX/+4bOnQconV55SUFNhQHItWWG0a6+CnpL7xVId/7H7V3kpXYU9idNjV2aQ9xH5vjFnzEma+2MUWiiIOrjAeFlwaOA/ny3Z9HSyvVZbLE6FzAw4r8dTVDjhoLhJ49qxcQKsMyijzkUIciI5DjFxkE057ll/+ytMyZzi3yOvzWvcmtvapGp2tg5qWYwpUun7OaXA25pTwPLgpShsKwLA6Y207d2bysuv+Vp//ZF78ucoZ9twA85Y0GPUWdd+LQuIKxiISdsfClsJqHUAlVKtAYCSZ2tKrmqO5emqygLj7N8Cl7c8uMW7FFLWrlam93Ydbd9r/vJCwWjYWbLFmwfDDie2/QPad4Gom8WisphkCE65PdLxK/FHy4Npk1srk9tPKJMz6vf42VcPvsEQoacLQscD02CFF0uGlXZ58+YP4bVFvHH+rR18Q4DD7p9p6v2Agr8GkchUysmYxOHUowwzb0XFYFMWuO/UbVcWibiQhxfJSlA8Jt8r+euieUgOCKUTfRM0RP8emlNl5T+Do5cVn6RYgAzH9CrAHIKGwetwcIg3QKA1Iz30pL1JDg21uBWfIMQUV+9/iccqojmnGyT+MNLWgpNfld7QAqANH21TGBTf2V+huqonnSxcozKhne3Oo0MhsI0Qai7Xau1I9JbCDUMs7tu45SRY4Yb11vbT9sxRbu/sp54qchcyoglbdDj/6Dn/Ou/i0ozqC3C0WmEYuziksLC37jakuhZb7DsfIjp+ypQ+1q6OBNH++1OwOeY/126wtOZebBY4f1md7TclJLdUVadUXLS+YhtAmPEQq0nhUYQ5L+o/+x8d94nU+pGrAJ16vVKv3se/AYYdyu27WQLA6DUGGNZKcVgNg2U+UWDASa5lUEw2hTSfz+YVdgYAfg68mDmyUuM8g630EfJ5BiX8ZqO1re5Dx071RzUM+iNvCZebOFtuX0mQ266J0Mvzh0m+Hmp0H7QkozkY34VWwXe28bSdyGVl+tkhSHusgtzg0OM5geyt77qpSe6uKzwvZ0sBbIhGeLrTwN5uAVDa2stwcCmo8/TSEMXF7B+k2sSj6PYEt9MafxYm3yXJvGH8gZLDevHxMUprqSDFfdvxVYGTfVCS8TUmwS0MRz2qVNiMsp5e8WDz1Qrr5IxuLvBHS6dPHgW0+/4Wt7QUAxQTzV8b8TfXjxwDeHUsTKHAR5TU/LUGj/CT8adiMizXap9+fUWDw6HDs/DYJPMWnH7uCBQLNDNvpU1oQQuVw1F1Er4iiSYI+YvTqxbKmq4TRVyehtIvSqVRkXicKkF+PFxzuA9Ol3acMIfnrbSaZt9i9JCb2SYfoyTRzg+WIkXUg8txGJHub9fY58JZNns7hITdwAwnpHU2PtDWXnCbJlqqvFK3qokB6R6QZpzMCL3BYv0to/TG9laU6mWeZWQHmDbodJUett9WYtBaiJSWd9eVO+pES7bNTbX3fw1LyyLquhm2uuOM+pN7NteIP+Fgj+eMunF7k61yzKAHUFQBiIr76RiDnjQ1UZuyn8+xUBARiJ4S2jpFFNRZUTDKweZK6PWq0v4SkaHIX9fpWC+E+qIPe7Xf5QHdI/VFJpRyL/5XhewJp8XR497HnC6or2GIizYccUKXRKHp6XY/01WU9Y/jRFSvm31echBKZRe3gtYKbCOYjM7KZ8OUNKR+hg1D7InyJLbV4k921LEvoRAPzRdFMmJH21DEArW7jk9XgEIX4+kqyPigjXbgVMMGVkcG13zhKKgOMK+NsSzH9IbL05ENQhYgpb/l2XmsJyxG9dAM6FiGirZXLK8M4VCraZxTw2oubV3Xs98meGw0/E01mgj6ad67or0ihOROov9KudcNf+XWsCOEuSzutjWM1xvNhCicFt2ex6aTJnwhdQLKc506y1cmz6V0U4PVA5pAhdQKqOmq9QjYYyLE636P9nVyP8j1rMfCEzmnF6k8fWldJKBsgt27X98pGeW4qoq15ZQNlAhdAa3Dal+d0v8r4RD78RvfXitKQz3X1R6XiXomSp3Uu0/FlO9aMHxV/kGC4APECCI49TBubFBmgI12pWK4oEEMM/e9OYFKq/gEaWzaQ17h4/xigyQODq74wGNrSKgAKTfw8Yz6ftNSnsQC3nbS8ZA3wvtV+XOPUvT89ibbdfEthR99RaaUDWYHfusA3qiplEhkOMCnw0SYQCSp69Es7hn+EQBTXJfEim1vkQHivSWzeCuTNgLHxPLXBG3THdHY4s60ZitxWj0ScXQEFs+tY0liv9igEjA0rFZZAn0FNMtsFLfgcUuKuvSl7eMAk3763bG8YgppCQAZf3OyG+AimYkA7RqxdQIYMqr98niuORtYUrnUpIwXcWf+dH9pB62Rljrw2GQEcycqhXjjS0EqT1w3xcERayuqhQpQbpOkSOk8JRpDsH4q95um4M3II6O+j2qgNkaf9CcwFDT6TpRFKGY15mbcPmVWCjAYCK9Mh7gm2DZzuSyF4HruXMfd1b9efOrnlKeVnewmoFzBdJbR9NGURSxJshtj6q27rq+khSzorHKqKI9uWmzDX+4w1MfplBS6dj75g79sN3dqGKl62Dwj0uZAWQuS8mHqXwWp5PR+0CHfVD1y5j2sOCwhO2Q9oaMJs9PfeVwKDL0VtKFaDBkAVQIA/v4B+Af/6+wvkF+gvsF/gvyB+Qf6C+gX9C+YX7C+4X/C/EH4h/kL6hfwL5RfqL7Rf6L8wfmH+wvqF/QvnF+4vvF/4vwh+Ef4i+kX8i+QX6S+yX+S//v2i+EX5i+oX9S+aX7S/6H7R/2L4xfiL6RfzL5ZfrL/YfrH/4vjF+YvrF/cvnl+8v/h+8f8S+CX4S+iX8C+RX6K/xH6J/5L4JflL6pf0L5lfsr/kfsn/Uvil+Evpl/IvlV+qv9R+qf/S+KX5S+uX9i+dX7q/9H7p/zL4ZfjL6JfxL5Nfpr/Mfpn/svhl+cvql/Uvm1+2v+x+2f9y+OX4y+mX8y+XX66/3H65//L45fnL65f3L59ffv/X9mkZ55nclg6J3TlXOsdl6ALwsknSTRjtqAEVNGe7ycHurFgqI8bkQ+GCh1eAC6L76YqWo3MSnjYGEmdnffd6YDmjRc1NQcYvdBNBvYc/OC97DZp4w8VWpId9GNqAiTLU+4w3MYD077tu6ZYmmW5NheQwWbAezzeWp6jQlfv/WYS0wyg93HNR/vGlKxRBeF2vEG8rD5ErMogF87wJhc24S66yEIt7v0w1bTrrT6oppcEc4npJQMfoK6VVRCwxacvsVkJpuXbyodPJ1+VcKXTIhbTdDa3Y1yH+2hncrvFVWcQw9lhj9cCr2nhtYNmVa7m4g5jYAlW9R6gBmtynjz74sloixWbbMyN9rJkCkTcuWNZxe75MTgu5U+JRaSRuR/xEslRg8ruFSIBGLJnkbqxvezEo2YV+KbsPXFyBhjqt0RDpNgYT8SGTHCE9TfAg3ORDfqkaBQmPGNVPOlEiyUX4LCrtqhvjBPEx47UObK6zgk3ufQhQygXfYbUxs4XHTfZcbD+DmJ4axW0NDp6zW57ARSAkxsp6wz6Jxh//NxjzwKlgqp3vAawjN+M9o1sDVT7q8H0a1RtQhTulVbuGMe67yIzf6TA9uu9Hpg1FW0bIATZ2kgG4z1I/xFQIwWM3WfrHxCj4FDOutd7WkEUHpHbon+lGxj08SWimNq/+zsDRCU/5ZWURc/qfmBdvCw7rSJyMzCv0Rsg0yclQLgEykkZWGKcaVWC+hQT2Xsia3aJsGj4SeeM6Wkks82+UfHgwKPCZOFV02GZRGGRaNERnPjbZW3TwLpwH3Lo98ZtWxr/i3YjQjYHLfgSSs9l5Ol63oFR9LbzWTwl96j6xPMSXvvITjc3TZVx+jgh+sHngCzFI42+XMmEccAbA/vpIDUJm1da96G8ufG75A6isUtA/9ejFi4dIBewECJz3m0ldP1ffXE2P9bJvAQ+0ZB4tL469wdIfffY=
*/