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
BAEPo1NiUV4+McoE0WZlomWe0PgxAQ/C8jjJu9I288ZXgihGOWiH2FH8hxM1B88eX+oKDh6PPgq6qexEwILuriHaUhdfj23HQGFhA5bheyajowFWWHvJM/05cH/FFnOK1O4X/RetA7/jPNPbsL7mlOO5ZPN9C5LQG60xGJ/AzAWMr6neSNzNiJmeac+WU5o6z38XwnH+97R8D5htHGD/3cK0rD5N6ZMPdZJJl5ww6f74ipp0
*/