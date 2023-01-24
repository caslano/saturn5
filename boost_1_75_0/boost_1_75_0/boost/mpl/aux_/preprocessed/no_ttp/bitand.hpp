
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitand_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 & n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitand_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitand.hpp
A4Ql7gU+gHL7kp4y44FBLrpxq9fn0twJg8FieQ4vECHNM6ppxjjCmH8g/05adlRz8qOoSRLFzpKloYEEtRoDlWr0rigg1Kl1Lk6Hn+lBaFcRnkFVb9QP78aV+GLwaYyw5i3maVD6lIJQ9nIr8xp/lkJRfOs18qU65XxCaRI0dauzpCWb5q+WVZ1TGoW5JYlZbGMOlO8Zl6l8S6mz/wq2izRk5rTBuFFlBn75ChSxui3N5fbDV0kj209sSDt8vdOOHv74OIT6nGcjekwVrF7fozwVfWeM4k3ZcHnPiETiHspGbJe+6m0oZbNhYhjXIR8InXQRGxyMBTUifouNeURyTvEcDXV/uSUEUF+uzrHxxA6Z//0le7dL7s4t+Hqj/UE4F8mlo2BkR6O2+CR0xQT92tO8BJISrcFzfRBw7tkFwdz0iFfDT5x0e7hzI84kXXzQDJ4BSpPFBKqsn1R0LeZQ+KRbwHk+VaOUUW+9CnmmYVN62BMPTV2/gPl6WBT+qp8mwmvwBl2yqdabefjDYak9LrSDkvmuK19DswBVvMOUL7m/6m60kBPEHGv5cFac6af0eCu8jHZ/GQ2S3ugsebl2V9EDSkk9evy5h+p1C235xTv+MKcvwTfvzmdSSZDB4rMd0uMB7o2RBD4euDvyZ+oXcy04z//FXsS+/I/h2b3S52u+ioI8Ucyu6w8N+FadjvVNEU22vds2yprmtseG
*/