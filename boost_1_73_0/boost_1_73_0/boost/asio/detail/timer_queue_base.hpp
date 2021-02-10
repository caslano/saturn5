//
// detail/timer_queue_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_QUEUE_BASE_HPP
#define BOOST_ASIO_DETAIL_TIMER_QUEUE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class timer_queue_base
  : private noncopyable
{
public:
  // Constructor.
  timer_queue_base() : next_(0) {}

  // Destructor.
  virtual ~timer_queue_base() {}

  // Whether there are no timers in the queue.
  virtual bool empty() const = 0;

  // Get the time to wait until the next timer.
  virtual long wait_duration_msec(long max_duration) const = 0;

  // Get the time to wait until the next timer.
  virtual long wait_duration_usec(long max_duration) const = 0;

  // Dequeue all ready timers.
  virtual void get_ready_timers(op_queue<operation>& ops) = 0;

  // Dequeue all timers.
  virtual void get_all_timers(op_queue<operation>& ops) = 0;

private:
  friend class timer_queue_set;

  // Next timer queue in the set.
  timer_queue_base* next_;
};

template <typename Time_Traits>
class timer_queue;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_TIMER_QUEUE_BASE_HPP

/* timer_queue_base.hpp
LWdKUs4a/CnYAAAAWwEAACcACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9jaXBoZXJzLmRVVAUAAbZIJGBdjsFqxDAMRO/6Cn1Ak9xNKZReWsihbLYf4DrK2qBYxlJ22b9vkiVQ9qaZ0Qyvl3xxGFKJVBXe6ypeOamhTIf7Bp/ExeEw9IeFJrgowXcVkyCsDs/9AB/e6CL17tBYoWkaGAqFNCVSvMUU4lMfU0aLhEFypmBJcovnVT8B4Lyoge5Td7x6TuMRtXgiP+JSUPI/wMfCSOYT6xZZTIo/p94BYDQr6rouLJVbpW6UoJ0qN8dmtJkBvqZHS8oGhuu1Eo+odKXqGS3NpC87PvsNNxPeEjP+0v7Ywh9QSwMECgAAAAgALWdKUidRYA2aAAAAzgAAAC4ACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9jb21wcmVzc2VkLXNzaC5kVVQFAAG2SCRgXYxBCsIwFET3OcUcwBQ3KsSVFKULF4X0ArH5tIE2v+anQm9vq+BCGBiYN7w7x86g5XFKJEJei/SqomEyuEb3GAjWVj8eOKo6ceaWBzGwZQ17a2p18Z68wak4HIu9Kl2mjtNiIO2ETai1Vl+d4DGHIesQ/8WFavogWOOQ
*/