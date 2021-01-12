//
// detail/reactor_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_FWD_HPP
#define BOOST_ASIO_DETAIL_REACTOR_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)
typedef class null_reactor reactor;
#elif defined(BOOST_ASIO_HAS_IOCP)
typedef class select_reactor reactor;
#elif defined(BOOST_ASIO_HAS_EPOLL)
typedef class epoll_reactor reactor;
#elif defined(BOOST_ASIO_HAS_KQUEUE)
typedef class kqueue_reactor reactor;
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
typedef class dev_poll_reactor reactor;
#else
typedef class select_reactor reactor;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_REACTOR_FWD_HPP

/* reactor_fwd.hpp
wr1YGG5YbZV9U4w56uoMDVbTtcfdd1MyEZz3hjFyX8Z2h8dcO+iz7jM121Qrm7zQsJgNAOjzhfAUITymkKNpLLFI2hpfMt+Cc9CNlVCk1peHONV6mVNSI/uQQzr1zlrfNITohzaY2byyajLOe1AH2Ii5MX3IP6qRSiD8VFMfsu9KSfLTFMVBa40kqf/H/zfteGmJP1Oijq6JqVKeYuXY+7F2Bxca+cexqpysvVATvi56WuDl
*/