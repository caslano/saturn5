
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
+aFEAp82Pz996t2zl45hmpSBl/0RKtEeu57C79bP7KmELmsoa9/eLiR602kJ9DCRPLsbUX31siguDiDPJs+T7/EnU/ljmyod9QjiZxfC45wiPPMEfN8nmhlPVaL/dLMy/uu87k+2MiPU9dZYhuViiKAW6U6s6Uh3I28UpbADU94njnvLbSOcASEHMsmxkIOYP4fB+V1idL5Dg/oLDL8zM+77TsC9mOeWW+yF+bhUeuaY8j307uGuLrc9e7YKoKU00LrOd77Vcj93uIIPsQ47QLVXGFTsckqlHenaSOqjT3UL8j51vLncWQZZh4zUvXPMAPjX9I21JNWMLLeQ2/7KYzTFrh6I1DgF2Q2ONeKI8JqLOASClmpWzvJUPGmFJA4sj0uM3HDPwiAN5ZtZ3P0HV/nSnhsb4OrDqfoJCW8fedXDzyh+/KA4nNw4M6ZjDCAp1cBYYWAwe7ZoC/mFET+wwzpkexOcrxbzVRUhzjJJ8qCBkycrf/eVSW0uwnk4pAmRD193yzwf8cS3ng9xfFIIrDRTZh/y9GqHXSC27GaPJJA2SDKFefDcCxElqw8TD86Lp+K9MshnKEpvBZrzYHi0Wy4nXJEW8d4vwj/DHxNVuiJPE1/8+Lno0X30ngLOT3+SB5XSE/FLyc0rlaqJFZUBR2RC2X1b/8hWFW+B9o/dsorI9sqCC8Os2OR647UDvqa3P67ZDVY9fkARFf1c
*/