
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitor_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct bitor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , bitor_2< N1,N2 >
        , bitor_<
              bitor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitor_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitor_impl<
              typename bitor_tag<N1>::type
            , typename bitor_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitor_2, (N1, N2))

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