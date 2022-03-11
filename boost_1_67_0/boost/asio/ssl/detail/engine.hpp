//
// ssl/detail/engine.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_ENGINE_HPP
#define BOOST_ASIO_SSL_DETAIL_ENGINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/static_mutex.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>
#include <boost/asio/ssl/detail/verify_callback.hpp>
#include <boost/asio/ssl/stream_base.hpp>
#include <boost/asio/ssl/verify_mode.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

class engine
{
public:
  enum want
  {
    // Returned by functions to indicate that the engine wants input. The input
    // buffer should be updated to point to the data. The engine then needs to
    // be called again to retry the operation.
    want_input_and_retry = -2,

    // Returned by functions to indicate that the engine wants to write output.
    // The output buffer points to the data to be written. The engine then
    // needs to be called again to retry the operation.
    want_output_and_retry = -1,

    // Returned by functions to indicate that the engine doesn't need input or
    // output.
    want_nothing = 0,

    // Returned by functions to indicate that the engine wants to write output.
    // The output buffer points to the data to be written. After that the
    // operation is complete, and the engine does not need to be called again.
    want_output = 1
  };

  // Construct a new engine for the specified context.
  BOOST_ASIO_DECL explicit engine(SSL_CTX* context);

  // Destructor.
  BOOST_ASIO_DECL ~engine();

  // Get the underlying implementation in the native type.
  BOOST_ASIO_DECL SSL* native_handle();

  // Set the peer verification mode.
  BOOST_ASIO_DECL boost::system::error_code set_verify_mode(
      verify_mode v, boost::system::error_code& ec);

  // Set the peer verification depth.
  BOOST_ASIO_DECL boost::system::error_code set_verify_depth(
      int depth, boost::system::error_code& ec);

  // Set a peer certificate verification callback.
  BOOST_ASIO_DECL boost::system::error_code set_verify_callback(
      verify_callback_base* callback, boost::system::error_code& ec);

  // Perform an SSL handshake using either SSL_connect (client-side) or
  // SSL_accept (server-side).
  BOOST_ASIO_DECL want handshake(
      stream_base::handshake_type type, boost::system::error_code& ec);

  // Perform a graceful shutdown of the SSL session.
  BOOST_ASIO_DECL want shutdown(boost::system::error_code& ec);

  // Write bytes to the SSL session.
  BOOST_ASIO_DECL want write(const boost::asio::const_buffer& data,
      boost::system::error_code& ec, std::size_t& bytes_transferred);

  // Read bytes from the SSL session.
  BOOST_ASIO_DECL want read(const boost::asio::mutable_buffer& data,
      boost::system::error_code& ec, std::size_t& bytes_transferred);

  // Get output data to be written to the transport.
  BOOST_ASIO_DECL boost::asio::mutable_buffer get_output(
      const boost::asio::mutable_buffer& data);

  // Put input data that was read from the transport.
  BOOST_ASIO_DECL boost::asio::const_buffer put_input(
      const boost::asio::const_buffer& data);

  // Map an error::eof code returned by the underlying transport according to
  // the type and state of the SSL session. Returns a const reference to the
  // error code object, suitable for passing to a completion handler.
  BOOST_ASIO_DECL const boost::system::error_code& map_error_code(
      boost::system::error_code& ec) const;

private:
  // Disallow copying and assignment.
  engine(const engine&);
  engine& operator=(const engine&);

  // Callback used when the SSL implementation wants to verify a certificate.
  BOOST_ASIO_DECL static int verify_callback_function(
      int preverified, X509_STORE_CTX* ctx);

#if (OPENSSL_VERSION_NUMBER < 0x10000000L)
  // The SSL_accept function may not be thread safe. This mutex is used to
  // protect all calls to the SSL_accept function.
  BOOST_ASIO_DECL static boost::asio::detail::static_mutex& accept_mutex();
#endif // (OPENSSL_VERSION_NUMBER < 0x10000000L)

  // Perform one operation. Returns >= 0 on success or error, want_read if the
  // operation needs more input, or want_write if it needs to write some output
  // before the operation can complete.
  BOOST_ASIO_DECL want perform(int (engine::* op)(void*, std::size_t),
      void* data, std::size_t length, boost::system::error_code& ec,
      std::size_t* bytes_transferred);

  // Adapt the SSL_accept function to the signature needed for perform().
  BOOST_ASIO_DECL int do_accept(void*, std::size_t);

  // Adapt the SSL_connect function to the signature needed for perform().
  BOOST_ASIO_DECL int do_connect(void*, std::size_t);

  // Adapt the SSL_shutdown function to the signature needed for perform().
  BOOST_ASIO_DECL int do_shutdown(void*, std::size_t);

  // Adapt the SSL_read function to the signature needed for perform().
  BOOST_ASIO_DECL int do_read(void* data, std::size_t length);

  // Adapt the SSL_write function to the signature needed for perform().
  BOOST_ASIO_DECL int do_write(void* data, std::size_t length);

  SSL* ssl_;
  BIO* ext_bio_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ssl/detail/impl/engine.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_SSL_DETAIL_ENGINE_HPP

/* engine.hpp
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
*/