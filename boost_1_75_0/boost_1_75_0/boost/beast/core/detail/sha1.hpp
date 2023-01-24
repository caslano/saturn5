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
hTVCEF2msMnwCmjWKaVRg4ny8R1rHlcuAPf+DjfOM2doROP+hWO6R/2e6vX+Fd/VdjK0qkQ0NfyY0ZYYCiW8gxqQPUCB4vYygwL4C74ntZdxiL52cMEaVz/VfVxKu07LPF0/tape8fOmpLTdUN/6yGPsJrMoqnBfwJeqdVd6EhSGvxPaUmyFv2/gj9tdpBMWe3OycZv/QgsgZ5ZBGneJnNLVj81YhS1M82zpBf0g9T4w+CC6XPib12oNZjd0Fy/yw2YStx9MEAwE1mU/DxAtKByK8/ROd92CZCjOUg7jMh8gyXeppD3UBTO+p7lJ/ExLOobEiFxL6jX4dS9aAEvzRrYs5UzwMc19MpekrAErEepnXIVsyOO3c/hz7GLqgvNgnl9oGKWnJ0NuX80EzodAPIiyMDGckCpXJgOUldoaaDFKZLg9SbjBD6AQPNm+al+WFszCGmfkSSxXenqDxi1B1AIhb2pIjxRvLuxOhPhxLYl2JTAIQnnpYgGLgJT4iiL4j/5MrwfhCzxazQDWsSWzdtJssGpot1T0BAP+HAPCnyud3q5nE5kQYAdK5EqvCx9OPUNI6DpOHZb2OG0DO3fElKnHKqX2lLMp8Zo1N7pZo/EAK0xRjlY9bPSELmm/vp52VqzTxVpAbWjV3hFRXvirI67ByDFV5fFMKcqL//dDvNpSphDpV2gn8UlvfIuD58KHt8nMLpwiFDFZoym8
*/