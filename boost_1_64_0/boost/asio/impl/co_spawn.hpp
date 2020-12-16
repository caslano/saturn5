//
// impl/co_spawn.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_CO_SPAWN_HPP
#define BOOST_ASIO_IMPL_CO_SPAWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/use_awaitable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T, typename Executor, typename F, typename Handler>
awaitable<void, Executor> co_spawn_entry_point(
    awaitable<T, Executor>*, Executor ex, F f, Handler handler)
{
  auto spawn_work = make_work_guard(ex);
  auto handler_work = make_work_guard(handler, ex);

  (void) co_await (post)(spawn_work.get_executor(),
      use_awaitable_t<Executor>{});

  bool done = false;
  try
  {
    T t = co_await f();

    done = true;

    (dispatch)(handler_work.get_executor(),
        [handler = std::move(handler), t = std::move(t)]() mutable
        {
          handler(std::exception_ptr(), std::move(t));
        });
  }
  catch (...)
  {
    if (done)
      throw;

    (dispatch)(handler_work.get_executor(),
        [handler = std::move(handler), e = std::current_exception()]() mutable
        {
          handler(e, T());
        });
  }
}

template <typename Executor, typename F, typename Handler>
awaitable<void, Executor> co_spawn_entry_point(
    awaitable<void, Executor>*, Executor ex, F f, Handler handler)
{
  auto spawn_work = make_work_guard(ex);
  auto handler_work = make_work_guard(handler, ex);

  (void) co_await (post)(spawn_work.get_executor(),
      use_awaitable_t<Executor>{});

  std::exception_ptr e = nullptr;
  try
  {
    co_await f();
  }
  catch (...)
  {
    e = std::current_exception();
  }

  (dispatch)(handler_work.get_executor(),
      [handler = std::move(handler), e]() mutable
      {
        handler(e);
      });
}

template <typename Executor>
class initiate_co_spawn
{
public:
  typedef Executor executor_type;

  template <typename OtherExecutor>
  explicit initiate_co_spawn(const OtherExecutor& ex)
    : ex_(ex)
  {
  }

  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return ex_;
  }

  template <typename Handler, typename F>
  void operator()(Handler&& handler, F&& f) const
  {
    typedef typename result_of<F()>::type awaitable_type;

    auto a = (co_spawn_entry_point)(static_cast<awaitable_type*>(nullptr),
        ex_, std::forward<F>(f), std::forward<Handler>(handler));
    awaitable_handler<executor_type, void>(std::move(a), ex_).launch();
  }

private:
  Executor ex_;
};

} // namespace detail

template <typename Executor, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(const Executor& ex, F&& f, CompletionToken&& token,
    typename enable_if<
      is_executor<Executor>::value
    >::type*)
{
  return async_initiate<CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>>(
      detail::initiate_co_spawn<
        typename result_of<F()>::type::executor_type>(ex),
      token, std::forward<F>(f));
}

template <typename ExecutionContext, typename F,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(typename detail::awaitable_signature<
      typename result_of<F()>::type>::type) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken,
    typename detail::awaitable_signature<typename result_of<F()>::type>::type)
