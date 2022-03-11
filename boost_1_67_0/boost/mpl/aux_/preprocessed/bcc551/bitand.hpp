
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