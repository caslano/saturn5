//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_5_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_5_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_5.hpp
gEvD6PWKwI0TwFnMLTms+F4EeEY/PrNNY9p80DVVavS6SNJ5PB1JZ7xYpkrG4DjFP1OF4Nwo21+P4n1NfVUc0EtCUzD1yCWh78TSOPwkajF0peUQ9G6oFYKj538aOTXrrrdsM1tHsEpmSzStbQ+N3boA5GITFH8PtDdNV9NEtMvp+3MwPGYA6Uc8w3kwvCqKxQDeVvM0EPYLqVZnveryRX4AUEsDBAoAAAAIAC1nSlKQwwCZyQIAAKwMAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA3MFVUBQABtkgkYO2X32vbMBDH3wX5H24ppWuZa6dZGRgvrJSyFMYS2qx7VuVzLOJIxpLr+L/fScqPtd0/MMg9JJHudPe9kx4+ySwaK7jBCcukKjR9rbDvdJObCZsuFnP/AfPZ44Jl8cGVxSH6hJ3AIzYv2ERG5siyBuuqJ3/OLQ8Z4tHlCD4nY/iugXe8B65yMJ0RlTY4YOF0Ck5IZPwiLviKPLdaWVQ2WvQ1Ov/GxqVdVwfHD1RLW6Zwfe33FAortUphm3nAet0CbxCUtmDauqbtHKyGZwReVboLK4MkyJZSLQ2U2FATcVCfBTlinU+YWck6hatxkpD7r/0s3nbsR3FbSScsjEL4xT7NhJXW
*/