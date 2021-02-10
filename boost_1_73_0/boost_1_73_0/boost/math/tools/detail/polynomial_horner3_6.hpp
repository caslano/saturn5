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
5xjkPTwxekOKywpVjmo5ZCVWGjhCp8jgQ9gd3U1uHjxyCAYh/BlFvV/hR3gtK4KFMKFNQIV/1gXphhQzudau2Q+0PkGjRKYp5evw6i+grhFe8QUVhGc7T8js2uoNerLk1Xue4RXsho2kMZbGrQ3s+cKuk5A7JOggg8Tt9tRs8AmrItuCXy7IjPwAl2PLM5c1/EY00Klz6whl09Q2plhnldVD5hfU+An7hxuwMXGL4D/GB+wHyeLXCxpPT29dadF9unmcT6YPAbtWCksKn4pT/+o85f2QWLxNFoff8R9QSwMECgAAAAgALWdKUnCYYkMeAQAA3AEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDg0VVQFAAG2SCRgTZHdasMwDIXv/RSipZepN+hgFBMYI1sLpS1ttnsvUWazxC621qZvP+dnSW5syRx9PpIEoadMeoyZ0Kaw4frB+8263Mdsk6bH9oD3JGVRpA2hK2SG7O1lu/s4JcxYE2GtPWnzDcp6YoKP9YJ3SDZncziju6KLvM6RCYeX8t4I+qBVvJYaDfWKrE2CpEBJvw4DThFdQsn4IHzLjBsboYT/pyCMrDAerMNNkwJtrrLUOUz7AME7KYjMVpU0effNmvPF5nBOt8f1Yn/Y
*/