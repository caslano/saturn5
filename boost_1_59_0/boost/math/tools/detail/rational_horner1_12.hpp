//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_12_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_12_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((b[4] * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) / ((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((b[5] * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) / (((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((b[6] * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) / ((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((b[7] * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) / (((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((b[8] * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) / ((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((b[9] * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) / (((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((b[10] * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) / ((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((b[11] * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) / (((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_12.hpp
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
*/