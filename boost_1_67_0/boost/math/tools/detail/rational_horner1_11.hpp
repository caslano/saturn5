//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_11_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_11_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_11.hpp
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
*/