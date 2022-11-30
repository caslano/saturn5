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
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
*/