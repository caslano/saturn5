// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_ASIO_FWD_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_ASIO_FWD_HPP_

#include <memory>

namespace boost { namespace asio {

class mutable_buffer;
class mutable_buffers_1;

class const_buffer;
class const_buffers_1;

template<typename Allocator>
class basic_streambuf;

typedef basic_streambuf<std::allocator<char>> streambuf;
class io_context;

class executor;


#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
class signal_set_service;
template <typename SignalSetService>

class basic_signal_set;
typedef basic_signal_set<signal_set_service> signal_set;
#else /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */
template <typename Executor>
class basic_signal_set;
typedef basic_signal_set<executor> signal_set;
#endif /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */

template <typename Handler>
class basic_yield_context;

namespace posix {

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
class stream_descriptor_service;

template <typename StreamDesscriptorService>
class basic_stream_descriptor;
typedef basic_stream_descriptor<stream_descriptor_service> stream_descriptor;
#else /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */
template <typename Executor>
class basic_stream_descriptor;
typedef basic_stream_descriptor<executor> stream_descriptor;
#endif /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */

} //posix
} //asio

namespace process { namespace detail { namespace posix {

class async_pipe;

template<typename T>
struct async_in_buffer;

template<int p1, int p2, typename Buffer>
struct async_out_buffer;

template<int p1, int p2, typename Type>
struct async_out_future;

} // posix
} // detail

using ::boost::process::detail::posix::async_pipe;

} // process
} // boost




#endif /* BOOST_PROCESS_DETAIL_POSIX_ASIO_FWD_HPP_ */

/* asio_fwd.hpp
uBmDBFMtB3zS7Fcy6nLhm3X4ez8wenee4PHzFbv3CSjXJJWyliI40VR/wihkKck31+u1jrI4roBzY7w35XMeIKrlI5KV/8SJ3+jK7hqUvrM/KPozJZNt/KJI6DlpImj3QCKpWlVVH8Cqqwa+hLrZrzkGqGkv3thlspKCrwKe01rk8rY2FuwJr3qUxViR5HT9tiKd7X3opW6OPrgWQODAaN/lH6sHTgP8BwpNAl8UOTbopk17Tmta0bEUY1ckJF3XWhmkUwfiVdB/ne6nWXKc+XnyEEdshDzMXlq6YT3qdU96r7inj5VnVrVrdZPBAMu5FQx/QMOq377MHvwcoXhvNFbw5+N+XQ3gObvtjioko41i4RSQrLdFSvDJolf7HXvaYCAe/P2ZdGZC9yz8ceNMuFgXotLAY4Aw/5KIwNyLPdBywOVc9f29fl4LF1dwyr3bh/aT1dJeJFp/RXmVjWs9SIUSGGHCAcnprRJ/KHTUs8UFRfWV/nyjfCRM3MBXrWB+aGOzgq8mVduSl6fICk1EhBBzQJHRbuAHfgJ/IfajuqbJQSmKmkKpLxjXIlYBzZiwwhRaYx1Cr6SXaFFFLeOwotATMpBIKhovSszsExDhgHp+1BBAKRPjAReR4DDSh/5D5BYuPMKQ7UYCd78I6ja63y513Cu3cV0L+WEqAvc4qcCLrLLGtUl9dxjT38B29km3ceeISuc52s49s4GZ
*/