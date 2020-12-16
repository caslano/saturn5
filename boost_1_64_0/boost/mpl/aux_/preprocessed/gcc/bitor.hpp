
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
naTUGZvX9HEbq3v6pK4ctfStb6RPXydsKvWePm5hgacvQnP/ctzA+PmXp7Ovs+2Lr/4wSecQ5BRsq9GkU74Sr0TgR5t3phEbjL7Xrhs/qPP9oNizTuy5CumCPUnFantc99KA61VBWO31Sr5JLvmtLQPJX8lP3+/N2OTm0Fvub72QrkobOd8jLfaMrf1+6vJLjjLMV00+RooP/EDJx/5Id3SnGeqW7ieAsp0SVXv/I/noyiPJa20/KXYuEjsvRHpg5zavdlLcfvhVq+ykz/avvNVlWeBR1tkl2v5h2PF63+Zp6LLOMbLb8ZAUiN89dut8zzcZ6DxduTfOcfo5Dxw3ukdq8qSkRMWp2m8/59Pau32q+4quuGZ6n+rjIxkXGuiyFhfNCMSvekhbbZkkoNFqK9To32Sg/wzsrNLrdzh2B6Bf0ms8JhT9vUM89Uu/6NKvHRZJF+m3DfRDehsQtQ0bDfz0+yj9R4kXG3IKswPJB4cNMhYUneGh+r3e17bhmcabTgZAVLa8PD/0qtO2LNS4/SR400OFDqSOSbvX6GwSpi/TfkqfaKzTUbED0OlZprukXqttKPO0Qe4JpcY2SOX23wbS7fOdhaq/cX/Cv+udhb9r38InWynnJ0+/ZlfITeM/XXBg6sElUSnPBv4uQ6DvLAT6bkKg72LcF6WcX1CS8XBl1+KLVz3/8Kj+IXP2e3/nwvjdhMDfcfD1LkMCUpnn9gFN8PABPaWe7GcPG8IusCmMgZGwq/iWzUCqJZ65Ek8jOFXiuUt8Mu+FkbASdpR3A/rD++FAuAmmwc0wBz4IC+FDsBhugYq+DRaZ/4NPi74wuF70PS76noRt4VPwFPg0HAKfhcPgdng23AHHwhdE74twBtwJF8OX4FL4ClwNq+B6uAveBF8TH+jd8DH4OnxC3h2Q/JG5PPpwg/zZI/ZWwyj4ITwRfgQHwL1i3ydwAvxM8mMfvAh+LnZ+IfrSLDKfBrNEX0OYLPp6Szn2hdGwHzwZxsNTYX/YD54JJ8ABcDIcCNPgIOiqP6In3KD+xEr96SH1p6foPQ2GwThVPFUST0eDeBIlnrMknqESzzCxf7gznnoy/wQq6jniOcmhx378JPl8EIbDn6V+/CL18VfYGR6C3eFvsA/8HaZDC3qmK4AXw2PgchgMV8P68Fp4LLwXHgc3wQZwJ2wId8FG8E0YCt+DYfBz2Bx+D1vIOxYRMAi2hOGwFYyBrWE32AbGwrZwCIyEI2AUzIDtYRaMhrNgR7gUngBXwRPhDfAkWA5PlnxMssg8Fpwi5XEcHCLl8ZXk49ewtfjst4M1sIv47seL7/5E+L3UyyqkTOJ9XeJtCZ+ReEdIvCOlfEZJ+YyBHWCSlMc5sB9MhoPheHgOnADHwYlwPEyB0+Bk6UemQBucCpfBafBSeC5cBVPhtTAN3ggz4EMwCz4Ns+ErMAfu0vqkyxwVupAED5/0hZKuUv47FV4EY+HFMA4ugkPhYrF/ibTzpep3GGze4y+Q+M+T+Asl/iKJ3ybxF0v850v8c1Txl/qI/3KJv0ziv1LiXyXxXyXxr5b410j8a6HjnTmZG5F/J3i8M5cg8Q+W+IfAbjBR7gtnwSEqX3CrReY24DqJrzHMkviulfiul370Bon3Rom3HI6CN0m9uRlmwVvgfFgBL4S3wqvgba53JmQeAvY26Kd6iy95HxgN+1qkX4W9YH9VfqRJPAMN8qOt2B8JEe7N8i6R3Mei5b7ZQfVO3zaJb5HEJ+/+aPYrPgU2h6fCVrCLtKsYeALsKvnUTdpZdzgSxsJU2AMWw55wHjwNLoBxkl+nq98pmOP2IU/w8R2gZrCl2qdcFW4DovYpf0fly14p17U=
*/