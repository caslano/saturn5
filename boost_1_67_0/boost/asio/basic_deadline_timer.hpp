//
// basic_deadline_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_DEADLINE_TIMER_HPP
#define BOOST_ASIO_BASIC_DEADLINE_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  || defined(GENERATING_DOCUMENTATION)

#include <cstddef>
#include <boost/asio/detail/deadline_timer_service.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/time_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Provides waitable timer functionality.
/**
 * The basic_deadline_timer class template provides the ability to perform a
 * blocking or asynchronous wait for a timer to expire.
 *
 * A deadline timer is always in one of two states: "expired" or "not expired".
 * If the wait() or async_wait() function is called on an expired timer, the
 * wait operation will complete immediately.
 *
 * Most applications will use the boost::asio::deadline_timer typedef.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Examples
 * Performing a blocking wait:
 * @code
 * // Construct a timer without setting an expiry time.
 * boost::asio::deadline_timer timer(my_context);
 *
 * // Set an expiry time relative to now.
 * timer.expires_from_now(boost::posix_time::seconds(5));
 *
 * // Wait for the timer to expire.
 * timer.wait();
 * @endcode
 *
 * @par 
 * Performing an asynchronous wait:
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
 * boost::asio::deadline_timer timer(my_context,
 *     boost::posix_time::time_from_string("2005-12-07 23:59:59.000"));
 *
 * // Start an asynchronous wait.
 * timer.async_wait(handler);
 * @endcode
 *
 * @par Changing an active deadline_timer's expiry time
 *
 * Changing the expiry time of a timer while there are pending asynchronous
 * waits causes those wait operations to be cancelled. To ensure that the action
 * associated with the timer is performed only once, use something like this:
 * used:
 *
 * @code
 * void on_some_event()
 * {
 *   if (my_timer.expires_from_now(seconds(5)) > 0)
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
 * @li The boost::asio::basic_deadline_timer::expires_from_now() function
 * cancels any pending asynchronous waits, and returns the number of
 * asynchronous waits that were cancelled. If it returns 0 then you were too
 * late and the wait handler has already been executed, or will soon be
 * executed. If it returns 1 then the wait handler was successfully cancelled.
 *
 * @li If a wait handler is cancelled, the boost::system::error_code passed to
 * it contains the value boost::asio::error::operation_aborted.
 */
template <typename Time,
    typename TimeTraits = boost::asio::time_traits<Time>,
    typename Executor = executor>
class basic_deadline_timer
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the timer type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The timer type when rebound to the specified executor.
    typedef basic_deadline_timer<Time, TimeTraits, Executor1> other;
  };

  /// The time traits type.
  typedef TimeTraits traits_type;

  /// The time type.
  typedef typename traits_type::time_type time_type;

  /// The duration type.
  typedef typename traits_type::duration_type duration_type;

  /// Constructor.
  /**
   * This constructor creates a timer without setting an expiry time. The
   * expires_at() or expires_from_now() functions must be called to set an
   * expiry time before the timer can be waited on.
   *
   * @param ex The I/O executor that the timer will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the timer.
   */
  explicit basic_deadline_timer(const executor_type& ex)
    : impl_(ex)
  {
  }

  /// Constructor.
  /**
   * This constructor creates a timer without setting an expiry time. The
   * expires_at() or expires_from_now() functions must be called to set an
   * expiry time before the timer can be waited on.
   *
   * @param context An execution context which provides the I/O executor that
   * the timer will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the timer.
   */
  template <typename ExecutionContext>
  explicit basic_deadline_timer(ExecutionContext& context,
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
   * @param ex The I/O executor that the timer will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the timer.
   *
   * @param expiry_time The expiry time to be used for the timer, expressed
   * as an absolute time.
   */
  basic_deadline_timer(const executor_type& ex, const time_type& expiry_time)
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
  basic_deadline_timer(ExecutionContext& context, const time_type& expiry_time,
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
  basic_deadline_timer(const executor_type& ex,
      const duration_type& expiry_time)
    : impl_(ex)
  {
    boost::system::error_code ec;
    impl_.get_service().expires_from_now(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_from_now");
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
  basic_deadline_timer(ExecutionContext& context,
      const duration_type& expiry_time,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
    boost::system::error_code ec;
    impl_.get_service().expires_from_now(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_from_now");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_deadline_timer from another.
  /**
   * This constructor moves a timer from one object to another.
   *
   * @param other The other basic_deadline_timer object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_deadline_timer(const executor_type&)
   * constructor.
   */
  basic_deadline_timer(basic_deadline_timer&& other)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_deadline_timer from another.
  /**
   * This assignment operator moves a timer from one object to another. Cancels
   * any outstanding asynchronous operations associated with the target object.
   *
   * @param other The other basic_deadline_timer object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_deadline_timer(const executor_type&)
   * constructor.
   */
  basic_deadline_timer& operator=(basic_deadline_timer&& other)
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
  ~basic_deadline_timer()
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

  /// Cancel any asynchronous operations that are waiting on the timer.
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

  /// Cancels one asynchronous operation that is waiting on the timer.
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

  /// Get the timer's expiry time as an absolute time.
  /**
   * This function may be used to obtain the timer's current expiry time.
   * Whether the timer has expired or not does not affect this value.
   */
  time_type expires_at() const
  {
    return impl_.get_service().expires_at(impl_.get_implementation());
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
  std::size_t expires_at(const time_type& expiry_time)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().expires_at(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_at");
    return s;
  }

  /// Set the timer's expiry time as an absolute time.
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
  std::size_t expires_at(const time_type& expiry_time,
      boost::system::error_code& ec)
  {
    return impl_.get_service().expires_at(
        impl_.get_implementation(), expiry_time, ec);
  }

  /// Get the timer's expiry time relative to now.
  /**
   * This function may be used to obtain the timer's current expiry time.
   * Whether the timer has expired or not does not affect this value.
   */
  duration_type expires_from_now() const
  {
    return impl_.get_service().expires_from_now(impl_.get_implementation());
  }

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
  std::size_t expires_from_now(const duration_type& expiry_time)
  {
    boost::system::error_code ec;
    std::size_t s = impl_.get_service().expires_from_now(
        impl_.get_implementation(), expiry_time, ec);
    boost::asio::detail::throw_error(ec, "expires_from_now");
    return s;
  }

  /// Set the timer's expiry time relative to now.
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
  std::size_t expires_from_now(const duration_type& expiry_time,
      boost::system::error_code& ec)
  {
    return impl_.get_service().expires_from_now(
        impl_.get_implementation(), expiry_time, ec);
  }

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
  basic_deadline_timer(const basic_deadline_timer&) BOOST_ASIO_DELETED;
  basic_deadline_timer& operator=(
      const basic_deadline_timer&) BOOST_ASIO_DELETED;

  class initiate_async_wait
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_wait(basic_deadline_timer* self)
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
    basic_deadline_timer* self_;
  };

  detail::io_object_impl<
    detail::deadline_timer_service<TimeTraits>, Executor> impl_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_BASIC_DEADLINE_TIMER_HPP

/* basic_deadline_timer.hpp
+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
*/