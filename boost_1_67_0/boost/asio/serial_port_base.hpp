//
// serial_port_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SERIAL_PORT_BASE_HPP
#define BOOST_ASIO_SERIAL_PORT_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_SERIAL_PORT) \
  || defined(GENERATING_DOCUMENTATION)

#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)
# include <termios.h>
#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <boost/asio/detail/socket_types.hpp>
#include <boost/system/error_code.hpp>

#if defined(GENERATING_DOCUMENTATION)
# define BOOST_ASIO_OPTION_STORAGE implementation_defined
#elif defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# define BOOST_ASIO_OPTION_STORAGE DCB
#else
# define BOOST_ASIO_OPTION_STORAGE termios
#endif

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// The serial_port_base class is used as a base for the basic_serial_port class
/// template so that we have a common place to define the serial port options.
class serial_port_base
{
public:
  /// Serial port option to permit changing the baud rate.
  /**
   * Implements changing the baud rate for a given serial port.
   */
  class baud_rate
  {
  public:
    explicit baud_rate(unsigned int rate = 0);
    unsigned int value() const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID store(
        BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec) const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID load(
        const BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec);
  private:
    unsigned int value_;
  };

  /// Serial port option to permit changing the flow control.
  /**
   * Implements changing the flow control for a given serial port.
   */
  class flow_control
  {
  public:
    enum type { none, software, hardware };
    BOOST_ASIO_DECL explicit flow_control(type t = none);
    type value() const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID store(
        BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec) const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID load(
        const BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec);
  private:
    type value_;
  };

  /// Serial port option to permit changing the parity.
  /**
   * Implements changing the parity for a given serial port.
   */
  class parity
  {
  public:
    enum type { none, odd, even };
    BOOST_ASIO_DECL explicit parity(type t = none);
    type value() const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID store(
        BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec) const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID load(
        const BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec);
  private:
    type value_;
  };

  /// Serial port option to permit changing the number of stop bits.
  /**
   * Implements changing the number of stop bits for a given serial port.
   */
  class stop_bits
  {
  public:
    enum type { one, onepointfive, two };
    BOOST_ASIO_DECL explicit stop_bits(type t = one);
    type value() const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID store(
        BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec) const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID load(
        const BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec);
  private:
    type value_;
  };

  /// Serial port option to permit changing the character size.
  /**
   * Implements changing the character size for a given serial port.
   */
  class character_size
  {
  public:
    BOOST_ASIO_DECL explicit character_size(unsigned int t = 8);
    unsigned int value() const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID store(
        BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec) const;
    BOOST_ASIO_DECL BOOST_ASIO_SYNC_OP_VOID load(
        const BOOST_ASIO_OPTION_STORAGE& storage,
        boost::system::error_code& ec);
  private:
    unsigned int value_;
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~serial_port_base()
  {
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#undef BOOST_ASIO_OPTION_STORAGE

#include <boost/asio/impl/serial_port_base.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/serial_port_base.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_SERIAL_PORT)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_SERIAL_PORT_BASE_HPP

/* serial_port_base.hpp
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
*/