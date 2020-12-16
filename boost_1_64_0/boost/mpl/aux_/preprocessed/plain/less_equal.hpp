
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
TXCO5GeubO84DMUEydc8HIGJGIVJ2m9MpVu/udS5pu03ktpqvzEl8/lVM1/RFdYXpP3GlG59zuYr163P6Te6dOtzNp9Phswn7ZW1832s/UZXhsTrYL4Ebfnp1udsPmM181XUcu3bTYEraOv7Sx3DYcJpguFX2sQS0ibSDphgbjt9lPlGMN3chro9B+Nppl1SpvP3liOmdtVJzBOKhZjDxXYXpq1knGBub13GtAHfeqvfiEqbRDw27a8JK+3bYAdjOKGKf/NZRTtjQhXT45mWwt95hPxI1oWO2mmXrLK21T6nzIsVjPtGMX8h5UAIJyQRKknfTiwlxESxbkIK6S0OY/24jfHKQtbJ+F7+PoX+q2kDzb9p23wXVxIXFqy2fseqjODNCStamQ/PMW64zdoufMJk2+9bhWIp1jPUtWknHn0bcWvai5dVmtqMFzL9DOMXlXWTHnMb8jKmR+M5vETIk29jtWe9AVOIh7/DcIuyDv6O5e8cwk7+PkqIYj5zm/MKxo2Me6+lXfURaxv0zowHVHlb2qKnML6Z+fayTDkhlmlVGM48efxdwr9p26kbmb6TZQ4TTvNvFyuJfyjxMV44lb8J3utID54n1Is2tWcPY9ol5j/K3zH8Hcx0I55hfDPWCyddunbuh5mejxOi+bcadQ0jCBsZj2e8kLAtnDSQt724jfHDaFhP2gkxhFOMH2D6MUIB4yksX8m0g+tN7eQ7f0Maoyl3ZXwa6cMQrGCdAcOYdpTtoeuTW99+3nc6yxCCNxCnMn26tS19ER4gnCJsJO4xxBe1wbaNfb0Z7HP8m7at/bYN1vb2BzcQN2VegT4bTe3vO6OjNvgTNhIP048y/14sJ1QQnLXNLyPewBj5bhnLVA0nLv4+z/Qwpgd85204zLihZl1DDONn+PsioUDa8wfczn6P4aht23+KabFYyHQjBrL8Nv6+xPRSPEfwn8n8TPe+w7YPgBSmBTDtYAR5w9CZTMPTjBfwbxvvYN1MK8F83Cx9BZxh/AB/lxMuMu5/J+XI/McIFQRfL/JEiCEYCUWEvYRywkVCgDf/Togl5BGKCLsIxwjnCd616ho6E0YQkgiFhF2EU4RKQuB1dQ3RhHzCLkIZoYrgf31dQyghmuAZPINn8AyewTN4Bs/w7x68CfN/9/b/SUrj/9/c9n++n8HcJoBnAXnGJ3ipv2FJ/fnOpjYBUvFPGsCnZqTmuN/GxVHffv4SX1PCeOY7I/HZVjSk9jDNdtKNrsepr5esrZOtTUeSvJsYK+kYTZhIOgxdHKWDau0hcQlpC1xvMy/psNSBW+9r2y51na9texNGDV+3YB5aVPKntIOQadnKNNt2w+/XtP8u3CTSH+88/elJcUota/fLUhtvtJd9vJHEa3Qar1rrXon5quIdJfGWO4g3ingLnMebzXhCTm6WS9+pu1Lchd72x8gU4i66YtyMx6UmXU3c5n1XaXNC2bES636znh+fU7Ozc839R/jKfNkZmTZp9pV+A6IkzZMIU0lzqcM0q60jJM0cLW4c4/o06+riW84ztaV9/1Cp4zAYb23P74RdHaaHPw0utUMcHWzfNkHf9irXoKaJJlHWNltKnfd09XCw1s9X2sUnKI1eDNb2Gtq205WMb1WOR1lO2+Y7gbXrzzHnJc8P1yDPuAPJMy8YHeTZ0kTPtTYZm3o4y7e+vZTzPFc5yHOlLs8Vuvxp97EQaSh8m7w3yMNpSvunns7zp2+LFWtwvT1Ueq/q26Go7fNSElIzJD8HdO1JSqztQ9VlDjOe0ZTlqOVsLpe9DsrqoHnbL2KiTNsl+1Y6ZWNu/1HBNg8mYW8zfl+Itf3OTk256tvnnpd29qe8mRdP4Aw=
*/