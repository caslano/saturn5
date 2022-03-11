//
// dispatch.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DISPATCH_HPP
#define BOOST_ASIO_DISPATCH_HPP

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
 * executor. The function object may be called from the current thread prior to
 * returning from <tt>dispatch()</tt>. Otherwise, it is queued for execution.
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
 * @li Performs <tt>ex.dispatch(std::move(handler), alloc)</tt>.
 *
 * @li Returns <tt>result.get()</tt>.
 */
template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    BOOST_ASIO_MOVE_ARG(CompletionToken) token);

/// Submits a completion token or function object for execution.
/**
 * This function submits an object for execution using the specified executor.
 * The function object may be called from the current thread prior to returning
 * from <tt>dispatch()</tt>. Otherwise, it is queued for execution.
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
 * @li Performs <tt>Executor(ex).dispatch(std::move(f), alloc)</tt>.
 *
 * @li Returns <tt>result.get()</tt>.
 */
template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    const Executor& ex,
    BOOST_ASIO_MOVE_ARG(CompletionToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename enable_if<is_executor<Executor>::value>::type* = 0);

/// Submits a completion token or function object for execution.
/**
 * @returns <tt>dispatch(ctx.get_executor(),
 * forward<CompletionToken>(token))</tt>.
 */
template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
        typename ExecutionContext::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(CompletionToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type* = 0);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/dispatch.hpp>

#endif // BOOST_ASIO_DISPATCH_HPP

/* dispatch.hpp
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
*/