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
IbuGqfh9Eowxz+ALSmUPJdr+5/rXSoXrN5H62ypk+mXetzxjYCK9WBjnFQpI5ROajvlnJfLJU9GwfMQzHk+2LK9cev4/wuZX31KGd1JJKnp5FUNvvZd+m6Ixh7G1Xjgd0PP8VX6hoaofgiR6NxWaRhwcCkx3BMXQh8bgwZzzog5MTZw5xTBvq9y92WF42y596hoiGDeuhvqfrYhQy0aTV8TXUssfiE5fu0hxPJXveCD+Ar62jcenHzooyR67ytcMnQUaEAZ7K+qC4AwJ+UCtr/foxEE03ed6L1w7Pz03urSxf/ebEzYCjlKr+3+cHNnygllxth/qedZ+s0khPL3sXxHt5BPt73VXfgo3Dyj6s9X96dgGezOgpQf+1c8eloFLxPZlaFtjoI+j/gPVtpD6HlQ3GNm0Iolig8CibeXCXPsSiGTsswzObrjlE/rM1Ex/lzlHvVRvvk5lVjhQ7j4xTmg+FZI5ksBj7xptLGZOJBqkIZwlZrF6XsdzYDHP8V2uVkPYtWGnxm++mPxHgFb3n5cHpgbF663JJXTJEJcb28uVtjCfqV+IM02T/dnjJ0SUMZPBt7GdV69daSG0U8FhJbeSoZGVT7Lxd3RJTitmldhPKIdvDL5pRrdwryZuxyurzVT9cW1+t6Dplw+cwLxd4PYFQoOY/91TPC2FUJdvUeEFgIIZS9Ksz6Ma61ySYJupJQxL6LyPEY3ZF9vE
*/