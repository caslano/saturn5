//
// posix/stream_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_stream_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of a stream-oriented descriptor.
typedef basic_stream_descriptor<> stream_descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

/* stream_descriptor.hpp
zR1F4WS0XVU8InFebVQJpEJBjQTgUAOnXUGf/DZXQA5/VIf2REEaROE1Tl7ImguvNNI9j9TGsJ4Kbzv7XHGCd7YT+wWl0kaf8ufACv6P43KHLddByix3kpw6chRrqnmAmXuqLvJLiEHseb0PQKsP3JRamSgT1PCX71ikUhVO0FgCry1gBtcMEkEHB2d+q3/wALL2MLry288rk2aq+2nHfi/MUaIp7hfv6Vds/vXmKJv++fc3d8v30/qxQR0CdQiDMMauXEF1XFOwIeDFoxCnxtxN71wKilUf/Uw/jUjLeV+ir/CvpYIo0jKCGt9kOsCJJDdSMGh+cdKwyRnZj0BMEVY0n2lx0TDYdcgfBWQZIyqn+laYRw/U2tk2dtzphIJ+juUfNgBP5FspnKCwhZLP+9tftlXsCQgBIJQ9Tg0lfSC2PsulA8U2BYK8vgikiwQgqHal29wR4Wj9gWRV/9fnIEBZZBY7QKGrvHdVspGbseJ6i8X1yEu+UjU7AtesgqX8mTJTD3CSS9qMnXdU9lmRmvZaLFWa5Y75QseqRiP/Fv2jsKOHFZOpmB/kqA==
*/