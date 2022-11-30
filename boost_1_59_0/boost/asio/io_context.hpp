//
// io_context.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IO_CONTEXT_HPP
#define BOOST_ASIO_IO_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <stdexcept>
#include <typeinfo>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/concurrency_hint.hpp>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/wrapped_handler.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/execution.hpp>
#include <boost/asio/execution_context.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO)
# include <boost/asio/detail/chrono.hpp>
#endif // defined(BOOST_ASIO_HAS_CHRONO)

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# include <boost/asio/detail/winsock_init.hpp>
#elif defined(__sun) || defined(__QNX__) || defined(__hpux) || defined(_AIX) \
  || defined(__osf__)
# include <boost/asio/detail/signal_init.hpp>
#endif

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else
# include <boost/asio/detail/scheduler.hpp>
#endif

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail {
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef win_iocp_io_context io_context_impl;
  class win_iocp_overlapped_ptr;
#else
  typedef scheduler io_context_impl;
#endif

  struct io_context_bits
  {
    BOOST_ASIO_STATIC_CONSTEXPR(uintptr_t, blocking_never = 1);
    BOOST_ASIO_STATIC_CONSTEXPR(uintptr_t, relationship_continuation = 2);
    BOOST_ASIO_STATIC_CONSTEXPR(uintptr_t, outstanding_work_tracked = 4);
    BOOST_ASIO_STATIC_CONSTEXPR(uintptr_t, runtime_bits = 3);
  };
} // namespace detail

/// Provides core I/O functionality.
/**
 * The io_context class provides the core I/O functionality for users of the
 * asynchronous I/O objects, including:
 *
 * @li boost::asio::ip::tcp::socket
 * @li boost::asio::ip::tcp::acceptor
 * @li boost::asio::ip::udp::socket
 * @li boost::asio::deadline_timer.
 *
 * The io_context class also includes facilities intended for developers of
 * custom asynchronous services.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe, with the specific exceptions of the restart()
 * and notify_fork() functions. Calling restart() while there are unfinished
 * run(), run_one(), run_for(), run_until(), poll() or poll_one() calls results
 * in undefined behaviour. The notify_fork() function should not be called
 * while any io_context function, or any function on an I/O object that is
 * associated with the io_context, is being called in another thread.
 *
 * @par Concepts:
 * Dispatcher.
 *
 * @par Synchronous and asynchronous operations
 *
 * Synchronous operations on I/O objects implicitly run the io_context object
 * for an individual operation. The io_context functions run(), run_one(),
 * run_for(), run_until(), poll() or poll_one() must be called for the
 * io_context to perform asynchronous operations on behalf of a C++ program.
 * Notification that an asynchronous operation has completed is delivered by
 * invocation of the associated handler. Handlers are invoked only by a thread
 * that is currently calling any overload of run(), run_one(), run_for(),
 * run_until(), poll() or poll_one() for the io_context.
 *
 * @par Effect of exceptions thrown from handlers
 *
 * If an exception is thrown from a handler, the exception is allowed to
 * propagate through the throwing thread's invocation of run(), run_one(),
 * run_for(), run_until(), poll() or poll_one(). No other threads that are
 * calling any of these functions are affected. It is then the responsibility
 * of the application to catch the exception.
 *
 * After the exception has been caught, the run(), run_one(), run_for(),
 * run_until(), poll() or poll_one() call may be restarted @em without the need
 * for an intervening call to restart(). This allows the thread to rejoin the
 * io_context object's thread pool without impacting any other threads in the
 * pool.
 *
 * For example:
 *
 * @code
 * boost::asio::io_context io_context;
 * ...
 * for (;;)
 * {
 *   try
 *   {
 *     io_context.run();
 *     break; // run() exited normally
 *   }
 *   catch (my_exception& e)
 *   {
 *     // Deal with exception as appropriate.
 *   }
 * }
 * @endcode
 *
 * @par Submitting arbitrary tasks to the io_context
 *
 * To submit functions to the io_context, use the @ref boost::asio::dispatch,
 * @ref boost::asio::post or @ref boost::asio::defer free functions.
 *
 * For example:
 *
 * @code void my_task()
 * {
 *   ...
 * }
 *
 * ...
 *
 * boost::asio::io_context io_context;
 *
 * // Submit a function to the io_context.
 * boost::asio::post(io_context, my_task);
 *
 * // Submit a lambda object to the io_context.
 * boost::asio::post(io_context,
 *     []()
 *     {
 *       ...
 *     });
 *
 * // Run the io_context until it runs out of work.
 * io_context.run(); @endcode
 *
 * @par Stopping the io_context from running out of work
 *
 * Some applications may need to prevent an io_context object's run() call from
 * returning when there is no more work to do. For example, the io_context may
 * be being run in a background thread that is launched prior to the
 * application's asynchronous operations. The run() call may be kept running by
 * using the @ref make_work_guard function to create an object of type
 * boost::asio::executor_work_guard<io_context::executor_type>:
 *
 * @code boost::asio::io_context io_context;
 * boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
 *   = boost::asio::make_work_guard(io_context);
 * ... @endcode
 *
 * To effect a shutdown, the application will then need to call the io_context
 * object's stop() member function. This will cause the io_context run() call
 * to return as soon as possible, abandoning unfinished operations and without
 * permitting ready handlers to be dispatched.
 *
 * Alternatively, if the application requires that all operations and handlers
 * be allowed to finish normally, the work object may be explicitly reset.
 *
 * @code boost::asio::io_context io_context;
 * boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
 *   = boost::asio::make_work_guard(io_context);
 * ...
 * work.reset(); // Allow run() to exit. @endcode
 */
