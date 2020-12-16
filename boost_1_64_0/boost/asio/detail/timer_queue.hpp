//
// detail/timer_queue.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_QUEUE_HPP
#define BOOST_ASIO_DETAIL_TIMER_QUEUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <vector>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/date_time_fwd.hpp>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
class timer_queue
  : public timer_queue_base
{
public:
  // The time type.
  typedef typename Time_Traits::time_type time_type;

  // The duration type.
  typedef typename Time_Traits::duration_type duration_type;

  // Per-timer data.
  class per_timer_data
  {
  public:
    per_timer_data() :
      heap_index_((std::numeric_limits<std::size_t>::max)()),
      next_(0), prev_(0)
    {
    }

  private:
    friend class timer_queue;

    // The operations waiting on the timer.
    op_queue<wait_op> op_queue_;

    // The index of the timer in the heap.
    std::size_t heap_index_;

    // Pointers to adjacent timers in a linked list.
    per_timer_data* next_;
    per_timer_data* prev_;
  };

  // Constructor.
  timer_queue()
    : timers_(),
      heap_()
  {
  }

  // Add a new timer to the queue. Returns true if this is the timer that is
  // earliest in the queue, in which case the reactor's event demultiplexing
  // function call may need to be interrupted and restarted.
  bool enqueue_timer(const time_type& time, per_timer_data& timer, wait_op* op)
  {
    // Enqueue the timer object.
    if (timer.prev_ == 0 && &timer != timers_)
    {
      if (this->is_positive_infinity(time))
      {
        // No heap entry is required for timers that never expire.
        timer.heap_index_ = (std::numeric_limits<std::size_t>::max)();
      }
      else
      {
        // Put the new timer at the correct position in the heap. This is done
        // first since push_back() can throw due to allocation failure.
        timer.heap_index_ = heap_.size();
        heap_entry entry = { time, &timer };
        heap_.push_back(entry);
        up_heap(heap_.size() - 1);
      }

      // Insert the new timer into the linked list of active timers.
      timer.next_ = timers_;
      timer.prev_ = 0;
      if (timers_)
        timers_->prev_ = &timer;
      timers_ = &timer;
    }

    // Enqueue the individual timer operation.
    timer.op_queue_.push(op);

    // Interrupt reactor only if newly added timer is first to expire.
    return timer.heap_index_ == 0 && timer.op_queue_.front() == op;
  }

  // Whether there are no timers in the queue.
  virtual bool empty() const
  {
    return timers_ == 0;
  }

  // Get the time for the timer that is earliest in the queue.
  virtual long wait_duration_msec(long max_duration) const
  {
    if (heap_.empty())
      return max_duration;

    return this->to_msec(
        Time_Traits::to_posix_duration(
          Time_Traits::subtract(heap_[0].time_, Time_Traits::now())),
        max_duration);
  }

  // Get the time for the timer that is earliest in the queue.
  virtual long wait_duration_usec(long max_duration) const
  {
    if (heap_.empty())
      return max_duration;

    return this->to_usec(
        Time_Traits::to_posix_duration(
          Time_Traits::subtract(heap_[0].time_, Time_Traits::now())),
        max_duration);
  }

  // Dequeue all timers not later than the current time.
  virtual void get_ready_timers(op_queue<operation>& ops)
  {
    if (!heap_.empty())
    {
      const time_type now = Time_Traits::now();
      while (!heap_.empty() && !Time_Traits::less_than(now, heap_[0].time_))
      {
        per_timer_data* timer = heap_[0].timer_;
        ops.push(timer->op_queue_);
        remove_timer(*timer);
      }
    }
  }

  // Dequeue all timers.
  virtual void get_all_timers(op_queue<operation>& ops)
  {
    while (timers_)
    {
      per_timer_data* timer = timers_;
      timers_ = timers_->next_;
      ops.push(timer->op_queue_);
      timer->next_ = 0;
      timer->prev_ = 0;
    }

    heap_.clear();
  }

  // Cancel and dequeue operations for the given timer.
  std::size_t cancel_timer(per_timer_data& timer, op_queue<operation>& ops,
      std::size_t max_cancelled = (std::numeric_limits<std::size_t>::max)())
  {
    std::size_t num_cancelled = 0;
    if (timer.prev_ != 0 || &timer == timers_)
    {
      while (wait_op* op = (num_cancelled != max_cancelled)
          ? timer.op_queue_.front() : 0)
      {
        op->ec_ = boost::asio::error::operation_aborted;
        timer.op_queue_.pop();
        ops.push(op);
        ++num_cancelled;
      }
      if (timer.op_queue_.empty())
        remove_timer(timer);
    }
    return num_cancelled;
  }

  // Move operations from one timer to another, empty timer.
  void move_timer(per_timer_data& target, per_timer_data& source)
  {
    target.op_queue_.push(source.op_queue_);

    target.heap_index_ = source.heap_index_;
    source.heap_index_ = (std::numeric_limits<std::size_t>::max)();

    if (target.heap_index_ < heap_.size())
      heap_[target.heap_index_].timer_ = &target;

    if (timers_ == &source)
      timers_ = &target;
    if (source.prev_)
      source.prev_->next_ = &target;
    if (source.next_)
      source.next_->prev_= &target;
    target.next_ = source.next_;
    target.prev_ = source.prev_;
    source.next_ = 0;
    source.prev_ = 0;
  }

private:
  // Move the item at the given index up the heap to its correct position.
  void up_heap(std::size_t index)
  {
    while (index > 0)
    {
      std::size_t parent = (index - 1) / 2;
      if (!Time_Traits::less_than(heap_[index].time_, heap_[parent].time_))
        break;
      swap_heap(index, parent);
      index = parent;
    }
  }

  // Move the item at the given index down the heap to its correct position.
  void down_heap(std::size_t index)
  {
    std::size_t child = index * 2 + 1;
    while (child < heap_.size())
    {
      std::size_t min_child = (child + 1 == heap_.size()
          || Time_Traits::less_than(
            heap_[child].time_, heap_[child + 1].time_))
        ? child : child + 1;
      if (Time_Traits::less_than(heap_[index].time_, heap_[min_child].time_))
        break;
      swap_heap(index, min_child);
      index = min_child;
      child = index * 2 + 1;
    }
  }

  // Swap two entries in the heap.
  void swap_heap(std::size_t index1, std::size_t index2)
  {
    heap_entry tmp = heap_[index1];
    heap_[index1] = heap_[index2];
    heap_[index2] = tmp;
    heap_[index1].timer_->heap_index_ = index1;
    heap_[index2].timer_->heap_index_ = index2;
  }

  // Remove a timer from the heap and list of timers.
  void remove_timer(per_timer_data& timer)
  {
    // Remove the timer from the heap.
    std::size_t index = timer.heap_index_;
    if (!heap_.empty() && index < heap_.size())
    {
      if (index == heap_.size() - 1)
      {
        timer.heap_index_ = (std::numeric_limits<std::size_t>::max)();
        heap_.pop_back();
      }
      else
      {
        swap_heap(index, heap_.size() - 1);
        timer.heap_index_ = (std::numeric_limits<std::size_t>::max)();
        heap_.pop_back();
        if (index > 0 && Time_Traits::less_than(
              heap_[index].time_, heap_[(index - 1) / 2].time_))
          up_heap(index);
        else
          down_heap(index);
      }
    }

    // Remove the timer from the linked list of active timers.
    if (timers_ == &timer)
      timers_ = timer.next_;
    if (timer.prev_)
      timer.prev_->next_ = timer.next_;
    if (timer.next_)
      timer.next_->prev_= timer.prev_;
    timer.next_ = 0;
    timer.prev_ = 0;
  }

  // Determine if the specified absolute time is positive infinity.
  template <typename Time_Type>
  static bool is_positive_infinity(const Time_Type&)
  {
    return false;
  }

  // Determine if the specified absolute time is positive infinity.
  template <typename T, typename TimeSystem>
  static bool is_positive_infinity(
      const boost::date_time::base_time<T, TimeSystem>& time)
  {
    return time.is_pos_infinity();
  }

  // Helper function to convert a duration into milliseconds.
  template <typename Duration>
  long to_msec(const Duration& d, long max_duration) const
  {
    if (d.ticks() <= 0)
      return 0;
    int64_t msec = d.total_milliseconds();
    if (msec == 0)
      return 1;
    if (msec > max_duration)
      return max_duration;
    return static_cast<long>(msec);
  }

  // Helper function to convert a duration into microseconds.
  template <typename Duration>
  long to_usec(const Duration& d, long max_duration) const
  {
    if (d.ticks() <= 0)
      return 0;
    int64_t usec = d.total_microseconds();
    if (usec == 0)
      return 1;
    if (usec > max_duration)
      return max_duration;
    return static_cast<long>(usec);
  }

  // The head of a linked list of all active timers.
  per_timer_data* timers_;

  struct heap_entry
  {
    // The time when the timer should fire.
    time_type time_;

    // The associated timer with enqueued operations.
    per_timer_data* timer_;
  };

  // The heap of timers, with the earliest timer at the front.
  std::vector<heap_entry> heap_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_TIMER_QUEUE_HPP

/* timer_queue.hpp
eLGLv9Ut4MsEu4JbgN3APHBrcBrYHSwHe4EzwG3BY8Eesi/TEzxD8s8FtwIXqrTUX2vJcw5slPrbg/Ol/j5Sfz9pf47sJ+0ADgLzwGHgAHAsuDs4U/aZqiX/aHAn8EZwEHgvOBhcLvkPg7uCT0pa/H7g7y/ymnhz1sDj69//3vXvf+Pa9/pc9477+/jnrXdf+i11Q6vj69Px4288Ntjv/4OnzpixHuz/s8X+v6Snso0eWzwyf1xh3ph8MfvnG0fyG3V+/ohRRXnjiieFsGieq7L5zuilePbML8wfl1fg0zxTyjULPOI/oLZ3OE+o34C0fpb53braxW9Ahoonc7z+rRfSGFFT13q/R4baZMIfu536kWJzaY9PWeDhMyDH2S5ki95XQEYvh326qfN2F18BHeiLWpc6MWNotk36kIBsLj4C3uP3Z4O/HvvAhfgGSMwKi3HYgj7nWo4+b0j08NPgbFezfALU93b0uemL7V18Anw1hD8nOOqM2RdAQL50sS3/TtUlePxA5pSzLhWsUfd5aUifCy+t7CYxRkfodL21J712AHQ4dDJ0CUQZeBKsHzVPG9v1Juvyo8317rPGsc5zMDQXOgdaAlEeHlPephc/c+qs2RX6321l3SRP8zyIHlui5YOqoVOhy6HboGz6TIl/DD2Rwf1/KyO35aY8S0nPjaIf2zGWOnUi9QCZrK98pOu0uhcU9u9vybnng+dyLFmHud+c21mnl5n0YJ0+z6QH6fRxJr2Tma/0m4nBOdikJ4eMb52Mbw8Z32xoIuNbdaJzfMtmu46v8AZ19c9qhp21tDFkfg/eyDm/z4CvzqVNcqu7tQv+2O91aVeI/Xqx3OQ5UqAftLGyx3dpF1GAc3yV1eVTZxaWHjaV65r28YIMrklL2WQTf/dlne6t+e/uqPirKqeXiY2L4c/R8/qTTjpfrIXEniXIEzG2saxji6y6XSaeKXVzTtet1wE7c476OCf1GfutUNv+YiuImyg7+PkefSNXcRk3KZNo5Omo032sYAzjquqjqqbKWq7wI+9mVoeIMgfuyVxVRu61QfMD985A0vY+KTX9Qb2kdb2hz/827s//3NDnf7PfuSW9vd+5PVOd98d1KoZbaF/H/M4NzPdVaf6McqgzdCC0qVqfd6lnlpnvM9zmu7EDekqX3ZN1sTQz3lzPxHlvq/c01LSTOW/ye+prFJBerdPd1Mq9LpPZwfhoNvsZz2ieUdbWwbV6uU62fx1d20HRYNs6+5s6v7elbHy2p49HIP/GynYnqTC5d3pyG23/I3kV5I3uS95G2cqo32En1HT8Z7Gvcbn3BoP0AefoA7vPE31Oyxhy372f7r/oSCuImyn/Nyd5jJH3fSdlutvsCvV0F7vC0PzEZKdfbMmPOMcD92DZScF78MCTzPvO+x60VNrfpkx5Jtnjx9vvkSSxU98XUm0vUKh8wfj7RX5QyEeLvD9mh36fC++mZk7do9O7Es+mtY1/spnbd+r8Xaxe5MrclWtkuX2HmH3HZzTPZpLG9k6n08w+HN8afINEF1M8B6Rd9vc+aed7f1E75zNkC/W8PtneP/KCde8feGN/v0ob/X6npE0p7d2fpUXHh7apOd/RdT29n6NV7Z19kLQL8zisD5r5DU39ofVUZDjr6TqU+k82/pnsv5N0X2eH+2SC19snk+R7+2QiP3afTNkx+GQKyF7ewSn71uo+DMoefEaJ7FuFyV4XQfa6CLLXtUD2rWKQfUhA9kyn7NtyvUZ32Y2fo+5h8jdGkL8xgvyNLZC/ewzyB8a+rKOLH0GuZ51i5Df3WED2HmGyw+stu8n3lJ382GXv0QLZt+/klH07rpcT0AEpC7nn3daH4G0=
*/