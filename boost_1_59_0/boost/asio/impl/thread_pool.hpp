//
// impl/thread_pool.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_THREAD_POOL_HPP
#define BOOST_ASIO_IMPL_THREAD_POOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/blocking_executor_op.hpp>
#include <boost/asio/detail/bulk_executor_op.hpp>
#include <boost/asio/detail/executor_op.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline thread_pool::executor_type
thread_pool::get_executor() BOOST_ASIO_NOEXCEPT
{
  return executor_type(*this);
}

inline thread_pool::executor_type
thread_pool::executor() BOOST_ASIO_NOEXCEPT
{
  return executor_type(*this);
}

inline thread_pool::scheduler_type
thread_pool::scheduler() BOOST_ASIO_NOEXCEPT
{
  return scheduler_type(*this);
}

template <typename Allocator, unsigned int Bits>
thread_pool::basic_executor_type<Allocator, Bits>&
thread_pool::basic_executor_type<Allocator, Bits>::operator=(
    const basic_executor_type& other) BOOST_ASIO_NOEXCEPT
{
  if (this != &other)
  {
    thread_pool* old_thread_pool = pool_;
    pool_ = other.pool_;
    allocator_ = other.allocator_;
    bits_ = other.bits_;
    if (Bits & outstanding_work_tracked)
    {
      if (pool_)
        pool_->scheduler_.work_started();
      if (old_thread_pool)
        old_thread_pool->scheduler_.work_finished();
    }
  }
  return *this;
}

#if defined(BOOST_ASIO_HAS_MOVE)
template <typename Allocator, unsigned int Bits>
thread_pool::basic_executor_type<Allocator, Bits>&
thread_pool::basic_executor_type<Allocator, Bits>::operator=(
    basic_executor_type&& other) BOOST_ASIO_NOEXCEPT
{
  if (this != &other)
  {
    thread_pool* old_thread_pool = pool_;
    pool_ = other.pool_;
    allocator_ = std::move(other.allocator_);
    bits_ = other.bits_;
    if (Bits & outstanding_work_tracked)
    {
      other.pool_ = 0;
      if (old_thread_pool)
        old_thread_pool->scheduler_.work_finished();
    }
  }
  return *this;
}
#endif // defined(BOOST_ASIO_HAS_MOVE)

template <typename Allocator, unsigned int Bits>
inline bool thread_pool::basic_executor_type<Allocator,
    Bits>::running_in_this_thread() const BOOST_ASIO_NOEXCEPT
{
  return pool_->scheduler_.can_dispatch();
}

template <typename Allocator, unsigned int Bits>
template <typename Function>
void thread_pool::basic_executor_type<Allocator,
    Bits>::do_execute(BOOST_ASIO_MOVE_ARG(Function) f, false_type) const
{
  typedef typename decay<Function>::type function_type;

  // Invoke immediately if the blocking.possibly property is enabled and we are
  // already inside the thread pool.
  if ((bits_ & blocking_never) == 0 && pool_->scheduler_.can_dispatch())
  {
    // Make a local, non-const copy of the function.
    function_type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));

#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR) \
  && !defined(BOOST_ASIO_NO_EXCEPTIONS)
    try
    {
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
       //   && !defined(BOOST_ASIO_NO_EXCEPTIONS)
      detail::fenced_block b(detail::fenced_block::full);
      boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
      return;
#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR) \
  && !defined(BOOST_ASIO_NO_EXCEPTIONS)
    }
    catch (...)
    {
      pool_->scheduler_.capture_current_exception();
      return;
    }
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
       //   && !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(allocator_),
      op::ptr::allocate(allocator_), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), allocator_);

  if ((bits_ & relationship_continuation) != 0)
  {
    BOOST_ASIO_HANDLER_CREATION((*pool_, *p.p,
          "thread_pool", pool_, 0, "execute(blk=never,rel=cont)"));
  }
  else
  {
    BOOST_ASIO_HANDLER_CREATION((*pool_, *p.p,
          "thread_pool", pool_, 0, "execute(blk=never,rel=fork)"));
  }

  pool_->scheduler_.post_immediate_completion(p.p,
      (bits_ & relationship_continuation) != 0);
  p.v = p.p = 0;
}

