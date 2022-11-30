//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_4_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_4_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_4.hpp
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
*/