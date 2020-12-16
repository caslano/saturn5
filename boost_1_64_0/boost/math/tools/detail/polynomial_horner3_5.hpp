//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_5.hpp
WdIWyjy47FiGcVpgPzdlT3UuL87U9hs4aBvWR22HenH8UvGWxXGjBXC2jg+O30fgvzHDMXxuqEAgjN9JTu2aY5kkpcb/gOkUhTq3NCcIkBDAIY5/S5wm05tdhMOKkvMzydEBiASaMQHnV5KT1DfdnYX2adEapudLtUcFZbb5ET1OUHvslK1L6pKHHkHyUafwQeL7w8V3MWMCZJRAL309lzbQzXt5faQMw1ldmYXUAVPFAWk8KXGozgtiYiIFItO4S3LMDjAk63USMFJfWAoVNBIZzwY7n97iwoqORtcbLVMMqo5re2NaKQ/iiiRP4zpSTM8BDGsKXPk25ftvOj0UA/lfH9P5mV7qrsLgTbIE8odlHJ6ceFXJQd3uM+pWfYcyGHoE6SckYgjTs8vbaBdPvU27WHo2tIte/E+U4dhpdnQ9Xe7MLy7pyobwpweHL490QPi98nm6DIeLNdSzxMsHdhne39CNvjTc1wOUF2DNu7axkac83eL5402Sp9UdyK86pyMxuaLR98JH8TtOAYavha0SV6ky/X9vt7De5TkxHGMeV3Y2cpZk0eAd8Ts18yAwldbX7tWcujfK1Gp8z10JrmYgnZf5u0lclxyWz557SExOber73+6pvoPBH8vt9/c2v7eW5QSl8aH7KXx1QdUG2au9v8RVIo1y9Y9QDEM3/L4eBU7PB/pMrx2j7WOixi712r2GNb5yTOG12gr+V4Xqh+uS649Q+EVhHMaKMNdn8aMUp1uP0PBOg0wueEKhb+ufAC5oDbBAWRVzK65T9zwWMOhZgwat3smYccn//u35eOZNynzvJMrQAQ3CxjytsUE8HSau7xzJpZMUBKjjPeD2czAwDGu7J3ng/FUcAc7xqj+e2fJNDsSC9flhgvXLviUwcBm70qOWng56lJ1COBKGZ3rGzmqOVnu6NR2IyGONvCfUjQKYirfrR1p3wykA7IqqHUoe/2EDT/ZPpaO+6BeaA+20Ue8ZV/n4sebaNOXFEb7WnjgepnTpHw2WgXYu7TstnZ6PWzqzo5xKYQY192ODuJDJ2qOB1unHPqW5c9NdHTX6ztU4jL9zbSNx5/X9q0+RsoKAdPhLnyYYBALFcEm3k5aqW1JnUP3ntX8qom+nLPYLLy3c9Z/RBn3bumP4ZRgH7WZi+m4aBg5tvkbecQ7d0MCDSgevX1086/aekUG8S70KGUKuv2kQF0ZLYCP3T01c6jpUc9+xuYFLG6g+f/PK0QYu1KDkysEYy3RrAx+oBufn2/s5app6kD4DNpCD85E623YnyYWVnkqYUTdTdzVwAV9aguO/l8SdaKFfClyHczfCkwQM57f7Cb4irDnTy0hEu9BBxYNCNTLQNezV99YcLPguxvW8QxI3C7vXL8nd3PhBwGsawjCsbz6EcOzhUJf50MMJr3EoGlf6zBhw1zXU6fnv+0eoDBSJqkzdRiSXH5NcrFNhF5ki/p+vPcLgtMR0KtR6URtQFZrzk+MGR+ptkqPn0dFHAUfrM5d6N0/9mjtknl0+oXiYxbaBf+kxCu+26ye35LtMKi0HTyJOXaliXZ1xgDNwutFh3XA1Dygia6pSjfL2gDNwVQGzvNaTrvi35CqdQvOfF2h+82IeQjf4E+Ft+DIGlfaxSPLpEEBs5druTrjNutJU3MhRNnPN85NGnkwd8iZS4Cmdx8mj6lSjHf/D/TySLp7146hhYR7jvJ9n2/snij4OnrVWbbAknKmpU4n7+CmyB4F6HeFCioz92srAtDTKXiM45Bgxn5sY5AKxw49DzNYlr6IuSbXnuRWt81yTHLI8plz03/+Smqs7dEety8USRoXHv6A5NJwlYcSWbwiV6h3rM9R/ZpnnmRc=
*/