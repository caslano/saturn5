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
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
*/