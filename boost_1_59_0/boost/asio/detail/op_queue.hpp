//
// detail/op_queue.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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