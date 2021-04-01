//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_TCP_STREAM_HPP
#define BOOST_BEAST_CORE_TCP_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/basic_stream.hpp>
#include <boost/beast/core/rate_policy.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace boost {
namespace beast {

/** A TCP/IP stream socket with timeouts and a polymorphic executor.

    @see basic_stream
*/
using tcp_stream = basic_stream<
    net::ip::tcp,
    net::executor,
    unlimited_rate_policy>;

} // beast
} // boost

#endif

/* tcp_stream.hpp
P1x1LoGMcGo5zf6lLLyg6HeXx6HmC+r6BP2tpu0MkN/rrQia1ADv4lJCkk+NOl4g+QXk92bmlnMNfHUGzwre7cbSCy8Zs2XidMBvzIEea4Eqfs2ldCKjlRbak+IMnlY4u6L2bN1RMy9+wWvOaYb1OPPlbQ7rcT8WpdIMW/C7MSRAR7GHSijejk/XnIYqb5g4Lsi2kFnmNEkodf+A8m2m1cwdhjJvaXHIZpyDgvjzmd/8Lip20jbjmd0JBoJIbp6uoIjyM+DZL0MSkgO8iDa9gjWniUnNyuhOQGlw+T2Jdv4NuEJG0+aOQfqezU1w+86bFGFTNsjtSuW/Xu8x4OEtl0VwHiB993BnnX/idkqjniRpecxyCsURtQLXlTMrhLt7ipEux2VZUsCGECYp2pj+tFGVhEV9UwlxZJR1nYqi543Q/qpbQKwvvDiWY2cuPNJ/0b4BWHExIy/5CZrZkcHDUAPZ+KlRzy/FL2xpOiJ3LU7bAFis0mQ6jlrJT28xKBZZl0f0s/7UwOnsnqiA5eqGtNAVxSMpbxI/bgFJb9al4zHK9NTDbo1DxIFZaA==
*/