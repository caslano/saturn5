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
P53Ng+IkOfJwV2jdSqVgmnCXWle0+iMWXqHSVmuouPY+qpwggy5HXWcTMbut5ZdL747zZpwjQNBoRhR12f49LNJxVOu+0qAF1SoqtObCVoiHwWqeQagfXsizT+NaEwnOINYtfp3WSXUZC9g//rIVKCWEdSnaI3A1CzbU3Ywo8QEftCEyzGyN0RQackYik3TSkDCXs1dITCdJdZNmVPV29fEuuSHVQCvSYXJToaQHOfWiY/T3hOyoPESE0up4FAYbNlSy72XSHWpfAMkXZiG2Z5ksCvk+LOY/FT1m07nSjYmFbVXYAljxcs60NuDVFKFVRRlcQNIjWyit/zOYewij5ym6R5nRzbOHui0Av/e0xYRafhHB0oZob8TArVua3teG9rL38c7Hjq7zWrHEhzIWhIsCrBYG934dM0llKxn4ClNTGMj5MccR5yqxcciYTovKXGoeMV5+7wKkQ1iPY3Kb0qaWykOkWRjneDIBghBLLNBBBMWe5IuiSlLYVFlBvCmf6RGsDldk/8v/HSU+YKULD9oyZrgnYjJ2wmo4Yh4PYEVPDRNrZDuJ/q9T+A==
*/