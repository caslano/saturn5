//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_7_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_7_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_7.hpp
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
*/