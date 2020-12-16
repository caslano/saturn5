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
P8vw1Fnq52RY88fDYxgfqu/kuXO9qLjM/FT/VzK6r78cfX3rxjPefpLbdx5mzX4a3Udy7z0qtuYzpKflbvUZ1q3G6mWE2i6Z1qyje+cSqT63wjOmONeat3Hbplda/SnSh9zOtP2u7c0pg5mhftc42++aG6/fJfmHM0P9rmL2IMX2u2wbWPuPVqOubuKwAFWvUc1tYN0L4nvvdJ5P23gmJE/1nYgeU1O+RZXHjmpcPqp+yHrUp6a+OOApj6zGr6E8Sr6t9qDFXYMvuW5WbnTMGvzweNoIK7cqMDs8nia7nWLKVVPzbcUMSXeNeK7VL6avcqz7bqTq3QiVh59amVTsnIod52+QfdY80Mo+C9pnrlvYnGjH6YbZ9B9mn68OhNe9F5bN9pS/s6x5Q1u+pvPeH2gVWn/eKj05LT1xaJw9bu0kv4wG/9OmfKUMSquXkpretF5KnfSskyPG/DSGFHe+oMiGoYqzoZvoWShtpgWa8jTeGGOJlSmkZ9DNGVNWmNa31nr4etkx5b025TnuPeo+69JzI9al+5f78Jrzw18Tfrhr0Y+uIT+yNeT9+5rnl+15fV/6hfuytz3y1GNtbr6tU/y1/f5ryOOt8f7m15Z/02vI/dfSx99D8YnOK+fPzitVJITvodnguYdGv/mm6Ywv1G89v58M/7bzRKt059djnt9P6PcJZg245/fT+s1rqTXqmnOGbX3Ohct21yxrzhim+sj18sjl1MK9VHf+0s7fWrl2pm6U3A90D8kPYXedazhS5xeOhSvh+fAnsAJeC1fA63T+Icqel/wzuBmuhs/A6+Hv4I26P+Mm+CW8WfdnbNK5hrfCnjr3sK/OPZymcw9LdO7hRTrvcKHOM7wc3gtvhRvhffA+uBXeb/yHD8Ad8Cq4H/7YPXdV80eaJ1sVde5qidbol5pwwblKhzKt0f8OPEfnwJZIv0B6ndOr+Q7iLvfdc3p1PmwvnQN7GqzWuZMLdd7kIt1DcqnWki8J57fmEPzz+wTPvTErJHeJ5Lz3xryi+2t2w746x/4k3W+SI/2p0k+Q3AzdGzITvqH7U/7onperMWaNb6+KOi/3Id338pjuAdqi+1l+DUfBp+Ak+ITSdSuco/tczpe5/NGYLGPCPv78Rud9/g4OhC8oHjvhePii1ui/BAvg7+Fi4ya8Us/dcxQP8f4NCMsxlllzfowOaIxR45QVCV/tvoEsuyG3Zn+RY+yr5vrBlqtaureilu4xThL33MhjvPVcLeUCX0hOZl6511w5VC3lcmohtyygfpv6oqui7rsYrPzJgV3gUN1rNQwWa09OhfbuzJN+vvSLtMfneu3luVd7ex6T/V3au/N6eO8OhUTte/VFVkWdvztNe43yYCt4FmwrfSfps+HZcBCcDmfruXHjHHgRzFc9NBMul9x66TvW8lzBHvezHhtVdP/RPSL/q3tEqu8/uk/k6D6R/859IivuJ31Q21B7UakPkN6ocag5qOWo9agdqH2owCbSAJWNGocqQlWj1qC2ovaikjYTZ9SQzUf3lRz9O/p39O+b//v21v+fX3zR13D+n1nDv4lxkZNDa9iC4fUb9bU26omWtLv/pvnlSufApAmnTmGxyOQpk04bP6qGcXbZbeScKafx86HO3HOhZ+5Zck3cMdoDHWqee9bZZ77jswPhUGcOulBz0G48Ryc6jvxQcVyCGmDmEDSn1bfk8OPp2G1d83yCR250zDqY8B3xx1u5CwIn8P+s8JyC7DfXGTRaH3Nulemiu+P8g63MvOg1T7r/nfy25iV2VmMqKrSO7L7Gzth8AC6p5XzP4Y6Pe9fjaJ2n1mwoHpHzPYyRa9yQcB8rbjfzjx+E8sq+DSw7888=
*/