//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_15_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_15_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_15.hpp
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
*/