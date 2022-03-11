//
// io_context.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/wrapped_handler.hpp>
#include <boost/system/error_code.hpp>
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

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail {
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context io_context_impl;
  class win_iocp_overlapped_ptr;
#else
  typedef class scheduler io_context_impl;
#endif
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
 * creating an object of type
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
  class executor_type;
  friend class executor_type;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  class work;
  friend class work;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  class service;

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
  class strand;
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

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
  /// (Deprecated: Use non-error_code overlaod.) Run the io_context object's
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

/// Executor used to submit functions to an io_context.
class io_context::executor_type
{
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
  template <typename Function, typename Allocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

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
  template <typename Function, typename Allocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

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
  template <typename Function, typename Allocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

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
  friend bool operator==(const executor_type& a,
      const executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return &a.io_context_ == &b.io_context_;
  }

  /// Compare two executors for inequality.
  /**
   * Two executors are equal if they refer to the same underlying io_context.
   */
  friend bool operator!=(const executor_type& a,
      const executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return &a.io_context_ != &b.io_context_;
  }

private:
  friend class io_context;

  // Constructor.
  explicit executor_type(io_context& i) : io_context_(i) {}

  // The underlying io_context.
  io_context& io_context_;
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