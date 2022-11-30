
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
+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
*/