class io_context
  : public execution_context
{
private:
  typedef detail::io_context_impl impl_type;
#if defined(BOOST_ASIO_HAS_IOCP)
  friend class detail::win_iocp_overlapped_ptr;
#endif

public:
  template <typename Allocator, uintptr_t Bits>
  class basic_executor_type;

  template <typename Allocator, uintptr_t Bits>
  friend class basic_executor_type;

  /// Executor used to submit functions to an io_context.
  typedef basic_executor_type<std::allocator<void>, 0> executor_type;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  class work;
  friend class work;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  class service;

#if !defined(BOOST_ASIO_NO_EXTENSIONS) \
  && !defined(BOOST_ASIO_NO_TS_EXECUTORS)
  class strand;
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
       //   && !defined(BOOST_ASIO_NO_TS_EXECUTORS)

  /// The type used to count the number of handlers executed by the context.
  typedef std::size_t count_type;

  /// Constructor.
  BOOST_ASIO_DECL io_context();

  /// Constructor.
  /**
   * Construct with a hint about the required level of concurrency.
   *
   * @param concurrency_hint A suggestion to the implementation on how many
   * threads it should allow to run simultaneously.
   */
  BOOST_ASIO_DECL explicit io_context(int concurrency_hint);

  /// Destructor.
  /**
   * On destruction, the io_context performs the following sequence of
   * operations:
   *
   * @li For each service object @c svc in the io_context set, in reverse order
   * of the beginning of service object lifetime, performs
   * @c svc->shutdown().
   *
   * @li Uninvoked handler objects that were scheduled for deferred invocation
   * on the io_context, or any associated strand, are destroyed.
   *
   * @li For each service object @c svc in the io_context set, in reverse order
   * of the beginning of service object lifetime, performs
   * <tt>delete static_cast<io_context::service*>(svc)</tt>.
   *
   * @note The destruction sequence described above permits programs to
   * simplify their resource management by using @c shared_ptr<>. Where an
   * object's lifetime is tied to the lifetime of a connection (or some other
   * sequence of asynchronous operations), a @c shared_ptr to the object would
   * be bound into the handlers for all asynchronous operations associated with
   * it. This works as follows:
   *
   * @li When a single connection ends, all associated asynchronous operations
   * complete. The corresponding handler objects are destroyed, and all
   * @c shared_ptr references to the objects are destroyed.
   *
   * @li To shut down the whole program, the io_context function stop() is
   * called to terminate any run() calls as soon as possible. The io_context
   * destructor defined above destroys all handlers, causing all @c shared_ptr
   * references to all connection objects to be destroyed.
   */
  BOOST_ASIO_DECL ~io_context();

  /// Obtains the executor associated with the io_context.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT;

  /// Run the io_context object's event processing loop.
  /**
   * The run() function blocks until all work has finished and there are no
   * more handlers to be dispatched, or until the io_context has been stopped.
   *
   * Multiple threads may call the run() function to set up a pool of threads
   * from which the io_context may execute handlers. All threads that are
   * waiting in the pool are equivalent and the io_context may choose any one
   * of them to invoke a handler.
   *
   * A normal exit from the run() function implies that the io_context object
   * is stopped (the stopped() function returns @c true). Subsequent calls to
   * run(), run_one(), poll() or poll_one() will return immediately unless there
   * is a prior call to restart().
   *
   * @return The number of handlers that were executed.
   *
   * @note Calling the run() function from a thread that is currently calling
   * one of run(), run_one(), run_for(), run_until(), poll() or poll_one() on
   * the same io_context object may introduce the potential for deadlock. It is
   * the caller's reponsibility to avoid this.
   *
   * The poll() function may also be used to dispatch ready handlers, but
   * without blocking.
   */
  BOOST_ASIO_DECL count_type run();

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use non-error_code overload.) Run the io_context object's
  /// event processing loop.
  /**
   * The run() function blocks until all work has finished and there are no
   * more handlers to be dispatched, or until the io_context has been stopped.
   *
   * Multiple threads may call the run() function to set up a pool of threads
   * from which the io_context may execute handlers. All threads that are
   * waiting in the pool are equivalent and the io_context may choose any one
   * of them to invoke a handler.
   *
   * A normal exit from the run() function implies that the io_context object
   * is stopped (the stopped() function returns @c true). Subsequent calls to
   * run(), run_one(), poll() or poll_one() will return immediately unless there
   * is a prior call to restart().
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return The number of handlers that were executed.
   *
   * @note Calling the run() function from a thread that is currently calling
   * one of run(), run_one(), run_for(), run_until(), poll() or poll_one() on
   * the same io_context object may introduce the potential for deadlock. It is
   * the caller's reponsibility to avoid this.
   *
   * The poll() function may also be used to dispatch ready handlers, but
   * without blocking.
   */
  BOOST_ASIO_DECL count_type run(boost::system::error_code& ec);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)
  /// Run the io_context object's event processing loop for a specified
  /// duration.
  /**
   * The run_for() function blocks until all work has finished and there are no
   * more handlers to be dispatched, until the io_context has been stopped, or
   * until the specified duration has elapsed.
   *
   * @param rel_time The duration for which the call may block.
   *
   * @return The number of handlers that were executed.
   */
  template <typename Rep, typename Period>
  std::size_t run_for(const chrono::duration<Rep, Period>& rel_time);

  /// Run the io_context object's event processing loop until a specified time.
  /**
   * The run_until() function blocks until all work has finished and there are
   * no more handlers to be dispatched, until the io_context has been stopped,
   * or until the specified time has been reached.
   *
   * @param abs_time The time point until which the call may block.
   *
   * @return The number of handlers that were executed.
   */
  template <typename Clock, typename Duration>
  std::size_t run_until(const chrono::time_point<Clock, Duration>& abs_time);
