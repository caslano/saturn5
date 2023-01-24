
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
NuQ3K+zV9Xl9dCnmlMqUfQ5dX90d5KnaWYZdpBDuB+VrceU4atZqbwYkSYp8Qq7nWR2mXaGY3SHzprQaWcUVGXvYZd+eBpsHnTT+NP31meBu7aLmJd0oMBBZwm8SDOq8fsfTbPeyGq4+xv7AvSAh/zZjT1jOXj2YddqXc8//idEXJ552It9znlfOiQxopzRPItlZZmGn4Bizr8pEUSwhAE9FlEA2OqWCyKlhreRMmQwd69F5M38fs9F2nDaZtEnav68pOVe07qwRYwQK15YFcK/Gucer4YwRuD30JeuxlEuffuN1AbbNubfpyZzy6NVWG4jef4CeOp6pjP30m1ygHcv5Nfk5/aPUkJ9V+XWNe94UewX5hNjHYnTgWCvF+6y2aRHEj/5d8veBom4URUI20f4xBxtjQql3RtImMkLIlyqwLvcedwx150s7adWibjujVpWP+gin9FqvNREdFcpxk0wm6tFCqX+GgYqBcTOJfThuQjKnY0wLp7zLeEoKwkTCEzYV5e5KK5TWXD9/jC1zTnLNG423ZFeiGGWMjcjRq64w9NEXVjsQTsmq7jIhHicPZRX3aigIbabVdXKmsA4wuqKCC1iuz23eQLRo5OMJX5vu+ii+jJBPYQaPjCT0/wFZtRN8Q8OJsn+FG/4MQt5zfcveb+1LqtK/vkt+Eqm3Y3zFKIqwPEMjgURyN3Z+kkEZqV5ULPYGGDE9QLQ7
*/