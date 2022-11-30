//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//
// This is a derivative work, original copyright follows:
//

/*
    Copyright (c) 2015 Orson Peters <orsonpeters@gmail.com>
    
    This software is provided 'as-is', without any express or implied warranty. In no event will the
    authors be held liable for any damages arising from the use of this software.
    
    Permission is granted to anyone to use this software for any purpose, including commercial
    applications, and to alter it and redistribute it freely, subject to the following restrictions:
    
    1. The origin of this software must not be misrepresented; you must not claim that you wrote the
       original software. If you use this software in a product, an acknowledgment in the product
       documentation would be appreciated but is not required.
    
    2. Altered source versions must be plainly marked as such, and must not be misrepresented as
       being the original software.
    
    3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BOOST_BEAST_CORE_DETAIL_CHACHA_HPP
#define BOOST_BEAST_CORE_DETAIL_CHACHA_HPP

#include <cstdint>
#include <limits>

namespace boost {
namespace beast {
namespace detail {

template<std::size_t R>
class chacha
{
    alignas(16) std::uint32_t block_[16];
    std::uint32_t keysetup_[8];
    std::uint64_t ctr_ = 0;
    int idx_ = 16;

    void generate_block()
    {
        std::uint32_t constexpr constants[4] = {
            0x61707865, 0x3320646e, 0x79622d32, 0x6b206574 };
        std::uint32_t input[16];
        for (int i = 0; i < 4; ++i)
            input[i] = constants[i];
        for (int i = 0; i < 8; ++i)
            input[4 + i] = keysetup_[i];
        input[12] = (ctr_ / 16) & 0xffffffffu;
        input[13] = (ctr_ / 16) >> 32;
        input[14] = input[15] = 0xdeadbeef; // Could use 128-bit counter.
        for (int i = 0; i < 16; ++i)
            block_[i] = input[i];
        chacha_core();
        for (int i = 0; i < 16; ++i)
            block_[i] += input[i];
    }

    void chacha_core()
    {
        #define BOOST_BEAST_CHACHA_ROTL32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

        #define BOOST_BEAST_CHACHA_QUARTERROUND(x, a, b, c, d) \
            x[a] = x[a] + x[b]; x[d] ^= x[a]; x[d] = BOOST_BEAST_CHACHA_ROTL32(x[d], 16); \
            x[c] = x[c] + x[d]; x[b] ^= x[c]; x[b] = BOOST_BEAST_CHACHA_ROTL32(x[b], 12); \
            x[a] = x[a] + x[b]; x[d] ^= x[a]; x[d] = BOOST_BEAST_CHACHA_ROTL32(x[d],  8); \
            x[c] = x[c] + x[d]; x[b] ^= x[c]; x[b] = BOOST_BEAST_CHACHA_ROTL32(x[b],  7)

        for (unsigned i = 0; i < R; i += 2)
        {
            BOOST_BEAST_CHACHA_QUARTERROUND(block_, 0, 4,  8, 12);
            BOOST_BEAST_CHACHA_QUARTERROUND(block_, 1, 5,  9, 13);
            BOOST_BEAST_CHACHA_QUARTERROUND(block_, 2, 6, 10, 14);
            BOOST_BEAST_CHACHA_QUARTERROUND(block_, 3, 7, 11, 15);
            BOOST_BEAST_CHACHA_QUARTERROUND(block_, 0, 5, 10, 15);
            BOOST_BEAST_CHACHA_QUARTERROUND(block_, 1, 6, 11, 12);
            BOOST_BEAST_CHACHA_QUARTERROUND(block_, 2, 7,  8, 13);
            BOOST_BEAST_CHACHA_QUARTERROUND(block_, 3, 4,  9, 14);
        }

        #undef BOOST_BEAST_CHACHA_QUARTERROUND
        #undef BOOST_BEAST_CHACHA_ROTL32
    }

public:
    static constexpr std::size_t state_size = sizeof(chacha::keysetup_);

    using result_type = std::uint32_t;

    chacha(std::uint32_t const* v, std::uint64_t stream)
    {
        for (int i = 0; i < 6; ++i)
            keysetup_[i] = v[i];
        keysetup_[6] = v[6] + (stream & 0xffffffff);
        keysetup_[7] = v[7] + ((stream >> 32) & 0xffffffff);
    }

    std::uint32_t
    operator()()
    {
        if(idx_ == 16)
        {
            idx_ = 0;
            ++ctr_;
            generate_block();
        }
        return block_[idx_++];
    }
};

} // detail
} // beast
} // boost

#endif

/* chacha.hpp
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
*/