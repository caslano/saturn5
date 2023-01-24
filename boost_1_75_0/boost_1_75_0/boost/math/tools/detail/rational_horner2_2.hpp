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


/* rational_horner2_2.hpp
jvEYtQHjcXU3jMcO3TAeT3bFeDz0IcbjuA8xHtd2wXgc3QXjsfGHGI/bnsV4ND2L8XgtHOPxk3CMx0XhFdpcLya4sbm2hf2/aXM52S5/XSzHdjEI5dou3cdVZLt0PfOobJcJb1dsuwzsXbbt8srYimyXtNOPxHbZ8Vb5totjzMPZLpvcpPfEdnGcpwbJY81k2+USO3++WWnb5TC71b6ZR+NDV3sRLt71pYe2ys7TZdgqnwO3zv3Cna3SKwvbKkKWaqvUJcf2Od7UDgjKemS2ytZFxFb56n6JJ7bKO4tcbJVkcsF+oQrN49xFiq0ybVFZtoqrL3PgV5LEfJnjZF/m95e5+jK7plnyrWuaCRWm0f3smqZThWnSbrimqVJhmuxbrmlOveGahsfuW/anr8bxe1WI3Yd8pMVLGaelIn3OLF3GH16WziDHp5X4fTbtkdXMIMvICTCGzQpOqWbMmhUsGdbU515oJ+1DlU/yJlJALT3yUgjt5xyTOcjVR/C7nthHsDha/CtadGAfQZKQdDrjs8G/LTAQTAxnD0GX8IpAmvYzS2l4RRoNx6iLtrWc/yK4AJKerRBov7Kd9G1tWp9ecAm4/TM6VEEj3Cxih+B5XpcdQoSbtXSEwkSSazuxQ4hwc5KORtAIN8nsECLcNGaHxmjreKFI0j73lhKr8TGSjeLRvhoUsHEuuBvCBhCZUspYCIxPfQVP94PtdvLN
*/