
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