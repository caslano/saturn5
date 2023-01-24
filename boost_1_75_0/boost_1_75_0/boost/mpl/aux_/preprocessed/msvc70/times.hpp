
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
    : tag< T,na >
{
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

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

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
S/HywwTZ/IL/qRHsc3yl95EnMqvhiKalQaHaKU4Vs6kRfixB7CVD9MeoW1/NkMOCDZ4jWrizx4R5dvHxnxqWfasUl0rLPUkuT5CbIKIIl9KM2Obq9mW9LSe/F0y8sVHrKJULcgVumQSisOankmE/PKOlOuvRwJ00xxRGVEqG82DQvZegn1Q8hqQCh5riLLUf6pevj2Sfu6cXIENvEjvsriLxYQ8B3vJKIQqCVJPftJHg/hzmm6o+7guLd3Bewmy0HVn499tgYefXYPfPsqUowpJ3B8+nzrb6nROzgPS6XLc/pcmMAB/oP/BnE/9KxD+vdblQpnf7bS9RmJGzdshNkV43jY57L9ExeKgg4J1zHc/A8EshWwkHNmYfzNEsiyYZeZDUxfCn87XFfnb+FwEdxVLMXzwq2cZf1g5tnHtklQ6EKrGvwmhzFYclvfWn0s0ToGqv6QmvP58DPpcKq/Bq8krZV9H9inP6Kk9Oz9BW6sSSXtf4yaS+alDcmD40BS/GKL1MAd/wVzqXSW5eRXHNVz1OPP8sJRXOeNrJrHtJfrlzhyNVHO8584OxK2qshl8Fv6UaRr5EkTbfj0+hPczIpOwVkNutn+Cc4IIolMSFP/ZjCyCK3jSL4E/1mTlRCH0wu7a9Zm/YZ9hJvMYXwEgdKwCGY/pM92s0nG+Hs80g3PN3vTf6kbpD4EUAC7V7O7+2vEaB8kGRu9CAGMB3
*/