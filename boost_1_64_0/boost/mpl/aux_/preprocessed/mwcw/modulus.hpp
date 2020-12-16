
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
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
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

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
f7brm1YB/uP+qQn212yJjQ/7c8+2u26NYnznuQL4VGbjU33v5Xb+VBdEOX7PLNmdavvTDX8qbPypzz1evgR8djrJMzbQyf47rsrHD8/dOvR7qt3zw4DOej+5bPWSLcczhq0w29zOzqrOfmOTspPqY4fq1NPOHvadDbimzn7t3H9ujZz9mr3/vzVyH7jXyBXuevHYiRXbn7ypU/GDnzz6Y3SgNXKB8ng37Fq4ZIdiivQ7rbKR79qZh7R2Zg08HD5s5g2W3uE2evuk9yt0x3Z49RDpNbfRe1Z6G2Az+JyhlyK9WBu9rxuhB/8GY+Au6NGbHMTPctl7QX6+aNhzBtF7VXqvSW+LoVccRG+b9N6R3ruGXkkQve+l94P09hh6pUHO307pfaXz97WhVxbE3k/S2yt7Pxt65UH0onUeWkL3eJVxHiqkF2Wj10567WFzGG/oVQax10h6jWXvEEOvKojeN6rft6rfd1B6im3gXm2j96b0KqD7/S1GPu4E6R0jPTMf9/ta0/URjNVavY7wr7AzrDTsp6qcGBv7n6u+X8Aj4ZfQ21+D+P076TWFUbCZoVcSRO876VVJb7f0FiBl0ntVepb+XOn1UH17wTjYG54I+8Ah8ER4M+wHV8D+WpM4EN4LU+D9cDB8Bg6DG+AZ8M9wOHwJjjD786OBz/d9Om/363yvNvtzEL1N0ntJei9Lj+F2zVFTpvSiYK70Rqn+o2EMTIUd4NkwCY6FE+A4eDEcD+fAc2AxPBdeAyfAUngeXAnPN6/7ssB+l8nvx+T342Y7BdH7THo7pPe52U4B9TimfhIF3XMV5nVfFvh+31p6sbAZbCO95Uil9HZLLxoult6Rat/W6l+x6l9t4HAYB2+D7eAa2F79J1795yi4CXaBW2BX+AbsBj+Bx8LP4HHwa3g8/AYmqj0mOjQHC13yrxkcJf8ukH8X6vynw3ZwitbAZsBxMBPmwanQCQnoVP01d6q5VP/6T1f5+TAeOuFlcCacDy+Fi+A8uBReq/a4Xv3pJl1ft2lN9B/hc/BOrUm/C26DpbAS3q32WGneJzU/2NnmvD6lfvQ0TIDrvHrIU4G/xz9Uf/gIxsCPoef+miq9GJv76zrprVf/ewa2gM/qPrnBvE8+Fbgfb1Q5m1TOS4ZecRC9P0mvXHovGHrMoQW8n78rvffk53ZDj3mvgPflt6S3Vfflt83rLYhepfQ+kd6nhl5VkPq9Kr3XVL8tNXqc5MB6HaWXIL1Ohl50EL2+0usnvf7SG44kSG+I9My108N03s+AR8MR8Hg4Ep4Kz4QpcJR5XlVeexs/zpIfY2BbmGqenyD+L5XeTfJ/maFXHkTvEek9Kr0y87wG0XtQeg9Jb42hVxlE7wnprZXek2Z/CKJ3r/Tuk979Zn9YF1jvFundKr3lZn8Ione79O6Q3gpDLyGI3kLpLZLeYq8eEkTvBuktkV6JoZcSRK9UendL7x7ppVoivUHSawqHSG+A+u2psCscCI+DKbAXPB2eAgfD0yw9ldsPKVO5rVSumaNikvy5QNf7hbAlTDP0K4LoXy79K6RfLP15hn5VEP050r9E+pdKf66hz/huQP350r9a+tdI/1pDPzmIfpH0XdKfIf2Zhn5qEP106U+Rfob0Mw19ZxD9qdKfJv1s6ecY+iVB9MdKf5z0x0v/HPP8B9GfIP2J0j9P+ueb5z+Ifp7086VfIH2neZ9YH/h6OFb6x+l6ON57H9c4Hehjcx8/QXo9pJcMu8GeMBH21nXRx/CD8bgAvzOhyjsaNoPHwLkhvudnzfraeSaUW8I3r0TwnBLkkgg9j0SMckeY7+nxzx3RB45HlCsiYJ4IM0dEFIOMwd7Bs/y0wHk=
*/