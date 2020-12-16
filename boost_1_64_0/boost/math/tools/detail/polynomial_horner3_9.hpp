//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_9_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_9_HPP

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
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[8] * x2 + a[6]);
   t[1] = static_cast<V>(a[7] * x2 + a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_9.hpp
XofhmcY7vUvyoMA08aZmD3n29sCbrjfV/U2+ntPKOn4HwHsbMuj3bcLdwP0fh38a/wN3vha/vmLyv7WnB79l3hfAN7y68w07eHyHqzcfCqy/d3kvwaXGFSquM/fRcNCM6gRVbp3DhxztP0/fz+AqCtp1/m0fcjqMQbQxffgBkmdea0bORcUx3RtiXVx9IOdc572sN41y7nXcs1L3gvcjv9NnEvLKMeR1vT8seO6BXjyVtMrr5Djn3sB9rav/k0/vqV/C75Vxpxi/K1PGd8V17bjIbuC9fPFd0e3CP9zf3eDJHD/mBoDb8/Os4rz3UC8edn3J/dsmg9s5Rqj6uSDrh7o9JPec9/j0nkViW04eRjd8z0L/7n6kv5dLUuR9q5/wTCM/xQuHCM8sLrlffUH5cavPtYds2EXU7t709+LUZp5WyyO3D7lTg9fiFnascYc3XIvbOql/Kz65kXKFg2uRU03PNhk8GGKqUUilj75kN3dyRYT4zd3SnYNFR+7RrT24mDR+c7f14s7yY5YWtuMtJG99hdYSLffk9h48zCreW9/Rg4tZVdw33RK5PVoJ713cmnDNVsJ62om8Hq2Evphug1yjplR8n71tNw4puuIO7erOxaIjl90eud1bCd8buHA//b0BP7YTOygjtrY4R9fvn7yfYR9oJ0mZZCXjY6CnFqyWsfzFd9sv6/I5c+M0iOzUYnXtVpgQWlR3Cx5G191xkltxJgxvu65EDPtLXf6QbxeRA0meaC9JIrlhMCv3RUOd/yAnzyy3KBPJp+fOUyRvAct4ZThp4UPeOlc+dP/1ebrseJxHoR0EIZuDzT7zjPo1JJ2UJZGfeyVPsPftVRmHqofzehyTuZs7YVny9A6PQyZVPdSVjZbOdyyWpmlRRkEEaV7Lka15N+Sq0X6lV1qR7ZY0716HBqj2fzjdM7KtPIhDUcddbgSbNqGTRN5iQWYFXhklUPJVJa4EnybrPCVyBfOCIEhShyZr+gw2zjsaehwpS3M/5TkPGKZbCah+eErnH7CDKPW4UrD1E8u0Tp79cGNPMY7C0g9cttatPpsd70mdI/IJ87M49ZPEbFqzS1nKP74uX8BRYBiHSchOdGrgimyHSyRNh2W2l0WJBzpsON6m/eQXutxEHgZZCF5/+BJmcc60y7lK0vBZboe8VvJEptGtTFJ222Fap0Xg2kUSQJncOmzCk6GNtse9iWzCErt0CisFHe3hKYmWMTxMzsWszA+ztAA1AfcfdDyb0rmTTpk6pWMlwH20/g7arLLvNcrlpX6Zp7mHYxTJmJTHcyJd/mAWu7FrhwH0Hli10XI8m3CToiziIE+BCyautBzPI2UO8tDhbWsBt1qdynwsyrjP0nxkaeZGVhU3nshJ7jmdO+G4SWDFZRX3qopZ2bsdpnpZREUQFN1sUel+4gVdrqzMph0vjLS+3SnzdSqThUlc+pbH1sjmAf3G/OIw1ekiTMs4tApWN5YNmBxT92QYPTOJnTxOrAw2Zxtr/G2jWS4Nn6emYQO4ixl9tfpmFm7nfQ16TjhqpJfnnu8UQcrM1YjRBq6RXpEXruukducdE1qfj2f0PdYg8uHpzeXp2Y45yF71jiDT5wNh6KV5nrpsmruZ16qij41J/df5GfNtv3SjEI4sUESmIdvsecy0K8rCPPMc1tWhPW3vNzHa3mUelU4cM+2Ewiyckv0kM+5fWFEQ5E7EqDN3TFR/i4TWpetGWVyEHnSapnJsaZzl/YnRb6vj+Fac2j4I1YmaUL0ctmjfiZ24sIsSxOY6tQTldlskPRC0Yy8EOdEbiCBT56REzmM5r9GwLGIQnMbm6KqboWXotJc6/N8EZGWbdOsLjzfy6jk=
*/