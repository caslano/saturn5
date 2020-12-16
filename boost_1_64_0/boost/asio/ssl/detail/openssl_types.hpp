//
// ssl/detail/openssl_types.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP
#define BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>
#if defined(BOOST_ASIO_USE_WOLFSSL)
# include <wolfssl/options.h>
#endif // defined(BOOST_ASIO_USE_WOLFSSL)
#include <openssl/conf.h>
#include <openssl/ssl.h>
#if !defined(OPENSSL_NO_ENGINE)
# include <openssl/engine.h>
#endif // !defined(OPENSSL_NO_ENGINE)
#include <openssl/dh.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#endif // BOOST_ASIO_SSL_DETAIL_OPENSSL_TYPES_HPP

/* openssl_types.hpp
82rsK7lt3l2DO0bxu8SxdaC3bOUTDlvIi8pnl9XTDyhvD9MPvDYwsB8wZ/aeE5oFVim/Wu4aTxsHn3m26Q+eEZquWsYRniwNZ4Q+xfanSrn9uaWdSS23UxouN7uNTo+z3PqdcnjlluN6v9T8xZwTfSxTz07oufad2kcXnxJbRhTORWqMLLh8lO90Uz5vqowC26Dh6WX60VXiv9/BYx5rdNtdIzSlVl89k1pk4uluyucR8Wd6+2v97rlKwjeJf4Lh74bcYnTq0SE7v2uuF7oHpdzXUOafZOj3d6Fd7t0s37FcaZG61JH0zNpvm28JrQ+fEXZh73htuKVmtj/1aNQLp2xp096+2rTn3Woz8H39vn8HtzkbKZ3qV1dK0BIws2z+xeXzy1zfu/NL5pVF2+Yq4X3JyovqQtT42vmOm23BzEFiR1L9WMLDH9Gd+KakscyU1TMS13eszsi5CSG3d8beEO4vuEj5PJrZsLzdYxt5iJkDGJUTJuZ9lrhA/d7YMMgjGzrLsuqa6sA2pDwFwW3G0PQz3wIviv+M0P/qGbd+KjSjQ/+h9LTNaDxdvd8YKr9dEl4YOmQ19S0Pm+Xu06SNq58vEvF3dH+T6Bg4WcK2Yzulp+ObxIjEtO898tzx1NX+pj2/K/cyjVws+5y1fCZEZTdf4m8V+x1h+vRLJDxLwvdJXZlX6uxXlkp4tZVhDZX2vQeavdnavgfV076V9lC2flOk1d6h72d8Q7hpstuYPmC1fI/o/VFtzPfIw3yIpCcP5tcK+B5Rnoo2+j3SvLbO8z2iNGvbmO+RNM/3iNLs0DQlL+8ng5c3j+6+agE83yWO4jjHsM2nHV5fpe8enj5pRMTWcNvwg3rqvGw3fX+sPN3T7sqqq8NGbMuZhptTUj4/+D1D+YktuA0amqDveA3vZN7TZ8Xx/XY0ZBPpk2ra+ctmg1c2C6pKy+ydZ8F9Uhzy2NCAPDZ8yfLY3jEcsd0XtlW05bHbKw8ZFMvLqoPkoTwnBMvD0PSSvuU8/J+IPy/0tpUSJCPl6WD69XfFPyD0ATnx9NHar38kND1Df+E32qeaLJi+77PT3fM8YwfL92xgv75NwnN9dUZMl7A6azbh9fXH1UKXEdgfL9A0ZDn1TtTMq7Qc7+/XCs0tzIj1M/NpZXJvCiNXH+mnF5Oo2g7ah51dz9yP0j7WwfS1V8ncz4h6+lrl2dvB9LU3e/papTnUIdLX1v7D09cqTa+Okb72mMC+tgP3UqN9rbwbljXi3fAng939bZFPG5oW0IaK62lDGzqFH7QR105xPbSVZ3jaUDU9CmUd2MfC03AbCtP0MnV9nfhrrAm67lAbbkOznPaRVwvNtdTNULQvlnsdY9udqWPfkvDLsd3WQngmGJ7OjjZlsmTeF24XmmK+Ok6QeriDsk3rFFmPi+878OI4x9CkM49sDEVW3EdWwe/65rtwXZfww3+i34UP63dh4Zneci6/eH5ZlQytgWUNn/u78KkzG56/g8f1XThH/N+Omb+LlkWZhF/IUzpquUfi6B74DThLwlebModexzldV5RnyBeg+aa4RGhukvLehHA+6Wy+/6TfaejdqQjaclyn7PjKff8Rlnt0Pq7hb7wPu4Yf/qK0b1DLPf+sgHLXz5l63qWUt8CU/fazGi77MM9xpk1PEv8DOoejfDHv7kVCU8mIcKYpf+JxzeEuEX9m4DfSWAnfYpUhE60TxOE7j2u+ac6V8Pvpb9CPZL4rbPHMJIHRsa5O8xSTFqlHt9HeCrvG951h007rar4hbo6Z+5X38rlx9imbzzoadWteaTx9Sl81iPqs9imP4e6CtrAwqG6xrBhcr+CL6VPE36T+PqUwpk8R/y0=
*/