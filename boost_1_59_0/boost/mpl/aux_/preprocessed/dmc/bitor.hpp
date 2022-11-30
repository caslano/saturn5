
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