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