//
// ssl/detail/engine.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

  // Construct a new engine for an existing native SSL implementation.
  BOOST_ASIO_DECL explicit engine(SSL* ssl_impl);

#if defined(BOOST_ASIO_HAS_MOVE)
  // Move construct from another engine.
  BOOST_ASIO_DECL engine(engine&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE)

  // Destructor.
  BOOST_ASIO_DECL ~engine();

#if defined(BOOST_ASIO_HAS_MOVE)
  // Move assign from another engine.
  BOOST_ASIO_DECL engine& operator=(engine&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE)

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