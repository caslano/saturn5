// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_

#include <boost/process/detail/windows/handler.hpp>
#include <type_traits>

namespace boost { namespace process { namespace detail { namespace windows {

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
SwECAAAKAAAACAAtZ0pS55L/IvMCAADUAwAANwAJAAAAAAABAAAAAABETjIAY3VybC1tYXN0ZXIvdGVzdHMvY2VydHMvU2VydmVyLWxvY2FsaG9zdC1sYXN0U0FOLXN2LmNzclVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlI7DvB7eQMAAOIDAAA3AAkAAAAAAAAAAAAAAJVRMgBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9TZXJ2ZXItbG9jYWxob3N0LWxhc3RTQU4tc3YuZGVyVVQFAAG2SCRgUEsBAgAACgAAAAAALWdKUgAAAAAAAAAAAAAAADcACQAAAAAAAQAAAAAAbFUyAGN1cmwtbWFzdGVyL3Rlc3RzL2NlcnRzL1NlcnZlci1sb2NhbGhvc3QtbGFzdFNBTi1zdi5kaHBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSnhGZPQUFAACLBgAANwAJAAAAAAABAAAAAADKVTIAY3VybC1tYXN0ZXIvdGVzdHMvY2VydHMvU2VydmVyLWxvY2FsaG9zdC1sYXN0U0FOLXN2LmtleVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIW+y0UehAAADIdAAA3AAkAAAAAAAEAAAAAAC1bMgBjdXJsLW1h
*/