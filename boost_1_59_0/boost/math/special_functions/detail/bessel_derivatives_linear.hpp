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
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
*/