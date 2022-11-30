//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_FRAME_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_FRAME_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/websocket/error.hpp>
#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/beast/websocket/detail/utf8_checker.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/assert.hpp>
#include <boost/endian/conversion.hpp>
#include <cstdint>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

// frame header opcodes
enum class opcode : std::uint8_t
{
    cont    = 0,
    text    = 1,
    binary  = 2,
    rsv3    = 3,
    rsv4    = 4,
    rsv5    = 5,
    rsv6    = 6,
    rsv7    = 7,
    close   = 8,
    ping    = 9,
    pong    = 10,
    crsvb   = 11,
    crsvc   = 12,
    crsvd   = 13,
    crsve   = 14,
    crsvf   = 15
};

// Contents of a WebSocket frame header
struct frame_header
{
    std::uint64_t len;
    std::uint32_t key;
    opcode op;
    bool fin  : 1;
    bool mask : 1;
    bool rsv1 : 1;
    bool rsv2 : 1;
    bool rsv3 : 1;
};

// holds the largest possible frame header
using fh_buffer = flat_static_buffer<14>;

// holds the largest possible control frame
using frame_buffer =
    flat_static_buffer< 2 + 8 + 4 + 125 >;

inline
bool constexpr
is_reserved(opcode op)
{
    return
        (op >= opcode::rsv3  && op <= opcode::rsv7) ||
        (op >= opcode::crsvb && op <= opcode::crsvf);
}

inline
bool constexpr
is_valid(opcode op)
{
    return op <= opcode::crsvf;
}

inline
bool constexpr
is_control(opcode op)
{
    return op >= opcode::close;
}

inline
bool
is_valid_close_code(std::uint16_t v)
{
    switch(v)
    {
    case close_code::normal:            // 1000
    case close_code::going_away:        // 1001
    case close_code::protocol_error:    // 1002
    case close_code::unknown_data:      // 1003
    case close_code::bad_payload:       // 1007
    case close_code::policy_error:      // 1008
    case close_code::too_big:           // 1009
    case close_code::needs_extension:   // 1010
    case close_code::internal_error:    // 1011
    case close_code::service_restart:   // 1012
    case close_code::try_again_later:   // 1013
        return true;

    // explicitly reserved
    case close_code::reserved1:         // 1004
    case close_code::no_status:         // 1005
    case close_code::abnormal:          // 1006
    case close_code::reserved2:         // 1014
    case close_code::reserved3:         // 1015
        return false;
    }
    // reserved
    if(v >= 1016 && v <= 2999)
        return false;
    // not used
    if(v <= 999)
        return false;
    return true;
}

//------------------------------------------------------------------------------

// Write frame header to dynamic buffer
//
template<class DynamicBuffer>
void
write(DynamicBuffer& db, frame_header const& fh)
{
    std::size_t n;
    std::uint8_t b[14];
    b[0] = (fh.fin ? 0x80 : 0x00) | static_cast<std::uint8_t>(fh.op);
    if(fh.rsv1)
        b[0] |= 0x40;
    if(fh.rsv2)
        b[0] |= 0x20;
    if(fh.rsv3)
        b[0] |= 0x10;
    b[1] = fh.mask ? 0x80 : 0x00;
    if(fh.len <= 125)
    {
        b[1] |= fh.len;
        n = 2;
    }
    else if(fh.len <= 65535)
    {
        b[1] |= 126;
        auto len_be = endian::native_to_big(
            static_cast<std::uint16_t>(fh.len));
        std::memcpy(&b[2], &len_be, sizeof(len_be));
        n = 4;
    }
    else
    {
        b[1] |= 127;
        auto len_be = endian::native_to_big(
            static_cast<std::uint64_t>(fh.len));
        std::memcpy(&b[2], &len_be, sizeof(len_be));
        n = 10;
    }
    if(fh.mask)
    {
        auto key_le = endian::native_to_little(
            static_cast<std::uint32_t>(fh.key));
        std::memcpy(&b[n], &key_le, sizeof(key_le));
        n += 4;
    }
    db.commit(net::buffer_copy(
        db.prepare(n), net::buffer(b)));
}

// Read data from buffers
// This is for ping and pong payloads
//
template<class Buffers>
void
read_ping(ping_data& data, Buffers const& bs)
{
    BOOST_ASSERT(buffer_bytes(bs) <= data.max_size());
    data.resize(buffer_bytes(bs));
    net::buffer_copy(net::mutable_buffer{
        data.data(), data.size()}, bs);
}

// Read close_reason, return true on success
// This is for the close payload
//
template<class Buffers>
void
read_close(
    close_reason& cr,
    Buffers const& bs,
    error_code& ec)
{
    auto const n = buffer_bytes(bs);
    BOOST_ASSERT(n <= 125);
    if(n == 0)
    {
        cr = close_reason{};
        ec = {};
        return;
    }
    if(n == 1)
    {
        // invalid payload size == 1
        ec = error::bad_close_size;
        return;
    }

    std::uint16_t code_be;
    cr.reason.resize(n - 2);
    std::array<net::mutable_buffer, 2> out_bufs{{
        net::mutable_buffer(&code_be, sizeof(code_be)),
        net::mutable_buffer(&cr.reason[0], n - 2)}};

    net::buffer_copy(out_bufs, bs);

    cr.code = endian::big_to_native(code_be);
    if(! is_valid_close_code(cr.code))
    {
        // invalid close code
        ec = error::bad_close_code;
        return;
    }

    if(n > 2 && !check_utf8(
        cr.reason.data(), cr.reason.size()))
    {
        // not valid utf-8
        ec = error::bad_close_payload;
        return;
    }
    ec = {};
}

} // detail
} // websocket
} // beast
} // boost

#endif

/* frame.hpp
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
*/