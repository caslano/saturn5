
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
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
cMITp+cv72A5jJzVqi6Q4cWsMAYSch008uZSTJkiiM41WlQWc7HIHVZ0guIvn4RlyvYy/MNF48Ke8ESkABJGhXXGfO+COQOGj88P6BfyO8WAwn+g3OCC3qpBp1vWbBUbkhWo6LSg9yPgxxVUr3QXCghRgOatuEHzxmDi4qM/qzLuvDdNlokUgdfz/v4kYAIENt2dGEzm7dTsh3wwYrBrkTorjqCqVXrvKTEaegdNQCJY+nxdxEuNcjNOPG1rgeRMxWbBvim2TcKaCiNwb9tjhqw9D8JZzLP0CwTWfDZKzWHrnA5hrclkJYzawU0rKmLipLefaiR+0FUt8S7q1sSRrOonE617ztSKVLZYy/AXxFo/27TNe8euAKTtFlUta2ZShRQpliBtJ2pnUMSSJ5P3xdY2lYPzUhAYuk+W/AqNiCCrE8rLWQaoeWfOQo14YY0yx/sETv9qsmONKVg62pfIPbpCbhTBN9mXcUgePwFFncmyr1M7EBMHQ/n8a4DpsNANeYiX5F3e1fjUdzRIttM23st9u5dhJhRnA5gt5m6YsQ911KxAA792NisHQRESoRKJ4CMwYPUWZgO3dWjW5AQ3NpxBvvET+HV7srQfIDLRw5ME3W9dnI15inH4lhN0X8oB/aKQSyj88U+UNxdw04r8X5TT/e9iFUkTNxuzf33+c41NF9k5eSwlUKQTM54/lOzL+E+JCInTXZy/xHMT
*/