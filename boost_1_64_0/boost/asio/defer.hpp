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
qHt6PvMHq0KkE8LDHS3i+UCpXCFT1cpZMKNaYoZLl3AnOpO7qT9TLbYDioLATe9l6P5gnlpzTvcF9YfrD5FPLV9wT3bnJTRDfKlJRGaD3ZYTyn/WxsjZFydYL2yIpLpr38rllizLZakZDAaE6ooF/NFRsAGliI1+qKU3sK22l8x/P82DMNYsqjgqSMa5nV7J7ZH6VHOU9kdIzdSKqmMZFZoPwklU9PkfWaxvuTxnXx2T6EokWM6BEUIeiCHbr2mIgRDuA7tK+XB4UG5NAn5teg3HisUr5DzEBV5JHyewXa8iJQhyHSBPESUUN+GwPuV8RRo9coctyFDMAPS9seqfDWjoJVKTmddpf3UfsIB6Poe7khLfEjrMXSnZdWxfMpz7U0rMLpC0r4yW/ZT587K3prQfv6rjLKsG1xh22m82nROVHkHAscbe8GYplxnWu2d7p+tIH3EWGraGLDzt/ENee1zxDpgDQd6nLGA/jAXBnhvZLFLAKBQt842Eh29cu7SI+s3htfKstPimSFdkytGXNOd0MIdDiPW4QY8FtQ3KRxL3fUZpM+N5qd19oA==
*/