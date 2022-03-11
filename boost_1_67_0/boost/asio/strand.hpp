//
// strand.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_STRAND_HPP
#define BOOST_ASIO_STRAND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/strand_executor_service.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Provides serialised function invocation for any executor type.
template <typename Executor>
class strand
{
public:
  /// The type of the underlying executor.
  typedef Executor inner_executor_type;

  /// Default constructor.
  /**
   * This constructor is only valid if the underlying executor type is default
   * constructible.
   */
  strand()
    : executor_(),
      impl_(use_service<detail::strand_executor_service>(
            executor_.context()).create_implementation())
  {
  }

  /// Construct a strand for the specified executor.
  explicit strand(const Executor& e)
    : executor_(e),
      impl_(use_service<detail::strand_executor_service>(
            executor_.context()).create_implementation())
  {
  }

  /// Copy constructor.
  strand(const strand& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      impl_(other.impl_)
  {
  }

  /// Converting constructor.
  /**
   * This constructor is only valid if the @c OtherExecutor type is convertible
   * to @c Executor.
   */
  template <class OtherExecutor>
  strand(
      const strand<OtherExecutor>& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      impl_(other.impl_)
  {
  }

  /// Assignment operator.
  strand& operator=(const strand& other) BOOST_ASIO_NOEXCEPT
  {
    executor_ = other.executor_;
    impl_ = other.impl_;
    return *this;
  }

  /// Converting assignment operator.
  /**
   * This assignment operator is only valid if the @c OtherExecutor type is
   * convertible to @c Executor.
   */
  template <class OtherExecutor>
  strand& operator=(
      const strand<OtherExecutor>& other) BOOST_ASIO_NOEXCEPT
  {
    executor_ = other.executor_;
    impl_ = other.impl_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  strand(strand&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      impl_(BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_))
  {
  }

  /// Converting move constructor.
  /**
   * This constructor is only valid if the @c OtherExecutor type is convertible
   * to @c Executor.
   */
  template <class OtherExecutor>
  strand(strand<OtherExecutor>&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(OtherExecutor)(other.executor_)),
      impl_(BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_))
  {
  }

  /// Move assignment operator.
  strand& operator=(strand&& other) BOOST_ASIO_NOEXCEPT
  {
    executor_ = BOOST_ASIO_MOVE_CAST(Executor)(other.executor_);
    impl_ = BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_);
    return *this;
  }

  /// Converting move assignment operator.
  /**
   * This assignment operator is only valid if the @c OtherExecutor type is
   * convertible to @c Executor.
   */
  template <class OtherExecutor>
  strand& operator=(strand<OtherExecutor>&& other) BOOST_ASIO_NOEXCEPT
  {
    executor_ = BOOST_ASIO_MOVE_CAST(OtherExecutor)(other.executor_);
    impl_ = BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  ~strand()
  {
  }

  /// Obtain the underlying executor.
  inner_executor_type get_inner_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  /// Obtain the underlying execution context.
  execution_context& context() const BOOST_ASIO_NOEXCEPT
  {
    return executor_.context();
  }

  /// Inform the strand that it has some outstanding work to do.
  /**
   * The strand delegates this call to its underlying executor.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
    executor_.on_work_started();
  }

  /// Inform the strand that some work is no longer outstanding.
  /**
   * The strand delegates this call to its underlying executor.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
    executor_.on_work_finished();
  }

  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the strand to execute the given function
   * object on its underlying executor. The function object will be executed
   * inside this function if the strand is not otherwise busy and if the
   * underlying executor's @c dispatch() function is also able to execute the
   * function before returning.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
  {
    detail::strand_executor_service::dispatch(impl_,
        executor_, BOOST_ASIO_MOVE_CAST(Function)(f), a);
  }

  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled by the underlying executor's defer function.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
  {
    detail::strand_executor_service::post(impl_,
        executor_, BOOST_ASIO_MOVE_CAST(Function)(f), a);
  }

  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled by the underlying executor's defer function.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
  {
    detail::strand_executor_service::defer(impl_,
        executor_, BOOST_ASIO_MOVE_CAST(Function)(f), a);
  }

  /// Determine whether the strand is running in the current thread.
  /**
   * @return @c true if the current thread is executing a function that was
   * submitted to the strand using post(), dispatch() or defer(). Otherwise
   * returns @c false.
   */
  bool running_in_this_thread() const BOOST_ASIO_NOEXCEPT
  {
    return detail::strand_executor_service::running_in_this_thread(impl_);
  }

  /// Compare two strands for equality.
  /**
   * Two strands are equal if they refer to the same ordered, non-concurrent
   * state.
   */
  friend bool operator==(const strand& a, const strand& b) BOOST_ASIO_NOEXCEPT
  {
    return a.impl_ == b.impl_;
  }

  /// Compare two strands for inequality.
  /**
   * Two strands are equal if they refer to the same ordered, non-concurrent
   * state.
   */
  friend bool operator!=(const strand& a, const strand& b) BOOST_ASIO_NOEXCEPT
  {
    return a.impl_ != b.impl_;
  }

#if defined(GENERATING_DOCUMENTATION)
private:
#endif // defined(GENERATING_DOCUMENTATION)
  Executor executor_;
  typedef detail::strand_executor_service::implementation_type
    implementation_type;
  implementation_type impl_;
};

/** @defgroup make_strand boost::asio::make_strand
 *
 * @brief The boost::asio::make_strand function creates a @ref strand object for
 * an executor or execution context.
 */
/*@{*/

/// Create a @ref strand object for an executor.
template <typename Executor>
inline strand<Executor> make_strand(const Executor& ex,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return strand<Executor>(ex);
}

/// Create a @ref strand object for an execution context.
template <typename ExecutionContext>
inline strand<typename ExecutionContext::executor_type>
make_strand(ExecutionContext& ctx,
    typename enable_if<
      is_convertible<ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return strand<typename ExecutionContext::executor_type>(ctx.get_executor());
}

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

// If both io_context.hpp and strand.hpp have been included, automatically
// include the header file needed for the io_context::strand class.
#if !defined(BOOST_ASIO_NO_EXTENSIONS)
# if defined(BOOST_ASIO_IO_CONTEXT_HPP)
#  include <boost/asio/io_context_strand.hpp>
# endif // defined(BOOST_ASIO_IO_CONTEXT_HPP)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

#endif // BOOST_ASIO_STRAND_HPP

/* strand.hpp
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
*/