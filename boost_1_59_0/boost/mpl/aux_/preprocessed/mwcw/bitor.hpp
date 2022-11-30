
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