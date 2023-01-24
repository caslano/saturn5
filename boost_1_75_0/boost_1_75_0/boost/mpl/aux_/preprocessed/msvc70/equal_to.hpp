
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          equal_to_impl<
              typename equal_to_tag<N1>::type
            , typename equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
Z34Ix8n/gBpWGnIrvUIJr0ECM9XqcEL5IZFCOGyM+U9gS62jYfFb52jBX1DKZeG/CdZxr7FykiCPh/5ZXlPHzu41EPdWv1fhLwIfIcN8vaIHu7u3ayt6EQEkIB89GHERILYyyTF2SdhDKhC9ys+zM51LRsT5qW714ceAL5dzzwe7q8MCIxPA3x9D+AnA5o8BL6jiOREeUqhiIMkVCPEc5inQ2UOVGMLMejcdOweXOF2dD4wK0AB6Kin6eBG/wb8+BMBbzV5DQwuv59/m4pWd3OgWen5p/yyGgV10qt5ipvgD/vGRnMKbiFrJGykA6d2qcdTVHCB8GRhoGeTsCZu8AUjeSEIHYUVPtSH2F/XCcMHbBr834X/wsyGfF8Yp5l/+r446278k7Crmxmb/kYN/cFMbde99aBb7JNz4FwLEEyCZHQJK/zV5Yv1LkkbX/cJfqCKNyjKZYh4TV7SvJqCmZDi5ZSPF7uc1sbYLpcZNHojWC1pxzr/JWp2dclsdUkYcdKhbcKgVxSCWZRV5RNzWRI4AfvYunSFZaZsZ64WUDmAvt+PJzBa/5/XUFn/XrDD3Q1qE0iwcM046pyJsZ0ZjLjWErfBnKd27cEgAf870SXQTQBGgcgYUQXzg0p01pd0RAJr3uRghO9E5fXXic/pVSp9eOVoOdYccy3fRoEknyghF7xEXvSXp9mdaY6adrApsjgiqL5qDkdW3NaS7
*/