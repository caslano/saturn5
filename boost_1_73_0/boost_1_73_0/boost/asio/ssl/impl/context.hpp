//
// ssl/impl/context.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2005 Voipster / Indrek dot Juhani at voipster dot com
// Copyright (c) 2005-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_IMPL_CONTEXT_HPP
#define BOOST_ASIO_SSL_IMPL_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

template <typename VerifyCallback>
void context::set_verify_callback(VerifyCallback callback)
{
  boost::system::error_code ec;
  this->set_verify_callback(callback, ec);
  boost::asio::detail::throw_error(ec, "set_verify_callback");
}

template <typename VerifyCallback>
BOOST_ASIO_SYNC_OP_VOID context::set_verify_callback(
    VerifyCallback callback, boost::system::error_code& ec)
{
  do_set_verify_callback(
      new detail::verify_callback<VerifyCallback>(callback), ec);
  BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
}

template <typename PasswordCallback>
void context::set_password_callback(PasswordCallback callback)
{
  boost::system::error_code ec;
  this->set_password_callback(callback, ec);
  boost::asio::detail::throw_error(ec, "set_password_callback");
}

template <typename PasswordCallback>
BOOST_ASIO_SYNC_OP_VOID context::set_password_callback(
    PasswordCallback callback, boost::system::error_code& ec)
{
  do_set_password_callback(
      new detail::password_callback<PasswordCallback>(callback), ec);
  BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
}

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_IMPL_CONTEXT_HPP

/* context.hpp
EYIINnN/Xi806gRzdcJL0wCXMXqTLXHWFbg1BF+2DG3LCzjrUcMdRQSf79sFdUzL0LuaRinO3QZ5qrDDsZEfapxDFdyoCqytc8OWnK/hOkOLxidFZIFHCieCHY0Dwh4tJrANEwlr40XQbhBnTxOZatrtkEWfVW2bBiPTx7snrdT3zXaxDQs0+TABk0o+d2eZMtJyIhGN2dJLSmx2Og/I1Ch4sRi+lVDDX+vqysQayICjWM5QqxSk7XQ62Hxt8/J9Y70kzcaUCY7IMgg3cJGQ0G+K50PHfn5ZzIZiPqdT263OgJiTXxfKlloCI14VEsSbXpwH1zdAoiRqWJgkbzb2uTh9lFYwTI4mI6Gj71lKWsuSQqEnZA2ZT4ZMkqqxMb3L8pZfHpxCa32f8VDDr5C5gckFkmAJnswvnRN6WpH1d/TRULH3njfqDLnHIakYyVfkgjTs5gKfAVHokPS59pD6akmbJqRjJVr2eGNGhDKhQgYLhJ0xRuBkI7qy8S7Xch7BV5KiBlhLSsPnzkY6T6V+951Iy8sXFQcuielBTd7aerhfRFM9YU4PdAPyLaO1KD7T5zP98d1mLZFqO7ffkY6pI+KLGq97fXnTqyDlXsLfevDzq8qLszeVDISNUGwiBa+KZudSdLfnVHbMYNSW
*/