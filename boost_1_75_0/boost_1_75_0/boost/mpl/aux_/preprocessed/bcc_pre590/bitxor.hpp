
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
yC2qsiG/GMiyF7/PgNyXZoxy77vVK2sAfB+yU55S2X54WXL7Z7U2EQn020LJtd4qeRXXpi8xodkkcCkHeuHqeZRqvWGaYXJUZKBbJNpPukZXWfFBRKTg7IcJ+h9WiaqASp5br0afXky0j74cuff/tA7zVpx4fIGwEgUiLh0epsYO02/P3qj99Wlfoy8h5rht7ddZIZBWuJsHdipvGnB25dmuA0tIfLgr/PaS33aO29sR6xz0cM+xxU8RU4oQw99WRYdNtHTLaxfMHKexBr/g4Z8azG4TPqvsCSdGMQR6QxgCxQtmod7lMWSD4or6+eUcz4iflxeoxjhG8RvR3ZR3HMHJt9/yL2pjiTkQaPIBxZryIPPRqbHe2d74Ur+dnolLxEeVCQTob8CN+8x6QPb/VKj/dcBb2sbS3P6fE97AvwK3Z77388u3TwrNrMJNPWWWik1sUW3ehJXq+ONP13OwIk98Bt2kSoYOuhWxrTl//yKb4du5RDNhTvqJqBzcvT7SqOvgvbcTrshoXicFbNGv0XeGXE6Jj2gUCp+Xmm2/0n06STj15/7uP0Hvu4t3TPOaCxecW89/MdXty+3u/x0c4L9Ub9zrt+6so7E6xbwq9yj05YwZ5Q11Fqlb5LPcY8AW+zSCIaBmIAIdd3qdXDBBm3QhZ+VPOzzPSD8ZlCK8RmRXArNSl1etGI16rY4jD1aZL0oPPl9DWaMsOMPC
*/