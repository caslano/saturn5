//
// basic_deadline_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/detail/deadline_timer_service.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
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
    typename Executor = any_io_executor>
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
    : impl_(0, ex)
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
   * @param ex The I/O executor that the timer will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the timer.
   *
   * @param expiry_time The expiry time to be used for the timer, expressed
   * as an absolute time.
   */
  basic_deadline_timer(const executor_type& ex, const time_type& expiry_time)
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
  basic_deadline_timer(ExecutionContext& context, const time_type& expiry_time,
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
  basic_deadline_timer(const executor_type& ex,
      const duration_type& expiry_time)
    : impl_(0, ex)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
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
          self_->impl_.get_implementation(),
          handler2.value, self_->impl_.get_executor());
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
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
*/