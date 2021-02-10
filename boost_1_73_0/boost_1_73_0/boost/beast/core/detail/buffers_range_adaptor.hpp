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
M1zrNMZqq2qQKpWSreIYk5FW+YbE2fl0yhmhR9BPQBFe5zoSeagK5Q4YTvhxOv8wnIYno/HwfLrsbHcChTeQwt7V2ztNNXl5V8Wa6VrBIukgDMiuzEVcw+P81xhczDwvQBXX2ny2z2im3WZBst5hQjauMChQzZ0p2rtIhEl49KHw0C8epZ4PiVLWyguJ4tXGkPnYuGOBX4vCNULGqAxEydBnBUVkDTOisCiwfVsrCiL0GuOaxh0RVjpItKcg8OWcny5D3L4zQm2UFIiQnnlfT34fciv9Qt9X1t26TQ+jvCcyVeAJZUdieR6J+DOjvoam8Dukc51Jf5oZ+RyaKpzg75H0/Ytj8wcRX5xNlqPx+ex4OZnPgp1i7JAsvIyVGj3Nkq89pqZf8VYK608PJnOL9H/EPhkuhwH91nR83XU+7gUaIXbqRqA7FoupP7TWPDBfKsUHifNaEWm0BfTRGZ37LZ6JH6zWYhTCc72AFzyHw+l0D8MCXRdzx+IQzHMqjXY61nk/kVF1zXNfQvR+LNifo7MP88UooFfbAJj9B7OFsxgpreqx2oEQ+VrcWYpzKYqq/DZc8+GBGYaTA4/C+Sd69o4jbebUuwSPLIHoosYbUVoaVDiFfuNkh8K1/eg7jX+GKku/JlesO+ynbox7
*/