// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_ASIO_FWD_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_ASIO_FWD_HPP_

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


template <typename Handler>
class basic_yield_context;

namespace windows {

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
class stream_handle_service;

template <typename StreamHandleService>
class basic_stream_handle;

typedef basic_stream_handle<stream_handle_service> stream_handle;
#else /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */
template <typename Executor>
class basic_stream_handle;
typedef basic_stream_handle<executor> stream_handle;

#endif /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */


#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
class object_handle_service;

template <typename ObjectHandleService>
class basic_object_handle;

typedef basic_object_handle<object_handle_service> object_handle;
#else /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */
template <typename Executor>
class basic_object_handle;
typedef basic_object_handle<executor> object_handle;
#endif /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */

} //windows
} //asio

namespace process { namespace detail { namespace windows {

class async_pipe;

template<typename T>
struct async_in_buffer;

template<int p1, int p2, typename Buffer>
struct async_out_buffer;

template<int p1, int p2, typename Type>
struct async_out_future;

} // windows
} // detail

using ::boost::process::detail::windows::async_pipe;

} // process
} // boost




#endif /* BOOST_PROCESS_DETAIL_WINDOWS_ASIO_FWD_HPP_ */

/* asio_fwd.hpp
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
*/