//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_14_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_14_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_14.hpp
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
*/