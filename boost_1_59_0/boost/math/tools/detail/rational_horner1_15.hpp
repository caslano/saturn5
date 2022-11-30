//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_15_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_15_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_15.hpp
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
*/