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
9wuv9ze9N+73vUEQdzcZvXf93vvhbaz3137vbUy2sy81XmoNqQlScakMqdtO4No2R0f8zPmMusNjMW25S+fsZJzDMEddfxB3PSgXqONpxnRpA7SRq42B2hjEiBvztRHThg7qcjY69eT4/Knzp+pxJVCmfhHTRhjJWoIxqL+PwwyYCbNgAmbDHDgA5sKBcBAcDPPgEDgUDoPD5aV4me4my92MczcF7ibb3STczXh3s5q7KXQ3q7ubHHezhruZ4G7i7ibD3Yx0N6Pcje9uYu5msLvJdzej3c0YdzPW3QTuJs/dDHE3E93NJHezprtZS1awdBy5CdxN3N1kuJtMd5PlbhLuJtvd5LibAe4mV6ZgvGTB6smC2VNOSZx9+fZy/PdjUTNINWXB187ICGSuCo6Ak6Hm+XAaDOAoODVZkJ0sGJcsKJhyypizL98yvJVHChmHmSE5p5IJPCh9IpzwSU0B0WPjnGoW97kuzo6aY/XsIEMbo7WxdniuEgsRAB/qr/m9XurF9HIrAbNhDhwQLl4WpI1Y0QuZgTdnymmy98uN/IVrBb23cXfLb3J6b4f13g7vvR3Rezuy93ZU7+1+vbf7994O8kN4vRgPwl+u5oXgXixEECIeIiNEZoisXhR6IWIhghDhHxSGf7C6HyIWIlQmeCH8ELEQYTbRC+GHrwzEQgQh4r0rxs/0Q2YEkN8HAeR+InWCGUsWrMM1gwx1Mpk0OBnPS8aHJuPDkvHhyfiIZHxkMj4qGc9Pxkcn42OS8bHJ+LhkvCAZH5+Mr5aMFybjqyfjayTjE5Lxicn4pGR8zWR8rWS8KBmfnowXJ+MzkvGZyfisZHzdZHy9ZHx2qm8F2dqTMrWRpY2ENsbQiDriOG2so43p2ihO7XZBLGoGUTMuk5eeDsMJbegRIDz73iSc+4zJvpNqxLQRaCOujQxtZGojSxsJbWRrI0cbA7SRq42B2hikz0ZGx4y808s27R3g/AFe763fexv+JlAhcHcHeb23fu9trPc2nEt99bhYPJZqRb+Lp1oZ9IaNYr4fNWNRUwejTJgFs2EOHAPHwgI4Hq4Dp8MZcGbvQ72xTXyA9M8sv/cmvAURY44RlEFIRQxyPw58SJwRIhP4MEy59UFM6dGIEiKQAXzY+8yDk4Nezuu9cc9q3uHuppozCq7bgyFwKBwGR8CRcBTUvxsNxzjGgvA23guZuzngsKkHHN67is/ZIDfm56WasT5zqMOi5qioOc6Tn2mF42p9YQVM93MReSt0lSlV/uOYVf4usXqYF8GYF74nv7vxqskXwcD9rdQvjdc+M7xfc/yoXsbxDjDedSynCWbgHWq8VpdDfQ3ZUkcbr5PcWyNkFt6vjVdMXg4TeGcYr5a8EWZT9fb1knfDHLzLjFc0IczL4AC2ybXGqyFX5rJNfme8RvJWOJBtcr1dL+Q9cBBek31+E1kvcDDeLcarJK+CeXi32fVH3gSH4N1hvLfIe+BQvLvt6y0M75dNCr1h9K37jFdFrhzONn7QPj9y5Qi22+PGayJXjsRbbrwOcuUovN/b/W1Nl0fMx3vHeGXkytF4H9n+Qq4cg9dt9zdy5VjWy3d2fyNX6mdt/J9W9br0dawVsoB9OMd4ZeR1cDzeYOM1TA/vd+OthjfceO14RUWhV4g32nhecXi/Cm91r/+fSrxGvDXYN8eb5bWQd8IJXv8/PeT5k0NO9Pr/aeBxy/AmsT0mm8etJm+Aa3r9/7SSd8G1+rUkPztcft45rEev/58S8gVwMut5ht1u5O1wCt5s4+WfG94vh1O9/n+a2b6teNNYLxva7XteeL8Urs3jbmG8OvJ2uI7X/8/wepdHnM7jltn+TK4sZv8ot48=
*/