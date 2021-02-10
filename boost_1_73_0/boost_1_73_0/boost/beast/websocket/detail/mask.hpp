//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_MASK_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_MASK_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/asio/buffer.hpp>
#include <array>
#include <climits>
#include <cstdint>
#include <random>
#include <type_traits>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

using prepared_key = std::array<unsigned char, 4>;

BOOST_BEAST_DECL
void
prepare_key(prepared_key& prepared, std::uint32_t key);

// Apply mask in place
//
BOOST_BEAST_DECL
void
mask_inplace(net::mutable_buffer const& b, prepared_key& key);

// Apply mask in place
//
template<class MutableBufferSequence>
void
mask_inplace(
    MutableBufferSequence const& buffers,
    prepared_key& key)
{
    for(net::mutable_buffer b :
            beast::buffers_range_ref(buffers))
        detail::mask_inplace(b, key);
}

} // detail
} // websocket
} // beast
} // boost


#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/mask.ipp>
#endif


#endif

/* mask.hpp
hCgPtChWlGYPqiJG7Ra7yFuJJqcuwf9bmqPfGFRBZqA7DmAedGEnjDQe3M43fy+3G7gdr9fjxeYOlm9gvLhjsrfzxZRKL0lMAz6WGg2Ja5B5mUmMG83vd/mdjj+A0XQWTK5Yf34zXpGuIDnkXjnI4gFocKnBDLkGkKiMssPLR36LJKIfZRFlVYwwMjaWaphenUxxZ9TtQdOs6dJGXwFGOrUzqgUtoMTym5w6b6ceT3xUhuczuWOFn00dRiRKsZOZtNQjbbEWirhsSi3rGr3V1Pi+kpTrlgJ+H/52MbzgzIud2rtaU4SysCxe9PZKxv3Ohw7AZLu+hgFjLpunSMVMaOC1e5yFy7eXHXrneF+7IURhnkJZSNvrM0wmPZ7uAzPS8TWAgHY/bQ1diBzrdhbGHJSO2QevOdIYtLSXHIHnFJerTbgNZuvF+GbmQZdpuk7mLGo1DoLb5Zo6sGsw0mgZ11pqC/auMtZtBuLdU5e6BHybqfU1MctclHRU8DBs8j+MVH4qxdGzwnR2PdvMaJvnOefAlBjRCcGl5ref+6Hug280MdkGm+XNevbPdhZsyE6j8WZ5PZ2tT02sUCdK1ydGRDHT4cFtghR9o1QX+ahX1oi6lkeiSYrRv2SSNrTWSpsWTlVnhh+OfdLv1D8r
*/