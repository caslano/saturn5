/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
N5/1AjAFe+MCfTu5d45zTLabLmNKZuAMnGnYrly2G2CyXYKkdzn2walYe3yqZbvxJsenv/TFDMMgHCDpD8TBOAhHYzjq9dPHdXntlvp5v9TPPcbzp4/r/E+S/MdL/icb91u2G2ayXTTrdcLhOARHGI+PbDfcZLtRsp+jMRLHGPevpev0xkl64yW9ONTrrWzX02S7CCnnSAzBKMN2lbLdWJPtZsv6czAGk1E/v7RyfRx6Sb3tLfW2j3H/6tlusRy/JXL88ozHr57tWkt6bSQ9X0N6FtkuymS7b2Vs1lkMx+9Q/1zWk94syedsyecc1I97Pdutlu3KZLur67bjhOl6u82y3RbZ7lbUP8/1bNdNyqW7lEuPunKR+0Csa7JdrJTLWOyK4/TzPEG2u8XkPH+bnOe3YW/cjgPxThyFO3ACVmAu3oX5eDdeiTvxerwHN+G9xu/f1q7TnSfpLpB0r5B0UyXdNEk3XdLNkHSzJN1sSXehpLvIkO7petL9UdL9WdJlRdIFHIUX4QRsirnojfnYHK/EFng9+uAmbInyHB25b0LZS7r6c3Rk7GAAfonR+JXs55m6fHOvw3W+J0i+4yXfk6W8LpN4pkh5JWAuXi7lNU3KK1HKa7qU1wxDutX1pFso6RZJulZJ1ybpFku6yyTd5ZLuCkl3paR7paRbWpcu9yFcp7tG0l0r6a6TdK+XdNdLuhsk3Y2S7iZJ90ZJt1zSvcn4u8fPdbrtpC9+e+yNl0r9CJD60UHqRyDmYkepH52kfgRL/egs9aOL8fzbzvX3/0ipHzFIusbnK8m1vvlYvJmsV+Zmn3jP85X+M/rDe/rC/2/3hT+XfvCePvD2feAt+fR9J1QRThL8Cui/TkgjrCPsIhwinCEEFvJMJoKNsI1wkHCS4GfhXEZIIZQR9hKOEXyWenuFE5IJpYRdhEOEM4TgIm+vOEIOYSNhH+E4wcdKORKSCKWEnYQXCacI7W2e/vOe1y//8iYs/uX7/yuTHind/8+773+fvl518zE3ketT7IDTcZXS7/twFy/+ycTIan9A47SMbs37tOkNtndjTkaZVzGzdlksDpd2taXSNhOvz7dtkf42+nuLbGc/751DH6QE6YO/S9qN7iaUKe1GR9Q8Jkk/XHlivl0/Vzfatpq1u0GJx+EZBV2dn1Eg+ZPoDfmWfsa5ju2ZxyTfIYSW0u/gauI9bZZvedK/O/1H5LnedXmUZX5onDfd2C5oaerc9/oatg85apqX/Cy32lWZD/5o/WUnbYX6HIRObb5yij8g+foD4Vq2rzHNlzQcu5m3RW+6d1z9Hdqr/e3aqzMLLdJnYmhtHyjJ85+UdQnPENYSb/Wbjnl2r5+ppGfMm32/+Wb8T9JqRlAWrlPSe8sxPbX/ChPYFmdb3ejnJfXIZbprTNK9Xqm/Tuk2boyAWbrG8j0j6d4lfcu3EdYrn/djTunS0NxwXWiofKukn/8+Ig/B3+NGpQ46p2fsq+PWeTTwHYfzqMnnI0f/3DIWxarVS4ssM46xkbmeZbn5OKAE6Zu/Qz5PtxM2KWX3rtm+aNP0utPXw/Vn2+55JmpepkpeTql5kblF5X5suVKuLvKSV6hM2lyUnZmrNNinZuUuyrW5M2bAqT5JWfnpc2Xrkdp9r2yWvv2rpKxWyLnH77hp/rKyFzbu/JN5vP7zT5Dd+ccuert8Rksf+0Fyb3Mg4WbiqTTPJ31LswvUEszMOKeyq/0uWakuIxJZFohNm+tz6Nrl8bjkMUzy2J+wWTlXmOZRnyEz43y/77o3Io8W6bO/Vo73bwi3sn34e6Z5lKm5qddujKWQ3z7GPJo/T8ehH7i39KfvQlCy11m+l2vqzRMfDc4=
*/