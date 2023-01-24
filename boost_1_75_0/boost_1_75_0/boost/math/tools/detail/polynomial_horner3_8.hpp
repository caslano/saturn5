//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

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
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_8.hpp
vdVUcweHCMPKpwgeuYq4iA4UDFQpP5gAZxvMWRuLMmhW2lLcZy8gQ5lIm8gFrkHyvh5Wic/vYUu+2v5UTqhX1gv1ygbYeL+XhHrlJl29st7YZMBURFqQOKhGJD5QZyKSzoB8EjteDet6hK0GjqRYDay2CjnGLShlJy2nq9ZKNkEREyQ9vMKQZHg0FdgQA3QIC3ZQLfiQzGCOutbs1AQSODHCZxjgDhseZDXx2brha1/uZ6qOUa5sU3fEsApHinsxhQw2aR571WQifAtjlwBawIe6ECdcUE78C+7pFLtWRgJZQaFeie7SdhceYSNCjEa9Ap2WIJo1mfQsF5OBZU8HuYxnKqOYbPxVuupVFe/UKfy0awqXOi5+j4nfI+K3Y0pqrA/l5fE2QzfDYuOAE/l41XPfa7raJtDShFLnVIQ5+TWTWmeX9h3y/8D/8TsWgFspas9T8xk8+aEIIbIwzSTSkGtMb2pS3qw0vVmZ8maN6c2alDfrTG/WpbxBbY7qUXdQH1mnw3qoj/GRpjNCEuLmz/UjrCKAgaiQR9Ekj0z2bWmxEy1IsuxpEnEpq5a55wElFsnmMAifjbGgSIVvjo4RoSRyKc+cLpGEOwrNkWIWSLEmJD3WxNVwnEm5Za6ftHCcASOYhA1xRiHxCCLHxboy1tnUUKILPKXemqzFHTPH4BDRTu7/zKnpaRoJHZ6mAECfiUDOONKdO1HbpmJG
*/