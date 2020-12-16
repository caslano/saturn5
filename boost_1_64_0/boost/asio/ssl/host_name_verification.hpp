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
QyrH0yoH8SqHnkECr/OR42OQZIOfAAeAnwQHgZ8Hh4OfAieD+8GzwU+Da8DPgGuVbj34GHg5+Di4GfwceJXGm3qwNbg8R4io+LU8R8X5EDy4/kxSvslaf6Y4+MLt8E1XvrOVb4ZDX4XKd72PvrJVX/1VX7mqr0LV1wDVV57qK1/1VAC+VemqwEFgHTgYbACHgldr/O9FHjkL4rLRkAJOUDnGaX0ZD+IIjz5voiP/hW8LzL/YXLGxDkwBN4PKx9mI4HIqV74KMBlc7+Arbud5G5Rvoz6vBozls0T58n3yeRl0vcG1YBhcB+aIP/7cRuUf5fPc5cq/AiwESx3P3a18BT7PXap8F4JZ4DKwv/jj38i3Kf9Un2/kz9D8TgD7qT8XnAiOBs8CJ4JFoKmv1wfr78NaXx/V+vqReD1hTzY4Hws1H4s0H4s1H/gNf3EgP/HK/xbln6n8+A1/eTv8s5X/XOU/T/nxG/7WdvjnKv885Z8v/Pid5dgO/xTln6r805Qff7ydtcN/ifJfqvyrwP7qN+NiO+U2WuvBGK33Y0HTHwbziS0saada3nXO/rA1mC9Tn9dbn9fHWb+Ur6cP3x/1eSfBdPBPzn6kneddrHyXqJyXGj5cO3zXK1+r8m0DTT/SDt/dyneP8t3r4Ctph2+Y6mW46mWEs/62Bvc/xWobaw4YBueCObbfjBc45b/BZ7y4X8eLh3ScfxgcDH5Qx/lHdHx/Nyh1GVwHvgcsU7pq8H1gPfh+sAn8ALhV41UO1leD5VijcqxTOd6qcmxUOcpUjnKVo0LlWA+WKV01WKVyVKscG1QO4o0cR9uR4w2V4+8qB4QiR09wBBgCp4BJ4AwwGVwHpoBlSlcNpoH1YA+wCUwHt2q8lquuIVLvfcr1d1qPfg/2Av8A9gVfdc7fbgjOxwLNxyLNx2LV5wrV5wWqzyWqz6WqzwvBMqWrBi9SfZaoPpeDWzVe5WD9K1iOBpWjSeWIqBxbVY5mlaNF5bhS5bgKLFO6avBqleMaleNalQMXn1dvD5Zju8pxs8qxQ+W4Q+W4ReV4h8pxq8qxEyxTumrwdpXjnSrHLpWDeCNHWztysBggcuSAeWB/rV9DtH7lav0aoPUrT+tXPlimdNXgQK1fg7R+DQa3arzWL9ZYgvuNc7TfmKX9xmwwR/1qq4w1jGBbZaXQtXbSFsrSBrGzcNoOyr/ZDsppGyj/2zZQumL/5LTtE7ftk4c2YfMEdxyXU4c+cVW4nbj9uGdxJ3GFm7F5gmvG7cYdwJ3A5dTDgyvH7cDtxR3GpTSkWFNxa3HbcXtwz+JO4gobU6xFuEbc3bjHcEdx6VfAg1uFa8XtwR3CvYrLa0qxiptO2005/Xf67/Tf/+7fv+z7f/v6Afn8v/vf/+8ZZ5k7SpgCyF+63tvzGu5V+7uSS2T/cUFpqXwf5LwWNOhOUOUZZu67eF78L5q7OaGvNOcSDP2Q+Ld84v8Vft2L5yzDFY7vA49J/DOyp1uYZrnuuHxZ4n6M38Q18p/59jD9UrknA7/jrh+NzzL8yeb+6xPi/641kf3RXvjPGSf3xQj+DYbVev9g3zGspYJHbH+nzgKkZt17qbmPot27LNEZYaozvYuCvBHW6DqP84TaBLgJ10/3S16jDMOronvj+r3mvJWrpCyd3xuKPq6Ts4ZcBxIvS+U9w3wXNF/8KY4zR5pMfM9ceQaZO7AmiL+WG5Ccd15qHrVMzxKaCmu549v2t6LHNeEO7+6+IKbP1avc+iwmnDyhJ8lT/O5mnLnfMeF8wY4U7/eRH7DbQYAO6yo2RiAJ0p/ypeA3+hIW1RXxnft+0s5PekJ+sl1ntCRd1/mRI6leewfvgv+Qf14=
*/