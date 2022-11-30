
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