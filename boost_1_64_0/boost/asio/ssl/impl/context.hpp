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
iXjq/jeJ92iXokzcswB9GhRif+6v9Yy7MFF0yyytrlb1ofp34F7pvc3+OfSTe8HbmBio79ryyhKrnVEv8icj7LOpkuLaYvVtO+LN+za+lxX6HhaW/qTaUvIwjS+nHfRpsdWnsHSz5qxTSzs6tXzKOvnaaH80v5kEDSQOG4Sx1KoTxmQbfWiTHwv/RKUf5E1+OUYORtjg36K4ff8WDuOeuU3q+X18AvJM0uOAu1BJuYMDy19eWVNaDXnHNqFMuuovxRI+pW3Br0M7UQZa8Dp+pYR/p9VoMbbXiYXgWSk8H2rXcNwsU+kM1ZIh4922tqSqbnVhZd2GwuIKiBvH3VuEt1of11n/Edq4JOn7co8xa5DsCbPBoxeVcnmQaxG5qVpvGSNwTslFKTvrF8I4EKqd8fpvuT7FJ6nx0dSWCTH4ER4c7GMzoUtjkqUtawprqqprS0s4RlrakjL9Q/Y/sEfpYu4fZ1imnewf14EeAW+LpUzi40WuZed77xFZFh9vorKrVyVcp+Xj1zJWs41PCs8KbZp/rMa9V0f8wvSMGzNEjdVqT6vzvfdd5v11Y83+mwaAxuAm0TPERkeYZEWFpuxlWVz745KxPk8zL4IWwzZusOQF00ecQ/uSP7bL7dvQz7q38M1DYD+W8niqPM5jB/nHqHoZkNx+vbQ3tqEh5Pg6KIX4KHhb7com47Nj+SgzWsILEe6TrIer1Pi8WcIRCKtnFNx+c5xT8pkSXoxwlJJHvF/e8uyhm/YkibuQYXhvknCcloj7uNtQ6Xv7e+8/elzZKzJ2UGLgNaLT92bxJn9VPn3gh0jyl/Pmfd9Z30NoCy7f/Uqypb7rasoc65r8QxyvGYxXthI/rHO20t61/TB7RjYTGgvaC+VaLPrAwZCzbZM/W7Ut/Cbxmccfl6ANstXX7ZcPua+a7q9NvmDKhSfJqrN6xmmKU3u8yJEA+uEU/Ay16gxHdBs88phJ3a3vBSg3yDKuL/DHISxxOKoqSiibh/goiY/rqN7rld7m8Vq1a2O8V/gyDhFLOGalWXUsK19b6/j8Nln452qx6hmCaYAjFX1zH3JbEe8dy2KjRsT0iRkeM0J/wIpzfr5aIvJpne6zev8sHmr//FQ0UO13gWsxkPeqDVa9cXPgfK/6gPBnUWeffLIaC1+RcESn7k318rew/N8eYh7PcxLsx5c2S/nrKqXlnPskZIKOMYj/14wxp0Un/z5nQ0F345wrJVAn+HaqK3W6npM/xXaMYRz6cs+Q+9Ie5zHEvC8sB4oZYlNA2lSupfxbSqurnG3qcuFPpz4++SHKpraktGtTDm3A+ub+iLsGe5kP837tcc37vNPgLW95ZW1pdWVxBZ+ond/dPCT8jbBN9e6GaaRabCpRtykVf5fmBsc6/VmD1/5WOV+LsyvV3pTJqh0xPuhtX1iFN7pVlTUsQxLwuyLXpM3m+FOm8lDvj3BUq/H0AvG11IdhX749bN93PiNxw/g+SZUR3GtRtkVxTWhjF+pyD5h7XBkzEncesWh/016YIzPb38eRzziWPpMX0GdScc6tbNBSJzJuRJyjxg3lw2xFJN4biS+u79x939zro3r8ffaa8x6ofPu8YmffWgvEx9jJnWnfHHe48uwXTu19fNveYQ+CX3yVeY5uuPGjtlE/+fmtc1Ky35n2dMfXv3XUh5n9vpLOvtY+30M//63lz0X1u/GvD2XsfzUj6675M518kjmtA+z4Or2YDP38C0Nf/ENOv5em9Fl211f73/B+jdP+jk6+35x8zjn5hHNal+i8jvEfks6VT16z1/Vq4rfnb3vvioozK+522p/ScT9L2Z+S1wPpB3r/GwfCvbj8jwPh2i//m7l34XE=
*/