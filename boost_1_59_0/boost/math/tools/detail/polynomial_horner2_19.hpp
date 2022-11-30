//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_19_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_19_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_19.hpp
dMAxnSEdl6oBZTFBNAcpQi8P8wadMk5Cnxujdapnc+tMPF51u4GMe2ZMqkF6xW29pX6Z0dfRnUQY3wMSvR3aPbUdFeo1TsTu9CJ4yGSNkej8lC+3sz9P3kEPXBBi9NnBxtBd8RcaV0VdBB9ELps66uOzBYtBzdXWRZSx7apJVrPR8MQmXqDklfLmffHyiN8lh8OebFSWfzalSRdtb5ZUahdfS629n78hfsPtYKWEdZujAixbc4uUr0nGiRlC+X07EGpHhFAnzNjVRAo1+8oV/Yht2VJSiwoPXMTov6yJcWmAe5Yb9eDeXMQUXBKs0QpxPM9XRS5Vb4C5sbnbsAwSSk/F4H5W1tNhpU9IU0yphkV2gnnAWJyqOYVEVYdcxAOq3o3VVVevc+XLANmp2+7rPi5rKnurtra2GQKqAg1JAEVIw/RPMDOsKmYYZd3GIADFPJTx1n2vxVuhqnfhinXASSlS1ZjkMW1vJBLYymXWBaDcTG0Fi6UtDQ0OifHrGV60tVVm/PetQiD1x3yckMlVp7kNGsG992IS5v3gI4vFC1VxeOv85cC7um3ICJJdK3K77cr7je///qR9GXvLYBygpWQ1ms0fZ+U3W0ZDVrlzxhXu6eSXc7lN2tzojtfx5PStqDCWfizn3qXeAddKqcakcBleW6iiMX3YDyRUonxPqwF6Ph7EYnQ6CbQ7DG0JRIdq874yYtix/vCtPouMFOh58R37JB+brqlFuoTctYjnYj5OINcpeQHQeYy0rvK/TLj6uFqsIHOwq7fiHh+XagcSmikMzXzLicJHxIcvw1qNK0QaxaZnKD9JEbmN7JO4Y3qyQ+nHi6/Q4iPp1Bj30L8j1FRxVSdT7mrZu/Od6Ns3mAZinko2G+DWAfER+DQHaGkVN+t8Ocq4jaBIRWxf8jSQDJT2bKkfxDQJ23f5TaZOVb3iAUnCaU9/HbJ7vaXgEmnY7AbEEtEu/qtEz26rvO9l7g2fT4tHxhPACZNO+CeGkIznesiSKoXYFAbKJ+iGB7JAs4m0mN1/8s5HC6bO1heFjvntctLPYx0gT0vxm0zx0dPXn66rxHBVc81VRvDsp7NHFoGOkD3TLeUGV5q/2HpCgvU9gESMFakueExjjE2s3mHvMh5dTummVT7iKyx30z4IXHbb9juYKqh5v0kQLoibXZvjg28fsnA9GXmW8WOt4HcSvWrIsty1AkaOZ+g4Il8jL/FQ/MZ6fdK4ZcRHtfTPMc0ef69JBFssjseVTEWwy3FdW5/xEjO2Dvj+IraqpaXs0/Ht8dPQt5WyZPk8GhqVrfuTuu2QGfleZGz8bVuBZIgWFAbmIGnxq61WMI928jvQJ+UH0SN2OiVGxGTZbpRheCVX3nEEW018hj1ZnOuUgv6kQ90kYeN9sRu6E2MvQgpttLwXHNrar4k3lyaiGOKLVs7cL6HYS3jLQivqV2+pO20PAwmqoiFx0XECcmsc+4kfyWb9Yq1VS6pEvDIeacJYEEMQLbGjQkGhotxd37Pz8LNc/Ez/bH4iwCXu6mGh/K5dr7OfXIuAiZxywRr5Dd7hLLVjDKJrytI6IFS44BME7krQ7x1TUTSWIm7vTv3bGUHx+w0MygllVt36vmRi0FFJPCzY0QWsrZ+AXD5BUimgJuA1qz3a0rgImx6WX91tKnk7O1hLVapGWMpKYfTRd/BO2Gm9sguPsVWsD5k+Z76TWvfYe3Er5c92N4hp3t4Op9w9PjwyqkqCIwFdW/7Nxwei92FK2llts882qRwXNFzrI97XslHPe/i57Qg04MSBXSoHx/KP8HZOnOSzRuD1fDY7Nsy451cyV378DNm9fPTKnWvJVfexD6byHtK4T2HiUKIPSljHLlx8x1n8JzaVheeUI3ZOGAbdr/+TPvx1Ki3+Gr9dj4WWih6wW5WMuxuZQ5ck/SZegqCPBYYRx0PHvOYDT9tpcJ0lZ/9ClaMxeitqdB7PO3apSOk6MTQ/QyaoKY9KXf7nGiM4vT+IIT2LgKd3kL9FhiTfKeLCi2WSF5DD7R/meVlH+rKR6jVrx7dVUjlF2l196msLPb3R/PLRjVF6wWhYEThZvNHOvoUwFLn1stj4bPdvl9w/tjcZHiqrdDKbJ856f+K+VnSgl7t5Ye1j5YNKBIQD/vIOlBvD8LjcjKV1/B7/NTOi62PnkCdfhH7WlZXPhD3Q3QKHibv3cRzeGVkvcdZ3c3kI/NQDsQu/3UPS3c49f4pLF0xMCTDDSGVqeJ7cuVjp5bE2D7KQkAORkPzUI8A9kVC/nwef9IWJQ392159/6D1y6vtfk2XkyZpt7Pv/Os7bDlg75JpAPy3wSmXEl7Wfq3lxD7OxgJxlSlh8y0ccbYwvtLSz3Q82dk9KUmSEWCJps3KDpqofgR6RKMq9QqV+yuaYbAHgw0DEH6KZSVa0TKD9RBYM71Am0uLGi8uHUsGDw6+626Oj7nVuXtpeZKf+26NI6bt3GYzR7rbP6XPy6cGMCje0EIBa+64PXMQko58KE2SoSwqy9cVeO74MAGTKW+FrGjpUMZAGtcf6NNQhk0wGup5CgGrE1gpU4+peWNcXx7lF5CM2fb2w6G1U9u+nom6Tcwm5Y+Sk5FyozuQ9KaNEyfT2WHI6u/a5zTu6mX0caccryA+fIDV0Q9zJVjcDn7/DvWEM8QKTpWMaJRM7n7DkzE/5m8i2aMva44kqzU9hBOK3L+GB7JaPrpOf/h/mnMWdOfC+eNBko7rGRujRqp3f6mqCstbX/rn7uuVWNe0lvdyVZbPkEovVHy7i52URMlZYR0SUP1QM/EztOSLMS1ujBYhQ6SxcqOwvHCRcShMllJWHS2cZhzhiY427b6iMHW9Cd330UTJ4/LBZLu9r+n7KgRai5nn1dT1JvNlZaltK7cz3tsNABRUS+Qlx5GaRJYUc6iLWARuUotaBETl8VO9RlegfjLLKCirsqxMddouGMVJOum9rLPHESeQ99RQWVYTSO3W253HCTQI8/OGJBpJHvYvJmkActNk/DZ0MCxpfGx1vz4W3Zn9/Ji2Z851+WBLiKxoDOxnWJ1LozcLYAKhECEXnZRea33i7m+E/4BdJZvmp+vxKWlvJLCJQxEllfUrFd5fen95RForfU2dKzwbV7vT4cqF9eEKUIb77VINJTVRWVNlG7tv20Nuc1LqtM9EXu8uZq6B64vH4GeWuCF+FgS1Rahk3MHtWlKPTQkXjTTkAaR9+hiOoYURq70ZWVknxNa5Qn5Q1FwtToHO6x49lwwRBvVHaV1T5pph8yKvm/q/brX98EinzMtLCvCo6K3MW3E3txn+LJ9g6Y+uy8s7p5dPiGPCq/Lk9EulqKjkLlhulgdlHMYLTMT9gWipzZF+PX1vDzUFFN6aGT3+IdxP79OtOfP7dwgxR/bvkKfo/rzd3ogvLzla0WjalqHYNH6vJtlf2eGWVNZP3lN4iL7j11dzIXHslGqZ/3//LAbp0//gX4MCAgODg3L8IB/4HR8D39tf+gx8DAoB/339v4H/k58K/7GgAAAAvEIH9f6n/vtVrwQBAAr+CA2/T//mfYGDhXz+Yvexr/+WBkcC3f/ZfvDO7Bf4dc4cYHhACFf1is7fc2npcTmYhhP0S9zn4lY9qhVqbXQnYj5jaemGuJUD+gG++P6+8vMHUAmxMqBgjzEacShebUwzjqWFSwJ/C47pjD/zaG7uyhghea7Km0169Mc64CAyOOP9Gz3+qL1sv7xosz0Ypbszhi7qHk5Bx9Z2WYN6kok6uuZcJudg9fmE44NLCrW/CAfRNqshgxjh2UKcHkwwhSaMDrsCDiAbS/D3UsnEttadHqNivB6B1NogmVnUKhnF9JMOH0+OZye470UTl7JAyZwPfYAqFVLjFW4E+iZuKc4b+3IDZf897jyN1Pj7Fs07/l7nQFyLqznomGgvrR0aOiU30aBXcSuvk5QcpptlPeaJluH9WwRjVzc8PgAAJO7cfp2YBSs3GyD3nOyJH8ex0N5HzTtXuxx60lJSsld85s93rRuUsGlj59rgc99pR3VrwsMrSMY4OYFq7PCua31jS924oUZ625LqpanwYVyBRjK0sLlHoBJnvdBiq3UfoMPfETjGJkBtc4uOfK43GNybXhowY21mjwisWmppmB9gmNf55VtrurrY66sudlrESDdJK5KQUMqeTdirQxNPLcFTU/pwlo+W6dPQMusjb7reXIsceS9MYD87Kc1wNT9eIDS2utMypoYXF8ww62zBu2czJpVPb+UjJxbeCjZvQV8fcJx01ohmxrBewDkCTCBd2r98zihl4f9hNJrrkxHHlAPv7Sn+nJlcE0MLNcREbY7pV1jdjWXHRWfijke6QuNNg7xOrty7+/Lual0M1D+DOqpO+dhJjoyhzPxjG/m7/x57T525spf1SCxyoNjjqx/UVJxEr6J6kZB0lwu1OGF3Fdejb8Ph60MVWbS33/tqrL/+Z8azIHswqWmri1YLDU3zqMimz61vgbrLWuNm1bHxU+lZY9+pkXCR7n3rooZnXKZMmBba8PKzNpY3SNJXmZOdOaJlNSuZN+A2kMMm6+QzX9F95iDpTFSW9WwBMivbgj5KQLkNi3wJAePtzPrk66b3HZU8jMjS0r9bedydijXnB2elmdgHHp38ZX5qirEZJa+w+8UX1UgmxbtlNJkMjUIxjIrNSoJ/3ETvDgp+fH2PeXnHTc53Hmz8lhunAD5bBf4vb+UR+la8Yjb3Fph/FQ0JzmE9idIPakACwddHuTduiuOfti0idHt46wyoslNBktUL33EEA4EXTg/JOmXOwbBPd1l1q33kEAJPlZ/YDm5tauBNy1rnQZxcpCOJMQJ+ZLxyb3XJ9Axq1W91QRuz+AQDgyvYOBWsiVEbAvPtgAvI/9r9lAix2+bTEmO6q6CMD8FH+oH9alP0jIIDuT4GC/4FS2CAw6A8DUQkJA4qKiJGQCxkREBeYhJgZEieg/5/r2TBQoh994mBvHnypb7gma9+TapFef/DMc1ijRifUb++c9IN91KYX/LjRkQc2WjGdIinMpzCr+pnFLqJGDRoE95IlXpP2XF6h248PeaZb3HWB5jW6dyBlQi8YxXhxqvsHgACAQ0sBAID/f67KGJCs/Uz34YQMAH/Cql8kg63MhBJspjo698Ig9Jy8wHtRPf40p2U5YNY/w/LSW5h8b2m33NzZDhM9+5nKncAoDUlXRb6AvOC9XgxjbiDLURLIbAZEQ3dUB4xucDjPY/KRVipEO2JfcjEl3z0qglyTDxiDZM1EcaoVH19aV7vBuWjUMk32D/NGS76W8ohu5rBByVe249xpmG3ZNrbPtXkHhDJlcnSbpwcTgFDD2RzDU84PFpN9C45Hi15lU/2T4c7l1C2fNx89HD9lD3pl63v/ZJIO+8YuXN3UfNNKjQAALP/TioaCkIk3/5MnPwdniNcfEnta5yjVA3pYXQLiqTK3wERL/M5dl8qEcnG/PMwvyohfdWfTTVKvT79BQRWuc/ofRKMQBes71JkRWuV8p24G4lw5TK2+JSrWzXyeogaxbjLnv3bP1e1vmMvMV7lrlnezFacRBzUZrwP3X6pq1t3NecW36B5CK6l+FFScGJm5yTy+kSI3VqtV+0pWrGUa5dgPak1wKpJpfv96LkV9SkwUzet92ldril1fjnJzUkFRbSKu4bvjQll3vX6KL19sLqxhSAvH4dDE1o8nbwivDoleuiuIJ811GlOtnGLNfVu1/NoljB9Dl05JZv+0cCy3RvR1sgj4qbOFBhLlo1NSoVZ/8JGaca+YJcl48r2flSlO6qfL/j59bjmXx+k+0uSGLO4woqHLbeiVojIxKJg9P608Xi7h51sm6X1af/LleAPGqQL9cFBtBmex2CB7KOxPR8MM2G5hwJipsDc1W0H3fslRigp89AA/3C3Tvc19px7W7nGrTBonQWyIqN2tWKtOqMdLNXNNUc+6ULxddf3g9nPxIMMYUZ9U0ut1gmkYYB7I5tdm71smVPpQDb8eYo+AZ+IsP2gqT6dpwimVXwCtJEcJERHGhaG7j+IT5h8ZPseR5z9NfNWEgI4Y7lXBaECc5XMlvmxxMwzYhC6DGVhWs1chwGTgxsTp2FOX9+3hRdLGMwjAkKceMTrQisRQG/G7YKK0NI5TCq6Pk80unuypjFdKiasStigvdyxklelvCWMesaQQAuXWPw5yEA5tVGfT2Umfs7LLbrLTo7Kmnah7rBE3WVFuMyqDoxe9higeSbbr4FsvgxFyl5ktiRqtrSHVGq1kzgTK7YWGx2sxprZv6bYD9hjFSmzaTWKRCN5MGFJaatRGyTbti6rRswlHrzK+Clycx9heExhYQ7xmgnxygWiUARJKhyKMPkZme2EEWi/8hVUhaUWhhFfJQOLzqY/aT4o9JWRyei2zL6E6UgRpvHXEm9vUBXuGmVCKNFXwgMjQqDTdwuDUH+VAj+1/k6iGNgJNmznzz1xZxlpmCiC8MvJuDHf4u2e1M/m2saDH7djskyPrjAijVCDpPZpqyNUbRHMSdDuLNzc7rf5OFrPQQgUk9cj7VMwX9nYumsfL3WTaA81yI02enFKLjrAGWpxVNDBYlLK5ERwvJasJVbbx9yNuzDwHUwXXai4XB8NTkjrC2WyOIl2ycAfbexUdkeLEhTBLvlEOGJa106EkcbMmJVX+WlA7xYmr3Ai+Er8O8qCGUjSt8HyXteZ9Aekla6A1UCKfzD2tlLbMGOryd3ZPh9vSXZok5tqUlg7p4PaRr2LQID5/WK5YH4bsKjLa57GbeZNJ3EYlfYukxTIgytddyXYU2D9EAQTHWsnIvWd1AqaklXaPFfSm8pGcvraGQ11nv0J0NqMt9ZztNJcVTy2NraM01Q2Cdk8szKfB9Z0Pn6incGWIz4w7G5Og/q6KoYcmRC7mtGCFBv2T/VPlltzWrbeuYTRwv4+fnBNNqshQghfhUBv+AhD5rVDQIg2VICpC4NrZ4nHnpaFO+N8uYufSoDTfa/CkwXYvUfaMmgG7YgOFLhlX2AlVpl8KClNonNHTHcncV6PSYTTWYqgKtaInTbGupen6yMn0XAy5UbUkZQLCz4+T1AXmsV0S1RJsMOyZTjzufmcTIn40FksfH3OBwlHP/TqbvZQhQ3WnDtPuXmxzu/idoncvJXmAvUvMcWze2Xk0sUokz3Z41MNa1Mv4xEbLayD1clzVyO5bksUW0pfTQGb6JtL7DeEvE96PfBIhvABprxo0c5pqf/4M55N3orL0f879sdBcMGgwGP83CtGqvyHmEwTmMBEF/yIh+f2M4G2KoV4OB8kxOHkZiJIiqYYUD9OI+QGQMGExlzcWW+2MqjfZB6P0M3JY2sqxm5B5HwOq/n8W+MEo/yqmRUHgU99QBRoY8ktrpSKk5hpRAqz3UXvermkFLp8mN0t4OMjmAJXgn33+2IkNbhSwgRUYCUz5XFgqkSgiqHekPRsUhuoq18o18dZ90qiuHQsMTOwhUVbqPLVorhcdeNyFTfxOF19+wQy6YV57TfoCNoTKZX/V3trcpaxAX68rjOgEVEnMQktvOb+WP4Gge2/1znJFfDP08BXuRgASKfbiotvSWs2ZSFac12mFOi5S+GyAbIx9hxJmv58xESCq8Bb2IF9v
*/