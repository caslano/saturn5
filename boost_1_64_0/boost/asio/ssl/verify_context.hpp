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
/FQdo2+p+b9/sOslYY6083p7cqbu7YN4QSMwW/Mbrce3qHkvndRZCPDghtxqVW2SwqgasWGJW0wkbBEnpkEdQeWA43KZYzchjCMT4/kZxK0Cj8DEzS3Otuc9whbouvfk1araTlz3s4/ioK7PEucjid3nSgN9sX7W24KKpviBBiL9cMjd438i6z4PZ5ncHN/9Pd/VTQMUdXS+/uVqgU43VXvJxiaPNv/MNgSO+KIo+bGrGcQvOVd3NTLLrfRsFHnJl/n+V+61w1pStp8/UuuweFf/kXIstrqZGCfnF287gtl2ZqAql3xp1jLNSoIyWSCc81oDz3l3+VYkLionRpEdq+rhHv6voJMPnPtZuslXG9EEgiPos7Mvi11bvTIPPgSgVwytk1t0zFcHkaO/SqaI3rPheD3xLpOxlm6OFCOxAZC/OO897xWINKs58P4YOypZp0iUgPPlmeVYAEFUBnJ4HYnWwksOM2wYgNFY1q1Ek7cJzZbQj8M5vdyA1RhC37cl2d8gZCJCd+uSeFzJv7DG9Yrt0Ji9vIQupRmKsVmYJiVmW7lA2bmbiJKTng==
*/