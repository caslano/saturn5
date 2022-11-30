//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_8_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_8_HPP

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
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z + ((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z + ((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_8.hpp
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
*/