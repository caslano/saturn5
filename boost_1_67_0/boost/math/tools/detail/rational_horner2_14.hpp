//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_14_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_14_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((((b[13] * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((((b[12] * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z + (((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) / (((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z + (((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_14.hpp
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
*/