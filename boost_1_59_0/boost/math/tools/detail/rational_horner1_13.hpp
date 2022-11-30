//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_13_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_13_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((b[12] * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) / ((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_13.hpp
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
*/