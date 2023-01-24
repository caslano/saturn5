//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_7.hpp
H2nQ9410kFeFDZBmsk8wBkQ5Wj8ewnQhS1D0HfMDzYoGaCu99dhbMvJ7g2gUDlVYkjUu0qU2Sk8G41daAvGMQYHSRtfq55HcnX3Gu+oM9vehS9GE9z4HKsChx8BhjId+tmA/W6Ro5wmlgjrZKcUxgWIB2ml3tUuwM10PP0fZsSa7Vc8rF6GwESFxkoR6uxrqZ50KvBEm20X4CzJIrnEF0ZgvnJcfn5AusWHrmVyHxTQMTGalBi9Ui3Yl+5keB+XTlJPrbdMAvSVZvshJHKEEI5S0EZIF4uwzYoBX4gB/aBcDvEgbYB+pXltlGuf8t842zn1WbZzvjNDGGUod53U9xxmSX0kd5uCewzwZvLCrxzA/C9V94qrdkTLMoN8S+bLHOH/dc5zP2P7TOFcePts42SMfx/lFnjbO61LHOaq3cb6aOs5Rwx0WxNS7pAvb4LiyhOSWAIrdNw8l4i+ZRXFdh6qeR/LYevd4ksIjDNzOYdraVM/TUDR6yhbJwYM7nh35yGERgqi7hgoKErlCp1S0V1n5M8T3sOFl2PAybPj4XLeGsGc2bxuU5lipuGH19/Clzbj8ykY8goHPpVhNTjC2MJcNmINkLIJY7SHEaj9AyXH6+cTYC7+2Q6rnq3NhUW9inQzGdfvnuVjgICCZE6rnXVhxrzz4hY8zUfDXjCM7dxg8itnhzivPyEBO2jnMYRH2hpQsD5bFGxuXgd6D
*/