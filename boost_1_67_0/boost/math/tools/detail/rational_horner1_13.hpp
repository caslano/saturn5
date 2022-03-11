//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_13_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_13_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_13.hpp
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
*/