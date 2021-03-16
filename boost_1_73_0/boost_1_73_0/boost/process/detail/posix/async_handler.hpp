// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_POSIX_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_POSIX_ASYNC_HANDLER_HPP_

#include <boost/process/detail/posix/handler.hpp>
#include <type_traits>

namespace boost { namespace process { namespace detail { namespace posix {

struct require_io_context {};

struct async_handler : handler_base_ext, require_io_context
{
};

template<typename T>
struct is_async_handler :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<T&> :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<const T&> :  std::is_base_of<async_handler, T> {};

template<typename T>
struct does_require_io_context : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<T&> : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<const T&> : std::is_base_of<require_io_context, T> {};


}}}}

#endif /* BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_ */

/* async_handler.hpp
GpYtRAv7mXQNfPUJxJpb4NMPXWDST1cifjdF/6GfT79h0ZINRL8ixk/5BvFnFvw7fNa96L+N4OFa6NDTCITpQcSeBqb97mRNS4vqfmpRxp8W7XvcpMawz2fGGXRdgWmve6iVzu8STkQk7DUX9cHPvzHaosummhT6h2jdjybNRhuOXQb5jIdfgA0+D9nmvYTYttKi1x5D3gG5vwj7O33MRA5iUh/ErudB86qa4Bf2/OT9Ju0DY2/2xpgNPm84+us=
*/