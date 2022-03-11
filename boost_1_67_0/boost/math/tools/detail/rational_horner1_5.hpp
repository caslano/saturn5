//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_5_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_5_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_5.hpp
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
*/