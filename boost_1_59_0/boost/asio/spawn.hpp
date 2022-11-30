//
// spawn.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SPAWN_HPP
#define BOOST_ASIO_SPAWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/wrapped_handler.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/strand.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A @ref completion_token that represents the currently executing coroutine.
/**
 * The basic_yield_context class is a completion token type that is used to
 * represent the currently executing stackful coroutine. A basic_yield_context
 * object may be passed as a completion token to an asynchronous operation. For
 * example:
 *
 * @code template <typename Handler>
 * void my_coroutine(basic_yield_context<Handler> yield)
 * {
 *   ...
 *   std::size_t n = my_socket.async_read_some(buffer, yield);
 *   ...
 * } @endcode
 *
 * The initiating function (async_read_some in the above example) suspends the
 * current coroutine. The coroutine is resumed when the asynchronous operation
 * completes, and the result of the operation is returned.
 */
template <typename Handler>
class basic_yield_context
{
public:
  /// The coroutine callee type, used by the implementation.
  /**
   * When using Boost.Coroutine v1, this type is:
   * @code typename coroutine<void()> @endcode
   * When using Boost.Coroutine v2 (unidirectional coroutines), this type is:
   * @code push_coroutine<void> @endcode
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined callee_type;
#elif defined(BOOST_COROUTINES_UNIDIRECT) || defined(BOOST_COROUTINES_V2)
  typedef boost::coroutines::push_coroutine<void> callee_type;
#else
  typedef boost::coroutines::coroutine<void()> callee_type;
#endif
  
  /// The coroutine caller type, used by the implementation.
  /**
   * When using Boost.Coroutine v1, this type is:
   * @code typename coroutine<void()>::caller_type @endcode
   * When using Boost.Coroutine v2 (unidirectional coroutines), this type is:
   * @code pull_coroutine<void> @endcode
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined caller_type;
#elif defined(BOOST_COROUTINES_UNIDIRECT) || defined(BOOST_COROUTINES_V2)
  typedef boost::coroutines::pull_coroutine<void> caller_type;
#else
  typedef boost::coroutines::coroutine<void()>::caller_type caller_type;
#endif

  /// Construct a yield context to represent the specified coroutine.
  /**
   * Most applications do not need to use this constructor. Instead, the
   * spawn() function passes a yield context as an argument to the coroutine
   * function.
   */
  basic_yield_context(
      const detail::weak_ptr<callee_type>& coro,
      caller_type& ca, Handler& handler)
    : coro_(coro),
      ca_(ca),
      handler_(handler),
      ec_(0)
  {
  }

  /// Construct a yield context from another yield context type.
  /**
   * Requires that OtherHandler be convertible to Handler.
   */
  template <typename OtherHandler>
  basic_yield_context(const basic_yield_context<OtherHandler>& other)
    : coro_(other.coro_),
      ca_(other.ca_),
      handler_(other.handler_),
      ec_(other.ec_)
  {
  }

  /// Return a yield context that sets the specified error_code.
  /**
   * By default, when a yield context is used with an asynchronous operation, a
   * non-success error_code is converted to system_error and thrown. This
   * operator may be used to specify an error_code object that should instead be
   * set with the asynchronous operation's result. For example:
   *
   * @code template <typename Handler>
   * void my_coroutine(basic_yield_context<Handler> yield)
   * {
   *   ...
   *   std::size_t n = my_socket.async_read_some(buffer, yield[ec]);
   *   if (ec)
   *   {
   *     // An error occurred.
   *   }
   *   ...
   * } @endcode
   */
  basic_yield_context operator[](boost::system::error_code& ec) const
  {
    basic_yield_context tmp(*this);
    tmp.ec_ = &ec;
    return tmp;
  }

#if defined(GENERATING_DOCUMENTATION)
private:
#endif // defined(GENERATING_DOCUMENTATION)
  detail::weak_ptr<callee_type> coro_;
  caller_type& ca_;
  Handler handler_;
  boost::system::error_code* ec_;
};

#if defined(GENERATING_DOCUMENTATION)
/// A @ref completion_token object that represents the currently executing
/// coroutine.
typedef basic_yield_context<unspecified> yield_context;
#else // defined(GENERATING_DOCUMENTATION)
typedef basic_yield_context<
  executor_binder<void(*)(), any_io_executor> > yield_context;
#endif // defined(GENERATING_DOCUMENTATION)

/**
 * @defgroup spawn boost::asio::spawn
 *
 * @brief Start a new stackful coroutine.
 *
 * The spawn() function is a high-level wrapper over the Boost.Coroutine
 * library. This function enables programs to implement asynchronous logic in a
 * synchronous manner, as illustrated by the following example:
 *
 * @code boost::asio::spawn(my_strand, do_echo);
 *
 * // ...
 *
 * void do_echo(boost::asio::yield_context yield)
 * {
 *   try
 *   {
 *     char data[128];
 *     for (;;)
 *     {
 *       std::size_t length =
 *         my_socket.async_read_some(
 *           boost::asio::buffer(data), yield);
 *
 *       boost::asio::async_write(my_socket,
 *           boost::asio::buffer(data, length), yield);
 *     }
 *   }
 *   catch (std::exception& e)
 *   {
 *     // ...
 *   }
 * } @endcode
 */
