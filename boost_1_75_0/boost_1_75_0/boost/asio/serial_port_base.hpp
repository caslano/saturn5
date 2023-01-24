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
ngyT2rwVN4T5IRvrbR3ZacR2kKu/SdkuYGXlcREMBMN7+xiBrV4ohb8b1bKIRKV7bCF/+pVx5tlbYoJc6nmys+fXOC2ae8AVv2liRLySAyaM+/XoXVkgB9qkQAs6oW29lA3pa4/CeTCKxRUTkhBZvSDkBhuPw74sLTIGubkUrrIIrv/niyAhYhFcdUrhqDOj8aEj2hl7Vn6yMrnYWC9r+clG0u7Lw3HEBm2XEbJu/ubUMCHr9vK2DNN+A7d18htwLunyEPFa+eLl+z8KEiozSquctwK1rB8wvuW3+/htnigzSymfQVk6KtFVLIIMjhpeEmrT0FPeBG7B0+MuyQK88k63rSnH1mFVYLxYOFDZGTvRPSkrVp2RmWNTouHU9ad6jYfk4qrn5wJP+hfg670+oJci8EJ0hTA5GxChRgZIiV40KaxE7/Yi1UclepsTcbc2SxZRpWoNXdRCP4cHeEjyU5S1WqwpHOHhs8A9kkVcpTiac514/ykJ9UGvdWMc/wtwrsFb8X7ptObmTQVnQCbqcJ/6EAaP+8cDw1dwCpn/CUBy+avfmFdbcNjchw+elYiZPg206jRk+BT+sUV2OgnMcyY3glS/8sKwAS5+DvHIS9jk2bCufGw9rMX5M5HeDsWmSzRU+1B4OmBatqyM8OcUqOIBLik35Cuyv3RlF/pCO082TcaAd9rkZvqLRWpUR9clmG2qFATkGluJqIbN
*/