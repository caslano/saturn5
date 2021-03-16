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
pTB7tknNNu6bY97/UnYt4FEVWbruvd2dR4d0EiAEEqDBBsGohIcSCGg6BKfbTXiIIszyMIagKI8YuhEZh+3QicJc4mZ9O+osM+LbHQHHSFBZwisokgEcBXyMsKJLbBAUleAsZs45det0pxPcmXxf56/6b1XdW3XvrTp1btU5Z1xpySXmQZ95xJVe4nHPdy09kjjf71r5jj98Xnetwl4PN0SA4NaquxqKNFdDMu6EkJ6N0NdTEaV412fsL8nd41s=
*/