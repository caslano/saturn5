//
// posix/descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of basic_descriptor.
typedef basic_descriptor<> descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_DESCRIPTOR_HPP

/* descriptor.hpp
KgJBNoHUwa4qUGJ//s0Sw6YnLNA1lRXrKTlgeSQMlWdxcv6tmHGsqnxdXpNfIbjEnz4Z1pcEQHXOB+GYcLzga99zcw6I7Xp/pZSza+oo8mPqJiHJYwPwnsaAr5lg3VOFpZVlv2XIc4K4xGHsHHjepKeBAHpIsuQ86KxLbuhoaZkQMATfd16BoilzO1AHlYXgSYasw+yOZFRNrz2Nu5WI9307Xv+4mrzl1pYOXUTokQx4DQzRhRQNw/ZQjITrtJkvDYXkjmU1YZyPUr4Ke3fJIl2+C/u8Ei9AkHzptt5gfIqpaZkYavZ1Qvr39NFF+Nn6WSHY2wueagjXV0tm5L8QiEKz5eELGKT5r8TljmTbztxwBAddd5BpX8nn6fKJbIVdpDqUO/G33yGrfAWUOHgKl9eCsn951y2L5qrhb0PhzdW/z51ItOWBdXGAldF+7LR/PtehGIOXoyfQSA596YWB6OyyuXIJoMNwtXBVnehkf1G1qTBmiCTAzlzW+Vq3yE4VZdhGR4bUhA2t14EsTC2P9veyf7bOwFg50cmUJa9SyAr/bk3CpSnoV9mIvQ==
*/