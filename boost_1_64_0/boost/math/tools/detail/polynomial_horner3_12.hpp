//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_12_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_12_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_12.hpp
Nnx+waNPA30C0m/4h5+i6cfWji4sr66sLAo5DKzJRAzmNe2YdY2BdHY/tR8jh4o1F/OFdoyRA/b88GI/Rg4nay5mx1IrxsjpQD23YSan1lzM2eVWjJFzAMaHlX6MnJeuIcxqK8bICQHztBbMNJTLYs6utWKMHA7l6vVj5Hx0zcUcPtWKATlNm0qgbT4dMBtHhotyhtlp3tYa3nlI0rrHm0+z3SbOErytbmOzzw7xgRcWULy7HQqryAtzYzCRNfSzOxEdaBJg40Ev3lrRwY312KkFea95Wc+C76XeEPjobQDTfvnBXfvt2I/n5RDwhvFAXO+83I0BeWSIowtD8pO5y548xI3JExWZCKM0ICbkhT7gv5fCz7j4sZTGYRBlNXmqOjeLNe4wwuUZL6M4qshTxzzcExGuCKIkTsKSPHVc4ab0fqqLCympBCtFRAuipsO8mgmqukyDAt/VP+3yPUSESVpGISerByZW1udtmKlU41+A9JHXYVjXomrwy6G5X2Pxr0H4IqUh5SED/PpqG/7tCM/KuKB5nQF+FeG1fs67+NG4TiKR1jlZ8uM6fBTpJyOU1qyoi5pYUx3QGX5QDvwpnZ15bL0hYEjn6wakJyYyzmgRQr7csGedg2N6L8bFF6QqyiDnYQEMx+dloND1Z6z06fY3qOx1UBdxUJcbXjkzxjPD3l36s4uviYjhEnyeqCJFKS9Yyjx9ffTNHUdfJS2DIqljoi4YWdxFhKuzuqo5jcgxjdN52DKN/GHDhIlK0FyrFZ6WNOXU58u7pl1dllkWVyllG+XUGdbYvS52MklzkQtJd++mGuwIwlasKinNEmI9P5x+Pe1ip1keSU2zlKj3HQzc6Jq5+Ar6v4jqCtzchWw5JZdN55DWjbnXPu3FsOJZErOqIhsh5CZa3qGyMXAQb0hyqf4syzSrf6OLGF9YxMdIUqdpIFLNt7C08VbW4hka9PkLnnV5BRFhmMYiyqCMuVdKo8ePujwFkb0bQhDVZNV4CGP8RYxPElFHJQ2JLRDG73jkkNMnUsariGayG1nfWnwH6YZp7B8VZWUS13CdAdaqjwlmOAQFByb7XsyFqSbWeJ+lVPFjA417zQCcis8b6Ld/Vg2u1bKAWPNOtNgEC6IhD3fXbyJu4E2kL1MtcvjUmCNhgzFe3m2YkQ05SC2qvAbTacM0GbIY8TCTH4Rz5VziNj8+ptJ3qqbxnYAsFYGgrLj+cV2uCW8v5yxjIM9Gpup1nza7Du93wNpqt7y7Nw70vqo0OJBzWcbOnWtw2mRDJGxJBjsi6b+9jxw/G/rA6js6d2z92CLgVbo/vireJG/Sn5gAvDKNNvlmfrgqY+4mDR1ZfJMoYEAXb+jHmIQAA/n6ocIYq20Qag0t0xqZBIxr8QzIyPmaxuQO6vi8SesHd5K2dwowqCkYQTBvPTLe8SRsvGO1KL87OWywc4DFjar5/pTmuyNBfV+X35EmIO/y+zPN9/5aafaoJGYZMH6LcebJ67KxHx0ybU51FUufuDGmQzht9829527B9IV1581XTIOuauQ+6yaY1tNyFf2Gm1p6b+GZKE/rw0BDdQrZNvTd23x6ky1Df0UfHb+582dNz/0UrIyzNzMYlIp5T/Xm/XQ/tvezFMZe/N647q2eijG4ue0I5192N+ujiVsZXPuldifO896dCNt6ed19n+FXt7b49kvqVva/boOwrZe63ZjTR3a34v3M21jyd1B4bOLRW47FHfsxC+u2/i610Js3GhT/A+4E9KvZSKubCwjbOhwauUf2XA0LWbRyf4awbUOyLe/MnRXW2EIQZelfN3Rkcw2d3aWPDhJMG/yCobdNI+w7m0fu2ooDWfZtl3YMFMg=
*/