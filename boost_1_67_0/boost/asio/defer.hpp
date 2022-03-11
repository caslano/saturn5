//
// defer.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DEFER_HPP
#define BOOST_ASIO_DEFER_HPP

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
 * from the current thread prior to returning from <tt>defer()</tt>.
 *
 * The use of @c defer(), rather than @ref post(), indicates the caller's
 * preference that the executor defer the queueing of the function object. This
 * may allow the executor to optimise queueing for cases when the function
 * object represents a continuation of the current call context.
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
 * @li Performs <tt>ex.defer(std::move(handler), alloc)</tt>.
 *
 * @li Returns <tt>result.get()</tt>.
 */
template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) defer(
    BOOST_ASIO_MOVE_ARG(CompletionToken) token);

/// Submits a completion token or function object for execution.
/**
 * This function submits an object for execution using the specified executor.
 * The function object is queued for execution, and is never called from the
 * current thread prior to returning from <tt>defer()</tt>.
 *
 * The use of @c defer(), rather than @ref post(), indicates the caller's
 * preference that the executor defer the queueing of the function object. This
 * may allow the executor to optimise queueing for cases when the function
 * object represents a continuation of the current call context.
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
 * @li Performs <tt>Executor(ex).defer(std::move(f), alloc)</tt>.
 *
 * @li Returns <tt>result.get()</tt>.
 */
template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) defer(
    const Executor& ex,
    BOOST_ASIO_MOVE_ARG(CompletionToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename enable_if<is_executor<Executor>::value>::type* = 0);

/// Submits a completion token or function object for execution.
/**
 * @returns <tt>defer(ctx.get_executor(), forward<CompletionToken>(token))</tt>.
 */
template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
        typename ExecutionContext::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) defer(
    ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(CompletionToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type* = 0);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/defer.hpp>

#endif // BOOST_ASIO_DEFER_HPP

/* defer.hpp
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
*/