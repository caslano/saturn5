
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct divides_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 / n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::divides_wknd<
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

/* divides.hpp
aLV/VkktcR9rMX8+23iQNE3lpV2Z6VNM95EOFd+69RDzetjpfRSO8mNmrGwrxnId5W02pm3tVOenJjHbnBet5V5djuRFMKE8YRChGctm/2zKi+gJKXd/r1w12c8mrJch0w7YlOlMma6BLoQogvFeoZ9UkL5Sl3oSWrBegTn+2ImZkfyUVpr3DpEGTDXFIWmQ6WiZvsVHSUNmlHn6pkzLfUMZj0C/b1isLh9tmWdr7G/vczGiIXn4iynNcbHhbqXOswy2lYDG7d+Q7beQ7TeT7adq23f/XdtX83xRhdvzvBV5vl7bPp0ESnH8WsWh5fm0Ovx2qZa7TMej9fgRxjQFm/ouyHakzNp48L9f1TQpVfH2emB/hzTFWaUp3pAmJQ1RNtKkjIGwjPwJIj0dmW5vit+yX0+WpN2Y/pOSficpszqEdh7ktZ5+3ixz9343d89T35prJU0pTSzzcJn0UZihLCfpbE8acvU0pE+OTP3deZhhX/o8PEV+LCI9AUx/cZc89JD0Z8jPNn7kf1X0QTfSH1wk6TedjKOmMFyHaR/W/458VM616TK9n7QwaZfQydy3YJFMR0empU3R7u3LMm7ST0ud9jCvk2Ncp5Pc/1eXcTcvk21cRt4dm2Cc5y3vl1XXk34Ep9RpT/M6q4zrdDTPSzXOk+W2GOf5mre1V92Wj3k6V532Na8TYVxHljmqLuNtXma9cRnpO5GnLuNlXibLuIyHZR+aAHnvXXp52l2MReUYyS+W8rV6/9oWu9K1s8aypp01HjNaX5nZ0gZmSN6Gqn305O/b1L/Lfp1Up6UPSJg6bdXXJayOtJ/1WA4HYCuWcyvvIPuk93ULsC/dMVfac+l5tU+i1M2W6rSUn6M6LWV8qlim3cO5PjPPO6Sto89LvWkuwzhPZctSrjdknle8hzqvsrpcJ/PayrxgdZ5PvLcyr5qhjibI8bFR4oyTsjiqpkHqdJD6d/dwLa5gdZ6vPi+vWOJy09N5UU2ne7wXS5qPG32et7pcSzWdHfX92a/vt6+6P0f1/SY1khY1Xm/ikOVC9bzoFN7Rx5wWdZ5vfEd1nr2Nc8wldf/lfOFzU0uvJ5jToaVX39dTN7R5HdW0uej74K4u56Yu56lvL6tYi0Pbnos6z0Of51SsxeGr7kNLPU+IV44Xq/NkjtV58nzx7efJNWqZeln0myJfZf+0fNDLKEefR9ySN9q+6GnMU5fzMOSDPo+aJnVd22e9zCsXa/vXSdveda3MtXWd1HzopNcNO63+s65sr4jlpB54q/O2aPNMcUgbKvsvebhKnZb2KV/dtpueBrsb2jxfrR7f0NKqlWOCllZ9XkCxNs9TTdd6Pf1eWn7oafVV07rPqo3ztGzjpD2Teq3WTW1aP9eEaXVAP64L9H3y1ur/dS2t2nJ7r2vp0vap0FjPpB61VeP11OPdJvPMpSTtmx4vOS7XBDe0+kEtleNTP+5IteSvdpzo58JcdZ6nXu6n1DR76cfi3pvaPG3dUD3PfdTzaLbV9cEJq+uDS8W3Xx/42bg+cNXOt/q+79eOAz0NNfT0yzyWU9Pvox9Xq7TznF6PAvR5Xmqd2aKd1+VaSp2W9mq9mi65lii6rh3XPtrxr+W9If+0vNeP11TtGNDTaaedt/XycLJxrVSkpkvObYvUafl7rlafzNMB6rRcx7lpdUuu/7R2Sk9Lvlav9P2IuKmmz1AG6nI+eh33L9bmdVSXi9CX81XrS4Lhmk9ZJkTLX73ce2ttsX78hWrnHX2em74P+nGqlo+Hfrxkae2Ufk7M09ofw3lc3Z4vy0n9iLC6Jj1jrM+yD4u0c6Ceby21878eZ4De5rMXkm9anuvnlQTt2NPbDh8=
*/