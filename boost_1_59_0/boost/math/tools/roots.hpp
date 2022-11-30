//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_NEWTON_SOLVER_HPP
#define BOOST_MATH_TOOLS_NEWTON_SOLVER_HPP

#ifdef _MSC_VER
#pragma once
#endif
#include <boost/math/tools/complex.hpp> // test for multiprecision types in complex Newton

#include <utility>
#include <cmath>
#include <tuple>
#include <cstdint>

#include <boost/math/tools/config.hpp>
#include <boost/math/tools/cxx03_warn.hpp>

#include <boost/math/special_functions/sign.hpp>
#include <boost/math/special_functions/next.hpp>
#include <boost/math/tools/toms748_solve.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost {
namespace math {
namespace tools {

namespace detail {

namespace dummy {

   template<int n, class T>
   typename T::value_type get(const T&) BOOST_MATH_NOEXCEPT(T);
}

template <class Tuple, class T>
void unpack_tuple(const Tuple& t, T& a, T& b) BOOST_MATH_NOEXCEPT(T)
{
   using dummy::get;
   // Use ADL to find the right overload for get:
   a = get<0>(t);
   b = get<1>(t);
}
template <class Tuple, class T>
void unpack_tuple(const Tuple& t, T& a, T& b, T& c) BOOST_MATH_NOEXCEPT(T)
{
   using dummy::get;
   // Use ADL to find the right overload for get:
   a = get<0>(t);
   b = get<1>(t);
   c = get<2>(t);
}

template <class Tuple, class T>
inline void unpack_0(const Tuple& t, T& val) BOOST_MATH_NOEXCEPT(T)
{
   using dummy::get;
   // Rely on ADL to find the correct overload of get:
   val = get<0>(t);
}

template <class T, class U, class V>
inline void unpack_tuple(const std::pair<T, U>& p, V& a, V& b) BOOST_MATH_NOEXCEPT(T)
{
   a = p.first;
   b = p.second;
}
template <class T, class U, class V>
inline void unpack_0(const std::pair<T, U>& p, V& a) BOOST_MATH_NOEXCEPT(T)
{
   a = p.first;
}

template <class F, class T>
void handle_zero_derivative(F f,
   T& last_f0,
   const T& f0,
   T& delta,
   T& result,
   T& guess,
   const T& min,
   const T& max) noexcept(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   if (last_f0 == 0)
   {
      // this must be the first iteration, pretend that we had a
      // previous one at either min or max:
      if (result == min)
      {
         guess = max;
      }
      else
      {
         guess = min;
      }
      unpack_0(f(guess), last_f0);
      delta = guess - result;
   }
   if (sign(last_f0) * sign(f0) < 0)
   {
      // we've crossed over so move in opposite direction to last step:
      if (delta < 0)
      {
         delta = (result - min) / 2;
      }
      else
      {
         delta = (result - max) / 2;
      }
   }
   else
   {
      // move in same direction as last step:
      if (delta < 0)
      {
         delta = (result - max) / 2;
      }
      else
      {
         delta = (result - min) / 2;
      }
   }
}

} // namespace

template <class F, class T, class Tol, class Policy>
std::pair<T, T> bisect(F f, T min, T max, Tol tol, std::uintmax_t& max_iter, const Policy& pol) noexcept(policies::is_noexcept_error_policy<Policy>::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   T fmin = f(min);
   T fmax = f(max);
   if (fmin == 0)
   {
      max_iter = 2;
      return std::make_pair(min, min);
   }
   if (fmax == 0)
   {
      max_iter = 2;
      return std::make_pair(max, max);
   }

   //
   // Error checking:
   //
   static const char* function = "boost::math::tools::bisect<%1%>";
   if (min >= max)
   {
      return boost::math::detail::pair_from_single(policies::raise_evaluation_error(function,
         "Arguments in wrong order in boost::math::tools::bisect (first arg=%1%)", min, pol));
   }
   if (fmin * fmax >= 0)
   {
      return boost::math::detail::pair_from_single(policies::raise_evaluation_error(function,
         "No change of sign in boost::math::tools::bisect, either there is no root to find, or there are multiple roots in the interval (f(min) = %1%).", fmin, pol));
   }

   //
   // Three function invocations so far:
   //
   std::uintmax_t count = max_iter;
   if (count < 3)
      count = 0;
   else
      count -= 3;

   while (count && (0 == tol(min, max)))
   {
      T mid = (min + max) / 2;
      T fmid = f(mid);
      if ((mid == max) || (mid == min))
         break;
      if (fmid == 0)
      {
         min = max = mid;
         break;
      }
      else if (sign(fmid) * sign(fmin) < 0)
      {
         max = mid;
      }
      else
      {
         min = mid;
         fmin = fmid;
      }
      --count;
   }

   max_iter -= count;

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Bisection required " << max_iter << " iterations.\n";
#endif

   return std::make_pair(min, max);
}

template <class F, class T, class Tol>
inline std::pair<T, T> bisect(F f, T min, T max, Tol tol, std::uintmax_t& max_iter)  noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   return bisect(f, min, max, tol, max_iter, policies::policy<>());
}

template <class F, class T, class Tol>
inline std::pair<T, T> bisect(F f, T min, T max, Tol tol) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   std::uintmax_t m = (std::numeric_limits<std::uintmax_t>::max)();
   return bisect(f, min, max, tol, m, policies::policy<>());
}


