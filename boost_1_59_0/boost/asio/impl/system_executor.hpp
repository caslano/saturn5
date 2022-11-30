//
// impl/system_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SYSTEM_EXECUTOR_HPP
#define BOOST_ASIO_IMPL_SYSTEM_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/executor_op.hpp>
#include <boost/asio/detail/global.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/system_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

template <typename Blocking, typename Relationship, typename Allocator>
inline system_context&
basic_system_executor<Blocking, Relationship, Allocator>::query(
    execution::context_t) BOOST_ASIO_NOEXCEPT
{
  return detail::global<system_context>();
}

template <typename Blocking, typename Relationship, typename Allocator>
inline std::size_t
basic_system_executor<Blocking, Relationship, Allocator>::query(
    execution::occupancy_t) const BOOST_ASIO_NOEXCEPT
{
  return detail::global<system_context>().num_threads_;
}

template <typename Blocking, typename Relationship, typename Allocator>
template <typename Function>
inline void
basic_system_executor<Blocking, Relationship, Allocator>::do_execute(
    BOOST_ASIO_MOVE_ARG(Function) f, execution::blocking_t::possibly_t) const
{
  // Obtain a non-const instance of the function.
  detail::non_const_lvalue<Function> f2(f);

#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  try
  {
#endif// !defined(BOOST_ASIO_NO_EXCEPTIONS)
    detail::fenced_block b(detail::fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(f2.value, f2.value);
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }
  catch (...)
  {
    std::terminate();
  }
#endif// !defined(BOOST_ASIO_NO_EXCEPTIONS)
}

template <typename Blocking, typename Relationship, typename Allocator>
template <typename Function>
inline void
basic_system_executor<Blocking, Relationship, Allocator>::do_execute(
    BOOST_ASIO_MOVE_ARG(Function) f, execution::blocking_t::always_t) const
{
  // Obtain a non-const instance of the function.
  detail::non_const_lvalue<Function> f2(f);

#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  try
  {
#endif// !defined(BOOST_ASIO_NO_EXCEPTIONS)
    detail::fenced_block b(detail::fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(f2.value, f2.value);
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }
  catch (...)
  {
    std::terminate();
  }
#endif// !defined(BOOST_ASIO_NO_EXCEPTIONS)
}

template <typename Blocking, typename Relationship, typename Allocator>
template <typename Function>
void basic_system_executor<Blocking, Relationship, Allocator>::do_execute(
    BOOST_ASIO_MOVE_ARG(Function) f, execution::blocking_t::never_t) const
{
  system_context& ctx = detail::global<system_context>();

  // Allocate and construct an operation to wrap the function.
  typedef typename decay<Function>::type function_type;
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(allocator_),
      op::ptr::allocate(allocator_), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), allocator_);

  if (is_same<Relationship, execution::relationship_t::continuation_t>::value)
  {
    BOOST_ASIO_HANDLER_CREATION((ctx, *p.p,
          "system_executor", &ctx, 0, "execute(blk=never,rel=cont)"));
  }
  else
  {
    BOOST_ASIO_HANDLER_CREATION((ctx, *p.p,
          "system_executor", &ctx, 0, "execute(blk=never,rel=fork)"));
  }

  ctx.scheduler_.post_immediate_completion(p.p,
      is_same<Relationship, execution::relationship_t::continuation_t>::value);
  p.v = p.p = 0;
}

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
template <typename Blocking, typename Relationship, typename Allocator>
inline system_context& basic_system_executor<
    Blocking, Relationship, Allocator>::context() const BOOST_ASIO_NOEXCEPT
{
  return detail::global<system_context>();
}

template <typename Blocking, typename Relationship, typename Allocator>
template <typename Function, typename OtherAllocator>
void basic_system_executor<Blocking, Relationship, Allocator>::dispatch(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator&) const
{
  typename decay<Function>::type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));
  boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
}

template <typename Blocking, typename Relationship, typename Allocator>
template <typename Function, typename OtherAllocator>
void basic_system_executor<Blocking, Relationship, Allocator>::post(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const
{
  typedef typename decay<Function>::type function_type;

  system_context& ctx = detail::global<system_context>();

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, OtherAllocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((ctx, *p.p,
        "system_executor", &this->context(), 0, "post"));

  ctx.scheduler_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Blocking, typename Relationship, typename Allocator>
template <typename Function, typename OtherAllocator>
void basic_system_executor<Blocking, Relationship, Allocator>::defer(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const
{
  typedef typename decay<Function>::type function_type;

  system_context& ctx = detail::global<system_context>();

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, OtherAllocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((ctx, *p.p,
        "system_executor", &this->context(), 0, "defer"));

  ctx.scheduler_.post_immediate_completion(p.p, true);
  p.v = p.p = 0;
}
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SYSTEM_EXECUTOR_HPP

/* system_executor.hpp
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
*/