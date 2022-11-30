
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitor.hpp" header
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