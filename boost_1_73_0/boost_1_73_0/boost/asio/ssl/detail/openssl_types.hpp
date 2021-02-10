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
SDhiwmT2npN0gOY16evzx27zYraJhXum3MH6cNiaNdLcwa5M6AhoxuwRraPMHSwZk3UTRgGPbtDKNyc4cbp04EVmY63VeBwyiEdo/mq2OtRAiCOno5PAEYRrpDBBW0+YWjj4kKF3EQoNvlF/iDkH8TVq7ZUJI7kJeISel5SxBfj0GIvbADVsLXF/pVx4uRbOs1qZ5sktws0dbu3tMmXN8nh0Pwj9kghKrpj2juhSPOrAnPAUeMn1LOdCDQIjE/E5g4PNDdvdrlM2Qvh6uGOzpBCnKqTLVWFHHHFl8FS6xuo7cHyUitRciEGCo3/V1pj3UWX0UjzXHfWrVmUtSRqVcMS8qr7ksoAC9C5Ed2ZrfgFQSwMECgAAAAgALWdKUohbj+LVAQAAXAMAADIACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9yZW1vdGUtaGVhZGVyLW5hbWUuZFVUBQABtkgkYFWSwW7bMBBE7/yKvRRpgcgfoFuaFE0KIzBSB7nkwohLiy3FVZfL2Pr7rmg5sY+idvbNDLmmtGuBcSDBpkfrkJtkBzS/e2Jp4ZfZMAl1FHML99vtxtxjHFt4zgjSIyySkek9OHTgQ8Sqv7WCO+KpBSoyFjFN05htHzLQKIESCMaY646m
*/