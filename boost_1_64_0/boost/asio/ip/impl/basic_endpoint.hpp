//
// ip/impl/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP
#define BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename Elem, typename Traits, typename InternetProtocol>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os,
    const basic_endpoint<InternetProtocol>& endpoint)
{
  boost::asio::ip::detail::endpoint tmp_ep(endpoint.address(), endpoint.port());
  return os << tmp_ep.to_string().c_str();
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP

/* basic_endpoint.hpp
P9h458/v8j4r86/y3THw60m/OA2uiQv0twU+/DGr9O/suOCaBh0PgSQTP9eaBtk71OZu2AK+YM6T0/EKuEDDOc+TG8inwww4CPaFOTAHDoaT4RA4HY6Ds+B4eAacAIN7yeZqvJBDf9hessi1AtnQD3vCLrAXnAj7wimwn0Pf+gb0vewTfeRRQN9h2AX+DU6ER+AUSF0UfUWWvvvCLaqvJZyj+r6j+i5QfRfDPPg9WADXwUp4BbwWXgk3wBfhHfB35jr6XgpXR7lOlebDCtgVVsOhsAYeD2uhnDMGS+H5cDm8DNaKPXg/9V0SboxyPyfpdWbodWbC0bAAzoSnwjI4C66Bs+EtcKnq32Hpe5i+DxZg2luhs0jf1b1XP4Bj4Z9gATwAy+BHsBZ+DC+Gh+Ft8G9wKzwCX4Ff6t6p/4SdIBfkHEwA+8NkOAK2gGPVPhl+qnvq/gWWwUPwEvXHzzLvCvquQ/z5pi/n3MmvC3JDYU84EvaBE2A/OB0OgDPgQDgP5sCr4HC4FY6Cj8Kx8Et4LETGmgBz4XFwNJTz/eAkuA6eAG+H0+ELMB9+Bk+Bh+EM+CUsgOl6rl8GPBPmwLPgaLgAToWFcC5cCM+Fi2AlLIbLYQm8CC6G18Nz4CZYAe+AS+HDcBmMI5+WwxZwBUyD58POcCXsClfBaTAPzpB8NfMe9PkLGS2PznkPrZDrATPgMbC95m8HOBv6VU+uedbhnkdp366kfNq8CibB75v2Qp8x4CwJF3lubBv4KuwJ98Fx8A04Ff4B5sO3IXUkcB7biZzfhDmESZuaYGVjHsd9JMzHlGBWY67B3GX7YfZjGjrz7fC4uIi5Hc7z2w5h7HPasjEjMXoem+sstl0R80Dc562tw2zG6NlqrnPV+mPmYPQctcjz04h/l1w5G82ci1aBqaFBWosJn1+yBx7AHMGkDUO/nm02J/J8Mz3bzH2mWW+b0xIcc1SQW8n14FpMPSZwLhnuGGuE88yxiHPGzLyW3TAHvc7zxTIx4zHBM8TWR5n7chjOhc7zwfIwwfPA6jDrMXPQXYW5ArMZ8xTmHcwRTPvpnPWFKcBUYNZOb55H0/xr/jX/mn//jb9/y/z/ivJFR+PbfzfGIO9lzKa/fPsvKV28kPHDQj6NLy2tKdNv6hMc+wSMj9d9kDDtMPswTxG+fmvwm/rCkpJCGTX1/LZjvndvdX+XeVDs91i5/HupY2x80r22exvswXnfNaUra8y3APToXH+dV/+A2BcwTpakc+2ZNS46WlnDGWfeY79T0fVPJF1pvTqlJQ1LTeVcoyFJ/rTk9kkd4junlqSOSO2denJSQlpyQmi+dx7ymKjzxtvC1XKNVLFnYi8Te3u1h9IxkDjc6AtsEnA8+uI7MdDdLZFjlZJyiAkHHnHxPlw8Jd5cez7pLsTo+JheOzR+mSy6lzM7PjUwnq7XeJzAk+xr1F2U2pfLJLYkDH5rcd+FmWznQWLdpcHvt39ua0l42/hVxwHkpthy8XUPpKW2MN965zpkGzmPR8c/I8fdppn1B3JPXWcgbk6MXtZ23essa+XLFleaouZV1gjjLmuvYo9W1hZta7Csocdd1l7GHl7WCreFylpePPcu8eiXtRu3ucvaOuzOskY6TFmz9R5IOHplrf+2iLIm18hNjF7WDuKXk9h4WbN1zE38z5S1d3QQPV+/r0/FvEBZ27/NXdaqamsKF1VW0i4v8yprGmaq5zqVkx0yfiOzsLimvHJZYUlpdbHKFUTVVXluYTHdQ7WuY4qqq3jhsuLSCpVzrl1CNuraJVwWVyxcUm1kc8Nk12H3B9fu6LfCQvlkEdI/NiwMe4Ga+zdVx+bnxrCWKXTfdK1LlDU=
*/