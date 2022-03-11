
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