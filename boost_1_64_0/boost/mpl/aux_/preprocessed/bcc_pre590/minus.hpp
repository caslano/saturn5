
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
eJ3fbZ5vN/lNxn5KdcyhnYa8XIxy2P0cMqtcZN5nnnE3mTG2870ufcrgbuF1/IB5jl3lxR7DiHp29CnndIrcpzzRzb2961x1iS2GUeT2DtZF2tbh8h8yz/j2LvLX4p6/1/05d+gwbxvZgdryuyia3+M+lg6WNZgXW96mgrMT/qbtQJt62ltjgl30boCdc+5Ogb+3H5XRbw+Pvrsg+F2/+u9OCH7Xt/67guB3u9d/d1jwuz713w1r+K7vXh6X3+tkxQoyvz2Ux5q203k1DWOA0N9xZzwhnz/4W/2IeVf1K36Q/m9lyjmKDfSo6UNyCx3vIz1Tw9v+1E7Ue0+r3kvNK3YMc1End7K91+vzBI/zfXWGZE4yMlWuszkv05IpI7w3pr3zAve1Z/34YLv7WkfyzY77YP9XfLB3TjLfH5x4UF7Pr166P3fZWb3OnXTIqJbxwU71yLdEf6eFrDVvm6A9EBLk82H5gnCeNacwXP4qM+VzfT1M1h4R22hviN7wFvle3woPgbdpL4TboR/eKZ/ou7SWew68GN4Dr4b3yje6Cr4CH4BfwgdhovaE6Kw9IfrAR+T7/Bg0Oj4Bx8Kn4JHwaflAz4fF8Bk4BS6AJ8MX4Gz4InwcLoRPwpfhYvgK/B4ugj/A1+Eq+Ab8A74Jt2hl7VnQBy6G+8N34Aj4rnzLB3rkOwK7q/5bw56q/y/lA79c9foVTIVf2/amSNP1e+p6+94UZbreDzeE5WqnCtgRTtGa+uPVPlOVbx9SpfLd2MU3/0fl+5PyXWG7bnYj163Udat03a+6rtS0ra4br+vM9Xm67lzpfQHsqj1RttWeKDtpTxQj+2LT7toT5SBTBt1vl8rn/zJ4FLw8uPeF5WshH4y0kL0vTpLcU+HO8DQ4UHt5jIana2+PM5T/mdoL4yzln2bKpfx3VP5tYH/lP0n1UQTbw2K1i097bZTY6rVG+WzkUq/fKp/voNH/e9t1dVtEbo81uu53tccftvvKI1v9UJf7KkfXTdCeCLnauyMP9lPcqr0VtyoNFijfeaZ9le82CVa+5vq5yrd9olXfm8LAlDPcEnaAB8JOMAsmw1OMivBcuCWcAbvDa0354C1wB/iiqXv4PtwJfgp7wG/gzvBbuCv8HvaEHdCrF+wKd4NbwT5Q9SJ/Avphl3rZppVVL6lwc7gt3M7oBXeD28EhRh94sNEH/mj1n/IdoG9QvklwuvL9pZVVLythP/PcwH3gb3AkXA3HmXaEOaYd4YnwTzgNetD/bAN4GWwN58A28H7YFr4MN4BvwHbwLbghtOLMyU9A821pIXHmMvScHKI1N2O0N9FYuBfM0vN4mJ7HbO2xczicqD01irWGpUx7apyuPTVmwmOC/aXs/bwruvSXoxKt+s/Q/TMaphjdofYGku2eNtf19r2Bhun6dF2/PzRyDoA7muvhznBkYlCfSuW3lYs+/ZTfHspvT9gVDrDpM78RfQbp+sG6fh/ps6/02U/6pEH1N7Kfc8+69Ddjld+hcDvTHrAHzIa9TXvY8klTPv1c8jlK+Xilx3ho9M+Bu8MJicH+Z5ry2cKl/+ms5yUZdjbntLL9jui6TV2u21LXbQXbwxSo/ly2Zsrq0p9vmGDdpzvAHeBO0OjdA+4Gd4H7m7aAB8OecDTsBfWcykbMb4nLc/prgqXXamjaeQ3sBn+HPeAfsB/8Ew6GrVpZ/WMiHArbwCzYFh4NN4IFcGM4GW4CzzV1Ai+GSbASdoDay0b2ZdpY+tn3srlJ/cjNsCO8FRq9blP/dIf6l7vUr8xRPzUXjoF32+o5NUlyXOp5guTkwe1hPuwDj4V7wAJ4ECyEo+Fxyn+SLX+PyjHGJf8rlf9MmAo=
*/