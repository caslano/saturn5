//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_SOLVE_ROOT_HPP
#define BOOST_MATH_TOOLS_SOLVE_ROOT_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/cstdint.hpp>
#include <limits>

#ifdef BOOST_MATH_LOG_ROOT_ITERATIONS
#  define BOOST_MATH_LOGGER_INCLUDE <boost/math/tools/iteration_logger.hpp>
#  include BOOST_MATH_LOGGER_INCLUDE
#  undef BOOST_MATH_LOGGER_INCLUDE
#else
#  define BOOST_MATH_LOG_COUNT(count)
#endif

namespace boost{ namespace math{ namespace tools{

template <class T>
class eps_tolerance
{
public:
   eps_tolerance()
   {
      eps = 4 * tools::epsilon<T>();
   }
   eps_tolerance(unsigned bits)
   {
      BOOST_MATH_STD_USING
      eps = (std::max)(T(ldexp(1.0F, 1-bits)), T(4 * tools::epsilon<T>()));
   }
   bool operator()(const T& a, const T& b)
   {
      BOOST_MATH_STD_USING
      return fabs(a - b) <= (eps * (std::min)(fabs(a), fabs(b)));
   }
private:
   T eps;
};

struct equal_floor
{
   equal_floor(){}
   template <class T>
   bool operator()(const T& a, const T& b)
   {
      BOOST_MATH_STD_USING
      return floor(a) == floor(b);
   }
};

struct equal_ceil
{
   equal_ceil(){}
   template <class T>
   bool operator()(const T& a, const T& b)
   {
      BOOST_MATH_STD_USING
      return ceil(a) == ceil(b);
   }
};

struct equal_nearest_integer
{
   equal_nearest_integer(){}
   template <class T>
   bool operator()(const T& a, const T& b)
   {
      BOOST_MATH_STD_USING
      return floor(a + 0.5f) == floor(b + 0.5f);
   }
};

namespace detail{

template <class F, class T>
void bracket(F f, T& a, T& b, T c, T& fa, T& fb, T& d, T& fd)
{
   //
   // Given a point c inside the existing enclosing interval
   // [a, b] sets a = c if f(c) == 0, otherwise finds the new 
   // enclosing interval: either [a, c] or [c, b] and sets
   // d and fd to the point that has just been removed from
   // the interval.  In other words d is the third best guess
   // to the root.
   //
   BOOST_MATH_STD_USING  // For ADL of std math functions
   T tol = tools::epsilon<T>() * 2;
   //
   // If the interval [a,b] is very small, or if c is too close 
   // to one end of the interval then we need to adjust the
   // location of c accordingly:
   //
   if((b - a) < 2 * tol * a)
   {
      c = a + (b - a) / 2;
   }
   else if(c <= a + fabs(a) * tol)
   {
      c = a + fabs(a) * tol;
   }
   else if(c >= b - fabs(b) * tol)
   {
      c = b - fabs(b) * tol;
   }
   //
   // OK, lets invoke f(c):
   //
   T fc = f(c);
   //
   // if we have a zero then we have an exact solution to the root:
   //
   if(fc == 0)
   {
      a = c;
      fa = 0;
      d = 0;
      fd = 0;
      return;
   }
   //
   // Non-zero fc, update the interval:
   //
   if(boost::math::sign(fa) * boost::math::sign(fc) < 0)
   {
      d = b;
      fd = fb;
      b = c;
      fb = fc;
   }
   else
   {
      d = a;
      fd = fa;
      a = c;
      fa= fc;
   }
}

template <class T>
inline T safe_div(T num, T denom, T r)
{
   //
   // return num / denom without overflow,
   // return r if overflow would occur.
   //
   BOOST_MATH_STD_USING  // For ADL of std math functions

   if(fabs(denom) < 1)
   {
      if(fabs(denom * tools::max_value<T>()) <= fabs(num))
         return r;
   }
   return num / denom;
}

template <class T>
inline T secant_interpolate(const T& a, const T& b, const T& fa, const T& fb)
{
   //
   // Performs standard secant interpolation of [a,b] given
   // function evaluations f(a) and f(b).  Performs a bisection
   // if secant interpolation would leave us very close to either
   // a or b.  Rationale: we only call this function when at least
   // one other form of interpolation has already failed, so we know
   // that the function is unlikely to be smooth with a root very
   // close to a or b.
   //
   BOOST_MATH_STD_USING  // For ADL of std math functions

   T tol = tools::epsilon<T>() * 5;
   T c = a - (fa / (fb - fa)) * (b - a);
   if((c <= a + fabs(a) * tol) || (c >= b - fabs(b) * tol))
      return (a + b) / 2;
   return c;
}

template <class T>
T quadratic_interpolate(const T& a, const T& b, T const& d,
                           const T& fa, const T& fb, T const& fd, 
                           unsigned count)
{
   //
   // Performs quadratic interpolation to determine the next point,
   // takes count Newton steps to find the location of the
   // quadratic polynomial.
   //
   // Point d must lie outside of the interval [a,b], it is the third
   // best approximation to the root, after a and b.
   //
   // Note: this does not guarantee to find a root
   // inside [a, b], so we fall back to a secant step should
   // the result be out of range.
   //
   // Start by obtaining the coefficients of the quadratic polynomial:
   //
   T B = safe_div(T(fb - fa), T(b - a), tools::max_value<T>());
   T A = safe_div(T(fd - fb), T(d - b), tools::max_value<T>());
   A = safe_div(T(A - B), T(d - a), T(0));

   if(A == 0)
   {
      // failure to determine coefficients, try a secant step:
      return secant_interpolate(a, b, fa, fb);
   }
   //
   // Determine the starting point of the Newton steps:
   //
   T c;
   if(boost::math::sign(A) * boost::math::sign(fa) > 0)
   {
      c = a;
   }
   else
   {
      c = b;
   }
   //
   // Take the Newton steps:
   //
   for(unsigned i = 1; i <= count; ++i)
   {
      //c -= safe_div(B * c, (B + A * (2 * c - a - b)), 1 + c - a);
      c -= safe_div(T(fa+(B+A*(c-b))*(c-a)), T(B + A * (2 * c - a - b)), T(1 + c - a));
   }
   if((c <= a) || (c >= b))
   {
      // Oops, failure, try a secant step:
      c = secant_interpolate(a, b, fa, fb);
   }
   return c;
}

template <class T>
T cubic_interpolate(const T& a, const T& b, const T& d, 
                    const T& e, const T& fa, const T& fb, 
                    const T& fd, const T& fe)
{
   //
   // Uses inverse cubic interpolation of f(x) at points 
   // [a,b,d,e] to obtain an approximate root of f(x).
   // Points d and e lie outside the interval [a,b]
   // and are the third and forth best approximations
   // to the root that we have found so far.
   //
   // Note: this does not guarantee to find a root
   // inside [a, b], so we fall back to quadratic
   // interpolation in case of an erroneous result.
   //
   BOOST_MATH_INSTRUMENT_CODE(" a = " << a << " b = " << b
      << " d = " << d << " e = " << e << " fa = " << fa << " fb = " << fb 
      << " fd = " << fd << " fe = " << fe);
   T q11 = (d - e) * fd / (fe - fd);
   T q21 = (b - d) * fb / (fd - fb);
   T q31 = (a - b) * fa / (fb - fa);
   T d21 = (b - d) * fd / (fd - fb);
   T d31 = (a - b) * fb / (fb - fa);
   BOOST_MATH_INSTRUMENT_CODE(
      "q11 = " << q11 << " q21 = " << q21 << " q31 = " << q31
      << " d21 = " << d21 << " d31 = " << d31);
   T q22 = (d21 - q11) * fb / (fe - fb);
   T q32 = (d31 - q21) * fa / (fd - fa);
   T d32 = (d31 - q21) * fd / (fd - fa);
   T q33 = (d32 - q22) * fa / (fe - fa);
   T c = q31 + q32 + q33 + a;
   BOOST_MATH_INSTRUMENT_CODE(
      "q22 = " << q22 << " q32 = " << q32 << " d32 = " << d32
      << " q33 = " << q33 << " c = " << c);

   if((c <= a) || (c >= b))
   {
      // Out of bounds step, fall back to quadratic interpolation:
      c = quadratic_interpolate(a, b, d, fa, fb, fd, 3);
   BOOST_MATH_INSTRUMENT_CODE(
      "Out of bounds interpolation, falling back to quadratic interpolation. c = " << c);
   }

   return c;
}

} // namespace detail

template <class F, class T, class Tol, class Policy>
std::pair<T, T> toms748_solve(F f, const T& ax, const T& bx, const T& fax, const T& fbx, Tol tol, boost::uintmax_t& max_iter, const Policy& pol)
{
   //
   // Main entry point and logic for Toms Algorithm 748
   // root finder.
   //
   BOOST_MATH_STD_USING  // For ADL of std math functions

   static const char* function = "boost::math::tools::toms748_solve<%1%>";

   //
   // Sanity check - are we allowed to iterate at all?
   //
   if (max_iter == 0)
      return std::make_pair(ax, bx);

   boost::uintmax_t count = max_iter;
   T a, b, fa, fb, c, u, fu, a0, b0, d, fd, e, fe;
   static const T mu = 0.5f;

   // initialise a, b and fa, fb:
   a = ax;
   b = bx;
   if(a >= b)
      return boost::math::detail::pair_from_single(policies::raise_domain_error(
         function, 
         "Parameters a and b out of order: a=%1%", a, pol));
   fa = fax;
   fb = fbx;

   if(tol(a, b) || (fa == 0) || (fb == 0))
   {
      max_iter = 0;
      if(fa == 0)
         b = a;
      else if(fb == 0)
         a = b;
      return std::make_pair(a, b);
   }

   if(boost::math::sign(fa) * boost::math::sign(fb) > 0)
      return boost::math::detail::pair_from_single(policies::raise_domain_error(
         function, 
         "Parameters a and b do not bracket the root: a=%1%", a, pol));
   // dummy value for fd, e and fe:
   fe = e = fd = 1e5F;

   if(fa != 0)
   {
      //
      // On the first step we take a secant step:
      //
      c = detail::secant_interpolate(a, b, fa, fb);
      detail::bracket(f, a, b, c, fa, fb, d, fd);
      --count;
      BOOST_MATH_INSTRUMENT_CODE(" a = " << a << " b = " << b);

      if(count && (fa != 0) && !tol(a, b))
      {
         //
         // On the second step we take a quadratic interpolation:
         //
         c = detail::quadratic_interpolate(a, b, d, fa, fb, fd, 2);
         e = d;
         fe = fd;
         detail::bracket(f, a, b, c, fa, fb, d, fd);
         --count;
         BOOST_MATH_INSTRUMENT_CODE(" a = " << a << " b = " << b);
      }
   }

   while(count && (fa != 0) && !tol(a, b))
   {
      // save our brackets:
      a0 = a;
      b0 = b;
      //
      // Starting with the third step taken
      // we can use either quadratic or cubic interpolation.
      // Cubic interpolation requires that all four function values
      // fa, fb, fd, and fe are distinct, should that not be the case
      // then variable prof will get set to true, and we'll end up
      // taking a quadratic step instead.
      //
      T min_diff = tools::min_value<T>() * 32;
      bool prof = (fabs(fa - fb) < min_diff) || (fabs(fa - fd) < min_diff) || (fabs(fa - fe) < min_diff) || (fabs(fb - fd) < min_diff) || (fabs(fb - fe) < min_diff) || (fabs(fd - fe) < min_diff);
      if(prof)
      {
         c = detail::quadratic_interpolate(a, b, d, fa, fb, fd, 2);
         BOOST_MATH_INSTRUMENT_CODE("Can't take cubic step!!!!");
      }
      else
      {
         c = detail::cubic_interpolate(a, b, d, e, fa, fb, fd, fe);
      }
      //
      // re-bracket, and check for termination:
      //
      e = d;
      fe = fd;
      detail::bracket(f, a, b, c, fa, fb, d, fd);
      if((0 == --count) || (fa == 0) || tol(a, b))
         break;
      BOOST_MATH_INSTRUMENT_CODE(" a = " << a << " b = " << b);
      //
      // Now another interpolated step:
      //
      prof = (fabs(fa - fb) < min_diff) || (fabs(fa - fd) < min_diff) || (fabs(fa - fe) < min_diff) || (fabs(fb - fd) < min_diff) || (fabs(fb - fe) < min_diff) || (fabs(fd - fe) < min_diff);
      if(prof)
      {
         c = detail::quadratic_interpolate(a, b, d, fa, fb, fd, 3);
         BOOST_MATH_INSTRUMENT_CODE("Can't take cubic step!!!!");
      }
      else
      {
         c = detail::cubic_interpolate(a, b, d, e, fa, fb, fd, fe);
      }
      //
      // Bracket again, and check termination condition, update e:
      //
      detail::bracket(f, a, b, c, fa, fb, d, fd);
      if((0 == --count) || (fa == 0) || tol(a, b))
         break;
      BOOST_MATH_INSTRUMENT_CODE(" a = " << a << " b = " << b);
      //
      // Now we take a double-length secant step:
      //
      if(fabs(fa) < fabs(fb))
      {
         u = a;
         fu = fa;
      }
      else
      {
         u = b;
         fu = fb;
      }
      c = u - 2 * (fu / (fb - fa)) * (b - a);
      if(fabs(c - u) > (b - a) / 2)
      {
         c = a + (b - a) / 2;
      }
      //
      // Bracket again, and check termination condition:
      //
      e = d;
      fe = fd;
      detail::bracket(f, a, b, c, fa, fb, d, fd);
      BOOST_MATH_INSTRUMENT_CODE(" a = " << a << " b = " << b);
      BOOST_MATH_INSTRUMENT_CODE(" tol = " << T((fabs(a) - fabs(b)) / fabs(a)));
      if((0 == --count) || (fa == 0) || tol(a, b))
         break;
      //
      // And finally... check to see if an additional bisection step is 
      // to be taken, we do this if we're not converging fast enough:
      //
      if((b - a) < mu * (b0 - a0))
         continue;
      //
      // bracket again on a bisection:
      //
      e = d;
      fe = fd;
      detail::bracket(f, a, b, T(a + (b - a) / 2), fa, fb, d, fd);
      --count;
      BOOST_MATH_INSTRUMENT_CODE("Not converging: Taking a bisection!!!!");
      BOOST_MATH_INSTRUMENT_CODE(" a = " << a << " b = " << b);
   } // while loop

   max_iter -= count;
   if(fa == 0)
   {
      b = a;
   }
   else if(fb == 0)
   {
      a = b;
   }
   BOOST_MATH_LOG_COUNT(max_iter)
   return std::make_pair(a, b);
}

template <class F, class T, class Tol>
inline std::pair<T, T> toms748_solve(F f, const T& ax, const T& bx, const T& fax, const T& fbx, Tol tol, boost::uintmax_t& max_iter)
{
   return toms748_solve(f, ax, bx, fax, fbx, tol, max_iter, policies::policy<>());
}

template <class F, class T, class Tol, class Policy>
inline std::pair<T, T> toms748_solve(F f, const T& ax, const T& bx, Tol tol, boost::uintmax_t& max_iter, const Policy& pol)
{
   if (max_iter <= 2)
      return std::make_pair(ax, bx);
   max_iter -= 2;
   std::pair<T, T> r = toms748_solve(f, ax, bx, f(ax), f(bx), tol, max_iter, pol);
   max_iter += 2;
   return r;
}

template <class F, class T, class Tol>
inline std::pair<T, T> toms748_solve(F f, const T& ax, const T& bx, Tol tol, boost::uintmax_t& max_iter)
{
   return toms748_solve(f, ax, bx, tol, max_iter, policies::policy<>());
}

template <class F, class T, class Tol, class Policy>
std::pair<T, T> bracket_and_solve_root(F f, const T& guess, T factor, bool rising, Tol tol, boost::uintmax_t& max_iter, const Policy& pol)
{
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::tools::bracket_and_solve_root<%1%>";
   //
   // Set up initial brackets:
   //
   T a = guess;
   T b = a;
   T fa = f(a);
   T fb = fa;
   //
   // Set up invocation count:
   //
   boost::uintmax_t count = max_iter - 1;

   int step = 32;

   if((fa < 0) == (guess < 0 ? !rising : rising))
   {
      //
      // Zero is to the right of b, so walk upwards
      // until we find it:
      //
      while((boost::math::sign)(fb) == (boost::math::sign)(fa))
      {
         if(count == 0)
            return boost::math::detail::pair_from_single(policies::raise_evaluation_error(function, "Unable to bracket root, last nearest value was %1%", b, pol));
         //
         // Heuristic: normally it's best not to increase the step sizes as we'll just end up
         // with a really wide range to search for the root.  However, if the initial guess was *really*
         // bad then we need to speed up the search otherwise we'll take forever if we're orders of
         // magnitude out.  This happens most often if the guess is a small value (say 1) and the result
         // we're looking for is close to std::numeric_limits<T>::min().
         //
         if((max_iter - count) % step == 0)
         {
            factor *= 2;
            if(step > 1) step /= 2;
         }
         //
         // Now go ahead and move our guess by "factor":
         //
         a = b;
         fa = fb;
         b *= factor;
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
      while((boost::math::sign)(fb) == (boost::math::sign)(fa))
      {
         if(fabs(a) < tools::min_value<T>())
         {
            // Escape route just in case the answer is zero!
            max_iter -= count;
            max_iter += 1;
            return a > 0 ? std::make_pair(T(0), T(a)) : std::make_pair(T(a), T(0)); 
         }
         if(count == 0)
            return boost::math::detail::pair_from_single(policies::raise_evaluation_error(function, "Unable to bracket root, last nearest value was %1%", a, pol));
         //
         // Heuristic: normally it's best not to increase the step sizes as we'll just end up
         // with a really wide range to search for the root.  However, if the initial guess was *really*
         // bad then we need to speed up the search otherwise we'll take forever if we're orders of
         // magnitude out.  This happens most often if the guess is a small value (say 1) and the result
         // we're looking for is close to std::numeric_limits<T>::min().
         //
         if((max_iter - count) % step == 0)
         {
            factor *= 2;
            if(step > 1) step /= 2;
         }
         //
         // Now go ahead and move are guess by "factor":
         //
         b = a;
         fb = fa;
         a /= factor;
         fa = f(a);
         --count;
         BOOST_MATH_INSTRUMENT_CODE("a = " << a << " b = " << b << " fa = " << fa << " fb = " << fb << " count = " << count);
      }
   }
   max_iter -= count;
   max_iter += 1;
   std::pair<T, T> r = toms748_solve(
      f, 
      (a < 0 ? b : a), 
      (a < 0 ? a : b), 
      (a < 0 ? fb : fa), 
      (a < 0 ? fa : fb), 
      tol, 
      count, 
      pol);
   max_iter += count;
   BOOST_MATH_INSTRUMENT_CODE("max_iter = " << max_iter << " count = " << count);
   BOOST_MATH_LOG_COUNT(max_iter)
   return r;
}

template <class F, class T, class Tol>
inline std::pair<T, T> bracket_and_solve_root(F f, const T& guess, const T& factor, bool rising, Tol tol, boost::uintmax_t& max_iter)
{
   return bracket_and_solve_root(f, guess, factor, rising, tol, max_iter, policies::policy<>());
}

} // namespace tools
} // namespace math
} // namespace boost


#endif // BOOST_MATH_TOOLS_SOLVE_ROOT_HPP


/* toms748_solve.hpp
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
*/