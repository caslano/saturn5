//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_2_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_2_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_2.hpp
ivO2QQ7hd5JNrSt7jNygfaAyg0kkIrGufCCW0xHuedN/TXzWEQc0zhZ75rRzZF87W3JRVx1+sMT0BwaEnnUqSqKG4YcjKKs3OKiEOC62myYuURfoIYZdRSXQzsHt8iYwVA5YUMZtNtoWQ7ZMyvFsvsqvFtm4S7OYL3O505YrSyYT+DskSZL0V26W+EzCj/squLo79NW6hb7Fek2MZR+hmyModYB7RAujUDoaCfXUYzlB4x054+qp4FGCF+IOzYnEzAXK4DeVkbhlq+LzB+bPwGx9Lcd3l8vV1fxbJM6NwYZfn8rTrik/5+6r+tD8Sh7rUIEKt6VXxutt8/bOIXzTXry6Kodl+d/0nv1hw17s2MFqJZ8HSh5/XD8AUEsDBAoAAAAIAC1nSlL+z4RKKgIAAOcFAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA2N1VUBQABtkgkYNVUUU/bMBB+t9T/cGLqCyJ12rFNZFknxBggMahoxrvnXBqrqV3ZR0v//S5xSytt2l62B6Qoie27777vO9s5YSCtAo5Fbmzl+DPHzdr5MozFdVFMuhdcXRaick3j1o3TioyzIpf7wFzG3DcwRb9CnwRTosg9LpsNr5aKVESTw8EQ3qZDKGoTgB8FazS+
*/