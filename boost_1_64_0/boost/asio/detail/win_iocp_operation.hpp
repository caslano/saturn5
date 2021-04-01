//
// detail/win_iocp_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/handler_tracking.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_iocp_io_context;

// Base class for all operations. A function pointer is used instead of virtual
// functions to avoid the associated overhead.
class win_iocp_operation
  : public OVERLAPPED
    BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER
{
public:
  typedef win_iocp_operation operation_type;

  void complete(void* owner, const boost::system::error_code& ec,
      std::size_t bytes_transferred)
  {
    func_(owner, this, ec, bytes_transferred);
  }

  void destroy()
  {
    func_(0, this, boost::system::error_code(), 0);
  }

protected:
  typedef void (*func_type)(
      void*, win_iocp_operation*,
      const boost::system::error_code&, std::size_t);

  win_iocp_operation(func_type func)
    : next_(0),
      func_(func)
  {
    reset();
  }

  // Prevents deletion through this type.
  ~win_iocp_operation()
  {
  }

  void reset()
  {
    Internal = 0;
    InternalHigh = 0;
    Offset = 0;
    OffsetHigh = 0;
    hEvent = 0;
    ready_ = 0;
  }

private:
  friend class op_queue_access;
  friend class win_iocp_io_context;
  win_iocp_operation* next_;
  func_type func_;
  long ready_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP

/* win_iocp_operation.hpp
ZVb3aOaenRHOUBY3id+vYyuHBUT6uwqWbj7H9COy/Ld502XPu+Cl9NrjDsMrAiphscwnXohnFCIpJedH/blGmUMbj+tHpBAvcy0V+OLwPdJc/doGhK5R3lV9AUgOoqVmiVm2AfSn0N5WUJL1UnyW5CND/Gmdue6mHiQ2FdqbVvS/Q7/8Nl6tMmT6Umnhe7WNnvPTCaG3w+BuJAALuP+Bp70AbUrZ29n80nOBBhCRAHWEggJTrqUrNFI1ugf8f7qyYbeif8MKkNpZPMp5N0fwA9qLisWlT06YAGMW/13z/eUqOcR19vceDQu68xtTDLkFsyl+bu97oTQR/yN6TV+zIyAKHJ1KgrUWT3DFiIwXYasINVpTAnHyAd7GS+roe8l6JBMR89IN2OB5Nw1wVj4bnbHIu5P5rH9wZDBS0uF1X3fnivqcWd2leqgsxT6TDG94OK5L8uzvw6SQsbXW17Xor4VoexRULIeesUdqR63sDGz9rdR5PsZqI4nF3PzQkFLwLaO9aUmGvT2kivMGcmlLs5lIwZBdsIOVt+ZN21d8gu3k43OhCdiyddCQKA==
*/