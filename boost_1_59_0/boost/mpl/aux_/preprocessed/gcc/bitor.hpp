
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