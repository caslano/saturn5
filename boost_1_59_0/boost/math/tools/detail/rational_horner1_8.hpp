//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_8_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_8_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_8.hpp
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
*/