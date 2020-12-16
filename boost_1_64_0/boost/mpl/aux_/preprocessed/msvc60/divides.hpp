
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct divides_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct divides_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< integral_c_tag,na >
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

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct divides2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides

    : if_<

          is_na<N3>
        , divides2< N1,N2 >
        , divides<
              divides2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct divides2
    : aux::msvc_eti_base< typename apply_wrap2<
          divides_impl<
              typename divides_tag<N1>::type
            , typename divides_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, divides2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct divides_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 / n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::divides_wknd<
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

/* divides.hpp
rT7+ReRPkvxGyT9F8ierj38R+X+S/D9L/l8kf4H6+BeR/7rkZwXygxy/iriFdYlrL93vEFSxRDWGSfyQKmZIGy/kInFCGzXxQIdJPqYYIIn/IWljfeT3AdY4H0+J51mvieGR+B1t7I41ZsdIUsfp2MfoFMbkZDmIwTFKrM0q4muySMdIl0gN+ZYSRIoiLSBtJh0jFZDcK1RyCSCNJ2WQMknZpFxSlYqVXHxIoaR00nrSAVIuyc21kktbUjDJSFpF2kFyTs7JOTmn/5bpljz/j4+NND3+v8Hn/834/b/y3OL8I8r36ijDpIi0+NQwyy0OF1N8wKfsieUZfYg8o/eQeyPupG7KPZrV1nsjyljYyeYbvsXfF7H5XX4R93rvlPJPSvnz0PQsBbsr92as5ZvDA5Ryq5SiXIlLUI1N3aPOt6Zt8l3D2/b+UIY8vw+QNuhGuot1QtZY62B6dD8xOTXMNB53KdqhSX3bdujBdqMSjH6q3xzIsinWZe6yLHZKgnLZYxNTcV4nxuFu1s3U1NWQGB2baCh9PdVlpctz9zZSVitSb8rK0pQ1KWJialJySqnLul3VJka8XdUeUzTP3Gq76R+jXE1duH9+Q/VI1NTDIPPuMh+luQedKvVqKvVqImNN+K5V1ytMPogy5EQJ7nOqj0OBlNFQyvAg9VE+I7ZlGNJNT+KK37aj/Td9VqLSbcoer/Os/h7lZpW67FLsl7psTns254KDUlZzUk1p077Ks9zCsnikWvxzQstnv8Ddvk+Hy7P47XK+2Yr9lGcYNmXI/pTgmaTyLouIdeTVvAelBRcx8hm0rY8h1XQuClynfy7KkfrdQXKVNuiv9PN11vqlGCamJcemTg+LjE1NKck9c22bq8ubIc/sn5TyVpLupbza6wvLK+u5T/s34C13+3Mfy7TnPpbpn/uqyB+AGKnrJNIg6pqjqmtZzkfqvxlST/X5iHn781GmKgbAlTRX2i38mcK6lPZ8pFePRE09VOcj5u3PRw2ryv0OqVd10n3K8Xy2sF5lOR9pYyK0x2ajlOsp5TYmBSvPnFTlluUcRZvonaOkTSQGITnapi7e1TTvX5DvNCGqusgj7FJ9fhx+p9G0xSkpf4ochwTS0H+zdzdwUZR5AMdXgVJD84U3FRUVlXxFQsUXFBMTCxOUjJTiXSF5WXlRTDRf8CVFpfI9Kyor6zyjsrKysrTyyjMqu6ys6KKyO89Irei0ut/s/nd3dpmF3c6r7m7m4+OXmZ1nnmeeedmdeeZ5hvSNdum7c46x7+tI0rduC/UzD6ZpRRw78ptnK2nKecY0/o5qXJ3nRHYUUxwpM2/CZOYx2J4TLcosdL3eX3XO0S4zh+OpWtJfIGU2T/qHCrKlX2xMLsicKWl7u5C29m9BW51cpdP+bJy3SbzSW5k+6vuQPgnfla7cNWF6wMmL19zifptK7bo053WB2nVyzusIHzEtv+yhO9/9/LXQ0CWvTS3JXvvgSffrArXbtP7n39fwiSn/RZ1u/XZJ/Lbpy/ted3fb8Ja1Tus+3X6PwyLTdrzvsW0vvf36nPoF7ff69Gvx/ST36zIHDlSmD/SOqy0IeeWHU0l/NvY+tXGEs7pM99sCW+uS5NrFT9oaq+tMesm97d7og33wNNYQUiQe11fEM/f7fVTiLZS6h8X864BLMACXYTguxxG4AsfgSszBW7EEV+NqLMetuB534234PN6Bh3EDfogb8W+4CX/AzdiCfG1Bf9yKvXEbDsE7MRq341S8C3PwblyK91jbsMq1GkZI+ajbsHaW8gnElthFyqkrdsJu2AuDsB92x6HYA639psvyL9Eo/3BZ/hBZ/lCJF0Ooknh9JN5FOEritZM=
*/