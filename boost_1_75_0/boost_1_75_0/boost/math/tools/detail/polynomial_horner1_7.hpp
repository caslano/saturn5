//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_7.hpp
b/FXZjA8mPSjyEZC3/5Tg9X2s6h9OiIn+lecjNxp5l8hR20+07WvbD17SuDtD41jm1r/141gzMOCwDKmMHeTsqin9Kor74/y8jllAJ7TNO7BOMn6NSeitwWnBK3dk7NlTruRfOLT+e9k/uuEX3S/2H5gv2n4y5yxH59gr4w/sKwDedZz8ZdsEJ0vjG0B+MdG1QhxYKgvnH/+GQ3i7v/aYD76V7wHMDbI1lELcc15SgN+kurhtVNql60p+JYHI0NqrqI57TA7c055VkroPHNBfTMaQKf05zfy44U1dEQw/yPZOrqEebekylX8vKJRzKlzX0UHAA+FcuIx+1FMzlGm7FGnVMlOJMLkRadARdBtstclsmB9a5TARy3LoVIeyda9DJgjQrQ4GiJ2KlGDaMudJjpzeAjACv0XKZWaf42CIXXTt26X70+Lap6H78P7h6R3Q4u/MwqK4ZTzNfOr8SuwCxSnmsoXJ4cPS59H1GFxSp4iChtxDAeFRgRHyCl9xobm+TtjDc2iO8OHxqsbmrt/e2heWhBzaLL40LCrfgk3+6jiRJe0l72Q19k0vBgihqVUNyxL+LDc+dvD0m+BblgKBWVY/kRcrhs0Tc8wJBlRTYcPSdM32pA8/2WiOhQo0m7k926mKlbehoe1RU5RohuB2TESMWcPd8dCN4Ar+5VDtDZahsHjrindKRyeLY18b3R+xGGGF5dj4GfZ6rwD
*/