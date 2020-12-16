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
6qMzv1bdL8+7+tKRhjpelTlZG+QdKn6ftyw4jbG+jkuYHs69HaTcf9TOyxqg/MukfEh417ysTfs087Kk/GQo//ulvEh4fR+L+Dt9LIFlQsrxcKW30uhDPsY6v6EBbbT8job2W/pL9Lc44+GjDXV8KePhO6SNzvncycMl5SH0tfj0+zpt9HLlrtG10eh76/M1yv2Y9n3nKuUv8+ic8D0D22gpP5cr/81Sl0Vf6vJ9Kt+WeJ59blL+C53yM1DNaYx2tc3eOe6pIf62Hp26d2jc7BsVT8M4p4+3PyPmZEMdz8m+2w8jKdZv7W53PmqfcUWvi6F5phX/jkaSPNO2+NRyr6ItwDoS7Lm2wGVXfgv9n2ed99Dmyt7dxmA0f4NIvkn49v755sxfbqPCXcc7SXNjPpLg0ZMxAEljd6U7TdzUUuVu43rXCG089Jd6tt0yVvZWlf28o+TZtu5TVx6G0C/l0+/l1MXkzyz3N7p+KdHv7tTFNkp/r65fSvS7OL+tCUr/+6BtZyJspfyvkrbUDt9Z/E3jVeXfM0jdlDm0yn+PEeyZV/qYxB16e3q0n3ntelg6zuCQtTil/laSprW+dVqpf4MGkoNWMO24Enko+pHOPX9EuaPr+2ZpghWBJOIX47QvYte1xuvNpn7t1LeT1H7bj//jYMxJpX+/OPr59L33PL6v8ftDL1T7Yfdpd27EY99Exv74mw/TV4wpvke3Rqpu7Vfd2qy6tWV1a63q1pzVrfHa+DVwNWvLataK1a9p+x3nJXPVOKR6rpf9tlMNWStEvm/DT/2dKPp1Ua59mz163rVhq2J8a8NeD6PFbduvDcG+pVcXop4REZpefIh6qSHoZVgSoU//nqa+9H8Oo8Vth8uqJ9yyZr5wV8NocdvxmhpivHLqsX9Q8sWI9dk3oR2utJ5wvdGz2EfCHQvteFXUE6+row/pVdWj95Ur/tX1xON3Ev8bpFzhduyvDcG+Kt8h6m0LUa82RL26EPQy1OLb+vTvlXL1hZQr3E64+HrCXSvl6hoYLW6nvEeGFq+Meuy3kPLRUspHK+iU93rCDZZwQyTcCdAp7/XE62t3ea/H/gopLzdKecHt2C8Nwb4q3yHqVYWoVx2i3toQ9DKQmnrSXyfl5UsYLW6n/a4n3HIpL5UwWtxOeQ8xXnX12G8v+d5B8r0jdMp/lD7cyRJurIQbB532PUofr2XSDk015NtjuFv0LDtjRK+c+PeCC2EGXALL4EVwCVwKV8NL4MvwMknvEPv7V/nuN0finG7KQxPlbiCcCIdZOnASPAVOh6fCc+A0WAanw6XwDHgTPBPeCs+Cd8Kz4VY4C+6E2fA9eC78CubBgzAfNiUOBbA5LIQJ8DzYHhbBsbAEToXnw7PgArgMLoQ3wEXwNrgY3g0vgKvghXAzvBh+CC+BTUn/pTAGXg5bwCtgMrwSdoXLYCa8VupjhfPdJfMg5P71Rcrl/lWSf8fB5XAwvA6eBqvgGfB3sACugCXwD3A5vA3+Ht4BH4PV8G14L/wY3gc/g6vhD/ABGGN9gwNbwYdgJ/gw7AvXwSHwUXgS3AAnwCfgNPgUPBs+A2fDGlgIn4VlcCO8FD4PfwdfgLfATXAl3AyfgVvgRvgP+BLcBmvhq/B7uB3+AF+HBvdrB2wK34At4C7YBr4D0+C7sA+shZnwAzgE/hMOhZ9GSz4Y8m2gfAOZI2Nw5VI/vkCvB9wL+8EvLTtWEHgS/AqOgs2scgTj4G9hS7gctoJ/gK3h7TAB1sBj4GaYJOWBc/J9m/qmT8WjDbJe4pGCXn/YHp4IO8CRsBOcBdNgCewCfwO7w+thb7gF9oWfwkz4E+wP+3GdQXACHAJnwrFwMTw=
*/