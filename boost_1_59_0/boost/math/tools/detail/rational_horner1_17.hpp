//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_17_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_17_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((b[13] * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) / (((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((b[14] * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) / ((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((((b[15] * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) / (((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((((b[16] * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) / ((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_17.hpp
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
*/