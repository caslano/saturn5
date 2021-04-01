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
5hPLtyfNYZ9fhQW7a0rhXh7zSTIG36fT1y2ugv7kv+Hmjm5v0+9cQ8HVFQf4YA/CLbcLLY8STmV3mczTSlb3POLKOgy3peFIBnqMtaPTxsx0V6/ypN3d6+3kbsEgOF1ReMXJeJDQcQPXT0hSiiO4wnUlqEotb0OkGqt6Pin0cq8dt9pg/GQ/vrvE/ORJZG0gdQA4Z/wH2ra7yArhe/oEvJh9suDRynLZWaoegWP4dZK4MXRg+8LfzAEFmss6l/2QAcv7vgwj5At5tcR/OeK5rgIBTFUDdbbpr2IiceSTESwbxYJxud7EhWMW8x9Xc6JCQtkTL0RbuZ0HcB3jehJt4NjGM46WtGIuttzk+FctjmVY9d7C3rbs8q4jRvI2zdC4hQPR9GCphjdidCu7kdfQ4hcTAV2SriQRj/o8kl8scxZ7PTghOMJDjacTSfMfehkXAQivM85um3IMCn1POAN22h2oQSHC9uxf3zz8gFNLrKPiVkA9qGV+9GSar3kIaPANyDu8CeFu75xx2VgUAqCL68JEAp1JMeujut4HdfbghwgPNprjRS3julTo/A==
*/