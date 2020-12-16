//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_SRC_HPP
#define BOOST_BEAST_SRC_HPP

/*

This file is meant to be included once, in a translation unit of
the program, with the macro BOOST_BEAST_SEPARATE_COMPILATION defined.

*/

#define BOOST_BEAST_SOURCE

#include <boost/beast/core/detail/config.hpp>

#if defined(BOOST_BEAST_HEADER_ONLY)
# error Do not compile Beast library source with BOOST_BEAST_HEADER_ONLY defined
#endif

#include <boost/beast/_experimental/test/impl/error.ipp>
#include <boost/beast/_experimental/test/impl/fail_count.ipp>
#include <boost/beast/_experimental/test/impl/stream.ipp>

#include <boost/beast/core/detail/base64.ipp>
#include <boost/beast/core/detail/sha1.ipp>
#include <boost/beast/core/detail/impl/temporary_buffer.ipp>
#include <boost/beast/core/impl/error.ipp>
#include <boost/beast/core/impl/file_posix.ipp>
#include <boost/beast/core/impl/file_stdio.ipp>
#include <boost/beast/core/impl/file_win32.ipp>
#include <boost/beast/core/impl/flat_static_buffer.ipp>
#include <boost/beast/core/impl/saved_handler.ipp>
#include <boost/beast/core/impl/static_buffer.ipp>
#include <boost/beast/core/impl/string.ipp>

#include <boost/beast/http/detail/basic_parser.ipp>
#include <boost/beast/http/detail/rfc7230.ipp>
#include <boost/beast/http/impl/basic_parser.ipp>
#include <boost/beast/http/impl/error.ipp>
#include <boost/beast/http/impl/field.ipp>
#include <boost/beast/http/impl/fields.ipp>
#include <boost/beast/http/impl/rfc7230.ipp>
#include <boost/beast/http/impl/status.ipp>
#include <boost/beast/http/impl/verb.ipp>

#include <boost/beast/websocket/detail/hybi13.ipp>
#include <boost/beast/websocket/detail/mask.ipp>
#include <boost/beast/websocket/detail/pmd_extension.ipp>
#include <boost/beast/websocket/detail/prng.ipp>
#include <boost/beast/websocket/detail/service.ipp>
#include <boost/beast/websocket/detail/utf8_checker.ipp>
#include <boost/beast/websocket/impl/error.ipp>

#include <boost/beast/zlib/detail/deflate_stream.ipp>
#include <boost/beast/zlib/detail/inflate_stream.ipp>
#include <boost/beast/zlib/impl/error.ipp>

#endif

/* src.hpp
RKV6lId6V4PflfIeN/vRM92Ib98IeHKuPLc2+y2UtdNPXNfpJ/P8GR3SH6JDOVcTMI9E3fOIaw6ifZyT9km/rzay2g7n97r2cRqDQ/ISemgotuccqVdTw0WLT5o+feaCBYtnzFww/Yw5ZeVzTptvzzyL61YtpzCX3es8GepXUJ+56nX3BVx3ONfdH++60VUNNXpvPjAGfetvarUzlc03cwprZuNfb54r3YzBBOrs6JXroUOu55rbuQbnuIZzT9O2lR3jb1v2OMLNpm0L5o+3H47NnF5ulNlxXTrXK5nsv17uOM4HXi9aH9VdRvTZhE+PyJk1ZLbcW+z8y1bVVRpdmjzmOUACdXZ0yTWNLvNVl1yHc+Y6el9UG53ib18e7SsLbh9GEto2ZIyN8NzFZyOkd95GuJ7PRrhGjI0cAF/7EH0c/qftLx7sk+/w7xe+TfYLf+fyhop/PPKbF8c88l7qb279w4own4JhvgA77gPyX+xdDXwUxRXfkFwIEOASQgghhBDCR4CEkw+JSPH4CAYS4AyBRkCTkAQTCcmZL2MNEBCRStS0pa1a1NSiUktrrNSiYo1KKdbUpoo2VqxRaUVKaWqpxRa0/528nczt1+3lkNr29vd797/ZeW9m3tuZ2ZndmbdftO+OX4zvi9eDcLDni2eh57A+SF/4/6nwvx99g/z7Emwl/P8LeBrwP15e703/L8H/N+n/bbKfJ/r/Hfz/Df1/gr5lnqbs96S5RoPK19Y+8j31Q2AE+TwcysKKDyza+whMInnRB9aPSf4J4CjyvUX5Yi+hcb4PkFwz5ftdyhdhLp9vIv8QyT9M8ntJHmEu32Aify/Jf4fkd5M8wly+2UR+O8nfRvJfJXmEuXyrifwdJH8nyTeRPMJcvtNEfhfJf5Pkv03yCHN56S5j+S0kv5XkbyF5hLl8gol8NcnXkPyNTB5h0XcayY/VqTdfIfmbgQnAeiFft0m+pSR3PeW7nvJFmMs3mciXk3wFybtJHmEu32IiX0TyxSS/juQR5vLtJvLLST6H5FfI8hTm7dVE/mqSX0Xyq0keYS5vbzKWv5bk80i+gOQR5vIOE/mlJL+M5F0kjzCXd5nIO0l+LsnPJ3mEeb1xNxnXm4UkfyXVm0ViezXJdwbJXUr5zmT5Iiy2VxP5WSR/OcnPZvIIi+3VRN5B8peQ/FSSR5jLS18zlh9J8vEkn8DkERbbq4l8EsmPJfnxJD9W7K9N5CeS/CSST2HyCIv9tYl8DMkPJ/lYJo+w2F+byL9L8u+R/PtMHmHRd+7XjOvNH0n+A6o3J8T2apLv6yT3BuX7W5YvwmJ7NZF/i+SPkfzbTB5hsb1+3Vi+neR/Q/KvMnmExfZqIv8cybeS/PNMHmGxvZrI/5zkD5P8L0geYS7vNpF/meTbSP5XTB5hsb82kX+a5J8h+YMkjzD3YdpC8l8necGHKfPdOwJ4B3Ak8C7gRODXgGmyDHAJ8BvAXOAu4BqKvxb4LaAbeDdwM/BeoOIbmb0jpXeuDSrfyPdTvg9Qvg9SvnuAlwEfBmYC9wKXAx8F8vpE6Q7XsUdiULc9xgDZIzJgFIXJZy29a8O1J3nBZy3z0TsGOBc4AzgPOI/CCyicCVxA5UoHrgJmAguAVwKLgRnA64HLgDVAF/BmCm+i8C3Aq4CPAldwH770rgZQwcon+vAFgm84MB84CbgWOAVYCJwOXAe8AlgEXAwsBq6i83kULqXwR8AmmSi/tyi/wcBtyngCfJOB1wNTgRuAlwMrgOz5PdWPSvKdWkP61wKrgHXALcCbgduB9cBdwE3A7wG3AH8CvAX4LPBWIB9nfMu43o+g6xwHjACOBA6VwyTfBWonediYycs=
*/