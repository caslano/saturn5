//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_2_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_2_HPP

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


/* rational_horner3_2.hpp
LT3RDmOkzfas6VroxvYmJNfE1tgMm8OZyflTfK6vdaG3iFb9dr/ZkTBuWwypoWYzO2LYHS5nHYHb7jr0qD7ecxrNRyqSqXV26TjdVbTc7GyuOS5TYXPw9KjXZqa8UrgHPrI1Up1PsVVArW2Ragv4biU6g04oek2n63W8YJVE+qSnI+NYWs9r4+Ye2y1kLejOx/tef1u0NdfguOV4qs8ZI5vr/emqLWuZN6K8tRK7sme7ejDdBLuJUw9W8zXNFlobcZzRnF6FkyclaA/2/d5QyZszlk9JUD5NsNLh8uYkl+rsBJ/V6GJRJ9bqoeQyTH7qHriiR7ki5VBijfQLAUMojljOKFYcuIed3ulLm4WxWeAHKQprId6MF4BtCeIgjg9kvyPt3XYQbMC67y+cERdMJa+794cTT1npQ3E9RrgiwrmNawh+LVnHi9HkwHMjY0WHbY93p3F9N1qJebtpdWbZOhK0bmRPDoE5AutwWy4yM80Crxs5a3PTXPFIje6H5krp6R3SMZOJ20oyFdiM1qtbST+zUymO57q88aL+uMe3W02NWY6mrczqR6LCLAe2J5XGvGv4PEtpSGkbIAufWkq9x6+bu04Q5dm8vT2IXhrWd62aNd25bWYAiPIgz+ullc2Z7pz2vLaSMySn+JOm
*/