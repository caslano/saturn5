//
// detail/impl/select_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_SELECT_REACTOR_HPP
#define BOOST_ASIO_DETAIL_IMPL_SELECT_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) \
  || (!defined(BOOST_ASIO_HAS_DEV_POLL) \
      && !defined(BOOST_ASIO_HAS_EPOLL) \
      && !defined(BOOST_ASIO_HAS_KQUEUE) \
      && !defined(BOOST_ASIO_WINDOWS_RUNTIME))

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void select_reactor::add_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

// Remove a timer queue from the reactor.
template <typename Time_Traits>
void select_reactor::remove_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void select_reactor::schedule_timer(timer_queue<Time_Traits>& queue,
    const typename Time_Traits::time_type& time,
    typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op)
{
  boost::asio::detail::mutex::scoped_lock lock(mutex_);

  if (shutdown_)
  {
    scheduler_.post_immediate_completion(op, false);
    return;
  }

  bool earliest = queue.enqueue_timer(time, timer, op);
  scheduler_.work_started();
  if (earliest)
    interrupter_.interrupt();
}

template <typename Time_Traits>
std::size_t select_reactor::cancel_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& timer,
    std::size_t max_cancelled)
{
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  std::size_t n = queue.cancel_timer(timer, ops, max_cancelled);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
  return n;
}

template <typename Time_Traits>
void select_reactor::move_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& target,
    typename timer_queue<Time_Traits>::per_timer_data& source)
{
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
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

#endif // defined(BOOST_ASIO_HAS_IOCP)
       //   || (!defined(BOOST_ASIO_HAS_DEV_POLL)
       //       && !defined(BOOST_ASIO_HAS_EPOLL)
       //       && !defined(BOOST_ASIO_HAS_KQUEUE)
       //       && !defined(BOOST_ASIO_WINDOWS_RUNTIME))

#endif // BOOST_ASIO_DETAIL_IMPL_SELECT_REACTOR_HPP

/* select_reactor.hpp
+YUF541/fJK61A7/U3fx+JYBHDIeh/TmBNLa0n8IoWIOG7ZObbEQ+yojvlSErKNTXHQGmh3fm/5qb/ePk0H1qoDPZ+D/vcQROyC5fjErILPfbRLna+c/DkOwX3fK4hIOkfgR+yGKQzX2q/KHrDlEeyZyvoqgBe531WDinnzUoX6opeT68097Jqn16h/yq/hnMl4Sf8vbu+YmqSidmhoPXXrroVizmY07CmYmoX3ddbF+FuZs3XMqNDQVdFj/Zdz+WDI9v6+SqCiFR75IYm8pvPdZEq2lsPiTJG6QQlUpvPNREmdJYd0HSTwlhdZS+Om9JJ6WwilS2ForiXek0FUKu0uhsEYSD0jhJCnsIIXx1ZLoJ4XWUthRCtOqJDFYCudJYW8prH4nieFSuFUKJ0mhlhRWVEriAyn0k8LZUqgvhY0Vkpgmheel0FsKp0mhnhQ2l0uiUApvSKGfFC6UwlFSqCmFn8okMU0Kr0lhgBS6SqG1FOpJISWNf//oiBuxh6DLrJ0RA1Pf0BTl0/XM1gtQVNNrYMlgfTSfxfcvcbsOcfo6w26I+lhSPI04k873gTcues6eG8MtKcHSM90mPgSh7ZI8WWtLS8pFPmj21ycwYZWJ3RgHFF6QZrXmeDTcT+wwY8tSK0uqbLCngkEsvPpSCOPHmlhS/Pzt54sE8G6qT0C/RzQK79I5LzQeShRfbaFmovj46zYE2iTCozND
*/