#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

  /// Run the io_context object's event processing loop to execute at most one
  /// handler.
  /**
   * The run_one() function blocks until one handler has been dispatched, or
   * until the io_context has been stopped.
   *
   * @return The number of handlers that were executed. A zero return value
   * implies that the io_context object is stopped (the stopped() function
   * returns @c true). Subsequent calls to run(), run_one(), poll() or
   * poll_one() will return immediately unless there is a prior call to
   * restart().
   *
   * @note Calling the run_one() function from a thread that is currently
   * calling one of run(), run_one(), run_for(), run_until(), poll() or
   * poll_one() on the same io_context object may introduce the potential for
   * deadlock. It is the caller's reponsibility to avoid this.
   */
  BOOST_ASIO_DECL count_type run_one();

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use non-error_code overload.) Run the io_context object's
  /// event processing loop to execute at most one handler.
  /**
   * The run_one() function blocks until one handler has been dispatched, or
   * until the io_context has been stopped.
   *
   * @return The number of handlers that were executed. A zero return value
   * implies that the io_context object is stopped (the stopped() function
   * returns @c true). Subsequent calls to run(), run_one(), poll() or
   * poll_one() will return immediately unless there is a prior call to
   * restart().
   *
   * @return The number of handlers that were executed.
   *
   * @note Calling the run_one() function from a thread that is currently
   * calling one of run(), run_one(), run_for(), run_until(), poll() or
   * poll_one() on the same io_context object may introduce the potential for
   * deadlock. It is the caller's reponsibility to avoid this.
   */
  BOOST_ASIO_DECL count_type run_one(boost::system::error_code& ec);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)
  /// Run the io_context object's event processing loop for a specified duration
  /// to execute at most one handler.
  /**
   * The run_one_for() function blocks until one handler has been dispatched,
   * until the io_context has been stopped, or until the specified duration has
   * elapsed.
   *
   * @param rel_time The duration for which the call may block.
   *
   * @return The number of handlers that were executed.
   */
  template <typename Rep, typename Period>
  std::size_t run_one_for(const chrono::duration<Rep, Period>& rel_time);

  /// Run the io_context object's event processing loop until a specified time
  /// to execute at most one handler.
  /**
   * The run_one_until() function blocks until one handler has been dispatched,
   * until the io_context has been stopped, or until the specified time has
   * been reached.
   *
   * @param abs_time The time point until which the call may block.
   *
   * @return The number of handlers that were executed.
   */
  template <typename Clock, typename Duration>
  std::size_t run_one_until(
      const chrono::time_point<Clock, Duration>& abs_time);
