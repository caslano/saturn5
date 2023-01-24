//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_9_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_9_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_9.hpp
dbcUPe4ORD+1Lu1Amx351SAl+EPTf2LkKkROkgVIcXBuqFzDy1ma3SylN3rlYEsW0po1Mae8I7lX01lES2A0h8MeCnFjlWJA5/18OEoNSi2RpOZoVFZJchWgV3KBXoFpsu3063TK8+hohYj5WkuZxbKoQIqvwguNiOgjbTNwOtMSvz9ItETSdsXba2Zakln0A3AC7a57tFlDltOeIGSZi0hSs/HSc8MgHhnrN4L8SPLVJPTORI0wMMp9kPa5L0HhpWBV5grDeS2Scz5a6vz2A46oihFq9HwB9IwC1RATjyKg0tYy1xMt7NppcCapwqGyWjUCnYACpRrbBbWtew9VCs2k+s2Q0IScc+wMxiawknQ9ctDcx3tm99oT6y982KIf58v7cQcVK4pKHlq2AeyhVaz03Wg3x3Jy0npm09ZYk+Ow7CzXwzaRE+rc7s5OKRqn6B05qMAmudv3pfiNp4Lx7CtIpprOMQ2nUD8HSk3vw4B2oEeOsgIWah18mW9JibUNa6GO+PMQdCrhXBRN0duclmggi/1wcjSdVTdTsgXlJhUt5ilDR1+yb2tj0daaIFmaHMWYWa6tUmFsUmHw/Hn50OEIhnkKdXphLd1S13sBmB5VcpU1SdFGp+Qa24QOJ4ex/5QmIycYr0ZvwWmq4UuP13De0VAD8h6lCEqvw418LuFd7sU6NKGoRyu9BHqnwOHjK3mg0CWy/71D0OTv
*/