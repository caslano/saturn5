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
2eJmjetnrieR1gCry1ms9FuoWhCw7CCRe7/2w5/kkHquwVuP4G3RwSuXwIqF9PhTAOfzQ9XsRuLzE1cDxlM2hLDQfmG1tdDeXTP7Z8okteffjOBrRB/AO3burFLWsM9+Ptozfc3V/H3ps/j72oP8/egV/P3sfvxOPv+lb5HHNa+Qx2vz8nh2Rh5vTcrjvXE8XvPCZ78GDyzAp599HTzX0PMGeL4s5VIDMbPh1O7g9LOvldh3
*/