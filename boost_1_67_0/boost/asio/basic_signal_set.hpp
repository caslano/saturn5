//
// basic_signal_set.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_SIGNAL_SET_HPP
#define BOOST_ASIO_BASIC_SIGNAL_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/signal_set_service.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/executor.hpp>

namespace boost {
namespace asio {

/// Provides signal functionality.
/**
 * The basic_signal_set class provides the ability to perform an asynchronous
 * wait for one or more signals to occur.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Example
 * Performing an asynchronous wait:
 * @code
 * void handler(
 *     const boost::system::error_code& error,
 *     int signal_number)
 * {
 *   if (!error)
 *   {
 *     // A signal occurred.
 *   }
 * }
 *
 * ...
 *
 * // Construct a signal set registered for process termination.
 * boost::asio::signal_set signals(my_context, SIGINT, SIGTERM);
 *
 * // Start an asynchronous wait for one of the signals to occur.
 * signals.async_wait(handler);
 * @endcode
 *
 * @par Queueing of signal notifications
 *
 * If a signal is registered with a signal_set, and the signal occurs when
 * there are no waiting handlers, then the signal notification is queued. The
 * next async_wait operation on that signal_set will dequeue the notification.
 * If multiple notifications are queued, subsequent async_wait operations
 * dequeue them one at a time. Signal notifications are dequeued in order of
 * ascending signal number.
 *
 * If a signal number is removed from a signal_set (using the @c remove or @c
 * erase member functions) then any queued notifications for that signal are
 * discarded.
 *
 * @par Multiple registration of signals
 *
 * The same signal number may be registered with different signal_set objects.
 * When the signal occurs, one handler is called for each signal_set object.
 *
 * Note that multiple registration only works for signals that are registered
 * using Asio. The application must not also register a signal handler using
 * functions such as @c signal() or @c sigaction().
 *
 * @par Signal masking on POSIX platforms
 *
 * POSIX allows signals to be blocked using functions such as @c sigprocmask()
 * and @c pthread_sigmask(). For signals to be delivered, programs must ensure
 * that any signals registered using signal_set objects are unblocked in at
 * least one thread.
 */
template <typename Executor = executor>
class basic_signal_set
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the signal set type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The signal set type when rebound to the specified executor.
    typedef basic_signal_set<Executor1> other;
  };

  /// Construct a signal set without adding any signals.
  /**
   * This constructor creates a signal set without registering for any signals.
   *
   * @param ex The I/O executor that the signal set will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * signal set.
   */
  explicit basic_signal_set(const executor_type& ex)
    : impl_(ex)
  {
  }

  /// Construct a signal set without adding any signals.
  /**
   * This constructor creates a signal set without registering for any signals.
   *
   * @param context An execution context which provides the I/O executor that
   * the signal set will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the signal set.
   */
  template <typename ExecutionContext>
  explicit basic_signal_set(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
  }

  /// Construct a signal set and add one signal.
  /**
   * This constructor creates a signal set and registers for one signal.
   *
   * @param ex The I/O executor that the signal set will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * signal set.
   *
   * @param signal_number_1 The signal number to be added.
   *
   * @note This constructor is equivalent to performing:
   * @code boost::asio::signal_set signals(ex);
   * signals.add(signal_number_1); @endcode
   */
  basic_signal_set(const executor_type& ex, int signal_number_1)
    : impl_(ex)
  {
    boost::system::error_code ec;
    impl_.get_service().add(impl_.get_implementation(), signal_number_1, ec);
    boost::asio::detail::throw_error(ec, "add");
  }

  /// Construct a signal set and add one signal.
  /**
   * This constructor creates a signal set and registers for one signal.
   *
   * @param context An execution context which provides the I/O executor that
   * the signal set will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the signal set.
   *
   * @param signal_number_1 The signal number to be added.
   *
   * @note This constructor is equivalent to performing:
   * @code boost::asio::signal_set signals(context);
   * signals.add(signal_number_1); @endcode
   */
  template <typename ExecutionContext>
  basic_signal_set(ExecutionContext& context, int signal_number_1,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
    boost::system::error_code ec;
    impl_.get_service().add(impl_.get_implementation(), signal_number_1, ec);
    boost::asio::detail::throw_error(ec, "add");
  }

