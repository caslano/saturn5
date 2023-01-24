//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_16_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_16_HPP

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
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[8] * x2 + a[6]);
   t[1] = static_cast<V>(a[7] * x2 + a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[9] * x2 + a[7];
   t[1] = a[8] * x2 + a[6];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[10] * x2 + a[8]);
   t[1] = static_cast<V>(a[9] * x2 + a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[11] * x2 + a[9];
   t[1] = a[10] * x2 + a[8];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[7]);
   t[1] += static_cast<V>(a[6]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[12] * x2 + a[10]);
   t[1] = static_cast<V>(a[11] * x2 + a[9]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[8]);
   t[1] += static_cast<V>(a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[13] * x2 + a[11];
   t[1] = a[12] * x2 + a[10];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[9]);
   t[1] += static_cast<V>(a[8]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[7]);
   t[1] += static_cast<V>(a[6]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[14] * x2 + a[12]);
   t[1] = static_cast<V>(a[13] * x2 + a[11]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[10]);
   t[1] += static_cast<V>(a[9]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[8]);
   t[1] += static_cast<V>(a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[15] * x2 + a[13];
   t[1] = a[14] * x2 + a[12];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[11]);
   t[1] += static_cast<V>(a[10]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[9]);
   t[1] += static_cast<V>(a[8]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[7]);
   t[1] += static_cast<V>(a[6]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_16.hpp
aUUq9ut52P9w7ApSytwvIgdGQL+SC7GOdhM5wOYankO7mBxQtF5pG/kS8weiV+Ko0BrSCnhXfaNRBN9oFMEn/rpPXGvOzxBZUE+GhwpyrNjK5Bhvz0wokLwOmfWhkvGejiCCjhOA0JLDcM8MEcQDv28T33cgiu+e15E08No5hm1n6ocZjrBYs7J7CIktYSTjK/m+N3ISOQS0nUV+rSyDlq02j/ISI0OOm6cwSHG/MDmrYZDwAe7ruOeLnQ7aIPiB6tmXRkbOQ+BFMuXF3+hFxEFMQPIWpCdT3v+E39viNWkwNXHP3pS3S/S3GUm0lW9IeXsjvXXVZSHGqkmXAf3jLZJEvjWXPl6YaWFlpn72wQh88YV9STWGh9+6M3Y4Cied9qWgGmUVlo5POtXt8V38uKvb42n8+GS3x9cQB623HB93Um92yBm78Uqnte7+Rn/KDwZAsZ223aMyMekZr2QCXWl32rbiM5/cmtIknPsKus0nD6AtI56N2y92I7I9DH+VV39vs6wzAUS4n+r50dd2HRuZNhLSSRoOYzpJx4Nd/yZ9pIqHECDhiq/tnIKtKtUvRaPTTKf3Ixa92XPP0my/1GaDbMHIdVFapCMpJ9jdqX15hW9N52PvPaFJIGIJyM37wiJyOLF8vSQ+Z+KtYjnTe7+M4i/QfyuI0otH+XGd+F0epccPiNt7RemxK/j36hVEPu5VLl/BBUJcfhz/
*/