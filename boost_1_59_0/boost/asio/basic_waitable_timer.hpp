//
// basic_waitable_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_WAITABLE_TIMER_HPP
#define BOOST_ASIO_BASIC_WAITABLE_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/detail/chrono_time_traits.hpp>
#include <boost/asio/detail/deadline_timer_service.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/wait_traits.hpp>

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_WAITABLE_TIMER_FWD_DECL)
#define BOOST_ASIO_BASIC_WAITABLE_TIMER_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Clock,
    typename WaitTraits = boost::asio::wait_traits<Clock>,
    typename Executor = any_io_executor>
class basic_waitable_timer;

#endif // !defined(BOOST_ASIO_BASIC_WAITABLE_TIMER_FWD_DECL)

/// Provides waitable timer functionality.
/**
 * The basic_waitable_timer class template provides the ability to perform a
 * blocking or asynchronous wait for a timer to expire.
 *
 * A waitable timer is always in one of two states: "expired" or "not expired".
 * If the wait() or async_wait() function is called on an expired timer, the
 * wait operation will complete immediately.
 *
 * Most applications will use one of the boost::asio::steady_timer,
 * boost::asio::system_timer or boost::asio::high_resolution_timer typedefs.
 *
 * @note This waitable timer functionality is for use with the C++11 standard
 * library's @c &lt;chrono&gt; facility, or with the Boost.Chrono library.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Examples
 * Performing a blocking wait (C++11):
 * @code
 * // Construct a timer without setting an expiry time.
 * boost::asio::steady_timer timer(my_context);
 *
 * // Set an expiry time relative to now.
 * timer.expires_after(std::chrono::seconds(5));
 *
 * // Wait for the timer to expire.
 * timer.wait();
 * @endcode
 *
 * @par 
 * Performing an asynchronous wait (C++11):
 * @code
 * void handler(const boost::system::error_code& error)
 * {
 *   if (!error)
 *   {
 *     // Timer expired.
 *   }
 * }
 *
 * ...
 *
 * // Construct a timer with an absolute expiry time.
 * boost::asio::steady_timer timer(my_context,
 *     std::chrono::steady_clock::now() + std::chrono::seconds(60));
 *
 * // Start an asynchronous wait.
 * timer.async_wait(handler);
 * @endcode
 *
 * @par Changing an active waitable timer's expiry time
 *
 * Changing the expiry time of a timer while there are pending asynchronous
 * waits causes those wait operations to be cancelled. To ensure that the action
 * associated with the timer is performed only once, use something like this:
 * used:
 *
 * @code
 * void on_some_event()
 * {
 *   if (my_timer.expires_after(seconds(5)) > 0)
 *   {
 *     // We managed to cancel the timer. Start new asynchronous wait.
 *     my_timer.async_wait(on_timeout);
 *   }
 *   else
 *   {
 *     // Too late, timer has already expired!
 *   }
 * }
 *
 * void on_timeout(const boost::system::error_code& e)
 * {
 *   if (e != boost::asio::error::operation_aborted)
 *   {
 *     // Timer was not cancelled, take necessary action.
 *   }
 * }
 * @endcode
 *
 * @li The boost::asio::basic_waitable_timer::expires_after() function
 * cancels any pending asynchronous waits, and returns the number of
 * asynchronous waits that were cancelled. If it returns 0 then you were too
 * late and the wait handler has already been executed, or will soon be
 * executed. If it returns 1 then the wait handler was successfully cancelled.
 *
 * @li If a wait handler is cancelled, the boost::system::error_code passed to
 * it contains the value boost::asio::error::operation_aborted.
 */
