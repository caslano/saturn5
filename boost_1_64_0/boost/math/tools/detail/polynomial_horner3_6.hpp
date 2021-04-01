//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_6_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_6_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_6.hpp
YDTt6juhXcTorKp6ZLx/TClLMQQNjDkXm6oVYfRmjkRe7jClQesikFdR3RBYJgQ4Xosn3nBnJXZNvY3l6LXxoSP2uh22vLMH9K5lN1jbjOdnd2hAef7zEF9eE97RiW6drZp3uj87SDSGdEfuWK6+cmbiiqmG1w1z8Ok9/6pMg6sOC0qxkkaJaRPeAgVOqipapQUilnOCf8SSI27Tuc5yTRFINrdgHdcbvloelAwdhQ68T8GVDi9NKER4SDov66dv+rwX68+Qk97HBEn5t+16MSDmR5pJKPn6iuWpj4Yxa5jq/yvJDmhBi7+08xof8VBwDoy23bWbHOEe5JPsFRqX25uuCaot2ZoQYVCXvyv33jTvU+X53dlkvuV70Me9973YGTE2TuY+k2d5U8qe7wvTFki95XSgBd14iXy84d5xhNTCTWMuquh31VRG6iommXpcMKx0G/i2qUXIharkAO9CKbq8kmkE3SP+SXGnFkdOyE0l6VdKvFJiewuXhF/4ejrWSihWN9Bx/+x24daEvwRWIk1at5YZ+arqiLv41IWX5+PHEgWGAEOrkIw3lg==
*/