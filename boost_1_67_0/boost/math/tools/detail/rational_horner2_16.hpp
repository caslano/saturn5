//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_16_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_16_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / (((((((b[14] * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((((((b[13] * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14] + ((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z) / (((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14] + ((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((((((b[15] * x2 + b[13]) * x2 + b[11]) * x2 + b[9]) * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((((((b[14] * x2 + b[12]) * x2 + b[10]) * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10]) * z2 + a[12]) * z2 + a[14]) * z + ((((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z2 + a[11]) * z2 + a[13]) * z2 + a[15]) / ((((((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10]) * z2 + b[12]) * z2 + b[14]) * z + ((((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z2 + b[11]) * z2 + b[13]) * z2 + b[15]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_16.hpp
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
*/