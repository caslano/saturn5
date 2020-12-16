
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
ZUxqGksjGCoeFSPxtKvRDZNzjFV7mmh/nN1kFgddOnpm9SeOjWjjHO2Pc9AB6cZs1nsgPgtXMJjZ8pLpbAjHuhOCQ15hiwKsEhtNZhi8zJeSpl5Km2O0yslT7HfTDgyJj2Sa0AtnOK3mizu0qvZ2qoLU8Q9QKrnEl5bt2NUSZrZ8Tx5LiJJH613sjMdSIa1CsoiLblDZiJrllK2+FJ/ABd8iBYWKEpf45Nvhi0qDybkbGy2FZb6scrdNMim+OEktM+VpZPZscU20zUTAovlepgxtrPIUmynVbqHuNGCX46q+tpCXq5JHii3kGFVupfohrrRAXdq5xAOQ+WDUYh2V3F8z5ysHC4FBwSGhffv1DxsQERkVHTO89uEAJRUBJSYJVZBY+zBswQV17m9ieFpnP9AkhR+28Qyj5iobZOuyosz03Vt6xlgJCkfPfUbFj4oRTLm0aSxJGkak8g2VbJxA66CN5Id48opYtiPALoZZl3Q7bHZFui2TVXtNVJtbEXDVylxS7xr0lCxe4dm5O2Xo6Exo3dAHZVTusFtCs5mpBj8IT+lW645MmJLq1KYUscrhaHYdIBanMq1/Wv49HZmmTYfV3QC32Vc92PYdHrZzfyTTuqc19WLNAEo0pYZgpEGyiNcUUO38SWNn8lajPypx9uUSafKKfPyB+zxTQQ3uaS9GrilXanPQRk6kLc4a1apRpsmOFl21+sjWFZtr0F6te2o5Hdks3Ta7w7n7apErGiet3CZN1Kna0KiI6uECWLL591DkgRFUIYu+DUyXYq/TPTepK2VM2WhndfX00ewA90fjKcFZ+27Id2SzaYvp4jpkcsnMS7HXStP2V/dHIWv2pFTzxULNZzsw6Bs38hYfVbZp93BNdQ9tvCdu8T1IfCZNngOqRToQuCL+msOEu+rhki4gwLxean0Q/BkGgJdrsE1G2Hbl903ZmuWC6UJtteWe6RePgzCYFXCqjUeRLPLLlulPMxkDBKvZZJBOEBCtxWCFBwwPRIs3G6hANHkVEYIlN8eO0lAZl1xAdfRHO3G03qmvB74V8hwHuZP40Tls1TtCkqowy0IdIaf7nISJJmXhpAyPEkL69x8Aw5HmXmgHUKbdxIANNcMCBgRyuWb+Rt5vCD8OmwktcI7FTBtj6DIVsAqqwQn1hxXVznrVeTm5+bnMvKA1Bey39qtMyguVZaYmX93+U1PnDGs0cdbw7SSqK1JtjRf79DyHgY0pa+NP6xg1JWm96KZ6dyWZyRIsFit+p+bnQDMiB2o7OnbmSXlAgNIt8RWdBs2BETW4j4mKErLy0UFzLpetSxOcwq3kX7Yv5Uf9E5JSq8dNmyhZ0EJyr5CwUHGrLX4G9+2nSGucxe5wdtZGDOuQsl2f0FG7Rhif7FyAiWTxgY3NoiMSY4S0BPRM2T5cm9HOw41RlTgrQtYwTjMZJsv1GFErN3KpaTf6qZxTmqmoa+zXQgnpBAbZT7VWgQZKpFXO3mGlsb3DooFnTadN2QwK8cYGdSdIaUiNSrOj9vJpC4sGT6nNZCqusGrNeK/W/fPajQWmhijHbcm4rbgLcZfiZger1atbeGwD3D32nuUBfIYMEYKEbt3YPrReQ8FIrzrahYnAIN/3CmOokMOCyMGPQPbDbmd+A+/lz1l8g8X4/ji9Gq9a0Kx8uZ1ep70K5Z/MNe2Nv+flVdRR74zvzm4KozbhWM/5/kvCWbhccBqOC27XOoSz1lk4FIZbHcL5V13Q4PQsGpvz57qPo6dac+s6Z5BlN9X5XRiDg7r6sVsn55Af7XVihXSGo6tCJ86DN7Ot4vvvKzTnYOJZGw6fz0aONO8ZFI4UvgL3+FY7E7JsJc5/7M3PX9Q=
*/