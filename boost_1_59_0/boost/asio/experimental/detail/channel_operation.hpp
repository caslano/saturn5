//
// experimental/detail/channel_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_OPERATION_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/outstanding_work.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/prefer.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

// Base class for all channel operations. A function pointer is used instead of
// virtual functions to avoid the associated overhead.
class channel_operation BOOST_ASIO_INHERIT_TRACKED_HANDLER
{
public:
  template <typename Executor, typename = void>
  class handler_work_base;

  template <typename Handler, typename IoExecutor, typename = void>
  class handler_work;

  void destroy()
  {
    func_(this, destroy_op, 0);
  }

protected:
  enum action
  {
    destroy_op = 0,
    complete_op = 1,
    cancel_op = 2,
    close_op = 3
  };

  typedef void (*func_type)(channel_operation*, action, void*);

  channel_operation(func_type func)
    : next_(0),
      func_(func),
      cancellation_key_(0)
  {
  }

  // Prevents deletion through this type.
  ~channel_operation()
  {
  }

  friend class boost::asio::detail::op_queue_access;
  channel_operation* next_;
  func_type func_;

public:
  // The operation key used for targeted cancellation.
  void* cancellation_key_;
};

template <typename Executor, typename>
class channel_operation::handler_work_base
{
public:
  handler_work_base(int, const Executor& ex)
    : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  template <typename Function, typename Handler>
  void post(Function& function, Handler& handler)
  {
    typename associated_allocator<Handler>::type allocator =
      (get_associated_allocator)(handler);

    execution::execute(
        boost::asio::prefer(
          boost::asio::require(executor_, execution::blocking.never),
          execution::allocator(allocator)),
        BOOST_ASIO_MOVE_CAST(Function)(function));
  }

private:
  typename decay<
      typename prefer_result<Executor,
        execution::outstanding_work_t::tracked_t
      >::type
    >::type executor_;
};

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Executor>
class channel_operation::handler_work_base<Executor,
    typename enable_if<
      !execution::is_executor<Executor>::value
    >::type>
{
public:
  handler_work_base(int, const Executor& ex)
    : work_(ex)
  {
  }

  template <typename Function, typename Handler>
  void post(Function& function, Handler& handler)
  {
    typename associated_allocator<Handler>::type allocator =
      (get_associated_allocator)(handler);

    work_.get_executor().post(
        BOOST_ASIO_MOVE_CAST(Function)(function), allocator);
  }

private:
  executor_work_guard<Executor> work_;
};

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Handler, typename IoExecutor, typename>
class channel_operation::handler_work :
  channel_operation::handler_work_base<IoExecutor>,
  channel_operation::handler_work_base<
      typename associated_executor<Handler, IoExecutor>::type, IoExecutor>
{
public:
  typedef channel_operation::handler_work_base<IoExecutor> base1_type;

  typedef channel_operation::handler_work_base<
      typename associated_executor<Handler, IoExecutor>::type, IoExecutor>
    base2_type;

  handler_work(Handler& handler, const IoExecutor& io_ex) BOOST_ASIO_NOEXCEPT
    : base1_type(0, io_ex),
      base2_type(0, (get_associated_executor)(handler, io_ex))
  {
  }

  template <typename Function>
  void complete(Function& function, Handler& handler)
  {
    base2_type::post(function, handler);
  }
};

template <typename Handler, typename IoExecutor>
class channel_operation::handler_work<
    Handler, IoExecutor,
    typename enable_if<
      is_same<
        typename associated_executor<Handler,
          IoExecutor>::asio_associated_executor_is_unspecialised,
        void
      >::value
    >::type> : handler_work_base<IoExecutor>
{
public:
  typedef channel_operation::handler_work_base<IoExecutor> base1_type;

  handler_work(Handler&, const IoExecutor& io_ex) BOOST_ASIO_NOEXCEPT
    : base1_type(0, io_ex)
  {
  }

  template <typename Function>
  void complete(Function& function, Handler& handler)
  {
    base1_type::post(function, handler);
  }
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_OPERATION_HPP

/* channel_operation.hpp
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
*/