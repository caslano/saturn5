//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_8.hpp
c+CZ+W+s+Tjc/r6zDyv73InnS2c/JV83iw/BVPOxY8yX9iyGdn2dEc+wJIh4q8euxOMH+t2Urg9dkS8UU+oj3nPd/8QX3rD01m6mNN72emP+o6nnyMe1OTzP7XTCtcO3snV+6Dx2+jn833y7+Xm3P+wJvsJ0u1V9O/u7p/Vf4RgY6nhca3SzzOkk2+v4aL7OOpj0qVm46bAf/eUOL3x+9trGkfcnvOTt7tPzD4/59Vl6OrmgZEjrPx/gcTtaUJqIYZ7zrweEdy/iPnVHGPBQt3+94UVi8U2uOboY7Xmkry/fGfInmHPQVZeYx+euU9KTVbcf8uR6iaeTTn1j2E9KtLDF6TO1y+dw0j1NOrZukPj6lKZ97xslWkLP6spNMvq0x+jMTOn44Ihnfjr+fNPEN1Smbs0SzkvYypqypg58Yd168oGzbz5w3lp4iGTzqJv/dvyvuNeMttH33rfvv3X3wNYSZeC/odcV3moOi+JO/5Bu//u7Mwr3znS+xNO+xIlrR1pwRIgy70nfH7cfNuOyse5NxwItvNq8Fq7reuyE870g4wfWm/j0nOrSsxSSE3k+EPq08NX/PezdoeVu786/wzYbp7qT2bW9g83JgcdMcj8IcjMT4vc7Xnv4HpKf2Ry/rx745hWCAkTam67T06JpqR68+bqBNjcpnU0P6WxaHNn0w/A1s+n9D+htWvzPNv0oyI1s6r+XNsXv82zqaXNtCrS5SUn7XWDNJBGvXGVJfdVrph0/i0b9XOL8A8HZlrGUdd8x+F6tiAU4x/hxLtUfvUS/hWtDer/ZD9ZPY/ra+sHFhLFzDPL0xy2Rfvy6kF72Q+p6kA6PW7K1R8HXH7dE+oePQ3p/1BJtOXZDSE9HLYnngwVPOmpJ6V08AXngUUvmO3Hjku/woD+vj21+9SaBJziZHaxvZOv6/ZuG77PM9s8Oh/O4KPP9mwXapPN77/qo4TzqluG7z7yD3YXHD370x68D/Owot8JRWaFo+/mlK/53iprwZ+cYNIvPEfW+GujVSBhKbFPXnd5dv9C/Kr1R7cJjB3/EQi9R2GjDcKe36/Jn2v+7xoVqSOvXizxg1LSiFqbTOcvG6fmrzoHUtv9Z6LW8sa3ATaZ3GBKn/0Hf2cH2u94A6pOSEFcx0ekbqsj06lLZ9jppoRMTXNeyIUBnnsqxrlg2W4WuxpmacjfLx261H+Yy06tJXtT5ilKn4pLLuk/epf3/QWWsm+8vba5Yo421QWnfZ/z3qhkVJ71fLvQybKwxhAW9Pgv3d9Y3Jv+D2qj3r4Veq5vGtFwFvX1//T+ld8jbO94Q6uWVFYRR1bfRXvXVKR3SigqdtRZcENe1z9hXXnVKU1vaLPQqaZgl2AG9a5e2p7Eu/Oe6+tJCn6hVVTNZp7oaatdVVSwU75oBnRhpXRnaEolCjzSTOnvk/172Wuzs5zOZraQdznuAHomkrLmopUU97lLfwx1Ng+eud9oO15eL7i3ei8x1KcSxwJpQHlV1XXxKw9FQjr/P5QhF1HHMhbAoDGEzrM2ZU+hDToefl2YL3/NLc+gojLHZXPUnYIztTt/8YxLTOH5+/VpX5Fm7Znsv7kXQ68zjO/KvAg4aF+IaduvYlXmT5jSX2L8e5J8xJTteen1Iz5TEc8T964c8XAt3ydb8VbK1/bDY8AEVtrJ6/efrwz1zTVRVV+1Vn3eGB79CBsf3gPIx56wzGktWmz7edPHm+kNy3mXS8Bq3xCF/YB3ZwXsXp152LRBXzkhKJPO6J5uj+5KPzHU/jEuimKFV0B3ZYx6IYpzEoiLCYI7Wp6Ev7m4lXfDvo3k5/3jJxtbR7jO6lmhnrbG/fRny/cY3u/kdh3wfZTs=
*/