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
mhfaO+fFjR6E4NulAtnY8jmdGm7LEbf8G/c2gLyg8+Uh9THfAL8Jl3KCKYH/29RXCQXBI4z6OXM3mZNrzNklA54M/8MR/4MjnY8yonP3oqmPcmF6OVMnNsAEh9cmA61LTF+EEBVsxJ0W0Ds5CvZ39zw9KzlkUo1KWWlR3ECm5Mh9XlOhB7CcrPvMMAUbUdcJokSORqxIHVZI6dopfqJn3XDNgHQ7vZhOOZ2yQltNwDsH7wRMcStlheC5CTUK1ErGygYGufU+lzfUjM4UGRFxF3dIr+Ebh0RxlAH0QFSObJ/jJswCvnOZgK9EMZFDnr4ikU2ywPXV5vU2HiHSI7FphjeDkQn7TCGsqTMzXwwX4a+5EtnMOg1YprmyqPYIG7AKmfAC6tVA6jqJJjbXaKKVKNvk+5uF/jEOPoTRONeiZEpTo4Fneh788O5dbzfXjYSuOiqV1DKReZuYoxB+He7Csmhe1DKEB1rUyFf0gnd4g/hoNJw4Xbv+2Ls661zWyGGS8BKX1+n6Q5NuB/5y8XHm0JfjImVq1vKeuJo82093G/7O3u6WMfpTuavZCw7HokLDioUz7wg4hc2zblo7kz0HhDGthTBjfA4AY7z6gTX3HPG+ZVfV0PxW0zJnojCcHrPzn/D0vNqKyZ4+Wl/s
*/