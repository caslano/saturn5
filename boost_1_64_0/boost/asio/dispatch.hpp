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
uRre13Z7kCsL8Xrs9iBXro73g90e5Mo18LyBZnuQKyfgxY2XSLg84kS8hPEKyZWT8HKNV0KuXBMvz3jl5Mq18IYbr4pcWYSXb7xacuVkvHHGayBXTsErNF4LuXIq3kTjdZArp+EV2e1Brlwbb5rdHtkuj7gOXrHxisiV0/HWNV4ZubIYr8SuZ3LlDLyNjFdHrpyJV2q8RnLlLLwt7XomV66LV2a8dnLleng7GK+LXDkbr9x4Xo7LI87Bm2u8fHJlCV6F7ffkyvXx9rb9nly5AV6l3R7kyg3x5tl+T67cCK/K9nty5cZ4C4zXTK7cBK/aeG3kyk3xjjJeJ7myFK/Gbo8BLo+4Gd4iuz3IlZvj1RqvmFy5Bd6pdnuQK7fEq7Pbg1y5Fd7ZdnuQK7fGq7fbg1y5jZ7/2e1BrizT8z+7PciV2+r5n90e5Mrt9PzPeD3kyu31/M94ebkuj7iDnv/Z8YpcuaOe/xmvlFy5k57/Ga+SXLmznv8Zr4ZcWa7nf3Z7kCt30fM/O16RK3fV8z87XpErd9PzPztekSvn6vmf8byBLo+Y1PM/u3+QK3fX8z87XpEr99DzP7ueyZUVev5n+z15A/yFnv/Z/kzeCvfU8z/bT8mVe+n5n+2n5Mq99fzPHlcHuTziL/X8z64/8iL4Kz3/s8dVcuU+ev5n11+YR9TzP9tPyZX76vmf8erJlfvheYPMeSe5cn+8uPHayJXzQk/Wk9ke5MoD8HKN10OuPBAvz3h5g10ecT7ecOMVkyur8PKNV06uPAhvnPGqyJUH4xUar5ZceQjeROM1kisX4BUZr5m8DR6KN8143eTKw/CKjZfI43wcHo63rvFKyJXV4mW4+3b9kSuPwNvYeJXkyiPxNjdeDblyId42xmsgVx6Ft4Ndf+TKo/F2sf2ZXHkM3u62P5P3wGNj4TzcXrafDmE9wxq8fe16Ji+Hx+HNt/2PvBYej3eo7VfkLfAEvIXG6yBXLqIfHGf7FbnyRLwTbb8a6vKIv8Y72XhF5MqT8E6z64VcWYv3G9v/yJUn451jvGpy5WK27/nGqyNvgKfEws8LXGLHSXLlqTE+l2G8J8iXw9NiXr8/HeTd8PQ0XmIY4xo8QzzHG83jVpBXwzrxctzzNV49eQP8Dd6ddv8g74Bnpnl+XeQ98Kx0r2M45xvw7DReEXkJPCeNV0ZeAc9N41WR18Dz0nh15A2wPo3XRN4Cz0/jtZF3wAvSrT/yHnhhuvU3guMgvEi8wJ13mu1WSK68GO9Re7wkV14S4/8/t/sleRm8lP3jGbu/kdfBBrwX7ThO3gwvw3vdeK3kHfByXse79jxC18vIkFewvBV2vZAXwyvZf1fa8YW8Ev4W7xt73Cevh1fh/WSPR+St8Gq8rMGrem+Rr4CNeHnGW0n+NbwGb7TxfiCPjwp5Ld4axsslHw5/hzfVeIXkyusYh9Y1Xim58nq223rGKydX3hDj31E3XgW58kaWt4HxqsiVTfSDjY1XT668ide7lfEayZU34+1kvGZy5S14exivlVy5hOdXabx2cuWteFXG6yRX3oZXbbxucuXteDXG8/JdHrEZr9Z4eeTKO/DqbH8hV96JV2+8YnLlXXgNtl+RK+/Ga7T9ilx5D16T8SrJlffiNRuvmlx5H16L8WrJlS14rbb/kSvvx2uz/Y9c+QBeu+1/5MoH8Tps/yNXPoTXafsfufJhvC7b/8iVj+B12/5HrnwUr8f2v9Euj9jK+ZqXZ/ofufKxXk/KeIXkyqV4OcYrJlc+jjfYeKXkyifwhhuvnFz5JN5o41WSK5/CG2+8anLl03gTjFdLrmzDKzJePbnyGby1jddIrnwWb6bxmsmVy/DmGK8=
*/