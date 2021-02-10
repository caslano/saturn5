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
yBgjV1S8Jj4TAnSeIx9fTgRUPjhJAnGQVqzm+KN8tcR4O/6/whis2iADedmAB4yJ9AclHGhK7CQJjZui7kqG8Gqa+rk/6afpNFIWU2B+4iLomMgPYqBxmLP9WODE6wnyhF5AQNANJ+QgtUQFqVtpd6Y99hdQSwMECgAAAAgALWdKUgROwyvyAAAAegEAACgACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcm94eTEuMC5kVVQFAAG2SCRgVY9BT4QwEIXv/RXzAxaEmyHGxBCTNTHrHvBkPHRhgCal07TDrvx7h4Iaj69973tvXskNFfhAX0uZF+opiHoYKfJH5Snw56M6ovUVvEeEY9Oc78S12YEcDOaKDlajqjXjQGHZYSrLMrWGeESIHlvTG+wSAn4RObz0ybASwM3TBQOYCI74L3MAw/KodIzzJAjNm70s7otcqUbi5OwCnel7DOhahAvyDWUYjwLTrksdqXpf7tnI+ixL8rBW8qhZaWacPIsimGV7/XY6PdeNfAaah3Gbmgg3Y+0+cZGGf3cxtWSVcZFRd0DbhR32erb8Yyxz9Q1QSwMECgAAAAgALWdKUvOmP6cSAQAA7wEAACsACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUt
*/