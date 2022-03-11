//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_13_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_13_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / (((((b[10] * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10] + ((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10] + ((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((((b[11] * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((((b[10] * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z + ((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) / ((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z + ((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((((b[12] * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((((b[11] * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12] + (((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z) / ((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12] + (((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_13.hpp
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
*/