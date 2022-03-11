//
// post.hpp
// ~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POST_HPP
#define BOOST_ASIO_POST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Submits a completion token or function object for execution.
/**
 * This function submits an object for execution using the object's associated
 * executor. The function object is queued for execution, and is never called
 * from the current thread prior to returning from <tt>post()</tt>.
 *
 * The use of @c post(), rather than @ref defer(), indicates the caller's
 * preference that the function object be eagerly queued for execution.
 *
 * This function has the following effects:
 *
 * @li Constructs a function object handler of type @c Handler, initialized
 * with <tt>handler(forward<CompletionToken>(token))</tt>.
 *
 * @li Constructs an object @c result of type <tt>async_result<Handler></tt>,
 * initializing the object as <tt>result(handler)</tt>.
 *
 * @li Obtains the handler's associated executor object @c ex by performing
 * <tt>get_associated_executor(handler)</tt>.
 *
 * @li Obtains the handler's associated allocator object @c alloc by performing
 * <tt>get_associated_allocator(handler)</tt>.
 *
 * @li Performs <tt>ex.post(std::move(handler), alloc)</tt>.
 *
 * @li Returns <tt>result.get()</tt>.
 */
template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    BOOST_ASIO_MOVE_ARG(CompletionToken) token);

/// Submits a completion token or function object for execution.
/**
 * This function submits an object for execution using the specified executor.
 * The function object is queued for execution, and is never called from the
 * current thread prior to returning from <tt>post()</tt>.
 *
 * The use of @c post(), rather than @ref defer(), indicates the caller's
 * preference that the function object be eagerly queued for execution.
 *
 * This function has the following effects:
 *
 * @li Constructs a function object handler of type @c Handler, initialized
 * with <tt>handler(forward<CompletionToken>(token))</tt>.
 *
 * @li Constructs an object @c result of type <tt>async_result<Handler></tt>,
 * initializing the object as <tt>result(handler)</tt>.
 *
 * @li Obtains the handler's associated executor object @c ex1 by performing
 * <tt>get_associated_executor(handler)</tt>.
 *
 * @li Creates a work object @c w by performing <tt>make_work(ex1)</tt>.
 *
 * @li Obtains the handler's associated allocator object @c alloc by performing
 * <tt>get_associated_allocator(handler)</tt>.
 *
 * @li Constructs a function object @c f with a function call operator that
 * performs <tt>ex1.dispatch(std::move(handler), alloc)</tt> followed by
 * <tt>w.reset()</tt>.
 *
 * @li Performs <tt>Executor(ex).post(std::move(f), alloc)</tt>.
 *
 * @li Returns <tt>result.get()</tt>.
 */
template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    const Executor& ex,
    BOOST_ASIO_MOVE_ARG(CompletionToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename enable_if<is_executor<Executor>::value>::type* = 0);

/// Submits a completion token or function object for execution.
/**
 * @returns <tt>post(ctx.get_executor(), forward<CompletionToken>(token))</tt>.
 */
template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
        typename ExecutionContext::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(CompletionToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type* = 0);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/post.hpp>

#endif // BOOST_ASIO_POST_HPP

/* post.hpp
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
*/