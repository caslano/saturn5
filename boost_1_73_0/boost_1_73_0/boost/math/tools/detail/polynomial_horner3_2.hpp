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
g2Sk8T3S0w6Y4Z2MZUAoA3a9tlzAg/ItXN5eIUBHAlhtu44bEUNcUHr2cVNW6/ziDH2DK0Wchi5osaoKmi5fw6ICbb/RMWY8yGGB2X9FYo3SEkKCt7M/yFlGPtnfHjIV5lvlMELwC11P7WHbn+WgmgOEeQBvvByQlRBmDy138FVKAzPXWj8jbB/ZOFs/qB641rDnWgm4V0Y4sM04DSwSVjkavuUe6t2goeYGnDQCJxpcM3IXya34kc5f/Jz/50ruYtjtY7p9PB5tz/9ujMxLNIJ2Y17WD9bb2uqM3JSrAmu15tDZnUtI/r4sAVV6J7/zrtfyHAeOp7dXCUGRgq6jEdQarSBZEi8ipM9fzZf4Yr55unyTkOpLvoJ1Em8ooDYJub5ZVwlWcqqAjfL8Q7UJYnQSgNHTz/EEUEsDBAoAAAAIAC1nSlJDWHx66wEAALcFAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA4MFVUBQABtkgkYO1UUWvbMBB+F/g/HBkhUHCVdDBGcDNKKUshLCFx+1QYnnyJTR1dkC51w+h/31lOk0Bh9KkPY8bYlnX6vu++Oylh9GwyjyOVlHZJ8nrEXU0u9yM1TtNZeMD3m1Q5zEuHhn9uXaWWVFVUV2QyLsmq
*/