template <class F, class T>
T newton_raphson_iterate(F f, T guess, T min, T max, int digits, std::uintmax_t& max_iter) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   BOOST_MATH_STD_USING

   static const char* function = "boost::math::tools::newton_raphson_iterate<%1%>";
   if (min > max)
   {
      return policies::raise_evaluation_error(function, "Range arguments in wrong order in boost::math::tools::newton_raphson_iterate(first arg=%1%)", min, boost::math::policies::policy<>());
   }

   T f0(0), f1, last_f0(0);
   T result = guess;

   T factor = static_cast<T>(ldexp(1.0, 1 - digits));
   T delta = tools::max_value<T>();
   T delta1 = tools::max_value<T>();
   T delta2 = tools::max_value<T>();

   //
   // We use these to sanity check that we do actually bracket a root,
   // we update these to the function value when we update the endpoints
   // of the range.  Then, provided at some point we update both endpoints
   // checking that max_range_f * min_range_f <= 0 verifies there is a root
   // to be found somewhere.  Note that if there is no root, and we approach 
   // a local minima, then the derivative will go to zero, and hence the next
   // step will jump out of bounds (or at least past the minima), so this
   // check *should* happen in pathological cases.
   //
   T max_range_f = 0;
   T min_range_f = 0;

   std::uintmax_t count(max_iter);

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Newton_raphson_iterate, guess = " << guess << ", min = " << min << ", max = " << max
      << ", digits = " << digits << ", max_iter = " << max_iter << "\n";
