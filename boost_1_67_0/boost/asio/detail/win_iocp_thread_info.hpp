//
// detail/win_iocp_thread_info.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/thread_info_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct win_iocp_thread_info : public thread_info_base
{
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

/* win_iocp_thread_info.hpp
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
*/