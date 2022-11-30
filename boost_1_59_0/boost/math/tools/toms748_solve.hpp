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
#include <limits>
#include <utility>
#include <cstdint>

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
std::pair<T, T> toms748_solve(F f, const T& ax, const T& bx, const T& fax, const T& fbx, Tol tol, std::uintmax_t& max_iter, const Policy& pol)
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

   std::uintmax_t count = max_iter;
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
inline std::pair<T, T> toms748_solve(F f, const T& ax, const T& bx, const T& fax, const T& fbx, Tol tol, std::uintmax_t& max_iter)
{
   return toms748_solve(f, ax, bx, fax, fbx, tol, max_iter, policies::policy<>());
}

template <class F, class T, class Tol, class Policy>
inline std::pair<T, T> toms748_solve(F f, const T& ax, const T& bx, Tol tol, std::uintmax_t& max_iter, const Policy& pol)
{
   if (max_iter <= 2)
      return std::make_pair(ax, bx);
   max_iter -= 2;
   std::pair<T, T> r = toms748_solve(f, ax, bx, f(ax), f(bx), tol, max_iter, pol);
   max_iter += 2;
   return r;
}

template <class F, class T, class Tol>
inline std::pair<T, T> toms748_solve(F f, const T& ax, const T& bx, Tol tol, std::uintmax_t& max_iter)
{
   return toms748_solve(f, ax, bx, tol, max_iter, policies::policy<>());
}

template <class F, class T, class Tol, class Policy>
std::pair<T, T> bracket_and_solve_root(F f, const T& guess, T factor, bool rising, Tol tol, std::uintmax_t& max_iter, const Policy& pol)
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
   std::uintmax_t count = max_iter - 1;

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
inline std::pair<T, T> bracket_and_solve_root(F f, const T& guess, const T& factor, bool rising, Tol tol, std::uintmax_t& max_iter)
{
   return bracket_and_solve_root(f, guess, factor, rising, tol, max_iter, policies::policy<>());
}

} // namespace tools
} // namespace math
} // namespace boost


#endif // BOOST_MATH_TOOLS_SOLVE_ROOT_HPP


/* toms748_solve.hpp
+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
*/