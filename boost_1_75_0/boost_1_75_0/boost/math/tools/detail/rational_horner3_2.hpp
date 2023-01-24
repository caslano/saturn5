//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_2_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_2_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_2.hpp
tFXN85FO6vtHou9O3K7KZCKqu138ONUhbVefz/1EzU/DPWrajG1KHmCNmKOoXolE39P+qHIdxiQc334uyyF+m5qfC5vV717jx4mO5VtU+Ytb1Pys3qJ+d9k2Jzkv2ELfn+AYyp8JcUzdon4rYov6rd5b1HJN5RgLduz5WP1W50/Vb+UfVJ9fhp7vk+tUxqubJVb22+g9J3m5ghynNyvPn6EyYe0izpG/WX3nZvT8r6i+Ig6q+Rmao9bvtTAVDwc+U6/3OKuWffkp9bgPknl79N0Inmejo9VmVf5tNqvv129Wn+mDMOZ9Rs3bol3q+9vsVzGTcUAty8psNa0fzzPRJ1+o15uGqNeXf6Tmcw4/TnTM/8hJ/mkfyfj33qU+v2EfwvN+p/byWo5cXxPzkK47rrbBph+pddF8qyqH25uc9FvxJllnnt6qyvnkEad2sbEOaRcyVuuy7wY7bh5T33/vmCqfbfmqDPML1LpYvEmV/7ItqqzGbVLfM2eTmnYOwr96TOp3q/p87C71eNxe9Z3Nw1X5S4fVtPE8nwkOv3xVzk0LnOrip42SpMj5+Ea57V/ZqD5/ZbP6/isI818iPTB/i3o9Yoeah5U71eNdXBelOmbmOemEOPbdRMe4jerz0xH+Cz9EZf9IldU2jitWv5vl/Kv6OdFRH3Hi6Zlq2s5HEBdscHrP1Q1UJhQPX22Q3/nHJlUOnT9CeXPG2MYd
*/