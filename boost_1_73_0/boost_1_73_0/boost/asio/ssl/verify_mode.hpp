//
// ssl/verify_mode.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_VERIFY_MODE_HPP
#define BOOST_ASIO_SSL_VERIFY_MODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// Bitmask type for peer verification.
/**
 * Possible values are:
 *
 * @li @ref verify_none
 * @li @ref verify_peer
 * @li @ref verify_fail_if_no_peer_cert
 * @li @ref verify_client_once
 */
typedef int verify_mode;

#if defined(GENERATING_DOCUMENTATION)
/// No verification.
const int verify_none = implementation_defined;

/// Verify the peer.
const int verify_peer = implementation_defined;

/// Fail verification if the peer has no certificate. Ignored unless
/// @ref verify_peer is set.
const int verify_fail_if_no_peer_cert = implementation_defined;

/// Do not request client certificate on renegotiation. Ignored unless
/// @ref verify_peer is set.
const int verify_client_once = implementation_defined;
#else
const int verify_none = SSL_VERIFY_NONE;
const int verify_peer = SSL_VERIFY_PEER;
const int verify_fail_if_no_peer_cert = SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
const int verify_client_once = SSL_VERIFY_CLIENT_ONCE;
#endif

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_VERIFY_MODE_HPP

/* verify_mode.hpp
Mez3+/A/Q4NjSvKkWGSGCUqVCz/QutaV6K+BM2xkhVKJ1X+ENaEJ4Wv/5y7FWDJ8mpUeXHahGhOMJ9KdSwgpqkEy4YlTwpk2oSe8Obq7x4fm/afm7Q7dXBOiGU3FdCVyfJmicRdTWkC/rMbOtsQXeH2Vab2FUvnieP9K7qBeKqpyHl6TDpRXSE/NYqj0c+bqSPgmHmBjtLAZXrx5/r76n+WKxOeN2VG9VOL86P3jEDl734hOyuL9gstUx2u8a66bj5CKkYeR6vZnhWFTSv1r//dCuW3vm6vwG1BLAwQKAAAACAAtZ0pSwiKkGJcEAADlCwAAJQAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3F1b3RlLmRVVAUAAbZIJGDNVmFrIzcQ/a5fMdyXOG1iCkc5zpRCe5fQQKG5JKUUDoK8q7VVa6U9SRuf/33fSCvvbpwL/VgIJpZGM++9eSP5d2c3K/rSu6jE/db5uKJP4jdluhXdK1tT5dpW2noRzik6Cso/KU9r1TivKHppQ6O8uPUuusqZsKLrh1u6x4f4IKPaOH9YURM7CvgQl5eXQqSs0pL0a40E/lBKcP64VeRVCzApkfMp11B2SZ8YZokPSKFEUDbSr1fXf9xdpdMFE0W5U4E6IytF
*/