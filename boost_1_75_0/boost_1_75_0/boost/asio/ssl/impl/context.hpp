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
rH372VXTYfiru32WJFyX9dOFqvTROaLsyuxBHx2bxn/10DKCf3n8K1IM/q+HrYE40mD7c8n238Pt2u22VCSupy1GJMz+vEIVxfGb21dhHbs/zp3wUY/0w9mG2Fdvnck6Sxzet6dAERT18Nkw7Nfb/pTVT4k4j9UDval4yiqwXoNz/ud9Wg/vNLCPH/jRUQbZr3oW1qUPsevQrWffNbSvvU3hnn0Kr/1dX/X/j9rg6N9w++ri0F89cL7/Oh6ssYvC1kHYu5t9pVYkDsanrTZY7zI4B0057uEOoYr97fj/Oor/fgyhKuxsi7Ij4u9RTlFBdoZE2r3YH8dM+EuEgpVds1z/np2UXehs37tNqpK6RCRUjqXTKOopR/GuvCfvw/vyfrw/H8AH8kF8MF+HJzzHS7zGh/CN+VA+jA/nI/loPoaP5eP4eD6BT+ST+WH8SD6FH8dP4lP5NH42P49fxKfzK/gMPpPPl+5KBRIlu8qecqBMZE7W5BC5sRwpR8vxcoKcKA+T0+TZ8jx5kZwpZ8nZ8iH5iJwj58t35QL5ieyqeCr+SoASqAQpdZTGSkslWolREpREJUUZp6QqK5Qdyj7lqvKnIqm71ddaRf2okWOcM3KNy0aeccPIN+4aBcYT47lBma6mp+ljMqZqRpgdzVgzzow3J5tZ5jUz37xrFphPzOfmK5PKczxniyKupDWJJNEkhsSS4+QVcaEb0vdp
*/