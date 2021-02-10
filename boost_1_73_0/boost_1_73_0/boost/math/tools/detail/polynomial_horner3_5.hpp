//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_5_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_5_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_5.hpp
jyje4+mDe0ZblwfoMgVREjS4Cn27SrTwG1HDoK2MI5fXXtvTG2ekURnr0vNjH/+XgC2IL4H/0gnYL7qA6PaFmtN9763iw+f502a5egzYrZTY0PY1v+6uugM+tkj5qS8///7/AFBLAwQKAAAACAAtZ0pSxklxTB8CAACaAwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwODNVVAUAAbZIJGBtU11v2jAUfbeU/3BFhbJVc126CrE0QqpYVdjagkrWl2kPnnNDIoydJYYWVfvvu06gUGkvsXw/zj3nXCd2WDslaxyyuDCZpWOJ22dbpfWQjZNk1nzg9iZhnBfGYZVJhWwy2/RZLA6lsWi72Qk7gTlWG6x4XaTI4gpLvaWCVDrZQoreWQ8uzs9h+j1gX6XDCO6t+QQXA/i21j4zgN5ldPkloprb+yRgLWAEniyvm4vI5BIDNrLEyTh+h2bh8gj6TcigcoU1ESht66OqZFuiR3lxotSyMAELGM+s5cS/5ReLHd9GyEgXvq0VopoLlWQo3bpCUl2UjQ2HQNySG7LcuZLv0vsYxEausPWAewe9rfBcuByKss+1VVLntnZw7DTEou2CWNnVSpp0yPgCOn5AJER3PJ0n/cks6nrU/mz6mIje+eBz
*/