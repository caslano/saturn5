//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_4_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_4_HPP

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


/* rational_horner2_4.hpp
MdwzppCMEN1wQfAPAuKd17rDDrxF3xDA92oJUyE0BD+2IIzc46AIvx5zaHVQFMGK8rAezwGeEpEwgqtW6UJ1oeq6xp2sr4mID0wgCrvfS1MOWjHn40W6yZfreNyJrNMs51N6fr79qKx9lW501DgVMzJ4IqHyY4ZuuBd0ujpANzXIKqDrV9btHxTt9RVpiRde2XDBxHuPJYbG2WALWyesm/CzOhyzjtjC+hDDF7cR21Jak4cdmYih+OdqPn55zDbL9DliD0WBDX2+4TcRi8jsWUvwkwF+/kH/A1BLAwQKAAAACAAtZ0pSfE7wrH4CAACkEQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDExMTJVVAUAAbZIJGDtmM1um0AQx+8r+R1GrqKeHGJHbaNog5rGRLXqBgQ4VnKJNrAUZNhBu+u4fvsOa1JbfYNKnJYZZn7zcfsPt9LYTBjpM16pAunZyP0OdW58dp9GCQui5JHFQRozWzUSt5bd3y6Wqzhg3DuGcu+QzT5AIvWb1BNT5ZJxLdt675M3JF+NIgeDjQRjhcqFzoFKgJamRWWkAYvQiI0EW8oGTInaSg0UCYUw9EkYihBvWOWwI0+lfkHXFBmVMwrUXS7kwgpoSxqrS6Bi2jJuXF9Z
*/