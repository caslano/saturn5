//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_11_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_11_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_11.hpp
3dNEcOXgcPDz2LicoHztcFhLPJX9gWiLM3z9NorZOvWHHHYjbvsY6UzMY7PEGaBZnTUQpXmTgUKY7A7EHhJPvQNJR5QD9ef3EFClKuxDbkNZJCKo0n0y3S9/Kck3UO6F/gDa+ZG+KCL9/CtEOCcI/N8agCT4TkmOU6wuOAIr4thT3lvx36HliNnwgDmDztPCv4c8x5pImi9nD/phJtTVKkiUdmXS32wYX8aGPmIYJuay9VouIVO8noA8BK0E0jE2jFfF0BLAFO0k4/zdJrIf8XvCj5ELusf7idv+cbXuSP05nC1kvjBIC5qDSR5MeeJQDw6fREtJJ55jQV9ZWI2ykzvR7TqfGSzll4+Z3K5N0Xq65RaBiqZerbl55wMq/yt0kCw4gebMUX6OtcRt40spJAo7dlPsNGjhamqhxeyjS3qkbVhAyaO3h4hGBUwZIzcjN3AlvnhZLlDx50nxifkULyxuay9hF+24bXQGk7V4qEyCa2+8QlE+fAwPSvIiK7y5eU9Pv+P/PF36PJndl4UPkNedzCqtyFnUrwAlg5RPINw/+Qlc5sqvASNO2eeEzunM47T+qI6R1Gpnauwj+XBEV8fjSYO6r1wYzrQcQUjIXujwlBy1MebNTQ4qHZuzaBBGrYrehmqvdinmzcFgawciHxLtsjTH4voJ+Ytj7RFK5qCW5e70uq3N/IwTPKgSPsMED3CXI0+BNiSY1Yz9
*/