//
// detail/null_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_NULL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/scheduler_operation.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_reactor
  : public execution_context_service_base<null_reactor>
{
public:
  // Constructor.
  null_reactor(boost::asio::execution_context& ctx)
    : execution_context_service_base<null_reactor>(ctx)
  {
  }

  // Destructor.
  ~null_reactor()
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
  }

  // No-op because should never be called.
  void run(long /*usec*/, op_queue<scheduler_operation>& /*ops*/)
  {
  }

  // No-op.
  void interrupt()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_NULL_REACTOR_HPP

/* null_reactor.hpp
7qv4IVP6MMUVkkhZMJv9e2V0cKDpXHk1Awh6AWYeHX43kt+nnV/3R3vhwNSRaGaOwmAVN1weORzFyaWAUemNcbvfqGX9ImKyTNyUcpUIVrDar/I+SiEx7Q9LFg9+sZRSWYKpOAJ5pEPJ6d0InrJG+P7rLZg2TWXkmx0z2okUa1J3s1S8MguJyxUWe4HTND5sxBwrUG9qWJfoiCpMwy+hChsLDXfQd88qODXAuVOLt16VckOxRZZbBl8IMGQIoWXRWYsS0iylnEXViX3MSIglDq0teFCWZjvWz1R+8AGBXccAiWWhjbp/AdfcpKgoaClbIJcxpmNwPXrW9GVbKOuZXfQeomQ9lLpHFIJks4xaHO5Ztko4SXunb3sKkFjDhOdj1aA6dBMFsEX9fMbEacZAPeDD44jFRPeQCbMm5DwEC8hutcqvumTchvSsJ2bRQfDerhUDuSphesxEF8qli4QZ17dYIQ9mt4YPSXtJIRZ5gGBnL+CTLN7KnXkxxYr+tFUH/LWojVAtRB2cbuDipo7wvs/BP3XkIGxMY/80BdSsYdHzXt2o2JhtgMUgqA==
*/