
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