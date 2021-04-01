//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_3_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_3_HPP

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


/* rational_horner3_3.hpp
5YAj7gW5N2ynW1Q2nx71UnjtC0sjshamJyL/F36AUrnOd07dX4lBl40GPbSJuoxdZElVeBbHXvi0mHFsGfWLuddKxBeGOWT3s9U9jPiY8uUX8RTiBEJO9FpGEADm25q5ImH8XWxfxUZW+TcMq17MEBEAJachmFtvjKVsZwPgqeHkp3Nyf0pO4SeKzlH/ra64u+7iJ2asHkg4OkmIZQ2Dv47dPK/Xdc7s3/UoHtxAx1L8B2Rz6aG3LvFY8VIPwPvXCQaFwJBCg8zS5nMFz70Y7QoDli4pDO0kmaqHBQWFx6K6M/9CZSzgWTZFOQyHVEBNRsQ2CzQmfCVt8YZNFd1KEw+6UABmMcxvRviUiJavtLft68r8+15d0vStc1HWyNJT1UoDYmeo7NVl2EKKHJ+GJYwcssdtN6VmDeZSYjPPG/XZmEPWPIDI1vXEsZHMlFD51tnCnJbR2y72C4f+ae27fApTCS52SzVq2eQfBjgZE18JicIcoOVnGOLNebULg16CjBVsfWZ+TEmryn9RWBiDN7pDIdRMUB5G7USQ0lcT3gT2jCRfe07ImxO9Pg==
*/