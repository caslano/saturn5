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
0ZNWotIF1fnm6Rz6EFLS9BeQQ2+yeKMXtr5N22+rRu8ejumMSz+JGr4GyqWb5bPiF8P9X0SGWHS8WWw28LyHdKBvRXp+S4Z0LL4dog18soe8jYiBEckzZbyFsVikTfRjGU9i1tHB893cbjy8Jfz8LPT3TdAGWWjxkKLNdMjV6cnJ52PYWPvbrYw2r4f/RwEd3nElJW8DVjIgLWqoW8jUXQwFeBcy+kNGDmCpOsgIbzBZvRagiyf3ztVHXxlUFzgmzjYrYjResyLXjtp6p0ZyH8m173I1HDeyPu2go56OXf6tBuf7uAckFRxor63wcgttT8DoPkINt9+nRrLItpS4zQxB/bU5aBbwjvxWdFRL3kBXVHjEWuxCt3vUOV2nfNJ/OUI+qlHjk4j1+pkGs6S+A2UmVejvhqSt+hlptN8txiKB/ptEmEe2JdIiz2iOXD7Bkj/6+SXjQSp6EPCJp6CXcA/nHQjZT23x8uxVjULfjlrc1BJuT3eeEW6V61HHffSa8bSVKb8/ujZi2/FNveeaYzHbe82FEYpwwk0G00HU6CH2Z9ndA86WwJy007LQ7Cb2h5Go6IdMMYJOPa5swsBc/EdeHoVUeG291UssZnR61ZRWg5aMY0jKHCQUpvQ5IU9eiHrpk1CtcpLc9CCSUutvqMNli5QqbTSn1ZArEzSO2tt+Ef6eeSvarr23vkXPqr/0DtDw5gmMVd56ut1p
*/