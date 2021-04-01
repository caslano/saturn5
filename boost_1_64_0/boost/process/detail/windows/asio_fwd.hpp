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
lechZBvabC0jBM2+8aiM1my5O4VIPQnOROB2/XGNXQ0M0uUyiDLhWG9I67t0Rwrs9ifEWP7oHrnQ/5FKGxVMNSEvfWYsfQ72GK1XAnpwxGoxG731/mPdEJt0fPwGeNm8H3iIOqgqTpZeAl3Ax8yB+1fw5cJEGeki7HlLO7EvKVwZGX0x/iqIuCvYq9vWM7ictI4rRgE1FdlLEadnoqGSH3dJvvPhmPZfNNGqFh9JttkpBxXjXENTCX3JJFE4T3Ai1RXKKqXr/owXZtyPbu8WSHsHtfPAchH22szjK7XtxubjB0x70PfUohcL2Ap9RzvNNbg9zms2gMWvY1IPrjSeXl2gBnrDF3GUHOI0yRS7znrNwYwsi9pPqnFXSMt2/rHIJDZ0eKbo6nwcQTK4psNpRZKlzSLKeHTRsYa6u/dQRj39z9P+NTTe0B6yaIbCRn4mPWGt3tj9ECh+67sb5EpAnaGE6npOX/mmHJ4NctAK9HJVtr3R9rNv7Sl5jS+BCZOosa/M8q9UZUQgTzLBN6Chc/grzaAtc6Ex58tiJh7LdapEHU8rQUAb6Cqjrw==
*/