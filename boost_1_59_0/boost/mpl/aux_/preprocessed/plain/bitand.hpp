
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