//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_14_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_14_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_14.hpp
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
*/