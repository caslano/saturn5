//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_2_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_2_HPP

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


/* polynomial_horner2_2.hpp
9zRp3W04z5nX5Uv3nu/gYmDFs/O27/vyTv0cbRTc2/zRbTbv7PwFIqvqYt+jfe+dba6crq/P0/7wXTQGghvY5upe5MA+qvzF1Cayb3tXxungj7+bwVfn55+HxUN70BynjFu2edM+zuHGIV3j92K85ZmBNo79xkCXY0eKdn7DfTo8N2K6X7IfuSurQ9eca8+zyuGjhJ/TWjA9lx6gMd2OeVFY3/MPEO+MPEegixP1LD+I47oLMzTyC/Bgw5MrGt7uyB/vQ2wOZIbkP4rYubOsxO279w8FzulzS8tz004vhZx/KE5PH2X5LF1+GOO4/Rimd/ThwANS9zzwMmJz88vz69wu1j2F0Ucgb8X1Vb/IMIyf7gchDr0c+9CAOl7ySMNhVkN7pI/WuIZUoUzPnlm17LpvvI+jRhHyA6s41Icon/kDwkcmADdjDPCW5BqPbL73KODLi9PDrvspWZ1Mh96Up82HvJFj/Tzd0SPv8ka8pbPw/RB5r3tMPw8+xdn+oF4x2c+DEUsOSudV3MY3bL0DfHOpXT9Z8HAERtKeA1siayMW7/KTu7xzZ4n5AOOHturwTI1Dzqm2yxlI082uD+cfT5DlM6rGXPnlZoir8H/vkeWrvjnMnTtzRo76S3PqW5cv+cP1y3SYJdGJqRPT7dRTRhQWDr+DaZg+xD1YYgXDgjLy6qe209lUVNHXNNDxZRmvQwp8/Z2twbj1wXAdN9zdnUZsyD1NXDsyhc2xtNAHO8CWGEYf+u4rsWeQTnhtS52FUkmANiHxZzk4LGptEtjh7IZ2IIMB7/kb8jDBdEcZxppNmgpNSO5k2GP5izc5+Nz8wsy5ZeRhv2HxsGJqEr49srmPI9czwLPvLG+xeINumiZHGb5hmm7YPGoEQKO2uhU4uoojh1J1T13PR4b1HFxMr+vzZ1jX9/K6jvm4Ln8OMdt6dWjl4+ImjlM+gGf52rF5lAsg0bxiM+dQLoBHtj21xeINuml6/CjHKU2c9xfkcdsCTfdxeIf9ELMvT5ndd12btfsb9XoZHK4YmH64NufyP8TP6NRekKSNV970GlVGIKC+6bL9x7OgbDE+LGD0GQR7t3Y5IdW6o7J5I47Oj31PaMtG3AHepXkXcXh52mRrLv3l0T6+y6V1xuG+MiY6pvXUdsa1OahvYow4WMYsdqo31xR3wyKW+dfzpZ3EI52uBWgc+osqwzldeNQ2v/4hdxyifu+IXQZRIPNMfd6RbrtknOvEIXsDgfV3jEM50Lx7Un9HvAFPy+Qow3rTcgM53P5RQHOXS1uB02/PKCA73hjasTOef5nbkY0fE7atQnf8YDilP+yOHxMdW4Xu+EEcloOwM35M2DYL3fGD4W6amF0neuwaOuPHBLMrT1VtzgA4fVbSlp7npzfvB3LYZ+F49FtVTsODvLqo6M00+XOU2VzRMP+nNvfi2FHh+mpLL4/1JW+yOSz3SIZ48Wxpl0u8h1k+8Y52y8eKn9KYbudc4lC8+8Ykh5UjixnHqo8Cj5elmxtsJ9c36G8ubdDf/AiWGaydpJiHC5tsDPPLOD9DDmsfqZ3P129mHEq95t2TfC4Sb8DTMjHKsN60/JY4vF2k1N+8aqvkbNQuUhrLT7ljedvWjVff8lhu2sXPVLkMzz33tYvH2HYe0li76MF72kUvj7cLm8Nyj2TWLjpc5DFfkcQb9Mf7ZeTw8iMubxePYeXIYmbt4jG8LN3c4Jpxf886dW5FMiGNwFEVsDPPg49F1kyAuFcngCtVGDrsQ9sbF2AfcyfrpVD2089ZXjk9s2zzR0ZW7mvOxaj60VGG30teArgbn7uZbM1FDzr118/TLC/i9Fbr7wN0/f2Rip/bZGhG4Nw=
*/