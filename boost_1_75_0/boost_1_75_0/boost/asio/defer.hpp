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
S8LHl08cX98oN0ScLja/BU/y9/oMo+SKg079iJdDQexNatVIDOyAEPfsVtQVokaM8Kx4VmUoKFU+YSEe5keg+KAbw/KBaP+UUMCoeJO2wypmHU7Pg6xz6+fQl3fN6f4aOzalPtEPe/GNWlppL9OJVDYUBLXBvFU6p3xnaPVkQ2GdjW3KNDa+8biSQrxVB9qHIaTp0jQ7n+mGLQXv1HMX90P6VHVmCMgT622D03j73tBpnMNii0ltY3hzg/PmtARvCxwxxHuBWrIIEiCQP7zXt2MTKHzdxQ5aqPGNxmZcrKv+gdrmSE0zBXGvACoKPRD5lMmhUJcXWynzrMZDm6+DzNdA5uA1IfODi63YRYUCFotRQeMW/luQ6y+zOeijraS/SeM7ju2f3gZC1OTL4gGl5BpG6KX6NXsPsTC3hLbe9PdNcNNvhnEoZsAUnOrCckGtdnqXbjumjkCiJc05GUwEHlrfjhnY+5hDxAzBO3VaFsuHJl1MOUz9IZwJcwr41adeZPYCzzeSHYZGdN1BO3uVWONiEZO2w3izNkyZnD2C8dqBarhUXLLXAOMwMtAqAU2HxA4fL7LiiY73IKeEmlnfIY6A4+ygnjOACC7TDyoT2EOQRfeIGG7dlJdMBP6q7+geSn7BTJ7MHrJh8gvh5HZKzY03xWEdxX9/Iwj77zbT+Xmf/ubbRNH4uy/BjDyGTxsPqZLzZPAaNsH1vjoi
*/