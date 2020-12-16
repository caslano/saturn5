//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_BUFFERS_PREFIX_HPP
#define BOOST_BEAST_IMPL_BUFFERS_PREFIX_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/config/workaround.hpp>
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

template<class Buffers>
class buffers_prefix_view<Buffers>::const_iterator
{
    friend class buffers_prefix_view<Buffers>;

    buffers_prefix_view const* b_ = nullptr;
    std::size_t remain_ = 0;
    iter_type it_{};

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

    BOOST_STATIC_ASSERT(std::is_same<
        typename const_iterator::value_type,
        typename buffers_prefix_view::value_type>::value);

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
        value_type v(*it_);
        if(remain_ < v.size())
            return {v.data(), remain_};
        return v;
    }

    pointer
    operator->() const = delete;

    const_iterator&
    operator++()
    {
        value_type const v = *it_++;
        remain_ -= v.size();
        return *this;
    }

    const_iterator
    operator++(int)
    {
        auto temp = *this;
        value_type const v = *it_++;
        remain_ -= v.size();
        return temp;
    }

    const_iterator&
    operator--()
    {
        value_type const v = *--it_;
        remain_ += v.size();
        return *this;
    }

    const_iterator
    operator--(int)
    {
        auto temp = *this;
        value_type const v = *--it_;
        remain_ += v.size();
        return temp;
    }

private:
    const_iterator(
        buffers_prefix_view const& b,
        std::true_type)
        : b_(&b)
        , remain_(b.remain_)
        , it_(b_->end_)
    {
    }

    const_iterator(
        buffers_prefix_view const& b,
        std::false_type)
        : b_(&b)
        , remain_(b_->size_)
        , it_(net::buffer_sequence_begin(b_->bs_))
    {
    }
};

//------------------------------------------------------------------------------

template<class Buffers>
void
buffers_prefix_view<Buffers>::
setup(std::size_t size)
{
    size_ = 0;
    remain_ = 0;
    end_ = net::buffer_sequence_begin(bs_);
    auto const last = bs_.end();
    while(end_ != last)
    {
        auto const len = buffer_bytes(*end_++);
        if(len >= size)
        {
            size_ += size;

            // by design, this subtraction can wrap
            BOOST_STATIC_ASSERT(std::is_unsigned<
                decltype(remain_)>::value);
            remain_ = size - len;
            break;
        }
        size -= len;
        size_ += len;
    }
}

template<class Buffers>
buffers_prefix_view<Buffers>::
buffers_prefix_view(
    buffers_prefix_view const& other,
    std::size_t dist)
    : bs_(other.bs_)
    , size_(other.size_)
    , remain_(other.remain_)
    , end_(std::next(bs_.begin(), dist))
{
}

template<class Buffers>
buffers_prefix_view<Buffers>::
buffers_prefix_view(buffers_prefix_view const& other)
    : buffers_prefix_view(other,
        std::distance<iter_type>(
            net::buffer_sequence_begin(other.bs_),
                other.end_))
{
}

template<class Buffers>
auto
buffers_prefix_view<Buffers>::
operator=(buffers_prefix_view const& other) ->
    buffers_prefix_view&
{
    auto const dist = std::distance<iter_type>(
        net::buffer_sequence_begin(other.bs_),
        other.end_);
    bs_ = other.bs_;
    size_ = other.size_;
    remain_ = other.remain_;
    end_ = std::next(
        net::buffer_sequence_begin(bs_),
            dist);
    return *this;
}

template<class Buffers>
buffers_prefix_view<Buffers>::
buffers_prefix_view(
    std::size_t size,
    Buffers const& bs)
    : bs_(bs)
{
    setup(size);
}

template<class Buffers>
template<class... Args>
buffers_prefix_view<Buffers>::
buffers_prefix_view(
    std::size_t size,
    boost::in_place_init_t,
    Args&&... args)
    : bs_(std::forward<Args>(args)...)
{
    setup(size);
}

template<class Buffers>
auto
buffers_prefix_view<Buffers>::
begin() const ->
    const_iterator
{
    return const_iterator{
        *this, std::false_type{}};
}

template<class Buffers>
auto
buffers_prefix_view<Buffers>::
end() const ->
    const_iterator
{
    return const_iterator{
        *this, std::true_type{}};
}

//------------------------------------------------------------------------------

template<>
class buffers_prefix_view<net::const_buffer>
    : public net::const_buffer
{
public:
    using net::const_buffer::const_buffer;
    buffers_prefix_view(buffers_prefix_view const&) = default;
    buffers_prefix_view& operator=(buffers_prefix_view const&) = default;

    buffers_prefix_view(
        std::size_t size,
        net::const_buffer buffer)
        : net::const_buffer(
            buffer.data(),
            std::min<std::size_t>(size, buffer.size())
        #if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
            , buffer.get_debug_check()
        #endif
            )
    {
    }

    template<class... Args>
    buffers_prefix_view(
        std::size_t size,
        boost::in_place_init_t,
        Args&&... args)
        : buffers_prefix_view(size,
            net::const_buffer(
                std::forward<Args>(args)...))
    {
    }
};

//------------------------------------------------------------------------------

