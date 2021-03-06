//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BUFFERS_RANGE_ADAPTOR_HPP
#define BOOST_BEAST_DETAIL_BUFFERS_RANGE_ADAPTOR_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <iterator>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

template<class BufferSequence>
class buffers_range_adaptor
{
    BufferSequence b_;

public:
#if BOOST_BEAST_DOXYGEN
    using value_type = __see_below__;
#else
    using value_type = buffers_type<BufferSequence>;
#endif

    class const_iterator
    {
        friend class buffers_range_adaptor;

        using iter_type =
            buffers_iterator_type<BufferSequence>;

        iter_type it_{};

        const_iterator(iter_type const& it)
            : it_(it)
        {
        }

    public:
        using value_type = typename
            buffers_range_adaptor::value_type;
        using pointer = value_type const*;
        using reference = value_type;
        using difference_type = std::ptrdiff_t;
        using iterator_category =
            std::bidirectional_iterator_tag;

        const_iterator() = default;

        bool
        operator==(const_iterator const& other) const
        {
            return it_ == other.it_;
        }

        bool
        operator!=(const_iterator const& other) const
        {
            return !(*this == other);
        }

        reference
        operator*() const
        {
            return *it_;
        }

        pointer
        operator->() const = delete;

        const_iterator&
        operator++()
        {
            ++it_;
            return *this;
        }

        const_iterator
        operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        const_iterator&
        operator--()
        {
            --it_;
            return *this;
        }

        const_iterator
        operator--(int)
        {
            auto temp = *this;
            --(*this);
            return temp;
        }
    };

    explicit
    buffers_range_adaptor(BufferSequence const& b)
        : b_(b)
    {
    }

    const_iterator
    begin() const noexcept
    {
        return {net::buffer_sequence_begin(b_)};
    }

    const_iterator
    end() const noexcept
    {
        return {net::buffer_sequence_end(b_)};
    }
};

} // detail
} // beast
} // boost

#endif

/* buffers_range_adaptor.hpp
JnV4foapgFMhELOcxkDhoZemdPitvpsfl5VYQB7R2x2s0tusnCbHN4TpdpYKV8S2NlngeYHUOvRE7669ErCd8fmIScVcm+jDap1oV8OBozUqVDRrb5iksMX2XqQbrqNXBkKLd3R6cm0R93p/PBEmI0bdI9TSAKrnwBgq3dVndeA5tgyG2wOt8VwahMpUKg7z6idA1OlhFRE5LZ6Am1GBZ5q7CY46zMGiTw6hTo+EwzPv5Hdxlok3dSH20qExKirCZtP9v//m3UBA2pL/eXRtKhiwZVIqBXc/WOiyc6CwiAJAmPn5HVcDWpztZzj8p8V6iQfgznLgwvmGkiPPlNBy1MRmEz1mTBFDbVfEefCaRkVMoB2nd602Hif3IeZtPpId0v6TSaouNnopK0/qjMt6xtKIgHUE/VFCVo/1oSDrG/3eWYhShERGs/te3z/WRNMl4U3Knj0Kzif8sffMqlCyxdyH2tXVCxsddSg82vxEsRge1We5xJMMBpcF8kYV2nHuNF4Og30i5NoYTwYV4OEyvsymPBVJdRWb2Eds+gV8v4VpWR6RXycC09amsQ==
*/