#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

  /// Run the io_context object's event processing loop to execute ready
  /// handlers.
  /**
   * The poll() function runs handlers that are ready to run, without blocking,
   * until the io_context has been stopped or there are no more ready handlers.
   *
   * @return The number of handlers that were executed.
   */
  BOOST_ASIO_DECL count_type poll();

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use non-error_code overload.) Run the io_context object's
  /// event processing loop to execute ready handlers.
  /**
   * The poll() function runs handlers that are ready to run, without blocking,
   * until the io_context has been stopped or there are no more ready handlers.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return The number of handlers that were executed.
   */
  BOOST_ASIO_DECL count_type poll(boost::system::error_code& ec);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Run the io_context object's event processing loop to execute one ready
  /// handler.
  /**
   * The poll_one() function runs at most one handler that is ready to run,
   * without blocking.
   *
   * @return The number of handlers that were executed.
   */
  BOOST_ASIO_DECL count_type poll_one();

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use non-error_code overload.) Run the io_context object's
  /// event processing loop to execute one ready handler.
  /**
   * The poll_one() function runs at most one handler that is ready to run,
   * without blocking.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @return The number of handlers that were executed.
   */
  BOOST_ASIO_DECL count_type poll_one(boost::system::error_code& ec);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Stop the io_context object's event processing loop.
  /**
   * This function does not block, but instead simply signals the io_context to
   * stop. All invocations of its run() or run_one() member functions should
   * return as soon as possible. Subsequent calls to run(), run_one(), poll()
   * or poll_one() will return immediately until restart() is called.
   */
  BOOST_ASIO_DECL void stop();

  /// Determine whether the io_context object has been stopped.
  /**
   * This function is used to determine whether an io_context object has been
   * stopped, either through an explicit call to stop(), or due to running out
   * of work. When an io_context object is stopped, calls to run(), run_one(),
   * poll() or poll_one() will return immediately without invoking any
   * handlers.
   *
   * @return @c true if the io_context object is stopped, otherwise @c false.
   */
  BOOST_ASIO_DECL bool stopped() const;

  /// Restart the io_context in preparation for a subsequent run() invocation.
  /**
   * This function must be called prior to any second or later set of
   * invocations of the run(), run_one(), poll() or poll_one() functions when a
   * previous invocation of these functions returned due to the io_context
   * being stopped or running out of work. After a call to restart(), the
   * io_context object's stopped() function will return @c false.
   *
   * This function must not be called while there are any unfinished calls to
   * the run(), run_one(), poll() or poll_one() functions.
   */
  BOOST_ASIO_DECL void restart();

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use restart().) Reset the io_context in preparation for a
  /// subsequent run() invocation.
  /**
   * This function must be called prior to any second or later set of
   * invocations of the run(), run_one(), poll() or poll_one() functions when a
   * previous invocation of these functions returned due to the io_context
   * being stopped or running out of work. After a call to restart(), the
   * io_context object's stopped() function will return @c false.
   *
   * This function must not be called while there are any unfinished calls to
   * the run(), run_one(), poll() or poll_one() functions.
   */
  void reset();

  /// (Deprecated: Use boost::asio::dispatch().) Request the io_context to
  /// invoke the given handler.
  /**
   * This function is used to ask the io_context to execute the given handler.
   *
   * The io_context guarantees that the handler will only be called in a thread
   * in which the run(), run_one(), poll() or poll_one() member functions is
   * currently being invoked. The handler may be executed inside this function
   * if the guarantee can be met.
   *
   * @param handler The handler to be called. The io_context will make
   * a copy of the handler object as required. The function signature of the
   * handler must be: @code void handler(); @endcode
   *
   * @note This function throws an exception only if:
   *
   * @li the handler's @c asio_handler_allocate function; or
   *
   * @li the handler's copy constructor
   *
   * throws an exception.
   */
  template <typename LegacyCompletionHandler>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(LegacyCompletionHandler, void ())
  dispatch(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler);

  /// (Deprecated: Use boost::asio::post().) Request the io_context to invoke
  /// the given handler and return immediately.
  /**
   * This function is used to ask the io_context to execute the given handler,
   * but without allowing the io_context to call the handler from inside this
   * function.
   *
   * The io_context guarantees that the handler will only be called in a thread
   * in which the run(), run_one(), poll() or poll_one() member functions is
   * currently being invoked.
   *
   * @param handler The handler to be called. The io_context will make
   * a copy of the handler object as required. The function signature of the
   * handler must be: @code void handler(); @endcode
   *
   * @note This function throws an exception only if:
   *
   * @li the handler's @c asio_handler_allocate function; or
   *
   * @li the handler's copy constructor
   *
   * throws an exception.
   */
  template <typename LegacyCompletionHandler>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(LegacyCompletionHandler, void ())
  post(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler);

  /// (Deprecated: Use boost::asio::bind_executor().) Create a new handler that
  /// automatically dispatches the wrapped handler on the io_context.
  /**
   * This function is used to create a new handler function object that, when
   * invoked, will automatically pass the wrapped handler to the io_context
   * object's dispatch function.
   *
   * @param handler The handler to be wrapped. The io_context will make a copy
   * of the handler object as required. The function signature of the handler
   * must be: @code void handler(A1 a1, ... An an); @endcode
   *
   * @return A function object that, when invoked, passes the wrapped handler to
   * the io_context object's dispatch function. Given a function object with the
   * signature:
   * @code R f(A1 a1, ... An an); @endcode
   * If this function object is passed to the wrap function like so:
   * @code io_context.wrap(f); @endcode
   * then the return value is a function object with the signature
   * @code void g(A1 a1, ... An an); @endcode
   * that, when invoked, executes code equivalent to:
   * @code io_context.dispatch(boost::bind(f, a1, ... an)); @endcode
   */
  template <typename Handler>
