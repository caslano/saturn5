//
// detail/op_queue.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_OP_QUEUE_HPP
#define BOOST_ASIO_DETAIL_OP_QUEUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Operation>
class op_queue;

class op_queue_access
{
public:
  template <typename Operation>
  static Operation* next(Operation* o)
  {
    return static_cast<Operation*>(o->next_);
  }

  template <typename Operation1, typename Operation2>
  static void next(Operation1*& o1, Operation2* o2)
  {
    o1->next_ = o2;
  }

  template <typename Operation>
  static void destroy(Operation* o)
  {
    o->destroy();
  }

  template <typename Operation>
  static Operation*& front(op_queue<Operation>& q)
  {
    return q.front_;
  }

  template <typename Operation>
  static Operation*& back(op_queue<Operation>& q)
  {
    return q.back_;
  }
};

template <typename Operation>
class op_queue
  : private noncopyable
{
public:
  // Constructor.
  op_queue()
    : front_(0),
      back_(0)
  {
  }

  // Destructor destroys all operations.
  ~op_queue()
  {
    while (Operation* op = front_)
    {
      pop();
      op_queue_access::destroy(op);
    }
  }

  // Get the operation at the front of the queue.
  Operation* front()
  {
    return front_;
  }

  // Pop an operation from the front of the queue.
  void pop()
  {
    if (front_)
    {
      Operation* tmp = front_;
      front_ = op_queue_access::next(front_);
      if (front_ == 0)
        back_ = 0;
      op_queue_access::next(tmp, static_cast<Operation*>(0));
    }
  }

  // Push an operation on to the back of the queue.
  void push(Operation* h)
  {
    op_queue_access::next(h, static_cast<Operation*>(0));
    if (back_)
    {
      op_queue_access::next(back_, h);
      back_ = h;
    }
    else
    {
      front_ = back_ = h;
    }
  }

  // Push all operations from another queue on to the back of the queue. The
  // source queue may contain operations of a derived type.
  template <typename OtherOperation>
  void push(op_queue<OtherOperation>& q)
  {
    if (Operation* other_front = op_queue_access::front(q))
    {
      if (back_)
        op_queue_access::next(back_, other_front);
      else
        front_ = other_front;
      back_ = op_queue_access::back(q);
      op_queue_access::front(q) = 0;
      op_queue_access::back(q) = 0;
    }
  }

  // Whether the queue is empty.
  bool empty() const
  {
    return front_ == 0;
  }

  // Test whether an operation is already enqueued.
  bool is_enqueued(Operation* o) const
  {
    return op_queue_access::next(o) != 0 || back_ == o;
  }

private:
  friend class op_queue_access;

  // The front of the queue.
  Operation* front_;

  // The back of the queue.
  Operation* back_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_OP_QUEUE_HPP

/* op_queue.hpp
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
*/