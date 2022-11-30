//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_BIT_OPERATIONS_HPP
#define BOOST_GIL_IO_BIT_OPERATIONS_HPP

#include <boost/gil/io/typedefs.hpp>

#include <array>
#include <cstddef>
#include <type_traits>

namespace boost { namespace gil { namespace detail {

// 1110 1100 -> 0011 0111
template <typename Buffer, typename IsBitAligned>
struct mirror_bits
{
    mirror_bits(bool) {};

    void operator()(Buffer&) {}
    void operator()(byte_t*, std::size_t){}
};

// The functor will generate a lookup table since the
// mirror operation is quite costly.
template <typename Buffer>
struct mirror_bits<Buffer, std::true_type>
{
    mirror_bits(bool apply_operation = true)
        : apply_operation_(apply_operation)
    {
        if(apply_operation_)
        {
            byte_t i = 0;
            do
            {
                lookup_[i] = mirror(i);
            }
            while (i++ != 255);
        }
   }

    void operator()(Buffer& buffer)
    {
        if (apply_operation_)
            for_each(buffer.begin(), buffer.end(), [this](byte_t& c) { lookup(c); });
    }

    void operator()(byte_t *dst, std::size_t size)
    {
        for (std::size_t i = 0; i < size; ++i)
        {
            lookup(*dst);
            ++dst;
        }
    }

private:

    void lookup(byte_t& c)
    {
        c = lookup_[c];
    }

    static byte_t mirror(byte_t c)
    {
        byte_t result = 0;
        for (int i = 0; i < 8; ++i)
        {
            result = result << 1;
            result |= (c & 1);
            c = c >> 1;
        }

        return result;
    }

    std::array<byte_t, 256> lookup_;
    bool apply_operation_;

};

// 0011 1111 -> 1100 0000
template <typename Buffer, typename IsBitAligned>
struct negate_bits
{
    void operator()(Buffer&) {};
};

template <typename Buffer>
struct negate_bits<Buffer, std::true_type>
{
    void operator()(Buffer& buffer)
    {
        for_each(buffer.begin(), buffer.end(),
            negate_bits<Buffer, std::true_type>::negate);
    }

    void operator()(byte_t* dst, std::size_t size)
    {
        for (std::size_t i = 0; i < size; ++i)
        {
            negate(*dst);
            ++dst;
        }
    }

private:

    static void negate(byte_t& b)
    {
        b = ~b;
    }
};

// 11101100 -> 11001110
template <typename Buffer, typename IsBitAligned>
struct swap_half_bytes
{
    void operator()(Buffer&) {};
};

template <typename Buffer>
struct swap_half_bytes<Buffer, std::true_type>
{
    void operator()(Buffer& buffer)
    {
        for_each(buffer.begin(), buffer.end(),
            swap_half_bytes<Buffer, std::true_type>::swap);
    }

    void operator()(byte_t* dst, std::size_t size)
    {
        for (std::size_t i = 0; i < size; ++i)
        {
            swap(*dst);
            ++dst;
        }
    }

private:

    static void swap(byte_t& c)
    {
        c = ((c << 4) & 0xF0) | ((c >> 4) & 0x0F);
    }
};

template <typename Buffer>
struct do_nothing
{
   do_nothing() = default;

   void operator()(Buffer&) {}
};

/// Count consecutive zeros on the right
template <typename T>
inline unsigned int trailing_zeros(T x) noexcept
{
    unsigned int n = 0;

    x = ~x & (x - 1);
    while (x)
    {
        n = n + 1;
        x = x >> 1;
    }

    return n;
}

/// Counts ones in a bit-set
template <typename T>
inline
unsigned int count_ones(T x) noexcept
{
    unsigned int n = 0;

    while (x)
    {
        // clear the least significant bit set
        x &= x - 1;
        ++n;
    }

    return n;
}

}}} // namespace boost::gil::detail

#endif

/* bit_operations.hpp
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
*/