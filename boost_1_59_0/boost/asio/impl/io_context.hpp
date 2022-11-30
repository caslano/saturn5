//
// impl/io_context.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_IO_CONTEXT_HPP
#define BOOST_ASIO_IMPL_IO_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/completion_handler.hpp>
#include <boost/asio/detail/executor_op.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/service_registry.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(GENERATING_DOCUMENTATION)

template <typename Service>
inline Service& use_service(io_context& ioc)
{
  // Check that Service meets the necessary type requirements.
  (void)static_cast<execution_context::service*>(static_cast<Service*>(0));
  (void)static_cast<const execution_context::id*>(&Service::id);

  return ioc.service_registry_->template use_service<Service>(ioc);
}

template <>
inline detail::io_context_impl& use_service<detail::io_context_impl>(
    io_context& ioc)
{
  return ioc.impl_;
}

#endif // !defined(GENERATING_DOCUMENTATION)

inline io_context::executor_type
io_context::get_executor() BOOST_ASIO_NOEXCEPT
{
  return executor_type(*this);
}

#if defined(BOOST_ASIO_HAS_CHRONO)

template <typename Rep, typename Period>
std::size_t io_context::run_for(
    const chrono::duration<Rep, Period>& rel_time)
{
  return this->run_until(chrono::steady_clock::now() + rel_time);
}

template <typename Clock, typename Duration>
std::size_t io_context::run_until(
    const chrono::time_point<Clock, Duration>& abs_time)
{
  std::size_t n = 0;
  while (this->run_one_until(abs_time))
    if (n != (std::numeric_limits<std::size_t>::max)())
      ++n;
  return n;
}

template <typename Rep, typename Period>
std::size_t io_context::run_one_for(
    const chrono::duration<Rep, Period>& rel_time)
{
  return this->run_one_until(chrono::steady_clock::now() + rel_time);
}

template <typename Clock, typename Duration>
std::size_t io_context::run_one_until(
    const chrono::time_point<Clock, Duration>& abs_time)
{
  typename Clock::time_point now = Clock::now();
  while (now < abs_time)
  {
    typename Clock::duration rel_time = abs_time - now;
    if (rel_time > chrono::seconds(1))
      rel_time = chrono::seconds(1);

    boost::system::error_code ec;
    std::size_t s = impl_.wait_one(
        static_cast<long>(chrono::duration_cast<
          chrono::microseconds>(rel_time).count()), ec);
    boost::asio::detail::throw_error(ec);

    if (s || impl_.stopped())
      return s;

    now = Clock::now();
  }

  return 0;
}

#endif // defined(BOOST_ASIO_HAS_CHRONO)

#if !defined(BOOST_ASIO_NO_DEPRECATED)

inline void io_context::reset()
{
  restart();
}

struct io_context::initiate_dispatch
{
  template <typename LegacyCompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler,
      io_context* self) const
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a LegacyCompletionHandler.
    BOOST_ASIO_LEGACY_COMPLETION_HANDLER_CHECK(
        LegacyCompletionHandler, handler) type_check;

    detail::non_const_lvalue<LegacyCompletionHandler> handler2(handler);
    if (self->impl_.can_dispatch())
    {
      detail::fenced_block b(detail::fenced_block::full);
      boost_asio_handler_invoke_helpers::invoke(
          handler2.value, handler2.value);
    }
    else
    {
      // Allocate and construct an operation to wrap the handler.
      typedef detail::completion_handler<
        typename decay<LegacyCompletionHandler>::type, executor_type> op;
      typename op::ptr p = { detail::addressof(handler2.value),
        op::ptr::allocate(handler2.value), 0 };
      p.p = new (p.v) op(handler2.value, self->get_executor());

      BOOST_ASIO_HANDLER_CREATION((*self, *p.p,
            "io_context", self, 0, "dispatch"));

      self->impl_.do_dispatch(p.p);
      p.v = p.p = 0;
    }
  }
};

template <typename LegacyCompletionHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(LegacyCompletionHandler, void ())
io_context::dispatch(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler)
{
  return async_initiate<LegacyCompletionHandler, void ()>(
      initiate_dispatch(), handler, this);
}

struct io_context::initiate_post
{
  template <typename LegacyCompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler,
      io_context* self) const
  {
    // If you get an error on the following line it means that your handler does
    // not meet the documented type requirements for a LegacyCompletionHandler.
    BOOST_ASIO_LEGACY_COMPLETION_HANDLER_CHECK(
        LegacyCompletionHandler, handler) type_check;

    detail::non_const_lvalue<LegacyCompletionHandler> handler2(handler);

    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler2.value);

    // Allocate and construct an operation to wrap the handler.
    typedef detail::completion_handler<
      typename decay<LegacyCompletionHandler>::type, executor_type> op;
    typename op::ptr p = { detail::addressof(handler2.value),
        op::ptr::allocate(handler2.value), 0 };
    p.p = new (p.v) op(handler2.value, self->get_executor());

    BOOST_ASIO_HANDLER_CREATION((*self, *p.p,
          "io_context", self, 0, "post"));

    self->impl_.post_immediate_completion(p.p, is_continuation);
    p.v = p.p = 0;
  }
};

template <typename LegacyCompletionHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(LegacyCompletionHandler, void ())
io_context::post(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler)
{
  return async_initiate<LegacyCompletionHandler, void ()>(
      initiate_post(), handler, this);
}

