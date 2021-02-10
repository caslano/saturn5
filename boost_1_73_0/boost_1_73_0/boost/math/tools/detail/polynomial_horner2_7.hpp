//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_7.hpp
ZXIvdGVzdHMvZGF0YS90ZXN0MTA3MVVUBQABtkgkYO1WbW/bNhD+TsD/4eohX4o4kvzSBoJiIGsLNOjQGLHafGaok0REIjWSquv++h0pv6RNG2zrBuzDAEMgxbvj3XPPPXLm0DrBLS7ZL3DZu1ob+YU7qRVIC73FApyGUhuBIHrT+J1B3sgvCK7mjh4IFs0nNORAMWyH/F6qCt7m+QqSs/gMcjIx+HtPN0Hb0+PO7y0qBxvp6hBCaGNQOArAv0qiRl6gOYW73lE2D+OegtKOFskZy6Qq9ZJl97jdaFPYJfNG4QGrD/mweC0rn4APzyYTrrZh5Y8iisay6OidRUNAymYdSptYWSDLDHbNlo4L7vjy4ArzOPkGuhuqVhrCzm6saLTFERsCpRDwJiBH7Pb2duLdCAcpuMMUfm24uG95JUXAuL0YV7JtEXjTwJYAtjNhZs6Ov+vL7d9x26HypJ9HWgm8GCfJdDqbzecU6ZVWjqJM8m2HvqjPLuoaLtXx5DdUlatTmC3CO0XdJWhS2OExYrnZAq/IBwgxVxPd9q3dEeoZNWKAmhqRewP62b7r9I6WgUeuN4q2GyrqIRkrdBb4t6Q+FNxIhdBxS5EmlEFpdDvwsJGU/NDiJI7jB22exjFcv3uypX8elensR6j4
*/