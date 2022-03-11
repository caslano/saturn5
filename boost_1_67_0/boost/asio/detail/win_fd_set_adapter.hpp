//
// detail/win_fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/