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
mozif9ApfXReHCyPTKETzFtNKbBhFSzRVfhRrDvisUle02BJ893Y6vh3zwYci4hAV53UErLTXl5KIVOqiBgzmlxJKmajrf6OP8SMuMSO3GXG/EbLmSuU5lu606Sm1IUX0pP7iQlkX+IlDVBTifgx5o/iNqZ5GBL+VVbq10tD80bufZERVWxYAvIjRjk2k0m3Jt5pZ2XBnaqzXt1ODJ0cPmNxLPKnQsi3AZl8N/lFs/WI+JJhJQv7lWPSQnipASNTTNJrKakKhv6wkA6jzz911OrVCK8ai+pxnDjCUvwGnoyJ8Pm5AIotF/cXHY4dHQ0o/TdUQWNWpRDPNz0MBTt8tGSXj6ccH9Di+ZIE0v/4cV2hMPK3hVDRzu63MV0+cfbYbCMGBnNMUZr4laGvFTXNrOcilxEJdOM4XtijsrLjngO1wPq6Z7eYnOjTibnmBY4fe+Mg9YG5jJIano1UMenAk18XZi4Vsp/PCukSo9MIrSrZgvHzGDF2WUoTLsu4UpiP1H5P0hHDHaHdCHjhaAhz9chK+ISxwW2lokLynERPVXyRkJpMGyQBp8tumi/XWXRAvl3eI6P43pVgy7Z/dO3htp6B6vb4gIzFzTncnUOpqHijaGcpDdCbJbVari0o8Ae/nTwNOl6Fdv+GzkvOEEWazJHJpjC6LfYVt9fgRI6WrM5X6eaPSJKFoFXvdyk7Yan+WAgL40km6aRm4v1E
*/