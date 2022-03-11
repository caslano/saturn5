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