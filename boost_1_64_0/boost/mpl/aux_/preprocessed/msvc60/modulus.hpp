
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
+fsLrXjf2k/7d+kA0FJ2EOhG/3/Fhdr+/+x7Ijbpbjw32n4D9v4/6P/P+dhSruqyuf6tauqhLPd5fvMzCbVey21S7faP982re67y/gIteSF5VF1XR2ux/Da4A5vjnXgTLsH+uBwH4wo0s23BdD9DCSHLybgiqjFF5B2k9v1jTcd4IfKeUd4x6sYDMcj7xXGTWM/J+B5FhE6q94dRhE0E/bvCGIJ6TA7po1DG1yCgqq9CeQeof/+nGTdDxszQjY/hfIx9eccn/R2ibZyLXCfjW6TiFQyTsStsY1Zcmu69z3sn7+SdvJN38k7eyTt5J+/03zT9se//5fmfh+ckmn1ZCgB+Zx8AyjN8A9X7/+ryLvl5rIXPYrDyLnmX5Rne+ugeb1QiZH/fE4Su3/f41f3uoYptrA9xtNRevI+S9z+TlHnlBRCT7T3bDJbFGdPMtmWBmMQfeOMea1sWhGbCrMRYyhLk/Zmujd55e5tex/svZT90FkBbY8c7tVRpx6i0lS1U8pJz/wpveZD4y7bljm1Z1bqsTJbNVDoHkPIKgiNN5V12H3mH1gPbK+8pd6vS1JisSVP/StL0y4dV7aclTfMlvWzpUFPSy5TsSNNuyjqm1ASjbBeoS78ASQsl7TN6hPYx6NLUpE0H8nCmKUU19rjkq6bN7Qk5/0JCLXm300G5ph5Rnf8spUKJO/Uo/Or67an8etJfJ/6VXCdyXajPSVPHolhean4sefgh3qi0hd+jOofZRnMoNSxmJxvT0t36bDiPuyMfXcf9kv6aljyzHp1lcn7KviRG9nfJz7HMFJtuv3YLLOskz0pJd7yPDrYs0+bjUSl+mChpMBZvCia++1RpoBzM4F4+XtjvyMcGkha2c5DPvev7gzqdrvL+YHJ+3drLMwulfsHTci98Erso1+2juvNVep6IlpR389wNB1xfww3knJ2lhb8uLWrLed/clHOP/81zljx1XC8HlPmkuNhUgzafj0jkH/HjvPFB7Krcrw6oznuBMc00a5HlXPtXcq5NCir/vDq75n8KIn7mlDSjLn9NyUoOW/cVJMtS5ls/w011595Azv3nIOv+lUpQ9joPuu+JK7rrokTm5zi758myU04+d5cc3xFEy7qs1MlnsczxnSP1RKQfCNn3aSefzeO6fDzvOJYpWfp5OKK0pSaRxzP/+UFHPw9FcrxUc5q9XlGA1EUi/zX1PkbVkO8sKcvvReiu1Ps4ZLkGlAve+jUSrVxBlff1YMt3yzXHCWra7JvimXfc52LTZmviUuIiLqFP2eMSb5ptTDf/gXEZInHZK+33v5bvsguEHspLfWtcLL/QouPo0yjamGFKN/NbS+Lm1ve6+rPhiJc9vzWfY3Lcdv/SfzdrrhvHNdmFZSnpRMeg7b+n6Q3WSNSV9K1DeLsln8mnLeeUPlfe2EwZPXLC8MnRoyeMmKh0MlJpPwW283mzpSWdNem4W45ZX45Zj/AO6xX/xjEXxCbO517g8XHV+UtHL5pzr16zYt3Jnko9T3s8pvMrKHrwuJETJ0cnGxdy4omJbsRBfYycmhXPtTfHMBQ6OUZqSmr0rDSjJ+cp17H9e6MXf1R2obzHY1Z7vrUq5vVtzdmjLi6RkZNHD5kaOdyS0R7EZUZzJS7avl1SnRyzE4kRrj0mUa687wvbcfLlnNX3iRO1KublTRwnRnMcey5Weiz1OYTVrngOXdl3qnbfpJb7adWlfsW0yqtd8Vrpzky29jip89MT3D6OpBXzjt8VfAdo0i6kTsXj9mAmX3Nc60fQk+uBc3T+GZR3uoUu+yfxvB+SETWV5f2/D2kf+V3m6ryRtwaVVbt7iev+Sc5a1j/21vQv9yU2Of/rxtw=
*/