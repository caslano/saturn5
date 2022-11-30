
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