#endif

   do {
      last_f0 = f0;
      delta2 = delta1;
      delta1 = delta;
      detail::unpack_tuple(f(result), f0, f1);
      --count;
      if (0 == f0)
         break;
      if (f1 == 0)
      {
         // Oops zero derivative!!!
         detail::handle_zero_derivative(f, last_f0, f0, delta, result, guess, min, max);
      }
      else
      {
         delta = f0 / f1;
      }
#ifdef BOOST_MATH_INSTRUMENT
      std::cout << "Newton iteration " << max_iter - count << ", delta = " << delta << ", residual = " << f0 << "\n";
#endif
      if (fabs(delta * 2) > fabs(delta2))
      {
         // Last two steps haven't converged.
         T shift = (delta > 0) ? (result - min) / 2 : (result - max) / 2;
         if ((result != 0) && (fabs(shift) > fabs(result)))
         {
            delta = sign(delta) * fabs(result) * 1.1f; // Protect against huge jumps!
            //delta = sign(delta) * result; // Protect against huge jumps! Failed for negative result. https://github.com/boostorg/math/issues/216
         }
         else
            delta = shift;
         // reset delta1/2 so we don't take this branch next time round:
         delta1 = 3 * delta;
         delta2 = 3 * delta;
      }
      guess = result;
      result -= delta;
      if (result <= min)
      {
         delta = 0.5F * (guess - min);
         result = guess - delta;
         if ((result == min) || (result == max))
            break;
      }
      else if (result >= max)
      {
         delta = 0.5F * (guess - max);
         result = guess - delta;
         if ((result == min) || (result == max))
            break;
      }
      // Update brackets:
      if (delta > 0)
      {
         max = guess;
         max_range_f = f0;
      }
      else
      {
         min = guess;
         min_range_f = f0;
      }
      //
      // Sanity check that we bracket the root:
      //
      if (max_range_f * min_range_f > 0)
      {
         return policies::raise_evaluation_error(function, "There appears to be no root to be found in boost::math::tools::newton_raphson_iterate, perhaps we have a local minima near current best guess of %1%", guess, boost::math::policies::policy<>());
      }
   }while(count && (fabs(result * factor) < fabs(delta)));

   max_iter -= count;

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Newton Raphson required " << max_iter << " iterations\n";
#endif

   return result;
}

template <class F, class T>
inline T newton_raphson_iterate(F f, T guess, T min, T max, int digits) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   std::uintmax_t m = (std::numeric_limits<std::uintmax_t>::max)();
   return newton_raphson_iterate(f, guess, min, max, digits, m);
}

namespace detail {

   struct halley_step
   {
      template <class T>
      static T step(const T& /*x*/, const T& f0, const T& f1, const T& f2) noexcept(BOOST_MATH_IS_FLOAT(T))
      {
         using std::fabs;
         T denom = 2 * f0;
         T num = 2 * f1 - f0 * (f2 / f1);
         T delta;

         BOOST_MATH_INSTRUMENT_VARIABLE(denom);
         BOOST_MATH_INSTRUMENT_VARIABLE(num);

         if ((fabs(num) < 1) && (fabs(denom) >= fabs(num) * tools::max_value<T>()))
         {
            // possible overflow, use Newton step:
            delta = f0 / f1;
         }
         else
            delta = denom / num;
         return delta;
      }
   };

