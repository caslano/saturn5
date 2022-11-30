//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_16_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_16_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_16.hpp
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
*/