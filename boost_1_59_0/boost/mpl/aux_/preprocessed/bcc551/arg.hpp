
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
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
*/