#if defined(GENERATING_DOCUMENTATION)
  unspecified
#else
  detail::wrapped_handler<io_context&, Handler>
#endif
  wrap(Handler handler);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

private:
  io_context(const io_context&) BOOST_ASIO_DELETED;
  io_context& operator=(const io_context&) BOOST_ASIO_DELETED;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  struct initiate_dispatch;
  struct initiate_post;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  // Helper function to add the implementation.
  BOOST_ASIO_DECL impl_type& add_impl(impl_type* impl);

  // Backwards compatible overload for use with services derived from
  // io_context::service.
  template <typename Service>
  friend Service& use_service(io_context& ioc);

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
  detail::winsock_init<> init_;
#elif defined(__sun) || defined(__QNX__) || defined(__hpux) || defined(_AIX) \
  || defined(__osf__)
  detail::signal_init<> init_;
#endif

  // The implementation.
  impl_type& impl_;
};

namespace detail {

} // namespace detail

/// Executor implementation type used to submit functions to an io_context.
template <typename Allocator, uintptr_t Bits>
class io_context::basic_executor_type :
  detail::io_context_bits, Allocator
{
public:
  /// Copy constructor.
  basic_executor_type(
      const basic_executor_type& other) BOOST_ASIO_NOEXCEPT
    : Allocator(static_cast<const Allocator&>(other)),
      target_(other.target_)
  {
    if (Bits & outstanding_work_tracked)
      if (context_ptr())
        context_ptr()->impl_.work_started();
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  basic_executor_type(basic_executor_type&& other) BOOST_ASIO_NOEXCEPT
    : Allocator(BOOST_ASIO_MOVE_CAST(Allocator)(other)),
      target_(other.target_)
  {
    if (Bits & outstanding_work_tracked)
      other.target_ = 0;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  ~basic_executor_type() BOOST_ASIO_NOEXCEPT
  {
    if (Bits & outstanding_work_tracked)
      if (context_ptr())
        context_ptr()->impl_.work_finished();
  }

  /// Assignment operator.
  basic_executor_type& operator=(
      const basic_executor_type& other) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move assignment operator.
  basic_executor_type& operator=(
      basic_executor_type&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_require_fn::impl;
  friend struct boost_asio_prefer_fn::impl;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Obtain an executor with the @c blocking.possibly property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_io_context.get_executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.possibly); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type require(
      execution::blocking_t::possibly_t) const
  {
    return basic_executor_type(context_ptr(),
        *this, bits() & ~blocking_never);
  }

  /// Obtain an executor with the @c blocking.never property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_io_context.get_executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.never); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type require(
      execution::blocking_t::never_t) const
  {
    return basic_executor_type(context_ptr(),
        *this, bits() | blocking_never);
  }

  /// Obtain an executor with the @c relationship.fork property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_io_context.get_executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::relationship.fork); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type require(
      execution::relationship_t::fork_t) const
  {
    return basic_executor_type(context_ptr(),
        *this, bits() & ~relationship_continuation);
  }

  /// Obtain an executor with the @c relationship.continuation property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_io_context.get_executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::relationship.continuation); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type require(
      execution::relationship_t::continuation_t) const
  {
    return basic_executor_type(context_ptr(),
        *this, bits() | relationship_continuation);
  }

  /// Obtain an executor with the @c outstanding_work.tracked property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_io_context.get_executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::outstanding_work.tracked); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<Allocator,
      BOOST_ASIO_UNSPECIFIED(Bits | outstanding_work_tracked)>
  require(execution::outstanding_work_t::tracked_t) const
  {
    return basic_executor_type<Allocator, Bits | outstanding_work_tracked>(
        context_ptr(), *this, bits());
  }

  /// Obtain an executor with the @c outstanding_work.untracked property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_io_context.get_executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::outstanding_work.untracked); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<Allocator,
      BOOST_ASIO_UNSPECIFIED(Bits & ~outstanding_work_tracked)>
  require(execution::outstanding_work_t::untracked_t) const
  {
    return basic_executor_type<Allocator, Bits & ~outstanding_work_tracked>(
        context_ptr(), *this, bits());
  }

  /// Obtain an executor with the specified @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_io_context.get_executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::allocator(my_allocator)); @endcode
   */
  template <typename OtherAllocator>
  BOOST_ASIO_CONSTEXPR basic_executor_type<OtherAllocator, Bits>
  require(execution::allocator_t<OtherAllocator> a) const
  {
    return basic_executor_type<OtherAllocator, Bits>(
        context_ptr(), a.value(), bits());
  }

  /// Obtain an executor with the default @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code auto ex1 = my_io_context.get_executor();
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::allocator); @endcode
   */
  BOOST_ASIO_CONSTEXPR basic_executor_type<std::allocator<void>, Bits>
  require(execution::allocator_t<void>) const
  {
    return basic_executor_type<std::allocator<void>, Bits>(
        context_ptr(), std::allocator<void>(), bits());
  }

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_query_fn::impl;
  friend struct boost::asio::execution::detail::mapping_t<0>;
  friend struct boost::asio::execution::detail::outstanding_work_t<0>;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Query the current value of the @c mapping property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_io_context.get_executor();
   * if (boost::asio::query(ex, boost::asio::execution::mapping)
   *       == boost::asio::execution::mapping.thread)
   *   ... @endcode
   */
  static BOOST_ASIO_CONSTEXPR execution::mapping_t query(
      execution::mapping_t) BOOST_ASIO_NOEXCEPT
  {
    return execution::mapping.thread;
  }

  /// Query the current value of the @c context property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_io_context.get_executor();
   * boost::asio::io_context& ctx = boost::asio::query(
   *     ex, boost::asio::execution::context); @endcode
   */
  io_context& query(execution::context_t) const BOOST_ASIO_NOEXCEPT
  {
    return *context_ptr();
  }

  /// Query the current value of the @c blocking property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_io_context.get_executor();
   * if (boost::asio::query(ex, boost::asio::execution::blocking)
   *       == boost::asio::execution::blocking.always)
   *   ... @endcode
   */
  BOOST_ASIO_CONSTEXPR execution::blocking_t query(
      execution::blocking_t) const BOOST_ASIO_NOEXCEPT
  {
    return (bits() & blocking_never)
      ? execution::blocking_t(execution::blocking.never)
      : execution::blocking_t(execution::blocking.possibly);
  }

  /// Query the current value of the @c relationship property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_io_context.get_executor();
   * if (boost::asio::query(ex, boost::asio::execution::relationship)
   *       == boost::asio::execution::relationship.continuation)
   *   ... @endcode
   */
  BOOST_ASIO_CONSTEXPR execution::relationship_t query(
      execution::relationship_t) const BOOST_ASIO_NOEXCEPT
  {
    return (bits() & relationship_continuation)
      ? execution::relationship_t(execution::relationship.continuation)
      : execution::relationship_t(execution::relationship.fork);
  }

  /// Query the current value of the @c outstanding_work property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_io_context.get_executor();
   * if (boost::asio::query(ex, boost::asio::execution::outstanding_work)
   *       == boost::asio::execution::outstanding_work.tracked)
   *   ... @endcode
   */
  static BOOST_ASIO_CONSTEXPR execution::outstanding_work_t query(
      execution::outstanding_work_t) BOOST_ASIO_NOEXCEPT
  {
    return (Bits & outstanding_work_tracked)
      ? execution::outstanding_work_t(execution::outstanding_work.tracked)
      : execution::outstanding_work_t(execution::outstanding_work.untracked);
  }

  /// Query the current value of the @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_io_context.get_executor();
   * auto alloc = boost::asio::query(ex,
   *     boost::asio::execution::allocator); @endcode
   */
  template <typename OtherAllocator>
  BOOST_ASIO_CONSTEXPR Allocator query(
      execution::allocator_t<OtherAllocator>) const BOOST_ASIO_NOEXCEPT
  {
    return static_cast<const Allocator&>(*this);
  }

  /// Query the current value of the @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code auto ex = my_io_context.get_executor();
   * auto alloc = boost::asio::query(ex,
   *     boost::asio::execution::allocator); @endcode
   */
  BOOST_ASIO_CONSTEXPR Allocator query(
      execution::allocator_t<void>) const BOOST_ASIO_NOEXCEPT
  {
    return static_cast<const Allocator&>(*this);
  }

