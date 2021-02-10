
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
wZLOoJT+qVOWO1fRhZMJkVY77KWE98LlwFNQOgXqCESiD0KUmN2OvFNGUY9q3+6M+UDfbWWMBy2mFGK4WG7ih5UctmCr5ToWoxC6zp6v0++RUEf1Besia6B9BajMYQ0ux641kCsLr4gaPJsb57Ho0OUSRFUbZxJTThlNDlCNb/8QgtNcDNjCWCfhP2ID9psE4HdbokLy7+tSDF9m683D8nlwbKCEa3E9YAOifCkYiTMLcRnuv1BLAwQKAAAACAAtZ0pSzRIm3XADAACMBgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMyMFVUBQABtkgkYJVVbY/aOBD+Hon/MKKt2nKbOGGvlYq8kViWW1Api5bsSVVfkAmG5BriyHZK+fc34/Cyd907qQESZ/zM+zyGW2lsKoyMPZ6Xa4WPb3K/U3plYm+UJLO5u8PtMPGSydyf3888zs4Qzhot7xnMpf4utW/ylfS4llWxx+2VsAJKlWYy/XbV3kvTbsyyKAihG4Zw977lDVRpZWl9u69kD6z8YVlmt0XLa3keHyUfJjG/vrv5iOYGw2kyvI/5KIqTLDeAXy4g03J91c6srXqM7Xa7YFPWgdIbZtTa7oSWDAW2QN+3ZY1ZcCZiztAGZweDHjqq4rk0
*/