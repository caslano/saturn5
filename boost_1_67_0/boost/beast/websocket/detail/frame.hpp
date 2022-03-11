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