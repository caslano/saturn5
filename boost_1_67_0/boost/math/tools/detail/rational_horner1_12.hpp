//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_12_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_12_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((b[9] * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) / (((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((b[10] * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) / ((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((b[11] * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) / (((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_12.hpp
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
*/