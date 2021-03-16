//
// ssl/stream_base.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_STREAM_BASE_HPP
#define BOOST_ASIO_SSL_STREAM_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// The stream_base class is used as a base for the boost::asio::ssl::stream
/// class template so that we have a common place to define various enums.
class stream_base
{
public:
  /// Different handshake types.
  enum handshake_type
  {
    /// Perform handshaking as a client.
    client,

    /// Perform handshaking as a server.
    server
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~stream_base()
  {
  }
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_STREAM_BASE_HPP

/* stream_base.hpp
Tr3LqW1xq6Xv3lNxJZtc8ACHn3gGL9lLaeshOU3xfipX8rznC2GQ/n6KmqoHzDgz8aXvaKCnahVXx6oi5XQM+NTilj5d2LK6KbUk7e3qT1VVes8n99HXz2blSVYHHajMlcAkSVnORD3F2OIWZXROm/0EnEdcknJP3Bwbo0aB3gwk6pOZ95bdJs/zyaB3ajXqdeLpjtJDNnN9slF5nt0WH+CTgTB5dht3rd8pAdbqq+YsYHOBLQC2CFgHsBuB3Qc=
*/