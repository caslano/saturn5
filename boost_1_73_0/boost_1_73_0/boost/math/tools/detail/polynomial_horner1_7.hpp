//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_7.hpp
GZYlN5BeZx/SLPkMDz+KSNyWJbYjQcjg+cD00QnsO9oNNRmkSRr9SztK+SaJOa28GhUWS9LOZlAaF/AcVBxajiF8JdnQ1kQiEtNpOyJ33YBH2nmLFdTebYEaFKHvHFSA7jbsDIGrISCRthtQFvC1NbrU1LOA713Utotl/Z8dz4GNHKzK5WgdO3pndIc0OFr2BxYM1WaiIWpZfjxCbtUWB6+HEpzbKNJ7BHKAtuqgam2QpXLQQl667VbZasiWSTmZL9bF4zKbdGmWi1UhX5QlmSYfbyD2ELPBXPMUxZ8jFuM+odf1YTBJ1cSOdA12WwYNe/OMaOEiNI4uRL7vtZyg9Y5c6cxM8KLBm2rHnYnE3AXK4D+ySLwd8Je4n/0vtiO+3TAST3bnjZw83a/Wj4ufxw3K4FJedlPN5bl0Lk888vxX/AVQSwMECgAAAAgALWdKUqAYTYjrAQAASAMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDU5VVQFAAG2SCRgZVNRj5pAEH7fhP8wuYvpy9GF5mxyZGNirFdNPTWK977CIKSwS3YXPf99B9DTti/A7M58833fDMKhdYm0OGKiUJmm1288n7RJ7YjN4njdPWCyWi6nk5jVRn+cXaMUluyVLl/H
*/