public:
  /// Determine whether the io_context is running in the current thread.
  /**
   * @return @c true if the current thread is running the io_context. Otherwise
   * returns @c false.
   */
  bool running_in_this_thread() const BOOST_ASIO_NOEXCEPT;

  /// Compare two executors for equality.
  /**
   * Two executors are equal if they refer to the same underlying io_context.
   */
  friend bool operator==(const basic_executor_type& a,
      const basic_executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return a.target_ == b.target_
      && static_cast<const Allocator&>(a) == static_cast<const Allocator&>(b);
  }

  /// Compare two executors for inequality.
  /**
   * Two executors are equal if they refer to the same underlying io_context.
   */
  friend bool operator!=(const basic_executor_type& a,
      const basic_executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return a.target_ != b.target_
      || static_cast<const Allocator&>(a) != static_cast<const Allocator&>(b);
  }

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_execution_execute_fn::impl;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Execution function.
  /**
   * Do not call this function directly. It is intended for use with the
   * execution::execute customisation point.
   *
   * For example:
   * @code auto ex = my_io_context.get_executor();
   * execution::execute(ex, my_function_object); @endcode
   */
  template <typename Function>
  void execute(BOOST_ASIO_MOVE_ARG(Function) f) const;

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
public:
  /// Obtain the underlying execution context.
  io_context& context() const BOOST_ASIO_NOEXCEPT;

  /// Inform the io_context that it has some outstanding work to do.
  /**
   * This function is used to inform the io_context that some work has begun.
   * This ensures that the io_context's run() and run_one() functions do not
   * exit while the work is underway.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT;

  /// Inform the io_context that some work is no longer outstanding.
  /**
   * This function is used to inform the io_context that some work has
   * finished. Once the count of unfinished work reaches zero, the io_context
   * is stopped and the run() and run_one() functions may exit.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT;

  /// Request the io_context to invoke the given function object.
  /**
   * This function is used to ask the io_context to execute the given function
   * object. If the current thread is running the io_context, @c dispatch()
   * executes the function before returning. Otherwise, the function will be
   * scheduled to run on the io_context.
   *
   * @param f The function object to be called. The executor will make a copy
   * of the handler object as required. The function signature of the function
   * object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f,
      const OtherAllocator& a) const;

  /// Request the io_context to invoke the given function object.
  /**
   * This function is used to ask the io_context to execute the given function
   * object. The function object will never be executed inside @c post().
   * Instead, it will be scheduled to run on the io_context.
   *
   * @param f The function object to be called. The executor will make a copy
   * of the handler object as required. The function signature of the function
   * object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f,
      const OtherAllocator& a) const;

  /// Request the io_context to invoke the given function object.
  /**
   * This function is used to ask the io_context to execute the given function
   * object. The function object will never be executed inside @c defer().
   * Instead, it will be scheduled to run on the io_context.
   *
   * If the current thread belongs to the io_context, @c defer() will delay
   * scheduling the function object until the current thread returns control to
   * the pool.
   *
   * @param f The function object to be called. The executor will make a copy
   * of the handler object as required. The function signature of the function
   * object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f,
      const OtherAllocator& a) const;
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

private:
  friend class io_context;
  template <typename, uintptr_t> friend class basic_executor_type;

  // Constructor used by io_context::get_executor().
  explicit basic_executor_type(io_context& i) BOOST_ASIO_NOEXCEPT
    : Allocator(),
      target_(reinterpret_cast<uintptr_t>(&i))
  {
    if (Bits & outstanding_work_tracked)
      context_ptr()->impl_.work_started();
  }

  // Constructor used by require().
  basic_executor_type(io_context* i,
      const Allocator& a, uintptr_t bits) BOOST_ASIO_NOEXCEPT
    : Allocator(a),
      target_(reinterpret_cast<uintptr_t>(i) | bits)
  {
    if (Bits & outstanding_work_tracked)
      if (context_ptr())
        context_ptr()->impl_.work_started();
  }

  io_context* context_ptr() const BOOST_ASIO_NOEXCEPT
  {
    return reinterpret_cast<io_context*>(target_ & ~runtime_bits);
  }

  uintptr_t bits() const BOOST_ASIO_NOEXCEPT
  {
    return target_ & runtime_bits;
  }

  // The underlying io_context and runtime bits.
  uintptr_t target_;
};

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// (Deprecated: Use executor_work_guard.) Class to inform the io_context when
/// it has work to do.
/**
 * The work class is used to inform the io_context when work starts and
 * finishes. This ensures that the io_context object's run() function will not
 * exit while work is underway, and that it does exit when there is no
 * unfinished work remaining.
 *
 * The work class is copy-constructible so that it may be used as a data member
 * in a handler class. It is not assignable.
 */
