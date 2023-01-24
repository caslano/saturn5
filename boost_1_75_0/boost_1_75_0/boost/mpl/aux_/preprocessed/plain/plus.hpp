
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
nhbzXcTEKc4pOxSvGYRrgmZCW0EAbut6gHsC4K8XTnAqN5mA1HD6hWz0p01mHWfq3LHkws1fpM9IlTu409AZaKTT50yl7Al/8Ar1hyQRuU9HuEcu4F2Hm++l+krUJZ+OZFVt85Wn1PP3j099CQYfsCZPAb8nL7CUsgDFh1P10e1/6T4zlr5gXfaOuyEgx2xHH+5NyRl4yl3zfvzKb5k23jndhjSUOoUUUt5I/h2yQnnWf8T3IwUjsl+QPGBTgBnMUjjGZetBzpHdDeTG4/E1HBPOrCfgPHNKJLwZ2rJ/k//jLPOGBcxLbFjgNBsw5XUEOKZ7rAFb71ksFaJo6cZ16/86/CADZ1DKZnrEo8mVXZ0wnpkFtn9R9a67MKMvM5xJIg3kXc+K2u0n4o5g98ZmOzxo+he9Ry5eXqfjc5iNRPqosfBN60uwAXmhI4wdSU02VPO5XuUp1+pgCwnaXfBKaARSth5Igi6/8HpdLGc5n9mJww3pgTNKYFvxm5rA4o0YPVqcNgejIPLYG92OD9SVP0+VLNSmSKcjPY0GLY988px/Z1bKRT26C5U1dm0pUnX81fND1D3icja9v05C6MMZt43scGbGnL4wezCOMIdNv5i2tz3qn1ft7FIsrmdqvND0xl3RSANgR/9YmzuH0Z6A5f3RW9ZDy3+v1HR/Z6xcN5uYwwginDcNMeXFNj5asuz/NOp1SKq3crT9jK63
*/