//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_17_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_17_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((((b[16] * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) / ((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_17.hpp
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
*/