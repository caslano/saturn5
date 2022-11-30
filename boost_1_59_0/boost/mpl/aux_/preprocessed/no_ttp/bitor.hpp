
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

namespace aux {
template< typename T, T n1, T n2 >
struct bitor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 | n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitor_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitor.hpp
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
*/