//
// detail/socket_option.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOCKET_OPTION_HPP
#define BOOST_ASIO_DETAIL_SOCKET_OPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <stdexcept>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {
namespace socket_option {

// Helper template for implementing boolean-based options.
template <int Level, int Name>
class boolean
{
public:
  // Default constructor.
  boolean()
    : value_(0)
  {
  }

  // Construct with a specific option value.
  explicit boolean(bool v)
    : value_(v ? 1 : 0)
  {
  }

  // Set the current value of the boolean.
  boolean& operator=(bool v)
  {
    value_ = v ? 1 : 0;
    return *this;
  }

  // Get the current value of the boolean.
  bool value() const
  {
    return !!value_;
  }

  // Convert to bool.
  operator bool() const
  {
    return !!value_;
  }

  // Test for false.
  bool operator!() const
  {
    return !value_;
  }

  // Get the level of the socket option.
  template <typename Protocol>
  int level(const Protocol&) const
  {
    return Level;
  }

  // Get the name of the socket option.
  template <typename Protocol>
  int name(const Protocol&) const
  {
    return Name;
  }

  // Get the address of the boolean data.
  template <typename Protocol>
  int* data(const Protocol&)
  {
    return &value_;
  }

  // Get the address of the boolean data.
  template <typename Protocol>
  const int* data(const Protocol&) const
  {
    return &value_;
  }

  // Get the size of the boolean data.
  template <typename Protocol>
  std::size_t size(const Protocol&) const
  {
    return sizeof(value_);
  }

  // Set the size of the boolean data.
  template <typename Protocol>
  void resize(const Protocol&, std::size_t s)
  {
    // On some platforms (e.g. Windows Vista), the getsockopt function will
    // return the size of a boolean socket option as one byte, even though a
    // four byte integer was passed in.
    switch (s)
    {
    case sizeof(char):
      value_ = *reinterpret_cast<char*>(&value_) ? 1 : 0;
      break;
    case sizeof(value_):
      break;
    default:
      {
        std::length_error ex("boolean socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
    }
  }

private:
  int value_;
};

// Helper template for implementing integer options.
template <int Level, int Name>
class integer
{
public:
  // Default constructor.
  integer()
    : value_(0)
  {
  }

  // Construct with a specific option value.
  explicit integer(int v)
    : value_(v)
  {
  }

  // Set the value of the int option.
  integer& operator=(int v)
  {
    value_ = v;
    return *this;
  }

  // Get the current value of the int option.
  int value() const
  {
    return value_;
  }

  // Get the level of the socket option.
  template <typename Protocol>
  int level(const Protocol&) const
  {
    return Level;
  }

  // Get the name of the socket option.
  template <typename Protocol>
  int name(const Protocol&) const
  {
    return Name;
  }

  // Get the address of the int data.
  template <typename Protocol>
  int* data(const Protocol&)
  {
    return &value_;
  }

  // Get the address of the int data.
  template <typename Protocol>
  const int* data(const Protocol&) const
  {
    return &value_;
  }

  // Get the size of the int data.
  template <typename Protocol>
  std::size_t size(const Protocol&) const
  {
    return sizeof(value_);
  }

  // Set the size of the int data.
  template <typename Protocol>
  void resize(const Protocol&, std::size_t s)
  {
    if (s != sizeof(value_))
    {
      std::length_error ex("integer socket option resize");
      boost::asio::detail::throw_exception(ex);
    }
  }

private:
  int value_;
};

// Helper template for implementing linger options.
template <int Level, int Name>
class linger
{
public:
  // Default constructor.
  linger()
  {
    value_.l_onoff = 0;
    value_.l_linger = 0;
  }

  // Construct with specific option values.
  linger(bool e, int t)
  {
    enabled(e);
    timeout BOOST_ASIO_PREVENT_MACRO_SUBSTITUTION(t);
  }

  // Set the value for whether linger is enabled.
  void enabled(bool value)
  {
    value_.l_onoff = value ? 1 : 0;
  }

  // Get the value for whether linger is enabled.
  bool enabled() const
  {
    return value_.l_onoff != 0;
  }

  // Set the value for the linger timeout.
  void timeout BOOST_ASIO_PREVENT_MACRO_SUBSTITUTION(int value)
  {
#if defined(WIN32)
    value_.l_linger = static_cast<u_short>(value);
#else
    value_.l_linger = value;
#endif
  }

  // Get the value for the linger timeout.
  int timeout BOOST_ASIO_PREVENT_MACRO_SUBSTITUTION() const
  {
    return static_cast<int>(value_.l_linger);
  }

  // Get the level of the socket option.
  template <typename Protocol>
  int level(const Protocol&) const
  {
    return Level;
  }

  // Get the name of the socket option.
  template <typename Protocol>
  int name(const Protocol&) const
  {
    return Name;
  }

  // Get the address of the linger data.
  template <typename Protocol>
  detail::linger_type* data(const Protocol&)
  {
    return &value_;
  }

  // Get the address of the linger data.
  template <typename Protocol>
  const detail::linger_type* data(const Protocol&) const
  {
    return &value_;
  }

  // Get the size of the linger data.
  template <typename Protocol>
  std::size_t size(const Protocol&) const
  {
    return sizeof(value_);
  }

  // Set the size of the int data.
  template <typename Protocol>
  void resize(const Protocol&, std::size_t s)
  {
    if (s != sizeof(value_))
    {
      std::length_error ex("linger socket option resize");
      boost::asio::detail::throw_exception(ex);
    }
  }

private:
  detail::linger_type value_;
};

} // namespace socket_option
} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SOCKET_OPTION_HPP

/* socket_option.hpp
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
*/