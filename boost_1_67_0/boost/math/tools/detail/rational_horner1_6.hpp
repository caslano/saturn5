//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_6_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_6_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_6.hpp
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
*/