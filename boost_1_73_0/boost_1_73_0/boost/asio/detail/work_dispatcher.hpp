//
// detail/work_dispatcher.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP
#define BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/executor_work_guard.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler>
class work_dispatcher
{
public:
  template <typename CompletionHandler>
  explicit work_dispatcher(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    : work_((get_associated_executor)(handler)),
      handler_(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  work_dispatcher(const work_dispatcher& other)
    : work_(other.work_),
      handler_(other.handler_)
  {
  }

  work_dispatcher(work_dispatcher&& other)
    : work_(BOOST_ASIO_MOVE_CAST(executor_work_guard<
        typename associated_executor<Handler>::type>)(other.work_)),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    typename associated_allocator<Handler>::type alloc(
        (get_associated_allocator)(handler_));
    work_.get_executor().dispatch(
        BOOST_ASIO_MOVE_CAST(Handler)(handler_), alloc);
    work_.reset();
  }

private:
  executor_work_guard<typename associated_executor<Handler>::type> work_;
  Handler handler_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP

/* work_dispatcher.hpp
ccKTQLsebhcjoOSmUFVSOOamEimLEfEpPZ0q4nxaorQ3VsLjBYpawbWto+A7rKN2nRAJSGcpR2xpWt5xgwbaC9l0sPLlB79rjKJtaSWQpv3qVZ05VPQkN+wkDWRplRBsu7zakgRfctWKrjgSbtdS03BwAqO2kGgbhPcGnQcykmMPKUJovYIgGtyZtPtkO7zBKSPfp7ibcpRrJxJm40Jr+bJKBi1bVv+Yoyri/6ybrnIc3tctOk69m6R9etFRNN7hVCznenlGR6NUXIjbgGoiVzT4YckR1YQyDI3/sP6xJkwXdEYaGqOG/saYpWsoNRPKqYie0q4MvOp/MQxqvwIxQzFo99R2yBq8iVQmkqu1Ctta6+mu1kSo7UXO8PmedmUb+8SWlXxuQUNa07AWG9CVfeT3tpHf3kWqmn7BfJL5KR3gNzeAubbrO7uurMn5vh6nrlWpK9jrat+0Pi3XiXzzq3o23805VrbA6opZFeLoGyflnDO1TWFA5qCJ8guPU4/N1Fp4XnLiRGeFMUWvTneSbMwm9yok5bfs9viApF3cV+bTAxUm0gGZ1PlVTGu3RGgqTDrT+rblvWetbm+W9zb5krOdRh4H0wjpPkYrySgpbapN7cRilWxOIQvLuXExjqpOZ7fsCYVBe7FF6ASR
*/