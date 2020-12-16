
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
/dvu9ks/rPYnL34u6emXriovtQ48uPPlqON1XHd3XO33ld9ruFb6js/HBYYcEy/shr4YjM2wO7bHHjgQe+IE7IXzsTcuwz5YjH3xOEYSlVJehJR3LoZJee0Mz6vogh2xJwZiGHbCMYacn6Im8rtMfq/tJ/rzOheVIUPml4kdMQu74jIMwWwchrk4Da/AWZiP83AFLsKrMBlX4lIs4r+VuBqL8WrcgGtxO67H+3AD7sKNuAdL8Tm8CV/Gzfg63oFv4Xb8G/4Zq/Bu/BrvwdN4L/qwbDsxEO/HLvggWnEXjsCHMAzLMBIfw3h8HC/H3ZiDT2IJPoU34x68E5/Be3AvPovP4dv4PH6KL+BnuE/LcZLfXNiJ2O+U4/SN7EffYiBWG3OjZLrOLqb7TqarwYvwGB7HLIv8loEcma4ZJsp0J2S7n8RA/AG74insgf/C8fgTRuNpjMFfcTFamrCeFDATz0F7fUul3AAX9W3K57zwXGyJ5+Fx/Igok+layX7aTvnbK9OVS31fwQB8FbviGzgYD+AI/CuG4Zs4E9/CuViBC/E9XIbv4xX4ARbgR3gHfox34Sd4Px7CF/FTfB3/hu/g5/gxfoGVWIXf4xE5z/MlXohfyfaotMjvBewhy9deqY9TDt1EbIWT8CKcjINxCk7CaTgTo3EezsBknInpOAsLcDYW4RwswVi8CedhGc7H3bgAn8GF+FeMw0pMwGpMxBpMwl8xWZ5zk4IX4eXYFZdqxy/5G45JLo5fQ2Q5rdgVh2IvHCbbZzjG4wik7eI5x+I5x+I5x/IHO8ey+zFfSwVRTfg97msJIRYQRcQ2opw4+rjnHIxn8AyewTN4Bs/gGTyDZ/AMnsG94XfI/+eUWOOc+29ryP9vJ/2rbQgv6QvrZOWaxS9s5/Dk8l7byf8GnOM0XqMd73Q+vpfk7u+QcynbiK5KB4tTWVzRnMoZGq28dg04n/Kj7d4COcbzKUFWWx5/B8N5M9ZxnPI5WyGurgvXz1epCReZeRm5cr5J6acNtuX2Wt6hzrzVcvt7yfUAHYzn0XOUoqQkWRdKDJD1USLrI1/W/XLCynyiD9vXR8NyLuzrXOrgsM79vGpv32Ar20cvg3NXIcrJK3ZFbq+Y0/BtrF+/oZ8HZT4O54hLTMr3r3IsPy1zCYkL7pdtPAcr83Bcfm/X5Yc4la+cxIzPzctOcmMfd7X8zMd2Lb2UXyTlN5PyfYnuVraxQ/nq4nO/i+yCuNyCrDOpg7HME1JmtHzPoogeynfaoUx9keM46ejO9ft6mfp2XtS09nL2pMwKY5lyq4czXT77Nq2Qsi6QsvyIXpRVaShLcg5ycuPTs9w5bunl6TkhkefWXrbeVqUT3aE8OWwptyjNyWXF5pxpufZ1uvvc2vfz6KN8dxzKdf8erK7KCpLcgTzZZ5bJPhOkl8XhLIE/I2lJuXKvDj83y7If94qlrHlS1myiL2Xt08pqWP6X/djt6rjXTk7Cj5B1F0r0p4yQL7Uycs70uCflOTx3lfloz4nJI3gv+Rn6Oi6TOiVIneKJAcrfP0OdzuRY2MvpWEh9tGNhG71OMk6tlsO6Gu/rel1ZvtLrdabHSFfrivk4rCvey7rS6/SR1Ol2qdOtRIhy3HSo06BG2X6HWzVs+2XJs1n3Sp2ekToFHXWo02/efodbubf9vJu5Xlf+XzvUq1G2H3Uz3X7Gv0GlUqfZ8h2fQQymTpXGOjn/3XPjb5DUS8tF+prff8YZGesSIAeqNVKXVYRV2Ze+0evyW/4eSl2c83gc9p3NUocEqUMcMdTK/7411EH+Pp7Jeqh9LyTHfSSwee38ylDl2GMo/0z/Zjpvi26EcUbG9bBV6jFS6jE=
*/