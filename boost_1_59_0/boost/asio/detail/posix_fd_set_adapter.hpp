//
// detail/posix_fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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