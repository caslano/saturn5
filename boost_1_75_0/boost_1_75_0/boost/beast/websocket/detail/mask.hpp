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
Bh39rD9ZHnh0ywNGzah+KwaPb34IYnCCqB+MvdBwtBD35T7UD00rry6dBF4IBULL1BBaNsNV6DGlXjn4DCMXwWRhMCgqxGH5ONywKP/vL6wXCjVSKsx6ATV0ijfpGjqGEKlvJiAsvpYQqTdmUL2w7NdVLwrYCoMNKTmn8cp0ZUBbjAYGmA0YB8NHRih5uhEK13YAIzfiCCCAALX9fYKJR0wDMnr65PRM4BtMOQugN464IezMKHE6UiznOeOlX1yOqdZmK+TGBM8GNWqrqzaukSOwPGi+t4/moyQ9U8MyhsCxXBuicKOuDZFGYU7wtkb2f/EE5/L7Wbub+rIeCtvcv1/+Z/QGNX2u6d/T6WJ5ZZ92bwNU7GNbHBxSfOSVj2Sp4KVnHEwU2tlM9BKckWlPPcDZOFf2VHYJs6HJ88eOMnsMv43Fx8CssR8J3JlGofKJHe7FQX6hDoK1TpBCBAbBkSuqdpEfGjyacM14XB14yUa+EKIZ+Bj5OyzL5lpjpnvNcfSLiyYTz+Mlk7svCneWQn6WnL8Mt0t0/k4xUW+KiG445Q0Tfko3NmTZmgVLCLeN4AcJt2/5eNsFxpG8A3x70BWzXoF0g2sPWP0MUKE900RE7Bkmghic2k79+LlSIU5tvQ9RQh5XGktVGkvp53qy6nyrr10Sc2xkPTi0VRCfcbW6RHQPzlMRgEtbWVQh0wEvNAyGZ1cjnYD+x7ji
*/