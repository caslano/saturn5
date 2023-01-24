//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_3_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_3_HPP

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
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_3.hpp
som1PZHsTpFJdkkpyZbDJ7auleCT47Uq5BPoddjTRBc++TVJ5RPvjymfRAoKn0zrwfmkcw/OJ0e7cz7Z0ZvzyS/dOJ/M6cb5JKgb55MvujI+IYfP9eYdSJldfntdYZdG4NbeMi6pTH6Zz/llW2QpflkV6cwvkU78shC+Ii4u0vBWtboIDQQQ4tlelxAP7YQS4unzqotWmxbgiVY7ai2feMrgnfee9ZR3Lusr5B1qPCyzct4J3kJ55+x4hXcWj+e80388550fkjjvTEnivOOdxHlnxTjOO93Gcd65PpbxDtQJPcw4QwWuNdg8Z6HvTG5YKOl3wkLemjJZ6B+SSDYUTtpXZrnU12c1PamvulllsZDcN3bRe3+HVYqH2tWsUPWFeZPa+nkR56EhPZD2q1OW7nvVHQtJ1RWld796ZVjoKVIDbZJcWGigqGP0sn4roZcwb0YvzyxyoZeh/p4owa0Ly6AXd9yypLPn3FJQo0IBQ8BM+4KFjFv+6fLw3LKimiLmt6s9Km7xqeGJWAdmPgC3dOhUCW6ZVN2zvkqLTBdu2TxZ5ZbmWyi3JPC+Sr1wzi2Xwzi3JIVxbjkWxbnl1c6cW5p25txytBPnlpc6OfVV3s/CfZUWkz3oq5zsXIpL9nYur6/ybJbcV5lXE/VVAhe4qKAe1TxRQUszHqyvMv4ZTzljQ1XP+iojMzhnJH9EOcM2ReGMPlM4ZwRM4Zzx
*/