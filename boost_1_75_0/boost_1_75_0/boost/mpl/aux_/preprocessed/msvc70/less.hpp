
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less
    : aux::msvc_eti_base< typename apply_wrap2<
          less_impl<
              typename less_tag<N1>::type
            , typename less_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
4hG0bb5criWAUT+iYoPI+L7vwtgwjf2+FJLFy1ceKhFktxj0KPB/ms8x2ZeQABHofF/Z5por8zVNknBcKtPVL53H5zaZhzD5+JjO14tGabCvlOXcBSOiggj3vZREuDt9D57u2q2JZIbcqxSESRznWrwGlsQZLbS446zaRiNtTkS68GSMrnr8G8pJ4iLOp68lmKl4VPm6WHMVIRiqN9GjU8FzJP6/1WNARjgHFgzk2V+THQstPn+Zo/C/F9yeWfIkgCYYp72STaB2Zx7V2CqVbcR6SSil2bLI0+f73J1JtUh8h50v/9H3kfBg3zaq0udmTO3WjPGgbnbwrzMeFmw4FOs/1Dvomac+vLaaak6QmDuNv/fx/7WMP4/yImJMGnoXHLnz2/0sFZuDpDg4Oktg1XSoBidiRr/7Vn4MJyZMnMlzzPv+kt9ytkpz5vUBGUzZ/IHdsCPgbvOsjUOqMny+SNJzYEnat5ExikJjK5KaxtKwGkBm8Wyj99c1kgK81WKdl7FWXeNC7Sq/pjrjSa6ETdz7Lr8c8bScKv9CH8c0/uZlde0rF5/KLXVd/VoX6qS5YmrshNE/HMnky8GSeIpuwxVVeTthuAlP5xamj1axOsqnLrz06PqKlsfxAwMDjR/ILzEOPtokxetge7ZyQTYeDdSM9Mre6Zb34ZVVlU7Ln7bUZqMwmpy1zBgpVQvrs+TlkzdKHt0sx58mEfSC
*/