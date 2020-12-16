//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_16_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_16_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_16.hpp
ddC2rff/3b8Hu5/8AeiTdXB4gATL9hUqHOsmmB2xD3IMTIDYDYbJLFhyB39oY/OzNvZMGzuiy1ljtzNMR2jJfpThEClhf2EYRErYI37k6j2E2KkONqlsVj1IzpcUBuaCbp3qlAwcubfdpi3spIsdscb4Dsbr+e4tiLO0ot9QhjMboY4rvZxJ8o0wijizFb6hiDizM+I/6uJgIMTDrQ4OWbT3sbo4ZIGtpxkOybP30lwckmf7A1I41HM+D3/mGIQzu5pGh5xP7nQ5uNrBdvu23YzTaddTd2T4ubNgHatPeMRtDAcU45+7SwfrpFHc1eLwbos4dwcOs29HzxvuYXFY90V5/eC9LA5mlXScuo+F826M+vtrpn3xefne72M4m5enGM7n5S/G8PlZO/yyrecQhf/IDp+k9hnKseI+WH/4PPp1DAN9hN1ADNPM5g6E8fjexDA+/x7ZYmN8/n1SYTqNvGzQV7LCWVUm/EfbCafyJ3xiJ+FUzakdje5GnM3fT91Bh7M6Q/Vb3Mng3Xn5lT0aY3WF5odX860wPwwWZwI4XgkxHzlsvWv6+mv2nmIiwiQoPK+55e9npo6USp85zUnj0D8eCUXTOeVJb9BCmlW5oSz20e0mhjF5fAtccTq4sQjyyq29PHq3xZTVtl4e2I+9Af7JHf08Kikqxyu7iOvMe2SJEGYJ037G98Cuah4NtZf2MyhctyCSeS9hUDsw/DqFQ41TvoEaeXc48E5MDT0Q8znk/ZTtMW7y7YAYi5/2DhGnuO6J71gzDNJH/nwUhvF1+tmTo4jzlmivtbcRh1oV4e0Y4dRyqKwu7TQ4lUZtzoJ/j9/5jeMs8cvypt8CxjcszDzrG6APD07TGs/Mtb7Zhx9C/FQvPon4q3rwdWuf5ZMMh0Uen0P+o4ODSQkf/1YHX7HTP9fBef4udXCevysdnOdv5NsuzvM3wXBYBPP8LXZwnr/XdXCev6sdnOdv9DsuzvM32cF5/pY7OM/f67/jli/P35c7OM/f2HddHPI3/M4zp/qFKirLzDN9A4SfkuFwwmjK88toGlzRUX8N4+x+3ba5zYnzXsZhdqH3nEY34si/7G8wG/Im6Zs84zA7IifcShxeF4jzBuLw+oAcGDuIw8uEOHO9HJ7/T/Zyuvl/xPY+Hs//7b0cnv/f9nJ4/tuxPg7P/2XGYX0K+WLe0cfh+V/v5XTz//UNeZPsLccuh+f/db0cnv9/MA7r72hdtAs4iPd+A5q4A+P0r53u5HImu2uO21xON66Ld2EcmecuZ/GuNocNmTQu393m4LiIOl5yD4azCendzFjydeWbcEHVBit8/BsmHAZ0Cp/T4aDN5l8y4VA64MdC9klrsk/y42EvdU/L5/f9cX+S7/8vIobx0h4/YhgHzYk2Ewbpsud4qwobxuXO8cSoxtikhWSntmmcrI/YxJjG0OrWO8s7NEYWx7NDH4UyZvu/kDD4bkbOjB+GvpFtrsS6XHrvSv48cEO91IbhG/EDmU7Oq815y6/z72FBGhRp6d/y2RQzL37550GfiROW/TTevQ8xSDdgcJKK8N8SfvxwD37gqqUbcYr7JOJqaGB7da+4auvm2AeZXo7dYDr5nuLBL1iYuzfIML6neDvDZhn2URc7ZO0LutiktS/4RYZB90r7gl+0887z8CqG8Tx8kmE8D//gOhk2/iWGsTzMMYzn4RLDeB6uIIZDGmIjX7YxnocJhvE8LDKM5+F1DON5uMownofRrzCM5WHyK3YZPWf2jIUtf8XOO8dez3Ry7MtM54X1gYWNfdWW49jjv8rqC9O5+lU7LRx7A9PJsa9/1W3fhO3+mtu2h75x7y/lz8lDsoeOTa+b8eQVcjw=
*/