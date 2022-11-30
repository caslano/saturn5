//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_19_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_19_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((((((a[18] * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((((((b[18] * x + b[17]) * x + b[16]) * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) * z + a[17]) * z + a[18]) / ((((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]) * z + b[17]) * z + b[18]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_19.hpp
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
*/