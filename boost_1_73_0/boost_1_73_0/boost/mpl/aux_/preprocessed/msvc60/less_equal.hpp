
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
AAgALWdKUnMjKReyAgAAhgQAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzNTZVVAUAAbZIJGBlVG1r2zAQ/i7If7i6FNpSR0nWldY4gZB1bVnbhMYtjHUbin2JTRzJWHJS//ud5LyMDQKRdKd7Xu7k0KA2sdA4YGEm54r+llhvVJnoAbuPogkb5safrmMW8kMg5E0uO2bHMMVyjaWvswRZWGKR15SQCCOaArzb7kKv04HxN/ZFGAwgqvACOjfwrNYU6Hagexlc3gSUcvcUsZGSBqXxH1EuTBrAlT2RGJtMyQDiXGnc50R1QfUMfhiemlXOvlZS1n6KIgmgRk2/Hf0A0m7fk2qTYontuVLBdde7gEr6S6l6vaON7HvBdc9jzKegTwobBSHfKnJSR3lmYRupsdtQyhyFqUokXxKcVQsmCFI7xw6RUDuXBiw1pqDIbguhFCsyvxClRshkrFaZXMCWNQiZgBZrBKNgnuVI+by5QAXJgvWAWK3EEsFB+3FV5iDiGAuzr6EICIpcZBJcQ0evL4+/h4/R9G302x70vRpF6jlSTUkIicaKsBu6Aecn9+Np9DAJTuyFyfgl4p8+X4Hvb6WCl6sFpw2tfYrYYvsStNw65Tx8wzKb12DtBTE3xM2kpI/G
*/