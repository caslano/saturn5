//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_11_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_11_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_11.hpp
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
*/