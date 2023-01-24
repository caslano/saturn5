
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
smMx5yxoJjDxe7Jx/76YGeQ+ou1i9eEcuoP2qSbgvYicEEsJr2fSol3q0RYiY/7PVZVErUrcy9JtkuT7+MXJPsFgd6qcAAxH3Ps+GrI5ac2H9xsq/SRVtGK5GlXsB6KSEJQriUfcF/KXNO1Hy993orK4xZcJwdZX7CuSiEElEvyNxN/IGCTmeEemi+5NPpHKh5R0zWlpprQ9pvCjaWwWuUesdc2VWT9kP7W7CfNk9zqXdCYGpc6j/Vy9bFJuVh5J8DlJrF+gnBEa4LmTo2JhDg7DVyTcQp/h5sHiQS+xmOvs+JpmimLbVu0KsNXT0g0mryWN/SasHdapti8jebiwS7gzfhlCOnXXSri0RyMSIe5V01d8Wzn03Wtxl92FjR7pQDf81FF4cRtwa/KRavBNYD8p5fCoJr5c7o6RzYAzfTWhvRuHVy1abB51izFp9Yfjlu3CR5JFtHbA4A/96frRtj/DJi1YBw5akV3Xw72v3lD9JrLtV2p9l7rzfT1E2JH/YgjZh0KPM9d1T0JbbO7efKLPkjOq3yPYSbBqqT69Psxzqog7EaVGNXnWgnLCBan9aXV7XpCYUaDGSSAXxHhdhK5Lmi7/B7+NLl2jK4VwLf7UHpKIUvrSo8DxHU9OYafDbnf/bLVbRFBu+lTq+AWa/PSpR/bv383h6hkOnNfstGjyN15RPsW2ZZGym2PLwb7vGO5NOXLyoWSPCD7o
*/