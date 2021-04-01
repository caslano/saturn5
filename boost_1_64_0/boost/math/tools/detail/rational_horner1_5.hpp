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
vYMhr/lqCn8XM5UZZ5fRGf+PonE2FzHGsL4z/Ey8Mnm7OwB6/XW6sWsRNznvfhQeDTt7t/cBMPi00Fn+N/YSJ2YmT0w9HvZMjwDPKfAGYya+MX69fdbWuH5l5k9fXMWtfSjdDAVsptsfkYTasI5i7TdGOQOE3wLXh3FRbjlufV4KCpDjMZhMrABfdSPNjX81VkTqN5ZLBVYp2FvxS9KESkBHEUorRBLsynXtD4gZCiOLNNaUaqqVNnbToT/sslaDUg5hNDaGQcyCW82Bii5BBoOGQXIGMJmhYjszk8LY2UVXqHpP20a0PyWgiBIlrQcCLJ2TgkEumCdu5/VIwy019ZSnLBcLuYJD8A0RUrgPRWISon6LJAC/QgXoz52Q6KcM1AatAr5aG4UNv5DI5ilBSV+k9cO8zf/ySDk/XGLAo91JPcfiXt0lFR5qnVaizVpEt0glsSCkV6tq/MTNXt/2Yr4HjBnHsnICTb4SzA04Sbc90fRuDuVmNckLeUJBDGzDIRo2GcjS/7dO4K6KFnL9wcukN/IuRY3UMfg6pCy96BaS1tpij9x/q6140A==
*/