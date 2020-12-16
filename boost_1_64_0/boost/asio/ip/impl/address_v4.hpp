//
// ip/impl/address_v4.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP
#define BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

#if !defined(BOOST_ASIO_NO_DEPRECATED)

inline address_v4 address_v4::from_string(const char* str)
{
  return boost::asio::ip::make_address_v4(str);
}

inline address_v4 address_v4::from_string(
    const char* str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address_v4(str, ec);
}

inline address_v4 address_v4::from_string(const std::string& str)
{
  return boost::asio::ip::make_address_v4(str);
}

inline address_v4 address_v4::from_string(
    const std::string& str, boost::system::error_code& ec)
{
  return boost::asio::ip::make_address_v4(str, ec);
}

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address_v4& addr)
{
  return os << addr.to_string().c_str();
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_ADDRESS_V4_HPP

/* address_v4.hpp
/+/U89Uz53T5ZUviA2sb5vZx6tIs/pPt/6Ztl7b78V9s+zJdDyls+N7O8IMO2f7LTfgnD9v2Qll/JsNx/lzV59E4TnfG8ZrEscLEMUbSMFPSkBU+DT2c4X8jbeWACR//Z0mD7jNGnt6w7aneGn2Frn8UNv6e/DPx3R6IT/qBqQelD/Ha4fPChz/DcqzZ2Ub6hzkxPawVmga+10qYMnOORSIzTfs+l9ZlY0ljTvhz9JJzaPjfSZqe8I51x7vtMBPDh8m0HOsZVUu5TTLreF0j5fRxPX+aloj/YJX3pylGxt/21D7eL/06/X/QWmepNfSnGuKWbvSn5ojd4qCPwD7CjMflW5HH10bKnMX05bvzVo76e58nymcsP/LR3U8f//gd375x175K73Opqnvg1X7qry7mNcF34CDYmk/Sh+AdsACZO+Ef4DqIyqy1Hj4A74KneJgPBnfBDXC8l/4MzoCb4BVwM7wN/gx+DX8O42NIC0yD98E28EP4AvwI5seSdvgJ/AQu5z79KWxBB/UZ3Az/DqcwB/UofBb+A74Ev4Ee8pnIMO08mAKXwubwZpgK0y3SxTfzXRi+0cu3+T385vu7fGN/Ofo9PXpEj+gRPaJH9JD3/6nf3fv/v9g7E/ioijOAv81FSAKEAEsIV7ivAOFGBImAAhohAioomEASSDSQQBKFltqgWPEstWq1VRsVAasiIlpE2+JZq1bRoqKi0mq9ikotVlqp7f99++3se7v7ko1ir19Wh39m5pvvzcyb4715c9SWl3z9ff/td/t1jn39k/X5Jj4Anrvw68B4wD55t59ZcMKM2bPzC8urq0trapeUl+Dd6D7LwWe3XZh9MgfqkdK7Z09OWT1zj7Xu+3f2OFj8vzMHSvcg0PzQfArbg4C5I3U2s2Ac7AyLgvMbvqG5DZmTmp+9mn/Nv+Zf86/51/xr/jX/mn/Nv+Zf8+8/9fuGz/+rLef/wtqa8gp7GOBrfve3xwHWOr7x79W1NS9hemIewnS29499XcYBTpteeNqc6fmFK0oXlhRWnW+Z83NYd1e7OLRmVuVzzfrlKrHXu+UX63d+Iz/YrFdcKvZNjv0/q8u/peeo+O38Ff9+Yi8z4Qeqv8/6ROx+c5YH66tXkOYa803PhOln1sMtEfudhAle87zSFeWLWa7iOotIw/kaPPuiPVwhcleJ/3GyR0FtufrL9+zLxP8cs3767R6cN4D5I+ZdzHsYe4wlr5HvbEWwStbVkqfqVuZ0W2z21Nd9TgN56cdtpTlnyOSPuNcZWc2D4D7KWk6uoJBLijB9MHMw+zoyt2JftHJiH9tIsbM8y4uGm+LIe86LWFJDMsyeryoz0fOeFhg94yLvocqUG5mRnmdI3ST+3cV/gtw3yUO537lW6KyMix1rn/MaOT8hNy60h0RBnPt++eWshGB+a7rVvSgu+v0pi4u4P2aNNXHW+x4ag8v2NX3dYtIk2UP0yZ/0vuC01muyem+uP/KzY1p+82Nz0b/bNn3M7raetvut9/74kRefXn742xk72g9K/vwUzzFHGeNbF6zf2gbK/cas1hvKt9C6nrAHHA57w7GwD5wE+8GTYH84Ew6AFXAgXAUHwRtgDrwJDoab4BB4DxwOH4Ij4Kcwz5R76prGJxFDmuXXTtdAdoRTYBacBTvDObALXAfXjY+TcciCqsi1VpkTYxuTPHx8YFxy7KSEqGOT2zdFjk/mIzsXU4G5onmssvnX/Gv+Nf+af82/5t//6e8b3v8v8P6v4kdj7r+fuf+J9jv+W/b37OqF51WXL0GluPeEebI/XU3NqsLKFfgY9ynGnfN8VP6HpHqacS9fZjncC0J6amvU3eZccS+vLlxYiCc=
*/