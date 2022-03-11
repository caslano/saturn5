//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_19_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_19_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((((((((((a[18] * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((((((((((b[18] * x + b[17]) * x + b[16]) * x + b[15]) * x + b[14]) * x + b[13]) * x + b[12]) * x + b[11]) * x + b[10]) * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) * z + a[11]) * z + a[12]) * z + a[13]) * z + a[14]) * z + a[15]) * z + a[16]) * z + a[17]) * z + a[18]) / ((((((((((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]) * z + b[11]) * z + b[12]) * z + b[13]) * z + b[14]) * z + b[15]) * z + b[16]) * z + b[17]) * z + b[18]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_19.hpp
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
*/