
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