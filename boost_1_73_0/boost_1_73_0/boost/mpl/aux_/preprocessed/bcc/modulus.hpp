
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
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
73QgK5Z/cnbfWzHdFxn+aD5yvcv3RieDXscRpmbv/6DaUH/UlvXYymSEPuzATUVCDfa17ISNqswtI111ArVKDiutksr9OeFAY6IMlog+pIraIFCphOvFkBLxOhO4gUoSkcqKqs/52c3En4+n/TPKPZ3M5lzwTJiQO3aXw9sQEntMSMt9OVTmA+potYPyFkCsDOpjk1Lv5rBE6vdmHirTZO66wlKCTCujAhV77N4fzUCkKt0lqsgbbDrw/VLOZ9yKJIuxRax0uhg2GNUHon6VsuoVaWuw0dR/aLD5r+kIBg1W/lcOZ/X6x/2Yni4/0br8qIWf/m+/AVBLAwQKAAAACAAtZ0pSrKfNcWMBAAB9AgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIxNlVUBQABtkgkYJ1SwW6DMAy9R+IfLKYeS7QedqgytKnttJ7KCm21YwZmoAFBSdqufz8HSlGvkyIljp/t914iLBqbSoMhE2WTK9p+8HJWOjMhe0siJvgYC95D2APEqE+op6bMkAmNbXVx6euB8ouqxMZe82kXEMB0VSHLbUvoIQLRyBq7cXBsKyUzsGcFeVmhAavAFgiGEJCVmsC8R4NIVV3LJgvZNIFKffO+Npg9PgENmHM+ed/EyTqa
*/