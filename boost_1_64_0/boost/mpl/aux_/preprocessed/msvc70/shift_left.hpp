
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_left_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_left_impl<
              typename shift_left_tag<N1>::type
            , typename shift_left_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_left_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n << s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_left_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_left.hpp
MRzb4yR0w8nYAQ37R0Fpk5O2uiR0I5aQ57WOMF9JPIEOmIL18TS2xM+wK17AoZiGAXgRp+AX+Ap+iWvxK9yBl3EvfoN2rPwGlseb6IzfYwO8ha3wB+yGP2II/oQzMQPn48+4Gm8r68E7uBHv4mG8hyfwPqbi7/glPsAH+AeWI88PsQb+iXXRpjD5wMK4EO1wBRbBTVgUd2ExfBtL4IdYEs+gPd7CSljYhnqDz2AVLIfVMQRr4iR8HmdhLYzF2rgUXXAt1sVDWE9ZD9bH09gIq7L9mqIrvoCdsRl6YXMMwRY4A1viPGyFsdgW47EdrkA3VOpHRkFp15P2viQcQrwm9eOM/J58gmXxU2yAn2ErvIBdMB0H4GUMwSs4Bq/iPPwGl+F13IE38AB+jx/gT+igbF+siXexEd7DdvgreuC/0Bt/w3j8Hd/AB7gH/8B9+BAP4p94DgtwPPgaC+K3WBzvYAn8DUuhrdJWgMXQHu2xNNbEMtgAHbAZlscYfA5fx0q4CyvjWayCaVgVL6MT3sRq+BNWxzJs1xpYBZ2xBj6PjbEWtsA66I4u6IF1sSfWR39sgKHYEPXYBI9hM7yAzfEnbIEllXqBjtgKq2JrrI1t5DjaFntifxyIAzAMB+J4HIRTcRim4gi8jL54D/2wsdLuja0xANviSPTEYPTCEByIoTgew3A6huNSjMA1GImbUI+/4gRkn9RNxM44CQfgSzgMJ2MUTsFonIazcTrOwRlIvadfp7RFShtlErYh3pL7hl3kuNhDjoteclzsLcfFwXJcHCLHxaFyXBwmx0UfOS76ynHRT46LgXJcDJHjYqgcF8PluBghx8VIOS6Owak4FudiFL6OelyJ4/ANHI8HMBo/xImYglPwIk7FuzgNdQUpDyyCs3EwzsXRGIPz8BVchvNwHc7HNzEWd+NC/ABfxZO4CK/hYvwBX8NfcDm+aEMZ40Bcib64CkfhGozBtbgIt+JK3Ibv4HZlPbgDT2Aiss/p9mA93IsdcB9OwbdxDu7HGHwXl+BBXIaH5XcxSSftoNI+moRliWwbQ+ikHMfRAx3RE5thV+yPvTAcvXA29sE4HICv4yDcjYPxFA7FaFY2DOtQLr7YD/1wBvrjcgzEVAzCoqQrGMtiCLriaGyCoXL8jtFJm6a0dSbp5F5x5ruXpV/jGXTEVKyDH+ML+Al2wPM4CD/DQLyE4fgVPsfCv8YUTMdv8DI+xGbKcZv1tkLplyhti5QdMcmsX+J40l0SJ2J9nIQdcDJ2wimSL1edtAeikyzHhugsy5nOfDY4A6vgTPlegrJfy/dek/26EXGJ7Nft5PfMHcuiBzZET/TErhiA3XAadscV2AP3YU88gr3wLPbGT7EPXse+eA+98Q/shwVZ9wAsiYOwDA7GujhEWS8OxaE4DANxOIajD0biCByPvhiHfrgT/fEDDMTzGITpOAqfYbuMxnYYimEYhqswHE9hBP6GkVjHhuMNdsco7Il6jMbxOB+j8TWcjN/iNLyPM7Ei5T0La+BsrIsxOAXn40KMlXrSQidtjtBDtq8tsZ5s3wipJ5FYGcegJ0bJdo5XykS+7yzb2VXV72OS9LufgU74MtbCOdgS52JPjMEB+AqOwPk4HmNxAS7EFfgqrsc4PIWL8CtcjFfwNXyAS1HZX5Zjc4xHb1yBPrgSA3A1RuIanIZrMQYTcBGuU9aL6/EIbsBPcSNexE14B7dgabbfNmyA27Eb7kAvVPrND8Vn0Q/L4Fh0wPewLCajIzqwHcuhM5ZHPVbASVgRT2IlTMHKeA2r4AN0QqXttlrmcy0FpM1R2iKTsD5RL9unrmyf+rJ9Gsv2aSrb5wV0x2bYDVugL7bEaGw=
*/