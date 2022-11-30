
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