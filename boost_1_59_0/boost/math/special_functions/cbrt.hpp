//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SF_CBRT_HPP
#define BOOST_MATH_SF_CBRT_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/rational.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <type_traits>
#include <cstdint>

namespace boost{ namespace math{

namespace detail
{

struct big_int_type
{
   operator std::uintmax_t() const;
};

template <typename T>
struct largest_cbrt_int_type
{
   using type = typename std::conditional<
      std::is_convertible<big_int_type, T>::value,
      std::uintmax_t,
      unsigned int
   >::type;
};

template <typename T, typename Policy>
T cbrt_imp(T z, const Policy& pol)
{
   BOOST_MATH_STD_USING
   //
   // cbrt approximation for z in the range [0.5,1]
   // It's hard to say what number of terms gives the optimum
   // trade off between precision and performance, this seems
   // to be about the best for double precision.
   //
   // Maximum Deviation Found:                     1.231e-006
   // Expected Error Term:                         -1.231e-006
   // Maximum Relative Change in Control Points:   5.982e-004
   //
   static const T P[] = { 
      static_cast<T>(0.37568269008611818),
      static_cast<T>(1.3304968705558024),
      static_cast<T>(-1.4897101632445036),
      static_cast<T>(1.2875573098219835),
      static_cast<T>(-0.6398703759826468),
      static_cast<T>(0.13584489959258635),
   };
   static const T correction[] = {
      static_cast<T>(0.62996052494743658238360530363911),  // 2^-2/3
      static_cast<T>(0.79370052598409973737585281963615),  // 2^-1/3
      static_cast<T>(1),
      static_cast<T>(1.2599210498948731647672106072782),   // 2^1/3
      static_cast<T>(1.5874010519681994747517056392723),   // 2^2/3
   };
   if((boost::math::isinf)(z) || (z == 0))
      return z;
   if(!(boost::math::isfinite)(z))
   {
      return policies::raise_domain_error("boost::math::cbrt<%1%>(%1%)", "Argument to function must be finite but got %1%.", z, pol);
   }

   int i_exp, sign(1);
   if(z < 0)
   {
      z = -z;
      sign = -sign;
   }

   T guess = frexp(z, &i_exp);
   int original_i_exp = i_exp; // save for later
   guess = tools::evaluate_polynomial(P, guess);
   int i_exp3 = i_exp / 3;

   using shift_type = typename largest_cbrt_int_type<T>::type;

   static_assert( ::std::numeric_limits<shift_type>::radix == 2, "The radix of the type to shift to must be 2.");

   if(abs(i_exp3) < std::numeric_limits<shift_type>::digits)
   {
      if(i_exp3 > 0)
         guess *= shift_type(1u) << i_exp3;
      else
         guess /= shift_type(1u) << -i_exp3;
   }
   else
   {
      guess = ldexp(guess, i_exp3);
   }
   i_exp %= 3;
   guess *= correction[i_exp + 2];
   //
   // Now inline Halley iteration.
   // We do this here rather than calling tools::halley_iterate since we can
   // simplify the expressions algebraically, and don't need most of the error
   // checking of the boilerplate version as we know in advance that the function
   // is well behaved...
   //
   using prec = typename policies::precision<T, Policy>::type;
   constexpr auto prec3 = prec::value / 3;
   constexpr auto new_prec = prec3 + 3;
   using new_policy = typename policies::normalise<Policy, policies::digits2<new_prec>>::type;
   //
   // Epsilon calculation uses compile time arithmetic when it's available for type T,
   // otherwise uses ldexp to calculate at runtime:
   //
   T eps = (new_prec > 3) ? policies::get_epsilon<T, new_policy>() : ldexp(T(1), -2 - tools::digits<T>() / 3);
   T diff;

   if(original_i_exp < std::numeric_limits<T>::max_exponent - 3)
   {
      //
      // Safe from overflow, use the fast method:
      //
      do
      {
         T g3 = guess * guess * guess;
         diff = (g3 + z + z) / (g3 + g3 + z);
         guess *= diff;
      }
      while(fabs(1 - diff) > eps);
   }
   else
   {
      //
      // Either we're ready to overflow, or we can't tell because numeric_limits isn't
      // available for type T:
      //
      do
      {
         T g2 = guess * guess;
         diff = (g2 - z / guess) / (2 * guess + z / g2);
         guess -= diff;
      }
      while((guess * eps) < fabs(diff));
   }

   return sign * guess;
}

} // namespace detail

template <typename T, typename Policy>
inline typename tools::promote_args<T>::type cbrt(T z, const Policy& pol)
{
   using result_type = typename tools::promote_args<T>::type;
   using value_type = typename policies::evaluation<result_type, Policy>::type;
   return static_cast<result_type>(detail::cbrt_imp(value_type(z), pol));
}

template <typename T>
inline typename tools::promote_args<T>::type cbrt(T z)
{
   return cbrt(z, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SF_CBRT_HPP





/* cbrt.hpp
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
*/