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