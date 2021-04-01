//
// detail/scheduler_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCHEDULER_OPERATION_HPP
#define BOOST_ASIO_DETAIL_SCHEDULER_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/system/error_code.hpp>
#include <boost/asio/detail/handler_tracking.hpp>
#include <boost/asio/detail/op_queue.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class scheduler;

// Base class for all operations. A function pointer is used instead of virtual
// functions to avoid the associated overhead.
class scheduler_operation BOOST_ASIO_INHERIT_TRACKED_HANDLER
{
public:
  typedef scheduler_operation operation_type;

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
  typedef void (*func_type)(void*,
      scheduler_operation*,
      const boost::system::error_code&, std::size_t);

  scheduler_operation(func_type func)
    : next_(0),
      func_(func),
      task_result_(0)
  {
  }

  // Prevents deletion through this type.
  ~scheduler_operation()
  {
  }

private:
  friend class op_queue_access;
  scheduler_operation* next_;
  func_type func_;
protected:
  friend class scheduler;
  unsigned int task_result_; // Passed into bytes transferred.
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCHEDULER_OPERATION_HPP

/* scheduler_operation.hpp
eLoDgAor6xmPQ+j1KOmxtbea2bAkoGxqoq+dCU8t4WgXPDq8FH84i0lNBPHMdWjrAjpPCwdPkEpPDi+0FHeLPdHGqDFv+Yr8DT/hlH2m2eUyOJL/+6M7VE4J9+zAoljlRk7Cm2Mav2phoKkOHOkZJ0pOJAvF98ceO8vwgoOR445/jAD02bRPzvlzyx1E7eCWuE8VHzoc0Ri7XoIX+6Z+Cp4VoPOIUpmGzW2GA8KWyCWQq+dv53qRWgikEHc7V0SpHT262yYQYL7doFO9Y3Szz1MEnHEBOK7AqJwSbZHEFxf1ZLOzDoqtysgf7tnnmBmzDoaDSZvP1oWbPgXUQv9XCsU9cIgtAgj2NYot5UF42t3g+tdnfDNDP0v9ZnmXBBcMCRbSXzzyDjTgmkvBoqC6AvReW4BNXuI8hWIhu8e4Y/MNN2wVWyiUjcCTe/Nkt3i949f9QcTc0qBmaQ/Pg1XEexwGZbX7enjrCRAUWnVudBQc5M91CZ6k8o2ktFbGgEj+aonIL2lU8eoChc3pKpnZJnotN0R4wLnQWz4QyInx1bfj5+REyGq2YwP/9Q==
*/