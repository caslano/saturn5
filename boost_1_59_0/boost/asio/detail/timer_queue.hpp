//
// detail/timer_queue.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
        while (wait_op* op = timer->op_queue_.front())
        {
          timer->op_queue_.pop();
          op->ec_ = boost::system::error_code();
          ops.push(op);
        }
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

  // Cancel and dequeue a specific operation for the given timer.
  void cancel_timer_by_key(per_timer_data* timer,
      op_queue<operation>& ops, void* cancellation_key)
  {
    if (timer->prev_ != 0 || timer == timers_)
    {
      op_queue<wait_op> other_ops;
      while (wait_op* op = timer->op_queue_.front())
      {
        timer->op_queue_.pop();
        if (op->cancellation_key_ == cancellation_key)
        {
          op->ec_ = boost::asio::error::operation_aborted;
          ops.push(op);
        }
        else
          other_ops.push(op);
      }
      timer->op_queue_.push(other_ops);
      if (timer->op_queue_.empty())
        remove_timer(*timer);
    }
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