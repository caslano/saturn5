//
// impl/io_context.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/detail/service_registry.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

#if !defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {

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

} // namespace asio
} // namespace boost

#endif // !defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else
# include <boost/asio/detail/scheduler.hpp>
#endif

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

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
        typename decay<LegacyCompletionHandler>::type> op;
      typename op::ptr p = { detail::addressof(handler2.value),
        op::ptr::allocate(handler2.value), 0 };
      p.p = new (p.v) op(handler2.value);

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
      typename decay<LegacyCompletionHandler>::type> op;
    typename op::ptr p = { detail::addressof(handler2.value),
        op::ptr::allocate(handler2.value), 0 };
    p.p = new (p.v) op(handler2.value);

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

inline io_context&
io_context::executor_type::context() const BOOST_ASIO_NOEXCEPT
{
  return io_context_;
}

inline void
io_context::executor_type::on_work_started() const BOOST_ASIO_NOEXCEPT
{
  io_context_.impl_.work_started();
}

inline void
io_context::executor_type::on_work_finished() const BOOST_ASIO_NOEXCEPT
{
  io_context_.impl_.work_finished();
}

template <typename Function, typename Allocator>
void io_context::executor_type::dispatch(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Invoke immediately if we are already inside the thread pool.
  if (io_context_.impl_.can_dispatch())
  {
    // Make a local, non-const copy of the function.
    function_type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));

    detail::fenced_block b(detail::fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
    return;
  }

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator, detail::operation> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((this->context(), *p.p,
        "io_context", &this->context(), 0, "dispatch"));

  io_context_.impl_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Function, typename Allocator>
void io_context::executor_type::post(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator, detail::operation> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((this->context(), *p.p,
        "io_context", &this->context(), 0, "post"));

  io_context_.impl_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Function, typename Allocator>
void io_context::executor_type::defer(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator, detail::operation> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((this->context(), *p.p,
        "io_context", &this->context(), 0, "defer"));

  io_context_.impl_.post_immediate_completion(p.p, true);
  p.v = p.p = 0;
}

inline bool
io_context::executor_type::running_in_this_thread() const BOOST_ASIO_NOEXCEPT
{
  return io_context_.impl_.can_dispatch();
}

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