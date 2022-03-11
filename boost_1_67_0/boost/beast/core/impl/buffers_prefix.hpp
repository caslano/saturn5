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