   template <class F, class T>
   T bracket_root_towards_min(F f, T guess, const T& f0, T& min, T& max, std::uintmax_t& count) noexcept(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())));

   template <class F, class T>
   T bracket_root_towards_max(F f, T guess, const T& f0, T& min, T& max, std::uintmax_t& count) noexcept(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
   {
      using std::fabs;
      //
      // Move guess towards max until we bracket the root, updating min and max as we go:
      //
      T guess0 = guess;
      T multiplier = 2;
      T f_current = f0;
      if (fabs(min) < fabs(max))
      {
         while (--count && ((f_current < 0) == (f0 < 0)))
         {
            min = guess;
            guess *= multiplier;
            if (guess > max)
            {
               guess = max;
               f_current = -f_current;  // There must be a change of sign!
               break;
            }
            multiplier *= 2;
            unpack_0(f(guess), f_current);
         }
      }
      else
      {
         //
         // If min and max are negative we have to divide to head towards max:
         //
         while (--count && ((f_current < 0) == (f0 < 0)))
         {
            min = guess;
            guess /= multiplier;
            if (guess > max)
            {
               guess = max;
               f_current = -f_current;  // There must be a change of sign!
               break;
            }
            multiplier *= 2;
            unpack_0(f(guess), f_current);
         }
      }

      if (count)
      {
         max = guess;
         if (multiplier > 16)
            return (guess0 - guess) + bracket_root_towards_min(f, guess, f_current, min, max, count);
      }
      return guess0 - (max + min) / 2;
   }

   template <class F, class T>
   T bracket_root_towards_min(F f, T guess, const T& f0, T& min, T& max, std::uintmax_t& count) noexcept(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
   {
      using std::fabs;
      //
      // Move guess towards min until we bracket the root, updating min and max as we go:
      //
      T guess0 = guess;
      T multiplier = 2;
      T f_current = f0;

      if (fabs(min) < fabs(max))
      {
         while (--count && ((f_current < 0) == (f0 < 0)))
         {
            max = guess;
            guess /= multiplier;
            if (guess < min)
            {
               guess = min;
               f_current = -f_current;  // There must be a change of sign!
               break;
            }
            multiplier *= 2;
            unpack_0(f(guess), f_current);
         }
      }
      else
      {
         //
         // If min and max are negative we have to multiply to head towards min:
         //
         while (--count && ((f_current < 0) == (f0 < 0)))
         {
            max = guess;
            guess *= multiplier;
            if (guess < min)
            {
               guess = min;
               f_current = -f_current;  // There must be a change of sign!
               break;
            }
            multiplier *= 2;
            unpack_0(f(guess), f_current);
         }
      }

      if (count)
      {
         min = guess;
         if (multiplier > 16)
            return (guess0 - guess) + bracket_root_towards_max(f, guess, f_current, min, max, count);
      }
      return guess0 - (max + min) / 2;
   }

   template <class Stepper, class F, class T>
   T second_order_root_finder(F f, T guess, T min, T max, int digits, std::uintmax_t& max_iter) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
   {
      BOOST_MATH_STD_USING

#ifdef BOOST_MATH_INSTRUMENT
        std::cout << "Second order root iteration, guess = " << guess << ", min = " << min << ", max = " << max
        << ", digits = " << digits << ", max_iter = " << max_iter << "\n";
#endif
      static const char* function = "boost::math::tools::halley_iterate<%1%>";
      if (min >= max)
      {
         return policies::raise_evaluation_error(function, "Range arguments in wrong order in boost::math::tools::halley_iterate(first arg=%1%)", min, boost::math::policies::policy<>());
      }

      T f0(0), f1, f2;
      T result = guess;

      T factor = ldexp(static_cast<T>(1.0), 1 - digits);
      T delta = (std::max)(T(10000000 * guess), T(10000000));  // arbitrarily large delta
      T last_f0 = 0;
      T delta1 = delta;
      T delta2 = delta;
      bool out_of_bounds_sentry = false;

   #ifdef BOOST_MATH_INSTRUMENT
      std::cout << "Second order root iteration, limit = " << factor << "\n";
   #endif

      //
      // We use these to sanity check that we do actually bracket a root,
      // we update these to the function value when we update the endpoints
      // of the range.  Then, provided at some point we update both endpoints
      // checking that max_range_f * min_range_f <= 0 verifies there is a root
      // to be found somewhere.  Note that if there is no root, and we approach 
      // a local minima, then the derivative will go to zero, and hence the next
      // step will jump out of bounds (or at least past the minima), so this
      // check *should* happen in pathological cases.
      //
      T max_range_f = 0;
      T min_range_f = 0;

      std::uintmax_t count(max_iter);

      do {
         last_f0 = f0;
         delta2 = delta1;
         delta1 = delta;
         detail::unpack_tuple(f(result), f0, f1, f2);
         --count;

         BOOST_MATH_INSTRUMENT_VARIABLE(f0);
         BOOST_MATH_INSTRUMENT_VARIABLE(f1);
         BOOST_MATH_INSTRUMENT_VARIABLE(f2);

         if (0 == f0)
            break;
         if (f1 == 0)
         {
            // Oops zero derivative!!!
            detail::handle_zero_derivative(f, last_f0, f0, delta, result, guess, min, max);
         }
         else
         {
            if (f2 != 0)
            {
               delta = Stepper::step(result, f0, f1, f2);
               if (delta * f1 / f0 < 0)
               {
                  // Oh dear, we have a problem as Newton and Halley steps
                  // disagree about which way we should move.  Probably
                  // there is cancelation error in the calculation of the
                  // Halley step, or else the derivatives are so small
                  // that their values are basically trash.  We will move
                  // in the direction indicated by a Newton step, but
                  // by no more than twice the current guess value, otherwise
                  // we can jump way out of bounds if we're not careful.
                  // See https://svn.boost.org/trac/boost/ticket/8314.
                  delta = f0 / f1;
                  if (fabs(delta) > 2 * fabs(guess))
                     delta = (delta < 0 ? -1 : 1) * 2 * fabs(guess);
               }
            }
            else
               delta = f0 / f1;
         }
   #ifdef BOOST_MATH_INSTRUMENT
         std::cout << "Second order root iteration, delta = " << delta << ", residual = " << f0 << "\n";
   #endif
         T convergence = fabs(delta / delta2);
         if ((convergence > 0.8) && (convergence < 2))
         {
            // last two steps haven't converged.
            delta = (delta > 0) ? (result - min) / 2 : (result - max) / 2;
            if ((result != 0) && (fabs(delta) > result))
               delta = sign(delta) * fabs(result) * 0.9f; // protect against huge jumps!
            // reset delta2 so that this branch will *not* be taken on the
            // next iteration:
            delta2 = delta * 3;
            delta1 = delta * 3;
            BOOST_MATH_INSTRUMENT_VARIABLE(delta);
         }
         guess = result;
         result -= delta;
         BOOST_MATH_INSTRUMENT_VARIABLE(result);

         // check for out of bounds step:
         if (result < min)
         {
            T diff = ((fabs(min) < 1) && (fabs(result) > 1) && (tools::max_value<T>() / fabs(result) < fabs(min)))
               ? T(1000)
               : (fabs(min) < 1) && (fabs(tools::max_value<T>() * min) < fabs(result))
               ? ((min < 0) != (result < 0)) ? -tools::max_value<T>() : tools::max_value<T>() : T(result / min);
            if (fabs(diff) < 1)
               diff = 1 / diff;
            if (!out_of_bounds_sentry && (diff > 0) && (diff < 3))
            {
               // Only a small out of bounds step, lets assume that the result
               // is probably approximately at min:
               delta = 0.99f * (guess - min);
               result = guess - delta;
               out_of_bounds_sentry = true; // only take this branch once!
            }
            else
            {
               if (fabs(float_distance(min, max)) < 2)
               {
                  result = guess = (min + max) / 2;
                  break;
               }
               delta = bracket_root_towards_min(f, guess, f0, min, max, count);
               result = guess - delta;
               guess = min;
               continue;
            }
         }
         else if (result > max)
         {
            T diff = ((fabs(max) < 1) && (fabs(result) > 1) && (tools::max_value<T>() / fabs(result) < fabs(max))) ? T(1000) : T(result / max);
            if (fabs(diff) < 1)
               diff = 1 / diff;
            if (!out_of_bounds_sentry && (diff > 0) && (diff < 3))
            {
               // Only a small out of bounds step, lets assume that the result
               // is probably approximately at min:
               delta = 0.99f * (guess - max);
               result = guess - delta;
               out_of_bounds_sentry = true; // only take this branch once!
            }
            else
            {
               if (fabs(float_distance(min, max)) < 2)
               {
                  result = guess = (min + max) / 2;
                  break;
               }
               delta = bracket_root_towards_max(f, guess, f0, min, max, count);
               result = guess - delta;
               guess = min;
               continue;
            }
         }
         // update brackets:
         if (delta > 0)
         {
            max = guess;
            max_range_f = f0;
         }
         else
         {
            min = guess;
            min_range_f = f0;
         }
         //
         // Sanity check that we bracket the root:
         //
         if (max_range_f * min_range_f > 0)
         {
            return policies::raise_evaluation_error(function, "There appears to be no root to be found in boost::math::tools::newton_raphson_iterate, perhaps we have a local minima near current best guess of %1%", guess, boost::math::policies::policy<>());
         }
      } while(count && (fabs(result * factor) < fabs(delta)));

      max_iter -= count;

   #ifdef BOOST_MATH_INSTRUMENT
      std::cout << "Second order root finder required " << max_iter << " iterations.\n";
   #endif

      return result;
   }
} // T second_order_root_finder

template <class F, class T>
T halley_iterate(F f, T guess, T min, T max, int digits, std::uintmax_t& max_iter) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   return detail::second_order_root_finder<detail::halley_step>(f, guess, min, max, digits, max_iter);
}

