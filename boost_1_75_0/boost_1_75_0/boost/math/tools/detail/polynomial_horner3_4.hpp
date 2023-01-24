//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_4_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_4_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_4.hpp
h4w0qWVJ5uecNoZIbjuWEi8PqhXYFCmvVtiFXY63/gIxk1XK+IdwJj3nPcuqajRNU4oWoUYASpbhpsGhoeW0lQeQzxm0kc8Lyk6aqelovdSmtGKlcrHw2hUWzDCemjSL2f4oEGugJxTaCzEetlShYzzDVs4O59E/7BoTvVv1rP2HXRvAhfoAHllBA7h7k2kAi+7XBkBhvzCyBe531DSz3uUsI7CfZQQre4xg5Xcdwdvvmkew9119BHn6CF5ZTiPY9oxpBFsW6iNIABws49PvNgLnt43A5+p9BGt6jGDNdx3BkJQR9DVGMEIfQRqPwGUewaf3mYEowwREOAg3DYKMlR/sMYiHME60nJOarR4Gsa77IDas+66DmP6O3WTeNe4dxDlnaBz0UVDY9aL1DX0ldhulKlBmhFDz5Kr9nqk1V+0Y0sL/Q4ox+g8K++ZUG57gWp29YbMnzYYn3yhPlEcOoiY24UmtjzitN9P4QSd9QKZafKnZ0r0sCvRipsu0yu/S9BcnxAsDY6QxYpgvTFuhe6OQUb8E/5yHf/pFT1sjQ0PyJiyK+eY3Ifgk3XCBOyHpgIsaYoSPIi8hrBecKHyZT0yj90UbnbpzMPHfHAbkXOqHsNzmzB9sLRGklBQiKAYCxL1Z6La014qGkgt183uUSLKtOfmNu9a0a5YlqfYdXKkw55j4lt00UYZ9OLwqFK+0SSZqzRv98Exqs7j2
*/