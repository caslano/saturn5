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
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
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