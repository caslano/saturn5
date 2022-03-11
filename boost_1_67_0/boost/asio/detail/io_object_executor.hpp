//
// io_object_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_OBJECT_EXECUTOR_HPP
#define BOOST_ASIO_DETAIL_IO_OBJECT_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Wrap the (potentially polymorphic) executor so that we can bypass it when
// dispatching on a target executor that has a native I/O implementation.
template <typename Executor>
class io_object_executor
{
public:
  io_object_executor(const Executor& ex,
      bool native_implementation) BOOST_ASIO_NOEXCEPT
    : executor_(ex),
      has_native_impl_(native_implementation)
  {
  }

  io_object_executor(const io_object_executor& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      has_native_impl_(other.has_native_impl_)
  {
  }

  template <typename Executor1>
  io_object_executor(
      const io_object_executor<Executor1>& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.inner_executor()),
      has_native_impl_(other.has_native_implementation())
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  io_object_executor(io_object_executor&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      has_native_impl_(other.has_native_impl_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  const Executor& inner_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  bool has_native_implementation() const BOOST_ASIO_NOEXCEPT
  {
    return has_native_impl_;
  }

  execution_context& context() const BOOST_ASIO_NOEXCEPT
  {
    return executor_.context();
  }

  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
    if (is_same<Executor, io_context::executor_type>::value
        || has_native_impl_)
    {
      // When using a native implementation, work is already counted by the
      // execution context.
    }
    else
    {
      executor_.on_work_started();
    }
  }

  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
    if (is_same<Executor, io_context::executor_type>::value
        || has_native_impl_)
    {
      // When using a native implementation, work is already counted by the
      // execution context.
    }
    else
    {
      executor_.on_work_finished();
    }
  }

  template <typename F, typename A>
  void dispatch(BOOST_ASIO_MOVE_ARG(F) f, const A& a) const
  {
    if (is_same<Executor, io_context::executor_type>::value
        || has_native_impl_)
    {
      // When using a native implementation, I/O completion handlers are
      // already dispatched according to the execution context's executor's
      // rules. We can call the function directly.
#if defined(BOOST_ASIO_HAS_MOVE)
      if (is_same<F, typename decay<F>::type>::value)
      {
        boost_asio_handler_invoke_helpers::invoke(f, f);
        return;
      }
#endif // defined(BOOST_ASIO_HAS_MOVE)
      typename decay<F>::type function(BOOST_ASIO_MOVE_CAST(F)(f));
      boost_asio_handler_invoke_helpers::invoke(function, function);
    }
    else
    {
      executor_.dispatch(BOOST_ASIO_MOVE_CAST(F)(f), a);
    }
  }

  template <typename F, typename A>
  void post(BOOST_ASIO_MOVE_ARG(F) f, const A& a) const
  {
    executor_.post(BOOST_ASIO_MOVE_CAST(F)(f), a);
  }

  template <typename F, typename A>
  void defer(BOOST_ASIO_MOVE_ARG(F) f, const A& a) const
  {
    executor_.defer(BOOST_ASIO_MOVE_CAST(F)(f), a);
  }

  friend bool operator==(const io_object_executor& a,
      const io_object_executor& b) BOOST_ASIO_NOEXCEPT
  {
    return a.executor_ == b.executor_
      && a.has_native_impl_ == b.has_native_impl_;
  }

  friend bool operator!=(const io_object_executor& a,
      const io_object_executor& b) BOOST_ASIO_NOEXCEPT
  {
    return a.executor_ != b.executor_
      || a.has_native_impl_ != b.has_native_impl_;
  }

private:
  Executor executor_;
  const bool has_native_impl_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IO_OBJECT_EXECUTOR_HPP

/* io_object_executor.hpp
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
*/