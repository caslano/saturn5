//
// co_spawn.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_CO_SPAWN_HPP
#define BOOST_ASIO_CO_SPAWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/awaitable.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct awaitable_signature;

template <typename T, typename Executor>
struct awaitable_signature<awaitable<T, Executor>>
{
  typedef void type(std::exception_ptr, T);
};

template <typename Executor>
struct awaitable_signature<awaitable<void, Executor>>
{
  typedef void type(std::exception_ptr);
};

} // namespace detail

/// Spawn a new coroutined-based thread of execution.
/**
 * @param ex The executor that will be used to schedule the new thread of
 * execution.
 *
 * @param a The boost::asio::awaitable object that is the result of calling the
 * coroutine's entry point function.
 *
 * @param token The @ref completion_token that will handle the notification that
 * the thread of execution has completed. The function signature of the
 * completion handler must be:
 * @code void handler(std::exception_ptr, T); @endcode
 *
 * @par Completion Signature
 * @code void(std::exception_ptr, T) @endcode
 *
 * @par Example
 * @code
 * boost::asio::awaitable<std::size_t> echo(tcp::socket socket)
 * {
 *   std::size_t bytes_transferred = 0;
 *
 *   try
 *   {
 *     char data[1024];
 *     for (;;)
 *     {
 *       std::size_t n = co_await socket.async_read_some(
 *           boost::asio::buffer(data), boost::asio::use_awaitable);
 *
 *       co_await boost::asio::async_write(socket,
 *           boost::asio::buffer(data, n), boost::asio::use_awaitable);
 *
 *       bytes_transferred += n;
 *     }
 *   }
 *   catch (const std::exception&)
 *   {
 *   }
 *
 *   co_return bytes_transferred;
 * }
 *
 * // ...
 *
 * boost::asio::co_spawn(my_executor,
 *   echo(std::move(my_tcp_socket)),
 *   [](std::exception_ptr e, std::size_t n)
 *   {
 *     std::cout << "transferred " << n << "\n";
 *   });
 * @endcode
 *
 * @par Per-Operation Cancellation
 * The new thread of execution is created with a cancellation state that
 * supports @c cancellation_type::terminal values only. To change the
 * cancellation state, call boost::asio::this_coro::reset_cancellation_state.
 */
template <typename Executor, typename T, typename AwaitableExecutor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(
      void(std::exception_ptr, T)) CompletionToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr, T))
co_spawn(const Executor& ex, awaitable<T, AwaitableExecutor> a,
    CompletionToken&& token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename constraint<
      (is_executor<Executor>::value || execution::is_executor<Executor>::value)
        && is_convertible<Executor, AwaitableExecutor>::value
    >::type = 0);

/// Spawn a new coroutined-based thread of execution.
/**
 * @param ex The executor that will be used to schedule the new thread of
 * execution.
 *
 * @param a The boost::asio::awaitable object that is the result of calling the
 * coroutine's entry point function.
 *
 * @param token The @ref completion_token that will handle the notification that
 * the thread of execution has completed. The function signature of the
 * completion handler must be:
 * @code void handler(std::exception_ptr); @endcode
 *
 * @par Completion Signature
 * @code void(std::exception_ptr) @endcode
 *
 * @par Example
 * @code
 * boost::asio::awaitable<void> echo(tcp::socket socket)
 * {
 *   try
 *   {
 *     char data[1024];
 *     for (;;)
 *     {
 *       std::size_t n = co_await socket.async_read_some(
 *           boost::asio::buffer(data), boost::asio::use_awaitable);
 *
 *       co_await boost::asio::async_write(socket,
 *           boost::asio::buffer(data, n), boost::asio::use_awaitable);
 *     }
 *   }
 *   catch (const std::exception& e)
 *   {
 *     std::cerr << "Exception: " << e.what() << "\n";
 *   }
 * }
 *
 * // ...
 *
 * boost::asio::co_spawn(my_executor,
 *   echo(std::move(my_tcp_socket)),
 *   boost::asio::detached);
 * @endcode
 *
 * @par Per-Operation Cancellation
 * The new thread of execution is created with a cancellation state that
 * supports @c cancellation_type::terminal values only. To change the
 * cancellation state, call boost::asio::this_coro::reset_cancellation_state.
 */
template <typename Executor, typename AwaitableExecutor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(
      void(std::exception_ptr)) CompletionToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr))
co_spawn(const Executor& ex, awaitable<void, AwaitableExecutor> a,
    CompletionToken&& token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename constraint<
      (is_executor<Executor>::value || execution::is_executor<Executor>::value)
        && is_convertible<Executor, AwaitableExecutor>::value
    >::type = 0);