template <typename Allocator, unsigned int Bits>
template <typename Function>
void thread_pool::basic_executor_type<Allocator,
    Bits>::do_execute(BOOST_ASIO_MOVE_ARG(Function) f, true_type) const
{
  // Obtain a non-const instance of the function.
  detail::non_const_lvalue<Function> f2(f);

  // Invoke immediately if we are already inside the thread pool.
  if (pool_->scheduler_.can_dispatch())
  {
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    try
    {
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
      detail::fenced_block b(detail::fenced_block::full);
      boost_asio_handler_invoke_helpers::invoke(f2.value, f2.value);
      return;
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    }
    catch (...)
    {
      std::terminate();
    }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }

  // Construct an operation to wrap the function.
  typedef typename decay<Function>::type function_type;
  detail::blocking_executor_op<function_type> op(f2.value);

  BOOST_ASIO_HANDLER_CREATION((*pool_, op,
        "thread_pool", pool_, 0, "execute(blk=always)"));

  pool_->scheduler_.post_immediate_completion(&op, false);
  op.wait();
}

template <typename Allocator, unsigned int Bits>
template <typename Function>
void thread_pool::basic_executor_type<Allocator, Bits>::do_bulk_execute(
    BOOST_ASIO_MOVE_ARG(Function) f, std::size_t n, false_type) const
{
  typedef typename decay<Function>::type function_type;
  typedef detail::bulk_executor_op<function_type, Allocator> op;

  // Allocate and construct operations to wrap the function.
  detail::op_queue<detail::scheduler_operation> ops;
  for (std::size_t i = 0; i < n; ++i)
  {
    typename op::ptr p = { detail::addressof(allocator_),
        op::ptr::allocate(allocator_), 0 };
    p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), allocator_, i);
    ops.push(p.p);

    if ((bits_ & relationship_continuation) != 0)
    {
      BOOST_ASIO_HANDLER_CREATION((*pool_, *p.p,
            "thread_pool", pool_, 0, "bulk_execute(blk=never,rel=cont)"));
    }
    else
    {
      BOOST_ASIO_HANDLER_CREATION((*pool_, *p.p,
            "thread_pool", pool_, 0, "bulk)execute(blk=never,rel=fork)"));
    }

    p.v = p.p = 0;
  }

  pool_->scheduler_.post_immediate_completions(n,
      ops, (bits_ & relationship_continuation) != 0);
}

template <typename Function>
struct thread_pool_always_blocking_function_adapter
{
  typename decay<Function>::type* f;
  std::size_t n;

  void operator()()
  {
    for (std::size_t i = 0; i < n; ++i)
    {
      (*f)(i);
    }
  }
};

template <typename Allocator, unsigned int Bits>
template <typename Function>
void thread_pool::basic_executor_type<Allocator, Bits>::do_bulk_execute(
    BOOST_ASIO_MOVE_ARG(Function) f, std::size_t n, true_type) const
{
  // Obtain a non-const instance of the function.
  detail::non_const_lvalue<Function> f2(f);

  thread_pool_always_blocking_function_adapter<Function>
    adapter = { detail::addressof(f2.value), n };

  this->do_execute(adapter, true_type());
}

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
template <typename Allocator, unsigned int Bits>
inline thread_pool& thread_pool::basic_executor_type<
    Allocator, Bits>::context() const BOOST_ASIO_NOEXCEPT
{
  return *pool_;
}

template <typename Allocator, unsigned int Bits>
inline void thread_pool::basic_executor_type<Allocator,
    Bits>::on_work_started() const BOOST_ASIO_NOEXCEPT
{
  pool_->scheduler_.work_started();
}

template <typename Allocator, unsigned int Bits>
inline void thread_pool::basic_executor_type<Allocator,
    Bits>::on_work_finished() const BOOST_ASIO_NOEXCEPT
{
  pool_->scheduler_.work_finished();
}

template <typename Allocator, unsigned int Bits>
template <typename Function, typename OtherAllocator>
void thread_pool::basic_executor_type<Allocator, Bits>::dispatch(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Invoke immediately if we are already inside the thread pool.
  if (pool_->scheduler_.can_dispatch())
  {
    // Make a local, non-const copy of the function.
    function_type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));

    detail::fenced_block b(detail::fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
    return;
  }

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, OtherAllocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((*pool_, *p.p,
        "thread_pool", pool_, 0, "dispatch"));

  pool_->scheduler_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Allocator, unsigned int Bits>
template <typename Function, typename OtherAllocator>
void thread_pool::basic_executor_type<Allocator, Bits>::post(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, OtherAllocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((*pool_, *p.p,
        "thread_pool", pool_, 0, "post"));

  pool_->scheduler_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Allocator, unsigned int Bits>
template <typename Function, typename OtherAllocator>
void thread_pool::basic_executor_type<Allocator, Bits>::defer(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, OtherAllocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((*pool_, *p.p,
        "thread_pool", pool_, 0, "defer"));

  pool_->scheduler_.post_immediate_completion(p.p, true);
  p.v = p.p = 0;
}
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_THREAD_POOL_HPP

/* thread_pool.hpp
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
*/