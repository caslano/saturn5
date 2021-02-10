//
// detail/socket_select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOCKET_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_SOCKET_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#if defined(BOOST_ASIO_WINDOWS) \
  || defined(__CYGWIN__) \
  || defined(__SYMBIAN32__)

#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class socket_select_interrupter
{
public:
  // Constructor.
  BOOST_ASIO_DECL socket_select_interrupter();

  // Destructor.
  BOOST_ASIO_DECL ~socket_select_interrupter();

  // Recreate the interrupter's descriptors. Used after a fork.
  BOOST_ASIO_DECL void recreate();

  // Interrupt the select call.
  BOOST_ASIO_DECL void interrupt();

  // Reset the select interrupter. Returns true if the reset was successful.
  BOOST_ASIO_DECL bool reset();

  // Get the read descriptor to be passed to select.
  socket_type read_descriptor() const
  {
    return read_descriptor_;
  }

private:
  // Open the descriptors. Throws on error.
  BOOST_ASIO_DECL void open_descriptors();

  // Close the descriptors.
  BOOST_ASIO_DECL void close_descriptors();

  // The read end of a connection used to interrupt the select call. This file
  // descriptor is passed to select such that when it is time to stop, a single
  // byte will be written on the other end of the connection and this
  // descriptor will become readable.
  socket_type read_descriptor_;

  // The write end of a connection used to interrupt the select call. A single
  // byte may be written to this to wake up the select which is waiting for the
  // other end to become readable.
  socket_type write_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/socket_select_interrupter.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)
       // || defined(__CYGWIN__)
       // || defined(__SYMBIAN32__)

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_SOCKET_SELECT_INTERRUPTER_HPP

/* socket_select_interrupter.hpp
QoOWC3PHFALFuUix1MiBaeCoUyXmdBAlmAxhIXKE3mg8G4TnHtxlIs0I40HWoDNZ5xwydougMEVxu4aomDIgF9RN2FxoQ3i1EbLsEDWCQVVogrDkLNcS2C0TOZsTDTOQGVPpj91uWquclHe5THU3fb56JzPF5hYzUlCwB5CVASOh1uiBrfOgkFws7E5WULKq57nQmbeVQkQl70oFGvOcoKhNoF5LRphsnPFsFVSkVhi7aVlqy3SXyeJVIVlIIItalURDFlANl2SwB3XJUTW1zaWfGTZuNtb+ZSRbrRxkSUrA9ScwmLgwZ1poD64H8cVoGsO1H0V+GM9g9Bn8cEZYl4OwT/MWxKQA7yuFmpgViKLKBfKG8O2Wo9G0hn449s8DcPcfe9PoKjkbhH40S/qDaLUZoJ3mkdt2SN+VZBz6tn7SODyKL4JofVwoslZn5AFvzHGMYqVeSFUkBfuONpWIMm25w82pQye3oR36l0FC5FEQxq/4X5Z2UgtDMijOa46t/+90GOdJWmsjiySVRUE3aNEcxjQKAtsYsXIdoCkP6di36XFApgRfg9409s+u6OffJU9G06gXrImXWHaq3KW/tygrtsR/Vrtw+itzPxgHYX8C+49rm1cUbV1eUcWXIDrz48HQab+8j2H0wpgW
*/