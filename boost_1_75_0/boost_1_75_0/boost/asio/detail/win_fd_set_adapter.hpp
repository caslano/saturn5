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
OJm4+wPSN01f42PxA5wKv+zePukHzFRZkhP2tQpuTQnQP3KlCpwcJ16/sKEKDlRmTh2QqIIR3vpzg6Mq4cN9Zye3Q5Wgd2e+yq7JlSC7xfnI6qwKePvr3rMxnhXg15fz6vHMChhh8DWpOqccWorbJoe7lEOBcqZr1aRyuP1S87QRtwxOL1RaXbitDF7UhCzR7ikF7pV0x2UXSyF1zcoFYdNK4eN0WQmHg98hLOzYDLlTJWDT8eiW89Vv0CMWeYtzqxiennPLSb5SBLOnfKze5P0V6udeHxVrWQh6RoxfKsiOGfZR36epKQ9kbMsba67kgpHXjvcvp3yB9zQDa0W/bNA7XL9fMTsTpPpHZpm+/wSytvTmB7NT4MZo6yl5PnGw0zTc5+fNtzDMTI4x7dEFYrzGcoNfk7uF93c5gvvhXOG9MH64DoZhXQOCvRiDLv9nyP8lRDP4v/DodzZFb22KHkXX3vOd877mKgjDIemwIvoLBGF62NgQv6Eh/gII08PUI05OTk9Owc0b1O8sDAh+ntjQH3ew3mYQuKVgRfPgRmIYG3kOFtKMByKprSLIn/Weyq2a6VWHIllePfnh30Ro3lEoTxuNntxGM+VGivAXMuK7RdpoZgVttE1FMXV0r/J+EX6S2YbsfSPoNPrUK+wdyDXIohnlW9FsW1AO226UwCQVlfET5eyJfPZ0JolqjEEB3ShnE3JzaHQZts0I
*/