class io_context::work
{
public:
  /// Constructor notifies the io_context that work is starting.
  /**
   * The constructor is used to inform the io_context that some work has begun.
   * This ensures that the io_context object's run() function will not exit
   * while the work is underway.
   */
  explicit work(boost::asio::io_context& io_context);

  /// Copy constructor notifies the io_context that work is starting.
  /**
   * The constructor is used to inform the io_context that some work has begun.
   * This ensures that the io_context object's run() function will not exit
   * while the work is underway.
   */
  work(const work& other);

  /// Destructor notifies the io_context that the work is complete.
  /**
   * The destructor is used to inform the io_context that some work has
   * finished. Once the count of unfinished work reaches zero, the io_context
   * object's run() function is permitted to exit.
   */
  ~work();

  /// Get the io_context associated with the work.
  boost::asio::io_context& get_io_context();

private:
  // Prevent assignment.
  void operator=(const work& other);

  // The io_context implementation.
  detail::io_context_impl& io_context_impl_;
};
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

/// Base class for all io_context services.
class io_context::service
  : public execution_context::service
{
public:
  /// Get the io_context object that owns the service.
  boost::asio::io_context& get_io_context();

private:
  /// Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL virtual void shutdown();

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use shutdown().) Destroy all user-defined handler objects
  /// owned by the service.
  BOOST_ASIO_DECL virtual void shutdown_service();
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Handle notification of a fork-related event to perform any necessary
  /// housekeeping.
  /**
   * This function is not a pure virtual so that services only have to
   * implement it if necessary. The default implementation does nothing.
   */
  BOOST_ASIO_DECL virtual void notify_fork(
      execution_context::fork_event event);

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use notify_fork().) Handle notification of a fork-related
  /// event to perform any necessary housekeeping.
  /**
   * This function is not a pure virtual so that services only have to
   * implement it if necessary. The default implementation does nothing.
   */
  BOOST_ASIO_DECL virtual void fork_service(
      execution_context::fork_event event);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

