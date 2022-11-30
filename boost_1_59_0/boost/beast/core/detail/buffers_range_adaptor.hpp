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
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
*/