/*@{*/

/// Start a new stackful coroutine, calling the specified handler when it
/// completes.
/**
 * This function is used to launch a new coroutine.
 *
 * @param function The coroutine function. The function must have the signature:
 * @code void function(basic_yield_context<Handler> yield); @endcode
 *
 * @param attributes Boost.Coroutine attributes used to customise the coroutine.
 */
template <typename Function>
void spawn(BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes
      = boost::coroutines::attributes());

/// Start a new stackful coroutine, calling the specified handler when it
/// completes.
/**
 * This function is used to launch a new coroutine.
 *
 * @param handler A handler to be called when the coroutine exits. More
 * importantly, the handler provides an execution context (via the the handler
 * invocation hook) for the coroutine. The handler must have the signature:
 * @code void handler(); @endcode
 *
 * @param function The coroutine function. The function must have the signature:
 * @code void function(basic_yield_context<Handler> yield); @endcode
 *
 * @param attributes Boost.Coroutine attributes used to customise the coroutine.
 */
template <typename Handler, typename Function>
void spawn(BOOST_ASIO_MOVE_ARG(Handler) handler,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes
      = boost::coroutines::attributes(),
    typename constraint<
      !is_executor<typename decay<Handler>::type>::value &&
      !execution::is_executor<typename decay<Handler>::type>::value &&
      !is_convertible<Handler&, execution_context&>::value>::type = 0);

/// Start a new stackful coroutine, inheriting the execution context of another.
/**
 * This function is used to launch a new coroutine.
 *
 * @param ctx Identifies the current coroutine as a parent of the new
 * coroutine. This specifies that the new coroutine should inherit the
 * execution context of the parent. For example, if the parent coroutine is
 * executing in a particular strand, then the new coroutine will execute in the
 * same strand.
 *
 * @param function The coroutine function. The function must have the signature:
 * @code void function(basic_yield_context<Handler> yield); @endcode
 *
 * @param attributes Boost.Coroutine attributes used to customise the coroutine.
 */
template <typename Handler, typename Function>
void spawn(basic_yield_context<Handler> ctx,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes
      = boost::coroutines::attributes());

/// Start a new stackful coroutine that executes on a given executor.
/**
 * This function is used to launch a new coroutine.
 *
 * @param ex Identifies the executor that will run the coroutine. The new
 * coroutine is implicitly given its own strand within this executor.
 *
 * @param function The coroutine function. The function must have the signature:
 * @code void function(yield_context yield); @endcode
 *
 * @param attributes Boost.Coroutine attributes used to customise the coroutine.
 */
template <typename Function, typename Executor>
void spawn(const Executor& ex,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes
      = boost::coroutines::attributes(),
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0);

/// Start a new stackful coroutine that executes on a given strand.
/**
 * This function is used to launch a new coroutine.
 *
 * @param ex Identifies the strand that will run the coroutine.
 *
 * @param function The coroutine function. The function must have the signature:
 * @code void function(yield_context yield); @endcode
 *
 * @param attributes Boost.Coroutine attributes used to customise the coroutine.
 */
template <typename Function, typename Executor>
void spawn(const strand<Executor>& ex,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes
      = boost::coroutines::attributes());

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

/// Start a new stackful coroutine that executes in the context of a strand.
/**
 * This function is used to launch a new coroutine.
 *
 * @param s Identifies a strand. By starting multiple coroutines on the same
 * strand, the implementation ensures that none of those coroutines can execute
 * simultaneously.
 *
 * @param function The coroutine function. The function must have the signature:
 * @code void function(yield_context yield); @endcode
 *
 * @param attributes Boost.Coroutine attributes used to customise the coroutine.
 */
template <typename Function>
void spawn(const boost::asio::io_context::strand& s,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes
      = boost::coroutines::attributes());

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

/// Start a new stackful coroutine that executes on a given execution context.
/**
 * This function is used to launch a new coroutine.
 *
 * @param ctx Identifies the execution context that will run the coroutine. The
 * new coroutine is implicitly given its own strand within this execution
 * context.
 *
 * @param function The coroutine function. The function must have the signature:
 * @code void function(yield_context yield); @endcode
 *
 * @param attributes Boost.Coroutine attributes used to customise the coroutine.
 */
template <typename Function, typename ExecutionContext>
void spawn(ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes
      = boost::coroutines::attributes(),
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type = 0);

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/spawn.hpp>

#endif // BOOST_ASIO_SPAWN_HPP

/* spawn.hpp
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
*/