//
// executor_work_guard.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP
#define BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// An object of type @c executor_work_guard controls ownership of executor work
/// within a scope.
template <typename Executor>
class executor_work_guard
{
public:
  /// The underlying executor type.
  typedef Executor executor_type;

  /// Constructs a @c executor_work_guard object for the specified executor.
  /**
   * Stores a copy of @c e and calls <tt>on_work_started()</tt> on it.
   */
  explicit executor_work_guard(const executor_type& e) BOOST_ASIO_NOEXCEPT
    : executor_(e),
      owns_(true)
  {
    executor_.on_work_started();
  }

  /// Copy constructor.
  executor_work_guard(const executor_work_guard& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      owns_(other.owns_)
  {
    if (owns_)
      executor_.on_work_started();
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  executor_work_guard(executor_work_guard&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      owns_(other.owns_)
  {
    other.owns_ = false;
  }
#endif //  defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  /**
   * Unless the object has already been reset, or is in a moved-from state,
   * calls <tt>on_work_finished()</tt> on the stored executor.
   */
  ~executor_work_guard()
  {
    if (owns_)
      executor_.on_work_finished();
  }

  /// Obtain the associated executor.
  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  /// Whether the executor_work_guard object owns some outstanding work.
  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return owns_;
  }

  /// Indicate that the work is no longer outstanding.
  /**
   * Unless the object has already been reset, or is in a moved-from state,
   * calls <tt>on_work_finished()</tt> on the stored executor.
   */
  void reset() BOOST_ASIO_NOEXCEPT
  {
    if (owns_)
    {
      executor_.on_work_finished();
      owns_ = false;
    }
  }

private:
  // Disallow assignment.
  executor_work_guard& operator=(const executor_work_guard&);

  executor_type executor_;
  bool owns_;
};

/// Create an @ref executor_work_guard object.
template <typename Executor>
inline executor_work_guard<Executor> make_work_guard(const Executor& ex,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return executor_work_guard<Executor>(ex);
}

/// Create an @ref executor_work_guard object.
template <typename ExecutionContext>
inline executor_work_guard<typename ExecutionContext::executor_type>
make_work_guard(ExecutionContext& ctx,
    typename enable_if<
      is_convertible<ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename ExecutionContext::executor_type>(
      ctx.get_executor());
}

/// Create an @ref executor_work_guard object.
template <typename T>
inline executor_work_guard<typename associated_executor<T>::type>
make_work_guard(const T& t,
    typename enable_if<!is_executor<T>::value &&
      !is_convertible<T&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T>::type>(
      associated_executor<T>::get(t));
}

/// Create an @ref executor_work_guard object.
template <typename T, typename Executor>
inline executor_work_guard<typename associated_executor<T, Executor>::type>
make_work_guard(const T& t, const Executor& ex,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T, Executor>::type>(
      associated_executor<T, Executor>::get(t, ex));
}

/// Create an @ref executor_work_guard object.
template <typename T, typename ExecutionContext>
inline executor_work_guard<typename associated_executor<T,
  typename ExecutionContext::executor_type>::type>
make_work_guard(const T& t, ExecutionContext& ctx,
    typename enable_if<!is_executor<T>::value &&
      !is_convertible<T&, execution_context&>::value &&
      is_convertible<ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T,
    typename ExecutionContext::executor_type>::type>(
      associated_executor<T, typename ExecutionContext::executor_type>::get(
        t, ctx.get_executor()));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP

/* executor_work_guard.hpp
11gmXaWsjVcraxWWFRJSv1+II8MW2oz164fM7BO3IZ6E31IZOBWtpOAtf2rgL4Os2h5ol5kH/UjjdmbnwprcBCfergeBTs0N/OUfOjqkk6rNzqpTEbiuHa8e4impIrGLFGCn8kFkpoRGDsZlblaFQ7nBP49Xfd1HgWG0OjSOifeVgEg29rsoJJE3/BF+LdYTxQZZB16pcVuh6V23wlZy37EMVi7fdzKDzgCPHb3Ca5PTo/vhmNJzrHCEgpR4B7yIbjOy00Tc6MyiW5QxZK3ubc+bY+VjkCVYIVPs0+noVpmbnB6otadZ1FhjO7Kj9GaEsR2lQyNvtmm/iy3IQa92mw/qR/pyn5HBlMz06PNmhsLZhkZ5CmeqLkgb3WFo2AAjP62hfo5FSYBGePn3gfy0e+aIWhwI2JGbCfUnU/0a1m9WGAKR/mSpOXMwZvr6CBhpuoF+n09EJhVDhI8iV35vCa9AybM3tKA7+HtL0aLO3mzD4nYupdArquy3VDWttdmrVq6lKBQ88HiUhZ1AruGkmq5XyFkPO5SZYp2dhnW2+izqv5rC6+w0rLPTtM7O/9ugoW9KHb7H6BrOjg78eXa2aiYbj+7IINcZy5Jh+FgvHP3FiAWY57ayRemBVlv0+/yhKZeMoVY7ltL+Wu+uWXe3qnznwe8uW7fxQXXD3essod3+LsL4f6JvjKiaiShLdO1vR1eKTgQeWmjHhZNr
*/