//
// detail/operation.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_OPERATION_HPP
#define BOOST_ASIO_DETAIL_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_operation.hpp>
#else
# include <boost/asio/detail/scheduler_operation.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP)
typedef win_iocp_operation operation;
#else
typedef scheduler_operation operation;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_OPERATION_HPP

/* operation.hpp
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
*/