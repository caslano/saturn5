//
// detail/reactor_op_queue.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_OP_QUEUE_HPP
#define BOOST_ASIO_DETAIL_REACTOR_OP_QUEUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/hash_map.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Descriptor>
class reactor_op_queue
  : private noncopyable
{
public:
  typedef Descriptor key_type;

  struct mapped_type : op_queue<reactor_op>
  {
    mapped_type() {}
    mapped_type(const mapped_type&) {}
    void operator=(const mapped_type&) {}
  };

  typedef typename hash_map<key_type, mapped_type>::value_type value_type;
  typedef typename hash_map<key_type, mapped_type>::iterator iterator;

  // Constructor.
  reactor_op_queue()
    : operations_()
  {
  }

  // Obtain iterators to all registered descriptors.
  iterator begin() { return operations_.begin(); }
  iterator end() { return operations_.end(); }

  // Add a new operation to the queue. Returns true if this is the only
  // operation for the given descriptor, in which case the reactor's event
  // demultiplexing function call may need to be interrupted and restarted.
  bool enqueue_operation(Descriptor descriptor, reactor_op* op)
  {
    std::pair<iterator, bool> entry =
      operations_.insert(value_type(descriptor, mapped_type()));
    entry.first->second.push(op);
    return entry.second;
  }

  // Cancel all operations associated with the descriptor identified by the
  // supplied iterator. Any operations pending for the descriptor will be
  // cancelled. Returns true if any operations were cancelled, in which case
  // the reactor's event demultiplexing function may need to be interrupted and
  // restarted.
  bool cancel_operations(iterator i, op_queue<operation>& ops,
      const boost::system::error_code& ec =
        boost::asio::error::operation_aborted)
  {
    if (i != operations_.end())
    {
      while (reactor_op* op = i->second.front())
      {
        op->ec_ = ec;
        i->second.pop();
        ops.push(op);
      }
      operations_.erase(i);
      return true;
    }

    return false;
  }

  // Cancel all operations associated with the descriptor. Any operations
  // pending for the descriptor will be cancelled. Returns true if any
  // operations were cancelled, in which case the reactor's event
  // demultiplexing function may need to be interrupted and restarted.
  bool cancel_operations(Descriptor descriptor, op_queue<operation>& ops,
      const boost::system::error_code& ec =
        boost::asio::error::operation_aborted)
  {
    return this->cancel_operations(operations_.find(descriptor), ops, ec);
  }

  // Whether there are no operations in the queue.
  bool empty() const
  {
    return operations_.empty();
  }

  // Determine whether there are any operations associated with the descriptor.
  bool has_operation(Descriptor descriptor) const
  {
    return operations_.find(descriptor) != operations_.end();
  }

  // Perform the operations corresponding to the descriptor identified by the
  // supplied iterator. Returns true if there are still unfinished operations
  // queued for the descriptor.
  bool perform_operations(iterator i, op_queue<operation>& ops)
  {
    if (i != operations_.end())
    {
      while (reactor_op* op = i->second.front())
      {
        if (op->perform())
        {
          i->second.pop();
          ops.push(op);
        }
        else
        {
          return true;
        }
      }
      operations_.erase(i);
    }
    return false;
  }

  // Perform the operations corresponding to the descriptor. Returns true if
  // there are still unfinished operations queued for the descriptor.
  bool perform_operations(Descriptor descriptor, op_queue<operation>& ops)
  {
    return this->perform_operations(operations_.find(descriptor), ops);
  }

  // Get all operations owned by the queue.
  void get_all_operations(op_queue<operation>& ops)
  {
    iterator i = operations_.begin();
    while (i != operations_.end())
    {
      iterator op_iter = i++;
      ops.push(op_iter->second);
      operations_.erase(op_iter);
    }
  }

private:
  // The operations that are currently executing asynchronously.
  hash_map<key_type, mapped_type> operations_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTOR_OP_QUEUE_HPP

/* reactor_op_queue.hpp
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
*/