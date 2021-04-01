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
59NCQ42oAoLZyXDda63/SVcEOTTjaIzKhOkZgc4KavJ0adMjQQqr3swLhK0gJVhDvuZh1DSlGf/hXQtXDvL4CXezlR/e7C5X1Qn/DOxWC12fenX7Re+mV5tm+CQ0uouyuXOKyinS14WfD6CLDWGhvLy28v/2zBKmjotAiJgQCI12Y4J3/tbuRUJw7PzaTasGSfG/El9VtjTJK3Cc3II54EU3kTmQ22Na3cgI7BRsB3xdtI4L6J9lTIr/LTHp27d5PdA1U4wTm8k8Td/pmyompOYXxNGygxNAjvmmZyt4FPNTur65YORuUU2B+kKi5GYcXd1I0ED472gZFCo4hJowhN0pfIs6+QvUBVOT+vE3Hbs582q+U9wyW1f58srySFQM+D5CR3Qgvfezd9HqQwyJL7Bk+PCChef9yIwa06QH5rS3DeF626SwX7OCI0RwpcQrD9m1MpRyWBp4LJv0zydpE0/VtmGsPxmuVJpxmEhRMRJmY39/wVbMWOs8UnGJAVrgIouISLkjoSa6+Hm+Jb01zGDHT/NAixfcyg2hRvwcOwTGL3x+lHYxNwuDkQ==
*/