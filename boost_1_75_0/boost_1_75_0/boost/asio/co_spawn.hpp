//
// co_spawn.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_CO_SPAWN_HPP
#define BOOST_ASIO_CO_SPAWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/awaitable.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct awaitable_signature;

template <typename T, typename Executor>
struct awaitable_signature<awaitable<T, Executor>>
{
  typedef void type(std::exception_ptr, T);
};

template <typename Executor>
struct awaitable_signature<awaitable<void, Executor>>
{
  typedef void type(std::exception_ptr);
};

} // namespace detail

/// Spawn a new thread of execution.
/**
 * The entry point function object @c f must have the signature:
 *
 * @code awaitable<void, E> f(); @endcode
 *
 * where @c E is convertible from @c Executor.
 */
template <typename Executor, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(const Executor& ex, F&& f,
    CompletionToken&& token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename enable_if<
      is_executor<Executor>::value
    >::type* = 0);

/// Spawn a new thread of execution.
/**
 * The entry point function object @c f must have the signature:
 *
 * @code awaitable<void, E> f(); @endcode
 *
 * where @c E is convertible from @c ExecutionContext::executor_type.
 */
template <typename ExecutionContext, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename ExecutionContext::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(ExecutionContext& ctx, F&& f,
    CompletionToken&& token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename ExecutionContext::executor_type),
    typename enable_if<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type* = 0);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/co_spawn.hpp>

#endif // defined(BOOST_ASIO_HAS_CO_AWAIT) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_CO_SPAWN_HPP

/* co_spawn.hpp
tpPKUhZneFeifXJ44PDg0fN7xXmQ2Ph3lMqgKdHUFKClEy5bQQg52WlBdGZYjI/tNhcjog/bREqNUuo7Tg2Vz7p1Ty+F8+jWVFldJGJ+ZLNuvwy/+Zl4cvxHBby2ER2zT+o7CG25l43XxpriLoZU6GZ1Z5yH9B1NUDRdMKAP6bOG0UEX5vgfCfmP/Zj8UTH8VHAiKziDgMgyn06vZUvz5E4QC1D73qPIgXvslsA9DkSMuu2+kNcuhfER+C+Kje3C0ij2gk3fjv01gcdQiNK3nxpafuG9o2/tjuh7p77gwsU/TDo2vVO91m/nxkjobGdZ4zEFD1wylrJ1RH0IbdIWyEG781gQ/W21xRIrsGmLZSSBbD/xtHtNOURwlaX6O1hLqZG0FGpJfLOTeYBmx7g66+wUfM/mLRXNCiaIcF2xDO0y7EMBJ8UZtegxOqOk4a7dDtJBsk+UMvhiKCXOFn+U1wtngQCEFXAZCIxiAmfYLncxdweXgAw/ZiTdjw1o+TBWjHiLAuCGI4KmdXe45dNH4Uj1vEgQshEgAt3BCcPAYuMaI8Fixz6Fer511eu+qxR927/ubiUEbgJ9On036TVjgJ/A093VrkzEq1f+CTw33lBg2Ir9cfyRuXCOHmpD0v/1j+GQz8gMaxIxBDX/xZPDfOBTd+FAfTg8tqRylRiw7mNmDFgCWuGlUCnqVpVrG5qfojyT2ZvYBr8VqVIZ
*/