/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_GCC_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_GCC_HPP

#define BOOST_ALIGN_ASSUME_ALIGNED(p, n) \
(p) = static_cast<__typeof__(p)>(__builtin_assume_aligned((p), (n)))

#endif

/* assume_aligned_gcc.hpp
jPe/ePbs8RP92/0IVtuqRlR7NQwHFyrBFI2ahtiYAGAqbkGWaP3vyuGnsmHz32DuSurPqTzLGsKtsyOnrK6uqdnLY3j71i7UavR46xAuvitXY8+dW6l5Px3dfrXIaJzpqreCAHvt5WXxvI7qX1JkNtbUpt7/WYMyEx4ZtxsiGt8W3bey+b3Aw5MqBixTvVbJRBVGtrIUzdSM/JD01cagbFEmdSu3mk0EfShF2qpeHown8/zG83eEdOzM54mq77XKXh781Z9TUDNaa+BdIljjRabbMVdgiBHZUdNZP4IZ62c3kC+efBmzlSH2l0V3xcaAzdUU/8MTmHNvEJesgKRMZ9D09MvQC8hCZ7ROGQ2JMzV1kKAE8m1xPx7nrjl2IT9z5+XBThpWnLtdbXMuy+iGK6tCHDRT9latASdkDrL78U4A984oWKoauyK9hgw8ZKLI0cEgEeg9p0++3jmKp8JGAIHn5Ek1aRxUDO/2pLcYxRMP6JJ9lnsGJzX49SCv9RpJoT6HNsMTZWiF+brt6U3cOoxeMoSwa1qSyibmp6uQ4uUhpTtEa8B6x0DvyaoB9Ols4enNaU+8AhD5vB1KcGHcQp9H3p2bUbuYsceh/R5/1etHkaB9tBOHDBov/Dcl+4XwUS3nqDA0o5Xhvf5l
*/