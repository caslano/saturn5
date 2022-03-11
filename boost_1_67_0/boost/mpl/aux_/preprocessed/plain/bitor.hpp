
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