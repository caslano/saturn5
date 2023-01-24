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
ewaWyNr5Sh2aDa0bKnw436EO3QhGqXrhb7pHCvlgp0FI9b330Psp1ts4Lhc12VqgEjdhCBqXkTBh7RFXc7fHi7rFteeO9ZrfhZEVYYsJGN+4YjfvvVkBaBJWaoNbp3Rr1+u2AZ9Do5FYMeXpAmh71RVHdS4SUGqgyftEMaQLnKR3VZ2tjcL8IaVODndWnuvA5pWz6XwKJwW9miUjeVUhgGh9K9uZkFYhtDKpplvJfOA9YrirXhxmWllW3XdZm0w2SNe2tiLvkfBP+IrOREitZOLFHpEobjmindkz4ujnXv+6dfiF98fRyCwDd8Oz1nxsmaBtSCY5zVxCyahVn3+ogPR0gsvhx/kgO8Tvr/ZJUCa2Abc39XvmF4Tmohc5y4WdeCgFVM7vphzmHi/plZcuv9Jgv/02jv9UTxSTZbDGuzoeNi0Wb/3hznOmyVgoOxbvUIyhmHdpO+7BVHR6ArlRlxkb2U0XrDEz5dHnYkceW4X0+X3zh0As2PMjbx14uRfcC6s0hAz3YWYqsPOE2sZJTqxrXsAuqOg63cZpUQbX2mHwjoAF3VYBdzrxRCZBoL68xFk2aa5AxIq7wDe6Hb/MEeMPpeLl0tYi1hIJs2IdY/c0NHws9o195MA+Zp6PM/36PPBK4ugJjrjKt7Cdv9s5sizbDae/1YHlek8opa4DFWo/kAZIG9K4ivyWHQwT3sf+5Q80u7wepFJGmMWB
*/