//
// serial_port_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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