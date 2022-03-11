//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_7_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_7_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_7.hpp
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
*/