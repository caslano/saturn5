
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
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
019OeG/R3uLvJ57bsQ2ZDmkL5JpgbIMhtsgwee8aDnuErJ2eCEfC0XAUDOirC6MvWfSliL5U0TdI9A0WfWk6fU1h9PUTffGir7/oSxB9iaIvCVbZfD9MbzCvL96MGOeUhc4l69p3Rl/Df/d7o8zPUr4/NjXYe4c82xB+jMOog/+e98jcg/beJY3zpDr2Trnr4H/uOuLHD6rfLU8dtPd+Wd/AnB3kbPTdMrpFt+gW3aLbf+H20bz/87baReP/k/E0sN79Lnn3dst38jLkV9r4/xt5ptav/z1vac7y65yFHpc2C6Bgk3PpwrmOCNZL+FQy79suh2EcQHlpkf9dOFZ+y9wC/754qI0BKNjkc3lFT5Icp18jeAy5oFCC39Fvi9PslPs8m4zr+m+W9/p9ks+9yK/JZ7aznXwum73IYWPt4z6O8+Ne8etyuDwe63wvaPW30/kmn9qcCUMeS+QxqlbyWIO8QR7T89rJo6/K15FzGejH0DJSXOoqI/Zpp/NlfT6NYxRek7z2l36afshvyGuzOq/ayAhtSWrbfTUf+O0a+6lypALEi82+Wp5S+Cff0iZZobcqgn4qsWvokzosdi8Suz2QE9hNU9v1umysa66wFyzballv/w9Sj95B3tLqkYU9KVvb9Ydz2lZ/FHUlVlFX4kPqypngPCHjOeou6/B7xfcK5CS+5xVY+C7nyM765m3+K69pwzmLv1BiB8q8qufhO/jREupHflGRU+q3Zj+lnTZmX1GwjZGxSIa+zKBPH+h8jA2UXUWhoSzJfPC6u7sfv9c5DGVbHpyDJWVdXmiao5XA79PB63Sj9Msaz0mSVIoCOSc3Iqe0+uSyKgu5wdhok8xl0LX3mJSQsktrKzvTWj/BtlnRdqT0MJfBH1BeH7YMuPl0sgy64n7TVWUwvKe5DFq0elAcrgy4OXWwDLr6/tTZcpgZqAuyfn1PaRsugH/W6kJoORS5ylw+lzQP7bcP7V0L+K283uX6Dfp9Snf9J+iud/83II9rA/81tsFy3AndceUu7bQZ871D8p0q97Fk5C9ahkqM+ZZzX1hRWe6z840nkO8vWXzTSZL18qeL3anIX7V6F2qXO7bfto1vXEGb1mVtqPtHxIdZUvdnIH/Dh2qVD6XlRa4qaQNt3Jf6RtgGluV7fe4Kr+mZS+/vLllf/z7x9x7k7/jbbOmvsb3q1UF/pb1S+WvrXnXaou3J6SOxrSU/VyP/ID97ShX58VF5pfjtPPvbKf/Afdg/zreyWPFMY30uhss6918W37+AfJDCPzdZ+S6noovOhV3fpS0IPrv/kfTag2Hb88DF/vzsv9j87P4h+WlqzY93nTPkMU0awvBtQZrhGU3qiOE8lIb4MVc0DRA/EpGP0Ti1WPlBRfcyF74zfmh10y3j4WMDfhVVtbaT4leDaI4Tvy5GxnEzil1n5Vd55foIfBqDLnzS26RHwXxOruC4dEubG/LLKl0R29SfD/Id/e4d/e7taPR/9x6T+43Dt25yl3/sgzeL8p99qvLcfvfOc0gfGHTLd+UeMCcQ21diI18EU2AvOBT2hlNhHzgTxsI1MA7620ZYpovRvcchfVBwn9iJgzvEzgCxkwKTYSq8FA6CY+FgeDlMg5PgULgYDoNL4HCxOwKugyPhJjgK3g4vhVvhZXAnHAO/BMfCvXCc+FnikH4kWCt+9oSrxc+/yHf1v8FB8AwcDv8O/fdauByehavgP2GlxPS9XWL61mgQexlIs9jrL/b0473XSGzeG2EP6JRyyoP9YH5Qj/TPgHiFnlWi51rRkyt6roN94fX6WOOi5yLRo49RWyR6XKKnWNLt0tJKuj9IOv28gZlibxYcDGfDS+AceBU=
*/