//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_6_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_6_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_6.hpp
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
*/