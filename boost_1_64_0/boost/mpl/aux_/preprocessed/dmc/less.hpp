
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
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
jNTsm8sc3tZa5u/4ErFWZS/wGLZXRvqOYVvS1lrmA9RDvO6DeflIoHGlfxllLXdYtLXcvyJdso3NQGNLY1NVbtOxXqLw4aw2Hqv7YH4cI36c3/YTjG1N+iHamun8Oxdtrfdz2C9V259ekFYwK78wKzOQuv9WEdPb0c5q95+kK1fbpXvxba+V2BvMlylMZDBPYrJZ3U5d1iqlzcDOK1UZ09urj22t0l5gcar9ObY1Fvt8Ykm7Tmmfa4w2rJGmdYsB+yHPXrZ1PynGWvfn4Uu8jS80soB9MJ7b1THWsodhL1lpL/A+7Vu7uNyyJu3kf+G72tVrt4IXx/H/7V3tnzrr7Re/Tv3yyZyYk/+6r2z4R11e+No+/uK+Ztrv5b+f2GlT+o6md1188EdR3zyxO3jvdv953Rq/P7/b6+VuPdZ88eHGUWvf35v1w73D3TlPKuOKDo94Yz0N8dASJF1TRbpRxjV9kq61l/wSkFJJ11fSGeN3vCbxO16HreEbsA2shJfCNw3vBq6SfCYjDo93Az8rcZ6eg13h87A3fAFeBnfBK+GLMAG+BEfCl+E4WAFvhrvhrfAV/d3AMrcnc34Oj3gxV4jdgeL/IBgLr4L94NVwLBwMZ8BrYB68FhbDBDgfDnXXP/N29sepj54O8ZKut17/iKRLVNT/eKn/FNgCToBDYSocBica8imTfPor8kmSfEZLPmNgXzhW6iFZjycn804yH+XwiAv3juTzLgyHB4z1crd9u+xsSBch6Vr7qJd4SddRUZ4y8WMrvAg+Iu1yG+wAHzOUJ13yaakoz17JZ5/Uy9sG+yWid6nC/nDRSxS962EPeAPsBUcY7FdKPu0U9uMln/6wLfyxu56Yu7BvP92N9b7KPl1XQ7p4c79hvyZX8mttnx/no4zXyzg+6Zx1s1P2hzwg8Yk2wzawDF4BH4EJ8FF4I9wGU+Bj8Fb4OMyGT8ACuB2WwCfhSrgDroNPwYfgTvgofBa+Dsvhh/AF+BncBc+EyDvnJe5VN/gaTIBvwnHwLZgJD8Bc+CvNDnwPPgGr4BvwMNwPf63Zge/DL+Bv4I+og2PwAvghjIYfwfbwOOwIP4H94O/gFfBTeB38DKbC38M0+DmcDf8IC+Cf4AL4JVwPa+Am+BXcDv8CX4a18G14Ch6FX8Mv4Bn4FfxGjnMqEiHH76dynJvAJEP83mbwcjl+A2BX+BN4KbwCDoKD4Wh4LRwHEyR/jpuM8VNXkn8ruEXynyL98lQYBafBWJgNu8Pp0r/NgKPhTHgTzIM/g7PgVDgbroL58BFYAHfAQrgTFsFfwDnwXXgbPAiL4SE4F+Iv/Z+M4cvYvuZvD+d5Lv2w1MdEGAtvhl3gJGnHt0AkJAPeBqfAxTATrodZ8GGYDR+D0+FTcAbcBWfCN2AO3A9z4XtwFvwcOuCfYT78BhbCCHwrgrFwDrwM3gYHwrlwCLwDJsN5cBKcD2+Fd8JsuAjOhkukvd8l7X0pfBkug+/D5fAoXAH/CFdKu18Fv4SrYS0shWfgfcY9A2ukH7fp7yUdypLOx/1PvCWdtX/aHyJj2LCbHE+tne2RdAuk/S2SfnsZvAouh0lwBbwZroS5cBVcDO+BK+BqWApL4bPwXrgP3gc/hGvhx3AdPAPXw+/g/TAUfzbAcLgRtoabYHu4GXaEW2An+KDxOibl6aW4jkyS68gtUp40Q32lS33F+Kj/UlM6+/qvtKSz1n81UivpkqX+22lrXyTdd3I+nYOR8J9yPv0L9oEoEj8SwOEwVPqBMPhTeD7MghfCPNgE3gYvgkthuPQLzeBm2AJugxHwBdgK7oGt4QEYCT+AbeApGAXPwbYwDv+jYX8YA5NgrF4fMqY=
*/