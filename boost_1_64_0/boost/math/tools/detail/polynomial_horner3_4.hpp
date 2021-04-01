//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_4_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_4_HPP

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


/* polynomial_horner3_4.hpp
aeKlAuXUjAjCEFKkFAvFpz9ladppyG5gKsCK1cmWJ6BiYH5ncCJnhSJy8MifNC6fecNP27vOwZTWrGHVhj9hu5IHDgPsenP3x1bI7YNFoyvO1VBvr38QwqbR9suZyVWMv8tqgwte8wGVpdi7/G4edtVpqxPJKb//3Eev4uGocdwHf1eZV5YUZFq4/7PzaFtELp70sDAplOPSe8rjHlFHw1M1HtMWVsYXsfGgKPIKCGSSdOnR5ocN3MMh86ZB7cXCNXl6QKqLCLAm5sNg74zLqHE+2GYLk4YXHK2lOf77sM31/Vez8vchy7NiIzldO//y8lMudeQgIcIHtQ4YUeN0ui5RSHaE00QKWLMiB6XoACXBPErM7BQGG54+SFbOAQ9vvG3KT4knAlyYe+t2VP7RJw5oJ3XZVIlYdn0RSL1V9tkIZM6k4YBHXK+NyLSh4c/J4NAYxlEZlO0JVZt/Feq90LRTA3BPrygGudsP3mvJohLbS1QBQNGCns32kB8MBSRYlX3yKA5FonAArbBqUPkm1dT2mXlMl9UdvBv0h5utwU6SzNbjgKWU8NsLwg==
*/