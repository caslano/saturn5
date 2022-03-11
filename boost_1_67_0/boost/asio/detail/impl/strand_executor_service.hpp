//
// detail/impl/strand_executor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/call_stack.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/executor_work_guard.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Executor>
class strand_executor_service::invoker
{
public:
  invoker(const implementation_type& impl, Executor& ex)
    : impl_(impl),
      work_(ex)
  {
  }

  invoker(const invoker& other)
    : impl_(other.impl_),
      work_(other.work_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  invoker(invoker&& other)
    : impl_(BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_)),
      work_(BOOST_ASIO_MOVE_CAST(executor_work_guard<Executor>)(other.work_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  struct on_invoker_exit
  {
    invoker* this_;

    ~on_invoker_exit()
    {
      this_->impl_->mutex_->lock();
      this_->impl_->ready_queue_.push(this_->impl_->waiting_queue_);
      bool more_handlers = this_->impl_->locked_ =
        !this_->impl_->ready_queue_.empty();
      this_->impl_->mutex_->unlock();

      if (more_handlers)
      {
        Executor ex(this_->work_.get_executor());
        recycling_allocator<void> allocator;
        ex.post(BOOST_ASIO_MOVE_CAST(invoker)(*this_), allocator);
      }
    }
  };

  void operator()()
  {
    // Indicate that this strand is executing on the current thread.
    call_stack<strand_impl>::context ctx(impl_.get());

    // Ensure the next handler, if any, is scheduled on block exit.
    on_invoker_exit on_exit = { this };
    (void)on_exit;

    // Run all ready handlers. No lock is required since the ready queue is
    // accessed only within the strand.
    boost::system::error_code ec;
    while (scheduler_operation* o = impl_->ready_queue_.front())
    {
      impl_->ready_queue_.pop();
      o->complete(impl_.get(), ec, 0);
    }
  }

private:
  implementation_type impl_;
  executor_work_guard<Executor> work_;
};

template <typename Executor, typename Function, typename Allocator>
void strand_executor_service::dispatch(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a)
{
  typedef typename decay<Function>::type function_type;

  // If we are already in the strand then the function can run immediately.
  if (call_stack<strand_impl>::contains(impl.get()))
  {
    // Make a local, non-const copy of the function.
    function_type tmp(BOOST_ASIO_MOVE_CAST(Function)(function));

    fenced_block b(fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
    return;
  }

  // Allocate and construct an operation to wrap the function.
  typedef executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(function), a);

  BOOST_ASIO_HANDLER_CREATION((impl->service_->context(), *p.p,
        "strand_executor", impl.get(), 0, "dispatch"));

  // Add the function to the strand and schedule the strand if required.
  bool first = enqueue(impl, p.p);
  p.v = p.p = 0;
  if (first)
    ex.dispatch(invoker<Executor>(impl, ex), a);
}

// Request invocation of the given function and return immediately.
template <typename Executor, typename Function, typename Allocator>
void strand_executor_service::post(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a)
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(function), a);

  BOOST_ASIO_HANDLER_CREATION((impl->service_->context(), *p.p,
        "strand_executor", impl.get(), 0, "post"));

  // Add the function to the strand and schedule the strand if required.
  bool first = enqueue(impl, p.p);
  p.v = p.p = 0;
  if (first)
    ex.post(invoker<Executor>(impl, ex), a);
}

// Request invocation of the given function and return immediately.
template <typename Executor, typename Function, typename Allocator>
void strand_executor_service::defer(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a)
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(function), a);

  BOOST_ASIO_HANDLER_CREATION((impl->service_->context(), *p.p,
        "strand_executor", impl.get(), 0, "defer"));

  // Add the function to the strand and schedule the strand if required.
  bool first = enqueue(impl, p.p);
  p.v = p.p = 0;
  if (first)
    ex.defer(invoker<Executor>(impl, ex), a);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP

/* strand_executor_service.hpp
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
*/