template <class F, class T>
inline T halley_iterate(F f, T guess, T min, T max, int digits) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   std::uintmax_t m = (std::numeric_limits<std::uintmax_t>::max)();
   return halley_iterate(f, guess, min, max, digits, m);
}

namespace detail {

   struct schroder_stepper
   {
      template <class T>
      static T step(const T& x, const T& f0, const T& f1, const T& f2) noexcept(BOOST_MATH_IS_FLOAT(T))
      {
         using std::fabs;
         T ratio = f0 / f1;
         T delta;
         if ((x != 0) && (fabs(ratio / x) < 0.1))
         {
            delta = ratio + (f2 / (2 * f1)) * ratio * ratio;
            // check second derivative doesn't over compensate:
            if (delta * ratio < 0)
               delta = ratio;
         }
         else
            delta = ratio;  // fall back to Newton iteration.
         return delta;
      }
   };

}

template <class F, class T>
T schroder_iterate(F f, T guess, T min, T max, int digits, std::uintmax_t& max_iter) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   return detail::second_order_root_finder<detail::schroder_stepper>(f, guess, min, max, digits, max_iter);
}

template <class F, class T>
inline T schroder_iterate(F f, T guess, T min, T max, int digits) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   std::uintmax_t m = (std::numeric_limits<std::uintmax_t>::max)();
   return schroder_iterate(f, guess, min, max, digits, m);
}
//
// These two are the old spelling of this function, retained for backwards compatibility just in case:
//
template <class F, class T>
T schroeder_iterate(F f, T guess, T min, T max, int digits, std::uintmax_t& max_iter) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   return detail::second_order_root_finder<detail::schroder_stepper>(f, guess, min, max, digits, max_iter);
}

