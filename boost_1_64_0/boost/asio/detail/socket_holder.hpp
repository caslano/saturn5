//
// detail/socket_holder.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOCKET_HOLDER_HPP
#define BOOST_ASIO_DETAIL_SOCKET_HOLDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Implement the resource acquisition is initialisation idiom for sockets.
class socket_holder
  : private noncopyable
{
public:
  // Construct as an uninitialised socket.
  socket_holder()
    : socket_(invalid_socket)
  {
  }

  // Construct to take ownership of the specified socket.
  explicit socket_holder(socket_type s)
    : socket_(s)
  {
  }

  // Destructor.
  ~socket_holder()
  {
    if (socket_ != invalid_socket)
    {
      boost::system::error_code ec;
      socket_ops::state_type state = 0;
      socket_ops::close(socket_, state, true, ec);
    }
  }

  // Get the underlying socket.
  socket_type get() const
  {
    return socket_;
  }

  // Reset to an uninitialised socket.
  void reset()
  {
    if (socket_ != invalid_socket)
    {
      boost::system::error_code ec;
      socket_ops::state_type state = 0;
      socket_ops::close(socket_, state, true, ec);
      socket_ = invalid_socket;
    }
  }

  // Reset to take ownership of the specified socket.
  void reset(socket_type s)
  {
    reset();
    socket_ = s;
  }

  // Release ownership of the socket.
  socket_type release()
  {
    socket_type tmp = socket_;
    socket_ = invalid_socket;
    return tmp;
  }

private:
  // The underlying socket.
  socket_type socket_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SOCKET_HOLDER_HPP

/* socket_holder.hpp
doFZrXQnx9vzgxwjm3PIFieUzciPSnXiMPvYdyeDvsnbJIZ31/GaaRVM3Rdrz5e9GLSzy30tdN3P68xkUcXDDw5flqTaWX4uKpcLPa88z6kyTNdS9bjOkvq7Vdy/VNwgv4ftDQNB/HROTr6/V38PilFCoPWm92cSWWRhS3IUw4f9cSQMqMMDtQJnCy2I/vQmJ8hz5xQKnTMusPNZEnmPIfYNBN7NSFSfaCyRy0o+BDdV0TiGDhf7vec/TIu8u34PB1ijDzwqNdiglafpg1G9mqPvZnlp3eOUgxq3RTzs4LhW1Qlmxg82fjw7st8zmsqIT8OhfTAvXINM7avoQSik6y9GIcs67UZcugd7jA4Zq/41/D6MGfUqjw43LUYfdUnmxh/SXiT8A+C17tIbpy2n1Vx7xgheTEOYzaPT6KaDwDe6NuAbJEPJGsQ8wJ8KbCvr58zFUp8h/9JZ8ReT/WIoviJ5JIdGYFn6LQLljdyMQsblnTK3FREjM33k4IGf7TnqTEhaALyqNqlhoIslT9gQM32e8OsNixOTyIvh0I17WNy3wVYZjBfs7Hxp8w==
*/