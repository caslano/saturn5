
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
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
fTeIzTGQVghhulCq19pB4ky5rzqIuyd4c9Ew+bcdQpF2w5v84fYjA2I7DZbzmHT1UYHzsNFv6U2UQnzPwqlgXPqsgrHfw73e/NWZ2MkxMZmdVCOEOjHnZ+eaui6u1+F1uMVTplxfgHziqdAvLot8PdTr3VaZHxPrd5/4oKuxKszWZ9DfD2LGnVlA7xU89dUyEcchxKTeZpm/Z8v354N1BUebZ+OPLXffI3I7KKeMiQ4dysuShUPdMjxnNco3Due1IzX9PYuNrtwINHv2M3Cz4ysjFF9zvhROdizG3p3MDWk26uLQho+xtWtFdltVVBMmylLAKvsacPVCTfb7rK3akA9WtBuXyJsfXIQuBJ8m+l50TDhC2oA/sJu5XzbPleSDulPYDFGNikRVAlQiZOwrJyM3mqm7qAKtqV4kXyr+hGrbtdS55mvIllINmDOcheu7LrDstj8g5/FaZ39X+01qbRN2n41DGJz/Q6AXgFVbPOMyQATnEMx4YRx1ZEg/9G21RvOkVfEhiPNbTt78jGnh6kLmlniFS5d67PbYyK1xuJcSlhTRQ1wKZB0TeDBarzzS/2L65rbk7Z0NRuVrldQtTfo7tnLzqO9T4t79/HW6vd3iwl+wHHu68CVZt+gDtHqC9raCCLYi8NMLRZjiOn2zNWw2UnwzNM+1hG9yFEvZIYECBhuCqUCRH0b4j/tHUIeRENHErLW4Rwv8eSpz
*/