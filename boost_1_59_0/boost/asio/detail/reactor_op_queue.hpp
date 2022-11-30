//
// detail/reactor_op_queue.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

  // Cancel operations associated with the descriptor identified by the
  // supplied iterator, and the specified cancellation key. Any operations
  // pending for the descriptor with the key will be cancelled. Returns true if
  // any operations were cancelled, in which case the reactor's event
  // demultiplexing function may need to be interrupted and restarted.
  bool cancel_operations_by_key(iterator i, op_queue<operation>& ops,
      void* cancellation_key, const boost::system::error_code& ec =
        boost::asio::error::operation_aborted)
  {
    bool result = false;
    if (i != operations_.end())
    {
      op_queue<reactor_op> other_ops;
      while (reactor_op* op = i->second.front())
      {
        i->second.pop();
        if (op->cancellation_key_ == cancellation_key)
        {
          op->ec_ = ec;
          ops.push(op);
          result = true;
        }
        else
          other_ops.push(op);
      }
      i->second.push(other_ops);
      if (i->second.empty())
        operations_.erase(i);
    }
    return result;
  }

  // Cancel all operations associated with the descriptor. Any operations
  // pending for the descriptor will be cancelled. Returns true if any
  // operations were cancelled, in which case the reactor's event
  // demultiplexing function may need to be interrupted and restarted.
  bool cancel_operations_by_key(Descriptor descriptor, op_queue<operation>& ops,
      void* cancellation_key, const boost::system::error_code& ec =
        boost::asio::error::operation_aborted)
  {
    return this->cancel_operations_by_key(
        operations_.find(descriptor), ops, cancellation_key, ec);
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