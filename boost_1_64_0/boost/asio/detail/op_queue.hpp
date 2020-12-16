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
ZwzVTV135+DHcFe37KTQ4Bx3tcB9gZ5Ki8umfSktDvMOpm/f72wEelZgZ3uHnj74qXTycI5Z8oFFZjYgv/ztznA+mzjHi9kSLG/AMjWG9xPiOfGeOBl4Xwmpxp2R6wXuzNIPrDSzw0nLeynzjd+PnTXOeE+tszbuqov7is72utRHvTOoUiFV2nzXOG+dt897YJgEj6FJcxC8Bb/1xNa8nkAVV86w1WrUvxh6fQrUZwWGN1h5CytHpVgn+oo7s5wVC0XwQHN9AX5LEdzEzLDiA/sKPTtEJ47RiXPvxA16sYFebKMXuY4BVrLX16WvZIe1NLGWDlYDfWU/Yj0TX8/aO5IK2649yBBrGteduUFnNrwzO76uAVY2EnlLruygqqRwUHfn3Ne2werYnW2sruerG2J9Y6yP/bnG+qC4WF8bK+zRudSqO4fqskd36FLqbgfK24fyDl15J9DeJbR3Q1fj2tuB+tJrDKG+Y6jv3NV3A/1tQH/b0N+e6+8QCmz2oa3NLKbKsEqcGagUJsLtXeLetri7juZrH+7lvlOQIjzQAvTbbbep1ybXPVfyeDpwNU+h59l0PM2h6sV0Pq3m9xbKbrPGLJg1Z5zlPSg8ukO9MZ+NqBHsR3G/pKZTLyqXFHxoiTQjYGdSNdidVA50Z8a+UFfs8uVZD/qdSOvIfw5u2ANU8i24Cc7XFyUqbO5uqDTUGfpiOh0za31oX+Lj0InwSfnq6pVVK+nMur6aftXl6nCoTfih5fw3vm+BvRTMld930EVj1Ia/mb+Rzpsumy6KUxoOiu4JbBiYiN0twemh9qm7I9SM9VFF2qrESHq8uaYC91gD3OEa87ThdzfgneGudjOjxvjzNbOu7i9vQeFSf3aVfgzQh5iJ6MMdXQ56sH8Roz9S54lPTk+tfmJMCXQbJAsOkO4PdAegOgHNqys4VdCbubvjkyRfJIoUcY60p6FTswEnfJbUSos+tAZ0oaqpUduguDHvDRqx4L1BH1pe2YH8+xi9v0LvU8/aULMe/RX6PnM1m6Prt+h6TGR6XPR8glVxLT1fyYQJCF3Nbhmgl3N08u4HQ/fG6F24WXRt86qFfh3CJ03cxza4HvYP18QJynVxNnFt7A/WhGsTM1xh1QVcZzUjsFox07gJNBE4B6qesPhDa5sZsxafA9fOdZPuNXwJ1g3VK84t+dC+wc+xUhm6n5XaUp/dXwy8UlTggiuB5+NKEl9JjgpxLVWayKAyuecH+6kl8l0VpAbV1OW8D6aWfmhfmBnnYXQ2BDEraHd5VnXd3F1wF/pM9a3yBdVUGTP4yD5HfTEPyA2ecyC97IKgWIqZoRsKaWY52aIvKtUMr7pXkXQzRb7IpZwrrGMr7WyBuq7UM0EHZdLPBbJGKQUNsMZQGhqjitTAsddyQTeEFbPXArkgeo0YdWXCo8covO/W7oEC+J82XG2XSugVz1lx9iGVz/NL13ViQOVzrZh73Ut3tnQDIZ0AepTVT+Wa2K0rKiF1sPWRdd81owq2XAd7roGJe9wxHYJ0cJPvtEvQdkeQoDrsnIWmq+8RaL76LoEmrO8TaMaWqJ+dV1M2ZErWnE2ZlDVpV3C/W83aFjqu6/4hgd5lmrYLuIhS8zYAA6EmbozuSzVzC9DqfkKZk56iB2rpiakvhRzFYcKJfog1zzJSrblbOknV5A1JkmZvSpI0fVfgaOed3NXsTZyhMfWWBGn6Bj+2wE5MdjR7C6ZUdga7grxw6npvFEo+7BDzWdnWtKRCk5fMeZk7L+X1Vo6Zytf1+Tmgbjs1E1DDmVn61GxwYjo7PWcn0dQkPQunZwN6oBzkR547dn5Gzk9BfvYON/zIvn53v7/UJj/aYaI=
*/