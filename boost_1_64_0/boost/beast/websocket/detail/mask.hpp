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
wLrmiNR6GASTl+LUrQrGYfXxPna4Ac4H7JjGQ0ya8Xf6Yvqe4j4gZrnluL7BHSKUUhpYSquFLRWtxXWF2PHgGzVKYWZoQ9qjKtE7X1INVZ1GduxSs8w94gSoSt9noiWheKeve0DlAgbIi3CXQOUePnQeIo7sa5klg0KB6r8w4VuT8vgPtGKrh0Fm5xwO1WyTBLVF2vZA6D20TH0UEuBCDPpgE9So3zsKzZ4m+NWV05fPd9mZ8Gt5neqb9OlHazFCArpiwaZhOXC2lfqtB3VZpnhVd8Vq98YofCuB0WQYuP11GU1rBWa5cRU+NUCBWgozk61EhJkrfdi3teT0pNyvkz9vY1zOhO3J/T98r13rZBSS9Z3Lqgqz8eM3SSZTqpSIG5ohNf57ajfnkA5hxmmxxAyKCqrJ6/XgO1HSzJFa8yUHSgSGNYhUWRpgS7btEI7mrDE9g0J99T7VF4Y5eXqeVkSnA1ULdSvZCDdLR69Ul5zJJjpbAUenvfoeZ4iJfvziCFvME+MZ9SRqveuTrh7Z5Ig0shb6b/Ue/BRCeug2b5jYPVgdB6VOaNbuew==
*/