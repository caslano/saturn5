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
kGqda2nkGm9iVDM5iGAeukAC0YSBXE/MPAeD0QWOPN7x5Qg74erlmZN/cJDLoJQJUKossRpIMYOq3v5/EuaKRP3o7VLZ7GeMbBcrWVdIPEoCci1Zx8OtR5BlsC4u72UqPik08sq1X6wf4cLK7kPwfmp62wXka6kuk32NhLEsNCGFWCBa/lkw+kFOq9LQ3jQaZuasHlxMqsD1w/3+N3pUnaoAVQGaATle690qWNuVK4GT6jAoOYxk0dm1CPd4Y9jOIi7AxqqItzy1xdr4u1GxZY+ByIWQ1KUhV24mSBXcAEKVgaBK2A/GamIfb7zmiRXNrbqkCOoGwNv9fWWdgrc6oxwFkrRTk975CMfHBwhX8osepjEvpxF0e7WLkhoBmX6QHPZmtc4eacgNKianjeBboHYjty7rR1sepdG0OIHQSFHb+pb3ZJAyySuQXo6/Oi0mQO9qbvlO6MKEL6p72HMoHoQPRrsuqZcKOShXLREEWRgC77H5JJcDgqDYF4wKVlf6VVhM5vPsTbxQLdcCFu5jfP0balIsN+MpxfyuR8Qqhf7wAiUKPXZ7WnOOkg==
*/