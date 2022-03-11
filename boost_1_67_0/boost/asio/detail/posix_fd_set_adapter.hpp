//
// detail/posix_fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_FD_SET_ADAPTER_HPP
#define BOOST_ASIO_DETAIL_POSIX_FD_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS) \
  && !defined(__CYGWIN__) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <cstring>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/reactor_op_queue.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Adapts the FD_SET type to meet the Descriptor_Set concept's requirements.
class posix_fd_set_adapter : noncopyable
{
public:
  posix_fd_set_adapter()
    : max_descriptor_(invalid_socket)
  {
    using namespace std; // Needed for memset on Solaris.
    FD_ZERO(&fd_set_);
  }

  void reset()
  {
    using namespace std; // Needed for memset on Solaris.
    FD_ZERO(&fd_set_);
  }

  bool set(socket_type descriptor)
  {
    if (descriptor < (socket_type)FD_SETSIZE)
    {
      if (max_descriptor_ == invalid_socket || descriptor > max_descriptor_)
        max_descriptor_ = descriptor;
      FD_SET(descriptor, &fd_set_);
      return true;
    }
    return false;
  }

  void set(reactor_op_queue<socket_type>& operations, op_queue<operation>& ops)
  {
    reactor_op_queue<socket_type>::iterator i = operations.begin();
    while (i != operations.end())
    {
      reactor_op_queue<socket_type>::iterator op_iter = i++;
      if (!set(op_iter->first))
      {
        boost::system::error_code ec(error::fd_set_failure);
        operations.cancel_operations(op_iter, ops, ec);
      }
    }
  }

  bool is_set(socket_type descriptor) const
  {
    return FD_ISSET(descriptor, &fd_set_) != 0;
  }

  operator fd_set*()
  {
    return &fd_set_;
  }

  socket_type max_descriptor() const
  {
    return max_descriptor_;
  }

  void perform(reactor_op_queue<socket_type>& operations,
      op_queue<operation>& ops) const
  {
    reactor_op_queue<socket_type>::iterator i = operations.begin();
    while (i != operations.end())
    {
      reactor_op_queue<socket_type>::iterator op_iter = i++;
      if (is_set(op_iter->first))
        operations.perform_operations(op_iter, ops);
    }
  }

private:
  mutable fd_set fd_set_;
  socket_type max_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS)
       // && !defined(__CYGWIN__)
       // && !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_POSIX_FD_SET_ADAPTER_HPP

/* posix_fd_set_adapter.hpp
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
*/