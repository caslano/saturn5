
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
YXAUnAxHw2yYDHPhGFgAU6ATpsJL4Ti4GI6Hy+GZ8AY4AT4AJ8J1cBLcAM+BT8LJ8Dk4Bb4Op8I34LnwS5gOv4bTYDXMgn/BHKgc43QYBnNhOLwASg5qedZ0PYPSL9oc1Hbplz6wD+wLR8J+cALsD2fCAXK8g+R4T4VzvbleqUeeDeFJ4kedEyacciGwhfR/hHc/eb6jjMF+J8h+UTAMtlLtVyz7RRnsN1P2y4eRcBZ055Qulf3Wy37qnNJF0h+XwJbwMhgLL4dDJVfoKDgfpsCF0h9XwmvgIngHvAreCxfD++HVcC1cotbJ7PLoMtjMdTelUq6ln3Lbdun0KoZ6mgp3fX7KVavKTT/CTF8iv9GwuZ9y9gDLpe4OzK8jgHJpWImUGyXnWx2nayPnuwNsAU+CrWAnOe+dYW/YBfaH3eBweAokrlovsRptnEYfo2k61jA2YxyX0cRi6icOIzEYTfxFG3vRxl2Sx6ljLcZxlhcwTXxFF1vRx1X0MRVtPKXrYv8xFG/8pPbYSdzV+pjJjViMxEckNuKNiwQZE9HHQ8xiIboYiMQ/dLEPbdwjyJhHbTGOMk9c4+By7viJZUj8Qhu70McstPGKqGX4Ibl8PJaBFWGrsC3Y+5jtYmIRWCpWhJViL2DVWNQl7HeJFXewNmuzNmuzNmuzNmuzNmuztsNrC8UuaID4P7kJlPD/Qcf+vwizeXLVrZEx2mdgM7gVDlbiIRXqOKlrxrSS6ENpg4MK/eb7UDQAH7/hyR0hu6nWBcd7kSp+/hYDhRQqNMiLIXkj9HPrjebf92vhqsczZ9nZUpsnQ2KczGHRx2C+YMCz5E2jGKcSAgo89jLZJ4dPbHN9zG3VkfrY1x76oMzjX8I/YxJSU0emnKFEvoKJ/+yK1OetijXIj/cu5SrMfErWqmByonEeNXmr+teSt6rMoD0fsn+1SXtqomCBt2VXADn7+oYax4DD3jr0MWB/c+ONY1XWnPnDbc78PzU3fm+k8nnCUa/kDfnksw9Hnziyz747Y0Y3zNx45nzKbwi/LTIHpaNr7qg3ttQMRsNWMAa2h22gHbaFA2A7GAdPhFmwA5wLO8G7YGe4BnaB6+Ep8BnYHVbAHvBt2Au+B3vD32A/+BfsLzG8ATAcngbbwTgYCwfDoXAIHAtPh+NgAjwTJsIMOBReDIfBeXA4XARHwCVwFLweJsMVcAx8AKbAJ+FYuBWOg545xm96Yyzbaok98Zthun5SI/U6S+76/JSrDrAc90hPuSiDWFbTAOfcjCivmXdzAJL/nbUmgovr1Kw18f9eZ+KfnI9T3+tM/BvWmAh2rg7rTBz0XJ20zcHP12mI9SWIY9V5jYnDZf5Ofa4vse4S5uJg+7GYecy1wRzzrFjXf3VrqPf/vNxp9fL+/1UYzy3y/h8nz2OJ8v4Tj52u5Gl+TZervkYvf36O067opoPID+/V+xvmyva05QVpy0TRI47DEmhLsUlbRI4+a06+0++cBH1btHrDfJ+2JBmMDyTSlmp9W5RW1HRLzQSAgPvFqxvX+t4mvk/AQqQNQ/Ed9rq5b/mgzr6Hi+/4EL3vJHzba/M9e05mXu55uTkFhXX27z72V8T/KeK/GzYC/6l6/+hTxb/rhAZ+PQ6PljkkuutR2xfJBmMDo9i3xLwtch5y0b/WrT2K/1Hiv0L8nyz+u4r/str8Kyl5PY2oexsS3X1gMBdgtPI9MG6DfDH5TgbxPRDfupye2xoZ68PDKupfH54oPkc0NtZm2ysaRpu9z8qX+J8a+/m35UuMPEH5fLBjReNZn7/ec9LUsUe1rur0XcOMCWXY5LkCJkreFrUeeqRN1q6ER8PRsBlMhpFwDIyBKbA=
*/