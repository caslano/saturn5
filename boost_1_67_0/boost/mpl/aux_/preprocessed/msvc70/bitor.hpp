
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