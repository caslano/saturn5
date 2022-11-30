
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