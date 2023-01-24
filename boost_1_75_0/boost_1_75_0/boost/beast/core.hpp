//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_HPP
#define BOOST_BEAST_CORE_HPP

#include <boost/beast/core/detail/config.hpp>

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/basic_stream.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/buffered_read_stream.hpp>
#include <boost/beast/core/buffers_adaptor.hpp>
#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/core/detect_ssl.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/file.hpp>
#include <boost/beast/core/file_base.hpp>
#include <boost/beast/core/file_posix.hpp>
#include <boost/beast/core/file_stdio.hpp>
#include <boost/beast/core/file_win32.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/flat_stream.hpp>
#include <boost/beast/core/make_printable.hpp>
#include <boost/beast/core/multi_buffer.hpp>
#include <boost/beast/core/ostream.hpp>
#include <boost/beast/core/rate_policy.hpp>
#include <boost/beast/core/read_size.hpp>
#include <boost/beast/core/role.hpp>
#include <boost/beast/core/saved_handler.hpp>
#include <boost/beast/core/span.hpp>
#include <boost/beast/core/static_buffer.hpp>
#include <boost/beast/core/static_string.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/string_param.hpp>
#include <boost/beast/core/tcp_stream.hpp>

#endif

/* core.hpp
gSf3xL1JVbyzBOcSstwK+CAvukZPlf7DPz6iwGp3ZYNShRawCSWR+rQbj9W9amVfu5NsGnkUbHEZ1amP3bxVN7AIAmDrDhjaU4F2MH3ivfsEVd69jQEvx8ee1/O52Ls9Cb6sy7EK3Tapwv1j6DVmWx3z6Tmnsnfo+ypECv6lJrOPsbO2beYM5Yc66SbABP1oi19oj5FXnw7DZIPAwgXP8To5OrvNXXc/0U/K12VaKgwP8NuGuYYrG6WC2Quldd8vbjvQH3vLNQ38LmAZFW3+rV+hahaDRKHvVRgmFZUfn46fQyjasig/rmy8b8tp0GleMgHg69Vb1PU4gSXsO0b265fvO5nuztu67BzT92tRMmJgGZz2lj77SLFlpXFyjDT2/PjXTw9U4wakEADXOu5Ok01beNj7oETcintDiBtOqz6LJcEaq6UlQWSbM9ioWyOCekqHvK2tRq/87NPtHWEJRiMmcfeQ6KapcXZZJe1r3krWzx5OzrMVbPbnd/e0gnTXTR+1xq/xzrEivPIFMfDt8pmq+poK2Kcn7UD4MtNmtNYN84NYKuidNGI/Jq3Qw50KDtAalN2aLJw4iMzZeHjp7bctWHXkq9YOuJBVUym86jpzFFYrp7yastVbRHr6XB4N7N16qopWFk/v0Az9A4lY/RR/GkRprypNzG9u4cBz5sYfc9+8P04UmqYj3ak3ukyk5pOT/aSYUphXDU48
*/