//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_2.hpp
r5TlUVJMNCYanJ81v65p2+W5V5bFhHK25VD1RVlPpexrSSTeYnHcDy3jLypnW1eyZPwqTuubISVFM+4uxp3O8EovybhyD3qpu2VceZ7gNZlXMMOV/jYyfm3pz5X+JX7aZ4p3VLBVyEDWwfpiPeW5zJec2i5jQoJSr/LGVGu9Di3hcyBtd2i36aa6fh9df6Udd97mUwl51MVxH7fSRiqZNcl6qVlmuufNrFu7dl21ldFsnGpg
*/