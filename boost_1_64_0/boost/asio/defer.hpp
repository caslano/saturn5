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
bw/jFT7q8ojP4e1nvApy5fN4hxqvnlz5Al6N8VrJle14p9jXQa58Ee9c+zpaXR7xJbzL7OsgV76Md519HeTKV/But6+DXPl7vAfs6yBXvor3pPGKHnN5xNfw2u3rIFd24L1pvEZy5et4Hxqvg1z5Bt4Xdj0vdXnEN/F+MF45ufItvKzAPD9y5dt4Q43XSa58B6/AeHmPuzziH/CKjFdOruzEm2W8OnLlu3ibGK+FXPke3rbG6yZXvo8313jFT7g84gq8fYxXTa78AO9gu57JlR/iHW28DnLlR3i1xst/0uURu/DOMl4FufJjvEuMV0+u/ATvGuO1kSs/xVtivMRTLo+4Eu8+45WSKz/T+RfbD8iVn+M9Z7xmcuUf8TrseiZXduO9bzzvaZdH/ALvc+MVkSu/xPvO9nty5Vd48bi5viRXfo032HhN5Mpv8MYYr5jrD+W3eJOM18FylH/CK8aLOoLLI/bgbWi8InLld3hbG6+CXPk93i7GqydX/hlvb+O1kSt/wJtvX8czLo/4I96RxishV/6Ed6LxqsiVP+PVGa+BXOn5oXehfR3kr0Cff2PnKuN1kitjfng9c4PxfiBXBni3Gm/4sy6PGMe72/YrcmUG3oPG24FcmYm31K4/cmUW3jPGW0SuTOC1G+8icmU23mvGW0KuzMF7x3hPkCsH4H1gtwe5MhdvpfF6yJUD2b5f2f1omcsjDsL7s92PyJWD8YIMM56SK/PwBhivhVw5BG+Y8TrIlUPxxhqvh1w5DG+C8YqWuzzicLypxqsgV47Am2W8GnLlSLwNjddErhyFt4XxusmV+XjbG6/kOZdHHI23m/GqyJVj8PYyXv1n7n7EsXj7G6+RXDkO7xC7fcnbYAHeQuN1kivH451g1wu5cjW8U4yX+Nzdj1iId5bx8smVq+NdaPsLuXINvCuMV0qunID3O+NVkisn4t1ivFpy5SS8u+x2I2+Ca+I9aLxW8na4Ft7jdnuQd+vrxltmPO+PrGc4Ge9l4+WRK6fgvWnXM7lyKt77xisjV07D+9T2e3Ll2jr+2fGKXLmOjn92/yVXTscLMs16JlcW4w0wXie5cgbeMON53dyHM/HGGq+QXDlLxz/jlZIr19Xxz3iV5Mr1dPwzXg25craOf8ZrIFfO0fHPeC3kyhId/4zXQa5cX8c/43WRKzfQ8c94PeTKDf1wXm9/4+V94e5H3AhvgfGKyZUb4x1tvApy5SZ4vzZeLblyU7wzjNdIrizFq7f9lFy5Gd5ltp+SKzfHu9auP3LlFjquGS/xpbsfcUsd12x/JldupeOa7c/kyq11XDNeOblyGx3XjFdFrizTcc14deTKbXVcM14TuXI7Hdfs9iBXbq/jmt0e5ModdFyz24NcuaOOa8bL/8rdj7iTjmtZ5nyDXLmzjmvGKw/ziDquGa+KXLmLjmvGqyNX7qrjmvEayZW76bhmvGZy5Vwd14zXTq5M6rhmvC5y5e46rhnP+5r7cA8d14yXT66s0HHNbg9y5S90XDNeBblyT7z9jVdLrtxLz+uM10Cu3BtvoV3P5Mpf6nld1th/6vNDbSxHuY+e/5nldZArK/X8zz7uN9yH++r5n/EKyZX76fmf8UrJlfvr+Z/xKsmV83SctNuDXHmAjpPGqydXHqjjpN0/yJXzdZw0Xiu5skrHSbt/kCsP0nHS7h/kyoN1nLTb41v6PTxEx0njFZOXwgU6TtpxiLwKHspx6yu7nsnr4GF4P9h+T94ID8fLSJh+T94Gq/EGGa+LvAcegTfKeIk/sV7gkXiFxismL4ML8SYbr4q8Fh6FN9N4K27Pl/sRj8bb0Hh5N7o84jF4Wxqvkcdrhsfi7Wi8lstHyf0=
*/