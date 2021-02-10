//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_SHA1_HPP
#define BOOST_BEAST_DETAIL_SHA1_HPP

#include <boost/beast/core/detail/config.hpp>
#include <cstdint>
#include <cstddef>

// Based on https://github.com/vog/sha1
/*
    Original authors:
        Steve Reid (Original C Code)
        Bruce Guenter (Small changes to fit into bglibs)
        Volker Grabsch (Translation to simpler C++ Code)
        Eugene Hopkinson (Safety improvements)
        Vincent Falco (beast adaptation)
*/

namespace boost {
namespace beast {
namespace detail {

namespace sha1 {

static std::size_t constexpr BLOCK_INTS = 16;
static std::size_t constexpr BLOCK_BYTES = 64;
static std::size_t constexpr DIGEST_BYTES = 20;

} // sha1

struct sha1_context
{
    static unsigned int constexpr block_size = sha1::BLOCK_BYTES;
    static unsigned int constexpr digest_size = 20;

    std::size_t buflen;
    std::size_t blocks;
    std::uint32_t digest[5];
    std::uint8_t buf[block_size];
};

BOOST_BEAST_DECL
void
init(sha1_context& ctx) noexcept;

BOOST_BEAST_DECL
void
update(
    sha1_context& ctx,
    void const* message,
    std::size_t size) noexcept;

BOOST_BEAST_DECL
void
finish(
    sha1_context& ctx,
    void* digest) noexcept;

} // detail
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/detail/sha1.ipp>
#endif

#endif

/* sha1.hpp
cItpq914FotFT94LsKTsZWbW31qjSGwGyEsdMXBCxCsu+x7Iq4vT8cm7y+HR+PR8CBr/lgNWqAuJHZWpu7K0HYqw3VY+uPAYrX6vJ8eD8SCmhnainwPKOmwzk4jd3mH/A0PrbY8jwy33yD+VdB4bYoHq8441E+jOBXYcHmfBrG5fiinGJ4wkqFmWOfjLhJisuVMQN1p+V61GJxeD9yfDMSoG0maZGqL/qre7LhV3gPINkWBeHvQONvKJsbNNgJViVkhOJPZJaa1BwMECeIuNPDsIfpwk5x9a7po0HIU9BApw6luYiCY438j8LT13IKi4s3ns24ja2wDJSFFU8xaRLJ1c0WStuUNDs4hDPzyY8TB64XgiWppMMcO3dX3QqesJbg2lS4+wUjUN5xzmOvCQaxhgZrxst9Mg3modm9AT6H7suxqnx1BzzncjEaZ/Td/Py6pBAv1ZJXFO5DxQt9JOTZm8S6On0dq9aMXaXJFSCl3NG27w1WTydb80Et/Wc2Kl7G7maGOottGvOTdf8L1ppdCcwRyfJwC6Rmp4rMWKNul8l3n8P1BLAwQKAAAACAAtZ0pSm4ONh/QDAAAzCQAAJwAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvZ2V0cmVkaXJlY3QuY1VU
*/