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
l+sNx5/QG/td4sd67sV8Az+sz6HHuQZxTN0G8oOP/tnOZ33tuMm0H5P/R/98d+nHuQ72Yv+A/edbP8xD4L9QegLOehE/Zp8IH5+JDni32+/JqyAnfon/UudKf84/0BPrNfxNvyGai7/QYp92jKOO1vk88pDEM+fD0C+v9/BNnQv6m+V96Cme37sLjp+m7+vkON/IeQHxNNnz3F7vr9eoH3ThE3094rz5w1qvQo98FPy/bz2Th8YP8VP85xPlp/Br7k3Qr5Pjr4vrS94RffTC/IKeqLuDT/b10FlhfNv0jJxfeV21VS1+wDqfcdTHgbe9/YF8Lf5Qx3HziOOiguvpu6kfennJ681JjGffqWf01szxWN12H+W8ZontyrkdflBiPaF35K8EXvI85pN1If5+jP3gFc+f5A+xM/UW0P9Az/D5tveX3dQfuo3cn3wTdIhfxvGdpT/rNvghj4Ed73fLfSHGn+d6i0lq0WcVr3tYTyEv+XLGr/N3nHUEdjrE8OWe1y7nmfyGxqFf623hQYKDj/Mu/I44hK7mnwacb7Jfxr5PuV7D80wFvkfw1U7+gB5Zb4HnEcdnN89rd9kPXrG/kj/ErtQjoTetXzJ5T30ofrPQ/RmHPwz09zpL8vFM/TZ4qdtBjzck8NMGS2/Ie7bP4VlfIV+h/amf44PzNvyG37RBz3ynsWuB15e7bD/ug/H8EuPg3/sh6g7R+wHGf4/XyW4rc14BPx2SthH7bvRZRXTRC99r+pE/RV/0A88g4OTxjRe9Y491jnfXQU4iH4s85GOJ54G8Jy/tOrNtgmMv9pHEHedc4FW+KRs9/qS4p/2T5OU95wDQoT4bO3IOAH+s+/EX8OL/ldUP//rA68r54ht4Xc9jHQVH7ormCz6wwxrjWZm0e6jrxP6sV9HnFO+Lc4x/Z3bqIPDxfQC//WIedevA+wmOfZZ4fUL+A3l3SV74oh/xaz9dQFzS7oQe98McX3zHsHsbwaG/R/2x0y1eN/UXHH9kX8J76o6xZz3PR3vthysFR55x3j+k6/5XmP9D1Z/3gx2H/bxPKXT+4Vjf71ssOHyl76vNVIs8X6lFT9w3Q443nEd62/3Iu2HHXYxnfa4WfVVTP/TFPhp9dbF9rJ82xl+nrvqBn7pG9DnY+0LOkfG3h0yHc1jgrNPQz+z0/sn3XW/TOMZTf4geyOMi74PAuZ8gvqBPfg8/8/PoKV6nEN/0I7+H3jmnRB9DPO/xXSIex6mFf+dLJ6TrY55SC75cweGLewPod4ha/Gq28KA/7v/AR2fBsedcx90I++F40Ue/fL/BN932ZZ+OvsibMY+z78PP5a8N8b9Mf/+6eR9QznHMPA3ePD2jx45q0ddJ9sc7EzrXVxUcvKwD8K+2Gkc7yPGP3rFTY+DUaXsfQH4UfY6n5Xug/titjec96tjQD/xgtzGCozf8EH1Q14Dd+L6hh5G01H+oPy3rA/hN1/fwXYWfnl53Ig/0L7Y/7fW5qPWfQ74OflnvY9+zPM/Otb2yBac/54nId1u63tb1Cz8Kjj+PYBxxmcC3O0+ScZLuPfGevDf+crrw0o/zRfwePRMXmk+ykJtzeegWeB9aTs/wTd0o/bivAl3y/cjFvQ38hDpn/CZbcOiSF8WvkBc9UdeKnpmP4Q+/JQ5+8vf4CcGRs0j9sLfOC57SfyykjhH996Af69lkXCfqAuGX+R89Zjvv0xW4xr0ou+LnnP9hnw6C06a/txf4ua3pb1I//IP7hsgzwd91rdcPxO6eJ3dST4JfkK+gH/Ue8D3pgFQ55L5S/NMuERx8ygMfxbzwSAL/vL7zchfRUn/suOV8lfd36vuJvOTx8J83PD9wjof9ejg=
*/