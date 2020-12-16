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
veodWa37wNfo/PCNaqNxLbiWyrPhnhRrB445zAbnLxuau3TPW3rnLP+G885VBsxTeuYlj86cpMxHuuYinfOQzjlIXKFz3tF/znEzzjXP6Jlj9M4veucWXfOKzCc2PJcYnUesfw5xDn7mDs28YZ1NG50nZI7QOTfY+DlB73xg0FygZ/5P5/7c837M+Xnn+xoxz1ffvN4YM5/3+c/ljcI55+68c3au+Trm6gi7JzEvl7gSV+JKXIkrcSWur9/1hXz/z14w/yJ7AuAIv//tb/ixvS2Prb0VODkrj1tuzw/0i+wfHTp+3Agx4FBTXYIi9Nk1bEMM7yW8MceCxk4Y3/Wyl1D5iK2PNZF7Zr+hskX33f5Y6M4VvtEOvu7sLsrR/faLuT+etCYPYH93p1yzB3k6cb6Gs/dmG1s37cPzCKfGsc+SdLM/UdKtOuLNnkVNp1tHPN/+cl2mNsIqcFcjo8J8p4xkrkOsSbj3Wl6E3M1eS+XpGtmHyyUc5ixDqYRPlP2sb8nTFxuZTZewKVZkP/pbbYi/R1ge8+LSj5+auVTisPLK5quNO5N3Sacr33m6H/0D3Ze0D7eCfO8PyHd1cL6Vp78733C00j3D2f3t8B879/GacxhnSdgI9Yese8R/rOxLPi5L9vTWzCmriiTBnDtpJnR1Ug9TRTAlFRVCFd3/O7C/e59xuvh/Tv1tImnNkPgXl/NjymiG0PRQP/YQxN9S7LvtTkKeFE5me+JKG2R04b+v9t06KM00aJ7qDk3y1PTUZunJ/dNTUyP1+6FMnNJH4lwK/Y9t+paVJs6xMTQboJnYG5pjap8zOvhjaJ6FJkPSVntNhGaa0jjr1fbujatXV/d316sin3plzjk0ifY57XCX41YWkK4B3no1t+zyoDql9L0d4ZUl1Vq2oyXcfRblePF/w1EHid1RroMl/DwJ3ysprYQg2medIOElrvZ3VpfGyWnygPrbX5arP5L8uNrkAd3v/QaRdFW8DtnVuWUnRkhnz15YVTL7ck9frfJTnjPr7af/LTSXqUwjPIP03AASP8n2/51yvEHOiizWPmBZgTyvBr/wFhnePkJXq3QdSBc9anl1jWXOD3wsdJtDs0JNPfv62e/I3IqkO/Qqo0WWORNmsmva9n8lnpbqD1kThC/bsdd/noyXERsk8+D5QHgeCF0cSoUvQodcqsM0C6B5T2geCZWHmrniqiAbkbgqoDsodA+FKkLJEtfjbURPTUmFw+bJMklT19A6xkK5Z2T6IilfJ2NhKflbkcb+W3ssnMRY2N5/LOystNuh/Wem3bfU3sLxNOBuehfL8u1flGcfPB/ZPC1rt/r1L9CIkvmKLGiOWX5lbP8SSWffZprO5XfKoO2XTlkD0DF7QRZx9G547LbbzlkF2naqqqSdVPqM5Yu9Y7nQ1oLUSe5H6uSgzC0iZ/qgvLD/pRj/p1G/285metQecDvd43wDceee7GmDZkwKaIPKc5KxFTpN/MmBbXK0iwe/4Ulz9IPyWNMOCiU817TD3KifcFq3+LO97Vb7zTMk/ALxTzD8nfBHz06CEt4OXKrxZ5nxWdIzk7fX6Fk+oRknY+afm1E/WlBO7e26Nd1hP8ZbXyZQV6bFoZ9J3nVONvVF/OTT1ffm+9SfU731J6aflrxoP+2qU1JHzo3002q7brvWkXst7ad96ghWR+dyRKtsdnk1D5xZWn5xOU8IrDMax8nBdcTQ5Jt+5qD4V1KHQ7HlbN59XhOa75GHJtE+W+51jNg14jLJs3L0/ewtoSm3WnCnh33ulyKYxv335P5q6cPSaTOjWmrfMJeuoaN/Hxa59zplfUFcdsJSMy8aaMq5Ue/48p7iLkOhJe1qX0k=
*/