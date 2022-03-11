//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_NEWTON_SOLVER_HPP
#define BOOST_MATH_TOOLS_NEWTON_SOLVER_HPP

#ifdef _MSC_VER
#pragma once
#endif
#include <boost/math/tools/complex.hpp> // test for multiprecision types.

#include <iostream>
#include <utility>
#include <boost/config/no_tr1/cmath.hpp>
#include <stdexcept>

#include <boost/math/tools/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/math/tools/cxx03_warn.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4512)
#endif
#include <boost/math/tools/tuple.hpp>
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

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
   const T& max) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
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
std::pair<T, T> bisect(F f, T min, T max, Tol tol, boost::uintmax_t& max_iter, const Policy& pol) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<Policy>::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
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
   boost::uintmax_t count = max_iter;
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
   std::cout << "Bisection iteration, final count = " << max_iter << std::endl;

   static boost::uintmax_t max_count = 0;
   if (max_iter > max_count)
   {
      max_count = max_iter;
      std::cout << "Maximum iterations: " << max_iter << std::endl;
   }
#endif

   return std::make_pair(min, max);
}

template <class F, class T, class Tol>
inline std::pair<T, T> bisect(F f, T min, T max, Tol tol, boost::uintmax_t& max_iter)  BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   return bisect(f, min, max, tol, max_iter, policies::policy<>());
}

template <class F, class T, class Tol>
inline std::pair<T, T> bisect(F f, T min, T max, Tol tol) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return bisect(f, min, max, tol, m, policies::policy<>());
}


template <class F, class T>
T newton_raphson_iterate(F f, T guess, T min, T max, int digits, boost::uintmax_t& max_iter) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   BOOST_MATH_STD_USING

   static const char* function = "boost::math::tools::newton_raphson_iterate<%1%>";
   if (min >= max)
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

   boost::uintmax_t count(max_iter);

#ifdef BOOST_MATH_INSTRUMENT
   std::cout << "Newton_raphson_iterate, guess = " << guess << ", min = " << min << ", max = " << max
      << ", digits = " << digits << ", max_iter = " << max_iter << std::endl;
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
#ifdef BOOST_MATH_INSTRUMENT
         std::cout << "Newton iteration, zero derivative found!" << std::endl;
#endif
         detail::handle_zero_derivative(f, last_f0, f0, delta, result, guess, min, max);
      }
      else
      {
         delta = f0 / f1;
      }
#ifdef BOOST_MATH_INSTRUMENT
      std::cout << "Newton iteration " << max_iter - count << ", delta = " << delta << std::endl;
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
   std::cout << "Newton Raphson final iteration count = " << max_iter << std::endl;

   static boost::uintmax_t max_count = 0;
   if (max_iter > max_count)
   {
      max_count = max_iter;
      // std::cout << "Maximum iterations: " << max_iter << std::endl;
      // Puzzled what this tells us, so commented out for now?
   }
#endif

   return result;
}

template <class F, class T>
inline T newton_raphson_iterate(F f, T guess, T min, T max, int digits) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return newton_raphson_iterate(f, guess, min, max, digits, m);
}

namespace detail {

   struct halley_step
   {
      template <class T>
      static T step(const T& /*x*/, const T& f0, const T& f1, const T& f2) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T))
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
   T bracket_root_towards_min(F f, T guess, const T& f0, T& min, T& max, boost::uintmax_t& count) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())));

   template <class F, class T>
   T bracket_root_towards_max(F f, T guess, const T& f0, T& min, T& max, boost::uintmax_t& count) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
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
   T bracket_root_towards_min(F f, T guess, const T& f0, T& min, T& max, boost::uintmax_t& count) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
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
   T second_order_root_finder(F f, T guess, T min, T max, int digits, boost::uintmax_t& max_iter) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
   {
      BOOST_MATH_STD_USING

#ifdef BOOST_MATH_INSTRUMENT
        std::cout << "Second order root iteration, guess = " << guess << ", min = " << min << ", max = " << max
        << ", digits = " << digits << ", max_iter = " << max_iter << std::endl;
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
      std::cout << "Second order root iteration, limit = " << factor << std::endl;
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

      boost::uintmax_t count(max_iter);

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
   #ifdef BOOST_MATH_INSTRUMENT
            std::cout << "Second order root iteration, zero derivative found!" << std::endl;
   #endif
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
         std::cout << "Second order root iteration, delta = " << delta << std::endl;
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
      std::cout << "Second order root finder, final iteration count = " << max_iter << std::endl;
   #endif

      return result;
   }
} // T second_order_root_finder

