//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_BUFFERS_ADAPTOR_HPP
#define BOOST_BEAST_IMPL_BUFFERS_ADAPTOR_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/buffers_adaptor.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/config/workaround.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

//------------------------------------------------------------------------------

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# pragma warning (push)
# pragma warning (disable: 4521) // multiple copy constructors specified
# pragma warning (disable: 4522) // multiple assignment operators specified
#endif

template<class MutableBufferSequence>
template<bool isMutable>
class buffers_adaptor<MutableBufferSequence>::subrange
{
public:
    using value_type = typename std::conditional<
        isMutable,
        net::mutable_buffer,
        net::const_buffer>::type;

    struct iterator;

    // construct from two iterators plus optionally subrange definition
    subrange(
        iter_type first,        // iterator to first buffer in storage
        iter_type last,         // iterator to last buffer in storage
        std::size_t pos = 0,    // the offset in bytes from the beginning of the storage
        std::size_t n =         // the total length of the subrange
        (std::numeric_limits<std::size_t>::max)());

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
    subrange(
        subrange const& other)
        : first_(other.first_)
        , last_(other.last_)
        , first_offset_(other.first_offset_)
        , last_size_(other.last_size_)
    {
    }

    subrange& operator=(
        subrange const& other)
    {
        first_ = other.first_;
        last_ = other.last_;
        first_offset_ = other.first_offset_;
        last_size_ = other.last_size_;
        return *this;
    }
#else
    subrange(
        subrange const&) = default;
    subrange& operator=(
        subrange const&) = default;
#endif

    // allow conversion from mutable to const
    template<bool isMutable_ = isMutable, typename
        std::enable_if<!isMutable_>::type * = nullptr>
    subrange(subrange<true> const &other)
        : first_(other.first_)
        , last_(other.last_)
        , first_offset_(other.first_offset_)
        , last_size_(other.last_size_)
    {
    }

    iterator
    begin() const;

    iterator
    end() const;

private:

    friend subrange<!isMutable>;

    void
    adjust(
        std::size_t pos,
        std::size_t n);

private:
    // points to the first buffer in the sequence
    iter_type first_;

    // Points to one past the end of the underlying buffer sequence
    iter_type last_;

    // The initial offset into the first buffer
    std::size_t first_offset_;

    // how many bytes in the penultimate buffer are used (if any)
    std::size_t last_size_;
};

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# pragma warning (pop)
#endif

//------------------------------------------------------------------------------

template<class MutableBufferSequence>
template<bool isMutable>
struct buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
    iterator
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename
        buffers_adaptor<MutableBufferSequence>::
        template subrange<isMutable>::
        value_type;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;

    iterator(
        subrange<isMutable> const *parent,
        iter_type it);

    iterator();

    value_type
    operator*() const;

    pointer
    operator->() const = delete;

    iterator &
    operator++();

    iterator
    operator++(int);

    iterator &
    operator--();

    iterator
    operator--(int);

    bool
    operator==(iterator const &b) const;

    bool
    operator!=(iterator const &b) const;

private:

    subrange<isMutable> const *parent_;
    iter_type it_;
};

//------------------------------------------------------------------------------

template<class MutableBufferSequence>
auto
buffers_adaptor<MutableBufferSequence>::
end_impl() const ->
    iter_type
{
    return out_ == end_ ? end_ : std::next(out_);
}

template<class MutableBufferSequence>
buffers_adaptor<MutableBufferSequence>::
buffers_adaptor(
    buffers_adaptor const& other,
    std::size_t nbegin,
    std::size_t nout,
    std::size_t nend)
    : bs_(other.bs_)
    , begin_(std::next(bs_.begin(), nbegin))
    , out_(std::next(bs_.begin(), nout))
    , end_(std::next(bs_.begin(), nend))
    , max_size_(other.max_size_)
    , in_pos_(other.in_pos_)
    , in_size_(other.in_size_)
    , out_pos_(other.out_pos_)
    , out_end_(other.out_end_)
{
}

template<class MutableBufferSequence>
buffers_adaptor<MutableBufferSequence>::
buffers_adaptor(MutableBufferSequence const& bs)
    : bs_(bs)
    , begin_(net::buffer_sequence_begin(bs_))
    , out_  (net::buffer_sequence_begin(bs_))
    , end_  (net::buffer_sequence_begin(bs_))
    , max_size_(
        [&bs]
        {
            return buffer_bytes(bs);
        }())
{
}

template<class MutableBufferSequence>
template<class... Args>
buffers_adaptor<MutableBufferSequence>::
buffers_adaptor(
    boost::in_place_init_t, Args&&... args)
    : bs_{std::forward<Args>(args)...}
    , begin_(net::buffer_sequence_begin(bs_))
    , out_  (net::buffer_sequence_begin(bs_))
    , end_  (net::buffer_sequence_begin(bs_))
    , max_size_(
        [&]
        {
            return buffer_bytes(bs_);
        }())
{
}

