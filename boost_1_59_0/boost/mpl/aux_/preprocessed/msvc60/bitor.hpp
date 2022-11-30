
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
{
    typedef typename T::tag type;
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

    : if_<

          is_na<N3>
        , bitor_2< N1,N2 >
        , bitor_<
              bitor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

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