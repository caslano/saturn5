//
// defer.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/execution/executor.hpp>
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
 *     prefer(
 *       require(ex, execution::blocking.never),
 *       execution::relationship.continuation,
 *       execution::allocator(alloc)),
 *     std::forward<CompletionHandler>(completion_handler)); @endcode
 *
 * @li If <tt>execution::is_executor<Ex>::value</tt> is false, performs
 * @code ex.defer(
 *     std::forward<CompletionHandler>(completion_handler),
 *     alloc); @endcode
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) defer(
    BOOST_ASIO_MOVE_ARG(NullaryToken) token);

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
 *     prefer(
 *       require(ex, execution::blocking.never),
 *       execution::relationship.continuation,
 *       execution::allocator(alloc)),
 *     std::move(f)); @endcode
 *
 * @li If <tt>execution::is_executor<Ex>::value</tt> is false, performs
 * @code ex.defer(std::move(f), alloc); @endcode
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) defer(
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
 * @returns <tt>defer(ctx.get_executor(), forward<NullaryToken>(token))</tt>.
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
        typename ExecutionContext::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) defer(
    ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(NullaryToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type = 0);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/defer.hpp>

#endif // BOOST_ASIO_DEFER_HPP

/* defer.hpp
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
*/