//
// spawn.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/wrapped_handler.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/strand.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Context object the represents the currently executing coroutine.
/**
 * The basic_yield_context class is used to represent the currently executing
 * stackful coroutine. A basic_yield_context may be passed as a handler to an
 * asynchronous operation. For example:
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
/// Context object that represents the currently executing coroutine.
typedef basic_yield_context<unspecified> yield_context;
#else // defined(GENERATING_DOCUMENTATION)
typedef basic_yield_context<
  executor_binder<void(*)(), executor> > yield_context;
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
    typename enable_if<!is_executor<typename decay<Handler>::type>::value &&
      !is_convertible<Handler&, execution_context&>::value>::type* = 0);

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
    typename enable_if<is_executor<Executor>::value>::type* = 0);

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
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type* = 0);

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/spawn.hpp>

#endif // BOOST_ASIO_SPAWN_HPP

/* spawn.hpp
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
*/