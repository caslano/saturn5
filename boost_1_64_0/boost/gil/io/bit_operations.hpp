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
zO+fYOiZhMwd95xJGNGpZEcyyPygWZm1zsKj3RzA0mIee2oex3uhOnwt4hAh2kfTX/CcbloNQG3U2qHjHe6u/xyv4y2QzPXnJOkvwg9SP5KugcR5eY6MsHuApJiNOsI++yU0LI234B3P8WlOfOk0N9I0z+T4mvbvW3Q8vYD27/FSZjg9wx3tGDYiV1vPdOYckzaggLbzfGs9eX2zh+Z1oo58knL020+FlRHEk/2hImdfRf/vfTT7ixCgtgZIYXJ/iZP8pYJkbvSR7PeDn/d/kXRdSIGXtkv2e+Zo9iOs7P+wARqWQYMzRvPWFHFznrEF9KZasNVAMl3hd17XF3sTA41koCAECpp2kIsd2V0QfG+cz+GgDV5tytl92wTiHLhrf/plr+RL6VHZiB63Faff9SMK+17aM2yxjMYrTdCyeF06oR/CjuFYLximEhIegxuNYSYeVs4qz7lxpY8JzIrT5pRxV8u/qIybdpeyiy0p/6LITzrl7I4A6VG/f8V0NaP9wybkcngcD1BznRVPXI9nTqd1Qo34WGdpIvnycxEmemOiLo/s+kQyYtaCI7tr0CEY4josKw0k3q5Ht5LggyuRkI29OTHxetGawl/CNhMg/2yOU/jfQMAGzZQOyHp2shdXZKM3OnzE3pVREL8KSYBkHobdE2bRizgBdAdSc7hwuKNwVeFC4YKLEAvz9Oeo/oQq0mA7uACi/umjgdfYikMFcovcQvabArfcQuvLIjSfspbAbYWbDTcH03g7j+Djd7T8xu7Tn90W1N+a3NiNCgeInaEYAhMKeVpubI4lsYBZ6mfigFUDLD+5RpMAe8293HiIvDtj86dSCnHRkvNCoPuhhNqpSI6m66DiBbohFocQ1FAfkyzgRpvKB+tPAFOCDOvPGk3XfNiMfUKYgdjRiLU7Yo3L5Pl9xe7jT2IKKIq3mL1Gf3jkEeveQzITVxIIES4V1EJSa87dyk9L/aVb+YoGRupPE/xkBlaT/8Hyv7Iy6spDU/n/6D3+lvhv3utggWWbGU9Z95IgtQU0z5tWpab12buvpkAAljUpHWSmlt6M/fhx3iduuFZaaH7/110LyuZPNPXsdp9jB/NsG3kxOva/48IxhvHlCZl8N2iWswQGnLdrL6gK/1ajQhH8W+OyRfBvZcsq/NuA8e8oIsucLW7ot4j1bAHYsqQBEve/PuLC5DkEMwkxmh+u9ncGGUCEG8/7WFuvphm49PXOzaAGb4GzYsMqrTFINP6LGv/qUKSxcKVqzPdoPNOhhMYq1PgzXlh3iL0rqegWFa0VRar/M0vRbTAkuHkbXFVZ/fxdRQFCI4b5Jk5UrkVPhVtLg7JuY8ZnpdWxKyhWorRQmkYVi7SrRFqO5g5tikXa2oq0vK870lqeSD84VyJSjA9BjHDHu/o/x3tDlgY1glOyr1zZl2+BCJtt7b2Acqu6iUvtETALwXGn930hV5FkxSDe6eQR3sYmgFSIAW/UOmcWPObOD6IM90BgxRhG9s5xoObGzveT+z/czPGjOSRBl03sumc2YhEho4skNPCVL9RGwaFmbPui8ZUKUxX+NqbLreJxUfH7RlERJCrKq4pGqiL/I1WRQRUFPP/eH2HdmFjnSEgCgd2A8xs+tZcnRcfLAQGZWuD8kpwGyikk5wMSqoDAurATYU52ITNA4RLedLC5//W5nutf5cXL6YwX0zC/DOTOnpV9DOeLVHP0rKdWR2++6w/2k6LGvs3Zlvw14Lvh+ZqRsFgJM5iQmiTMVEIBCRVISAOBm3LOl7jwOkrYilF36RYILyh7t7MD2UnCVtSww2S3VcIaym8joZkSNpLwyS0pk63OZeQ8AI7CGSp5tjOL5DtnJEA=
*/