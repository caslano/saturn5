//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_13_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_13_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_13.hpp
EdncxZVtwEiQeOt81d0c3oDlD+ML7855euikN3bvgbjeC6I4XnJPg1Vht+8gHYv3cnhnaG9s7707WOeOyLscjrmVdMHer7gP4/TW14n7djjmqhrsH1F7vh/jsbqK5b2fc0gP2fYNNofqKNolvD/hWj290WljcLJKHYUmfP8DXRwGZeofPunirBOGZJBdVg/0cbt+IfY+iPHYiVUsK8Zhp1WprB7cx1lge0t/6eXwMnjdQ4jDT55S3/f4g/2c1XP60Q5lCrLbz/r4cP0UvloC1x4TH9rlsruPpt49jHh0opPiLB/u4oMNy+rxj+hwe8vq4CO7PLesxh7V5bhl9bMup1NWVx7d5bhldXm8y3HL6vZDHc5/LauXHO7wNyyrFx/pcHvLanGCeKqfUR0i9WWjRwnXcSD2PhsDMWsNJpy5bei1fuBF+a3ObfH7HdNXiyyMkzKMvf556FmZEXsqqtLIfFi/jekrRdWGTRZ7wQb6ls531Z0Uet/nx3JMEcM14pr8NrauvSzQ+5zy547KTv4LZdc6tSLPubD31LYZXJ38fsH0UA3WpTchDn4UJMFEYJX3gbF+jjw5cJbiAl++hjdgcT3R2OVXm5kvzDxP4ziIQjEDnnmVWaXguVW0DmyKWL40v+yPMF/Bgefnhd/WQs7bF6QPzKPrKytSBbymgb5VfXM3nMVdiCKOysj3CzErP5Usy5dcN04Apv8vTEcq6iKvfK8qxHDuZ7vjPKrc9Q/lPSO/99e2fCISLy4br22F/Op5Rl5wAifF0i+xPhqF0XuHzd0tW74UZRxWUejXAnoiO0ZJXTFxChZnLNKoiVovDgV0TTpCmIbNn5k/i1HKOGNzdo3JtyKtg7TJk1TL452bjVQZPS+x9QSBCLygKItUQK+sZeHtsiUpPvTMrDqpJx1VUzoh/b+ZOsTSE4mi9QI/9BsxtwR1QMasCxL6jOH5LZT9qGOLpG2rtPYjW3aVn/3Csr8cjLCyy8rGj8MqE8rsQxfOsklABVJPrGhDHvXNepzFnYmkaYOijRItD/VuXckvLIEHbXjWz5TFc0wa/uHUn6JJkrr2QiH94kOsID4jSwLOOykrDDUII7/vNzz/bRmXVdoGrvzaYMYSJ3+0E0w+FE2YRG1b1ra8lJxbtKRN3CWTjUTo1WFYtaEry6OmuOecuIO2jryoKhz5eTvjvvEbO7eJ2T6NKz8NA0+Qrd2mh7Y3Ol7M4i9EVYZ1FEW5WFpenn8OOPFWdzm7NUjqMHl4nWN/v2zbOM1rgS9C6aaETZns914mm4g4CusqCEOhhnSdfNRDfQf2nUw+EFFbtEXmV1L+vJSY4xWP9zu/fZMlWwk/CqM6bUMSpQKbN/G94SmbWHlFgecHbZUwId28F5UwpfW6m9agKr2kKlGWuh3sr46ZffvfWrKtaAqvrrPUF+rQvR53z62ZLFpt47fcvnnbtn5TxEK+m7SyBildOrMkTSwfr5a+uMm+Rn6Cyaeihs4hbyMpPwCH6U86qr7NQyFJK8OHKN43jVzi9oqrIG7CumS+nnm9OmDyvGzH3YikLvM0zmtxVo6GemiC/qVjq+UpK85GVHHq+17eSDlMLZM7bNqCjI+dm238MMsLKUeDqNt3vILZxxdNmKZR2CQgRMXJ4jvgm7rLZHNRNkXaNk0khnIgxqu/1X5j4zOe6WhEWSZNUReVkGYFoWWZbDjOviyXCsrcMKcgW2Nfsu93PC1tEhRJkXhCn2nUFhj64mAtmeYik46OuAgaP21KR8f8WaaDt+eTTEcoqqot8ypIxfDMpFYBZoHufChtyu99T7PKvRV5mqR5GgnpIv6sfHAH6wzrfy6x+BIRe5mfl21DUnLv3Do=
*/