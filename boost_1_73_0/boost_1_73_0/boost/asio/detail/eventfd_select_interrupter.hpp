//
// detail/eventfd_select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Roelof Naude (roelof.naude at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EVENTFD_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_EVENTFD_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_EVENTFD)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class eventfd_select_interrupter
{
public:
  // Constructor.
  BOOST_ASIO_DECL eventfd_select_interrupter();

  // Destructor.
  BOOST_ASIO_DECL ~eventfd_select_interrupter();

  // Recreate the interrupter's descriptors. Used after a fork.
  BOOST_ASIO_DECL void recreate();

  // Interrupt the select call.
  BOOST_ASIO_DECL void interrupt();

  // Reset the select interrupter. Returns true if the reset was successful.
  BOOST_ASIO_DECL bool reset();

  // Get the read descriptor to be passed to select.
  int read_descriptor() const
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
  // 64bit value will be written on the other end of the connection and this
  // descriptor will become readable.
  int read_descriptor_;

  // The write end of a connection used to interrupt the select call. A single
  // 64bit non-zero value may be written to this to wake up the select which is
  // waiting for the other end to become readable. This descriptor will only
  // differ from the read descriptor when a pipe is used.
  int write_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/eventfd_select_interrupter.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_EVENTFD)

#endif // BOOST_ASIO_DETAIL_EVENTFD_SELECT_INTERRUPTER_HPP

/* eventfd_select_interrupter.hpp
Ifnw9VKxwPf/oxBDDG76WOuc5t5ULWsACzvxUjoLtNuIUdWRYsFXWsI0gTU1u51pYK1F/MqudfQiBGtZiRhraPb9eXKzMSmfBz7skQe1ESArxHcaLUCEsS9LjVn2/q04NWMYzJVKDRc9Vna34lAfc9rLKg4GfWlW6A2jyOWSbSJPhmcCRoGeZGAYFIzUuL4OsQL1rQ/JvTsnj4HI4GpH8MI8haoBREFcHoKRXWEq400gtRm4qDS6yDQfYQn+amhGjQ3qvINguWi4yGuOjOufXJRwY6n0e94TWgpSbDRm4t9FF8EK1SLrAQZd6dnhRAsx/khWtJucocgfWwvjIflQrXAPtICsrTnOLSDm4wBuPN4e2KMzqs1ac2xwmiWiF2VkCHxSYaVr7DT6Wr9tTAcgQeCxC/lYeWYnCv3kFGtEcm7f4gWfFBUPfUxChqHvNUPokCAdIyS2FkfG4mAdWt+Z9ZqZyXD2+ZuR324Y6h6N4XlYGk40IghNSo/YwaLjop0jB2/rSxrvhZfoNd4bnaCH6VVjz4XDZAKFtR6FCCMzEgK553KrYZx6TKvcmoPC20GPf9SYT7RigbpqMI6i4T6Pxu/f09hKfvjf0LDvv6/IaA4wxqFAz2BWow3vfj5fTB4H1bhTG2Wg+50FaZYW
*/