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
i2N+Gseth98FqRyHth25t3Dcb66pVf/XXNX8WLPULDc/2lzdvL35l8CIGuuAEW1LpozoZLLGiLK53hnR88k6IzqaHGJE1+ND79apfNweZpeRdlqk3Ehxe6SCNt6CbvSQunZRJh7sEmLIS0P1T4Wdq/TlBOeDQLdNXaofRXDY2RO854WZN3WIwdhSp9zwQE2sWGNh7uAHkcVowHMR3WHjmXPVF/wgF5k5UL2+xbatgkagM3goU6y34HlB9Gzlc150edwaX69mqoZ75HL0sTXTUR7ccCe8ONJqfEvNGcXpMzqFm9CRe0LFL2I4oV8u2YOnytB+hDpBagvgvQnzxLpYCQsQjsoFbW7SWIymW3XMCKRFNwIZO4MagVhL1n0A3fPlaNo9t49Ru4d6quHwhFsvXXR1tN5FKWN+xC/Oig9UvzggpaCZAesXIQYmCjpVFdRRA0SAI4hwFDA4Xh0dPl/Z9oUDgVJ5MUCxIQTFH0brhHI9OL7+4Nr5vnjXEYAAr9aCEh31vM22r6ZYmoyBrXu5buSyaXA4ufw3JZdmJJdrp3ycv6EbXGFTeNwTrGMXUDEgG2KL051EGEElgYRi2dkOTUS/QROpNIBXQefLB6oOChnXL0z4Xwp3D6mgGF1sdqIjh9mZTCrINNj2TizejY0KHAc0L28ANLcnUTTPGqWhefZ10WwfpaP5jlE/Ph7nQvEMr573GF4beGuxNB1D
*/