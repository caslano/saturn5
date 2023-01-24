
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
YRqzTJJWzk52scCnAiX7FRf6UXVLjp5IYylgKSgR2kYWUmZmqISP0V3SZUrRVDJK/mRkuEH7CZ93ALWnSUOPGcplZiGvRVtqU1aRQTP1W06hKtYUpTQ7rW9C7Fx7Rofab9mu2F71sKPBlUWl9SnnZVH5Ekwf9Q1iAue0ss4BDOamtHm6797cqMGsSJTXWM9DSxDGrUiKA9jPWHLCSLtm4cB+y21oT3iHRPFPGuJ7hwHi+omtUM0TsFeCThR/MMNgoSCunbgxjR54f5itoJ6AnhCPbcdtxx2+a+Z3TO3rNyfUT+RPyE9MwYCcw/UBIn+EuwihLVF8f6Uh0lixJXWi9iLA0xVdznPzbTSoeneGBlsRpdxzV/mmUHKo5I4eRVyNqL1qd/GHWudrepSmY16hfwsrcbifwa5UsSGQsSFb5/TbSLqaXJlqGefIgAx98bFvzttjPWlXZMNQmYp91u/SXVm11GzD18Tkid1sjJ9F1nn9hBXulzKNrzsq+csG1jiHE4UTEKCDVKXqYsNiXaVDRxTCsCp+YSz1o1Wousm25dvjIb1+qKLtn7xb+nfvzvjdu+erVP/q3eF/9+6zt2Dz6Y5pFr5L9j2veZNuEF7A5BXpdOtVm8S6fNw+MAPT33/grP/NJO/dB1ylxaUqG1dPyNnfTXmr+8vvlVJP0rZh/UtLiB5flvx0PIPQZwqH/yPxOSzOOIgtXvBLEuiq
*/