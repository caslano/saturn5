
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct modulus_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus
    : aux::msvc_eti_base< typename apply_wrap2<
          modulus_impl<
              typename modulus_tag<N1>::type
            , typename modulus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct modulus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 % n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::modulus_wknd<
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

/* modulus.hpp
Ez4O8+AWWASfgL+BT8Jb4FPwfrgV7oZPw3fhM/ADuA12Qmc97AqfhYnwOXgGfB5mwhdgAXwRlsGX4MVwB7wS/gneCV+Gj8NX4BPwVbgDvgEb4C64H74FbaT7bZgI98BU+A5Mg9go+5/JWKA8cxt99j+byjLJCHgG7AOnQe13+5F0+d0x+V1PuFd+N5NwHeHZsCvMkt//HCbD2fBkmA1HwnPgeHgunATPg9NhDsyBc2AhnAuXwXlwBZwPV8Hz4dXwAngTXABvgXnwt/BCeB+sgHWwEj4DHbARVsHP4TLYDKvht3A5lH3IZNxM/MO14OutroVw41opPubUcOY+5ig3Mv4D/yHh4uGjEu5ByefNMA4+BHvBOjgOPgJnw9/DufCPcAl8HF4It8Aq+BS8HG6FG+DT8A5YDx+Gz8LH4XOwHm6Hr8EX4R74EvwA/hkehC/Dw3Cn5F9WKxkLctlIOlzfnhlQO1YQrju8RMrJr+AQeCmcCC+DuXAVLIaXw0p4BbwbXgmfhavhTngV3Aevhu3QcQ3sCdfAIfBaOBleB+fC6+ESWAOr4Q3wSngjvBGuhY/Dm+AOeDPcDW+Bf4frYCTp+i2Mh7fCvvA2OBSuhyfDDXAMvAOeCmthBrwTzoV3wYXwbngZ3AivgffAW+G98A64SfI13SbjRjBeykdrmCbl4y2pv2/DdnCPlJd3pF6+q8TT0EI8r0k8DRLP6xLPGxLPmxLPaqRJ4rlK4ukEV0g8veR3J8rv+sAesC/sC/vBQbA/PAUOgFPgz+BZcCA8Fw6C5XCwlN8hcDkcKuV4mDddMpZDGJN03Str2O+H8fAB2B8+CAfCzco+o40Sz3MSj7rPKG27M57uMBEmwFNgD3gG7AnPgolwDjwRLoS9YTFMguWwD6yCfeEvYD94A+wPb4ED4EY4EG6FyfAZSJkWO2WsBj5jYudfJb3vw0T4ATwFfgjPgPvgWfBjmAM/gXlwP1wEP4Nl8HPogAfgxfDvsAYehDfDQ7AWHoZb4BfwSfgPb37K2A1ti4mdzWLnUbHzO7Hze7HzmNjZSvLzBMnPCMnP1pKfbSQ/oyQ/20p+tpP8bA/vhtHwKdgRPg1joOzbKmM5/F/sVPdtnSD3fRLsCifDnjAD9oNT4BB4BkyD0+AYOB1OhGfBaTATzoQzYAGcCRfDs8X+n8Pr4Cy4Fs6G62C2lIdzxN70CBnjkbEfzd5CrbyLL41rCNcdroG94Y1wMFwLx8KbxZ5b4Nnwt2LHbXA5XA9/BTeIPbeLPXfAW2Et/B28U/LxLvgCvBe+Cu+Db8P74XvwAfgR3AwPwYfgV/B38DtYB7X3p0dgd/h7OAD+AQ6Gj8IU+BicBv8IZ8DH4dlwC5wPn4DF8Em4GD4Fl8Ot8Fr4NPwNfAbeC7fBB2E9/D18Dm6Bz8NX4Xb4JnwB7oYvwvfgS/BD+Cf4d/hneAS+DL+BO2Er2u9XYBR8FfaAr8HesAEmwdfhIPgGHALfhKfCXXAqfAvOgm/DIrgHlsJ3YBX8C7wEvgdXw0Z4C3wfboAfwLvgh/ARuA8+Dj+CT8OP4U74CXwD7od/gZ/BQ/Bz+E94ANoiqP8wCh6E7eAh2AU2wV7wS9gfHoHD4D/gZPgVnAb/CXNhMyyDX8OL4TfwOvgtvBkehXfA7+C98Hu4CR6Dj0DbCbQzMAI+DyPhn2Eb+BpsC/8C28FGGA0PwI7wEOykPMcYO7N8jqXIcyxVnmOj5Dk2GvaFY+Q5NlaeY6fCKXCcPMfGy3NsAiyHp8MqmC7PsYnyHJsEZe2djIkRRuxR197Fij1xsDeMh8NgNzgWdofjYYLEtwOpk/h4dhAfYbX3P4kvV9q1BTAO5sFecBE=
*/