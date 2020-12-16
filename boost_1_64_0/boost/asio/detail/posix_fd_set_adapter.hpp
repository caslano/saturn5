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
ZQob2NBJ8ulsMk3F6UBCST69SJWjMIh1sRq4DhSZgZyQrpFZndt2NA9dBxqxLFe0pm9gPS5HNJ/Jrpvoy6R+VZMcWCdbEH5fzSj32qLcUXIqdSQlynydJcfONQdWswdWW1N0xmy6YOcSBdHisjDE9cHIBe1Ttauxf0VLfXi1RDa1XibFY8E4v6pP5ZODdiGxOpV5/F/VonNoAAQ/bwjlH4fLn5/C+rWYFId88Zsy4ZeDovySGYh0C/rk13T5AvgjASejtL3uQN86/WmuX3+czkX9nMraxWVdh8qqY/6eokaqqP+K8+lcln/Ot56a83VN2+BrWTgFf2oew7+frsvzjilpjunZI8WqW9nWEtgGuD/etgFtFMvdlpzvTkAYdN5RdR2xIWinUNoeazVrXKzbjYw5yi6WVy9tUSyXmzBzrTeLo469TYOms2EcirZa1DzrD6TxZ6//p7LGn25sce0Lx7PztUrOGnc6waeWH6o3nJoHV1olh/70KosOt91KedHuxboXW2Jk0a28niW6l1HcNkuPWdTbrNh0yos2nYpT9BxWWL06zbKz1RDHWzc5VKjXK95Qfx7+7B6zWPcSi/UsJZhhtza0Rt1rrb/0mKFt4FeqLJZeH9piD6ez2GJD8B/ny9YMlZrbNlr1Ibi8Fz+7NFxaTFyTDP/95RmqAw3eL7bc0mKN8rA10ViUx6KZvzGXOf7W1KR73Fqp0i47f3PinKroI9IXnXLgtH+D/r3mklrLUgOD6Ww+3ydOnmIO05fJrgVoKj9gr5fJLtkDf2dxzmpIC2vk0olU3kCyA3ZqA5iGZJIwcq6eyaYNbjCThCOC86lMbqWhucA00zZlnDU2+6Lseq2AT3+HU4cq7vDQkFMbFROYRbvt7qG5tB2/nvOfzBBokcd6S86x6NblMUsst8Qci67uif/1wm/bORat1Sv10brhjPwGeeVX/Bdm1omsDScRux/+EO3hJ+5/oBDnoVQmkYU/7WSuIObT6+TS6O00TG+SMOoDtU42kxxIib9s9Wd/ao5FByCTDd05Fi1BY/i9A0mi0Nffm5TN4w9E1DHmSi4/NNisjzaL1Tl63YrjzbHANssuveDQem6tXN/am2Mtt+UNwem5d/18aq2hMYstvVi3jD3Urs5lfcfl/71JdS+hooM1SyzWvdQSSy+52BJDbbi0netPJzJmyeVEIlTvfzmZdvV3JAFj70zWONONC2Ufl+/DjA+/CeA3IfzEWD4R/PvrOW3t1rDYBeh064v7KpDeWOJsDb+uKeiKe2L4ibzGQj9PDkeJdF6M/7ZTw2HEmou5KYFLwpVtYUDQ3T3LSgXE76wpO6z5Y+efkWE8//htnsJn82yc59Rks4hjGqVsmlbZFJB0SEPRn3/2K2loWUQay/6+NLRMzCXmBH4M6KaHXxfYJrAewPaE4/kNbCXAHoTjmQxsZdbNYWApwGaHycl78Ov6o/6vNx2ogID/Z/X5fzouVy+VW9V0AA/5aU3GPacl44hHClE8xNX8H7HfKUW1n7kj23wf5Sfi+OojC/jm4LtzU9AH2aeDjB24rMZyjB0wqLECY48torF1GfvMwIYAuxSwgbE0NgzYj3Cc6tLYKOvetzS2JWBrwax3RgPbmuO+PrbGDuB8bzbsO5R1VxlxjwHsaIj3sIGdCdgDgN1rYOcA9jNgUxjYRXDQ3eW35XLAdgJsAQO7jvO408BuA+wm0I0xsNs534cM7I6I9O7hNv664b/HI/J4KiK9V83y/sH+4Y46Ee1rlcjx6XVuX8OuiKaamOo/bwIvpwRl17ECY7EZ6Q/1garrlcJ9OBXZh9/lvOqNlluveX8on3rkWL16pC/el/l0GKs/VGM=
*/