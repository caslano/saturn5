
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct times_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct times2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times

    : if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct times2
    : aux::msvc_eti_base< typename apply_wrap2<
          times_impl<
              typename times_tag<N1>::type
            , typename times_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct times_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 * n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::times_wknd<
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

/* times.hpp
due+ILHldEb72c7uyP0uwksTYaDx3Hhr02MpdlwiFYI5pZr8qOMKbAtuT/XAYmd4euwZrfpK7vTL2D+2JHJb4hPazmWMB9JG39nNBCnEZFLK0XC0I/WholvizO5n4rKhmJtyciCZRtxJcCxIn5JBEC5SehsGXRzsRGW0bJJ+XQuogeZ5YWD2Ug2ZTWlCUmZr3svMbUbWW3QRGdIQrPaYzMTlgArtfBJpPtUIWGPrwpf3ivOEg/DUlPDh2B2USdosKHUvT/prWJ9UBcgrci5ETAeY3rmywYgagZI4jk5GDwinZ+AFHUfhN5RkUCnaV5I6ShIvdOOFplB+vHhAzuXNC8rGFQ/EUzWKQP/OAcPVQ5SXFEx0w/z4DzSIrDe7dOOTCtmoETo6HUyxOmwxz8RJnKY+RtZaNRLaj0EoyyKG15ha0zpJY5D4EEwyD8hSTwpo0jRBnD33QjOy3NB+QLpRmIEwe14UMXQ8A8cMc7LA/2/UdPQkBdkfgjx5brVoaO+mfIW/oGWaWbd+EYR25rygBIVDiw9I+5/HwEfhWFM3Cv94JGr4Iwou2D8eb8yP/4T13X9xk+5Cm/bQOIm2wMyefTfNoCIqa/KiN0YfnSyLXzBsA4tHJwB6VgtBhhm66YHQwjbB8wWXPuO1es3K
*/