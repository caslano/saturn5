
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
9Q8f5nfVEfIPBpbb+4sjoFGfcQL+5Uu5HqlFGhFv/cih+NnK7f3JO2G5kvf4HS1HH6yHZ5FSJSwSspV6CWOhts+5Dr9kWIa/Fe6D55K4FjYgwcso6236PukQjg/DOBjN+Sx4kuNymMxxNSyBO6XPup7jQ/yuRc5yHLyda3hO1SCNSKd9HU0RyEwkCylHqvb5+6z9zu/8zu/8zu/8zu/8zu/8zu++T/df6f9Pbbv+/wE9Tc5+rSjp/zdLv5baHtvHRDuMq5+crid1brkv/bwyv13Xj9VV04+VX+jWryfxR0v8Ucg1xG9e6Ipf0aP2N15E/I5+03yrSbdOXmrBalm/ztVvit9Yj35R6bcfLv2iQ5G+2Lnf3U5r0aqcbLpHc32f6xmEnlSHnXK8ysu4Ae28/FFcV+sqJ5/ns/bQxCt5pCuTkvbSnyFlshq5UonLntb8nHR7V2d6Rlp+esb5y0Tpex+xyG0NBIO+zgDY0BO/dCoqTrtOBF6M8mi5LoWKEXvE7nuQMdidskhvd0aeYvf5xwxo88ndzi9ddsr6gDKPOi/N0MZmpQ61Yf+sfw7v99sfmq72h857d5r1cMPOAQ89vGXNL59duth7f+je7mo+mO+bfvpgTnRFZO2vP//X1uFt209qNslzW36faKfvnwyRfpYBMAQOhGFwEBwFQ2EsHAwT4BBn/6Q8j2G06NX2Tw4TvcNhfzgChsORovcKGAVHa+ae7Rd9w0Wfdu7ZWOn/GgeHwmhNuFpJXxeDcH0kXDDsBPtKuCykVuJbK+G6wGQJd63YPwX2glPheDgNToBx0Aynw4UwHi6Ds2AGnA1XwznO/lF55sA9Ep+2f3SexGeGIXCBlMNCOBIugnEwESbAxXABXAKT4FK4HCbBVLgclsBkeBtcAX8EU+A9MBVm+TC3rvi+ji3Or7M1/Xfn2O1vav08u5qmtptrd7apbefbRXxx4XPuZn7x3c27u9A5d7uoL4eQOuQsEnh/R1PU/f4+Cr/zO7/7/3Hf6fp/GcUWZSy3/cv/4r79lfXwHuCF7NA65b1JFKOzH/7tScQBrb8lJz9trf1cD66p0p6TQbbDOAdM1eq59HyL9rQln8SxpJrNorY5DNbsOVgs37KRsA8cCB/DrpRp6nfatIXLzInzLelFVofCC1iXbMV01/dmb/mOsyFpOamFhRiYnuGan7AW22z5ru/NP3OcWZCf6/i2O+ZYE0uOa+VYu2aZOt7aVqAen5DzucX288c5PjiK663E4Vhbn+NCWypZbPc7LGFs+WSZ+NXgV6Vch2fq6gx0Xd19rD1dpofx164zd0i+2V/gZB9YBZ/kmtB4TZ6qrTjOTFXzNK4VefrsDN/zVMkPqqx6HCh5nJrue/4VECjTJPnnlp/HfMhPo7zbarffVOmWd6UdZK0aaTfYi6xX2qBmGuSdmk5f5sJc2v3dmb7nl5of6fbjs27pa9bVDWkDkTxKNWnTgpNx8lch7eV7rVqpB7O0aWH1Rkc18KG9yNFO9WcpQzeb1fgnS/xRMk4+k4RfDlfBp4nfahQ/Czvas8GXuRCXdj82+/z5Ke0zjra9HG07krTtkauy36jUBcWMzKK8NId/sNxfPIF0/iFyvVIT5MRFl1eCvC5Xy337IHwGXVFztPmFhW7lFevjfdu7De/TY23wnDO6Lw8kGN+XjZI3R+W+PIw8yzXmudq8KXTVZZ/mAZEf2nS633+ausI8FCk7Rz7o22STJKJgudd6IzYCx85T7ZPZUWyh48M95mhrVJ97VK1CiSvecV93RnA5khdZSCPXpkhc6suCxRFlak6O5o+xzcd80aSTtLTvnkyAc8gIjjcp8RjUd2zUr4codk4XO6c=
*/