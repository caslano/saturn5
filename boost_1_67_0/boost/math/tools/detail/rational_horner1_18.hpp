//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_18_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_18_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((((((((((a[17] * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((((((((((b[17] * x + b[16]) * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) * z + a[17]) / (((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]) * z + b[17]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_18.hpp
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
*/