template<class MutableBufferSequence>
buffers_adaptor<MutableBufferSequence>::
buffers_adaptor(buffers_adaptor const& other)
    : buffers_adaptor(
        other,
        std::distance<iter_type>(
            net::buffer_sequence_begin(other.bs_),
            other.begin_),
        std::distance<iter_type>(
            net::buffer_sequence_begin(other.bs_),
            other.out_),
        std::distance<iter_type>(
            net::buffer_sequence_begin(other.bs_),
            other.end_))
{
}

template<class MutableBufferSequence>
auto
buffers_adaptor<MutableBufferSequence>::
operator=(buffers_adaptor const& other) ->
    buffers_adaptor&
{
    if(this == &other)
        return *this;
    auto const nbegin = std::distance<iter_type>(
        net::buffer_sequence_begin(other.bs_),
            other.begin_);
    auto const nout = std::distance<iter_type>(
        net::buffer_sequence_begin(other.bs_),
            other.out_);
    auto const nend = std::distance<iter_type>(
        net::buffer_sequence_begin(other.bs_),
            other.end_);
    bs_ = other.bs_;
    begin_ = std::next(
        net::buffer_sequence_begin(bs_), nbegin);
    out_ =   std::next(
        net::buffer_sequence_begin(bs_), nout);
    end_ =   std::next(
        net::buffer_sequence_begin(bs_), nend);
    max_size_ = other.max_size_;
    in_pos_ = other.in_pos_;
    in_size_ = other.in_size_;
    out_pos_ = other.out_pos_;
    out_end_ = other.out_end_;
    return *this;
}

//

template<class MutableBufferSequence>
auto
buffers_adaptor<MutableBufferSequence>::
data() const noexcept ->
    const_buffers_type
{
    return const_buffers_type(
        begin_, end_,
        in_pos_, in_size_);
}

template<class MutableBufferSequence>
auto
buffers_adaptor<MutableBufferSequence>::
data() noexcept ->
    mutable_buffers_type
{
    return mutable_buffers_type(
        begin_, end_,
        in_pos_, in_size_);
}

template<class MutableBufferSequence>
auto
buffers_adaptor<MutableBufferSequence>::
prepare(std::size_t n) ->
    mutable_buffers_type
{
    auto prepared = n;
    end_ = out_;
    if(end_ != net::buffer_sequence_end(bs_))
    {
        auto size = buffer_bytes(*end_) - out_pos_;
        if(n > size)
        {
            n -= size;
            while(++end_ !=
                net::buffer_sequence_end(bs_))
            {
                size = buffer_bytes(*end_);
                if(n < size)
                {
                    out_end_ = n;
                    n = 0;
                    ++end_;
                    break;
                }
                n -= size;
                out_end_ = size;
            }
        }
        else
        {
            ++end_;
            out_end_ = out_pos_ + n;
            n = 0;
        }
    }
    if(n > 0)
        BOOST_THROW_EXCEPTION(std::length_error{
            "buffers_adaptor too long"});
    return mutable_buffers_type(out_, end_, out_pos_, prepared);
}

template<class MutableBufferSequence>
void
buffers_adaptor<MutableBufferSequence>::
commit(std::size_t n) noexcept
{
    if(out_ == end_)
        return;
    auto const last = std::prev(end_);
    while(out_ != last)
    {
        auto const avail =
            buffer_bytes(*out_) - out_pos_;
        if(n < avail)
        {
            out_pos_ += n;
            in_size_ += n;
            return;
        }
        ++out_;
        n -= avail;
        out_pos_ = 0;
        in_size_ += avail;
    }

    n = std::min<std::size_t>(
        n, out_end_ - out_pos_);
    out_pos_ += n;
    in_size_ += n;
    if(out_pos_ == buffer_bytes(*out_))
    {
        ++out_;
        out_pos_ = 0;
        out_end_ = 0;
    }
}

template<class MutableBufferSequence>
void
buffers_adaptor<MutableBufferSequence>::
consume(std::size_t n) noexcept
{
    while(begin_ != out_)
    {
        auto const avail =
            buffer_bytes(*begin_) - in_pos_;
        if(n < avail)
        {
            in_size_ -= n;
            in_pos_ += n;
            return;
        }
        n -= avail;
        in_size_ -= avail;
        in_pos_ = 0;
        ++begin_;
    }
    auto const avail = out_pos_ - in_pos_;
    if(n < avail)
    {
        in_size_ -= n;
        in_pos_ += n;
    }
    else
    {
        in_size_ -= avail;
        in_pos_ = out_pos_;
    }
}