template <class F, class T>
inline T schroeder_iterate(F f, T guess, T min, T max, int digits) noexcept(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   std::uintmax_t m = (std::numeric_limits<std::uintmax_t>::max)();
   return schroder_iterate(f, guess, min, max, digits, m);
}

#ifndef BOOST_NO_CXX11_AUTO_DECLARATIONS
/*
   * Why do we set the default maximum number of iterations to the number of digits in the type?
   * Because for double roots, the number of digits increases linearly with the number of iterations,
   * so this default should recover full precision even in this somewhat pathological case.
   * For isolated roots, the problem is so rapidly convergent that this doesn't matter at all.
   */
template<class Complex, class F>
Complex complex_newton(F g, Complex guess, int max_iterations = std::numeric_limits<typename Complex::value_type>::digits)
{
   typedef typename Complex::value_type Real;
   using std::norm;
   using std::abs;
   using std::max;
   // z0, z1, and z2 cannot be the same, in case we immediately need to resort to Muller's Method:
   Complex z0 = guess + Complex(1, 0);
   Complex z1 = guess + Complex(0, 1);
   Complex z2 = guess;

   do {
      auto pair = g(z2);
      if (norm(pair.second) == 0)
      {
         // Muller's method. Notation follows Numerical Recipes, 9.5.2:
         Complex q = (z2 - z1) / (z1 - z0);
         auto P0 = g(z0);
         auto P1 = g(z1);
         Complex qp1 = static_cast<Complex>(1) + q;
         Complex A = q * (pair.first - qp1 * P1.first + q * P0.first);

         Complex B = (static_cast<Complex>(2) * q + static_cast<Complex>(1)) * pair.first - qp1 * qp1 * P1.first + q * q * P0.first;
         Complex C = qp1 * pair.first;
         Complex rad = sqrt(B * B - static_cast<Complex>(4) * A * C);
         Complex denom1 = B + rad;
         Complex denom2 = B - rad;
         Complex correction = (z1 - z2) * static_cast<Complex>(2) * C;
         if (norm(denom1) > norm(denom2))
         {
            correction /= denom1;
         }
         else
         {
            correction /= denom2;
         }

         z0 = z1;
         z1 = z2;
         z2 = z2 + correction;
      }
      else
      {
         z0 = z1;
         z1 = z2;
         z2 = z2 - (pair.first / pair.second);
      }

      // See: https://math.stackexchange.com/questions/3017766/constructing-newton-iteration-converging-to-non-root
      // If f' is continuous, then convergence of x_n -> x* implies f(x*) = 0.
      // This condition approximates this convergence condition by requiring three consecutive iterates to be clustered.
      Real tol = (max)(abs(z2) * std::numeric_limits<Real>::epsilon(), std::numeric_limits<Real>::epsilon());
      bool real_close = abs(z0.real() - z1.real()) < tol && abs(z0.real() - z2.real()) < tol && abs(z1.real() - z2.real()) < tol;
      bool imag_close = abs(z0.imag() - z1.imag()) < tol && abs(z0.imag() - z2.imag()) < tol && abs(z1.imag() - z2.imag()) < tol;
      if (real_close && imag_close)
      {
         return z2;
      }

   } while (max_iterations--);

   // The idea is that if we can get abs(f) < eps, we should, but if we go through all these iterations
   // and abs(f) < sqrt(eps), then roundoff error simply does not allow that we can evaluate f to < eps
   // This is somewhat awkward as it isn't scale invariant, but using the Daubechies coefficient example code,
   // I found this condition generates correct roots, whereas the scale invariant condition discussed here:
   // https://scicomp.stackexchange.com/questions/30597/defining-a-condition-number-and-termination-criteria-for-newtons-method
   // allows nonroots to be passed off as roots.
   auto pair = g(z2);
   if (abs(pair.first) < sqrt(std::numeric_limits<Real>::epsilon()))
   {
      return z2;
   }

   return { std::numeric_limits<Real>::quiet_NaN(),
            std::numeric_limits<Real>::quiet_NaN() };
}
#endif


