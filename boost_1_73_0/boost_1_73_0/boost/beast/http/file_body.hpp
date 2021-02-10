//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_FILE_BODY_HPP
#define BOOST_BEAST_HTTP_FILE_BODY_HPP

#include <boost/beast/core/file.hpp>
#include <boost/beast/http/basic_file_body.hpp>
#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/// A message body represented by a file on the filesystem.
using file_body = basic_file_body<file>;

} // http
} // beast
} // boost

#ifndef BOOST_BEAST_NO_FILE_BODY_WIN32
#include <boost/beast/http/impl/file_body_win32.hpp>
#endif

#endif

/* file_body.hpp
3IrI596y2DH6hpFrlbFVMUQi3+qccMc1yefOSGHJ1Qvtd17e3PDdC2yaTk9Z//jd9fnJycWA9k4FtS9len82nVVMld1chFzw0L38GpYvMeXqYjw7eXc5OZqJf+py5urACiw3Hbj3Pr3AUpF5fDg7HNAqW2Wrj4a8QDfLda44f1OMfOxIWI6nhS6Sl9h9Pj4/uTocww/77IdHV/MBdkZ+pGQEKtSW4c6L2p8lHBrOQRa+kpYusB6/8Zh97ge3FbYxDaG0DDrfHP7wcdRs6fO0dSMoEy9SPsYL8wIeF03xB9tZMSL5XirhLw3H9Qfmz12gkee28FOzYMHoLLLS9hPpbj3nkFGVKTI9pjK8STylZkjkHPXKHoWlTEseVUHhWsxKQXzTFtde3XICP90CUAAWP10CgqruOlWNlkw+v5y+945PJtfrmQAoiTVzdH+MMML4FTA3FvwNqCWk30D1E/7mcXtbzBH3wplPAufNlykqZLeOHm28zn0bbdStV9icGxZVh8VYowpUn40+nZcypAoLbf3LbKGnDipVXIO5PrmX20inGHnVH7rc67YR7sFCaetoa61r/+LYs18lsZBZPOMdo73EmY+DgjtaZDwdunI8IOvfIpl59sWYsDo5ykjIaEp8nTpgCALbpBlVTx8w
*/