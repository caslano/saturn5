//
// ssl/rfc2818_verification.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
Nld582HK5xXhudRaaO4c0nSQXO9IlDsoTbs28QPNWZHfiL/Muki/K9uJkkuQ8SP2d2WZE80ZhFX6XVmMphmavXK3VKGh+Z3rTrMO64hpc31Wt1tHzPkT8kMY+UmoHzX6Pfv7dK3hDtw98Deu9tOpHkALrh/KV2h0tEv8N1iL1I5Evv95N+UbbO5oui36fL7toXzMGbjKhsar42X4DqHZas3XO+WOplJGaawhjrT1P9+rf6V5FZq/2jSpoz3679oZutSsH67uXFvN9zlXNz32PZd+z38XboDin0mjeE1iWchJGW8ZqF7WCP0WLZMYf4H6GWlsv9bZOso/hed+TO6pXWn0UZyt+lCasdD8zdZZ+JzE7yUNzdJ0uS8FmjM8NMPxQ2INzpEzNaLXbzpcxSnck2X0mlCXi3vqmK9MPXB/hda6LFF/ci6dS/BbqiPNgXVZ+dK71Jc55TrsI9ffoA37y8UH+B2MYd2UK1bf6vSb/rfj+uo5gL9DW+iVi4NycT1ZCX3pAqFfx55zyIx1v9X289mCjtuPU1ezMnXfP4QD08Fb7T7eI5Pr/H5gW3hd+H6puoulM1rHL7XNEjFjvcZPNvOlpLVyb7rOD7w2cPJAS2iOi7/GPKNIeby2hgaAfxKaV8Rfa3jGWTPRX2/L3Ta+jXvcBw1Nx3MK00/tWNu58SI6Botu9B7UWJjJv4SvkvBgG0VVvXUfQMfsq3HvtPu0db7lqdfzB4/bq4Wv2ro4Pm5rWvnOO/slGR1bND7XjEmXiH+ztU77wOJM6lnvWN+V7+m7YjY3Pjmuc3puR696F5vIJ3paFjsvrN/14zHn6e+A/0SAnuoauNS9sam6stY+fFlWVbuxlhQD+zJNJ0vqZIvUScOsdd/QdKlfiZ2vJ23CTNqu+XyzfhvfqHWhWuca4bf65rGqekPH8w14XWU7WvyrrcV2qJlvuJIydWmc0C635mhdWmLSy9d+LDpOHT+F9jXvre23rwLXPMAll0tXW7QEMvUBGXa8/d2uv674vrO6XmpC5fogXSlvpsSfkHiIzRzMHZ+c5r7bvSQe36X6EZvbn5AwnqtheSDP0vu83TrYmuX9ZvJh+Pf560BvGyXt4PqivD0lvtWjAxMfpAPiO/ftZXs6aD0FHdyt3/hv1TZTh3s3/G0BOpDLHKUbDdSB8uabNvND8a/nlsuQ3x2epr08J3SXWbNNeyEtbX+xu0+X6v2W9jzvQ3kdt5nAubLnfkr3t/41+q1/L02sp74Llpe1pxe6SZnxBepG+XsFvgNqfLfKP/FdzHyTm6P3eWlZT8S9D/7GdvO0qTqgf5Qyu6nMZRdF08oV+sNSzvDH86fx+WZ96Rbxj7R0DJS5+568rs3VY9++81zCeG5C/jMHxOd+w8AeYIr9fUhA/uOGvgLLU3nHmfttfyX+1x1zs7itIx0HlWe0mQO+JP5X5Bljw+Zeb7O+96LEvxa3I6A687tztp74VyT+D+bbnHSrpXnDDLEBZdrab4Tmec4F9SVsXpZWDWtHOeEmDEK73kvYtMS1KFOGr0tax6PveyT0an/O68oaRetezzuy0uSR8c/IGkXrI4nvyMOVphWau8LQJFemJXGZdUaPjHH2D8aquK7Qb5OjPMaVx+ffLQnrlTXEj5b4EfKc0Tw3nbiR46Lz3YMUzmrwsw5bcU/163gtTdciXXXRPXfVOqC05SCy613Y7n5nh36jvlHXS1ZY0TpaVNFRHS2zTS0GzmtXCP806n1f1VUszeHt1VWlGSPpDMB/qfhnkk6vxPpq+vuLhWYONiVTtc7G0hnlrUMqyxqJTzb9wKdJd/+4ju/d9/YD+m1NgO6L3bp3r2Xme+cDGfb3mR4=
*/