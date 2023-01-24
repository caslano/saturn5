//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_5.hpp
rloK1I2pK1TP8wW0SqNF0jR48nt6EsnzyeUZ9Ege6O061PWW6llf4NA+++sIEbZiUpUmE+6gRV72fUAn05wFA+XyLJ88McNb0ISFfHK62V0YiuLEIrBPLUAaFYhK3MF6wLfwUwQF1ZhfRSR+v3+6KaRy0YEQUSL4UbKSNXwaFz4Od8S2NMLD0/PKAO3ib3GQ3B0xlWSQglrFbaNKHZZ5PjQuYBEUTBC9pTSVhbrjsPJb6ksN4SZ1xI8udljMfsDs4X5wmknGK+LL00rcqTFM6M3uRbuJZoqwody92W6JDQMA3MLZXfxbYLudcxyPzX0coqdevKiHF+knTC9axYtWzEv7qenFIfECWEfP+UZVMrIpoS20GZZp7NoiZteAqXHCrgjKk93EUYbYsTVUzxCM4YSKSX/BNaP+Yq2pyYdyLGGJuPNGOFna8evLmAoAPsYT+ZSpAOJKGwE1DiDUMg5ZqRxKGB9qNG0CqOEQ1jCLa+iUD/LH8GEQmsoFzJvaVIHeVGVnb+0AcpyR27MdMRm0S6FUBgxy3RbB09FkwY4YFISDIH6DkzVjVdqroOxvRSuMIQF6fU4ANjMRzPpbtIbn3p0XQMXOLq1BeC+4KyymjdXTo5DWRH9ogqp3m/uVgkG2dOfMeBOxAKBwo51jdgs9UA956WlApc8yKj1niga+QDX5HwLWX/4bBxk6DdUt8aNfzNz7fPJXpO6S5Lq1
*/