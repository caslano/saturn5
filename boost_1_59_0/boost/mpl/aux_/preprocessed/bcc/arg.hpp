
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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