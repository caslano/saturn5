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
AgAACgAAAAgALWdKUhIzls+hAQAALwMAADoACQAAAAAAAQAAAAAA21MsAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkMxMS9zcmMvY3VybC52Y3hwcm9qLmZpbHRlcnNVVAUAAbZIJGBQSwECAAAKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAIgAJAAAAAAAAABAAAADdVSwAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzEyL1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLP5dsBGQAAACAAAAAsAAkAAAAAAAEAAAAAACZWLABjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDMTIvLmdpdGlnbm9yZVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlI+PGnImAcAAI59AAAuAAkAAAAAAAEAAAAAAJJWLABjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDMTIvY3VybC1hbGwuc2xuVVQFAAG2SCRgUEsBAgAACgAAAAAALWdKUgAAAAAAAAAAAAAAACYACQAAAAAAAAAQAAAAf14sAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkMxMi9saWIvVVQFAAG2SCRg
*/