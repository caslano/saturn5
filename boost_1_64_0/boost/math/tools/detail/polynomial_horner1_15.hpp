//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_15_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_15_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_15.hpp
L/Lr+n8PylOScAp8ks+7jXX5PwTyQtPAtdvI503EuvzfAvnEiOWMbQy0c+VVa/lLj+vlFZHBKDmVf/GqV11dyz8WyAvLsedWVflVf3gmkLekAHTayLfe361fQF5bbUTivsqvyn8lkA/Y2cC0m+TzarS252uBvGc8cKf4Ir+ujwLyUUtMtFNVflWfW0CeExKCt2Ijv7ul/HcAeWkZ1knKKr8q/wjIm+gjjWJT/pWrW/T9ALRnYMZJaxf5dX0+CuQTUcxHRmb53XX5n4D2MXmEJc438te31OfTsHwbjVbOLfLr+nwO2gdrK1Tyk/y1V26pzxdhf2aqhMxmi/y6/K/A/uM5Vdhu7L/z6lety/8G7D/JiaiFWeRb+WR5A5Dlgc8YV6Lkp2y70Zzc6V6JpFY2m++/ODqvRaAao3cow0vObEzqX5dxdVXGEx8Py9AGU6YZ/tdlXFuV8YqhDIPzbGoU+ddl7KzKUEMZzjEurKP/uowHVmXcHsqwJZyJS+xfl/HqVRkfGcooK4/Knf1fl3F9VcanhzKYt55LFf51GburMr4EytCoxNjzUvt/0z/mjGutjO8MZUTpZVI+/JsyXjWW8cuhDB+isxzHf1NGvcuta8MT4FpCTCy9Ix+AVU8EkFvlmVke+G1z7jVWoh4STQdhAHulxpXosQllu8vyfm4OP+z3Tkt2lMGPhwE+hYLJqy+lYRV8uMGBD+Y7AJ7kPkMps1KgfOZ2+M585gYVvbPY9gLgLBIJY6FxrLx6g9+iMKrnun0ZERFnuCFCobj3nqOD7JHG6ZVwY/fq+ly3xz2gXEzWELLJWTtLh+q3AzkEDwIrgweOayuOLwMOxm1kKcgNxywdqk/ENx8MfbiwxRh7hij23DmNhyirGbJfYwYM9pcs6hAVR/v5MPHo6HAPRFuF2Kd+C/IGxrxSIvW8u1cA74PqO66B12PFrYm68rYoohVbY0oMvERTkSvdaIegmNVXeOAk1FstpWmcLTLmWN9LT4RYHgjFXJpG2iLmjtinDlhRwqTbEBtvi5w7Yl8+YItvnmJJQBtv533tgE15FrSBU2jj7bxpwDLPsPCKQyNv5709YGlSWlPPoJ23835gwMpYEruKuOrLYs378QGrQrJcRbPqy+9a835mwPpAY4yeQjtv5/3igA1RyuJ5Au28nfdrA5Ykgz3hDNoZ8taYHas6a5ISh2ZutO0dJMBRxG3E3gTdOMfb6lbfRz4JYjOhtIpus/EK+8IB61gqZ8gY2ng77/UBG2X0kTMCbbydNw3Y3KGUVsJAG2/nvTtgVfEKMlZDI2/n/ciANY7SbCqyxc7XR+ynBqyPjBMv8RY7r7BfGLCy7EqJNtDO23m/NmCZolEkNczL23m/P2BTyVXoCYZ23s77xwFrA2eCRgLtvJ33iU8e5hsuecmyN9o5bhm7lyG26OtzvRvvGAW875MDVquCVBbaeTuvG7CGO6yTD9DO23nfMWCF4FLF5KCdt/NeDFhenglh7qGdIW+9I+mxO2zaLyWK3hgYF8tesubcADwOSWy4DdQsuTpqlqMaUu58dc70hb6MXe9yGZgzdD/fNr7r8Lg60J+JZc/Uy1OOyjSc29PWPWHN91HZaxYV1N05/LAv5wEpubfSTim3bp8fbkjfWePFAD0NijimSLyafJTzfrd/EJMmt60Jf1G/IZ8yfCMkklceTaaLvJ3Je32nJiV6ZdnW7t+Y93/3F71f0ZdBKdLYK+1M24PrTV1yea022Yez1KfX+1ZfzjVJrfNKMnT6nv11vpC3ZVkQawobabGKfZycbbGlLwAuIE6UoZz+W3VzTS0d3jN9CpRjEfeBe8p01Rk6G7SadLFWv9SXcZUGKgM=
*/