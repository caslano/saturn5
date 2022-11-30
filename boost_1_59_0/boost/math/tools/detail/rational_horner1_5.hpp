//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_5_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_5_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_5.hpp
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
*/