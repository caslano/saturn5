//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_5.hpp
Gp4ftS3WXNR2PnZf2ueXn9zbELEfWcO7glhRrJjNsTeGdcGArWp4XkmMrQkjc97tXCU+IUv7MVp6CLuNUoxiiC14914iy7HX+/dDyDDevbiG4x1vHcccNcbAOc5LYZ5SyXEjHVC9c7HXHe+i5zKLlglHnVTI1o+N8SF24h0+mHYlcNViB7Jtszxze38us0SMtdJJXz9No1aG+hnnaDD9rsK4bkSTA0z3nwn3ED5eFz7IVEtMTAywF2Y7q+md9KUYnw5iEY5l5WoC68A29LH9dV2+cRHmAdKiYUq11CEt7V2IYfbinHIY646L4ry6ZQ231pUV3/e/o3dO7pjLOkRtJZhxuI+pBy2NfmUFnpatahxrR3hx0ZH8L6gofKEEq7DT1djeYQ4NsZ9WYCuMmTbYjLD3hggbaf/vUMBY6tgJoyqT9m3TfbfN6F8mirUdY6bCZmzrpenF896Zq7xD/GaIqTTjxknRY4I7aRejvyPAdEg0tMZOVOP8PQwvjKzEZ8eWzw0+BesxhgHE17LhRBiXbD48GK1RflzgO1vrum2a/46/3E8rUkzCE00x7zQNlsRidPHAXwjY2tv3MfCzXFiJexENTINkXUX5D3nQnxTEPEhpEEUaasUwl20L0xByAqbhKUUaCCFWiKr572kY58OLizQI5kRT1RakId2AWxnq35uAHEM1EY3AoioGluXgubq9H/uG58R7yQUuqSiVNVMAN9b81E4/CuQ48jKitryEDTsc4Z2pEe73C1xqCabO1AVub2+KX/hnINcgihtFFG9L4O5W+HQrnMAO2A8bsE+2EFsTKWtHYJ1L+yokvovVlrGmTc0pbUrs1ZXVsL0yOkN5JJAnyDHZ4FYJRLbW/f+n/YTPV5DnPPTMQ5ZGsqsFNpfOYTGGphn0ILtT4EpqJDZKhncBN2a4+wVu8p9tYX7jWjqjZYnbPysZsdO7PC2IyaBa5ZRto8Ux9kB8C7Et9p29oYTVpgSkjycr/X5sXr+qGGMQ4FpdCy10NBjO8b7dFnsuVrZKtu18zOm+n15OMtAq7tdL2JeqtuFCVOhwZ3phkh5+TO8USDi3VLo22nEKJ2ax7c7dY3+IhLFbDHPENO3sOhrPURcmAy4CuBJR05q2UbbE9U4vR2G3UK1fM+mH+BQnQYKY35bUzlgcYMNzQY/l5Zt+OxKWq2WyxlqxEvPSDrvs439vCn8JI77UkeXxqwEuFlbY1rGQxR7XvzFf3pd5syziSevatVxgiBsrsNjO3vOP6x2A2baVkcS3gH2fP41kxXsZAK9FqlVUaiogXjcd8OMBeAsV8WF8LfPK4ZYzW88g/byne7JgMsQIZ5d9nd5NobCq+Ca4Ku68EGJsS+oyLZNdf2mAgIdhYXx3ldvvnBDYYoG80LPX9ysyesfynCri2+u2biot5+b5+HGbCg/jqyricVeKVA2rETn0ri4P3Q+u7LOTmSdULu5iw/dPnq+Ks0puBHe0LP/Q2z9+fedoZPubcvllzhuNCVW97U9YdWU9f1uR54ZXlZWsKvF8W972zu7e8q519clOZfdxVbxdyWsiBaO97a6wvX8mJN1EjO+cFelRjFeMqysUxWPDWw3pqQH/K8YN0MVeLXastZVGXScxWdnyjiL9xVfQHh6gYRmqyjGu3Sg7uus5vjo7/1xE6eOgdLGPTqylhKGVFdHftk3zGj7UHV3kn6hbVTejcu/fBR55asV5WWG3sKpmvHGZ3f3rHzDf3wzkLCKM2cpgCvH7f/aXk0Ii+oqQ/B+g7bWrNW2kmNmeAXvWS3gY+3TxZo9obdMaVmLHO6Wre8+YFLEIfg9xtbPeANF4s/3J/t7RYWnvgoF9Vi25bklZ0fo=
*/