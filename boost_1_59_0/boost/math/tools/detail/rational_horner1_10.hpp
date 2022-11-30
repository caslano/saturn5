//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_10_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_10_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_10.hpp
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
*/