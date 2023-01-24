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
Cm0ngoPWSUHB4qN1WyYv4ovBDPzYBytgNAi7DdinITSn9ZXV4gLhUHWai64lliROy8gQ4yUW6QBmxKiSCSlBV59qiDhaR5Oz5n4N0uh7YZJfUHKY6WlOJN4Gl4OwS36mh/6U3OyKpQfDb6NGgWTuMqI9KMNwtG5ygto2AAos9dPL0QM4yy62dl1sbc1CzJd8FYG7CEbw4Ai7MltYAqHHCORc1WzG85kN83SjtsIwQ/mTtD6rpepG+iYesrfKRGfexlhzSRn88Y4oqcCTqaQKT1ElVe4IamH5PeoqEw7plCiOi2miiWcdFw0ZGY5J2vIteXQTvsPYegeNQEN+yMiprkmhHe0Hjai20bMxmFAUSdprgCY86tTjIzjegOO4emy5o2TZqgTYQ1aXrFwlwo+77hVV7CXII7GxSOy6LCc3fI54SHfRvY2D8oRDHXKDq9CPpmtMOnQVd24cxE9+ZG+Apn2CfE+6HtGH7pbJhXHiiGCjscWeFPSOWdBY84lBOOTHtFgdmJyJqpEU/f2X2a9AJP4sz69k5yFqbgbqQEsCb/8WbsvxcqnBfiNO9kIQEFvZS3kqwuWclorpE4HLQaVLZpfDyGmq92LgCO2L8YWcFuZEEDktUIre4UWR1milzXzWyQ6+7+T4sQNHdamwWM0wCt71HOXP+Anl3lJUy+tSN8EcuAD6y78+AQwjttBfr9Oz+lwoSfPAew36aU9G
*/