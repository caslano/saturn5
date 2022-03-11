
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