
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