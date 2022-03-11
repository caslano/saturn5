
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