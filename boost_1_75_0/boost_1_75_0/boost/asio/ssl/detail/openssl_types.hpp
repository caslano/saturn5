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
l8+4kuzAH3NOfuPcmev78u5J48qeVYVZa+5/IW7UiX2zdJ7VxfyToV4v5h5/cUHXfd/bV/Vh33otZOuaI+FLGP/Kv4UFj94xanVw/st/PPZIYF15ka9Pn6LAUWFXdYn8+K5fhj7zx/KgQ9r40OvcrI7yb06FfNsh8uqq+dND+jco62LDK4LtisTIL58dGjzh0xde/6rdGgc9U6eEzx4+q3HfD/6FGzpdOhN6sdMDtz17PL8vsZv1g2Meo0NruTPpb/Q6ULk08kX9c+cmh1R+eOnWmGd3VgREvfTPD7ffGxyleOOZsYP8w/Z08xo7fNLO0Be7d9/YvUdY6NaG3Q+Wv/pFSO03L8fIFwWHfLDj3KuD+38S/NVP/gs9hz0QPHLYTzVVlWUOOoRmW6QJc+zDFDHDXc8M2YQjFQ3CKPkX8YhFkS/8Kzvno+kF5howe4C5DsyeYK4HszeYYT95au4BcxqYuK4ZB2ZHMDdBOK4VbgET10O3gYn6YxaE4zrrLnDjWYv9YOK6aBWY/mAeBRPH/sfBJG/lgnkvmOmQDtc2a8GNhy1ywI1rkCyYqJOWgUnWMsHsCuZqMO9HusHsACAs39OLdIPZD+kGE390bQOYMM1gNoMZBAUKgkRBvQUeMUXAgyJhzqQZi9kCXyYL/BL0pC2QxhXTOOLmN8UFJE0HVooks7Ai2cQmlt8OlcQJl9jHNV9DDcXJk9tdFJe9
*/