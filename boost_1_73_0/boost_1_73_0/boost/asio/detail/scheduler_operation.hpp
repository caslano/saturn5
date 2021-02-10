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
VWXZODAoqBZt/Pji3ljfjGtb6GUG1mGuaRztDYXhMqvH4WAoXuI6/sFI6B9AiEYiuXE/pvBj+qSpDXcRb/cCrHaZxnNIflpaPSNOXjPM/KsaI4cRnw+Jnsh+Wl8jVMUeyAIXHnfWgD+6Lheas+UfxInox/GILF4nIMSDMeODsOdTphQs6Zv+wYXktkmN7LS9ReG5KtIRCz2Uf3P1h1xXspAUxIcZZq1xDRUF/YMHUzmAVNEqDpXJyoM6FE8HNJDZTxbC3FE7aC01T9PlIbsfvj7IaZ9y5kuveEpDhp3wQXFCzx/nfZ6fnhIOlTNqoW7TUj6UX7NNEYs83zhnQITGCV89bsJXp6d2lX5uCGYoaYNQBLgJJkkca/U+x8ZMC9YmpKFftC5GGKuGSWPHM03xX2TU0pr3X/Cw7oIsJPiSoeeZd7vgj0VpT/t4JcF14fW6k9DOlWJVjrNwkb2mrZvK/O+g+W9Lr8njEKQNOxwy5fmJtuQkd2gzU6Z5DpWY1t0BNNA2zhrLmgPtpzWBFfA75jOErLuiBrA2w6yJUP8JSeg1LquBslxuUYVWh34g2ujuWC2xWoo/G3L84/Od5Sea4xMRWfoI+mLl7/Ly4odXP128+/fXby5ezVXJKnh8dpr9D1BLAwQKAAAACAAt
*/