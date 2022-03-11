
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