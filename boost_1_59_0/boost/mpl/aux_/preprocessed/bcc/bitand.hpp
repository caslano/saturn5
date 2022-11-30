
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitand.hpp" header
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