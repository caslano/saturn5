//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_4_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_4_HPP

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


/* rational_horner2_4.hpp
sHeir8+eDy6Q1mYsBpI3TtS/kf7Wv9EyOhiiw13ibnRPJOJpp1wKhmVAsmE1D9s7Iax71YyCJhxypYqwXFtRNBn7E5Gs2F6GYZs8qCkNCeTzXOljksH69kv3KROU6a6dW7Bo8wfvYmU4P6L12O6VQaJrLpn7qDgjnlNc6yOAtEqO8MWnGjRPiOEaDGTLCA2vDmbJiRGFZ98+Wko21Y6ADXF6FpiAlQpGHmvq9t1HVfRV2yTfwEfYaa6/jrA6fwBIaSTa+68S3CsPF4pH+iVVHlQJaniECUywWFHgGfXGIsbBL+jX9Yl3zQJVqohyt0Mx0MbjlNph2vPFw67N3u03jeJmR3pLDpTw5HksjqBlFfE1pvUYFEMjCNNhug+AL3+ISN5Uxfu6U+jA1SkQAZK5VmS/MxrNRuKTKuD31w8mi2j0kPR6vhS1z6Dyn7CfEhIPos29SRYu8xJilRvLFoZISnz5xHz9XtgFcIPIw7g4Sy2I4IX2AxD0UAbbd2wA2T512je3xA3KncNksBmtafOJRfR+TZj/vGNE9Pl2bmvO9MYPKJ4bwdDizOy0gw==
*/