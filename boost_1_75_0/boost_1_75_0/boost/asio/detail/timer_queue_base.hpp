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
KagbBuEAcuSSBvP54xTmG3dt9FntElpxvIyeb4UztIDdGKpZ61WeT+xzXbVu80XgYjdMQw3DjHxHnW1bJVPrdjk0te6NTK27CtW6C+Ni7L6qzVc0ta7ikt5pwRJmfdiuaWNMkahaWUc1JHpKF/kqXlehnsOiNncvykU+CCWowSvaq7Dga9S6DajWxZgwtS5+ojNu38Yrun533SWm38U4Jc6uaXZrTkVArRipanYfP6IDfjetFeMgH9rXkAld7bpmd5YaRYZAoO8JZyR8yLWsohQ/wDi5BJp8LPhGBFXYmQ7OXyA9SUtxHNNVvF+b6Wx9EWeysKYfGqQ3/QNMMXl1T+y9FEqxG5XiO3pi77FQgkfMOOGWXW0PU/F+gyre5bifbNs3J6vLu2QRa6L0JIFnseMQf4sclI/55ik+69xinOsHOs6W9RdbjTNs+wxyY7GjChMKLTLNlqak1Ek0hOqAHagDvtLfJk5QdcB1LvdbTPWGIIIkVtPYoanevqA64BK9hRB7aGCo/XichpaMOx96ipdCKXabumMIYreHYqtQAf68jh2IfDAUWWLSQEIl8PzOdnqvJiqBMcxF7sQQ3zYn/UIl8PuxOtjjTN3JGkoeECq5H1a7J7za9jg98gJKnM/iSMslZ660UyUwq/AofPWiBMZI26PHKYH+GZJoSuBcFuV2kXUfdWg09Rtjd3xC7MOhugVjd7Ahdkko1oO6
*/