//
// basic_waitable_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/chrono_time_traits.hpp>
#include <boost/asio/detail/deadline_timer_service.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/executor.hpp>
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
    typename Executor = executor>
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
   * timer. It always returns immediately.
   *
   * For each call to async_wait(), the supplied handler will be called exactly
   * once. The handler will be called when:
   *
   * @li The timer has expired.
   *
   * @li The timer was cancelled, in which case the handler is passed the error
   * code boost::asio::error::operation_aborted.
   *
   * @param handler The handler to be called when the timer expires. Copies
   * will be made of the handler as required. The function signature of the
   * handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        WaitHandler BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WaitHandler,
      void (boost::system::error_code))
  async_wait(
      BOOST_ASIO_MOVE_ARG(WaitHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WaitHandler, void (boost::system::error_code)>(
        initiate_async_wait(this), handler);
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
          self_->impl_.get_implementation(), handler2.value,
          self_->impl_.get_implementation_executor());
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