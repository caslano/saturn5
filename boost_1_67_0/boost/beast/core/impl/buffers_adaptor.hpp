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