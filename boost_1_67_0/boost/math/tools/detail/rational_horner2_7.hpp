//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_7_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_7_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_7.hpp
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
*/