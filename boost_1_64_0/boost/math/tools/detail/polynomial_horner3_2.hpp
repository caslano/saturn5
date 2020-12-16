//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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


/* polynomial_horner3_2.hpp
7gdhEpRsdeHiwuKzxFVkWdaW74D30PQFhZ9zP3NRTDQX2//tp02ZnCVBUKReDFHVOtpcp03fofgmyUfh5JWTeYk6OUDz8SOTy1nqp57vlDmmpzcGqLJiqTorZMp5LktFirI4rMtZ/GTd06I5gRtGT0zbIo0zsB0yOaXa58mjDPcIt8/TvZ4gS0MOb0mcPKaDe4IszfoCHS5wV/QdxnlSrnGapUFeYHVgSHRPa8yUO54mVcmjLGCXj0AMXjK2NoYmn1SdIyLp9ZlfVanj5oWZ3lxU4yT5V+4ByfhDdRfRynvqZm6cuHlfWIlPQlJ+FVQZzlrhhGXJkzJLzXB06dMw2GNV+7fDSIMy8svYDCPQgyYG4apzmZZ87BZB6LmBKX9ajTJWGlTZftgKo8yLxAlIcQipxn8b7XIfRB0A98IkPrRJ4hJ6mPHW1getMVG/YN+VZEN3/tWo5PfPndLKj+Pd0DbgNq+JPwwYHQvx/uQdANPju0oE+usk/TFnnheWgR+t23ePXs/Kd9AO1uFBQry88rKWLxQ5sZ6t8uCUU3qB4Mm8i58PDVMtDZcvWEYfHh7AAxVJrvYehv60BnP10gX5fxvAR/WsKzaKOzotH984iK+XKTp/Z0cauLgE02Ee3NTPw+URzd/hzbfiYv6OKTvvlma+uRfqTYEh4PRUdSrQaToxOkhO5xPfiNsKXLlGU+eGnM29c0OLdP0EfM0Ja87i+JzNwbb5p2dYd+AKt3Kj/H9eV6HeD+2JmIU0dnUDYLBfqDF8v2MjYDI7Q4aNfJP8jjLoL2yrxGj2dJgvugPgkH0a5ugO/E7DBF9lEqNh4h7vbsDlOIDPduAeJcHpGHJij4EtLdL9XYLBUzzGPbS9gJGxB89W2/VXllHsRv+zrUz7pTfDy5mbRX7uc4/12nCY5AGdb2dNfshZUQaOXyYFs63LmIi2MEjqpIC5eVz5MzHDKuE8ahFHmcs6C2BnbsNooZSdJbCT/bFeg8LquXeP9M/w/0Zfg/eZ/kK/ibW240M/s+eijwybLBggcfy4OmzhOHide3a9BAEu3kmjXDirqW+KgKNv9Ks20sgFDq6VN9sc6h/k+BaNq2Ed788hRlbDCn/IVguHo9LmHo6Noz1I97H5bciBlN1fvyUK32fEskYt1OTzmcpepWxEd+zxBAfkaxI8SnDeOGPykJ2So2aLupzA0Cl9w6o+NJAHQRt3GXY18SCZOKeP7BYc6HMya7Kn6z65RHDo6Si7Zw/B1MpKy47uJTj0di17k2Cqt2P/PHjefKOkjHOvKqOI6VTavvMeYvLdiEVp7PpVUkkJXeTwnuQx685vTGQDllR+EGdRzBqqy36f4SyRTVlVhE7O45gNqh7L996LrHT7ruOEvl+yxu5C0/0eIhuySEiUHg/748YF3TFlZySyDotiv0i8gsaL5ezoO8rnLf28KMs0LTMRpyxbcgbfUeX0GyIXs6h+FSBPWbNao9fFSv5flnyclVXkxyVr7np96+p9F8z1qEh1XLhRyeSkStdjh0xuyeLYdXNRNebkrMJfUuUyYcq4HsuT3Pd912d90zZdJ+ckXUFRuV7OYyYnZpquMzRdAfdcp0oSIFsJw/scs1a6qjCsqij2WN/UT+N60QVqI/B4UYI7ScP63+dX76opw5kbOzyKioTR3Rya/w+T/EPvKYQQk1oHbe/XSV4C5iXcS/IyV2zaw6kPw+8RWYeFJTzHFYXMMufZb4D9yoozcWN4Z8dnDSY8O86/WnEGWZXEsRehbHOco7N0bV9EUVoGsvCpya9v/XyQyMbMrRI/q8KCNZsC+/2IEvmIBb4fOHmVs0YTIbXjnJml+c2KynM8XjDL9KfaqEo=
*/