co_spawn(ExecutionContext& ctx, F&& f, CompletionToken&& token,
    typename enable_if<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type*)
{
  return (co_spawn)(ctx.get_executor(), std::forward<F>(f),
      std::forward<CompletionToken>(token));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_CO_SPAWN_HPP

/* co_spawn.hpp
Hgzqppk0WyuZU8bn8eJw/3m8D8vfclQjTegQpk2Q/PzNwRcUjpXj8d69eKz2skaqdKDys377jMJt5WQJ8o7H6ruLmIcUnE+k4bghqyX3zTWIU7B1fY/xJ1PaBUZcURaM9tgH6CnW6PMo3W1ID94rl0vpd+McCS/bo/AVC8W1prOVS6H7f+yN9yr2KOcAfMzgceba3VnM+PFokykKfvR447cMAmcA41jdWZyBcCTCN6dAn8UH4c629PD3B83fmwh8Q0BtzHttpj00MdYN6cvncfK8kc4QRMfJ36iRp7mKTBcWl84O9Lk8kqEavvsPZ3EQ7mIpF/lOwcNyxXn4EVb1A2XBelVNj6d86CwvCi+Rzsf/K/Ao7bET9XayD+uaHvGe+AGeWIzJpDsKEP85nmykOePdI91ZuLAtNhJaI0n54YLiiE0CbtO6YxDNB2ro/fNIZ9Qi30/wkM5wx0uqvmiOTVI95zyP2qFGncMCKmGuA/TxuRtFH9e1SX6uea5ehTjvpmCbBFtE1yZc94yLHOx0M7cB8HjvQcxJyisLoa14vcLpsUKus0PP40dYlT9RV349HyyzrD/p3bq6qOZz4Z/EE893bl6Zi7wt6gKmCEv5LCLcZbQTOAsP1xHnkazZN2XeSosXB+uI8fi+vjYIT6PwrdKl4LMaj00dC7meQvh3ShPwfyEe3lvlfNta1v1YkY5vtHjOdh2FL5P8oOmHx2r8m7WJ5/gs03MpvBR16ia5noC629OP5drbneTa3D+a3j+yaWNep+nqkdLyQrT/MH37c95iHUt9pXaTdV9ZPYDPU+XxcCOg4vuT/LCQD14ZWX8bk8Qycj7h3yr3Q95X4/Hiu8VJeFhWkB+3lY3fxpzNSno2eMO+JM+pXqE4t9inlHifMonHokGU50q5L2lPyAXaeAIe0j+Q++rz0f8S6C78J013NjLOauDEJND9kPea7odknN3A6ZZNdzb2Md7rmMg4majH7sBx1p10dwkP9yTESvo9AB5fPVSm9sJPojOFE4jnPXhP2gAe51rW/Woc55QnBXERUnBM24wOkoP39sDTM/uPjXPGb8EuIl5o/am7W6L3CLbTRkIWAU9FBGQkbwvJCH2czJtetntepYT7UQTLA9OmaeSB70Jkeah8hNYAtP6gc6UpfNh5n3S1I9t5KQ6HzBPfnS6mvHCnD+uLm7cp4UedI3HKaRLRQws8qsRd5PwQJ25NwTmk9zsulZw4T9TPc+pbtirpz4RHSJVht4S1c7B/Ev5I7EX71dO7PGIv7hYK99GUo6ZG1V0VSF9L6fvCIqQezgHOhXIixavvexrv2yMNwbrrRWdfTR5sr+a6uJDK7hPlvetxJbxBTuR+kk/pvcKSJJejn+M2+V3neGADV5RrF97zYLii07ZLEsc9h7in9GtErutEqqtksf6QKH8PlakKZVpE4SPOB6Xjjr84z5eaquNEruM59N5j4Z1xSuKdyH03tFYS5any+QTVx1fSy1J5mEfajsfQ98W6vpjq9V8R6twa9U4TVXWe+i7JwNXyFHyt7eNvrHcTzd3yO1IE4+FWZarLuzA29qVyXGbi5Vd5uDNbXhs2nuY5uUrfp3zWRoj2YttdBtffJkrvFv453nNMXi//O2ySNNYVIdW7UqVtrkyqR79om914z96wk2F7ZeRPa6Gnif72CL/Iv7iiVrNlnsHtsp/wpru2wBrQXs6WRmIF/ol8tXzIOUe+yBWP8tjV+6Swrq71qJehMX3mQ5KQ1z7Ka3mET9y5W1NWPG/6LDoTluWukXASUZJLoOMfkLc43pBucBbK4a5WjKO+673wB+SV0q+Q65lhadI9YS2lLNcGOVrtUxp9+Dzaie4=
*/