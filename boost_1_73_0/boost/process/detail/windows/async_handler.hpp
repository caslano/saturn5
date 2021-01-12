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
b+kkAaOMml5xFDCeGT/EejNtzcGv/D1YoGnHMJXrgpQrIBb3otFBQW/vcQ0dkiqz+GVt/JFT/anYdtHeCv3JdD9TvZM7Epb32tvrXDlw/4TdmEIYjjf0kS3pUcirJL8tuTSz9NBHnI0i5IZJLtTiTp33USnyvKnwV94Xpu6HsZms1dn61PtBJXMJS/ZJ3TGRJOl3J6WHjqhjeSobdTDPF1Dn/uy1KKczBtIcMboP49nGSPlS
*/