  /// Construct a signal set and add two signals.
  /**
   * This constructor creates a signal set and registers for two signals.
   *
   * @param ex The I/O executor that the signal set will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * signal set.
   *
   * @param signal_number_1 The first signal number to be added.
   *
   * @param signal_number_2 The second signal number to be added.
   *
   * @note This constructor is equivalent to performing:
   * @code boost::asio::signal_set signals(ex);
   * signals.add(signal_number_1);
   * signals.add(signal_number_2); @endcode
   */
  basic_signal_set(const executor_type& ex, int signal_number_1,
      int signal_number_2)
    : impl_(ex)
  {
    boost::system::error_code ec;
    impl_.get_service().add(impl_.get_implementation(), signal_number_1, ec);
    boost::asio::detail::throw_error(ec, "add");
    impl_.get_service().add(impl_.get_implementation(), signal_number_2, ec);
    boost::asio::detail::throw_error(ec, "add");
  }

  /// Construct a signal set and add two signals.
  /**
   * This constructor creates a signal set and registers for two signals.
   *
   * @param context An execution context which provides the I/O executor that
   * the signal set will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the signal set.
   *
   * @param signal_number_1 The first signal number to be added.
   *
   * @param signal_number_2 The second signal number to be added.
   *
   * @note This constructor is equivalent to performing:
   * @code boost::asio::signal_set signals(context);
   * signals.add(signal_number_1);
   * signals.add(signal_number_2); @endcode
   */
  template <typename ExecutionContext>
  basic_signal_set(ExecutionContext& context, int signal_number_1,
      int signal_number_2,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
    boost::system::error_code ec;
    impl_.get_service().add(impl_.get_implementation(), signal_number_1, ec);
    boost::asio::detail::throw_error(ec, "add");
    impl_.get_service().add(impl_.get_implementation(), signal_number_2, ec);
    boost::asio::detail::throw_error(ec, "add");
  }

  /// Construct a signal set and add three signals.
  /**
   * This constructor creates a signal set and registers for three signals.
   *
   * @param ex The I/O executor that the signal set will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * signal set.
   *
   * @param signal_number_1 The first signal number to be added.
   *
   * @param signal_number_2 The second signal number to be added.
   *
   * @param signal_number_3 The third signal number to be added.
   *
   * @note This constructor is equivalent to performing:
   * @code boost::asio::signal_set signals(ex);
   * signals.add(signal_number_1);
   * signals.add(signal_number_2);
   * signals.add(signal_number_3); @endcode
   */
  basic_signal_set(const executor_type& ex, int signal_number_1,
      int signal_number_2, int signal_number_3)
    : impl_(ex)
  {
    boost::system::error_code ec;
    impl_.get_service().add(impl_.get_implementation(), signal_number_1, ec);
    boost::asio::detail::throw_error(ec, "add");
    impl_.get_service().add(impl_.get_implementation(), signal_number_2, ec);
    boost::asio::detail::throw_error(ec, "add");
    impl_.get_service().add(impl_.get_implementation(), signal_number_3, ec);
    boost::asio::detail::throw_error(ec, "add");
  }

