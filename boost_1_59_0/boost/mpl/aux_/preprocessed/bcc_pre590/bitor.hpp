
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