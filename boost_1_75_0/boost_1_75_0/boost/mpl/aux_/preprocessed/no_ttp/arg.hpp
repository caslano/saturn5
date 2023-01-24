
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
lUQSD0KNmYUcmPiDteZ+rFYHvNYG76YPXetPnKKfpfotXy3Jv5/Q1d+7WTgx3quuXN2/EfFawrdohtTqxgxErTZmPcxrgA82VkNbHdrtxmyu9yXlPS4WMFZ3yR6M8xkocBH6YzUbMAx/DUlCJeJT7jHV17qd9K/8TnV6Z+lFepOdsr9VX8EBAtbbS48UlQQN2a+XKCIKILblVEKb3tBiC1pBFC/j74NEOSc+7d01UpoatVf53Najr2WzeEFfDZuz/HZzuw8jT+WSw72OkX8l41zNu6Ef1MKj0uzlWzElGqQjSTVY+EzDosJBmvLCnL2gXMYXwajnDxInOw8wMFL7NfHBn5W5pPDwsgy1XwP2XhHdfQX+AP1pRldaVpb265rb7Kodx+xL8dFUk2/Vtdl1Wo9XhZaZccyzuwHVk3S3BFfxTgPSgr1f/mJenvlriRlRH7t+PmNwtAO6llrdLDf60Q2NVUk6LHwf/8EXl3v8fDssF9PiaYVsjBXkBMqrNiQvBpbu03loiEqT1AV+cbx1Fi7uMJpb29+SvJOdTEBZa9FV9UtdzqkORNBHgwTX6YluBzhm3vE+b2+axjomPEzCfylUr/FrewdTu+8qDZMbl+wS793AIX+39v4u10G138+2ooMsvf7LgSUt5uUJXSv3YEQLM/kQqCvJVpcAxKFhyJkQJubTC00hNHrlyohpbdkVrX3nWfeH7o4/myJ+
*/