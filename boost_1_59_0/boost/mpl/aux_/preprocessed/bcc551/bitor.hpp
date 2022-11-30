
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
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
*/