  /// Construct a signal set and add three signals.
  /**
   * This constructor creates a signal set and registers for three signals.
   *
   * @param context An execution context which provides the I/O executor that
   * the signal set will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the signal set.
   *
   * @param signal_number_1 The first signal number to be added.
   *
   * @param signal_number_2 The second signal number to be added.
   *
   * @param signal_number_3 The third signal number to be added.
   *
   * @note This constructor is equivalent to performing:
   * @code boost::asio::signal_set signals(context);
   * signals.add(signal_number_1);
   * signals.add(signal_number_2);
   * signals.add(signal_number_3); @endcode
   */
  template <typename ExecutionContext>
  basic_signal_set(ExecutionContext& context, int signal_number_1,
      int signal_number_2, int signal_number_3,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
  {
    boost::system::error_code ec;
    impl_.get_service().add(impl_.get_implementation(), signal_number_1, ec);
    boost::asio::detail::throw_error(ec, "add");
    impl_.get_service().add(impl_.get_implementation(), signal_number_2, ec);
    boost::asio::detail::throw_error(ec, "add");
    impl_.get_service().add(impl_.get_implementation(), signal_number_3, ec);
    boost::asio::detail::throw_error(ec, "add");
  }

  /// Destroys the signal set.
  /**
   * This function destroys the signal set, cancelling any outstanding
   * asynchronous wait operations associated with the signal set as if by
   * calling @c cancel.
   */
  ~basic_signal_set()
  {
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Add a signal to a signal_set.
  /**
   * This function adds the specified signal to the set. It has no effect if the
   * signal is already in the set.
   *
   * @param signal_number The signal to be added to the set.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void add(int signal_number)
  {
    boost::system::error_code ec;
    impl_.get_service().add(impl_.get_implementation(), signal_number, ec);
    boost::asio::detail::throw_error(ec, "add");
  }

  /// Add a signal to a signal_set.
  /**
   * This function adds the specified signal to the set. It has no effect if the
   * signal is already in the set.
   *
   * @param signal_number The signal to be added to the set.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID add(int signal_number,
      boost::system::error_code& ec)
  {
    impl_.get_service().add(impl_.get_implementation(), signal_number, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Remove a signal from a signal_set.
  /**
   * This function removes the specified signal from the set. It has no effect
   * if the signal is not in the set.
   *
   * @param signal_number The signal to be removed from the set.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Removes any notifications that have been queued for the specified
   * signal number.
   */
  void remove(int signal_number)
  {
    boost::system::error_code ec;
    impl_.get_service().remove(impl_.get_implementation(), signal_number, ec);
    boost::asio::detail::throw_error(ec, "remove");
  }

  /// Remove a signal from a signal_set.
  /**
   * This function removes the specified signal from the set. It has no effect
   * if the signal is not in the set.
   *
   * @param signal_number The signal to be removed from the set.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Removes any notifications that have been queued for the specified
   * signal number.
   */
  BOOST_ASIO_SYNC_OP_VOID remove(int signal_number,
      boost::system::error_code& ec)
  {
    impl_.get_service().remove(impl_.get_implementation(), signal_number, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Remove all signals from a signal_set.
  /**
   * This function removes all signals from the set. It has no effect if the set
   * is already empty.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Removes all queued notifications.
   */
  void clear()
  {
    boost::system::error_code ec;
    impl_.get_service().clear(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "clear");
  }

  /// Remove all signals from a signal_set.
  /**
   * This function removes all signals from the set. It has no effect if the set
   * is already empty.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Removes all queued notifications.
   */
  BOOST_ASIO_SYNC_OP_VOID clear(boost::system::error_code& ec)
  {
    impl_.get_service().clear(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Cancel all operations associated with the signal set.
  /**
   * This function forces the completion of any pending asynchronous wait
   * operations against the signal set. The handler for each cancelled
   * operation will be invoked with the boost::asio::error::operation_aborted
   * error code.
   *
   * Cancellation does not alter the set of registered signals.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note If a registered signal occurred before cancel() is called, then the
   * handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  void cancel()
  {
    boost::system::error_code ec;
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  /// Cancel all operations associated with the signal set.
  /**
   * This function forces the completion of any pending asynchronous wait
   * operations against the signal set. The handler for each cancelled
   * operation will be invoked with the boost::asio::error::operation_aborted
   * error code.
   *
   * Cancellation does not alter the set of registered signals.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note If a registered signal occurred before cancel() is called, then the
   * handlers for asynchronous wait operations will:
   *
   * @li have already been invoked; or
   *
   * @li have been queued for invocation in the near future.
   *
   * These handlers can no longer be cancelled, and therefore are passed an
   * error code that indicates the successful completion of the wait operation.
   */
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Start an asynchronous operation to wait for a signal to be delivered.
  /**
   * This function may be used to initiate an asynchronous wait against the
   * signal set. It always returns immediately.
   *
   * For each call to async_wait(), the supplied handler will be called exactly
   * once. The handler will be called when:
   *
   * @li One of the registered signals in the signal set occurs; or
   *
   * @li The signal set was cancelled, in which case the handler is passed the
   * error code boost::asio::error::operation_aborted.
   *
   * @param handler The handler to be called when the signal occurs. Copies
   * will be made of the handler as required. The function signature of the
   * handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   int signal_number // Indicates which signal occurred.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   */
  template <
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code, int))
      SignalHandler BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(SignalHandler,
      void (boost::system::error_code, int))
  async_wait(
      BOOST_ASIO_MOVE_ARG(SignalHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<SignalHandler, void (boost::system::error_code, int)>(
        initiate_async_wait(this), handler);
  }

private:
  // Disallow copying and assignment.
  basic_signal_set(const basic_signal_set&) BOOST_ASIO_DELETED;
  basic_signal_set& operator=(const basic_signal_set&) BOOST_ASIO_DELETED;

  class initiate_async_wait
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_wait(basic_signal_set* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename SignalHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(SignalHandler) handler) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a SignalHandler.
      BOOST_ASIO_SIGNAL_HANDLER_CHECK(SignalHandler, handler) type_check;

      detail::non_const_lvalue<SignalHandler> handler2(handler);
      self_->impl_.get_service().async_wait(
          self_->impl_.get_implementation(), handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_signal_set* self_;
  };

  detail::io_object_impl<detail::signal_set_service, Executor> impl_;
};

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_BASIC_SIGNAL_SET_HPP

/* basic_signal_set.hpp
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
*/