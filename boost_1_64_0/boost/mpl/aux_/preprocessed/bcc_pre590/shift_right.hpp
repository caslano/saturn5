
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
fuRIpa59rMPh+uxgTHu/rsCEM3Hxz1QLsPqMAcIS5myPsThv3lTtrfS44ZCLhU8DfnFvfQmPhFLStawi1an5pyZpY8Lz7StQsNdMyVkVdnlKB+u0a0anHwhmNe1Y0L+UnJ8V1l+6pCT1ctPbMXOp5Z9uXxDeMkO/mTDHdGdwSrEV8obywDLsui2TEoI+UQ5Hcno3PbNFt8IadYJE2SDo7CLumNwJxuJo48t5CV+uESGqUSe1F33XPXxZXcUC05FQiNjwzyG7w9E08EabeXmKaR23MkQF7a6+kash7eVyE5AtbATVXvkCsj3pMEUm82MSokyQsJoLjHfWEnW39eCoqP0kZi2u1+WPOirdJVkmay9729GxdtWntQTmV7IOVXUyOWNWux5vraXbYEngFcvMw2Oow5Q48bF6+mG8ZG/Hhd3484sjvMgf6f3BT8ohEXtSVunNyGclQbtBwUxTfA+05gObT2OBO3NkkpHHICO6BCejro724ZHoHHZDf3Izhu8BgPaHvCwn4Cr4X9TiZzZZoyGTavht1tWxqP9+TeP4zsjGvhamHNo0xNjC0g==
*/