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
b3B0cy9wcm94eXR1bm5lbC5kVVQFAAG2SCRgZVC7bsMwDNz1FRxboMoHZDUKZCiSAjHQWbUJy6gsKiIFN39f2paLPiZR5PHueC8UhyOkTJ93KTFiMFdPWbRlThjSES4JsxME8ZnK4MFFOLXt67YC2w48FB7jAM3lfH5u2kdzRbQuMFVm0yjDQPm+/6215s1j/MM2MhTGHqxd/08qqi1KMlKEeQwBJveB0JUcduVqy4jHjeQArZZ16pL2XOcX5sn1qCTiYcH+UK2uIeOtIIt66s1SjxlZsU7gmxxcCDQz9DrrBDpSFX2FVkjGiTSppPlBLNM75tWqmV0UXkG/PGvnYExLwEVtIvM/P5woMoJHtZ4Z5iWx9Xg9h3HVpSKpyA4xGp+mtxPaatDW8cF8AVBLAwQKAAAACAAtZ0pSaYpjOEsBAAAkAgAAJgAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3B1YmtleS5kVVQFAAG2SCRgbY9Ra9xADITf91fMYwN3pk0f2h6lcARCCqE9cP/AniPbIuvVdiVf6n9f2U1LCH2TxMzom3vJwwFlPj/SEo7V588+fQmnKiadJD2gvf1xQntzCneUiq/tHU7zOXEHV6LnRMhxonATjQapywHaW4F2BXG2
*/