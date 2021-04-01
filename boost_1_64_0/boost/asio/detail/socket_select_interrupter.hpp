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
Z3dG2fQy2U/vutw4OClrBKcYUjZmevwRR3usleQj0/ex3ZgwhsTM4iNjxk1Qd3W0VOOJaHBJonvNkmMMqy/JtT2rerEH3Yw36iPjiQ3oJtiBwbtfSGtAMtwgNlxxbcnlIts/+V188v7Fg7CnR4IjB1Rz/wFFQT9gnyvg27tVSp93haGzIrYV/pg3ZvW9USEOOW2ltl/z9m5GVcEyXyabVCYFU7oi90jNE3hkLBuxJ70uR3hWrXy0dDanh9amlKEd0xlaZkpmOA1KdG6qgsRPqO3kyx8BJXU2F0NmLdEQEi+31OVP8hEboZF8Id9moLIy8fCQQKKFDjKaBGz0kJk+2Jt9qOGQwqyplA0QszUGIWFTFl9m6KXhDoJXOhl15T3ZukKBqAaERVvhTMeO4kdGnVVPKxH5lIE11pZp+JF28aRpenqt775JDaJiUJWjHoyFGmWi4J19IKcSl8txHUtbCJeGc6K23zQrz7m3QSCdbOysZDoPaIGLvGohFZ9Gm1n9Q6hawd/hZtsRxYGPBAp1gdc4sF1R8eHu9isvtVphTMNXxi1qnk2Qtgne5g==
*/