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
Gky5lXtwsA51+KpxBXVPV+JI/I16F3ECpd8MWofUigUSmhNdh8Ny3k6pQ6mlwfpVF/dFgWVx9wKPpS+OKIJL1/1bkAsCwMM5zqXLwhk3KqPOz+Es2BKbxLdKl1aXZruddVUUgCFe/JeR/1VUYIEh6mDta+x9BlcFAl1zgoWf6rzljVOGJGp87Zd3stPEVFDp5U8AIkladvjI17pnCitabo2gbK2oqGpXydNciYAB5MwU9r62d+/qMlTIRz9gRl8FRJQ8UQTRTORg5goca5VSiFi31h1D5AsjKiEiqDs5GeIuf9FSEDYAXDUvPaQj90OyStqa+JRbhgrWwABX2DkLnNnjxoHws5xU2NTQJj6hTN0iYY0fOl4BTUVxNfId7oNb9/1LuCgsABN5Q/96yIyN0C8J1vnq8vz+lf4EgdkPIo9gVO+2VYaZjim5hWriIMBe/6RYWUdvuuNAdlay1Gjyl7Iv8cTuOqgVHv7LxjZPGyJUVPYwyvwHnng9pAHEeLu3/4gSNJskkwUFVtIECWrpUipjArsIBimHA0MTaldRbzzAzV4mqE5BKXXv4w==
*/