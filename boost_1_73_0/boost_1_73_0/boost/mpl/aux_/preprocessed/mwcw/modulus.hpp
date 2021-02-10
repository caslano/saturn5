
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
lzLICasajaCsCWiCB1/bvS5Bdh1KB9YohMo6QKlq6JFEGsuGalWj2v2a4l/Bo5+TEcFPs6GRTXVDDKeRqSEggB8GSZZDR+ifSARr9YTpZnt/d0v3MQRhZIvDO0H/ROApHLrC3jfmAxx6DFBLU2r0sMVwQDRRW3DS+AodkfDIAkLZtiXs0PyB8/HLIi/m2cOY+LPFsuCdDDWPAs5QOp6kk6U1uqY6Qm8YZBXQQagR+hUjEb0A6j6iiYURE58Dlgg6Z4NVvZ9Vni5BGmuOrd37pN+9HEjLI37JttN4Q13pdjNL2HQzg15OwtIsXyeseMtSmCcsn7+nQBKTYWfjKSL+KvO6mhcJ2b7IFvzshV9+p29QSwMECgAAAAgALWdKUkFOIp2MAQAAsAIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1MzNVVAUAAbZIJGCFkk1r4zAQhu8C/4ehpeypVSDkUoRpSbw0UKgbuyntTZHHa1FbMpbSNv9+R1I22cPCniTN5/POSHh0XkmHORPatJaODzx82alxOftZl6y8r7ZsU9QbNux7r5ngZ7/gKYVdQoXTJ07XTjfIxIRjfyB3I70MUelkwsUgNTQ5VSwf3yDUhcViBr5DaHWP0Fh05ocH/NbOH6Oq
*/