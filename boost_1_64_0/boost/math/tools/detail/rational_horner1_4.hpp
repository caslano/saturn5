//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_4_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_4_HPP

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
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_4.hpp
YDKvRXApZWG4L6PhvJlqrgNucDG13pXYoOnx+wzb6lLutsNz8XysYPB0YjfPh4XJdTXMQK+vAzAbg8nqRTp72jd7WdkZxYYxysTFNtY6Y99feQH5BOxfHwRw1MCNCSe7gKBmZ0OBSEJbmmD5snuPKE1FxUU2UgPvuzXIn4QpWIXz/sIxK/GHVOAieT1o7yUJebMLxOBxcP6GQU36XE2o8O04M4Ww6U2fHLsz9ZTSKDRu+hmwDos+5t6Mf6OrcrncWy/RV8Hh4i7vnrvEwKNGrKQFbGjyM024t4u0SOinp7cnkoLtIKZb4Bltv7X+9I8/HqKUjyYajyox7O7ZQ9MFuIHMQC6HoUgoJpE6BMrEoOsPIil7Q56jZmmR2fPm6mklvU8yynefcVE1pZGghVfcW04mDUb8eKeo4mPq2i7oXSX0slDZ1lNGGy9USNYLAZzqQVyOkCjkPY5OO2WWyo60HK2ZNkQ/yhCCxuLfTOQjzawlw5FIzXF+i7me13Voi53MOkprf4r4h5wRT54ocpRI6yhJoIBGXFCZzl2RdywBw65N4HEOtvba4s3bRg==
*/