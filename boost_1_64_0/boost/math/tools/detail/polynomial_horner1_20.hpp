//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_20_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_20_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((((a[17] * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((((a[18] * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((((((a[19] * x + a[18]) * x + a[17]) * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_20.hpp
eaOYtk97ybUy24UVwlLjd8eWzy8unk6XUVGcv7024z/DDOcVJgzRXnW6DwTKvUKE1q2iSqBrwoZpiKri8reftuI4lstZVOvKqIpZ6IZWvNnw5RJLWKZdxSHWYcSK79Xm5bJMW0oq2fphv3FMUy/R88d4YT8vcBStrLYmh1lOz3clnH+C+sJo4yQ2yI/kk0ubCSat1Y+fhjhOmbbiDuIcJpy47srlLGqdbURtxayeFVYNWA8osIzDzlWNzcDyN662Bjl0ujy/bmkluUhmgRoX5VZLPNWSRlMN8cqyCkaCNRCjlWCm9cNpPlPJyuqwwNGChvk4z3GWzh6McF4KcBpXVZbUYbkbZysQ5/UlDlWqbaSAOGN73glx2oaIStCZPYzgEc4HCpxWEayYyPPtzOmHjO35OMw3ooitNff2xFkLxPlyieOk1o22EGdsz88BjpSEWMNYXz58bM+fCxxuHaWqkTnOucWxPcfPFDF8iFCO9OVzYWzPLc8UOFJYJmgDccb23Afg2MoxTpye2WPn2LNY4MjKYMtpbo+PwzW2RwAcozTTjMmZPXtz7FktcRjXbds0ECfZE9+/zeUWiVCNDFP3J6sGj9Za+zmvQoS2vG6UQG7FMdLwhtEiRhtIE0ayNsxiqdBzd7avOb80hJ8MHTd8dxPiGCm5aZlA+zFMIMR5W4FDa6qkExRN5i+SY+yqXI4QVBPeGmpbP5iu+CPPne6aoB/qDzepmI34z9i84P+xsTW5lPvZfR/gSyS5rjlm8Qz0PyyTL/Vp8RWliAnvQkqaKybFd4ZDYsD94gcsgr3fyhHRVjVysnlijI0+YC4WmK1TXNbcXRl06WwOGmOq5XqWKGuxU/3t6Gf0k56IuVVgylYa1eorG+pbYYaZ6shi8Wa3qavugeXODywccBUxMApc2mrBjaiviOtbS44b76AvQr8V4bhtw9x8Va2cX3rC5JrkihYSEXaUet9KWPf+DNIjEBWNwE3Ni/Rs7F1YD9F8QQXM8+HUEsgHQbRUyjq0sbPtscf5sJjzkxa1XBgpaHtF3FTbUJCP5bgE84EzTTCzPMsH0iVhbj6ktvOKIj2McuqcvWJyUj1E6R2/JXh+2BpiwmtJe5uTldl1Z5gHny8wKSGdS+0VQVNFBD7Px87CWMGiFUpwgogHPr8EoDf4MO6chdiSMKGZEVfETpURnMuKs+X8jHDqiJ1d6nfeSWSykWU3jb5auZxCmtdtixXz8KHy+xbra1gZC2UHYBGEFa65lDXyNzMC2vmlEd40+ngX6VQtaytGQ7tLVmao0ccb5q2yhmHhDDr0F9dXDtcv7cesTfcI3gmwGtRWEjdKkbl7EjAmK4rrjLPFOkNjpRlD3YX5pYgMfSELXKsZwRWXV9ybyHDjWwC5jmWmjXEMM3RpGiqTd04d1rMD5j8LTNIYajjGcH9ivq3xXvPD4PhnKBWy0i6/wxL8Yp+1vXkU/Kbzep2Pf+hhMC2c0YpZ14L9ivn27w72P+Vh8O3autK8sr393uO1tH+rwKw1VtwpecVdiwwz3v0q7K8lNwzzKtnfO9sebGz/J/vfU6QFV67RjJO4l3EV9n8c2C9qohR1Mti/qgLiYH+cjz+s9GEyuHVaoo3DNT+rCt4za9ON6IC0xYf5OJAzqDaaCGOb3ObVg6Nwvye4BRXd2ELyETxXvEvaCitrohDxt9ecTwBw3CWrfUIu3m+YR+fyS5Ri7VzVeHtXalL6eT3kXPnWUyVVQ3Bu6/7e9nRvF/bzAshZxDGlRMlkahqra5/OzeECaXmPYgfoaZFtK8EVbufa6rKEZHFnXwHsNbVtHDHeXMZXRvdEXl/YS2rcyKZqQdluX4weyO1QD3M=
*/