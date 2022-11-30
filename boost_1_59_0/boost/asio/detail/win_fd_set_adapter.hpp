//
// detail/win_fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_FD_SET_ADAPTER_HPP
#define BOOST_ASIO_DETAIL_WIN_FD_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/reactor_op_queue.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Adapts the FD_SET type to meet the Descriptor_Set concept's requirements.
class win_fd_set_adapter : noncopyable
{
public:
  enum { default_fd_set_size = 1024 };

  win_fd_set_adapter()
    : capacity_(default_fd_set_size),
      max_descriptor_(invalid_socket)
  {
    fd_set_ = static_cast<win_fd_set*>(::operator new(
          sizeof(win_fd_set) - sizeof(SOCKET)
          + sizeof(SOCKET) * (capacity_)));
    fd_set_->fd_count = 0;
  }

  ~win_fd_set_adapter()
  {
    ::operator delete(fd_set_);
  }

  void reset()
  {
    fd_set_->fd_count = 0;
    max_descriptor_ = invalid_socket;
  }

  bool set(socket_type descriptor)
  {
    for (u_int i = 0; i < fd_set_->fd_count; ++i)
      if (fd_set_->fd_array[i] == descriptor)
        return true;

    reserve(fd_set_->fd_count + 1);
    fd_set_->fd_array[fd_set_->fd_count++] = descriptor;
    return true;
  }

  void set(reactor_op_queue<socket_type>& operations, op_queue<operation>&)
  {
    reactor_op_queue<socket_type>::iterator i = operations.begin();
    while (i != operations.end())
    {
      reactor_op_queue<socket_type>::iterator op_iter = i++;
      reserve(fd_set_->fd_count + 1);
      fd_set_->fd_array[fd_set_->fd_count++] = op_iter->first;
    }
  }

  bool is_set(socket_type descriptor) const
  {
    return !!__WSAFDIsSet(descriptor,
        const_cast<fd_set*>(reinterpret_cast<const fd_set*>(fd_set_)));
  }

  operator fd_set*()
  {
    return reinterpret_cast<fd_set*>(fd_set_);
  }

  socket_type max_descriptor() const
  {
    return max_descriptor_;
  }

  void perform(reactor_op_queue<socket_type>& operations,
      op_queue<operation>& ops) const
  {
    for (u_int i = 0; i < fd_set_->fd_count; ++i)
      operations.perform_operations(fd_set_->fd_array[i], ops);
  }

private:
  // This structure is defined to be compatible with the Windows API fd_set
  // structure, but without being dependent on the value of FD_SETSIZE. We use
  // the "struct hack" to allow the number of descriptors to be varied at
  // runtime.
  struct win_fd_set
  {
    u_int fd_count;
    SOCKET fd_array[1];
  };

  // Increase the fd_set_ capacity to at least the specified number of elements.
  void reserve(u_int n)
  {
    if (n <= capacity_)
      return;

    u_int new_capacity = capacity_ + capacity_ / 2;
    if (new_capacity < n)
      new_capacity = n;

    win_fd_set* new_fd_set = static_cast<win_fd_set*>(::operator new(
          sizeof(win_fd_set) - sizeof(SOCKET)
          + sizeof(SOCKET) * (new_capacity)));

    new_fd_set->fd_count = fd_set_->fd_count;
    for (u_int i = 0; i < fd_set_->fd_count; ++i)
      new_fd_set->fd_array[i] = fd_set_->fd_array[i];

    ::operator delete(fd_set_);
    fd_set_ = new_fd_set;
    capacity_ = new_capacity;
  }

  win_fd_set* fd_set_;
  u_int capacity_;
  socket_type max_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_WIN_FD_SET_ADAPTER_HPP

/* win_fd_set_adapter.hpp
+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
*/