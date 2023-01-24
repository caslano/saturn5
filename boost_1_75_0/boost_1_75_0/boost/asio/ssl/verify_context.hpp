//
// ssl/verify_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_VERIFY_CONTEXT_HPP
#define BOOST_ASIO_SSL_VERIFY_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// A simple wrapper around the X509_STORE_CTX type, used during verification of
/// a peer certificate.
/**
 * @note The verify_context does not own the underlying X509_STORE_CTX object.
 */
class verify_context
  : private noncopyable
{
public:
  /// The native handle type of the verification context.
  typedef X509_STORE_CTX* native_handle_type;

  /// Constructor.
  explicit verify_context(native_handle_type handle)
    : handle_(handle)
  {
  }

  /// Get the underlying implementation in the native type.
  /**
   * This function may be used to obtain the underlying implementation of the
   * context. This is intended to allow access to context functionality that is
   * not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return handle_;
  }

private:
  // The underlying native implementation.
  native_handle_type handle_;
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_VERIFY_CONTEXT_HPP

/* verify_context.hpp
8EaH/bX0f/3TtPrRcP9Wv/8o2f/uL3VuWrouY15mVvb8nAW5eflPFBSy+oWLFi9ZSsODQ0LDwiMmR06Z+si0qOmPRs+IiY2LT0hMSp75n6Vb+GadoSuhQ4OCE+ampqekpRay2kI2XattHsYuyddlpYuhzuEpKbl5uSkFLJuVkjc3W5cmIpHGwfQpWbkZeeCP6/BF7f/rdCd1YjQzuzBkf2ZQs1DbU9J8dYvTdPlsVl5uE+l3v3/zl58o7MWBWXUH8JTw7Qf7UTcwFHAObSE/lB+y//qD9nOpv7v1e/HbnOR8xuavuMU9sZZ4gR/KafU9jCbpXkaz1QWP9AsVzF1mRlMOsB+gCuAowHGAUwDVALUAZgAbwC0ApQUUMYAfgD9AP4ABAIMBhgOMAhgLMBFACxAGEAkwDSAOYA5AphA/H2AxQBHASoA1AOsBNgNsA9gBsAugCuCchXHcwzaD3QbQAMD8BDQBaAC6AfgDDAfQAkQDpAMsBlgJsB5gE8AWgG0AuwD2AxwFOAVwDqAOoB7gCsAtAJUVcAIMttL4Y8EMA4gGmAPAAhQDrAPYArAN4wEcB2gAUNUDrUL9iPS71t+d+rcW/mfjtxb+P/P73z5u+G8+YBC+sY/RNnTbZa/edYNUlOkiAAPE7cbgYzRQywBPSeKhPr8PzPEAyQCLAPC3vrcBnAT4DQAVzjCAKIAcmfM5AdczAyK+CQDIuMUA
*/