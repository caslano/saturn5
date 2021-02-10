
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
5DLQS+FfVej9QKTrBvphZmcQXw7jmFfE5D2Rw918eG5v2JhiA8Er6IKwAVogBCQstIcPRAuRXzhixLrVMmA7h0DaR3XjyGWuTMR89jAFbZ3dVG7lO2JyO5sBd3GD37qqSzxmI3z6ft8Rz/fpM7D1jnidj9MO8w4YJffl5OE/+gVQSwMECgAAAAgALWdKUlTCfxqUAQAAoQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNDhVVAUAAbZIJGCdUtFO4zAQfLeUf1jlxGNx2gMElQmHjqKrBGquCSAeTbK5WiR2FG8L4etvk1Aq3eNFluxdj2dnRlGEnnLtMRbK2NLx9ordm2sLH4vbLBFKHmolR4hQLTZVx426oDoWs+l3mEXRaXQSXUyj2dnpBUPHKyU/oeIb/KwMWpp4U6BQ+VAwwGO7wzYWJTWM3legrK5xkADbpnK6ADI1Qu5sYcg4C7jT1VazfLi9vksXcBnvgdp2b7pjCjlyqNJUCP35MqzcH9lbnp2cH9M7hbEoNGkB/JEbNgCPKGijCXr/bP3V84V3UDgeZuiKZfaMvcjc1bW2xaB+LuXRr1WaLZP5Eb9MVutM8hiYZPDPVJh8QKibFqZDbBCdz6OIV8jMX4x8/IyIo3vE1pQd
*/