//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_6_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_6_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_6.hpp
zJqsRkeOc06On5OmyZgewX0XXyJ55ZaoYg33jyqucFb0lDvsoCM7eWdAfkVPyoUTkO2NljgXObzy/RnRj6wYEjO0llihCX9E5EfHUOVaCvOF6Yr9q+GyQZIdLf61yPr4Yssf98XuWR+Mzd0A7NemYCyyNRZp4UU5jvOQv4FEe892F+1J0JFYlVMCboS8k4DfZ98f3LYzaJvAfsEMilDkBLpoxBYq3ugutaWsM5eJiJh0qGzN5fFJ6aonLQ+RI5Dr8Rll9GG6JmE+xig4GB8/D+1t3BPcrv4Btzw2N+bNdW0dmzcv5s2T4uXjcHUvw4W/GJmXYqiVEtNSi4CwtCZhQsrWFKqeH11IDc6T4uufsYjO0qrUHQjfCu2Z2nK5x+a6+ntz5bGFMW8htHkltHnlvJIl48IX+Fxbx4+T4jLlA4yvf0dwLhJW41YWv2u31OOrebHyvKSk/B14h+T3BSVLtkNYL1SKFSYHml/A6HBkqqc132FpsQxCOtjz13w8N/7BEcLlZlPqMpTnm1yxKhBAkZ+G/xFJii1H2ea9kxBKXwUAwHCIwMHyWq1JR5nbhD6RDPl00uHa+oM+UvpXMK67MgINJ9hjywW3t9uD6f90bV3kDKa/L6V/LtWpaJAYsiQeJunM5HHSqiaahVWn8TRYUqxc4ESp/cnaxvAomiUbT5LkAm5hSTryAdH3ANc3KV+i63jBe3Q4JvPhE1Hd
*/