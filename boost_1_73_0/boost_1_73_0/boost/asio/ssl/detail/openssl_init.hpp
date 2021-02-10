//
// ssl/detail/openssl_init.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_OPENSSL_INIT_HPP
#define BOOST_ASIO_SSL_DETAIL_OPENSSL_INIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstring>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

class openssl_init_base
  : private noncopyable
{
protected:
  // Class that performs the actual initialisation.
  class do_init;

  // Helper function to manage a do_init singleton. The static instance of the
  // openssl_init object ensures that this function is always called before
  // main, and therefore before any other threads can get started. The do_init
  // instance must be static in this function to ensure that it gets
  // initialised before any other global objects try to use it.
  BOOST_ASIO_DECL static boost::asio::detail::shared_ptr<do_init> instance();

#if !defined(SSL_OP_NO_COMPRESSION) \
  && (OPENSSL_VERSION_NUMBER >= 0x00908000L)
  // Get an empty stack of compression methods, to be used when disabling
  // compression.
  BOOST_ASIO_DECL static STACK_OF(SSL_COMP)* get_null_compression_methods();
#endif // !defined(SSL_OP_NO_COMPRESSION)
       // && (OPENSSL_VERSION_NUMBER >= 0x00908000L)
};

template <bool Do_Init = true>
class openssl_init : private openssl_init_base
{
public:
  // Constructor.
  openssl_init()
    : ref_(instance())
  {
    using namespace std; // For memmove.

    // Ensure openssl_init::instance_ is linked in.
    openssl_init* tmp = &instance_;
    memmove(&tmp, &tmp, sizeof(openssl_init*));
  }

  // Destructor.
  ~openssl_init()
  {
  }

#if !defined(SSL_OP_NO_COMPRESSION) \
  && (OPENSSL_VERSION_NUMBER >= 0x00908000L)
  using openssl_init_base::get_null_compression_methods;
#endif // !defined(SSL_OP_NO_COMPRESSION)
       // && (OPENSSL_VERSION_NUMBER >= 0x00908000L)

private:
  // Instance to force initialisation of openssl at global scope.
  static openssl_init instance_;

  // Reference to singleton do_init object to ensure that openssl does not get
  // cleaned up until the last user has finished with it.
  boost::asio::detail::shared_ptr<do_init> ref_;
};

template <bool Do_Init>
openssl_init<Do_Init> openssl_init<Do_Init>::instance_;

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ssl/detail/impl/openssl_init.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_SSL_DETAIL_OPENSSL_INIT_HPP

/* openssl_init.hpp
W1oh42IgmLwHmOW4fBKNpe2NtpLJZs1817a07dK0qmn1KM+J+8S6mNqWJye5Txa0BkcTpF1B9RpFcMtZHtcPGzjx6Uc28SnQEcsIq7BNE6Ft/qwJ6aZKnKQ+rCUVKIk7oo5WVlAN+vnzQuD2ZwkpMBf/AFBLAwQKAAAACAAtZ0pSg4t5C60AAADpAAAAIwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Jhdy5kVVQFAAG2SCRgPY+xbgJBDET7/YoRNXdSUhBpU0VJQUFBgUTtnM3dKYt92nWE+HucIGg9mvfGO9Mxo9IlbaUsGV+G7eGwxypOq3eowStpO0kFy2A865g+mIUz3vqXTf+a9tXcBist/zfTJ7mMVq8Zk/uSuq5Lx0kUv014jdnBc6PvIg1UCmZ1qUrlbn0oYCcMFpE6rD4nJNF7Hl3l6DYXYpzpJ2g+yRkLtdDAQhfQQP8545U+3QBQSwMECgAAAAgALWdKUgS+8qxEAQAAFgIAACcACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9yZWZlcmVyLmRVVAUAAbZIJGBFkMFOwzAMhu95CqsHuCx9gIKQEJch7TBtQ1y4hNZtIry4StxNe3ucbINblf7+v8/ecJw6
*/