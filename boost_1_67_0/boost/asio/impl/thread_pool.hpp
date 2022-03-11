//
// impl/thread_pool.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_THREAD_POOL_HPP
#define BOOST_ASIO_IMPL_THREAD_POOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/executor_op.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
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

inline thread_pool&
thread_pool::executor_type::context() const BOOST_ASIO_NOEXCEPT
{
  return pool_;
}

inline void
thread_pool::executor_type::on_work_started() const BOOST_ASIO_NOEXCEPT
{
  pool_.scheduler_.work_started();
}

inline void thread_pool::executor_type::on_work_finished()
const BOOST_ASIO_NOEXCEPT
{
  pool_.scheduler_.work_finished();
}

template <typename Function, typename Allocator>
void thread_pool::executor_type::dispatch(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Invoke immediately if we are already inside the thread pool.
  if (pool_.scheduler_.can_dispatch())
  {
    // Make a local, non-const copy of the function.
    function_type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));

    detail::fenced_block b(detail::fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
    return;
  }

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((pool_, *p.p,
        "thread_pool", &this->context(), 0, "dispatch"));

  pool_.scheduler_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Function, typename Allocator>
void thread_pool::executor_type::post(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((pool_, *p.p,
        "thread_pool", &this->context(), 0, "post"));

  pool_.scheduler_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Function, typename Allocator>
void thread_pool::executor_type::defer(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((pool_, *p.p,
        "thread_pool", &this->context(), 0, "defer"));

  pool_.scheduler_.post_immediate_completion(p.p, true);
  p.v = p.p = 0;
}

inline bool
thread_pool::executor_type::running_in_this_thread() const BOOST_ASIO_NOEXCEPT
{
  return pool_.scheduler_.can_dispatch();
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_THREAD_POOL_HPP

/* thread_pool.hpp
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
*/