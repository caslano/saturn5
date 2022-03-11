//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[9] * x2 + a[7];
   t[1] = a[8] * x2 + a[6];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[10] * x2 + a[8]);
   t[1] = static_cast<V>(a[9] * x2 + a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[11] * x2 + a[9];
   t[1] = a[10] * x2 + a[8];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[7]);
   t[1] += static_cast<V>(a[6]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[12] * x2 + a[10]);
   t[1] = static_cast<V>(a[11] * x2 + a[9]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[8]);
   t[1] += static_cast<V>(a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[13] * x2 + a[11];
   t[1] = a[12] * x2 + a[10];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[9]);
   t[1] += static_cast<V>(a[8]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[7]);
   t[1] += static_cast<V>(a[6]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[14] * x2 + a[12]);
   t[1] = static_cast<V>(a[13] * x2 + a[11]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[10]);
   t[1] += static_cast<V>(a[9]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[8]);
   t[1] += static_cast<V>(a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[15] * x2 + a[13];
   t[1] = a[14] * x2 + a[12];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[11]);
   t[1] += static_cast<V>(a[10]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[9]);
   t[1] += static_cast<V>(a[8]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[7]);
   t[1] += static_cast<V>(a[6]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_16.hpp
pH1+0n4/tHNQKM44vPD9a3poaw0KtKtm2zp447r0RWy3K3nME5dtSks0RlP43UG0SUoqdeKQgxUp/J58F8kD7H8FUiKYihIWLtVTkhvV6eEZCtVRqLu9KCqNkAdllav1aqMsBho9lnzaiXbupIuk12bpr12q64XrK87xythky89CgqL4UKEfYKAre8HLB4DjjnQYXbUYCAAIiAgS8uKn09IPW6aTBMJdrT6nJt26rlW9g4Haywxy32EFpkiScQnu4SSkXlqL3jyRsaykcvqFfVr2lJKWg4qvo/uHJMx5IIwmrIXKd4Mft6kqm4qMgZrk6fJD7frufcKBs8Eqx0Q+o8pkZ/pX0KaYiNObE/QeMuptb+HSvsdANyBzS+ODgOAFyp06gmIhIrLivrdN+YJeMLxU5w6s1DrtwgzaQe0HQ1Q/ikqjOYlSt8/u3L90bbN5HHcNmDPb3cH0fHuCL5UiG1aVCyzWnq3/vui/43bHHc8QXAa6wakos/rkBaqwg0A01VAEyTa4Mat1AoN+SPlGV8LeYSBbNE7m0EqsxZSRWpPi7NWgYDZ3etANJZv5R+EuPsM7cECFpeflczC8EO6fvlFvZEaR2coWkoSGv889t6PlKnjiCqMCosy9lN3ASanDFUOzLb6jk9au4wdwrBWpz5YMC8MM49ODCfmCv6y4gMGuJ5Q34XHwX0BnFKZnT7c56ivA4G2T1YJf9x8d7mMPyFXqINl9sHwNudgwy8iY56IO+vDSu3xmrBu8dlmJe1nmF46Gza4KfgW4JtaEIO4ozEvCwp5Eiz7T2S60342dtY6xTU3H3MnU3xswM1UCcMU7rjCJKhJEbHUwK1H06woGqXC6vau9By9eSHSmr2RKv4/huCmpemMsOr87EoCwyQKZZpjU6mBBoMFBDItEDE9xKQm9KGR4emLLgk3v01u+R/zdGZYsKRRoCurquozqNF39RjJiFi4leUt7Iys0dNUwsV9WsdLFQkn7kUvimlGdu9psoio0olQ310C/u0SxSEhdPiZB+6zbfd4ay/9UTNHgrastrZgPKnncreLJqJ9DNchbyMjISRMPOxNRFPaX1VWT6mWuo2Q+4gjg/zqoJV+2YKRWVHERBS+bPfxb3iYmbT+DR4NOoa1dn56WbT5JC4rp03c+Mhni+a5dKl8CG+558BOEJFeZZHe56ZKZwqKewwzPDpXEbRmkq1beTvLSzMoFZV0DLobjrr9vNfQrRZh3qKpv10wPIUGEYWlBRIVJiztL2T+XO4FS2rHj1vRk44muF4TzvL3YpaZav+ix+SrRxJ9RwfsSMb11cbWV6Pi+uHqwQAchG347yOLUmKPV7s9kmZW4PFBHR85Uv9DcbXEHKzhvnOnPtsOY7+l/1TOT9rGN1wR0/x0mqYmHAS0djnnfUArf/3FnwGQ8EmZGSjoqn3FTAxvlwNPR3IF7qH2i+FsqvZtd2V5zME6H/Ig2/wd5+Rltsc/4+Xe1p3qEjk7rQq6joMoZyVpcEg8MvMys1GdUpSzZ2QUvxuFXVMR7+WY12FqaPkXf9jlVKB0KyzHL3NpUXB/Ukb8SEuVimcJkdWHZPt6VYZnOcIYzZIF+yIezUoz+mTgPuFO2X6zxALY8XQHXmTRKWRNn3uke9W8lhbonql90WMa7s3/AjGtxq8be689w31lpe4Nwm4Y827f57CunGGZllIacUENCS0uDMLx9hpSzMcEtt5vnoJo0mWj2GXwOXU+SHN+E1CwdJ15ZbZG7P6/d/FAN6YpBCaFXSjyGXFABKIJJnYZFfk/68sf2cG5C8d0awPlRL7pNnJmYTxltMnUVfSw6k0OQdeUst8CblMF2D5eWDbOclLexkBRuZfLs3ZoZePy9GS4wlfkIT1rONZpqo6K7g4W9idZsOunpjQg7Np0V/61BaWh87EO7lnn2RxQWO+719cKu7szO13k+TCdH3y4yMVxchwpysc+9fXeUjhHQ3t6WA7HHMITJLvjTfgazqU32x2vlbx1gdEHB2syyAk8s3tSw+R20P+wlo0JyOPt1LcijMjw2mXWV2dUJgO8q+bGBx3XDkrVU+ppLPVXUAVSwmv7WnflglGNKzrLrijBdvGyt8mJhKA9FpQjD32wN4d01/PO0y3QnajLZ/qfLkm/3cHEGt+FmosItdpOTRmcTo0zOqKjy5S3DdatMsPvsj6xNH3DO6PE/kmR1ietHjN4/AWXxbTzdrHjtmCpkU1Rjl04tSUyYjnZcvEXfoPhPmaoTrBRX7nFY0gLpEojeSQ3gbxoAmW3lhxd78Ka2LY+f2Q5sd977mF3I1j6H8vwyBSBwQDdrG+8Z8bQrQDEu3CCLbKrxwBLvFc78OibpBnIXhwAnZC9P2Zcm2TqyLLAVs6uP7yp35noOhCe73yWv4PFAsI7lqmdomcjb/0W11/B1EYcxfXH5kBU4+8+o48jopiEo22bDu8xehwdWV3YPc1f+5cXLtiQjbScnW8htUHqFD3rbBjDcrNm2IDGFuRnUm9TVy2iVjEtEeu4n62zMaSFuKfZoWsynZwy+eAp0LbiNnlq2QqXbWgH2XrZzLvFIk0U2JkN7ly0lURkQhcvWvh+OYUBX+YfOtttq/FneMovkpOJs3mBg1PMq+Wxn2RHMIJeZcTIMq+h1MLYEDlDaDr6N6516JrYxNqduNlJFYn7SGX12hR27F5Eh5QD+8C59lq+eYEvwkEf1/MJL084HVJaK7wZ+cpWj7MHWTW7qjrzaXxs0vIiOvh1taeXRZ/YfXnM+Qh8Ju1NHt07I7o7Ll2fHYsw+Qsyu095QTPOWzFwtQEk/l7bjaF9udxMl/w9Lcm+vlTpIm+dHXvGg8Cm+Mt6c2/3Vo1IkzKPDYblQ7JH3u5/Mj1M4xUldOxivYmu+Bj19a9FLv+qnbA8aMk2fm0pRCiq/b/H2Hy+B+h6kIQyeiwIfffJnyZ+5o2wFFlX8U+RsYaJRKDvenjeilBF9PfWLvOPjofbztgHH86RMS5sh00vmbp0Cpb8Di+JmA3KrSUb7RYQ0BTLj+mH6HdhsCco8GG5s2rQH5o2LJQb93WwH+/gWEgRzYHBWM1Vq97VhkjPo3tQ2u04DyeBAKvtKamZ8Z2ZWcv2pKbGXB83IHv4Q+keKvYQ9QOiHzoA0f8XkpCVD81QLC1JRmxcE0TLxZCGJe4lI6/AnCBIR/Fls3L5Wov4q0fXrfv0fvy9DQy9tDXBDW4xghKnBDPHA1MpEEm5jELh1mtnSgHpvORM9cVW1c31SapxQzPsc6WMzVle4es+YvqB/tEp0VC0CQ68As8SdyQUxrad6XH756KmXUla8+xjhFOtVttOLIQPoENyUKKlqbNabYvg/35I9+mxWL2TrTdiZIws2yiLMumKhSMDjvdLa7Czvp/3fHEG26vp7bRvdaC50vXdZ0i7UV3J492d45oTM7xl5gtXaC12aFUo7Rf/KsbH6W/GHFzyt6vWSuyPmPgC+d5878zvA9UBee7FmqYXeY2Vky+9LJwiyj2lqLbr2bysqSyuB/jS0gS1+QLRvYFQZY93Ovw8rLH47KL2DXTQBW5hu+hB8r1d++m+OW8qCJfFvLSxb3EswCOhOr8FBFnZFxfLF2X23dj7dj6KUJWp+az90Zc17/0I97X2dITxrHebMmv29ISf4BJ10dUdbelzoTfRVKDP5bupJcXv5qGJLRdv85vVuPn7ZyOwRqn2qF8e9DC5EY1xiMUO/l6QhKG/VG3O/tJZ5dKfFppbsdAISFFimu3ibFWUSDk1EYvR/zBpSaSiHrVFhrJPuxe6rMwwvGenRCYPJcEsls3iJpHZNu3BQSLXm2fyL7O6TukV6Sj6yGdFIxH/eAN33onx98JvaC9/7hLLD2OjigujtArYCi2LE4MtLnvgzyHF2W+UEvp+EQ5wwIO09/NwvGkIdHZZ2eX0HdHUbmvVM/giy1JFC96my5vHBaLb78UumMzNMczYbf0oT+8IDIviMJC7Peb2L14yM/Jbb+HdbLWVYrrL5uZzFVMrUVM8mkXdKChbbDwaVOFpQUB3x1Qz55pzyUdV+doOCFmq1VRPawYQd/syo7ENtzihZ5vnS9hiSBmTE2xlc/A09GBoXkGcETJlrIcgwUWF373AaxnA9YAUkfbWxAYCP+01xUhwQ8KulcAYqtX8uiofdWUULo0gGKQHiW4ClI7vJ74jLTT8lqldfMNelzElFlciY4OiDcbgLTJM8PBRX2NyO0fT36eOR9BqzOlG9e6fHdRnyz1C4VjqXVr6VY2raj4sAACz/0ze4DgxGnxiuObcgWFBgfNYyBudqxn007YtA41KFFFKBnylAwckGBUej72GQjM8p1HsokxOb3qfxEPv42VjlHfWVlfzXrv5XU41RJXJOXfWTNjk7tXD7ck/B34efv91lb6422nt7doVat4uMgIuHIHpsykQ7ZpnyF1X9AC/ywln2WVxqLybDvVhDvnJ/NeDU9lk/iWkj+mn50FtW8KxSzq7C269k33Vc4q5clQbTdKavSN+/6U7jDRUGMfZeZZR6EMzFQeiABHqLpfTd2P4l8wtCeQa9DkWnrAHXVknTxo3cwamDBo7g+g/7Yw9BNsw5KzlDvqHv+WMf7hHK9u2j0KJoaLyNYb61eZQSEipy6ZUfhkWazTtAoTc4ePD+IdKIAcNe/3pfO0JpS7GwkDon1/R/aXvx4KyGrCzSgvHk/J5VfTV58DWhohpPL1YhQOsRQS54OG6iJ7fjorsj5J0VX5BCIeHcW7eXddvMo6QCEiTg6TJmb3n+gtY+qIjX0v25AmIbC+6nIzfGZHCB53dVb7fMrzqP7wmI5OkC4v8JYz3lorJPRtlz0/vXAsLJcycsLbkqoPE751YoMZjfRrgfXXu0J04Ca/7sYHiqHYffAs7VAzi0SxL9BLVk6ZIbK4QRkiwDda/0EAL9ktAePDHfc5Ux4R/RyqrR1snAtLDAwsJVGzn7e2ZJRo0+yY7XfLvbeJTrbAcm8t+bL1s6sWPfaVBMsXGzYvn5RZ9h8kPDzkKLUQ3Um/Xm+ewVtlgxtYfI9af9dga8jbdwsDUw9Zj7zxRUnZvtEC+lPlP/iT7GAvPn8pKDqaYq1trQlbd9bqkUIap7+43rBYN1KhxUj8K6gnwfN4pIoiKQaoTSXCys9nfn8XZdGiZxCLGreLHfvrq1zKsj48FHo73713W9Q0PKWO+X2YshLO87xGsmrV2yVIwzppYih9RoX/MD3qjF/AFkK3TEGIbhFvX0+6x1AMOH1BjzoaYJO5H6lJXJ5TopTQzN7ndm7NOerkCPxO1hqs3n8qXpKMdlNDnv6HVsPvyeuGbOqmzFlFfehd3Vqyk82/DbTBhd/eXXlhgqLfrs+zV/wVB0mz5VuFTOqV0+3ekL3bl+eL8XW+7tnv3mr2Wp+CTZ7YvWLyfvMy7wxWj/SkJx0PUwPy5zKMnGT6jdGHTd3wxjbGzkDuvR9K2KPviJTcMer9UrpLofBNIq7qedIufqMg4GT9vK2df2H/UNsHq3uagyaWG1NhGs0FMbKonZST8p0z4oDxzrpQ3of2r7ALZ9b1Sfut4yskbbr9wB0tAsqOMf/sBIwX4GGub7tj/QAEJfwQdje6G7eIDRzmZlmDVBpNCohXrdUzzh5iZVhOLlVF0+OdB1o3V2j7UOLkHuuDOAweJ+2FhddCQlHT2oGdMD19vG0dR3vJR1UwSXuDT85/Gc9VvYuLtmPAVgWQNcy1JZcl9ZpdGYVtPE5kDuOTRqS7/DYAg/4QCjTk/yLKt5LPbb9xuCTOKpJSclRWpuN7gbBenc4vBwP/j0dFaTYzTpFzS3m/hh+AonkbX+3nf5sLEM+qqXV6q3i1vr6xd/C0R7ATOvETJDCKq9GqpAb7VGAOyabgiblCedfL/eZ1/rl32OlfXYmsVZLB6srgy7YLzH5FJ+/X9ztCaUzeDX4AdfOHJr91jrwW7Oi9N3sdhYdKDDBjVY3IQjyRi6SmL1Aawn275G/kv2tQUoW6+2ZxMnl2vaAYAtZfXtL3ohenGcJ2egQvyWVwaMy59WFkPX3lHu7kD4rxPl7y6uu7s0XJo68ImT199uD0r0ZT/JyLVtXfULsAVc9yZdvxe8Q9eKdVjVBUbIo132JpLsxPxf3D3HGEtISjY5N8Z51nxMSpKpe3vVWAzdHO6YUIrVPF2JjYGNdnd7K0PtTs2PlMgPLHeRjVEZZ4c8TsAmigvo2vPk+AQiBpbQdiOIhwdTv83/SO0GOnfYzNMtZuvy3gKCClGe59VCqGYLh3QC/Ehzpxjh/ycXk14nfTmsmlkaGdot24hl+fjLG3vhnE+7pougZ+ekru3rUhiwJYyJEu7bRAJPAIuDPHnePC0P6pETEuriLKh7AyB2YlOMZtX262ZxVNI7gu30Rul9RbuqxSRJgUgBLPFyRIczPeJ0QnHKKqzL2vIDHJ4smscUrS07zIfLgL3qi11GnVH/85+wNsM6q4HMHySD2cepamHJpdkipB7+ReQw8T4+8RwnKERYOEUfQMan71IxNjz9ciftm5NKQeXKpdiKYUycVlVNegI/WCcYzEvf7Js+nMq9eq8eHj0BBq3qyKnM61FlCWN3fs4ywPO5wGPXF9p25We+/PESB98DnI6h+dP///UnKojWrkOPuhCL5zoBY4+cGfl5gofoMe/uwYAb2icQhMgfRjDQIK9PXacetoeUbRbh0HOgB0fBT53/UAFsYbe898eY1y8o8TeaIwJW+LDz1MQvy/OOlzI6l1vm+7K5fdyPpSujnke9rrcMUkp+3kg5sByPG/APBDH4dGs5TsLNpAtBQMqT8106cCNyyff1hH/LA3Ey7G74SS9Hx3n3bRGVXC0OuiyBhICvdXiNOciViHQvzO6XiwN/cLlP73wMo6S9v2i997Bnn2hii4AXiMsb8c4aGUBFd/iSv28A2qIF9tJTGf/QcFzI9Ub54MY9yck7u4a7g3Nq5NjJ5PjxeNcbGezMr0NGdDnxn3+2v036fD0Lxq6XpjLrKEVHobO/zTxpdeJu3sqy7qk7M2N9KcAh8yRJUOK2t12bJbpDzdh0naqEC6rDd3otjZONhlXJlFYopDNgl6H89mnF24W118nLjJ7p5XmmXa9MtS5JNvrNbLR0B15c7d/BgxFdLU3z5xqU8dTM+uoZORxXErJzlso209oU6ozyVVxhPtQvqniKK5DWj7jEqwXpbPmj3yq5sv78VzhIJlOhb0BGxshytdu2JUCICI3oPt7+5uYvBNehAuFB30B6LOtsygPiZEj38DBcPKjyK+qggPF3s52j8qQlOT/yHp+974pKqxnonLvWPJ889rdDhE90S0AnOyE6KChvaEwUMOZ8sVGYiL6OD3lqTcQilKCfNCI3dNoGwyC5WmZy+I2KR92GZcTZy223Rk1OLXMeszZE9kaCQQDGG3eDKh3oA8sQyQrYHuzVVn5s+qWsz4WFJn+3WtOoRYGwtibV8hbT5tH//1yv6+Tw6pK+8SQKNfSDtQ+CJgAQHksdKA+3xUL3S+L2CaT/sDo90y9dWahd1s3vqctFWTlVOjTy6tb9Ln8G8NLw4+mZFvs+rlTEvrQz22gx2bfk1iGRA4/4hFgadAIPmZZm/Nf5JuiTCcm/Ffc1k5nn5UVnysrgw5pR8I+4gyGvJNXyFC8rA0ZTiE+X+8ifXs/fVtZlfjty7OfgHs/gvtrl7DodvdmCRpZjMsgA71ObAnJsZXQ4WrwMFqfu1YRNmHvQX14E/+0t5+Xcsmvc+9gZWWxZEv/9oKcLntFic47/f7+v9TPbha79EpJjYwBQCNDPQ+obh3mIhm+L9wXEJvCF/kxSF0x6OV0z6C/26DCePU7KhUtrbX0O37qZ3wuXqXBu9opLG7jGoIWz8vIF80XTGHVYQv32128ei+nOw5y2b9NzyVGbsJMUIG4NxBEF4EeZnqhBOLn+38fzL19kuyzb05zafJ2Fh04a88A6q7bfIv6VfzXrJdWvaxQWU0I/iPc3T0/WWXzCi1VES9h8k3riBSfH+qsEM6s4FCC8h9TsmVSkSeFysEVuYVtdm04btbjGE4k5AUegx+Ejs5+pZ7c1MyrJ65j/AqA7jHqPvmXJmRYzyq7j+3MycJ2SUTxxtTFRzRMfn4eo2KZ0dP0k1hvDc/SJ/9uXsyXO9fwCzk61LDbcjxJu+cu1fLN42oE7aOdGKkdpl8d8r68T//hVzYOc+h5w4e9gnY/Ah/lRWAQAbL+ncwGhFraDWjpr98f3hSTQ4de4yx0Arey9rpbGKVEQIX/UPeFOaUNVgegGP7A/q4p66N1/42nX5GX7vFxnUxz//2s/0LrYP7UHQCD2oD/+C0/oxfrvXHf4O/3g/auc/0SutICP/1Gzz/8I/1Y/f0n94f5TgsMv9L8Bf/s/5YMfM7H//itP4i7/Dv+n/wY+8P4EVfP/nkt/kev4p9P4altj8vJgnQBP4QDU6P+I4e7/6Fab32zwJt+8jl2xk9f+2QeE80OvmTL+H88xoM32PbheRO5QaKO85f4iyAg42H8p01HP/dRizLZf/wK9rVeoQxJ4+g1+eKgeNHcfZdmCg6Pwae183Bb8rpv3gs/0n9oPcdI24FBvzUNtYhqg/NP6hr2/NXcTZWWb81aplKaOponXA9KehCljP4uWo4FzOb9znBMNy20du7EN7sgsOX57bTM/kP+a+NFXZFOrS6mwEKp5i94eO7ZdXsPLZ4613lCjYYbQ2/fM7d+xsc6z9jTgfLm+OjEm9TPUSc3faTy9V3IB6+WaL6VhisOETmmbEPaR/fMTO/3OUiCIxRcMTa7bv5dJnzm9As8hy9VdXGbO+9rH3uUdhpUqyMjmVqAMSioiE/wVresw/KD4JC78kr1/6RVby2JrFs1BrlIFHDpYKdJdPo7YHsnJR8GDShWFyhF9Bt4Y52Ob2ea9T/xTPYXF2NV9XSlXe+gEC/YvRBUqVSNNPZinZIAkWP65t/25pXZPElbm5u+Ebzf9a5Un6ck05ciCgPNmkPnn/W4McvaHjvTJBKWdrWGrsaNBYwD/eStPg1p+X7j8RTvfWYy58O9NuUdDUW3uUXsfgA5MPLhDvQywvPwWtYFG/lblPL0iUGH/fpySY+cAnld993mlS0yyXMbfu4WLZcCkT+mXBo2ghjGBxH82T9BJ1ZJMZ82xD9Y=
*/