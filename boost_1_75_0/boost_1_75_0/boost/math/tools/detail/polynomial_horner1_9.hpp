//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_9_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_9_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_9.hpp
JMHa//d9/H5k3nLfXc899+wHAyS/did5aNZem4ZunBjp0FWH53vxBo6H3Z4Cma5ahA5YpDkF0/NuQcv4AkA6Z/dFREfRLfO5BaT1ijdwUPcfWM0g7aq967+qFXbozaJSJJwT3+/WxwIrDZzHO4xN+OdAlbfoVeLaUYj9nt21ippLScy0ur1bz7wFjdi5qJLmjTamiTH00lXRz+fv4No+txi9EF39Lp0Ji89R4fF/35mLqLbwYt165A3Y+Enby7g3aFeV9W5fTarM84/Ye4kayfsqW7FZlEIgI5QC/HMR/jkf/5yHfwbjnwGf4lbTeCuzivPQWhNlxz6Ih4GWqNKku0AWKxgnUPYrpF+8nIQrKA2Ozm0EUJ5YDSUaJbldeSuTKPVGFB3XNnLEZGBzNixxaMlw2oFZOWQhteSdWczmDGD2pJ0ghwLYUpOdgNNGX6qxOajygS+BrZk4P4jyablSUQpsbDyYpHGEOontmeYU3Nvbpqfy42QRyZHtXzNeyG8KYv9lC9P4ZfgiKPeX/QsJ+/jnE3T4q1klvc8n++Gc6fCqU8nfba1RlVpRAax0We/ycpo55EtbVc/SOQ6dtAi9azfncGZ6/omPGTnOP6bT65d+xPR5JT5SZk9jverdH/PT2eKDm8X9tI9thm5Q5FC58AGHlkMlhyJ+Cps7Tb3L6aL0nKS6xcIL8W+zBbfN7jUHCrqzp+RA+eT272Kp
*/