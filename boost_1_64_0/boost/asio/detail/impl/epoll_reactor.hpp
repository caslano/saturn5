//
// detail/impl/epoll_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_EPOLL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_IMPL_EPOLL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined(BOOST_ASIO_HAS_EPOLL)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void epoll_reactor::add_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

template <typename Time_Traits>
void epoll_reactor::remove_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void epoll_reactor::schedule_timer(timer_queue<Time_Traits>& queue,
    const typename Time_Traits::time_type& time,
    typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op)
{
  mutex::scoped_lock lock(mutex_);

  if (shutdown_)
  {
    scheduler_.post_immediate_completion(op, false);
    return;
  }

  bool earliest = queue.enqueue_timer(time, timer, op);
  scheduler_.work_started();
  if (earliest)
    update_timeout();
}

template <typename Time_Traits>
std::size_t epoll_reactor::cancel_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& timer,
    std::size_t max_cancelled)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  std::size_t n = queue.cancel_timer(timer, ops, max_cancelled);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
  return n;
}

template <typename Time_Traits>
void epoll_reactor::move_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& target,
    typename timer_queue<Time_Traits>::per_timer_data& source)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  queue.cancel_timer(target, ops);
  queue.move_timer(target, source);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_EPOLL)

#endif // BOOST_ASIO_DETAIL_IMPL_EPOLL_REACTOR_HPP

/* epoll_reactor.hpp
3iIstqagH0Jh9Ghq0YO5zqZweeXKcPA+p8U7yIzrb0n488L/e9lH4Qa29+Z/SPzdlp7I6368bcwNl69ft3Zrq/3Vk8JTYdZNbrvY2vNgbNP54tQE7Kn6zRPJK9dI2+X3avdwr7+g6kgZXWz5C5o7+5LZl81YKC6DFtu8gSXuD8xK89YR3jR7RxS7xDdNj6/M13zOKCBrfG0dyfD1tQXP6fvaIk2Pry3SCfS1VZHj1XFbIXcN0hFPW8H6WXIZEp/s9eNH/On72jK62dpLssuPn9pxZcPbq9eNF/KM89Wr1WfkExkenZA5fT9u3E/z7PJ/5ZO/m8hfhX/+1LdgYB6Ri+r/ivjT93/1REZs/1eWXtWjvHq9OpbngdHL+QmO3VfrobFevWrOoOy5n2/ZLxntzeNheOuC8iilH5zHuhhlX3cGZX9obOyyt9p8Tq5XrxWRObfRy7nVh3XeoLNUKpOh7/KefmzizbtyAjqRnkcn0tB+7ByDG310em4i476/TpUbyzeu31DVel7tWa+vOJXNsM0F4s879/P1/7tljDefqwpDMPvm05yNvKPlWc6xY042mzyKnCOPl8dRvtZ6Pfckj3pPVz4zx/qXZ5Z/PumdgeWIzOn3zaByPDbWvw0X+eZPHkeBbRiZ4DYs8af/LEqoDY/z6nQ9OlX46iRr2xxtKJeHdYBuKpsR2IYW2HjMvk8C7fwF93tEjHYVzvPqeByhmgAd6aSButW48v2F06wX+5hfku/N3y9og3X++dMRP7DtIxdjzF90+mP+s3H4mxR70cln30b64/Ld54+eKXvt7rUDjr59e13xC9n3vx78vembwl//ytLBd1bc0/VD3Q4kZZzY+1DQd6iJ2/r2/241yKZ6kC3uIJvebWdrfXfL969/fGrkg8NGfOr3v9y54I5nH1+VuE11/+9rg75zDbI5H2SDPcjmfNB3xkHfJQfZlk/c1rr/977Rbafvg/jJWYkKcC/EHor4EFgcGX/N37JHKjxfhdLN37JmJzwv8fdT5m9Z7zN/c27c/D3Y9neh7e8C29955m/Z9zF5G2/723wXXNz6nexOl73aHGOfWL95ATv78C2wfxccx/0KoLDyjRU+pz3eR+CL4A/AvmADOBJ8VOUroHqVX6fyXcAlKv8t+IaD94HTwG+Ds8AHwLngd8AF4HfBReCD4GK157wU/J5JR78XAD/uk85E+HqpfdYs8CIwT+2zzlZ7rAvBIvBStce6TO22vl/Dxu6tppPlU265hg+aE1y+o5SvCCpVvm3K1xGcoHyL4RsELgEvBC8HV4Bl4Cpwqd6nFGqe46ync8Bivc9C+Lqr3djzwEu0HErBoRoeAS7S+is1dpyhubb25LIb+aTW/1PgOeBPQNO+5ga3wyE2vtK5sctJ7EkrX4ZPPuo0H3eBfcCvGjniouT/cZV7QvP/Y5UrgepVbrTKdQKnqFyxludsLc8ScDA4R8tzrrbrEls/atb7DfTpR3l6v3xtpxeAfTVs2lNJcLsbbi/PkuDyHGrja3SME8Hf59fEcb+d1hlAPc9IWMp+Oxj5fU7trn4ezADr1N7pt8BSsF7t+d4PrgcfAG8AvwtuB7+n9nEfAX8MPgo+Bz4GHgZ/AjaBT4Mhyw4t2Ah213Cahs8Hfw4OB58Bx4DPgoXgL0D6gtznPeAvwfXgS2AN+Gvwg+AJ8BPgb9Q+7svgHvBV8BvgG+C3le8R8A/g0+Br4PPgn8CXwT+DfwKbwTfBv4CdKL/XwX7gG+AgMHKfkeBesBT8Gvgu8G7wPeA94Crw6+Bmldumcjo+6Nkxxjyf8SEfvnPB8WA6OAHMAieCw8ApWl8Xqn3mIr1vLVSv7eMJve+54C0=
*/