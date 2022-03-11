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
#include <boost/mpl/divides.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost{ namespace math{

namespace detail
{

struct big_int_type
{
   operator boost::uintmax_t()const;
};

template <class T>
struct largest_cbrt_int_type
{
   typedef typename mpl::if_c<
      boost::is_convertible<big_int_type, T>::value,
      boost::uintmax_t,
      unsigned int
   >::type type;
};

template <class T, class Policy>
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

   typedef typename largest_cbrt_int_type<T>::type shift_type;

   BOOST_STATIC_ASSERT( ::std::numeric_limits<shift_type>::radix == 2);

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
   typedef typename policies::precision<T, Policy>::type prec;
   typedef typename mpl::divides<prec, boost::integral_constant<int, 3> >::type prec3;
   typedef typename mpl::plus<prec3, boost::integral_constant<int, 3> >::type new_prec;
   typedef typename policies::normalise<Policy, policies::digits2<new_prec::value> >::type new_policy;
   //
   // Epsilon calculation uses compile time arithmetic when it's available for type T,
   // otherwise uses ldexp to calculate at runtime:
   //
   T eps = (new_prec::value > 3) ? policies::get_epsilon<T, new_policy>() : ldexp(T(1), -2 - tools::digits<T>() / 3);
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

template <class T, class Policy>
inline typename tools::promote_args<T>::type cbrt(T z, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return static_cast<result_type>(detail::cbrt_imp(value_type(z), pol));
}

template <class T>
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