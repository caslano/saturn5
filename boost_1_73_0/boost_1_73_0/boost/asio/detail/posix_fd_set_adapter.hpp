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
Jvra1TBUPZ28re/z9TJOVF5ql0MOFOkov6xcuKWreQeHyixLPiHPLWGtVQA6NOCC1oW30US//jYadRL46h4P7qM5RaYytD1gVLcLm7BLN3YqVNRGKQ3V4abWzMQHNIbDF2pYRrDn6ftYZZ4OgPOK6a/ORkHMdh/RjOiv3on97k3rtOhNcxjvyrHW4hbqNGdBU4jd25YOvG01YLeTZPdwf2/vsJfUsy8E29Nv4vkepNbaP4zhiqiQJ0pz8Ynt5rail9naYzO2m8rllk3NlnACmK5b955vcGLDs+6kdiUkPivumvv6Pwu0o53+Qb8F2q+6kIgVAHRQq7/x2hc36LTLgIGso9heMIiztRQYSHQUxG9rXJHWWNXRHp0Cc2y1zJl1YWx5QyvGjrxzNbg8IFGj9mgZCwWbJN5qOC+EnfDakZ6Lm3bh7JpyREo7KjX9RNuaG8qiGV22qwtowMrvTG90bZyJOjexU+ONCRWNw76mc9zs0Is2ZWNYZYl6AbTbHpRvV76mreuiJkCnQrgC5sFWaqSM3SniN8fvpl/E0+ujHgyIO8+7k8pXGduuQwSJs6piKR9XVB3FnQp3iYql8uVF4yMOfMmnTZfMMOHJoMBqDlHeTqxGZlYfIu6JgJhMBJm2Anks8mJUIh/PC0NP
*/