
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
2uFSyNUC1NsIzxsg7IawUYUlEF4NwYWwBsJK4LKlAO9aeB+BsBxKPgTPDRB/EFJWAAecgedy4LAQnmsh/nIIl0JYAnHr6W/fraK/gYdhHeHUCuUdSlsBuZYDN7ZSXauBNxzxPorHtm2APnTEJKVh3GrgEUm1dcDvIQhXQkAI2+CJKffA8ziEAH5dQfiuA0yuhj5j3N9GudbAWwvESuBhSTggri3Q6v1Emxaiw4cp7RIot4TwWwKj5CZ6Xk30Z3oshXHBNFuiYK4Ebl8BI+HNUHYZ5LsF4tYR7VdBHkc8oej+DkWTT1LZpVB6uXgr1bmU6HMphKWA181UD1PqUXiPIbwFYJcgrIIaVkGu2yFvBcJrIA0pf4ieDoxlbiPS7WuE20qAtFb8tkpHfL8M4TAET7XhLkrbBLwuCb930G9s6VXQP0yfffDcR+1aQbyyB8K4osceKLOb2rYGxqskOLeoNn6n4qPV8OtGyJOh9xUwNiVRYLXCA9/3wvO1EI5AQFq8Dp5r4Xk38aYD/CeB15g3kCbbFP73q7iHFayVQKc2eL5J9cP3E41XUF9EVJcjfovaKMVHIPgEfxXIGyzbAmOfeQf74VbKtxTkGI6/VVTvHtWfXP8yKoe0PaDahv15lxpnQ1T3WuAOh+rHPh9S+bE8tu0yCHspnyNOqrTbVd1Ih2fh+YRq23qAch2071qIn1J5YsJ3NcgrSeP9RuKc
*/