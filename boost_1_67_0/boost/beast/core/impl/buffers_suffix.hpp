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