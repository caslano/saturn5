
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
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
bZtmvtPZtV/sihBftENuwa4yc7vq7AuHXVFkJlMZQ5VzFHVnsCXLOPsQ8dUlyK3YVLnYNSdkgu34PW2HQe99tF5s0Z+tUcOWuRm68wnfFVvCxT9hyO3YElWs2pKZlZtlzcIcn85TqmmP6Nf5Ik4y1lX0d0E2RfO9Tj+KPe6hb6pbl9dy0dUdaSG6tqKrRKdrthzlprUL3vv+Dhk7V/PWrZG5bysM+shfPfnVUe/3NTLW+zvRXWWmO3Xm1anjRg093bLNZ6/IELWupRdaLXMLdXalnG206y7sCrrGjV2cHHA6do1AK826W7suE7tOnW3urzh3dmUU5FhzMtJz62CbesYUyWgws09Xd3MbG88zvRv7LKb2Zcwtyvd+n2Sze8VxaFaU6OuAbEdfqam+zF45dfCD27oTKH6RMKHyHXOFdPdXcRPj79y92v1lZmOh7/bpzk010bUDXZUGXa6dnOtyT+vOP21q1HkfOqsMOrVdiL0//5S2ylDeB0107SRcdU1dstUwu097rc+sfg0yOdNvF/oCltTUNz+rQNv41wdfmuVvn+jrI21/T+R+wkXp9BXWqe135C9Mqc+uVPT1KFfO7csXO65CdmOHRW+Hrh7VpQ/gsKXm3uLtpL/E91p/SdWiq3uBzY12PqSVz1K9nVL3fLbP0Qaqe2iHKedrYZukrC/HMhO7yrV2SW+XWk/rbJvrrGKXbd3ENvleZ1tHk3P+HtXqWInOtjrVab1tEJFU9Ptqt6g5fxJqZyGVmJ8NUZc5lJfVOJ8oWT07wT830D83sA5zAy22uYGNG3cfsH1H489Khx9Jat/ixu9/m3MDY5HqRa79nTrX2E8oXuZEXQabwARojyfP4KCZSbzREm8MbArHKvvWBUm8ORJP3beup8x16g3bwD6wA+wLu8N+8GLYH46EA+AYeAm8Ag6CM+GlcDYcrNhbJnojTOwdLvaOgO3gSCVepcQbYhKvXOx9BF4CH3XGk+dOGK6LZ9wnNAw+qOwPGifxuko8dX/QtRLvevHrOtgM3gAj4XrYBd6o2FEi6XU3saNE7F8m8ZYr8SpqsX+H2HGf2L9TiVdV7N7Pt0u8jeLnTa54PDe5j7dF4m2VeNvU/Y9riXeXxLtb4t2jxLNIvFCTeDdLvFtgCNygxCuVeFEm8Z6QeE9Kvd2j+vMa9/fLtRLvOinXVWr9qyVeN4nXXeL1UMuhlnhFEm++xFugxKuuJV6axEuXeDOd8aS/C1qZxGsj8cJhMGwLnfuvSrw+Ek/df3WR1M/FsBsshj3hNc72BJH4+SbtSYTEj4ThMEruk2jYA8bA3vB8OAp2hGPhBTAFXgizYGd4Feyi6A1Y6l5vlujNFr05ovcq0TtH9OaK3jzRO1f0WkTvPNFboO77WYveRNGbJHqTRe8k0TtZ9E4RvVNF7xWid7roTRG9M9T2TOZ2tzEp3xAp31awNQyFzv0DJR7fs4+QcT+9IB/21fHPSf3/m5N6puaj1mUu6u9pL53/xHzU+p6L+nuYh7qXuaZVSJM72FsGmYosRDYie5HDyCkkagvzUhELsgHZixxCArbyP2Qoko2sQx5H3kVOIhHb/HNZ/Zf/+l+7ztD4f72u/6ez7nyPOlXG4vvBFvBi+Li2/v9q5Z1gPay7d773NZznxxvQmmvT/e/o/O/o6vCOboftHd24ki29o/ouvueTTulXfhhpnfjbfEdH2cs9xr0n62pDbe+OZNxJnvnawFYwHLaD7WAX2B4OhufBCTASzoRRcB6MhgtgDFwLO8LN8gz8gDwDPw47w9fgRfAj2BV+BbvLetNY2AP2ghfDi2G5f72h/9nO/2znf7b7nTzblfqfvfyX//Jf/st/1fM=
*/