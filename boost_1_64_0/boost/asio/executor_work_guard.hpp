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
AxwehHXO6/TpLNUjrj5T4sQlGNmRj4VXmuVO4LMcKR+D7ef+BJ75Pl7IAERgHUHNld+iW0bESiV2Jhq1G/HaHwp71XSNX6/hIdfgHar1MvUZ9AmrrhL9SccydvU38U3ZC/74Ax+xCynpYPLN0SE1wHhQfNorvQDn3A00MfCUMjZ2yB5Y9vH46Kp+bJyL5DzENbKCFexh5DE+nGgEzXvF/xgPvQOakBqqxlUVT7vExn2CESvus6So29Jtp+nteqtTiCY+JVa5KJLFIxY5XcWaLdzQkI5EzZxEyNsMZwdwGl+gfrhEoZBtZgWccNxHpwcrB5nbGeHWHihcGw84kIpLJGoL2LpqFfGL+my7fuSzU6T0WbGKp4k8CYs6blcRDzwvAcSe0XssRsPznvzYid8aXdS0ByMhbqgAbvZEwA23g1+SlQxpZvjJxW2l8f7lrndHqpoKLaD5GJQTo0Rt47Z0m4bknv+qpghjBhJ+sZ2BVdZelCtGjvbMC/RZB2Toi60tpW2+d41jcLhOMwg2Yw2PTbukNroxS3zaU4Qvy9cpsChRGJsIqiwot+ejPA==
*/