template <class F, class T>
T halley_iterate(F f, T guess, T min, T max, int digits, boost::uintmax_t& max_iter) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   return detail::second_order_root_finder<detail::halley_step>(f, guess, min, max, digits, max_iter);
}

template <class F, class T>
inline T halley_iterate(F f, T guess, T min, T max, int digits) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return halley_iterate(f, guess, min, max, digits, m);
}

namespace detail {

   struct schroder_stepper
   {
      template <class T>
      static T step(const T& x, const T& f0, const T& f1, const T& f2) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T))
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
T schroder_iterate(F f, T guess, T min, T max, int digits, boost::uintmax_t& max_iter) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   return detail::second_order_root_finder<detail::schroder_stepper>(f, guess, min, max, digits, max_iter);
}

template <class F, class T>
inline T schroder_iterate(F f, T guess, T min, T max, int digits) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return schroder_iterate(f, guess, min, max, digits, m);
}
//
// These two are the old spelling of this function, retained for backwards compatibility just in case:
//
template <class F, class T>
T schroeder_iterate(F f, T guess, T min, T max, int digits, boost::uintmax_t& max_iter) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   return detail::second_order_root_finder<detail::schroder_stepper>(f, guess, min, max, digits, max_iter);
}

template <class F, class T>
inline T schroeder_iterate(F f, T guess, T min, T max, int digits) BOOST_NOEXCEPT_IF(policies::is_noexcept_error_policy<policies::policy<> >::value&& BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
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
IUk60fqE0YIgJC5F6hAwhcU3LT0tv//tT2go+Ku//glvt1vM8Skm7Ehpw/nJih9+8CkPnwQ+ePyAtCkwKiI+FTw9rhB9jSkL+pR4fJ71vDYbTdMFbq/fDRpeR3lWSykgXxslTZ41isNoZEp0bc9ms4UYqQqDd4626enqljhQkrRtC1xzvFryj/7gB/zl33zO16+2OB/QKnB+sqQoDEZccNsF3r29Jvkdz58/4nufPEGJwOe//JKf/uIL1vaEFANJ5IZDEQVVVdG7LV4k/uSf/jP+h//xf+eoOmXTdLzTnqNliVG5aVKLIaIjURiDQVMDeqBsTckjhYUkESk3WHbRcdNG3jWRzW7HyVHL08cnGCdIsUfoEmsNXdeDT9OCn3bOYQVLBEGKIdjPxpMxo6GLPgqSjHtjHJ47MJT3+Ki5keex32zpozLHaPeRBJOkzvsjEMmaGL5GqB7PiiQTlTK4ziEpkKtTfHQUrqETEEtAJ3ayJZmW2F1j0pA9xIRPKV9LmbuR7zqBKUXi0IHcfaTRL8T7rz2w5vf8PjoMIe7Mav6OCOyel5g5qfkjA9OC907m3gXmxsdIBDud4BCPCiGRJFyMWQs+pQEzGnieQ8iDnnIPDgr2IeMYSX368SXPHp/R1w196Kg7hxKSy7MVQiXghO9/6wyJwgeJUOBjSyEVpGNS6rNnV47oWqL3qKRxveL124ame83jRxZZQ3Ve0XYNGx9YusCJaTl7fs7FqeU7Dx9yel4SokeWibWNXBx9SPC3CAF13bOtG6xpWCxKjo9WHPU5HBUqE0yF0KOUnHh3qnKZb4JIOfXxjhRgtVgjCTS7Lc47tDbUyeUKjlTE6IDIrt5ycXnJ73/2bba3f021XPPpd57x8GLJ5dlpZuzrN3R9fv/VskCJHu89z5485Q//4R/z1as3/MV//Cu215nNTyaNkJbWBz785BNuneNnP/4Z6/IUF7fsfM+pLimUQKSA0pDIqiGRRNc13NzcUBjLydGKqbs9kpsWtWZTN2waTx2gVyUv3t7Q90u0SBQC2hhpuhYfAtxhyxzXyVjWzYyGAy4j9tXdLM+cK6xiWOw5WpnTpIKQhxHqZFACZDpcm5M5xNFBCaLcv3ZKdmb4VB88VWWp6zeIdosNC5Aljp6qSsSdwMkdS5NoKfBNoGwjcSEpjs64uelycSdmArhx8xfsCcMOrs0Mm/mmx55XawgipJgion0EJKY+v8P35cAJjTJbd4+5Wx2bPnsWic3/Nh6v51HQPt+b40QROQDOSDH0G4hppxIpi63JQaLHp0QQObIxs/sjlMIKiRKRGBVKQdfvELYiRolKBnzN4/MTmnc7/Acd0loKF7FiiTCZ1iLR0fVZpE8phZYZEMUHWoYJ9pQRf6k0rZN5WLKrOVktIfa8vBVs/uZnKC/42X9s+Yuf/pR1teCf/dEfc3FSobRHyMj6QYk0At8nvIioqOnFLU0X8L6j6xy73Y71eo0xEXAgEkercjg3ga4WpCRYLPTAMOjx3mONJZEXslRwdLTk7du3eeSicbi+w2pJoRRtSCAKCrsgomi2W9aV4M//2fc5OzujKkoQUDc7eu8QIXG8Xudrj8NHSecSQjRI5VnqGxaLC3599Q5jdOaotpGm7fnk48/4l//Hv6LUGq090Sdi5wkxIk1iHRXJlOAdyI4kBMH3fOeyoFxq6t4TRMj9PEHSNlmf3gVB23cYW5CCZbPZUW8s4kzRS0nUJV2IuPWSk7bBe08IMVcRydS4ACFmjMSI3PIvZDawSbc0SbTY84oTuSMzDFGpKc0TM1WLNBhMdi6H6YNQ45AqeRwjx/hMiiIzMLySkRQqKtY06xO6PqLdLUas6dAIvUXqkpveYvQKWwgaWSHaW06F4VpsEP0WVRzRJomSDTp1BFk+7YtoAAAgAElEQVRmtRHfTY53hFLjcLZjsWgfdBySiAkhEHqgNh7kmMTMkc/TsYNIaXwfwdR+E+Pcuc/eY0jxxtnGOSEc7K/vcDvuT9HnN4qT15PIfRqWskfJXCvADCgbcFhSyprm74vSRnI0KXPUY23JoAeMSo7TleX5xYqPnzxmtazwwVOYClFVpIFWdFQGikmQXMQLv7+440UQUNdbYsqSyLuto24jXis2neHt24b/+1/9W2x1zOWnf8rJ5Sd861Tz8UenPHl2gWt6eldTlZoYwzCQmt+377qDm1qWJaUtMGakiw3EBEbrwWgyYCvIZGyQgffe9fm6KYnVmrbe0jU7uqYleY8IPc4HkIqu9yzXR7i+oygKYkycHp+gjMZoQ7vbcnt7i3MdxaJivTrGdQ1FVdBtNuw2WyL5XNu6Zb0+xtoGayRapYlA/+j8gqb1/O1f/SXGKIJrkSJO/TMpRLCKFDYIIklofDQk3XN6ojleGV6/iexCQcQjdKJcCLpe4fqYpZBjIGpNFxNfX7/lYojeipQoYqRteuIw/jDu/jnyybjkGBlOSq6zFCTr0GWKjbz+8mtI6WBW8X27+OSjZgt3Yg8djVkc1E8O3mP+ulZCISOyToheZEVeXSGCJMYbVHmJth0OT9v1BCWR5TFKJ6gFhdF0/YagWpTI9MDOdYTgEMq8txlR3HEI+ZzuE9LPX/e+n3NHdNAOkJ/4xuv2vve/9x5pLGxlLzU2UB70CWVTyTcxkxCN4ei+wxShcjlvSOGEFGi5H6pLKeXoJI30rGP37GwRpNw/JLUixDwGYUXPBxcnfHhZcHm+YLUoSbGn7nv6zRUhRZZVnolqmjoTvA+pYCb10iCzd3bek0Te6XwImGpBfdXxN3/zOdXRA15+/Zq6t6zOHxGbyNPTC/7RZ8/58NEDQvcWpUoqpQi+o2mazAmsLcaWRAW92yGlpCg0i8WCqiixRuODRwgodCZKCzFMjsd5h3OORVXRO5fxlKIYqC5qbq7f4ZoaGR2axG2zQ8lM40r0tG1Ncj3amqwPJjN1alfv2NzcUm9uKEvLyapCF5buZsvbt6+QMeCdIyXB9W6LsSXbOnJyvKT46gVnx0eoRea9Pj97yP/6v/yf+Lrh9PyC7nZLaSyda9k1NQ+PH1D3HUYrCAljNKUpsLSUtsWaRKEVfSrxdPS+IaLoo6JuAtYuqHykEUA0vLi64TjkNUUKmBRJzhMG0jGBmkIRKfZzY1FkdHSknQnDghaAkOkAl07DkO90PNzjm5oMZHz+dxnaxCg67545fAgMfoiUloXGpSuSc/TxBFGdkJwiokjlkqAFyb/F7L5CKMmufIStt3i/BZVHX6KUKFuQW8CG+CzB3SzmgAfpTmokZw7mfTjQ/Nj3RUVw6Ijmn/M7q2fsHdNdp6eEyPJTU4meSVIyi45ML7r/4pT2YLYSYs+axiAFIxMq5p6gUeF3DFclEakhhKEtXEikFpyUBd/54AFPTw2rhSKlQL3rud1u2LW7AfD2aDQej7V5h9iraGTQLkZIKJQUeYQgRhrX8/b6lq9eX6N2ki83XxGPz/n4B5/xq7//EccfPOLnr14gfx7444/PQWliFGx3G0AilMT5SOd3WZGCTDqmtd1HSex11ZxzUy+KH5QmYgyE4DMGFAPGWqSA7eaWd29fs7m+wbs+iwj2GQsqy5K26+iDZ6kVx+fnKFPw4MFDTGFxzrHdbunbGqNgURg0ke7tKza310giXduglKF1EV2suN20vLy9YruRfPzBOat1yUqf8+ThCVdXV/zyl7/geLmgrTcUKneh26IgJWjrDmUFV42kFBYhItbsOFoojo6O0Aac7klBEJ0AUdA0Pb2DKAVtvcVWK6RLRF3Qd45N0yPsES6mPEs0NHIyW3MphUwSJ4bq6mAQ81EMGChkBhCV9xjiZCrfgF1MRjUA4gel7LlBzl4znQNMI06BhBYG3+/o6zf4rkfaErQlSUVUithtEARssSBJAz4LCQjAakOINUEHtiFkIQYlECKMI+5AmtHbkHt97uG6ezqUb45dvrm8fz9Duu/A3ufMpmPv/n18v5gORBW1GOY8xvBXDSnT7BSHD5b3OXmFyCDsXYclctyqMnnP8C5hIBBXQwUln6SUEhEc66rk8eU5a9uwq7fsNg11HYYJ34z7tG2LEYZiWdzzwuPiISba1tN2NatV7nJumjaTzOtA8DXXX7/i9PxDAoJvffsZn//y56TXb2k3V3xw/Acs1ooQO+qm5/j4mJQEdd1Qty220Byvllhj0Cpz4fSuHeSH3l8xSSkP8jrXoZXA954YHG3wXL17Q7fbIWJmYezqBmMswhg8cHR2xun5BaZaUC3XRMCWZlAb8QNfcmCxqCitpN1uqG+u6HY1kMu7ujQ4NL/96iVXm5qPP3nOZ7/3McYWvLt6TbfZYHTiF7/9LS++/IL1Ys22qSmlQPg44uhoreldy+s3r3l4/ID1usJUCR8Sv/mqRplEVAXCaEhQ3zT0TtAGT6JjdWToXUNJiVeKROT6+hatHxFcIkiQSiGDmAHGQ8FjDMTFOGI6M6A7RjbilWECRLOTmCbrxf20Yb/a83/VkBXEkaZ4hmIIMZu2H9fezDcFFZAuoZu3qOUCr5/hqyUx9Ri/RWLZFsdZ7KDfImJLX5yhhKBsX5CSgu6aFGqUKhExU+EoPEIXMFMrvgvgz6/B3okeDvbuwW1xyMM9u6aHr78Tzdyxu/F9767790VK73toMXuBuoOOH37I4Hln3jZ3SA/53SDNnF+Tm9OyQxoH2MYyXzbUHIGJSRJGSknvA14Jrq5u6LuAwORdWERCcBRFkatIA7AWwp5zeNSWynSiC444AhGRAqwtOT9/wA9/X/Gv/+2/h7c13/r4kqbuePnqhtPj5/z4L/8dvP2Kl9/7hLXvqaoi0y+ERAgeFJSVZbmsKE01ONFAjPsu2lGe2Vp7wIMdgqdrWvqmQYQ8jxV8j+9a+rbJg5Ba0jQBN4w0fO+73838RFKzXK9AGWamh1ASpSyxL7ipb4m+pd4l6noH9Q6lM3+0MgV179HVEa1/x9MPP+LbH31AFFDXV1gZWJ0sqYzmVz//nKrQEHvWpUEFDxKsVCTneP3mJcdHS/7oBw94/bLn81++IJaKVXUGtaMqIsdnBV1qEF6wud3leTHh0TKhNfjeIZWBDOvQbG6xpwIrJTIGRMrKtSKNkfW4Yx4u+PctawFTWT8JUKPs0GA4o7OKzLp+Z68fK0gjlfBoOyMkIYZ2iZESZLSPySBl/vxCQIiWIDXWRgqtqXEkPEqWxNSDXpKiwMcGEzRSaZIp8Vyid18g/FuIHcYoVBeJyqBFIiTxXgdwaLMcPJ9/T9MXmouKjn2A80cgsR/w3W8I43cdZ8/ScHEmu2cP5s/P6WDgODFJKY3HTpiQnLy5ILCXOLn7BacxDebeNuy9oJLIEIeyqGDqNYphuiBKZTVRIXI65yO4JPnNl2/gvMKUa6QaOIf1KIu7wGqdR0LYe+XRGQUhUYMjiMIhUMQU6fsuV/BSHoD9xz/4gJd/+B3aeMu7K0+XElFr/uv/5l/w9Yuf8qsXX/KHF59SFYqUSiCTsC/VgrGzLkc1buiKzphUCGGqGHifRQnH/p4QshCiEpJut83XwXlc1+fp8FnJt6oqPv7OJ5w8usyLJiRQEtf3xBgxxmThQ3Lzp1YCIwQqBVzXEfsOKSJt69DlEo+gWFScXFxw+vASY0uU0vRdTQw9wTuikrx9fc3Lr77muCzzoukadJm/19IW3F7v+Nmvf84//oe/x+PTU/qN5zcvWl68q1kuoRQCeQALLPTT0/OLL99ws3nDutD88//yTygKw3/60d+ztBUBjSgSvfcIIyljxCSHcg1GVQgh8UkgZO6CH6PvxNAgK8Qwt8gsBBjNZVRVmRnbQE86xyNTSvtm2Th7bubY9qRlDLYxvPN+x+abHgLQLkB5RF1d0IeA7b5GaIUtzrJzspaq3+SUTFpSeZK9gdvg/I5leYLsv6QPDdKkKfIQCXoXKPX+/Caq1Nn3m1JJ9g5mfwneH8Xc/T2yB+HfF2WNP78J6B7xo7FpcfqMwaHPY6Y9MD28eASb9/zSaRKWO9iJZELKIWgddMLS0Kw4DrQd9DTMmNni8P+57ComCePffPmKQl7w5OkFxAaRHFqCMgWQRwWcyMautJ4M3TlHCpEUc9le6qxnnyLUdY1KiWVVgquplOOf/4vf58c/vaH7xW8I2zd8+9tPef6tJzy4rDipjuiaDUoWLKsSrQVWm+x0pMQWduDKCcgBHJ9XK8axFe/9EA3FPKMUIynk88y5fyQGnxs3B3WNsixZLFcs1itc22Ks5XbxKeDsB4AAgENLAQCA/3+3zayJMY+A3FzdYsRAMi9idkAiISJ0TU10DiEzZtX2PXa1wBjD9fUbyuWKFB3CHOG6HuccfqCkffniNa7z5Mn/gE6B6Du0Nfhux8nxik+++2csiXz5xSskKz5+9hHLXZOb6WKDsWtav+DBo4c8PDWEcEXXSM6OCmpn6LwgCoVRgWAkVRBUpeE2eITyYApSlBk3HMX1SBMOJIb5QMFem2u+6+c0LE1pmEizg+4Az5Cd1PsUZJgBuPPjx/+fxq9nTIwHpWwgiIjQS8pqSRkE27YhdA1SbDHJZM5vASq2JEduXo11HjjWBbumZnN7zdJGDOTKpMzSUSR3cF7j547VprkTndRqGO03ZzsHzmN2/vOfYWb7c/sPzFOswzRsnrnm182u3fhLPMTZtBw2DjElTKDDOJqRQKVBzM6DyOV3lRxKmlxxSKCERolB83TUDSN3e47h2v5E8+IKMaKNJkXwQXB1s6VYSuqmh/4WWxiEKIkugncIIfAh4KNgUVratpvSLyEEu75l09YZp5Ge0hT0XYfrA0pKIh1FVbBYrnlWnFB+dsTSBharz3j26DHbqytOHz7l6PSI3bu3dG2kKgRaW1zwg4yRwoVIN1SphJS5g9enwSkPBFBzJrqYaHYbvOswUqA0SF3Q1hlsjy6Pb2jAWk25UPS7HWa9ou8afN8SfKIsDN53CNfjYsD7PssBeUfwHuc8XT/MaEWFjz6H+D7hugja4NoO5xo67ZFIfIBkNEHA9uoNKnaU1hATdNpSJY2OieLUQNdidg1+aSkWC7o6kIj4viYJQSksfQ26lCjvEERciPROY+WSqHcIqZC+IHQdOnpAEUTLib3mpShRCbRk4CAfIoDhHqeUiGMxIw3cPaMfGB2MEDkSjznakXJQoYgeQkTEbFQhzHA7sTfnNOhghRRmKcWMwHXAPVUcHE1Kk8Flcvf8fKsVKyJeOfCRTfkMoXt095a2V1zEd7TtlpR6WByhlcB5nylbDPRaIBdLlrsvKR98Rm2PgJ4+aUxUgBsCgWGzT7M0UcjJ2U69UoPjmGXz2Rn9DkD6XorH6MfTcGsOK153saGpAsa+FD8+FwSTcwPQYwo2NN1TjC2LEgbgPXts27Zt27ZtW3ts27Zt27Zt23fuw3n4kn7ppHt1uqr+dCVL6ynzgqItBwCT4e/o/aSEhcEpyKXZrgq6xuRDRjkgbJZQpgZJSeZ8C1mRnTcfKjEDceK81gs1rQ12Trm/clO+MzUBib8rmiEcgZxax8so/q73spztx6YbMjQeV/XVHU++sYtClytZTe1yfkR4/o376y1+RQFicwZ1zs87a2Z2tbv3U/TEAvPFU/qSR5Qr9sYVjDWUgp/jVu6bDaNwCJwQbrEJB9zrrCzC0vYJT3F9o1oV2LQgwuqBc3T4u8s7jU3D3taGZaXOviHfqdf1Mlk8bKO3qF32+KGFpgOOAB9iGAREBZ0E/u0i9yH8El0Hbni/WiFzo3N2Km05gSSCrc1sP6Gy0EtcULKSAJx2hDiCMbMLGUsqjFWemZcsLlAzm0BorwD/CVYSS2Ukv2UMrJxa2BKkTYbN3/GiyahQEUp/qdNE1n6gNG+9ahh6ruHHFLAw7zX3mJtDz9iCvUmF2Hme8nD6Y09mpfXn1dHaDNMuvESlhWH2EVYSLcHQMCLeKd/hTJwzOD6Tsxvhy9u8ImjwoPz4NP8VpRSk9t63ZB9H6TLq51d6bQ25++iDCNNFWt2DdOpyjeNt0r+78KldexFrYsLpjDo3hHF1tY2uKAEJCAbpaRm6J22WGB8Fx1d/DorpfjLbvGV5gj6mLbBi0O9Y00wKTRZCIIJ58MFH84BoSWlTe6SWW3Ak7/GNp1Ppn8efW1V5pjqWU2lJCsNDC+XH/WOIdmbf+RL9U1iZa3R05FfD+9EKmQOcogQ6oIwsicPkTf+5zhbitqn4OwLmMlev5nX5FudsdSSfcmlnEMdKat7uhcyoY1PfbQOmxTdXawaKtdEzgJ9XF2EWphXoWWCC4Rtl0dX17CLibbG+ntYGkHQR7XkXohHld41Hc/0VFahds3o9r6hhY+c8enxkCljA3xcA3cYvGGHWJwMCEvOrb0zUyKsjI7/rmomfB4iXGhWAXg0TmiCQXIZqf6EA99JesNqpa2xLk6MQRoJP4poIEkYHhi+vB6qa1Ql4Wk00nQ4kgxtfeOEsfwo/5YhfSizKc8HWcB8PIi6SUt7oYAJ7FG9MBkOspdlHeHMMGgUsGxhHZQRlrp6r66coPr+YzSUbRBKPOstMtOi/4uK2R7BLUtwjqjuJ4CmFCOOWohd+ZMxABySPG3SSEYEk8EcCztuCW2DWoZGTUMAQToQU2IBzUUVDVsNGvvQYMfkA0cbC156aswhC0t3r0AxfQsRIQZ5O/IcHU6EBGs1RlBdOC/Pto9bWvtNNxxHKHswy37v9FWnrcbny/XWys0LFAcKuAWYv1xCibqiGsbYfTKArUYhGXhgc5ygc1cACH4SDpczxmi9g5Ncap8QiYLPvGLaQANx98/Y6UAK2e3wVvLCgiACw8gJGDC+xMBK4DNxtyXfkcNdp7TW5eKPPJJHXKGSeZBpcyDciZkwEOyPbtrVMleI+STA8+rZGf+Uy8P8/Qd6KBoXF0ZsQ7jbbVkQC3thiJicer5+c28v9hyHwJ46eogrZOM3P+uYebEStnFXkICuHgAQfKMJi6OyMHBaHa3frCdo4qS5TyjJdWdwwvLV7KliYgFjWiZvfRKG2e4YtBh4uHk8iSgHDGopHwsuOCdvqAwMdGcIPkvvqOPiQA0Vlt6BQ1k8BE0kPDAkYqRyvHScJivUJOmXkJJOiD/MOwvwewlw631EzOsjInIniEYmglocCXmPX0y8UXh8YBY7coKp3ne8Iwcc=
*/