//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_10_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_10_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_10.hpp
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
*/