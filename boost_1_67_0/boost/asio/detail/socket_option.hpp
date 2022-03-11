//
// detail/socket_option.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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