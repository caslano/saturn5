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
OfrJuXJYcenKbkf3Iag+17m/rS6HW/5RvtGOPS2pmNjicJMK2OY2ZW3HHyg8ndr7/OYK2HJmpJfpbFQ/OgEtg5gK+PQ0b4nFgZ801dnGzEGhEsxErvNqz+D+e/wGf0YlPDe78+MoT9eSyqh6zTtSCQ8dn34oPYrqw77n6tPFlWDV+4ZzZjJqP2rP9+xe7yBgsGpU4ToFXL7sBUvfwd00zfyCWlQf+mautZffwbKApqM3bVD5PXy0hbXvoP8oE6EgApU/8cyANYOrIHV/44p+HVD6zTpFhz2q4PzaUTn3t5XRlNzoBba3q6B16fLGra4FNNVd/5bflyqInfSys0UHFJ+UvPI/kZH51WK5LkSMuiIxGoRVkyOd1f+VrMz/KJaVPWv+ISvX/beycgT1v5CVTWr+yMq8mn/KyrY1f2RlQfUfWVlY/V/Kytou4riE/5Sb2TfPgn+Xnama/6nszNWxqPq/k50Na/5NdsZhOdlZj/hSUa/5W3bu9f+37CwtL7M/QSlw+E/5meKT+wnE6HPBtsuEPHB8qNln+Nc+/8/l5853PTf03z+SV03rLFM6qigoiba7FZBqIBg16sSrDqt+wPvU9B0XbnfljY7Y/Kpuax2jOG4o47F1/r+kg3/vOt2Q3Q69muyMLeTRekK9eXLOIRDkTdp+Ka1G45V/4s09z2OgW364s8+P0YhvFTz05Wno6bn2fE4vNN8LnJqK
*/