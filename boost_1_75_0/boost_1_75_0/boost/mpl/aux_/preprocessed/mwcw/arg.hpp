
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
l9GtyNfF/4W8pYwZ/kreK8ozMjMSToF5OrMO+U+iweK9lmSBNEjVSPZImIgMQfK7LZU8bJKofSoarTtjVR3Iggsw3j6mRWDGluX7HKoTGl55J6WHh3mIH2E2PNptA2Bz74UKlbJ0Yjzj0ReqFebd4BCy4A2BnVj1moeiivfUR7ARW5EdlHIQE9865zPjf+IQ+3kzb6n08oOahmKARwDXOlpCrCfIavD9E3EqzeUPHlwMkjcGMXGpUSJij2fErRmv2mVKurNCs75AnIj71rAfhYXq2DLlR3H56rOH6CQhP42tuuAqZl3jZCSfcajz84yi1mpt3kYi80eu48t95JQqjbo3iSKLvEZvKBgIwty6y1Xj2fZ4qpwve77xmmroDyM7LuRW8HcHiQ7U/lW9N2xD+wdf0nj++OkBk2zEbzeCxkvnC28s3Tn51wcKTCTxdObZSzLM9x0M3eI9eTSkkUjvvhp5TYDJiWyl5i/jYiCxHuC8PozNnlLvyeDPs2fXkv03cc9DXo5QjpvUh+fk58T7uQeDhwp9s0i8th2yuB9dVV+GePmx456pVRz4SLoWKD7G+gzFRBaOk918IY8wv8DAkuX68dTSmUGKuZIVB3s94rcEivtmdm/vunRA1tfW7Sch9pOTk4qY61v8U6r2LnJddg0L0oRc+OQx19+n+Ap3ZZyaDB9DW9ftHjsuW/h9s23KiTYgmOZLU3wU4FM+
*/