template <typename Handler>
#if defined(GENERATING_DOCUMENTATION)
unspecified
#else
inline detail::wrapped_handler<io_context&, Handler>
#endif
io_context::wrap(Handler handler)
{
  return detail::wrapped_handler<io_context&, Handler>(*this, handler);
}

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Allocator, uintptr_t Bits>
io_context::basic_executor_type<Allocator, Bits>&
io_context::basic_executor_type<Allocator, Bits>::operator=(
    const basic_executor_type& other) BOOST_ASIO_NOEXCEPT
{
  if (this != &other)
  {
    static_cast<Allocator&>(*this) = static_cast<const Allocator&>(other);
    io_context* old_io_context = context_ptr();
    target_ = other.target_;
    if (Bits & outstanding_work_tracked)
    {
      if (context_ptr())
        context_ptr()->impl_.work_started();
      if (old_io_context)
        old_io_context->impl_.work_finished();
    }
  }
  return *this;
}

#if defined(BOOST_ASIO_HAS_MOVE)
template <typename Allocator, uintptr_t Bits>
io_context::basic_executor_type<Allocator, Bits>&
io_context::basic_executor_type<Allocator, Bits>::operator=(
    basic_executor_type&& other) BOOST_ASIO_NOEXCEPT
{
  if (this != &other)
  {
    static_cast<Allocator&>(*this) = static_cast<Allocator&&>(other);
    io_context* old_io_context = context_ptr();
    target_ = other.target_;
    if (Bits & outstanding_work_tracked)
    {
      other.target_ = 0;
      if (old_io_context)
        old_io_context->impl_.work_finished();
    }
  }
  return *this;
}
#endif // defined(BOOST_ASIO_HAS_MOVE)

template <typename Allocator, uintptr_t Bits>
inline bool io_context::basic_executor_type<Allocator,
    Bits>::running_in_this_thread() const BOOST_ASIO_NOEXCEPT
{
  return context_ptr()->impl_.can_dispatch();
}

template <typename Allocator, uintptr_t Bits>
template <typename Function>
void io_context::basic_executor_type<Allocator, Bits>::execute(
    BOOST_ASIO_MOVE_ARG(Function) f) const
{
  typedef typename decay<Function>::type function_type;

  // Invoke immediately if the blocking.possibly property is enabled and we are
  // already inside the thread pool.
  if ((bits() & blocking_never) == 0 && context_ptr()->impl_.can_dispatch())
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
      context_ptr()->impl_.capture_current_exception();
      return;
    }
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
       //   && !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator, detail::operation> op;
  typename op::ptr p = {
      detail::addressof(static_cast<const Allocator&>(*this)),
      op::ptr::allocate(static_cast<const Allocator&>(*this)), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f),
      static_cast<const Allocator&>(*this));

  BOOST_ASIO_HANDLER_CREATION((*context_ptr(), *p.p,
        "io_context", context_ptr(), 0, "execute"));

  context_ptr()->impl_.post_immediate_completion(p.p,
      (bits() & relationship_continuation) != 0);
  p.v = p.p = 0;
}

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
template <typename Allocator, uintptr_t Bits>
inline io_context& io_context::basic_executor_type<
    Allocator, Bits>::context() const BOOST_ASIO_NOEXCEPT
{
  return *context_ptr();
}

template <typename Allocator, uintptr_t Bits>
inline void io_context::basic_executor_type<Allocator,
    Bits>::on_work_started() const BOOST_ASIO_NOEXCEPT
{
  context_ptr()->impl_.work_started();
}

template <typename Allocator, uintptr_t Bits>
inline void io_context::basic_executor_type<Allocator,
    Bits>::on_work_finished() const BOOST_ASIO_NOEXCEPT
{
  context_ptr()->impl_.work_finished();
}

template <typename Allocator, uintptr_t Bits>
template <typename Function, typename OtherAllocator>
void io_context::basic_executor_type<Allocator, Bits>::dispatch(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Invoke immediately if we are already inside the thread pool.
  if (context_ptr()->impl_.can_dispatch())
  {
    // Make a local, non-const copy of the function.
    function_type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));

    detail::fenced_block b(detail::fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
    return;
  }

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type,
      OtherAllocator, detail::operation> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((*context_ptr(), *p.p,
        "io_context", context_ptr(), 0, "dispatch"));

  context_ptr()->impl_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Allocator, uintptr_t Bits>
template <typename Function, typename OtherAllocator>
void io_context::basic_executor_type<Allocator, Bits>::post(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type,
      OtherAllocator, detail::operation> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((*context_ptr(), *p.p,
        "io_context", context_ptr(), 0, "post"));

  context_ptr()->impl_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Allocator, uintptr_t Bits>
template <typename Function, typename OtherAllocator>
void io_context::basic_executor_type<Allocator, Bits>::defer(
    BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type,
      OtherAllocator, detail::operation> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((*context_ptr(), *p.p,
        "io_context", context_ptr(), 0, "defer"));

  context_ptr()->impl_.post_immediate_completion(p.p, true);
  p.v = p.p = 0;
}
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#if !defined(BOOST_ASIO_NO_DEPRECATED)
inline io_context::work::work(boost::asio::io_context& io_context)
  : io_context_impl_(io_context.impl_)
{
  io_context_impl_.work_started();
}

inline io_context::work::work(const work& other)
  : io_context_impl_(other.io_context_impl_)
{
  io_context_impl_.work_started();
}

inline io_context::work::~work()
{
  io_context_impl_.work_finished();
}

inline boost::asio::io_context& io_context::work::get_io_context()
{
  return static_cast<boost::asio::io_context&>(io_context_impl_.context());
}
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

inline boost::asio::io_context& io_context::service::get_io_context()
{
  return static_cast<boost::asio::io_context&>(context());
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_IO_CONTEXT_HPP

/* io_context.hpp
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
*/