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
b0jmvcVE+HKWsaIrM8vk5REBFnqIDnwcJ+HE+6wwjBYnW/MTVtPqXSHuA5TmYvTiKixFUF+bj97L7YbB/mxpKXNs83eFwaU8AGzVFBFL25fN/qNhuXcil+9Wx8h1xdYG+ev67JnLZc9f3KXQs3dnB+l4dae2kNKEWUF+6Nhdugr4t/8UrZNUja2WU4tF4AyCI5iLD54AbiKpwsjJ5MwDPydTzgdJ06KY5MinSkrjd7ByrOEaJ9uv5l93GdbeLSb3V2VlDmSHUrEKZmVOZO0KCva5UfuBsIz74/iyvFHO57qvsnlXjQIPntis3lu5miSQIQJ8McpJhLM8Bbgpfs0U10ZPMFolugl9YLEyUG8MUXS1PNCnplNAyx+29J4uWNbylKLW8l6tHJhroVA7lDPbob4utJiXkhg+JhdVkfooWQDF+T6w9ZK7VaHpiD+AUK0VoJQTQplTkFMMPrZoxY4MxKM4L/9bJoazQdFEuttVuyS6ZEwKtwoFjmC0p4DfgPzqOZq5nOmcWZNpk5mtacA7z3YppATsCANqAt2CUj99sGPfvhLwwr2CnSoPmhTtcoH6uMo+PUZFBXSVmfcavOd8LI7qE9YUES3ctREfmDMmzsnRdllWd7nXIq7uqti91dFqD0xUgK8DabQpn10GZsabU/TArraOw9R2c9wNEoWr7KmaX7i1IEiogGIXDN2AU5XU1qDhfFX1nNuhSbvg
*/