template <typename Clock, typename WaitTraits, typename Executor>
class basic_waitable_timer
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the timer type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The timer type when rebound to the specified executor.
    typedef basic_waitable_timer<Clock, WaitTraits, Executor1> other;
  };

  /// The clock type.
  typedef Clock clock_type;

  /// The duration type of the clock.
  typedef typename clock_type::duration duration;

  /// The time point type of the clock.
  typedef typename clock_type::time_point time_point;

  /// The wait traits type.
  typedef WaitTraits traits_type;

  /// Constructor.
  /**
   * This constructor creates a timer without setting an expiry time. The
   * expires_at() or expires_after() functions must be called to set an expiry
   * time before the timer can be waited on.
   *
   * @param ex The I/O executor that the timer will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the timer.
   */
  explicit basic_waitable_timer(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Constructor.
  /**
   * This constructor creates a timer without setting an expiry time. The
   * expires_at() or expires_after() functions must be called to set an expiry
   * time before the timer can be waited on.
   *
   * @param context An execution context which provides the I/O executor that
   * the timer will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the timer.
   */
  template <typename ExecutionContext>
  explicit basic_waitable_timer(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
  }

  /// Constructor to set a particular expiry time as an absolute time.
  /**
   * This constructor creates a timer and sets the expiry time.
   *
   * @param ex The I/O executor object that the timer will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the timer.
   *
   * @param expiry_time The expiry time to be used for the timer, expressed
   * as an absolute time.
   */
  basic_waitable_timer(const executor_type& ex, const time_point& expiry_time)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().expires_at(impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_at");
  }

  /// Constructor to set a particular expiry time as an absolute time.
  /**
   * This constructor creates a timer and sets the expiry time.
   *
   * @param context An execution context which provides the I/O executor that
   * the timer will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the timer.
   *
   * @param expiry_time The expiry time to be used for the timer, expressed
   * as an absolute time.
   */
  template <typename ExecutionContext>
  explicit basic_waitable_timer(ExecutionContext& context,
      const time_point& expiry_time,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().expires_at(impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_at");
  }

  /// Constructor to set a particular expiry time relative to now.
  /**
   * This constructor creates a timer and sets the expiry time.
   *
   * @param ex The I/O executor that the timer will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the timer.
   *
   * @param expiry_time The expiry time to be used for the timer, relative to
   * now.
   */
  basic_waitable_timer(const executor_type& ex, const duration& expiry_time)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().expires_after(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_after");
  }

  /// Constructor to set a particular expiry time relative to now.
  /**
   * This constructor creates a timer and sets the expiry time.
   *
   * @param context An execution context which provides the I/O executor that
   * the timer will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the timer.
   *
   * @param expiry_time The expiry time to be used for the timer, relative to
   * now.
   */
  template <typename ExecutionContext>
  explicit basic_waitable_timer(ExecutionContext& context,
      const duration& expiry_time,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().expires_after(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_after");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_waitable_timer from another.
  /**
   * This constructor moves a timer from one object to another.
   *
   * @param other The other basic_waitable_timer object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_waitable_timer(const executor_type&)
   * constructor.
   */
  basic_waitable_timer(basic_waitable_timer&& other)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_waitable_timer from another.
  /**
   * This assignment operator moves a timer from one object to another. Cancels
   * any outstanding asynchronous operations associated with the target object.
   *
   * @param other The other basic_waitable_timer object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_waitable_timer(const executor_type&)
   * constructor.
   */
  basic_waitable_timer& operator=(basic_waitable_timer&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }

  // All timers have access to each other's implementations.
  template <typename Clock1, typename WaitTraits1, typename Executor1>
  friend class basic_waitable_timer;

  /// Move-construct a basic_waitable_timer from another.
  /**
   * This constructor moves a timer from one object to another.
   *
   * @param other The other basic_waitable_timer object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_waitable_timer(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  basic_waitable_timer(
      basic_waitable_timer<Clock, WaitTraits, Executor1>&& other,
      typename constraint<
          is_convertible<Executor1, Executor>::value
      >::type = 0)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_waitable_timer from another.
  /**
   * This assignment operator moves a timer from one object to another. Cancels
   * any outstanding asynchronous operations associated with the target object.
   *
   * @param other The other basic_waitable_timer object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_waitable_timer(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  typename constraint<
    is_convertible<Executor1, Executor>::value,
    basic_waitable_timer&
  >::type operator=(basic_waitable_timer<Clock, WaitTraits, Executor1>&& other)
  {
    basic_waitable_timer tmp(std::move(other));
    impl_ = std::move(tmp.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the timer.
  /**
   * This function destroys the timer, cancelling any outstanding asynchronous
   * wait operations associated with the timer as if by calling @c cancel.
   */
  ~basic_waitable_timer()
  {
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Cancel any asynchronous operations that are waiting on the timer.
  /**
   * This function forces the completion of any pending asynchronous wait
   * operations against the timer. The handler for each cancelled operation will
   * be invoked with the boost::asio::error::operation_aborted error code.
   *
   * Cancelling the timer does not change the expiry time.
   *
   * @return The number of asynchronous operations that were cancelled.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note If the timer has already expired when cancel() is called, then the
   * handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t cancel()
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().cancel(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
    return s;
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use non-error_code overload.) Cancel any asynchronous
  /// operations that are waiting on the timer.
  /**
   * This function forces the completion of any pending asynchronous wait
   * operations against the timer. The handler for each cancelled operation will
   * be invoked with the boost::asio::error::operation_aborted error code.
   *
   * Cancelling the timer does not change the expiry time.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return The number of asynchronous operations that were cancelled.
   *
   * @note If the timer has already expired when cancel() is called, then the
   * handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t cancel(boost::system::error_code& ec)
  {
    return impl_.get_service().cancel(impl_.get_implementation(), ec);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Cancels one asynchronous operation that is waiting on the timer.
  /**
   * This function forces the completion of one pending asynchronous wait
   * operation against the timer. Handlers are cancelled in FIFO order. The
   * handler for the cancelled operation will be invoked with the
   * boost::asio::error::operation_aborted error code.
   *
   * Cancelling the timer does not change the expiry time.
   *
   * @return The number of asynchronous operations that were cancelled. That is,
   * either 0 or 1.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note If the timer has already expired when cancel_one() is called, then
   * the handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t cancel_one()
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().cancel_one(
        impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel_one");
    return s;
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use non-error_code overload.) Cancels one asynchronous
  /// operation that is waiting on the timer.
  /**
   * This function forces the completion of one pending asynchronous wait
   * operation against the timer. Handlers are cancelled in FIFO order. The
   * handler for the cancelled operation will be invoked with the
   * boost::asio::error::operation_aborted error code.
   *
   * Cancelling the timer does not change the expiry time.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return The number of asynchronous operations that were cancelled. That is,
   * either 0 or 1.
   *
   * @note If the timer has already expired when cancel_one() is called, then
   * the handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t cancel_one(boost::system::error_code& ec)
  {
    return impl_.get_service().cancel_one(impl_.get_implementation(), ec);
  }

  /// (Deprecated: Use expiry().) Get the timer's expiry time as an absolute
  /// time.
  /**
   * This function may be used to obtain the timer's current expiry time.
   * Whether the timer has expired or not does not affect this value.
   */
  time_point expires_at() const
  {
    return impl_.get_service().expires_at(impl_.get_implementation());
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Get the timer's expiry time as an absolute time.
  /**
   * This function may be used to obtain the timer's current expiry time.
   * Whether the timer has expired or not does not affect this value.
   */
  time_point expiry() const
  {
    return impl_.get_service().expiry(impl_.get_implementation());
  }

  /// Set the timer's expiry time as an absolute time.
  /**
   * This function sets the expiry time. Any pending asynchronous wait
   * operations will be cancelled. The handler for each cancelled operation will
   * be invoked with the boost::asio::error::operation_aborted error code.
   *
   * @param expiry_time The expiry time to be used for the timer.
   *
   * @return The number of asynchronous operations that were cancelled.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note If the timer has already expired when expires_at() is called, then
   * the handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t expires_at(const time_point& expiry_time)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().expires_at(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_at");
    return s;
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use non-error_code overload.) Set the timer's expiry time as
  /// an absolute time.
  /**
   * This function sets the expiry time. Any pending asynchronous wait
   * operations will be cancelled. The handler for each cancelled operation will
   * be invoked with the boost::asio::error::operation_aborted error code.
   *
   * @param expiry_time The expiry time to be used for the timer.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return The number of asynchronous operations that were cancelled.
   *
   * @note If the timer has already expired when expires_at() is called, then
   * the handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t expires_at(const time_point& expiry_time,
      boost::system::error_code& ec)
  {
    return impl_.get_service().expires_at(
        impl_.get_implementation(), expiry_time, ec);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Set the timer's expiry time relative to now.
  /**
   * This function sets the expiry time. Any pending asynchronous wait
   * operations will be cancelled. The handler for each cancelled operation will
   * be invoked with the boost::asio::error::operation_aborted error code.
   *
   * @param expiry_time The expiry time to be used for the timer.
   *
   * @return The number of asynchronous operations that were cancelled.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note If the timer has already expired when expires_after() is called,
   * then the handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t expires_after(const duration& expiry_time)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().expires_after(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_after");
    return s;
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use expiry().) Get the timer's expiry time relative to now.
  /**
   * This function may be used to obtain the timer's current expiry time.
   * Whether the timer has expired or not does not affect this value.
   */
  duration expires_from_now() const
  {
    return impl_.get_service().expires_from_now(impl_.get_implementation());
  }

  /// (Deprecated: Use expires_after().) Set the timer's expiry time relative
  /// to now.
  /**
   * This function sets the expiry time. Any pending asynchronous wait
   * operations will be cancelled. The handler for each cancelled operation will
   * be invoked with the boost::asio::error::operation_aborted error code.
   *
   * @param expiry_time The expiry time to be used for the timer.
   *
   * @return The number of asynchronous operations that were cancelled.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note If the timer has already expired when expires_from_now() is called,
   * then the handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t expires_from_now(const duration& expiry_time)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().expires_from_now(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_from_now");
    return s;
  }

  /// (Deprecated: Use expires_after().) Set the timer's expiry time relative
  /// to now.
  /**
   * This function sets the expiry time. Any pending asynchronous wait
   * operations will be cancelled. The handler for each cancelled operation will
   * be invoked with the boost::asio::error::operation_aborted error code.
   *
   * @param expiry_time The expiry time to be used for the timer.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return The number of asynchronous operations that were cancelled.
   *
   * @note If the timer has already expired when expires_from_now() is called,
   * then the handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  std::size_t expires_from_now(const duration& expiry_time,
      boost::system::error_code& ec)
  {
    return impl_.get_service().expires_from_now(
        impl_.get_implementation(), expiry_time, ec);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Perform a blocking wait on the timer.
  /**
   * This function is used to wait for the timer to expire. This function
   * blocks and does not return until the timer has expired.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void wait()
  {
    boost::system::error_code ec;
    impl_.get_service().wait(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "wait");
  }

  /// Perform a blocking wait on the timer.
  /**
   * This function is used to wait for the timer to expire. This function
   * blocks and does not return until the timer has expired.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  void wait(boost::system::error_code& ec)
  {
    impl_.get_service().wait(impl_.get_implementation(), ec);
  }

  /// Start an asynchronous wait on the timer.
  /**
   * This function may be used to initiate an asynchronous wait against the
   * timer. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
   *
   * For each call to async_wait(), the completion handler will be called
   * exactly once. The completion handler will be called when:
   *
   * @li The timer has expired.
   *
   * @li The timer was cancelled, in which case the handler is passed the error
   * code boost::asio::error::operation_aborted.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the timer expires. Potential
   * completion tokens include @ref use_future, @ref use_awaitable, @ref
   * yield_context, or a function object with the correct completion signature.
   * The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code) @endcode
   *
   * @par Per-Operation Cancellation
   * This asynchronous operation supports cancellation for the following
   * boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        WaitToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WaitToken,
      void (boost::system::error_code))
  async_wait(
      BOOST_ASIO_MOVE_ARG(WaitToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WaitToken, void (boost::system::error_code)>(
        initiate_async_wait(this), token);
  }

private:
  // Disallow copying and assignment.
  basic_waitable_timer(const basic_waitable_timer&) BOOST_ASIO_DELETED;
  basic_waitable_timer& operator=(
      const basic_waitable_timer&) BOOST_ASIO_DELETED;

  class initiate_async_wait
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_wait(basic_waitable_timer* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WaitHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(WaitHandler) handler) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WaitHandler.
      BOOST_ASIO_WAIT_HANDLER_CHECK(WaitHandler, handler) type_check;

      detail::non_const_lvalue<WaitHandler> handler2(handler);
      self_->impl_.get_service().async_wait(
          self_->impl_.get_implementation(),
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_waitable_timer* self_;
  };

  detail::io_object_impl<
    detail::deadline_timer_service<
      detail::chrono_time_traits<Clock, WaitTraits> >,
    executor_type > impl_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_WAITABLE_TIMER_HPP

/* basic_waitable_timer.hpp
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
*/