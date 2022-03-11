//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_9_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_9_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8] + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8] + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_9.hpp
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
*/