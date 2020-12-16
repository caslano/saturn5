//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_16.hpp
kRF5Nn+F1b04sItSyhptS0jdm3gVS/qroEwnhGHa4ZwRZyjza6BM5zhWNmj0nuaq2cr8cL/fvSqpVDxXIddzZ7ij68u8nsebJEI6dJNz1m/UDpdyP/fGS125yRJto1K5rkO53wPlUusd5rx45eYh2DZxrdwfAhsoyQ1VlqM30OHe4h3feHDvj2QIJ8STub6U0LHcn4JyS4R+H5VFZ/tDub8E9SVKGYwjnevbNveHV5b3Cb18RImq4JXhZcCPl+EH9bv8qcAvNQTMVORz3dvEi+uZ7VPBPSahLvIkN9f1tcN18pdB+Zy53Du9mnVokzOuPixZHsZIMVZGkxvzX/oSnFU/L8DlFJZaC7+0Q9XltPp5AV1CLBtARmZdlk7Zyd8G5RvpjFFpUgXsiU+rD++gC+dY0WBp6ZnblWm6fBxw0ZL+UumybcO0r9wHa/6CXt4j54OkKSuTCN80zC7j89RzUs9Pob3KeQdmaJM+vw6erm2+uNanuOMKdPrOg6JPpsHHtzNP6/VtTPfYXcaEtSrO6rTMMZd49X+B+lgSGEnaLPrsdPrQheOngMOSmJdaEmaFsqfCTILrXm3Qh2GjSi7Nps/OSp/6Lfy04U0PDSJ6tcnpnHK01PfnqKwkx4G/7fEMrfkdX9FjrwUphSJ6ymoJOa4BDoYEDoYanNDpXP6NnXdmhvy/xmGWsQCwDgWjVFLR/Ys8mJepfsuNa1MNqJmLanmm+rIi8rw42M/5t5naKJlNDNa1jwJ+gyiTWjIhETt8V3YAydHJ8i4tR4HepsJip8/2ZVwh3uisQ0I0DG81PjfYyUsavY5T/Q7Ly7/7p6fFze7W3nJs1/rMV3qsQ1EXPy2nUHYzuXdy3KKd1vh9vXxA1AbhopRoP0chzv6Kh13Cy/OaH7THvEqWJ43ES0TH+fsH0M6OUCkk1YjmLcVQevMF7jEehUQUp+UOfB2OtrbNQ58O+4bixjrr3GSw802gzPIOOttgeuPRhXivffhyX8arIo02BmyQW3Sq7zMAl0aiRK/laeKaSPbO9w8Pb+V3QGXE5dfbAurHenxAjjMqZS5nCvx/eNEreFjfkvTniAl57JzAc96w7Ic8fQe9/6w+1HvDotOtnuuKw4bRKPJaOD9neFX1e4TlM2MJYUHW8nevwPJrTA9gC46CZdQIX5xjS978s+xe+r7skn/QdGo+xp+GnJZ5TyJPC+f0rdM4W67gU9BO3njlorcoznJXlna6AHVTSOaJxgU75Ph6w0EZF1OO4uFt9CcAniBJaEjKORDjuCl2UGMkAZxAJaZueYELeW+eHuznTXBlbXPpV2Cbece5wATFN24kd+v5MOChKCmiy40t4IEOh6jGrhls47D3GPshfHN+WXHRFKxrzMDrsSTGSwV4oRNpixfyjDF2B2PYBgawwBm02eXlPfYqEyV5MXFlKzjERB44WAzMGywBB3T+bDE1nwHX6EiSDzpOC+68flZIjTHfYxwi1JYXarh8nOWbuN05rw3EHPWYhAyVBBMiK0/XarU/fuQZw5kxt1YRbhaiKS5Sm9famxTIZQXRSmR842otVdcfwMXLm2atfFqoDo5zPOuT08oGbPgVyEdVuSGxovF1rVvv9ABfQM5z7mmSULe8deFr5vqGFPIKZy3FCjfersXrG6hnDudTJgiimK6Nd3jn4PxiHef1hQCHkXTUGSkVyj3s7aWDvR2Mu7b/AbjpyN5iYcLCV5+uVsr2ztwNnMILGqnEjROMOVx9g3vcDsWOpkhEYawX52rZO9ztZXcZLx4a3KH33z08Ozo9OTlapsj6rqqXT0hRrwnhBN2+m99w4ztnBy2fdfOxAhyJKiOC02jzNvj0bJXL45M=
*/