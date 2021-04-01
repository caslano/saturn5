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
fRYC/idWAfHn5LxZOSdbE2n3jWbgEIIuOKGeJueRfV35eKsYF0DYuoRUzsb/Ex6dJZs0wRalkWEhl0ni2nYzaz5LTobbGGSxEn7928Y7EXtwtEE4nIgidHqUbVjZCRw6IK0CGokzvwff3Hc4F7FnJkdLT0WGFUwEUZdhNVPGRGdY/zGeZRmxScMkmB8uQ8LIjSJ+a3SEzbEIHAew77RFuQXD9RjzJ6hv78ngGcy7mmvzOMZnblYcFB9103Cvt4tVDwSdAwhK5DHeQkprRdyFk5gmH52kgOaDK+vQ2LBV87JnfZiuua1CIDT+6DuK5PNbpUfpuUcLplCVxVHQ1IgPDXnFcfezldTJrHshJc4R1Nk/cNYMLqHRs/6FOXi9heQlqkkXLwskHvSzqpC2WHQjgPdymDMcWEvpK6HjarNrdUix9gmf39WYFeq+uOJ62+ZGULrZPhzvP85nwVcTM/gaIknZRM7DWpIbl/ODQVAOCd6mnOpBvcJFJxaVXj4evdXyEus2WkT6pfObIt/9B83bTOS8zqHfIOIGa296mpaumdqDYLZzzAl5vhMITw==
*/