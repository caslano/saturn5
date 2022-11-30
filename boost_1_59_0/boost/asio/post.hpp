//
// post.hpp
// ~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/execution/executor.hpp>
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
 *       execution::relationship.fork,
 *       execution::allocator(alloc)),
 *     std::forward<CompletionHandler>(completion_handler)); @endcode
 *
 * @li If <tt>execution::is_executor<Ex>::value</tt> is false, performs
 * @code ex.post(
 *     std::forward<CompletionHandler>(completion_handler),
 *     alloc); @endcode
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) post(
    BOOST_ASIO_MOVE_ARG(NullaryToken) token);

/// Submits a completion token or function object for execution.
/**
 * This function submits an object for execution using the specified executor.
 * The function object is queued for execution, and is never called from the
 * current thread prior to returning from <tt>post()</tt>.
 *
 * The use of @c post(), rather than @ref defer(), indicates the caller's
 * preference that the function object be eagerly queued for execution.
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
 *       execution::relationship.fork,
 *       execution::allocator(alloc)),
 *     std::move(f)); @endcode
 *
 * @li If <tt>execution::is_executor<Ex>::value</tt> is false, performs
 * @code ex.post(std::move(f), alloc); @endcode
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) post(
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
 * @returns <tt>post(ctx.get_executor(), forward<NullaryToken>(token))</tt>.
 *
 * @par Completion Signature
 * @code void() @endcode
 */
template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) NullaryToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
        typename ExecutionContext::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(NullaryToken, void()) post(
    ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(NullaryToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type = 0);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/post.hpp>

#endif // BOOST_ASIO_POST_HPP

/* post.hpp
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
*/