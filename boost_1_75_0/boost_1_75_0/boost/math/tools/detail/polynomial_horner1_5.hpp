//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_5_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_5_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_5.hpp
QqsPkK0jIJVn2dpuLz8sAMi+YJ5lXLtdOpnvk0svqh0jGng6TfrB4R9BTjCR9r+WgkzDzWeWipcZr1+0XgFU1AD96QEGKI/6B2x4PkbzDBgPPqnkfupJNfd4luxgPS3GKzLck2XrB6VYcFZB9izRnYL4o15mQN/U+IGfn0gU0I3XEu/wX6uZuGLUMRzahDD3RKJq+kfvQonkx2Oe+m1+/JclHfPjadf9b/x4V2vn+PHh08bwOI0s1u/mk0qs30d4rN+drZHaTOTeNz5XbN6lqQJqN9Ipt2lYsPlZ8kTfYM4fto980Xh/nJ3dkyqNynTmBN1peL1HJvk+b0zNk+rtu5vx8i/PJ5Sfdkh5l5kFdx78pAoYV3lsWsvVqHkbwZBoGQzqmgP9Sd3n5Zxj8ABOdsfNA9x+lxVsMfYJ2rvUgh2zZelTGJ6y5Qnar7jQnLcaeIyvzQN69EK8aoHsDRFtkgsx/HKi6F9ibkkVc1xmTHvMwD39Hng+5p66elSGmPPxKnsGrklY8ppBzcqv2MfW9PyiuSVFzJllxisS8DEVrQURA/VKowBPdvYMAMXTRRLwTk1PsmEIXXwJknFkGrxIU14Arxhpw2oB3pwDGNMZ4zuPzeace3a2ys3JknB3ka3/9uDK0OxMgV2TAizul+9Am7XkX33G0xO3HZLHJyT3EoSW+PxhbfbVtdF7HG1KAAV9LG40JU6hJTQaa33l
*/