
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct modulus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus
    : aux::msvc_eti_base< typename apply_wrap2<
          modulus_impl<
              typename modulus_tag<N1>::type
            , typename modulus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct modulus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 % n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::modulus_wknd<
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

/* modulus.hpp
NpcbqOPilt4vQbpwnUFcsKFnDvz4idtg4ICBwcDakCuWT+eZ+LQYnbyto6h9rvr3aoAbGccCmmRgo8pDpdChfdVOZmtx8SXd+khOp87EIqBoem5akIm694KUeYz+f4059I4ldRRT3tUtOUS/QCn+dL/NarO5yt/iJRsCTbIqJnwUNuQksGcYL2dPXeUTAn3Y0mjadeUTEnEFzH+ah0qUwIraZSQF+vha9OV04WiJBBTRjeY3Re0RiZzjNAi1/FZTIWiVqZa34zYYreqS44hVduumU6GowCsFRt5OHMrw6v9JY+B8iyN94OhBTQN6bKFyQWiDM3C1pxp9Zy68q4z979m8npQYLQsVEJCSJVd3nEfwW1G31ae8qsz12oYQ1qfkX5djI71FNZGbE6tFaG0spjYOJzyFtwweTgG/EQBDAzWK/WkUzBf5ALNm9TqmbImlHvH1QIX6pDNtZ3t05xeiCm4BjHyIJSgtgKHqcyIaMxECkEBxKrrwMXiY3t/N8uMMf1FG6KyqImiAF7ugQsU5fR1pXr2jc5A07Tef+pCX3baRA+3kD7aS0lxufQ==
*/