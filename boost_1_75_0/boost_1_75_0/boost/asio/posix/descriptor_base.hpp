//
// posix/descriptor_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP
#define BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/io_control.hpp>
#include <boost/asio/detail/socket_option.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace posix {

/// The descriptor_base class is used as a base for the descriptor class as a
/// place to define the associated IO control commands.
class descriptor_base
{
public:
  /// Wait types.
  /**
   * For use with descriptor::wait() and descriptor::async_wait().
   */
  enum wait_type
  {
    /// Wait for a descriptor to become ready to read.
    wait_read,

    /// Wait for a descriptor to become ready to write.
    wait_write,

    /// Wait for a descriptor to have error conditions pending.
    wait_error
  };

  /// IO control command to get the amount of data that can be read without
  /// blocking.
  /**
   * Implements the FIONREAD IO control command.
   *
   * @par Example
   * @code
   * boost::asio::posix::stream_descriptor descriptor(my_context);
   * ...
   * boost::asio::descriptor_base::bytes_readable command(true);
   * descriptor.io_control(command);
   * std::size_t bytes_readable = command.get();
   * @endcode
   *
   * @par Concepts:
   * IoControlCommand.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined bytes_readable;
#else
  typedef boost::asio::detail::io_control::bytes_readable bytes_readable;
#endif

protected:
  /// Protected destructor to prevent deletion through this type.
  ~descriptor_base()
  {
  }
};

} // namespace posix
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP

/* descriptor_base.hpp
a9+I+jTWJvSeTSPTO9j1Ib9J1IJa0ziK2HyBCAs9OBrHNwd83K8CCYkpI8h5OZ8qGONN1wz6Cp8k7ElekRHO1nXkYcLXbocgQ06H6vY/JhUhQUOmjRJEqKxJhMynWudi4C84wWyJhx+dEnmo/gW7vXVYtCE+Yh/3PHnkdx2PFQrBTxkaGabhKT2u+RYvgrCSQ9Q+36NpxafGjLM3fCD1vOco4Zja+RKl0M2RHwbTa5omQt5kEg49nudEyZk2PGvmI0xL/uZl9cYe0RRfDEPqbE1ycUd1yTgZncPhO9OUws9wjZb+Rrl0VFVyWK/HnRNbkKkUf1FePYBE+U09s/x3APWDxMmTML6ib+UkqEmtvp/wQ1J+48jPyOt9DRcZRlOEiDSMifhZvZAn6iKKNkPAmyEgtIYhMsK1vc7Zl+YTowIoqDCVxIED6KgykSehflMnl0ZTLCQaEWq0JOBvX3iexJccQ5KL48vobJu2Y2Fu6rwKgK19ur/0JzTItL/SMkpJp/1TcB4blmDeeqK1aT42IVpxwmC0OT5LTb3dTibY+Fom0CXMsP8pzLCfIzPsqBN/fYY9BuKMrLlcvRYbgOQYXANOYO+pfln0hpltjecAlKSXxV6edPfiMMDjF1EZXgsvk4tTRnm76VTJ/QG+SFRLk2vgurPqRLoewdl1RM1lmovLkbgG59m1C2GASzK7BgqkxGKGUWVkf9NZARd4
*/