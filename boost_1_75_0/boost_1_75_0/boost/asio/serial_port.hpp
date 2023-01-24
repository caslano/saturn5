//
// serial_port.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SERIAL_PORT_HPP
#define BOOST_ASIO_SERIAL_PORT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_SERIAL_PORT) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_serial_port.hpp>

namespace boost {
namespace asio {

/// Typedef for the typical usage of a serial port.
typedef basic_serial_port<> serial_port;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_SERIAL_PORT)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_SERIAL_PORT_HPP

/* serial_port.hpp
RtJqsf1x9W+Ph9k7ARJ140l1vrHJZoJuFxH+cri0ejkCW76b/+xaGAF394exwBbeD8Ui+vw0ASYIpDIi6SnecG0Yhh6W86NZBMqOPEQIkz0zy2Zi9NNKCs1R0v8eNrXmPelnN+LQfzgUIgbGDRotxks03dgkh/tQibhjNpYzE84Y2Bip2TtiQRx+yCaQjVE9XxEKTgrPq0PPj+me1B0mJrAjhNBu59tHog6YqjVmIFJraHnmQuUchfBQ41e+1HfViGm1t8QRwc6MeF8z4co40/hvJaQNzF8JRJeCC6sJ/MHP+43WU1Ev4DN/Oj/9UkgLllHSETtzDohCebI/WvNIer28qtRIQjCsQIe8ZPP5jtgBKK3DMxOpa7tntmUVLlm0UGjbbYH6x2XE2TdDAV74txr+/RF+Y/0jnXH2tfDvTfj3OTx71Ey7Df6F2hlKG9l2TIun+kzh997m03NmBg7jeZpeqMYT+NNovxUjHbeHJwD62LBltkV9kBU6nC0uW2M6jKoiZ4PsWbcqeLZEr5T1lLaSIdD9GByHujt0zzxvifA0xPzK7BLhncg69cUHKJLEUSWZxbEN85ahMXAq++jiH3TPAYowwZ09qzCuhYlxkzrkV0c70i9VtOfNtkLNcFpcpdhJ/6xYBBJokwshl3rQtEEOXfYQsXkvjiLM5/LUvZdRmjQzkNvnl3Ch48Jytuj16T/72c+cLVM96fdo
*/