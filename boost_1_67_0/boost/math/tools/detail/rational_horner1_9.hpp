//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_9_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_9_HPP

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
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((b[4] * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) / ((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((b[5] * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) / (((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((b[6] * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) / ((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((b[7] * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) / (((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((b[8] * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) / ((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_9.hpp
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
*/