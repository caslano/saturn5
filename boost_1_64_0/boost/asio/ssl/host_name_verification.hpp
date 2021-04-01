//
// ssl/host_name_verification.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_HOST_NAME_VERIFICATION_HPP
#define BOOST_ASIO_SSL_HOST_NAME_VERIFICATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <string>
#include <boost/asio/ssl/detail/openssl_types.hpp>
#include <boost/asio/ssl/verify_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// Verifies a certificate against a host_name according to the rules described
/// in RFC 6125.
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
 * sock.set_verify_callback(ssl::host_name_verification("host.name"));
 * sock.handshake(ssl_socket::client);
 *
 * // ... read and write as normal ...
 * @endcode
 */
class host_name_verification
{
public:
  /// The type of the function object's result.
  typedef bool result_type;

  /// Constructor.
  explicit host_name_verification(const std::string& host)
    : host_(host)
  {
  }

  /// Perform certificate verification.
  BOOST_ASIO_DECL bool operator()(bool preverified, verify_context& ctx) const;

private:
  // Helper function to check a host name against an IPv4 address
  // The host name to be checked.
  std::string host_;
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ssl/impl/host_name_verification.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_SSL_HOST_NAME_VERIFICATION_HPP

/* host_name_verification.hpp
HfzJo4xLq5srwxJBx/j83MogbtrUITcLDohv642T96s+0fP8AIQjfzhWYAoYApo922hqGWWULA3yp8uS9huitIJEXa5d+yT/2ZM8ADkmxsRzRGz6j+zl7AjPjv923PiQEWTcg0AM0ZcOnmpi/uncl4HI7oR3YMAuhMtqZNkDFp1HbUdKNROmpN6BapU/qN0tY2aWrhrvivyDLSo6OH2EOqg3qmnEZbEtMWealQ8tddxC8ottyEDnI4xdOtkAE3eaHwK8O9Zy4T4m3zxRnsgHArX3HqvsOi0D222K7GIt5OH6bWm9F/H8Jte7R5E/mR7NhUH9OQC6xXi4QNFz6VLk/q2CHhmQTJ0nuzxciN5oP+unqoXldJ6GZ5F7Cs1/jvDhcNvS30njwvQ7hSV3vl+l7oq+PZNB4UX79xaJNNZhbFypeEVuIt9+xjpWed5kHiCxDawZw0RHDIsK/UQWknAJXe+KUPEtYJd8Bd63OMH0bjuUKsaw5ppF3iTrXF6gvimq0e9Qb76R3+pbn04oUSLpNEV0ZHciSky1J3/BWFqYr31TM1KGynCkQybqqw==
*/