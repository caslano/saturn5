
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
JHB4OY7nN9uSN29hPuVxaCt+ZyHjZHKaKLLi3QeZ++8yIpvO72r8egaVheCqG80cp0BVN0I36uDfjjeRxV3T44y1bZYRh1ChnLp3aWnoo7G9E0DVDeQzIzkwD/KVK5/IirKvj/F81LDKpqDbeIMWMD3YtKJwzuilLDEQRbRPTShjdeJYAN9Ugj8wu5rdNKcBn9712wUYVsJEYm58dh5WppYldwLge02RldKnKgqd7Z82NPQX6hKSrK0moPhlY64FlCY5OR5cJ0oz7tbXzqZgIPGk/+tKoeRyWPcwjX1DX1nXmze4Dldb6VbHfpf07Cn50rlT+ab95GuSQwQHHalXEgq7t0QE1soITmD+UqwcODzmKjQASJMbmSDKxHLSvqyg04m37fjT6lXIk8H3bbd5Jttygp5iPrOhfMqli6101VtFB9vTXAVIO5u3ooYQQc8hihKH7bEY3Mu19M+jktbNHrPhX5oouN4Zo6VjSnFOxo3I1JlPx3zZxh1FFEqVFgSf59FT+xzj0Wm6Z4Dl21H9M8Qi5zZvEvR/wN5rPiAKwfm6ot+FNtYd/ayoCNM9YAZOsuFtRhcx+sA7oplFx6M3Q3I9YnIkxAYctSnuZ+64BGwm2UZPJtfRhyS83meKi08qXyW6puIN678hL3v6sWKJdJdrHf7hKXkZTrmh7m7O5m5ds20vbOpF//2YRzyJr5FXezWQre/GCtv3e/hz
*/