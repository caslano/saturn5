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
nCgHO3A5zW0hnjqSXDtctxOyi/mbG2qi1XVVkepIDfYd89J6BOxuaYnqJj+3Rcp+DqfjoNy8Izke7yIez0yTtrTdoZ9u40lko3qDbS3xAaUDj+qW8vr0da+X3VT1xHOJbGCJbXKf9XPloXf7xJ64/7zDa/ef9+oRRa+WJbaZ2W1jiWw/iW2HY9Nd+dJn+v39+K/vurky/MRVS3Lf6ZTIRpjYprWUwzlubcUdfVe93bxhwpzbz1r0p2pqy1l+20d3HjP30ZvPDX3+w4JOv7j2Zsf5iOUdj7x52via5Iq9j93/wU233rsjsS2tpoMrP2fP1A1pH1fd9uy23Pxum3aTzewrN5+5Coh3pJtbV5sLW9der21Hn9IyJPA94A9k25awUc2n61S6bqbrdLpupesMul5H1wy6PutWMrq+6PbBdKWscGbT9UO65tD1a7rm0rU5PWMBXVvRNZ+u0+ha4NrG6FpI1yy6FtHVbTNK6Bql6yK6Hk/XUrrW03UxXeMhbsM2nuTWVbpuoGsZXd0+MUxXN30THbQZaPe6QVcYifT9PNnZ6Paj59J1mNse0NVtFy9JFv6pCPDesR/OH7cLHqTYAtvBFujau/vSNY042xux350+me17bO/bQX/vIneA3G7Y7cZp9jrCYaebybY5aZdL82xwsLu1nEJ2qynC7pY2RdjeJtJ17hTdBlc6hcJU7G7rE9jX4oo9be0UYUNbr9jMNk/R7WZXThG2svMVG9lDU4SNLF2xi+0h2X5yLac22caafk2/pl/Tr+n37/3cPv24/8L3f6RmZbQmElvmbu4Zrqqt+E/YAdxv+hnppEPhu6wz5gAkeYmBvt9PfNOLKIgN1xEJXtHNuj7oVl1f1eXt49M/fbz2p+rOP3Uct3VzV37r4hNL9yefu+2U7Z327bnpgscTj7tncrqmfp02tPir9WftmLOk2/7Dfr6B9NIxrnzOj6f/LeftnSete+LcU5+8Y9uxjnPDAFd+/Z2X//aFp1cfOCn1vs4jWn69IPE4t13HT/xtdAvHP97j7C83Lbx8yRnDj76647hW79B3P8tPv/mKl999Mj1905NFa6Pn3LT/p88PcHXSNAd1A3XmE7esyfXydHzSQd3rTFcnJSCX9KwqcpvJbSe3i9zrU8UYcvNpNC46DWPJyhhyLsmqyG0lt4PcHnL7ybWdTuOd5GaSWzZdjC2fTtcbp4vx5D10/YJctxmke5IrnSF01/UzxDjzlhlijHkHXR8n944rn0m66kwxvpw1U+i14ZnEJbed3C5ye8nt9MaW6e9eGaTTkismtzZDjCtvySBOhhhffilD6LgHMigusyi+5MLkTp9FOLnd5PaTa5tJcowzj8wknnufKfTg9ZlyjHlrJsUlU4w1784kv+Q6ZlEeZpGMXJzcleQeIvc6uS+yCM+mtJArIFdHbiu5e7LFGPRL2RQGueWKPt15NsWB3FxyVeS2kNtJbs9sMR69f7YYj3bmUPrJTSS3nNxGctfO0cem75kjxqdfd6/kOs+l55JbRi5Obiu5neT2zG3SwZt+Tb+mX9Ov6df0a/o1/Zp+/3+//9b8f/n9X1FeF/335//3oXHdNBpnO78omb7Z3DDLKqrD7gmLNdinqC2PVz+/g77tBB4Nr6UxRshfYnl9rLwsiO1lLGzFXmdMnPUGkOPyx7E0xvGm/yw34OpIfFUtjZ8wvoYGOiZKPCxxGfZMxhtikbLySKysIlYHv8MonXUllE6OLzA+u0rgwwnf5+ORmlUGnt6bcI437dCS427EUOZOCojHgCelU9xv1/B6Xi1AhAGIW9abPl4VXYFTlCpqw/wMcPrt9DjAozXROPA0srCkMS5qgpd7joI=
*/