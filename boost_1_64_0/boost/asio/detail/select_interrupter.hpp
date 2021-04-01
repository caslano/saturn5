//
// detail/select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
# include <boost/asio/detail/socket_select_interrupter.hpp>
#elif defined(BOOST_ASIO_HAS_EVENTFD)
# include <boost/asio/detail/eventfd_select_interrupter.hpp>
#else
# include <boost/asio/detail/pipe_select_interrupter.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
typedef socket_select_interrupter select_interrupter;
#elif defined(BOOST_ASIO_HAS_EVENTFD)
typedef eventfd_select_interrupter select_interrupter;
#else
typedef pipe_select_interrupter select_interrupter;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP

/* select_interrupter.hpp
UOeemT8FS+tAYFxVqO59CNBosy4JqyTssR260YvPCdZhA8zrpGAcAXmtZgWHptM4hDZER8+4RWSi7DO4aU+K/HiTzsl5EKJx0ZVLVc6/d1HoPhQ1r0vcawpXuMSbuwaH4WgyVv9yrDVFQ68upE1eet0gP7jWMUyku9MRpUYN7+0q0fWx/tC5Rft3TL35I5NNVF/o8OHct/xeBIjtTOrH2SLwpAuk/eILteo/LGTi1/7yuorL0iOz9aLYz418SjueeXMmDg9v9TK3pei7nvrlQ3GxtGtG0XKEA1hNUc2/T505Lo4OCwTnui/hicxNSPe7GLTJbK4bN5V5iSdKgnPnvXG2PKigUVDhae77HJK79Bf0Ow3okfn/5NEgJodJbOM8wdmv9VYOFonb9O/MJYfxTOLF09XBmqkZK9GdYXxeOY3p9xD5r8A/NvULdIDOBHFG268Uky4KzVvBWpQ+LqlUoDwMPRkyDo8kxO/L91/UgXp8f/6wecv7jtfVC3hBLPwNb5+C/EF1ujgs6wTo/4l8Oq22JBILjjv/zDExqdRSH2+Lc30SGUSvpYsb4A==
*/