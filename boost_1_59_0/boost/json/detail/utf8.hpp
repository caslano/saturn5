//
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_UTF8_HPP
#define BOOST_JSON_DETAIL_UTF8_HPP

#include <cstddef>
#include <cstring>
#include <cstdint>

BOOST_JSON_NS_BEGIN
namespace detail {

template<int N>
std::uint32_t
load_little_endian(void const* p)
{
    // VFALCO do we need to initialize this to 0?
    std::uint32_t v;
    std::memcpy(&v, p, N);
#ifdef BOOST_JSON_BIG_ENDIAN
    v = ((v & 0xFF000000) >> 24) |
        ((v & 0x00FF0000) >>  8) |
        ((v & 0x0000FF00) <<  8) |
        ((v & 0x000000FF) << 24);
#endif
    return v;
}

inline
uint16_t
classify_utf8(char c)
{
    // 0x000 = invalid
    // 0x102 = 2 bytes, second byte [80, BF]
    // 0x203 = 3 bytes, second byte [A0, BF]
    // 0x303 = 3 bytes, second byte [80, BF]
    // 0x403 = 3 bytes, second byte [80, 9F]
    // 0x504 = 4 bytes, second byte [90, BF]
    // 0x604 = 4 bytes, second byte [80, BF]
    // 0x704 = 4 bytes, second byte [80, 8F]
    static constexpr uint16_t first[128]
    {
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,

       0x000, 0x000, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102,
       0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102,
       0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102,
       0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102, 0x102,
       0x203, 0x303, 0x303, 0x303, 0x303, 0x303, 0x303, 0x303,
       0x303, 0x303, 0x303, 0x303, 0x303, 0x403, 0x303, 0x303,
       0x504, 0x604, 0x604, 0x604, 0x704, 0x000, 0x000, 0x000,
       0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    };
    return first[static_cast<unsigned char>(c)];
}

inline
bool
is_valid_utf8(const char* p, uint16_t first)
{
    uint32_t v;
    switch(first >> 8)
    {
    default:
        return false;

    // 2 bytes, second byte [80, BF]
    case 1:
        v = load_little_endian<2>(p);
        return (v & 0xC000) == 0x8000;

    // 3 bytes, second byte [A0, BF]
    case 2:
        v = load_little_endian<3>(p);
        std::memcpy(&v, p, 3);
        return (v & 0xC0E000) == 0x80A000;

    // 3 bytes, second byte [80, BF]
    case 3:
        v = load_little_endian<3>(p);
        return (v & 0xC0C000) == 0x808000;

    // 3 bytes, second byte [80, 9F]
    case 4:
        v = load_little_endian<3>(p);
        return (v & 0xC0E000) == 0x808000;

    // 4 bytes, second byte [90, BF]
    case 5:
        v = load_little_endian<4>(p);
        return (v & 0xC0C0FF00) + 0x7F7F7000 <= 0x2F00;

    // 4 bytes, second byte [80, BF]
    case 6:
        v = load_little_endian<4>(p);
        return (v & 0xC0C0C000) == 0x80808000;

    // 4 bytes, second byte [80, 8F]
    case 7:
        v = load_little_endian<4>(p);
        return (v & 0xC0C0F000) == 0x80808000;
    }
}

class utf8_sequence
{
    char seq_[4];
    uint16_t first_;
    uint8_t size_;

public:
    void
    save(
        const char* p,
        std::size_t remain) noexcept
    {
        first_ = classify_utf8(*p & 0x7F);
        if(remain >= length())
            size_ = length();
        else
            size_ = static_cast<uint8_t>(remain);
        std::memcpy(seq_, p, size_);
    }

    uint8_t
    length() const noexcept
    {
        return first_ & 0xFF;
    }

    bool
    complete() const noexcept
    {
        return size_ >= length();
    }

    // returns true if complete
    bool
    append(
        const char* p,
        std::size_t remain) noexcept
    {
        if(BOOST_JSON_UNLIKELY(needed() == 0))
            return true;
        if(BOOST_JSON_LIKELY(remain >= needed()))
        {
            std::memcpy(
                seq_ + size_, p, needed());
            size_ = length();
            return true;
        }
        if(BOOST_JSON_LIKELY(remain > 0))
        {
            std::memcpy(seq_ + size_, p, remain);
            size_ += static_cast<uint8_t>(remain);
        }
        return false;
    }

    const char*
    data() const noexcept
    {
        return seq_;
    }

    uint8_t
    needed() const noexcept
    {
        return length() - size_;
    }

    bool
    valid() const noexcept
    {
        BOOST_ASSERT(size_ >= length());
        return is_valid_utf8(seq_, first_);
    }
};

} // detail
BOOST_JSON_NS_END

#endif

/* utf8.hpp
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
*/