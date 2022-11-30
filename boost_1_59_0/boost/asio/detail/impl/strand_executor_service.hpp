//
// detail/impl/strand_executor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/defer.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/post.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename F, typename Allocator>
class strand_executor_service::allocator_binder
{
public:
  typedef Allocator allocator_type;

  allocator_binder(BOOST_ASIO_MOVE_ARG(F) f, const Allocator& a)
    : f_(BOOST_ASIO_MOVE_CAST(F)(f)),
      allocator_(a)
  {
  }

  allocator_binder(const allocator_binder& other)
    : f_(other.f_),
      allocator_(other.allocator_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  allocator_binder(allocator_binder&& other)
    : f_(BOOST_ASIO_MOVE_CAST(F)(other.f_)),
      allocator_(BOOST_ASIO_MOVE_CAST(allocator_type)(other.allocator_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  allocator_type get_allocator() const BOOST_ASIO_NOEXCEPT
  {
    return allocator_;
  }

  void operator()()
  {
    f_();
  }

private:
  F f_;
  allocator_type allocator_;
};

template <typename Executor>
class strand_executor_service::invoker<Executor,
    typename enable_if<
      execution::is_executor<Executor>::value
    >::type>
{
public:
  invoker(const implementation_type& impl, Executor& ex)
    : impl_(impl),
      executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  invoker(const invoker& other)
    : impl_(other.impl_),
      executor_(other.executor_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  invoker(invoker&& other)
    : impl_(BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_)),
      executor_(BOOST_ASIO_MOVE_CAST(executor_type)(other.executor_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  struct on_invoker_exit
  {
    invoker* this_;

    ~on_invoker_exit()
    {
      if (push_waiting_to_ready(this_->impl_))
      {
        recycling_allocator<void> allocator;
        executor_type ex = this_->executor_;
        execution::execute(
            boost::asio::prefer(
              boost::asio::require(
                BOOST_ASIO_MOVE_CAST(executor_type)(ex),
                execution::blocking.never),
            execution::allocator(allocator)),
            BOOST_ASIO_MOVE_CAST(invoker)(*this_));
      }
    }
  };

  void operator()()
  {
    // Ensure the next handler, if any, is scheduled on block exit.
    on_invoker_exit on_exit = { this };
    (void)on_exit;

    run_ready_handlers(impl_);
  }

private:
  typedef typename decay<
      typename prefer_result<
        Executor,
        execution::outstanding_work_t::tracked_t
      >::type
    >::type executor_type;

  implementation_type impl_;
  executor_type executor_;
};

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Executor>
class strand_executor_service::invoker<Executor,
    typename enable_if<
      !execution::is_executor<Executor>::value
    >::type>
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
      if (push_waiting_to_ready(this_->impl_))
      {
        Executor ex(this_->work_.get_executor());
        recycling_allocator<void> allocator;
        ex.post(BOOST_ASIO_MOVE_CAST(invoker)(*this_), allocator);
      }
    }
  };

  void operator()()
  {
    // Ensure the next handler, if any, is scheduled on block exit.
    on_invoker_exit on_exit = { this };
    (void)on_exit;

    run_ready_handlers(impl_);
  }

private:
  implementation_type impl_;
  executor_work_guard<Executor> work_;
};

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Executor, typename Function>
inline void strand_executor_service::execute(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function,
    typename enable_if<
      can_query<Executor, execution::allocator_t<void> >::value
    >::type*)
{
  return strand_executor_service::do_execute(impl, ex,
      BOOST_ASIO_MOVE_CAST(Function)(function),
      boost::asio::query(ex, execution::allocator));
}

template <typename Executor, typename Function>
inline void strand_executor_service::execute(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function,
    typename enable_if<
      !can_query<Executor, execution::allocator_t<void> >::value
    >::type*)
{
  return strand_executor_service::do_execute(impl, ex,
      BOOST_ASIO_MOVE_CAST(Function)(function),
      std::allocator<void>());
}

template <typename Executor, typename Function, typename Allocator>
void strand_executor_service::do_execute(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a)
{
  typedef typename decay<Function>::type function_type;

  // If the executor is not never-blocking, and we are already in the strand,
  // then the function can run immediately.
  if (boost::asio::query(ex, execution::blocking) != execution::blocking.never
      && running_in_this_thread(impl))
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
        "strand_executor", impl.get(), 0, "execute"));

  // Add the function to the strand and schedule the strand if required.
  bool first = enqueue(impl, p.p);
  p.v = p.p = 0;
  if (first)
  {
    execution::execute(ex, invoker<Executor>(impl, ex));
  }
}

template <typename Executor, typename Function, typename Allocator>
void strand_executor_service::dispatch(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a)
{
  typedef typename decay<Function>::type function_type;

  // If we are already in the strand then the function can run immediately.
  if (running_in_this_thread(impl))
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
  {
    boost::asio::dispatch(ex,
        allocator_binder<invoker<Executor>, Allocator>(
          invoker<Executor>(impl, ex), a));
  }
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
  {
    boost::asio::post(ex,
        allocator_binder<invoker<Executor>, Allocator>(
          invoker<Executor>(impl, ex), a));
  }
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
  {
    boost::asio::defer(ex,
        allocator_binder<invoker<Executor>, Allocator>(
          invoker<Executor>(impl, ex), a));
  }
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP

/* strand_executor_service.hpp
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
*/