//
// basic_signal_set.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/signal_set_service.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

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
template <typename Executor = any_io_executor>
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
    : impl_(0, ex)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
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
    : impl_(0, ex)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
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
    : impl_(0, ex)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
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
    : impl_(0, ex)
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
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
   * signal set. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * For each call to async_wait(), the completion handler will be called
   * exactly once. The completion handler will be called when:
   *
   * @li One of the registered signals in the signal set occurs; or
   *
   * @li The signal set was cancelled, in which case the handler is passed the
   * error code boost::asio::error::operation_aborted.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the wait completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   int signal_number // Indicates which signal occurred.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, int) @endcode
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
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code, int))
      SignalToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(SignalToken,
      void (boost::system::error_code, int))
  async_wait(
      BOOST_ASIO_MOVE_ARG(SignalToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<SignalToken, void (boost::system::error_code, int)>(
        initiate_async_wait(this), token);
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
          self_->impl_.get_implementation(),
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_signal_set* self_;
  };

  detail::io_object_impl<detail::signal_set_service, Executor> impl_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_SIGNAL_SET_HPP

/* basic_signal_set.hpp
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
*/