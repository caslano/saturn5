//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_BUFFERS_SUFFIX_HPP
#define BOOST_BEAST_IMPL_BUFFERS_SUFFIX_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/type_traits.hpp>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

template<class Buffers>
class buffers_suffix<Buffers>::const_iterator
{
    friend class buffers_suffix<Buffers>;

    using iter_type = buffers_iterator_type<Buffers>;

    iter_type it_{};
    buffers_suffix const* b_ = nullptr;

public:
#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
    using value_type = typename std::conditional<
        boost::is_convertible<typename
            std::iterator_traits<iter_type>::value_type,
                net::mutable_buffer>::value,
                    net::mutable_buffer,
                        net::const_buffer>::type;
#else
    using value_type = buffers_type<Buffers>;
#endif
    using pointer = value_type const*;
    using reference = value_type;
    using difference_type = std::ptrdiff_t;
    using iterator_category =
        std::bidirectional_iterator_tag;

    const_iterator() = default;
    const_iterator(
        const_iterator const& other) = default;
    const_iterator& operator=(
        const_iterator const& other) = default;

    bool
    operator==(const_iterator const& other) const
    {
        return b_ == other.b_ && it_ == other.it_;
    }

    bool
    operator!=(const_iterator const& other) const
    {
        return !(*this == other);
    }

    reference
    operator*() const
    {
        if(it_ == b_->begin_)
            return value_type(*it_) + b_->skip_;
        return value_type(*it_);
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

private:
    const_iterator(
        buffers_suffix const& b,
        iter_type it)
        : it_(it)
        , b_(&b)
    {
    }
};

//------------------------------------------------------------------------------

template<class Buffers>
buffers_suffix<Buffers>::
buffers_suffix()
    : begin_(net::buffer_sequence_begin(bs_))
{
}

template<class Buffers>
buffers_suffix<Buffers>::
buffers_suffix(buffers_suffix const& other)
    : buffers_suffix(other,
        std::distance<iter_type>(
            net::buffer_sequence_begin(
                other.bs_), other.begin_))
{
}

template<class Buffers>
buffers_suffix<Buffers>::
buffers_suffix(Buffers const& bs)
    : bs_(bs)
    , begin_(net::buffer_sequence_begin(bs_))
{
    static_assert(
        net::is_const_buffer_sequence<Buffers>::value ||
        net::is_mutable_buffer_sequence<Buffers>::value,
            "BufferSequence type requirements not met");
}

template<class Buffers>
template<class... Args>
buffers_suffix<Buffers>::
buffers_suffix(boost::in_place_init_t, Args&&... args)
    : bs_(std::forward<Args>(args)...)
    , begin_(net::buffer_sequence_begin(bs_))
{
    static_assert(sizeof...(Args) > 0,
        "Missing constructor arguments");
    static_assert(
        std::is_constructible<Buffers, Args...>::value,
            "Buffers not constructible from arguments");
}

template<class Buffers>
auto
buffers_suffix<Buffers>::
operator=(buffers_suffix const& other) ->
    buffers_suffix&
{
    auto const dist = std::distance<iter_type>(
        net::buffer_sequence_begin(other.bs_),
            other.begin_);
    bs_ = other.bs_;
    begin_ = std::next(
        net::buffer_sequence_begin(bs_), dist);
    skip_ = other.skip_;
    return *this;
}

template<class Buffers>
auto
buffers_suffix<Buffers>::
begin() const ->
    const_iterator
{
    return const_iterator{*this, begin_};
}

template<class Buffers>
auto
buffers_suffix<Buffers>::
end() const ->
    const_iterator
{
    return const_iterator{*this,
        net::buffer_sequence_end(bs_)};
}

template<class Buffers>
void
buffers_suffix<Buffers>::
consume(std::size_t amount)
{
    auto const end =
        net::buffer_sequence_end(bs_);
    for(;amount > 0 && begin_ != end; ++begin_)
    {
        auto const len =
            buffer_bytes(*begin_) - skip_;
        if(amount < len)
        {
            skip_ += amount;
            break;
        }
        amount -= len;
        skip_ = 0;
    }
}

} // beast
} // boost

#endif

/* buffers_suffix.hpp
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
*/