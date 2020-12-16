/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   date_time_fmt_gen_traits_fwd.hpp
 * \author Andrey Semashev
 * \date   07.11.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_DATE_TIME_FMT_GEN_TRAITS_FWD_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_DATE_TIME_FMT_GEN_TRAITS_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

template< typename T, typename CharT, typename VoidT = void >
struct date_time_formatter_generator_traits;

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_DETAIL_DATE_TIME_FMT_GEN_TRAITS_FWD_HPP_INCLUDED_

/* date_time_fmt_gen_traits_fwd.hpp
7DbaaORho8bGSzlIWUsbZWRVYPaVtdG+ocb9WOY1KJBniXxkJWFrfOwrzV1kmSNE3fR0dqHnOzZAXT31fbV5vs9Syj7zWepstf9QV3/Ls9S1f/JZSs0FInbbx8sp+2zlqrG9zINo6Yc/Px3m2/OkwvqMEuD9QcXBX5w5b48ZgS6PCB/cebbcT6SvWealMY9jL58x0nd/qJz/Q5ALSWtay7QOkWcdv8+TRUqnq/66KemwlyF9mtMseVSmTihfyqvgzWNy9lFhxjIfLeEoG6H4XSVlYkUA8wvp8kuVC3tZsZYLEtqyXNyM0XW+eWV77gqsXDTFQTkn7I1qnIM1Bj/rjbWhbHSTtHIs/KzHspeP9Zo0X4lOg2+azee4wNLbYDnHdSq9ou1vLbA2pNWoBxwHPzmOTzqf6tQynRd73xt90xnk82BjfuDXw8Y2pFFzTbOlrz5Wfx5dBb7pk+fJANOHvqTPOI9KW5c+wrY9feocyjGs6avtrE9fim/6zOfRwNKHvk85FW1/c+i1IY32cmoex/7eEtcynfWEz9CkU6p0QOnMsKTzGpVOQ9vP3EPbIJ0cBz/zOLZrradLy3Su8D7b+abT8nwcaJnNtqS1ON0b1oxBm9bsbZBWjoOfeRzbOR0X3zKtF3LwGk1aeY4NOJ01lrp5vjqnSlv/LNaGNBp1k2Pgp45hb6/A3zd9l6VTzrXpk+f0QO+bBc33zUJ1Ls0Y/N8325BW477JsfCzHst+TlMSW6b5cu990zfN5nN/YOltMMsuYdU5FW1/9802pNUouxwHPzmOZQxigTv4sWvBjtXLVmMHF63ZtdudRwy6d0Tk6au/7fRh7+DHuunHMgY/hlI/9s7/2Ef9WEZ/YwH9j3FsmndA2p+lfTvbZ96BITKfxFAYD9NhMtwd9oDD4b5wBDwA7gEnwgw4CRrzmYyG5XBvWCX7NylKuzDcRY4fro4j7dFy/P4wGg6ASXAgTIWDJZ40s61Wrq/m2B37/Ak5MBJ6LHprRC9So7eP6I2DEXBfi15jK8e7VvSuk+PVW/Q2tqL3oOg9JHoNFj1Xnn+96aI3Q/RmWvRiW9G7XfTuEL07LXopreitFb03Re8tUw9pRe980btA9C606GW0oves6D0nes9b9DJb0SsVvfmiV2bRy25F7yjRWyJ6R1v0yrR69jF2p4reaZb5PWpEr0BTz5KknCdLPesm9ay71LOeMB32giPgDnAk7AdHwR2l3vWBHtgX5qv9MjbQeO+X+0e2z9jCfLG7ALaHhTAWHiH6BUia6B8q+u2Q2aI/Xuw/ACbCA2E3OBEOhZPg7nAaHA4zxd4pcDKcCg+R/Ya9da3Ye5PYe7PYe4vYu8qi39CK/qOi/5joPy76T1j0G1vRny36c0T/cNHPatYn0/zrrxb9e0T/XtG/z6Kf0or+u6L/nui/L/qNFv2MVvQvE/3LRb9O9K+w6Ge3ov+y6L8i+q+K/msW/ZpW9CtFv0r0F4r+Iuv51+vbx2KK/gmiv9R6/lvRP1P0zxL9WtE/G9ahFHtP4GsOW8dqrkVkfKaMyWw5HnO9l5lN4y/P8BlvuRyJlzGW6/ntOVg/lnIgImMozTGTE+FSn/GRMjbSd1ykOR5y1KGWMZD6dSdkrCPh/IxtnCFjGOsZo/gY0ohElUa7BiLTkGpkBXI/0oiEzY92pSLjkTJkObIKWYv8gvQpYx9SjJyBrEJeRbYgyQuiXRkLnLGQjnOc4xznOMc5znGOc5zjHOc4x/0T3XYa/19cOK/t6//v5IpRY+Uq53jbdj25eXOriiuzjO61+TSvNs0BuCPxD5a+uUq3fX6VTkhdOttzzL45WbdK1tX2Pz8JOvZ5Qd5NDHw=
*/