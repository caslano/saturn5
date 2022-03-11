//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_12_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_12_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_12.hpp
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
*/