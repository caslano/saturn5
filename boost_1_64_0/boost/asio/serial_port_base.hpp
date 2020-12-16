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
XrCj6gkqyLScbpQIQ3A6Xpj3BL2qFR9GVmTha4R1tHBAVSK+oE5jdOw0ww/KroTkeNmkHI83hVh4OQZMj/txOm16GR5bPWE8/bwWQxEryBAsHO6JOV7zVPotfhQqPBx/I0zK9sZvAwdVGAPmy12KJ8haRYYLKUKs+asUcdO3wqOphE/0wCCjQ9ZRWLVpBj5RUxHdeHKPgtJHC0gLvoKoPmt4nE6sGYWkajyORx7PsF/ERxrPEaUWSwHDWR4iTISPmwRPZ161GpQVN7LGo2lNibWZKR72P5M27B3I+F2QOBys3/j7y3BGjSNa8USqai13wo1wXMxyPBOz/J07GlO4pzU/NboBw2+ok/uybQjbIn4jJThP4lMRtkb0JoSjET8ZYSvEv0D9gPj5LP6LCJcifgWL/xLCnYjfjZDK9zLC9vUS363eGv8VhJmIn1DP7OYjnI/4xSz+FoTrEL+t3pr/VoS7EZ/aYI3/KsLFiF/O6K9RfMS3P9lavtepfRE/GWGye+hpNr/Na4vYQjYN/iptUZtic9iCtmqbxxYEimrzAaYEzvLsAAGn++0QxgUwF2I22MK2KMStgt8e+F0tUgSaU0+1Dnw+SCXSovxakq4Cv4faBtsybf9NTiwR9Q0gjvpC8IMkClifMvWL6ToUMY1L+ZifHlPG0/365ACWjsK1UUsCpnWcWlFb5Q6odWrA8Cu6X0kfmqMLWThgysqBD5lgJYbFE1+QTf4qIW4EDmQGhhVbS/P7mlPxHflsZWiOvVTsmBzluZPtRfkOJR3f4B8A2QmaqyC/CDcVvH20sGZj7QPnzwIHJNg/GROpS40KklLRAI3mUyUBw4lS8nACN4iKIlEg2mC9U6mL7NglEWoJc3qiXjw9wJnTK3HZ3fDJd7p7kjRrxOoVCoLAD8JMbsErMbxePCCyeFIQI97IX4+LNNGZWm1NjSfSMCgrpzICnyJ8gQas7vAccX0J5jFY7wO3DFJG5zgd0yTjgG/oyJzy8vJByrCsHAhSR+9ZCiUy3gycH6WKG5ZHRJJ4ReJloSrkPDVIMcolizUsx1rxeJnpw8DUkyYul0MEq0gd0HvazN6N44snf2Xz5TaKr9OAXZUcRZOWxNjQk/HszgL5GT8fzi8m4dEb4UvpBhH5y91FjhkWvwuiCc4QMXm6ecA1ecX6gLDgISsxgix+JyAMP0uT4fVzEQMP3oJSc7hCuBwnjglK7QVwUuFCkolebM+DhAqmQ55mfLHTUQSHMcU0dAkP3K8HB7XG3Lh4RxHHy0qjfzocV+Riu0JTQ5sVOnJL4Q6fvbA4H+MVFjjgTqKJLPEzCvIc7lI4BHLJHOCkMiq2ofgufrVlE410EGUgPuErnJ+/qor0KsnUMb8GfpGYaeOiH+16vPqKEBOhlatBF9fFYBFZ5/fB0LeQbbAUBf7H96/9UT9sFk42r0VFVBwlprh8vw17NSGaY7MD34dzliZ6Fe59LfLCljicGOFUEV0+sHDi3NuSHeLxk6DeeDK8mEX04KxKlbVBXEDHfxMaSiKWolAQa0TaZ/k0j/kp5IpAqEKp8VSB17qvZvGscisOnaXZiB5pYb4QVq9DPVTQ4BiOx50Kkc3v6YZA1gfjv8tvvC8c9Pvi0MOSXRi+6Sek5/mDw7JMBRGjRh+P+qcNGLyKoygfpAgGj/8dRDK7Nlt1i+iWDycu5DBDpsNuA7XjTHQprXWST5IY3by+MUJxOnBfgvTn4vqFZ2HUE4SWhU04Pa8RPS1Qb9N5ISezXvfX1ts8flgp2QNVgJLxYY0DXaCLQeAltxgx6QPQJgoEKSrIg6AYTgotPZyYsN1wikBhyWEf54jfPH0fxPOFKAsqY7kOHXg=
*/