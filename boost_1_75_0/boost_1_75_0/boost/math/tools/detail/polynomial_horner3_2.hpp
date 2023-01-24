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
q8T94XttbOOWW5nKCh42FJ0vDdLTNoSQD0QL5CMYJh/BwmtHScgcNMD8AuPLF3vlr/G3UNsQvjyJd8R0NIrIfvJOsSW+sVk0/abUbU9swAqEGvK8W2hXaJo7LbgNTvp+jK0RaqHYXhfaEB0syMuguzkk70/jlI/egr1sgRBNOF21Abw47XbVfcb811auditVS6Ttw8zxbaVens+s6GbevJtR37dV11V6NOLNw0VwZTAB3/LNpJ/0yR8gAf4xyeyOMs2HbW1KUTwO5eY2UXO7Mro31/jr/9BcUI5sRsF9sWjuCWbkNhHi6kFrbtXAeKtOEB9hfNNi4Jt1GcbEvpbOqpMxqDW5BOYy/D3UmlyW+B/C3QyjTk39m3ze+xKpTPp5XyKFiZ1DauOuC1AzxziOFzZzOQXaJdylWD2wzCEEnbmbkZ3Q0BEFN+QQgG8mGB0dI3TUbjAgGjpqM6Gjd9PFa0JHLqTqhWUbIaSbyJ9fJYS0WUug6qY4H5UqCRymz2ecBA3PTRANDszv8s08iAYqT9ByCom8krkN4SqcaH69iV6T8H4u96OBxQebOIYMvvClk47VVYuRXHdiWBcdCD4l2dMMaDXxgYXt7TEojKgfhrIJ+dvnUZnahkivE2BjkMZbDAUCY5NFAAegsZmbOKIMPvXXHXWtuSRdA8etfHZsNXRBdq1TQ62mPdDBvKEWDAcaL/glS2868aPfktk4
*/