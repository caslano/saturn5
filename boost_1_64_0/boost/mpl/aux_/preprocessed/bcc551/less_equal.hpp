
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
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
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

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
6zGXjPAr9kd2jZs8CzY/tgw/16bHZ/ojEpNl/2UopfxhaO+R7+vBM/sYNl/vpEr+f4x3t7fFy4hlxrJi2TCY6A08ubG8WH5sbKwAV2UiaLso9picLO2DankSWHsBLsHLfm+Uuh/AY5eAa2LhbPbQFlQ6OqP0+Q4cjfPpbY/orXqb/qzBm5asPFzK5eRIE86t7IA8Jtp7YDwvfi5sZqZ/D/rSmZxD6ZvQ6HIPy5yOftbx6rnqNcw3l2TvTCbm+0Z/EJhunUC3/MT6nt3ILhvjVOD/Ou4J7mVeaywrfnX8Fdy7MDgV7X8Qio2S3Vcp52eNdce757s3uGvRpbbQ7Y70xtIDriEztF/sUO56buz62D2xNZKTzokfBrt6FidQ8X3/CJKUc/zH/af8X6EaXhpcEdwGgt4O2xsYOuDKSzlh+UhoJuKJieDnh8BdryY+xU/tq3SIhmCpJ6rnq79Rt6H2jWJOXwDzXU4/+4hdeIheq6+A+X6o5xjfgyNONe6g6tYY7xpTzBL85Tthv++Ze8C8J4E8Lrdus7JwNRP2aSjat5Pd2QiWynI8+vtrzI3fOZlyhu4SMlPNoOptpFdvpIs/7DVLYk2NjQM9Lojdj1N4DFms6fF5nAT7ZfzX8X1hC8fKafE9g+7BcCZYRXAN9fk03W4vTsInQM9rSLUoCR8P5fTEbLybJ/GXPser7Ss64CXqHPUWtR6k9Du1v2Zqpdol8MuH6HAOaOcC/X59pf6S/pGcBxhnTDPSwj6hGo4LryMtcz+zYu/EfrhWRyfW4EV3iJcard/eOPL56lQ62mp1jfqOqqAcXKXdqT0J8txDH6oH+kyp5cd1Dy45iV76CA7mRniHbnrUZhm4/XPwqGGdT50vZB78BpSdbo/C0VtpN+MLH+KoYPhz8K7vd17AZzzLne5eDwJ4j32S6h1MurvEu4pJmB0bTn1Mid0WW4Zy/racLAjjk0A97zArBsPBi/DjbvFf9Vv9z/1+uBa3BvUonb1ALxaa8Y2oxg+FzeHxiQnkuasSLyZeTvqkRX2FY6Vxl8er02A3+2rp2vdB6NewT+4lC70nyuFwPQ/m+rz+Pup6wjjKONO4wvi50WS0MfFnm3NR/Fdzl4o12Ipxl7OtW3DnHVz5U+2Z9iPskxZQt+a4zkmco+h0PgOvaii7Ze4CdwWz/xPJTiT7f1/RburB8q3G50yko2BAV9Ah+zJPjwfN32o9yrnVKbCtuSD5DvpPDxjrKlz/jfxU3z3CLcIr7u718kZRXzehTq6iO03BM74q9lNYeydd9dD4I+JPb4/vqq0eQe9gFIhpAfP1keDl4PTwhzgcd1DBW/FdDoGR/jzxRmIH+K8vXl2UQZ6iXg5aoKJYqQWghEfo60V4Aj/S72CVfqN3x21fKWrWdsM3j8DfnU3Cdn95V/CN1mLc3Zdwd6faV1BH7ahIqc4wcNFj1NE2J+Yehm93mXtMeB7TMY/TDjVopn0jXY8qSuqSSnNfmadbjUnWESTj9qPa3vSeRmGv8i8JJodHSu/uKxh5pNoHpWuTnoUnUGbf4ax3v/BGxE/yrwxWhK3Sq/uKprivZjN1qzi3ebTzjJuIPRF3godFs+onv3u0ep82JKGSV+knmuJ01OX18c8ifpHdT2Z9rnW0paj9ZI6H+rX4MZuNJ603mN4m0+lCFNMxZPgmgf6WuG+5P+BM4v3hGtFD+8mc6aMWo1psRjVZpv/WmIRiG9oaWdL5pDk+dX8ILnwS9NcJQ//QH4hfoxT0k3l2Ngy60phNWnZv+tHxqBatbmkswambC/zr/OygluTvLFChUtRPfEZD64F3cz3sZxNIJpuddgJnrY/H+7w5Oqkb+Y7OPu4=
*/