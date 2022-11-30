
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