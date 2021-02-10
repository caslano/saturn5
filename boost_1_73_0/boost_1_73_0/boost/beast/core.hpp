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
Rh+SPEN8jej1RnQf/Ljwi/P2HuljvqEvUZ8uf3oaIEsF8Fq90deowLzj1TrIsa0pAcPbtfA1+WHcmqgDrmz/cJqYK+iZAniMl44b0qNCWsqYROBfPuCkKmU3SSSrKMIPECaX1ZIEhv4ycQ703wbksixw32MqPA+CvCPfUddtDtDW1NbFrUYuEgw/USKcNKv8WRUNi+SJNCnluGZBgb1rmjiUKzBFJbKGyp4a4jl9pw6I+li0ZNRXlNgC/3uMcDtEne57ayQjRD6VajrizOKeN36KQ/Qi1XBbIuua3YpOW1z5NzJsfcHGxZlZdrrX+tzGhqWEzD73Pv0lR0avVsPiGuIqyo+Sac3IC3OGqEZzMoFIQLdLWYIPq2B74m+K5qLwLAtAAGuG0lBLpYBqEE5IJn8e9UMKOZiY1yPdSvbyTMlcxWZ6jiL5Cf+SGqKhvq/hBwX0ZIB651TtuUa6c98PqyW/3eStIJ0N9sq2uClok8LGRsu7uB94VqAyEj4U1L/nt7EPGVIYMSX+RCkQtst/VUQE8MuNtZ9qKt1kMlMHofo7h9Ts96ZlJFPJjiJC/P5qw84xWN5APiCRtZZYizpiv9fXpPOYJrYLTwuwlJ+ZvyJpuD7+jxG35ernydTdFSlv0YHdMImn69/UZmPD
*/