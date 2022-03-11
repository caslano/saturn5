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