template<class MutableBufferSequence>
auto
buffers_adaptor<MutableBufferSequence>::
    make_subrange(std::size_t pos, std::size_t n) ->
        subrange<true>
{
    return subrange<true>(
        begin_, net::buffer_sequence_end(bs_),
        in_pos_ + pos, n);
}

template<class MutableBufferSequence>
auto
buffers_adaptor<MutableBufferSequence>::
    make_subrange(std::size_t pos, std::size_t n) const ->
        subrange<false>
{
    return subrange<false>(
        begin_, net::buffer_sequence_end(bs_),
        in_pos_ + pos, n);
}

// -------------------------------------------------------------------------
// subrange

template<class MutableBufferSequence>
template<bool isMutable>
buffers_adaptor<MutableBufferSequence>::
subrange<isMutable>::
subrange(
    iter_type first,  // iterator to first buffer in storage
    iter_type last,   // iterator to last buffer in storage
    std::size_t pos,        // the offset in bytes from the beginning of the storage
    std::size_t n)         // the total length of the subrange
    : first_(first)
    , last_(last)
    , first_offset_(0)
    , last_size_((std::numeric_limits<std::size_t>::max)())
{
    adjust(pos, n);
}

template<class MutableBufferSequence>
template<bool isMutable>
void
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
adjust(
    std::size_t pos,
    std::size_t n)
{
    if (n == 0)
        last_ = first_;

    if (first_ == last_)
    {
        first_offset_ = 0;
        last_size_ = 0;
        return;
    }

    auto is_last = [this](iter_type iter) {
        return std::next(iter) == last_;
    };


    pos += first_offset_;
    while (pos)
    {
        auto adjust = (std::min)(pos, first_->size());
        if (adjust >= first_->size())
        {
            ++first_;
            first_offset_ = 0;
            pos -= adjust;
        }
        else
        {
            first_offset_ = adjust;
            pos = 0;
            break;
        }
    }

    auto current = first_;
    auto max_elem = current->size() - first_offset_;
    if (is_last(current))
    {
        // both first and last element
        last_size_ = (std::min)(max_elem, n);
        last_ = std::next(current);
        return;
    }
    else if (max_elem >= n)
    {
        last_ = std::next(current);
        last_size_ = n;
    }
    else
    {
        n -= max_elem;
        ++current;
    }

    for (;;)
    {
        max_elem = current->size();
        if (is_last(current))
        {
            last_size_ = (std::min)(n, last_size_);
            return;
        }
        else if (max_elem < n)
        {
            n -= max_elem;
            ++current;
        }
        else
        {
            last_size_ = n;
            last_ = std::next(current);
            return;
        }
    }
}


template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
begin() const ->
iterator
{
    return iterator(this, first_);
}

template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
end() const ->
iterator
{
    return iterator(this, last_);
}

// -------------------------------------------------------------------------
// buffers_adaptor::subrange::iterator

template<class MutableBufferSequence>
template<bool isMutable>
buffers_adaptor<MutableBufferSequence>::
subrange<isMutable>::
iterator::
iterator()
    : parent_(nullptr)
    , it_()
{
}

template<class MutableBufferSequence>
template<bool isMutable>
buffers_adaptor<MutableBufferSequence>::
subrange<isMutable>::
iterator::
iterator(subrange<isMutable> const *parent,
    iter_type it)
    : parent_(parent)
    , it_(it)
{
}

template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
    iterator::
operator*() const ->
    value_type
{
    value_type result = *it_;

    if (it_ == parent_->first_)
        result += parent_->first_offset_;

    if (std::next(it_) == parent_->last_)
    {
        result = value_type(
            result.data(),
            (std::min)(
                parent_->last_size_,
                result.size()));
    }

    return result;
}

template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
    iterator::
operator++() ->
    iterator &
{
    ++it_;
    return *this;
}

template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
    iterator::
operator++(int) ->
    iterator
{
    auto result = *this;
    ++it_;
    return result;
}

template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
    iterator::
operator--() ->
    iterator &
{
    --it_;
    return *this;
}

template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
    iterator::
operator--(int) ->
    iterator
{
    auto result = *this;
    --it_;
    return result;
}

template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
    iterator::
operator==(iterator const &b) const ->
    bool
{
    return it_ == b.it_;
}

template<class MutableBufferSequence>
template<bool isMutable>
auto
buffers_adaptor<MutableBufferSequence>::
    subrange<isMutable>::
    iterator::
operator!=(iterator const &b) const ->
    bool
{
    return !(*this == b);
}

} // beast
} // boost

#endif

/* buffers_adaptor.hpp
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
*/