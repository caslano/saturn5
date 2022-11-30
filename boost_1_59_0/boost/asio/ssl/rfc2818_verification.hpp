//
// ssl/rfc2818_verification.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_RFC2818_VERIFICATION_HPP
#define BOOST_ASIO_SSL_RFC2818_VERIFICATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_DEPRECATED)

#include <string>
#include <boost/asio/ssl/detail/openssl_types.hpp>
#include <boost/asio/ssl/verify_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// (Deprecated. Use ssl::host_name_verification.) Verifies a certificate
/// against a hostname according to the rules described in RFC 2818.
/**
 * @par Example
 * The following example shows how to synchronously open a secure connection to
 * a given host name:
 * @code
 * using boost::asio::ip::tcp;
 * namespace ssl = boost::asio::ssl;
 * typedef ssl::stream<tcp::socket> ssl_socket;
 *
 * // Create a context that uses the default paths for finding CA certificates.
 * ssl::context ctx(ssl::context::sslv23);
 * ctx.set_default_verify_paths();
 *
 * // Open a socket and connect it to the remote host.
 * boost::asio::io_context io_context;
 * ssl_socket sock(io_context, ctx);
 * tcp::resolver resolver(io_context);
 * tcp::resolver::query query("host.name", "https");
 * boost::asio::connect(sock.lowest_layer(), resolver.resolve(query));
 * sock.lowest_layer().set_option(tcp::no_delay(true));
 *
 * // Perform SSL handshake and verify the remote host's certificate.
 * sock.set_verify_mode(ssl::verify_peer);
 * sock.set_verify_callback(ssl::rfc2818_verification("host.name"));
 * sock.handshake(ssl_socket::client);
 *
 * // ... read and write as normal ...
 * @endcode
 */
class rfc2818_verification
{
public:
  /// The type of the function object's result.
  typedef bool result_type;

  /// Constructor.
  explicit rfc2818_verification(const std::string& host)
    : host_(host)
  {
  }

  /// Perform certificate verification.
  BOOST_ASIO_DECL bool operator()(bool preverified, verify_context& ctx) const;

private:
  // Helper function to check a host name against a pattern.
  BOOST_ASIO_DECL static bool match_pattern(const char* pattern,
      std::size_t pattern_length, const char* host);

  // Helper function to check a host name against an IPv4 address
  // The host name to be checked.
  std::string host_;
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ssl/impl/rfc2818_verification.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

#endif // BOOST_ASIO_SSL_RFC2818_VERIFICATION_HPP

/* rfc2818_verification.hpp
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
*/