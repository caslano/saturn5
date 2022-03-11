
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