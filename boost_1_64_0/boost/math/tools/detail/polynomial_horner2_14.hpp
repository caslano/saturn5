//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_14_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_14_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_14.hpp
8u22j5858mkTJEmUtMI+Cg6Jxh6Bz0NGf2/JB5EovSrI4ji35dH20oy6OinH51IR5mP89+4ctCzLrM66etQes0nHgklHyeRrkYZtGbURF5d7dqfn14bzmDX5AWkOqxGeuVhlejxReE3bpqnHFUnX8Pr9AZxHMTsEIiyjOEnrhMuxioSFIkasedTvnfKo2zJ2rABe1YcTKV4XPunIBrUXxkUWCHDAxsZT9e6faY0rpv7/iMnnIqmqqAkyT8qvQNNTK2KcAbIKsXjY1Ic/sH4+CGEkzTJYSpxdGjoakXnn9X6fLVOLxk/zJEsDkHEkRlDmII8njuq8SepQycBrzlZbwbJ9/B942TZpmsdZECuh9Qk3rnkj1zpyYVbBP56SA9tibFxuzpErwzD3y7gUsuC1Y3AVpyt3gckFIgjDxg+yGNdEPKVYd25ncqkoKq8Mm1TMLs7Ifw/Ly/8ryy88dGT8qNr/4LZ5G5P1RRhERZAWYvbM8nKPbQ6YOD/I5GLRxFEbekkk5qRt5IB8pGMgKsNv8zLM/DKL0ygQ/CQVT+dvHdvETZNESdCK6Glm+1b7NOO2GbvB57lRkGVJUUVSjn8aWlk1eUTZ/Y5s6xd+lgWeK0tWpXFpksk2ooyypi6b2JWV46u1Vc7T/kwn/tAr2tzTOsLhKWR1ag1zPfIcY691JhuILK3CJilKW3bo6I3b+RWOXO3ncVCXjZQzR+F67fwG185eGBZpVii56Ox/Tev7nDjb2ovLLG1IlqcV59BMLhRNU8VpXAzLpwqxXDFKGedhM6e1ZSspWhRZAVHS7lfnTtM/bJlapDJ7VVCGUoZud5k7TSZvu//o9AVpk2RBVArns747P9vP5GJRxXGTpF7lyk3jcEDrmscz2VBkVdyUce2L7nGEjl2mbNlWJEWS17lHydWrKtaPL3KZ2iubOPZawU/LcJkXO/HEjV8VXiH4CRo+zt3+R3euV6d1EZco5F6xUuI0L7/M5ANRZ23WhIWP8tiaeT37JJNLRJYGSVHHBZfjT86YOH/EZH3ht02byHQzWfj+4aT1L45cGqdemHqZcK8haDmT1t1/4mlt4iT06ijvyGEfS/k8yGRjkQZ54UV+KvquPgxFMZ8hk/VEUWZ10yQBytKTOnze7MRZtX6RV0XkylnJxfqwzmRzEURBW4Vhi7LulWHHxq9i8r4oy7pOwqQS7vUSJUdr6Tc5No7yJE29KuBy/Tb+qJvfwm+qNnTi7LfxNSe9flCnVV16wr3ip+RoXXmDyQUiDJIgTvLIlTvh8bTu/rMzN2+8sqzSRvRdCRyKUl1isqHIYy/zEj8T3auAnbm4YLKBiFLfi5s6FZ1rhrytnWRynghT6FWiUjhX/d1xftnJZ1rnbeRngStHxUlzmZfbsrWoUs+vkjAS9g09LbJk0nnJyV/m+2kdVqnouApw9jyZXCqaIg3jOvRcOZ7SkQMmrVds+Ub4UVa3VeEL+2a7jnLJ2ObbTjm2WRMEYVUxIR6fwHrnlEfh53VeF5lwrq67Y9/YX5x90bCFxWXiylGstG90gMlmcE40DhtfbHBbvrO3IZh8Laow9eM0yjZS0Fcn5mwdjQi8qm3yLBfsFvtQZhbnayxeTyRlWTZRngjnqr2Oag3rny1XiaytvbxMGmF5OdEi1OdeYnGFwg9aL86bRHSv8WhZqg+XmWwiwsjLwzIJRPcqVaf+XmGyuairOvC8LBIbXbFyvtdcd+TjMEjjKvdQXs9OXHljq91/ZeVSBnFUlnEs2O3HocwLTbnc+6+8rTal3zRZ6Is1OGU+85ylWTifAh9dlSCeL56w5SbDokzCOGqk1FG2XJgHH3Q/kt+hL8qfLeokafd9uF8=
*/