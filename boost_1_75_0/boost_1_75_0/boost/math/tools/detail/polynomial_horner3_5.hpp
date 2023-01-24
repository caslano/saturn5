//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_5.hpp
rxPD91etH8j0NRHTZwBdv6BuK85MGudPJP+fw8IQpSKlo8xGAXhu4veG/bcL61L0utYFS+A8xEifwbwa1VODxZN9/Rikjc2/ODICn8Hs+8M2KlAL5xnXTmI8hjH/CR+1o2ACkIZ4jK1pgYz4ZgpzEBarxkEsKwzJs4t1qxNBWbx7E9OXtlvIOOTMzfQz9DabRbG3qiq+6ncbPXPcphOpz94kuKK2m/nrZDX/flBNRd8Rt69XMzGlxVgU4Yg3MsN0V5oejjggNwZZpxGrVDErG4kV77ES/d7FqUjbkTNWmm5AkQyT5TO7zIQ97Sa/VWcd0inqp76NijRbSeQ/TFvoQv7imAVo+7NtH0neytsHLnj7wAVvH7jgU5JiqGiSsFjkGG2eetw7SDQi4WDsHP9gsWtIKHUswDqisZnIlx230jr3Y7G9gwMr3Cr1zNjlEnxKUYddG7LOuwzv0HmXgTjaqe4AevJxzN73J5PuAlfB8CG6eJa+uq9V8eoNmsW//WYxL2yfxb7U3dR6AK+2DRZTqoqvYBHbo3MboQcXwIAarcyGYcYI0lPxyBQhbjrN6PZ3G8jiolVZiIw9FO/E8SjMAXYCk9Yqyu9n1q0TZX4DkI36xRt2C6kEKCkKhc7krzB05j82aHxjzRJM1yfD05hDY9cOmXi4Tu1hp/4wuryVXHYxgP7eN1ggI3JW8HD6k2t8ixamMTaJNZLV3bSR
*/