template<>
class buffers_prefix_view<net::mutable_buffer>
    : public net::mutable_buffer
{
public:
    using net::mutable_buffer::mutable_buffer;
    buffers_prefix_view(buffers_prefix_view const&) = default;
    buffers_prefix_view& operator=(buffers_prefix_view const&) = default;

    buffers_prefix_view(
        std::size_t size,
        net::mutable_buffer buffer)
        : net::mutable_buffer(
            buffer.data(),
            std::min<std::size_t>(size, buffer.size())
        #if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
            , buffer.get_debug_check()
        #endif
            )
    {
    }

    template<class... Args>
    buffers_prefix_view(
        std::size_t size,
        boost::in_place_init_t,
        Args&&... args)
        : buffers_prefix_view(size,
            net::mutable_buffer(
                std::forward<Args>(args)...))
    {
    }
};

} // beast
} // boost

#endif

/* buffers_prefix.hpp
suR3gSxviCxSrk2WtiGOfoB9Q6FGFo4TdLKQbgNJ3yz8exvpf/79D8qymeZ7e9FQ93e/yEUWji10cggN64TvvWQPzc12QZ0E3nkp1zYembuVe99crJHDMR7RyQR6Z/+siFT9FHeifuz9syrb9rtTNsxdNr+7bBzLRJSLtBtY/KwGyDh/oWTzd0K2HJtstvJt71NBfngbXIVyGt3l43hIKxvpukeck2vsRFvUzMnZxlLL8t3Hn002mYLjDO03M/J3bszJ+SLsSzbkKuRcw47kp9nKj/v4l2tozIsStrScHzolLfpzkHW8rd7auXbNuQYbb6ImnZ6Qt90164h6WgOcF/NVRF9FurMx179PotQK837tF48OnNy64q4L+jXe+P5t36f983wMuftC6rqzSX9Q/jVl3VjOScxCmMC/d0bgOZTcnyN27vZzKOlnxsSb6cfjFmCQro108S5060j3K/2A/GahW026OBe6+0n3AP2uPKjouK8EkOBC95knQPc5MB74BZB02N+hf95SPu8RPu9Ry/Nym/TyPUO6Zynfc4oOIQLdctK9SrrXLHSFEei+Jd13pFtjoStq0tffKtJ9yvr7zEJXHOF5P5JuLZ/3k4XOH0GfaayHdKB5P8NSD40R6i+HdL1Zf30sdE0RnuchnZfP62aha44g35eU7yvK97VFvpYIdC+SrpV0L1nPZSXdBkb4uaRvkO5t0r0DTKIfI/UeRpDzI8r5MeX8BKjewwh0CaRLJF2ShW51hPr4mnSrWR/fkG62QXtWQAXpUoBVpBtG/zvD6fdpL/p92ob+kUYABwK3BY5n+v7A3YEH8jzgQ3m/mPFSxlV7OE8v7wLqeSHf50UWuuYIdE+Q7knSPWWE5G0h3ZUu8o6jX6/x9ItVBMwH7g/cjv7UEIwDKMdE4HTgJGAVzy/287zkRuDB9PN1iPWc4PP1fLeQ79vJ9x1WPUWg+5B0K0n3kVVPEeiS2S5S2J5Sgeq9IV03F7qNSZcF9AJ7km4ewlLSzSXdhsBjSZfB9rQxsA9wCNtRFvXeEzgUmA3cn+mTeB72IcAc6r03sJbnYs9ivmMZP8GMU/5ig/ZtwFrhh3M/5OcwtusS+sWayvZcSv9wZWzH04HFjJfTb9503v9WfndoZ0Y7NTxH/Fst5nOOxK2NLOcw++kXbSbfm+uABwCPAU5m/HDmO4vnTZ/H+5fQL9cVjF9LP1wLGb+F/rPuYHwJ8Erg4/Rb9zqwGbiS/us+Zj72e7R5go5d+r27WX/3ADPph64n46p9X6Lvh97ysN9kP/QOMOgXrYl0KaSz+kVbQrp7SXcfMBH4ADAJeD8wmXHV7i/R9/uPs7wngHHAJ63tPgLdw6RbSrpHFB3tVDTv2Wuke53v2QoLXWuE571Eupf5vFesvxNaPSONdO9TXx9YfyciPO8Z0j3L5z2n6HDN18u3KelyKV8/63gtAt32pCsg3UigOlecdLNc2uEeyJcN3BO4K3Bv4HTgOAv9UtJv7kIP+3xpx/sBc4BFwL6MKz1F4Pt88n0B+b7QqqdL9fq9lXS3Ub8tVj1FoLuRdDeR7mYLXW4EujtJt5h0dyk6hAh0N5BuAekWKjquY2r0cjHpLqFe5lvoiiI87zLSXc7nXWGhK47wvDNIdyafd5aFzh+B7hzSnUu6Juu4NgKfzaS7hnxea+2/SLdbWP8FRL6ewJ2BQ4C7ArcGFgK3MWmA2wFHq/bLdR7N+HMK+TiM/B/OftCn6LmmAujuQn886U8AUj/iD/NEC31aBPo5pD+a9MeQ/ljr+xuBfi7pTyH9qaQ/zUKfH4G+jvT1pG8g/UxFz3lyjf5KSD+V+iul/sos9EURnj+N9NP5/Ao=
*/