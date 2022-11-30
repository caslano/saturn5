//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_18_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_18_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((((((a[17] * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((((((b[17] * x + b[16]) * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) * z + a[17]) / (((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]) * z + b[17]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_18.hpp
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
*/