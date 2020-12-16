//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_18_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_18_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_18.hpp
Mn4ce0VathgPWMmVmeQyZdKmXuiXGE+fzDO5TFLkYRiFPsYDFnBllrlMlYdR7uUxxmPL2OPyQT4u45F/PS5jP/bbT9vtJvbS1i+8WqzNS92nl+dRN/qwsPlBLto8DZuiueV3tnNz79ger8JYRFGRl3nTiqlF6Vzz+eeWwDXm6TXleXVh5YJ8HuvcmVVw2qm8zBxVfuRgv/xLj5bfpFTaYMK1MifX6M8b0W/JAeZnzXQVTaVNOAz7rAw7vbQirbGwMq3PlX1V85oC7wjjvdKHbgJkYdoYht4OhW+RgCs3nlIfhf9lM4WvnFvH8OVRCF+WPkAHL5hZtfattkL4yvOmZ2V5nZ6RUjDPJn0f3KZxCMb4wU+CDoflkRX+DxMOSwD7DbhdOhyeObDCT95Rh79AelGdp/A37YFw6Y9I5c56s/jOJhxyN0K+Lz/NfVPXSZrkUeC6iMa6Zcrvxaz88P1LLIOH6TIA5L54pwXCz8xtZLPFzRpHm9GZSQh3bfY+HQ7LjIEVPj6mwx1b/kOHu7a8ulOHK1tSXzn18E1W/1eESejFbSqYP0/0ecLaWiHSpPTTILvldbex7z5mX3k/SLeP7+p6H9UBVHx1ZuqaDkOzLpxl96wfrsuC33OEfsdgap3Y3ZvdAriMmxcY2u2jo4izckx36HBdYHfDN71NOBQMhe/epcN1wdwN31804apgsM5OfpL7iQrqKAuLJhWnZwbzxya0l2rwmM3LqPwkL6Mw9urWD6JbLaPazFOZvlZUTRQUdRD+j/0zeNFveV5i8D/2Gy3vtfWFpcjSIquLMrsJfSsLC6AvKG19I5+y9aWiTYq8DqLo5vWFla0vZPoykQWZl7XRzaRP5pf05WZebuvzYcKYlGG70Rs3S/bdYuPQo6qNP0InbU1aR2Gc5TeRtt68Xrf1BZEIoqot/aj9H/rWz6yyvGJ7Hvuk3Z7lMR3dnn+m265/bALaM2u3j9DtdlitmX8EiUkdbrvEs0KIs3Z5easJ5+3yVdtMOG+XF7abcPmcw4DCT42ZcN5exR11uG6vuZkbfoL7bCzCPAmaJhWywsbL56QB5d8D9tec+T89Y2L3Th+pfHytroF/N+WIXqbtAfSGZheHj0+2H6UtvZyFVftu0ihwhriceyj/MH+VZQWeWabKJlF7v9pBDPTB/x5iJ4IpQiB8dNwKP7OK4dspHAoDwlUcu8cpDpIYUdidLIyk+FzyUZtkbob+z4bdlnaBZuaS6NPtw7wPzcvcK7KiJN/5y0un12bWXuj43xy35VpR5GlZB1UpBi8crM+fcaVILnTi873Sq6ogFKeXniPdmiif9PLFlPmBs0dy0parRVzGWZikoYAHBEiG+8hbZHFlwo/KqIm9SoTyTZ0luRWTyum4fNzIVeCbfQUmX4gi8NPSy3Ih50JL6zPLMMCcn1+WIwXXYPv0fwPTkYok9ZO4KTx8u0O/D+XmwTe+xZl8KRIvL8MySsTK6efOz8LDEnPybaAlmZ21DW13jduubZssSsJctFHlyjwJ31XhMlFbFlGbRmKua+8n+Wac+UjnHZosrptEXDg6flx2jvNrkNDZmfX/Yq/9H3H9elZhkfupgG1YGtE3tNfjmXwl4jqL26JoBTh0WnrOuTXz+ILssjcq91NOPpIm89o8iNVbWCvDJjFsVBvn4yLTkYm6DuI2CDMBK8DVdXgFY/bc2nk3DdhOXmfLtyJtksIL/FREQXjC60Z7FvcCbLlGpF5QFXUOYqkrJYzMB22ZWiSyipd1UIoTJ8oNZa5ymTSp48JvMuFnTUcGffbyPMV+GBShVyuXlY/pydNjzbjBbOmLsgijtigrcVLVq6cd6ciSX+Oxjzp+V9s=
*/