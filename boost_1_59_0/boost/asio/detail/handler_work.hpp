//
// detail/handler_work.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_WORK_HPP
#define BOOST_ASIO_DETAIL_HANDLER_WORK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/allocator.hpp>
#include <boost/asio/execution/blocking.hpp>
#include <boost/asio/execution/execute.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/outstanding_work.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/prefer.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class executor;
class io_context;

#if !defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

class any_io_executor;

#endif // !defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

namespace execution {

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename...> class any_executor;

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename, typename, typename, typename, typename,
    typename, typename, typename, typename> class any_executor;

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

} // namespace execution
namespace detail {

template <typename Executor, typename CandidateExecutor = void,
    typename IoContext = io_context,
    typename PolymorphicExecutor = executor, typename = void>
class handler_work_base
{
public:
  explicit handler_work_base(int, int, const Executor& ex) BOOST_ASIO_NOEXCEPT
    : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  template <typename OtherExecutor>
  handler_work_base(bool /*base1_owns_work*/, const Executor& ex,
      const OtherExecutor& /*candidate*/) BOOST_ASIO_NOEXCEPT
    : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  handler_work_base(const handler_work_base& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  handler_work_base(handler_work_base&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(executor_type)(other.executor_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return true;
  }

  template <typename Function, typename Handler>
  void dispatch(Function& function, Handler& handler)
  {
    execution::execute(
        boost::asio::prefer(executor_,
          execution::blocking.possibly,
          execution::allocator((get_associated_allocator)(handler))),
        BOOST_ASIO_MOVE_CAST(Function)(function));
  }

private:
  typedef typename decay<
      typename prefer_result<Executor,
        execution::outstanding_work_t::tracked_t
      >::type
    >::type executor_type;

  executor_type executor_;
};

template <typename Executor, typename CandidateExecutor,
    typename IoContext, typename PolymorphicExecutor>
class handler_work_base<Executor, CandidateExecutor,
    IoContext, PolymorphicExecutor,
    typename enable_if<
      !execution::is_executor<Executor>::value
        && (!is_same<Executor, PolymorphicExecutor>::value
          || !is_same<CandidateExecutor, void>::value)
    >::type>
{
public:
  explicit handler_work_base(int, int, const Executor& ex) BOOST_ASIO_NOEXCEPT
    : executor_(ex),
      owns_work_(true)
  {
    executor_.on_work_started();
  }

  handler_work_base(bool /*base1_owns_work*/, const Executor& ex,
      const Executor& candidate) BOOST_ASIO_NOEXCEPT
    : executor_(ex),
      owns_work_(ex != candidate)
  {
    if (owns_work_)
      executor_.on_work_started();
  }

  template <typename OtherExecutor>
  handler_work_base(bool /*base1_owns_work*/, const Executor& ex,
      const OtherExecutor& /*candidate*/) BOOST_ASIO_NOEXCEPT
    : executor_(ex),
      owns_work_(true)
  {
    executor_.on_work_started();
  }

  handler_work_base(const handler_work_base& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      owns_work_(other.owns_work_)
  {
    if (owns_work_)
      executor_.on_work_started();
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  handler_work_base(handler_work_base&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      owns_work_(other.owns_work_)
  {
    other.owns_work_ = false;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  ~handler_work_base()
  {
    if (owns_work_)
      executor_.on_work_finished();
  }

  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return owns_work_;
  }

  template <typename Function, typename Handler>
  void dispatch(Function& function, Handler& handler)
  {
    executor_.dispatch(BOOST_ASIO_MOVE_CAST(Function)(function),
        boost::asio::get_associated_allocator(handler));
  }

private:
  Executor executor_;
  bool owns_work_;
};

template <typename Executor, typename IoContext, typename PolymorphicExecutor>
class handler_work_base<Executor, void, IoContext, PolymorphicExecutor,
    typename enable_if<
      is_same<
        Executor,
        typename IoContext::executor_type
      >::value
    >::type>
{
public:
  explicit handler_work_base(int, int, const Executor&)
  {
  }

  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return false;
  }

  template <typename Function, typename Handler>
  void dispatch(Function& function, Handler& handler)
  {
    // When using a native implementation, I/O completion handlers are
    // already dispatched according to the execution context's executor's
    // rules. We can call the function directly.
    boost_asio_handler_invoke_helpers::invoke(function, handler);
  }
};

template <typename Executor, typename IoContext>
class handler_work_base<Executor, void, IoContext, Executor>
{
public:
  explicit handler_work_base(int, int, const Executor& ex) BOOST_ASIO_NOEXCEPT
#if !defined(BOOST_ASIO_NO_TYPEID)
    : executor_(
        ex.target_type() == typeid(typename IoContext::executor_type)
          ? Executor() : ex)
#else // !defined(BOOST_ASIO_NO_TYPEID)
    : executor_(ex)
#endif // !defined(BOOST_ASIO_NO_TYPEID)
  {
    if (executor_)
      executor_.on_work_started();
  }

  handler_work_base(bool /*base1_owns_work*/, const Executor& ex,
      const Executor& candidate) BOOST_ASIO_NOEXCEPT
    : executor_(ex != candidate ? ex : Executor())
  {
    if (executor_)
      executor_.on_work_started();
  }

  template <typename OtherExecutor>
  handler_work_base(const Executor& ex,
      const OtherExecutor&) BOOST_ASIO_NOEXCEPT
    : executor_(ex)
  {
    executor_.on_work_started();
  }

  handler_work_base(const handler_work_base& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_)
  {
    if (executor_)
      executor_.on_work_started();
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  handler_work_base(handler_work_base&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  ~handler_work_base()
  {
    if (executor_)
      executor_.on_work_finished();
  }

  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return !!executor_;
  }

  template <typename Function, typename Handler>
  void dispatch(Function& function, Handler& handler)
  {
    executor_.dispatch(BOOST_ASIO_MOVE_CAST(Function)(function),
        boost::asio::get_associated_allocator(handler));
  }

private:
  Executor executor_;
};

template <
#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    typename... SupportableProperties,
#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9,
#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    typename CandidateExecutor, typename IoContext,
    typename PolymorphicExecutor>
class handler_work_base<
#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    execution::any_executor<SupportableProperties...>,
#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    execution::any_executor<T1, T2, T3, T4, T5, T6, T7, T8, T9>,
#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    CandidateExecutor, IoContext, PolymorphicExecutor>
{
public:
  typedef
#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    execution::any_executor<SupportableProperties...>
#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    execution::any_executor<T1, T2, T3, T4, T5, T6, T7, T8, T9>
#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    executor_type;

  explicit handler_work_base(int, int,
      const executor_type& ex) BOOST_ASIO_NOEXCEPT
#if !defined(BOOST_ASIO_NO_TYPEID)
    : executor_(
        ex.target_type() == typeid(typename IoContext::executor_type)
          ? executor_type()
          : boost::asio::prefer(ex, execution::outstanding_work.tracked))
#else // !defined(BOOST_ASIO_NO_TYPEID)
    : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
#endif // !defined(BOOST_ASIO_NO_TYPEID)
  {
  }

  handler_work_base(bool base1_owns_work, const executor_type& ex,
      const executor_type& candidate) BOOST_ASIO_NOEXCEPT
    : executor_(
        !base1_owns_work && ex == candidate
          ? executor_type()
          : boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  template <typename OtherExecutor>
  handler_work_base(bool /*base1_owns_work*/, const executor_type& ex,
      const OtherExecutor& /*candidate*/) BOOST_ASIO_NOEXCEPT
    : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  handler_work_base(const handler_work_base& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  handler_work_base(handler_work_base&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(executor_type)(other.executor_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return !!executor_;
  }

  template <typename Function, typename Handler>
  void dispatch(Function& function, Handler&)
  {
    execution::execute(
        boost::asio::prefer(executor_, execution::blocking.possibly),
        BOOST_ASIO_MOVE_CAST(Function)(function));
  }

private:
  executor_type executor_;
};

#if !defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

template <typename Executor, typename CandidateExecutor,
    typename IoContext, typename PolymorphicExecutor>
class handler_work_base<
    Executor, CandidateExecutor,
    IoContext, PolymorphicExecutor,
    typename enable_if<
      is_same<
        Executor,
        any_io_executor
      >::value
    >::type>
{
public:
  typedef Executor executor_type;

  explicit handler_work_base(int, int,
      const executor_type& ex) BOOST_ASIO_NOEXCEPT
#if !defined(BOOST_ASIO_NO_TYPEID)
    : executor_(
        ex.target_type() == typeid(typename IoContext::executor_type)
          ? executor_type()
          : boost::asio::prefer(ex, execution::outstanding_work.tracked))
#else // !defined(BOOST_ASIO_NO_TYPEID)
    : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
#endif // !defined(BOOST_ASIO_NO_TYPEID)
  {
  }

  handler_work_base(bool base1_owns_work, const executor_type& ex,
      const executor_type& candidate) BOOST_ASIO_NOEXCEPT
    : executor_(
        !base1_owns_work && ex == candidate
          ? executor_type()
          : boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  template <typename OtherExecutor>
  handler_work_base(bool /*base1_owns_work*/, const executor_type& ex,
      const OtherExecutor& /*candidate*/) BOOST_ASIO_NOEXCEPT
    : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
  {
  }

  handler_work_base(const handler_work_base& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  handler_work_base(handler_work_base&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(executor_type)(other.executor_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return !!executor_;
  }

  template <typename Function, typename Handler>
  void dispatch(Function& function, Handler&)
  {
    execution::execute(
        boost::asio::prefer(executor_, execution::blocking.possibly),
        BOOST_ASIO_MOVE_CAST(Function)(function));
  }

private:
  executor_type executor_;
};

#endif // !defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

template <typename Handler, typename IoExecutor, typename = void>
class handler_work :
  handler_work_base<IoExecutor>,
  handler_work_base<typename associated_executor<
      Handler, IoExecutor>::type, IoExecutor>
{
public:
  typedef handler_work_base<IoExecutor> base1_type;
  typedef handler_work_base<typename associated_executor<
    Handler, IoExecutor>::type, IoExecutor> base2_type;

  handler_work(Handler& handler, const IoExecutor& io_ex) BOOST_ASIO_NOEXCEPT
    : base1_type(0, 0, io_ex),
      base2_type(base1_type::owns_work(),
          boost::asio::get_associated_executor(handler, io_ex), io_ex)
  {
  }

  template <typename Function>
  void complete(Function& function, Handler& handler)
  {
    if (!base1_type::owns_work() && !base2_type::owns_work())
    {
      // When using a native implementation, I/O completion handlers are
      // already dispatched according to the execution context's executor's
      // rules. We can call the function directly.
      boost_asio_handler_invoke_helpers::invoke(function, handler);
    }
    else
    {
      base2_type::dispatch(function, handler);
    }
  }
};

template <typename Handler, typename IoExecutor>
class handler_work<
    Handler, IoExecutor,
    typename enable_if<
      is_same<
        typename associated_executor<Handler,
          IoExecutor>::asio_associated_executor_is_unspecialised,
        void
      >::value
    >::type> : handler_work_base<IoExecutor>
{
public:
  typedef handler_work_base<IoExecutor> base1_type;

  handler_work(Handler&, const IoExecutor& io_ex) BOOST_ASIO_NOEXCEPT
    : base1_type(0, 0, io_ex)
  {
  }

  template <typename Function>
  void complete(Function& function, Handler& handler)
  {
    if (!base1_type::owns_work())
    {
      // When using a native implementation, I/O completion handlers are
      // already dispatched according to the execution context's executor's
      // rules. We can call the function directly.
      boost_asio_handler_invoke_helpers::invoke(function, handler);
    }
    else
    {
      base1_type::dispatch(function, handler);
    }
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_WORK_HPP

/* handler_work.hpp
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
*/