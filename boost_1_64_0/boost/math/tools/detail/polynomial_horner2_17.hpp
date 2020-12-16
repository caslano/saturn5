//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_17_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_17_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_17.hpp
8aITMKDgmvdno7L9u/2e7cdvK+GUJ75Xy3EoU2t+wXGa7vL92i5n0jpPhDhrh3Q+c7uL8/3g1Q7+HJaHKx18hckfHOvg/Jsi4qyM0AbXGM76aNQhdhCH6hzhr0Oc9Tf0TnoXZ3mc2univJwud/BuOe3Z5XJ4OS27uFNOn3Rxp5wO7HZxXk4XXdwpp2+7uFNOk3dwcV5Or+rg3XK6gRzWZyLe3rGDszy8zcWdchi7k4t3y2HR5Tjl8FEXd8ph/x4X5+XwYhd3yuHrLu6Uw8RtLs7L4XYXd8rhegfvlkN5Z+JQP0xz+zcpfGbDvfEX70V89kzPHvW77s5wtr9941421v3mceU+Ng4vmHXjf9N+5PTuzU8+0MInu/ieB1l4j/6fPVjjfHlE++wHDT4/2yv/MI1D2ffg+x/JcPJ9bs7HMJzb732Hbaxrv9snCOf2I/3iMZpD8mS74wZb6c3bt5/A8E7aX/9EhrO0X/ZsrBv3+wLEe8vl9kjj7NMd4RdShne+Ha7nBr+w3meXl5QMZ2l/Zm1hqJq+54gWcClzbEKis7iW2f15fs6g9L26irJbPmdg9AlbX1iIsvKDNGj+16Uk7YZJ/X5GjPA3YB+k+oJQUdjdjy0c675Z5OLd+yPhNs7B88r4VgDH+f0RWM9y3L0/8u2dBq9Cdrabxs0u7qTx5B04Rxc9zQ/uyHA8G44+he/EcDwXjucO9jAc7//Uxqfk5+w6UokoadOsKOpbrSO4nwprcxkf3hFCX8XEmdzscrr+iq+7nK4fYlzbv24L53I/w6QzHd2IN7dimuRhM//diItnF80roZSOd23lMo4PYtR9attGvAHXbdls33ZXpus3+PaxPs6g12Yv39HPdW22vrOXx2yGfqN3ca7j+5fyv7uf17Ut+QK+cIcNZLgDdvLVf0fO5z6GKX9zd9qARw7bKd17+rndcqO7SRft9jUZ+F5dRpkvZGs68qTj8sS4vmiE/FfZ/ONFkHpFnqWaDztVWuBhxs+GzT+WBUFZNGErho9TDbme4V5l3DTJSr/KJVe9YoVc6psfskk3fH1/aVm/zTfQ7+cZvS/+jKV3Iojays9rX4TRiZMme8h9CeM2WZW0ZZELuJyB3AebO9c290hQe4XMWwx6FRV5r+M8r/WTMFI6FQ/jvsziLoI2LsqyBn1HOul8L+O2ZVQmdZKCTuKijwCbW4m8SODC6TChx6Mwkv8JfNefE5dJUy+u0qZQiT4uj9zI/8yedmT+YsvUok2yNMqrEOM5QhGhzNgVJpMEeRwFXoXxHKGIsA5O2jLHw8aLo8iPh3k/Lqc3xu+KsVVr8yeaNC2rqm5FFkaezgHVwZOMG5SRHzRFKuCwJHJNuS4zbtZ4tVdX4kQUhbz8L17h5e+HmRcE4inBYc57CeOVWVIleVvBrXSe/5fbvMdUSRuUbe0r3nG5pNPppPy/4Qprg3HqJ0WRDvnHJngdfB/jNkGep2VVD7kT4zy9V2zu4TrOwjytPOHH2v6Gd5Xx0iwq2jgLxOkFzTP5+rLNmwyq0G/L0BOnpX+7BXl/sZOv68z+ZeyVfp0XAo5nGK4w3BuMm+ZSd9sEAg4uIBffEWPpyMqyDss4H+o9Lpd9WgDTPfZZmx9mQdmkXqJ0Mz76u7P5lQjzOmiqVPm7g+KjKmy199SWOVZnQZMEUS686ASW+CrWd8712yb1mxTUE9ekZZmnpfKqrGiTUpGPH+5PyyuY/qDJoyQOAkgLiPC0vIpz0yhKk6wy6nlaLvO0xEURF0EbAFkuxPvTcpXpj/04bZOigrSACE/L1zk3y9Im9lA9T8sNnpYmbIrCqyNhvvGDJd1+dvRzTCbyotqLUg9d/fXJHOQ=
*/