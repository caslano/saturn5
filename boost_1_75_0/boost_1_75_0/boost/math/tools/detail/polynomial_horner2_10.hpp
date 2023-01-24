//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_10.hpp
cP07mtJAy4Ey9yPT+aDLR0fG/7N8dNnt3yIfveR/Jx/d8PZ3k49u/rCnXsCwpb7zMSO2gaYTSD1QNt/GhEqZQaiUYVAyoRDYaemhEECBq1JF3WtV9hBQniJqMunuLsVHKL/vhLoaFb7BeAOGCyB8R+GTI7NIkJ+jehbPwtClJ1btYzG+a9KJupM1Du/O8flW+V8nVApGUHcyDLDt2M4UdBsaCfw7ELtOczYhL81/VacE0tG8NA35OEUL8L9lN6cHQtO4D4w4rNGP85WnqlXMtjR9KSumg3HPnUvJuvn9GkyD0N9QUf++xqyiXlxjVlFfWmNWUR9bYlZRD1liVlG/8IBZRR16wKyiPhYxq6hjEbOKuihiVlG/FDarqB8Km1XUU8JmFfXuxWYV9czFZhW1usisot6/yKyifmqRWUXtX2RSUdsmvguQJjeJlGg9/M412TuK34pOFqkh+RS5rSYQV82TZAk2V2uw9LNwEIEv2xtfAeijzB2QP0u+i9pFW7RNTV4SkN8MFOzzubamzfOVZvSJ9JOiO9Lm+QGKkkVq0jZUjbZZUVqytBmlYMmmIhWrRyE/ei9vQ6Gu8utDdjTzQUkZBjuOS4VStBrxUTUmL6vG5GXVuZadZfkWZfznNljuZcWpgbvghG1Egfz5UqyoTl2aLcmTYFg7pditzmR/SR6Xgyxh7FY3SuRnwhxMhH1TnoOwCA9uzMEewUVV
*/