
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
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
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
*/