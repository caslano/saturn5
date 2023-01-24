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
P6w488nM5/a83XDo5Xalv04acjPrxVVXg3aL+F8xhV8N6bgveH+ltg+zbkxwzJrHL7wybr2WUmULYn86/MUXD5/WJjYkpwweXqd9ju381MYtp7Tr6nr2nDbiXe0XZ87q545N0767Y2bdZ4vqHfFrqx4MjAqs067t9lLe6U8h/ohRk/bOflebeHbYQ8+9nubA7/mz/ytF0xPK5zAffpszaV757d+XD9BdfazcvPHUb+enjSlfN2nfqOoff9+78dv2t5d6G/fS+J9oT0/PPl2WeFB74ZdegyfP2aXNTMteWhfyovaja8NimDcTHPgPJ75wzWLpG+L3yk+/PiT7vSLkTG2ngD/eDH7m11s5tsipFfU3h2ZN/7FW+2R6wqTF32aXz62aeWvvO9agpAFJJ7hzc/f2bVgQG7Tn+MO798V2ffT3EXsWZqiTP+htnETxBoZ8MHrRWm2X3cHHZmz0G7F9ZPA/Nrz68trSfzjyD89oiLg38KI26UCo6uymy9qXr7/0+vJXLmifyk3/+G9LPta+mPj9trr0bK1Zt1kzp9cVR3yLYWqPI+sva688/KC8h/GC9lpmapEu5GPt/AO/Kv82N8uB/40nV6z98je91px5blL0yqe1g/8+/daRV5dqEzY9r+1/NE6rKn+56lh4Z+3N0V9klXV5LWhFbMrBXaG7tb893+HjLj2Paa+O1G3uVVuhvdG4YOjeaeu145+/
*/