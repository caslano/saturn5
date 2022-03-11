//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_8_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_8_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_8.hpp
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
*/