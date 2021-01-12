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
tA9UhPsRwZzYjzTZWzLS9Be9k7A3CcMdaXIFz2W57ZtdSmDPAS7G2Vj4vN7V77vlg1jX7PS1IFzO3FUdkQ3ln1pcYx3j+YPi0ZHxHfX4mGS2LcecdlfEmtPSaJ7y6yyCzsYqc2EiOid0zCEfrEMOQtVsFHGNDddxOoktp6jKMVfwVmva+RqzIPKuU+dZiWwGcs7J0nJfZsN9UJecOmOXAFtiGsxB7v3zmtREqPKN9UIEZqCm
*/