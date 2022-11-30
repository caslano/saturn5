//
// dispatch.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/execution/executor.hpp>
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
 * @param token The @ref completion_token that will be used to produce a
 * completion handler. The function signature of the completion handler must be:
 * @code void handler(); @endcode
 *
 * @returns This function returns <tt>async_initiate<NullaryToken,
 * void()>(Init{}, token)</tt>, where @c Init is a function object type defined
 * as:
 *
 * @code class Init
 * {
 * public:
 *   template <typename CompletionHandler>
 *     void operator()(CompletionHandler&& completion_handler) const;
 * }; @endcode
 *
 * The function call operator of @c Init:
 *
 * @li Obtains the handler's associated executor object @c ex of type @c Ex by
 * performing @code auto ex = get_associated_executor(handler); @endcode
 *
 * @li Obtains the handler's associated allocator object @c alloc by performing
 * @code auto alloc = get_associated_allocator(handler); @endcode
 *
 * @li If <tt>execution::is_executor<Ex>::value</tt> is true, performs
 * @code execution::execute(
 *     prefer(ex,
 *       execution::blocking.possibly,
 *       execution::allocator(alloc)),
 *     std::forward<CompletionHandler>(completion_handler)); @endcode
 *
 * @li If <tt>execution::is_executor<Ex>::value</tt> is false, performs
 * @code ex.dispatch(
 *     std::forward<CompletionHandler>(completion_handler),
 *     alloc); @endcode
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) dispatch(
    BOOST_ASIO_MOVE_ARG(NullaryToken) token);

/// Submits a completion token or function object for execution.
/**
 * This function submits an object for execution using the specified executor.
 * The function object may be called from the current thread prior to returning
 * from <tt>dispatch()</tt>. Otherwise, it is queued for execution.
 *
 * @param ex The target executor.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler. The function signature of the completion handler must be:
 * @code void handler(); @endcode
 *
 * @returns This function returns <tt>async_initiate<NullaryToken,
 * void()>(Init{ex}, token)</tt>, where @c Init is a function object type
 * defined as:
 *
 * @code class Init
 * {
 * public:
 *   using executor_type = Executor;
 *   explicit Init(const Executor& ex) : ex_(ex) {}
 *   executor_type get_executor() const noexcept { return ex_; }
 *   template <typename CompletionHandler>
 *     void operator()(CompletionHandler&& completion_handler) const;
 * private:
 *   Executor ex_; // exposition only
 * }; @endcode
 *
 * The function call operator of @c Init:
 *
 * @li Obtains the handler's associated executor object @c ex1 of type @c Ex1 by
 * performing @code auto ex1 = get_associated_executor(handler, ex); @endcode
 *
 * @li Obtains the handler's associated allocator object @c alloc by performing
 * @code auto alloc = get_associated_allocator(handler); @endcode
 *
 * @li If <tt>execution::is_executor<Ex1>::value</tt> is true, constructs a
 * function object @c f with a member @c executor_ that is initialised with
 * <tt>prefer(ex1, execution::outstanding_work.tracked)</tt>, a member @c
 * handler_ that is a decay-copy of @c completion_handler, and a function call
 * operator that performs:
 * @code auto a = get_associated_allocator(handler_);
 * execution::execute(
 *     prefer(executor_,
 *       execution::blocking.possibly,
 *       execution::allocator(a)),
 *     std::move(handler_)); @endcode
 *
 * @li If <tt>execution::is_executor<Ex1>::value</tt> is false, constructs a
 * function object @c f with a member @c work_ that is initialised with
 * <tt>make_work_guard(ex1)</tt>, a member @c handler_ that is a decay-copy of
 * @c completion_handler, and a function call operator that performs:
 * @code auto a = get_associated_allocator(handler_);
 * work_.get_executor().dispatch(std::move(handler_), a);
 * work_.reset(); @endcode
 *
 * @li If <tt>execution::is_executor<Ex>::value</tt> is true, performs
 * @code execution::execute(
 *     prefer(ex,
 *       execution::blocking.possibly,
 *       execution::allocator(alloc)),
 *     std::move(f)); @endcode
 *
 * @li If <tt>execution::is_executor<Ex>::value</tt> is false, performs
 * @code ex.dispatch(std::move(f), alloc); @endcode
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) dispatch(
    const Executor& ex,
    BOOST_ASIO_MOVE_ARG(NullaryToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename constraint<
      execution::is_executor<Executor>::value || is_executor<Executor>::value
    >::type = 0);

/// Submits a completion token or function object for execution.
/**
 * @param ctx An execution context, from which the target executor is obtained.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler. The function signature of the completion handler must be:
 * @code void handler(); @endcode
 *
 * @returns <tt>dispatch(ctx.get_executor(),
 * forward<NullaryToken>(token))</tt>.
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
        typename ExecutionContext::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) dispatch(
    ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(NullaryToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type = 0);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/dispatch.hpp>

#endif // BOOST_ASIO_DISPATCH_HPP

/* dispatch.hpp
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
*/