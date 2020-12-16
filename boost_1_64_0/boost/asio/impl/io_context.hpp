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
HM5n32va4wVK94ozBhYFyqZbu+Ml4pu+rZTeC/UULXXg/ckYwV+cpNrNdyZCL+B5LLFJu/kIMbcwrKv9rOOTqY3UemI9L/S5ph5YzydTPJVTtw5ftEaiPycqOQvwGARrQV/g/0u0J6t22zk9444Q9yLMpnCJNE1ycBx8vSmuoyMNu7wG2RD1XEI4LznUPnf0Az7DlPPl95jt56AfgnAVpe8keqVwO4i+Pd9pq9JvkzYzX7MEX4mOztiFbClsdHNrF1eXibMgNhLOQofG/1rYmM5Q2iey6nt9gsLJjnYUx/kZ5Nmv9OV/kwzKF0sHOA4zDuJ3G+xE5eIMz+WU370O3djFNuK3KW2Uw+Snz7p3HKW/4RB8qP1DM1ZuJpx+bM9Q+R/kmIsyLqLdMpUWdx4wrWoP+5bKcAl6Sk/tN4OMXzWvtLyymHQ873U/8C/+Fpv6HfMTEEnxvfZqwrmFcfi9jKPKRRTVU7LQKaeIj3FSLO9rjxDt4HW0gE1ikbxCnP9xK8Xf6Qi29fya4ploay7TWsrbSfi9EV5C+JsdVt82tGR7/h1E4+Aw3k3hfiSnb8QTDRUTdUR2VQtfeaFLDtL7bpOVeUM32MZZl3CerYmvAcBrILzxDpPtj3XcD1QnXTiMFTSXi8YX6PBP7lRtIXXrTTYYxvHcxb7ynrrXPE7zWWg9Ge8V4M0im0lP7B24wqOdPuwetAmPcjrC4zz+GPyoO4B9hUhPisNGFxp1MdXVMECDzhWyV0fliwUfrUSfuoPiPka9bbaR56Tg2SvsI30THkCcwQbIOnk70kLdE7JBc09Io8Xa77SFLRRM6Pau/Dwmz6c47lsa2zvkBvEkNzp9nXx3gJlePP52xfMkFEXjiaC+nldGF8GY701mneX4kPoP62+V1sft26QdSuNHZro/WfB5aC1PQJBhKt1fwnv/Hwo++bx2e/v9NML9nflUabuav2NifVdM6dGySR+ybplM6R7Zri/7AW8lnLclxfaQhrqORznKFdnu4e6MXS+PE8cvhqHiNXVFMqXiF61V91O/w3ZbmFP5PLJVdMCG2A5pU/Hwnur/jP1Jax8cweekd8UzCU++ApuxJrTzmZ7wkbWPxt33Bog/wtOe4XXKXjrh180oryxlC5Xt+A9c1se8Pmuk8Mv4itBpd1cw03QWNu9fKPys9ITF/br5Aj9V+G/9QOEXQSFLoc72SPqY2lzIQBcKV3IYszMKR1t+A/U/esfT0ibJzTLH/kkae/qvhLNLelDykswcRvvmr1O/pU2lc2lgwXa57OxVTLNonbqvN8TyG6cujJd9L/pFFvDCStwR7kycbzGDz7fwOsMga2GgVXXsd/yd5Pd2Z1hwPxtKdZBLdxpQnKiXJdjpuERfN6x/Syi9Le1XURxC11CcH/hhzb7T2c52Ju50Nn+jQvKMduSzGgy+vfdL9HeB0vaAGYA3KPqR8OtwZRJ9yUsfIoXyDYn9JKArWMaZPpXwd3VXbcgszyK9f/A+N6J3yBr8UhAIOUyhdJnyzxf0PU2yP1akDdHMrYS5RtzXZdUH2BfEuDYW+vIS4mEwh3FOE4XHGM93E3OjhZTu5fZW8WFJoG+EmUZn+xtEd2p1ILyWsmGfXdz/ZthLF/O61US3Fh4Qmbr5QDqfow9sUZa/EO5oU1noTBT0maPr0S8S6Ju+94x3j/O3KeRzNzsbD+vZopCy64rBO0xnsFVbyLMCIQNs3w3E1Yk4lgvErTD7wfD8QLQ3r/MM/u0cX21eu9ueATfM4vyTeioP8jD0qcMPSfT3EhI78B0sTys2ok+1fYpfaL9OBD7fc8N95DkKXy9nQeePxWO3pzNS0D4sZMbOVpwvcPuyXy8=
*/