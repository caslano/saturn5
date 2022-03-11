//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_16_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_16_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((b[12] * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) / ((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((b[13] * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) / (((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((b[14] * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) / ((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((((b[15] * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) / (((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_16.hpp
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
*/