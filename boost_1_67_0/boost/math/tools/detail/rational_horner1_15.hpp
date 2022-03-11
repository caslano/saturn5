//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_15_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_15_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_15.hpp
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
*/