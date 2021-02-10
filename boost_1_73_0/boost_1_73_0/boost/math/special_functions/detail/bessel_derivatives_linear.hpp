//  Copyright (c) 2013 Anton Bikineev
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This is a partial header, do not include on it's own!!!
//
// Linear combination for bessel derivatives are defined here
#ifndef BOOST_MATH_SF_DETAIL_BESSEL_DERIVATIVES_LINEAR_HPP
#define BOOST_MATH_SF_DETAIL_BESSEL_DERIVATIVES_LINEAR_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace boost{ namespace math{ namespace detail{

template <class T, class Tag, class Policy>
inline T bessel_j_derivative_linear(T v, T x, Tag tag, Policy pol)
{
   return (boost::math::detail::cyl_bessel_j_imp<T>(v-1, x, tag, pol) - boost::math::detail::cyl_bessel_j_imp<T>(v+1, x, tag, pol)) / 2;
}

template <class T, class Policy>
inline T bessel_j_derivative_linear(T v, T x, const bessel_int_tag& tag, Policy pol)
{
   return (boost::math::detail::cyl_bessel_j_imp<T>(itrunc(v-1), x, tag, pol) - boost::math::detail::cyl_bessel_j_imp<T>(itrunc(v+1), x, tag, pol)) / 2;
}

template <class T, class Policy>
inline T sph_bessel_j_derivative_linear(unsigned v, T x, Policy pol)
{
   return (v / x) * boost::math::detail::sph_bessel_j_imp<T>(v, x, pol) - boost::math::detail::sph_bessel_j_imp<T>(v+1, x, pol);
}

template <class T, class Policy>
inline T bessel_i_derivative_linear(T v, T x, Policy pol)
{
   T result = boost::math::detail::cyl_bessel_i_imp<T>(v - 1, x, pol);
   if(result >= tools::max_value<T>())
      return result;  // result is infinite
   T result2 = boost::math::detail::cyl_bessel_i_imp<T>(v + 1, x, pol);
   if(result2 >= tools::max_value<T>() - result)
      return result2;  // result is infinite
   return (result + result2) / 2;
}

template <class T, class Tag, class Policy>
inline T bessel_k_derivative_linear(T v, T x, Tag tag, Policy pol)
{
   T result = boost::math::detail::cyl_bessel_k_imp<T>(v - 1, x, tag, pol);
   if(result >= tools::max_value<T>())
      return -result;  // result is infinite
   T result2 = boost::math::detail::cyl_bessel_k_imp<T>(v + 1, x, tag, pol);
   if(result2 >= tools::max_value<T>() - result)
      return -result2;  // result is infinite
   return (result + result2) / -2;
}

template <class T, class Policy>
inline T bessel_k_derivative_linear(T v, T x, const bessel_int_tag& tag, Policy pol)
{
   return (boost::math::detail::cyl_bessel_k_imp<T>(itrunc(v-1), x, tag, pol) + boost::math::detail::cyl_bessel_k_imp<T>(itrunc(v+1), x, tag, pol)) / -2;
}

template <class T, class Tag, class Policy>
inline T bessel_y_derivative_linear(T v, T x, Tag tag, Policy pol)
{
   return (boost::math::detail::cyl_neumann_imp<T>(v-1, x, tag, pol) - boost::math::detail::cyl_neumann_imp<T>(v+1, x, tag, pol)) / 2;
}

template <class T, class Policy>
inline T bessel_y_derivative_linear(T v, T x, const bessel_int_tag& tag, Policy pol)
{
   return (boost::math::detail::cyl_neumann_imp<T>(itrunc(v-1), x, tag, pol) - boost::math::detail::cyl_neumann_imp<T>(itrunc(v+1), x, tag, pol)) / 2;
}

template <class T, class Policy>
inline T sph_neumann_derivative_linear(unsigned v, T x, Policy pol)
{
   return (v / x) * boost::math::detail::sph_neumann_imp<T>(v, x, pol) - boost::math::detail::sph_neumann_imp<T>(v+1, x, pol);
}

}}} // namespaces

#endif // BOOST_MATH_SF_DETAIL_BESSEL_DERIVATIVES_LINEAR_HPP

/* bessel_derivatives_linear.hpp
yux47p6nvba/bLdVIq83q974fvf5Y7Oc+qZ1Xc/yOeaF4aC8Xpsp49r3wslMMgj3O3YWnKPVarS7SfxpqFxw6uoY24d0m7bpdtn2U/DWjJ3pWG3NrTMObe3AbNf3cyh4LLbT1mhfBFNwi4nTydnVXRtzy3jo+66Lz7ZhVDa4sa+3sKKzrzXGTP21rvs7ts9fza5+Vrp6tpubi0sIE9TQuAwPOKHRN5i7lm3idar780d5Gc/S+SnenitGxtIyH7fzXbBTnoevoTqYuRY+YPwuG2kQYV/3NpNgJh5WDnM9z5+zHdE2ZnjytD5x79G1Xd3m9gBr2lYrHmzR9idSOFc38XKzrHPdYDeFPTNclYsWQZex1UEwrLVDplaVt4EYHKrzIy70XZBx3Saqn6a30txF/Rg9FseMjXju7rHqhQvcXZFK2Z4JWnvW7WJrvVtd16frdLNa93oPXZgHrH87ifPpGh9UaTENaqvkt4vdqr3p9a2qF/xiym+7I6YybnNv+mDXY71WnxbvH26HsGJ3McsNR7vi7mek4S+uy92aXhlZkjJ4SLkRpzEZL6aOlzFX+7B4nh5HeWrw+nBiTEXtLhd4F3G4UcV2GPKqcsc2/8DXh73NDc2+8CKWdncDj1jO3DMnxQ7P9Xj2XK/zH1dq
*/