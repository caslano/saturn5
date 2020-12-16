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
89gH2t/0McGrrz7h6jXrh6QRrKm5o6b42bd7EzzooOEHVY85XCX4yy+v/HL2iM8aCH7wwXEfPHzOzX6Cp5/+yelvXvvbHQT79l3cN+ehyd0Jjh375djn3qz7g+Bdd11519CcqdcQfPnlo14ev+XMXQQPPTTv0AVlva8meMkl7S7pcEGbswkWFaUVTZm7rC3BRx759JEtx2qVBL/4YuEXB855YTvBceN2jfv9xfqnCJ555vgzT33yqN8JXn75iZe/9seICQR/+unXn77o8H0Pgo8++v6jN1aFuhE87LDCw5a6+y0kOGjQykGnLSs/luCrr8599Y3Vj+9H8B//ePwfc2e/uohgMHhrcMYL744h+Oyzo54Nfn/FnQTbtOnQptsh7Y4gOH26Y/qFh939LsG8vIPyDi9YcALBM8748IwPrv9jOcE77rj+jl6jihcQHDhwxcBpZ5VWEXz88Tcev79mbgrBp57q89Skj244n6DLdazrpta3fUvw3XdnvHvvwlsjBA88cNCB5f27uAhed13Rdcte7d+KYCBwTyD/qW1HExw69NmhV/xYcQvBaPSl6PmP7vye4D//+ec/Pz7g284EJ03ab1JK7qJCgnfffeHdB/Rz3ErwgguOvGDcVYesItipk7PT8rz0hwh++OHNHx438YPHCHbpUt5lZdGg2whmZ+/Mfmlr9CeCfv+j/tDmre0IHnBA3wMmZ3S0EwyH3wvffs/2Nwk+/PBHD79VelKI4ObNVZtffuSJIwl+9dVlX409ff0bBF98seuLg9859yOCEyd2njhwxjnVBJcunbX0oaczBhG85ZY7byk4uOwrgunpy9OPX+CsJTh7ds3st4euPo/g7t3rd192zFdzCZ53Xu/z8m459GmC3fo8v/P81a2KR9629ceG0JKSOWuuvfjmDqeM6Ln9zacHT/1jRud5oz65YdeUt8s3Dki5f/ncc584PvWHF8bvV7Wjv33h7addse3Xr0+tfK9r/vWbMp7c/55ZZw+z7XP73D73l10hKVJpim6eshKOIjVxvuiBz2kR+GQUijQkq19SPyJzzOyKBjdE5LoWoGeS5k3LHB2oHwy/fCx/kSnkCUedXqFk1dL8RPSW2P/T40XFw6IsFtM3MelGFPrh6DU9t6RwQHaKtV6jNVRxUdLgW316Zn1aoH5ASjw6HVWnQ0AIEaMX6Cr19EHawBd6IM+yMGhBmBRiUoBQpNY3IhQVFzkEhCIq7I6CWZ9DMdVPM1elKKTECzKYgijg8Jt7kfmbe4qCztRYeVQwKg8c3TeYStXCfoIPWk33E354xOoY5c2TukisH7JZRzWml8XpKKqmq7ZCfEjNTvPGxStOacwf3qFSCqSWBKY/NEszaOzFJqSX0duKUn3RCG7lC7v+oG4tdaAR35OZnZmZYvjxOyqmKfUEPRTZaBfjUzlXAgNnUgOzIYtC2iO1FvSfANCBCfsP8qJ25Dxm6k8QG4Fa6BLN2nEpoqL0QcOUjhxU0E0MP11oWfqj2KSIRyd0WSaKJxfM440HsFeKD0QQgI1f4Bo/tKNCim0GHVkjfoByaJy6YWxwxOGr4lyXUxGXYjAyLx9xC+i68rDG+CV1Bc5+opwDtVKp5KiUaYKzAIEkooOIMAUB0cDoqGpmToDHxyAsAaTbA36PRjwGfn0M+bCE0P2ZWeVJ8Jv4xw1c3oL3sI143powxuMuL1uPLPXKYun4YFrAxDLqNDAyOSpGqh85PEODb3mqLyOiwldlTaUQQB2Cqsl60nshv393+kPwWsDeqo+e3+CwWpMwP/gmKu8D5RWUWPyTCgod4KeXx8VixYb3tsw3l3BZEVMuwMs4nhqpDBGNQEBzjfmlHJ8=
*/