protected:
  /// Constructor.
  /**
   * @param owner The io_context object that owns the service.
   */
  BOOST_ASIO_DECL service(boost::asio::io_context& owner);

  /// Destructor.
  BOOST_ASIO_DECL virtual ~service();
};

namespace detail {

// Special service base class to keep classes header-file only.
template <typename Type>
class service_base
  : public boost::asio::io_context::service
{
public:
  static boost::asio::detail::service_id<Type> id;

  // Constructor.
  service_base(boost::asio::io_context& io_context)
    : boost::asio::io_context::service(io_context)
  {
  }
};

template <typename Type>
boost::asio::detail::service_id<Type> service_base<Type>::id;

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename Allocator, uintptr_t Bits>
struct equality_comparable<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

template <typename Allocator, uintptr_t Bits, typename Function>
struct execute_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    Function
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

template <typename Allocator, uintptr_t Bits>
struct require_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::blocking_t::possibly_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::io_context::basic_executor_type<
      Allocator, Bits> result_type;
};

template <typename Allocator, uintptr_t Bits>
struct require_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::blocking_t::never_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::io_context::basic_executor_type<
      Allocator, Bits> result_type;
};

template <typename Allocator, uintptr_t Bits>
struct require_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::relationship_t::fork_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::io_context::basic_executor_type<
      Allocator, Bits> result_type;
};

template <typename Allocator, uintptr_t Bits>
struct require_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::relationship_t::continuation_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::io_context::basic_executor_type<
      Allocator, Bits> result_type;
};

template <typename Allocator, uintptr_t Bits>
struct require_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::outstanding_work_t::tracked_t
  > : boost::asio::detail::io_context_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::io_context::basic_executor_type<
      Allocator, Bits | outstanding_work_tracked> result_type;
};

template <typename Allocator, uintptr_t Bits>
struct require_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::outstanding_work_t::untracked_t
  > : boost::asio::detail::io_context_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::io_context::basic_executor_type<
      Allocator, Bits & ~outstanding_work_tracked> result_type;
};

template <typename Allocator, uintptr_t Bits>
struct require_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::allocator_t<void>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::io_context::basic_executor_type<
      std::allocator<void>, Bits> result_type;
};

template <uintptr_t Bits,
    typename Allocator, typename OtherAllocator>
struct require_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::allocator_t<OtherAllocator>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::io_context::basic_executor_type<
      OtherAllocator, Bits> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

template <typename Allocator, uintptr_t Bits, typename Property>
struct query_static_constexpr_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::outstanding_work_t
      >::value
    >::type
  > : boost::asio::detail::io_context_bits
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::outstanding_work_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return (Bits & outstanding_work_tracked)
      ? execution::outstanding_work_t(execution::outstanding_work.tracked)
      : execution::outstanding_work_t(execution::outstanding_work.untracked);
  }
};

template <typename Allocator, uintptr_t Bits, typename Property>
struct query_static_constexpr_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::mapping_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::mapping_t::thread_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

template <typename Allocator, uintptr_t Bits, typename Property>
struct query_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::blocking_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::blocking_t result_type;
};

template <typename Allocator, uintptr_t Bits, typename Property>
struct query_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::relationship_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::relationship_t result_type;
};

template <typename Allocator, uintptr_t Bits>
struct query_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::context_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::io_context& result_type;
};

template <typename Allocator, uintptr_t Bits>
struct query_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::allocator_t<void>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef Allocator result_type;
};

template <typename Allocator, uintptr_t Bits, typename OtherAllocator>
struct query_member<
    boost::asio::io_context::basic_executor_type<Allocator, Bits>,
    boost::asio::execution::allocator_t<OtherAllocator>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef Allocator result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

} // namespace traits

namespace execution {

template <>
struct is_executor<io_context> : false_type
{
};

} // namespace execution

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/io_context.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/io_context.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

// If both io_context.hpp and strand.hpp have been included, automatically
// include the header file needed for the io_context::strand class.
#if !defined(BOOST_ASIO_NO_EXTENSIONS)
# if defined(BOOST_ASIO_STRAND_HPP)
#  include <boost/asio/io_context_strand.hpp>
# endif // defined(BOOST_ASIO_STRAND_HPP)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

#endif // BOOST_ASIO_IO_CONTEXT_HPP

/* io_context.hpp
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
*/