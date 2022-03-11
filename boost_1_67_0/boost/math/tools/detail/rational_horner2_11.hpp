//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_11_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_11_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_11.hpp
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
*/