#if !defined(BOOST_NO_CXX17_IF_CONSTEXPR)
// https://stackoverflow.com/questions/48979861/numerically-stable-method-for-solving-quadratic-equations/50065711
namespace detail
{
#if defined(BOOST_GNU_STDLIB) && !defined(_GLIBCXX_USE_C99_MATH_TR1)
inline float fma_workaround(float x, float y, float z) { return ::fmaf(x, y, z); }
inline double fma_workaround(double x, double y, double z) { return ::fma(x, y, z); }
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline long double fma_workaround(long double x, long double y, long double z) { return ::fmal(x, y, z); }
#endif
#endif            
template<class T>
inline T discriminant(T const& a, T const& b, T const& c)
{
   T w = 4 * a * c;
#if defined(BOOST_GNU_STDLIB) && !defined(_GLIBCXX_USE_C99_MATH_TR1)
   T e = fma_workaround(-c, 4 * a, w);
   T f = fma_workaround(b, b, -w);
#else
   T e = std::fma(-c, 4 * a, w);
   T f = std::fma(b, b, -w);
#endif
   return f + e;
}

template<class T>
std::pair<T, T> quadratic_roots_imp(T const& a, T const& b, T const& c)
{
#if defined(BOOST_GNU_STDLIB) && !defined(_GLIBCXX_USE_C99_MATH_TR1)
   using boost::math::copysign;
#else
   using std::copysign;
#endif
   using std::sqrt;
   if constexpr (std::is_floating_point<T>::value)
   {
      T nan = std::numeric_limits<T>::quiet_NaN();
      if (a == 0)
      {
         if (b == 0 && c != 0)
         {
            return std::pair<T, T>(nan, nan);
         }
         else if (b == 0 && c == 0)
         {
            return std::pair<T, T>(0, 0);
         }
         return std::pair<T, T>(-c / b, -c / b);
      }
      if (b == 0)
      {
         T x0_sq = -c / a;
         if (x0_sq < 0) {
            return std::pair<T, T>(nan, nan);
         }
         T x0 = sqrt(x0_sq);
         return std::pair<T, T>(-x0, x0);
      }
      T discriminant = detail::discriminant(a, b, c);
      // Is there a sane way to flush very small negative values to zero?
      // If there is I don't know of it.
      if (discriminant < 0)
      {
         return std::pair<T, T>(nan, nan);
      }
      T q = -(b + copysign(sqrt(discriminant), b)) / T(2);
      T x0 = q / a;
      T x1 = c / q;
      if (x0 < x1)
      {
         return std::pair<T, T>(x0, x1);
      }
      return std::pair<T, T>(x1, x0);
   }
   else if constexpr (boost::math::tools::is_complex_type<T>::value)
   {
      typename T::value_type nan = std::numeric_limits<typename T::value_type>::quiet_NaN();
      if (a.real() == 0 && a.imag() == 0)
      {
         using std::norm;
         if (b.real() == 0 && b.imag() && norm(c) != 0)
         {
            return std::pair<T, T>({ nan, nan }, { nan, nan });
         }
         else if (b.real() == 0 && b.imag() && c.real() == 0 && c.imag() == 0)
         {
            return std::pair<T, T>({ 0,0 }, { 0,0 });
         }
         return std::pair<T, T>(-c / b, -c / b);
      }
      if (b.real() == 0 && b.imag() == 0)
      {
         T x0_sq = -c / a;
         T x0 = sqrt(x0_sq);
         return std::pair<T, T>(-x0, x0);
      }
      // There's no fma for complex types:
      T discriminant = b * b - T(4) * a * c;
      T q = -(b + sqrt(discriminant)) / T(2);
      return std::pair<T, T>(q / a, c / q);
   }
   else // Most likely the type is a boost.multiprecision.
   {    //There is no fma for multiprecision, and in addition it doesn't seem to be useful, so revert to the naive computation.
      T nan = std::numeric_limits<T>::quiet_NaN();
      if (a == 0)
      {
         if (b == 0 && c != 0)
         {
            return std::pair<T, T>(nan, nan);
         }
         else if (b == 0 && c == 0)
         {
            return std::pair<T, T>(0, 0);
         }
         return std::pair<T, T>(-c / b, -c / b);
      }
      if (b == 0)
      {
         T x0_sq = -c / a;
         if (x0_sq < 0) {
            return std::pair<T, T>(nan, nan);
         }
         T x0 = sqrt(x0_sq);
         return std::pair<T, T>(-x0, x0);
      }
      T discriminant = b * b - 4 * a * c;
      if (discriminant < 0)
      {
         return std::pair<T, T>(nan, nan);
      }
      T q = -(b + copysign(sqrt(discriminant), b)) / T(2);
      T x0 = q / a;
      T x1 = c / q;
      if (x0 < x1)
      {
         return std::pair<T, T>(x0, x1);
      }
      return std::pair<T, T>(x1, x0);
   }
}
}  // namespace detail

template<class T1, class T2 = T1, class T3 = T1>
inline std::pair<typename tools::promote_args<T1, T2, T3>::type, typename tools::promote_args<T1, T2, T3>::type> quadratic_roots(T1 const& a, T2 const& b, T3 const& c)
{
   typedef typename tools::promote_args<T1, T2, T3>::type value_type;
   return detail::quadratic_roots_imp(static_cast<value_type>(a), static_cast<value_type>(b), static_cast<value_type>(c));
}

#endif

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_NEWTON_SOLVER_HPP

/* roots.hpp
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
*/