/// Spawn a new coroutined-based thread of execution.
/**
 * @param ctx An execution context that will provide the executor to be used to
 * schedule the new thread of execution.
 *
 * @param a The boost::asio::awaitable object that is the result of calling the
 * coroutine's entry point function.
 *
 * @param token The @ref completion_token that will handle the notification that
 * the thread of execution has completed. The function signature of the
 * completion handler must be:
 * @code void handler(std::exception_ptr); @endcode
 *
 * @par Completion Signature
 * @code void(std::exception_ptr, T) @endcode
 *
 * @par Example
 * @code
 * boost::asio::awaitable<std::size_t> echo(tcp::socket socket)
 * {
 *   std::size_t bytes_transferred = 0;
 *
 *   try
 *   {
 *     char data[1024];
 *     for (;;)
 *     {
 *       std::size_t n = co_await socket.async_read_some(
 *           boost::asio::buffer(data), boost::asio::use_awaitable);
 *
 *       co_await boost::asio::async_write(socket,
 *           boost::asio::buffer(data, n), boost::asio::use_awaitable);
 *
 *       bytes_transferred += n;
 *     }
 *   }
 *   catch (const std::exception&)
 *   {
 *   }
 *
 *   co_return bytes_transferred;
 * }
 *
 * // ...
 *
 * boost::asio::co_spawn(my_io_context,
 *   echo(std::move(my_tcp_socket)),
 *   [](std::exception_ptr e, std::size_t n)
 *   {
 *     std::cout << "transferred " << n << "\n";
 *   });
 * @endcode
 *
 * @par Per-Operation Cancellation
 * The new thread of execution is created with a cancellation state that
 * supports @c cancellation_type::terminal values only. To change the
 * cancellation state, call boost::asio::this_coro::reset_cancellation_state.
 */
template <typename ExecutionContext, typename T, typename AwaitableExecutor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(
      void(std::exception_ptr, T)) CompletionToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename ExecutionContext::executor_type)>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr, T))
co_spawn(ExecutionContext& ctx, awaitable<T, AwaitableExecutor> a,
    CompletionToken&& token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
        && is_convertible<typename ExecutionContext::executor_type,
          AwaitableExecutor>::value
    >::type = 0);

/// Spawn a new coroutined-based thread of execution.
/**
 * @param ctx An execution context that will provide the executor to be used to
 * schedule the new thread of execution.
 *
 * @param a The boost::asio::awaitable object that is the result of calling the
 * coroutine's entry point function.
 *
 * @param token The @ref completion_token that will handle the notification that
 * the thread of execution has completed. The function signature of the
 * completion handler must be:
 * @code void handler(std::exception_ptr); @endcode
 *
 * @par Completion Signature
 * @code void(std::exception_ptr) @endcode
 *
 * @par Example
 * @code
 * boost::asio::awaitable<void> echo(tcp::socket socket)
 * {
 *   try
 *   {
 *     char data[1024];
 *     for (;;)
 *     {
 *       std::size_t n = co_await socket.async_read_some(
 *           boost::asio::buffer(data), boost::asio::use_awaitable);
 *
 *       co_await boost::asio::async_write(socket,
 *           boost::asio::buffer(data, n), boost::asio::use_awaitable);
 *     }
 *   }
 *   catch (const std::exception& e)
 *   {
 *     std::cerr << "Exception: " << e.what() << "\n";
 *   }
 * }
 *
 * // ...
 *
 * boost::asio::co_spawn(my_io_context,
 *   echo(std::move(my_tcp_socket)),
 *   boost::asio::detached);
 * @endcode
 *
 * @par Per-Operation Cancellation
 * The new thread of execution is created with a cancellation state that
 * supports @c cancellation_type::terminal values only. To change the
 * cancellation state, call boost::asio::this_coro::reset_cancellation_state.
 */
template <typename ExecutionContext, typename AwaitableExecutor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(
      void(std::exception_ptr)) CompletionToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename ExecutionContext::executor_type)>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(
    CompletionToken, void(std::exception_ptr))
co_spawn(ExecutionContext& ctx, awaitable<void, AwaitableExecutor> a,
    CompletionToken&& token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
        && is_convertible<typename ExecutionContext::executor_type,
          AwaitableExecutor>::value
    >::type = 0);

