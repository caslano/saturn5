
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