/// Spawn a new coroutined-based thread of execution.
/**
 * @param ex The executor that will be used to schedule the new thread of
 * execution.
 *
 * @param f A nullary function object with a return type of the form
 * @c boost::asio::awaitable<R,E> that will be used as the coroutine's entry
 * point.
 *
 * @param token The @ref completion_token that will handle the notification
 * that the thread of execution has completed. If @c R is @c void, the function
 * signature of the completion handler must be:
 *
 * @code void handler(std::exception_ptr); @endcode
 * Otherwise, the function signature of the completion handler must be:
 * @code void handler(std::exception_ptr, R); @endcode
 *
 * @par Completion Signature
 * @code void(std::exception_ptr, R) @endcode
 * where @c R is the first template argument to the @c awaitable returned by the
 * supplied function object @c F:
 * @code boost::asio::awaitable<R, AwaitableExecutor> F() @endcode
 *
 * @par Example
 * @code
 * boost::asio::awaitable<std::size_t> echo(tcp::socket socket)
 * {
 *   std::size_t bytes_transferred = 0;
 *
 *   try
 *   {
 *     char data[1024];
 *     for (;;)
 *     {
 *       std::size_t n = co_await socket.async_read_some(
 *           boost::asio::buffer(data), boost::asio::use_awaitable);
 *
 *       co_await boost::asio::async_write(socket,
 *           boost::asio::buffer(data, n), boost::asio::use_awaitable);
 *
 *       bytes_transferred += n;
 *     }
 *   }
 *   catch (const std::exception&)
 *   {
 *   }
 *
 *   co_return bytes_transferred;
 * }
 *
 * // ...
 *
 * boost::asio::co_spawn(my_executor,
 *   [socket = std::move(my_tcp_socket)]() mutable
 *     -> boost::asio::awaitable<void>
 *   {
 *     try
 *     {
 *       char data[1024];
 *       for (;;)
 *       {
 *         std::size_t n = co_await socket.async_read_some(
 *             boost::asio::buffer(data), boost::asio::use_awaitable);
 *
 *         co_await boost::asio::async_write(socket,
 *             boost::asio::buffer(data, n), boost::asio::use_awaitable);
 *       }
 *     }
 *     catch (const std::exception& e)
 *     {
 *       std::cerr << "Exception: " << e.what() << "\n";
 *     }
 *   }, boost::asio::detached);
 * @endcode
 *
 * @par Per-Operation Cancellation
 * The new thread of execution is created with a cancellation state that
 * supports @c cancellation_type::terminal values only. To change the
 * cancellation state, call boost::asio::this_coro::reset_cancellation_state.
 */
template <typename Executor, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(const Executor& ex, F&& f,
    CompletionToken&& token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0);

/// Spawn a new coroutined-based thread of execution.
/**
 * @param ctx An execution context that will provide the executor to be used to
 * schedule the new thread of execution.
 *
 * @param f A nullary function object with a return type of the form
 * @c boost::asio::awaitable<R,E> that will be used as the coroutine's entry
 * point.
 *
 * @param token The @ref completion_token that will handle the notification
 * that the thread of execution has completed. If @c R is @c void, the function
 * signature of the completion handler must be:
 *
 * @code void handler(std::exception_ptr); @endcode
 * Otherwise, the function signature of the completion handler must be:
 * @code void handler(std::exception_ptr, R); @endcode
 *
 * @par Completion Signature
 * @code void(std::exception_ptr, R) @endcode
 * where @c R is the first template argument to the @c awaitable returned by the
 * supplied function object @c F:
 * @code boost::asio::awaitable<R, AwaitableExecutor> F() @endcode
 *
 * @par Example
 * @code
 * boost::asio::awaitable<std::size_t> echo(tcp::socket socket)
 * {
 *   std::size_t bytes_transferred = 0;
 *
 *   try
 *   {
 *     char data[1024];
 *     for (;;)
 *     {
 *       std::size_t n = co_await socket.async_read_some(
 *           boost::asio::buffer(data), boost::asio::use_awaitable);
 *
 *       co_await boost::asio::async_write(socket,
 *           boost::asio::buffer(data, n), boost::asio::use_awaitable);
 *
 *       bytes_transferred += n;
 *     }
 *   }
 *   catch (const std::exception&)
 *   {
 *   }
 *
 *   co_return bytes_transferred;
 * }
 *
 * // ...
 *
 * boost::asio::co_spawn(my_io_context,
 *   [socket = std::move(my_tcp_socket)]() mutable
 *     -> boost::asio::awaitable<void>
 *   {
 *     try
 *     {
 *       char data[1024];
 *       for (;;)
 *       {
 *         std::size_t n = co_await socket.async_read_some(
 *             boost::asio::buffer(data), boost::asio::use_awaitable);
 *
 *         co_await boost::asio::async_write(socket,
 *             boost::asio::buffer(data, n), boost::asio::use_awaitable);
 *       }
 *     }
 *     catch (const std::exception& e)
 *     {
 *       std::cerr << "Exception: " << e.what() << "\n";
 *     }
 *   }, boost::asio::detached);
 * @endcode
 *
 * @par Per-Operation Cancellation
 * The new thread of execution is created with a cancellation state that
 * supports @c cancellation_type::terminal values only. To change the
 * cancellation state, call boost::asio::this_coro::reset_cancellation_state.
 */
template <typename ExecutionContext, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename ExecutionContext::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(ExecutionContext& ctx, F&& f,
    CompletionToken&& token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type = 0);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/co_spawn.hpp>

#endif // defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_CO_SPAWN_HPP

/* co_spawn.hpp
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
*/