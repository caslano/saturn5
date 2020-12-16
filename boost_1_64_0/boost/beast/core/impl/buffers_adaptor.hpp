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
BnzWai/N8s34fIe99FUs/xqeP3ktcB/gdcAi4EJgDfBWYD2wBTiL8WMYPwl4I/AU4E2m3oA3A88E3gI8h/kuAd4OvBl4D/AF4BJgK/Be4OfAxcqelnNlnEOb77Cn/Yb2tN/SXvo74GDgGtIvCc7ncA5svsPO/UX6732Z/oNfAW4K/BQ4CPgqz0tdAdwF+AbP5XwTOB74FvBw4DvAUuC7wLOBbbQP/4Dyfgi8ArgSeA3wI+AC4Mc8T/UT4H3AVcCH+fxv5T3kPAFwW/KfDCwj/z8iXzfgz8ANgL8AzfRunsB2o195Dupv1M/vwP5AFAj5AMBhQC9wBOm+5f5lP587kM/1AHvwueeSP+iC37ryvSx9RYKcK4uLejOoNy/1lkq99QS+Tf7esdY3y9vcpb6/IP2XwBzgV8C+Zpz0hQa/C4GppI8HjiD9aeRnHjCOdvMJPE83xWI3n2sGVY5efjlLlvk2dnne+XzeBayXC8n/JcAeZn71PI7vOTZa5njeKEs+f5T5mqLM1xJlvtZ28t1M+/WKe2Dzek9iu3bsOtv1C2vjw3xeX4Hygnbri25M7LTtus5ufRnKjmC73q7f6yW18Z2yWXfYq9ts1d9G2bBX73Kf1xq7dGWPvurGxC63SXfxdx21r+tVs+Kjsj9383fd46bE9evzupM259Ham7fgfViOsAYhe0miUYAwEcGP0ISwCGEZQhtC0r2JRi7CaIQKhCaExffG7NBjV+yKXbErdsWu2BW7/i/XX2T/X1U5tfP2/6Yt/2f9DOWLaZxHne8nVwLC69ko+1xly7H7XkVjx0zA+sFk31Q4pjnSV1d5dHlwrX55dti5caRNbHddMLj2iTKs59cp3laRt3iLnqvMtXh33hqm+aprSmuq62TNkvb2Dt5IGx81b8pu1ul7xkueSNQN4TXTb6Irb7TB1OuMdHFRr6XrdFbUTdWj0t2J5gRckytfaG+1vmlVJdPr9DojbYJlXShAwXUhpnv/lE651s21ICnXJs8X3Rx6ZvtMc5WnvFreGbR4va5N2nZ1HVX7nBcX3j5fxmJYritv4nHH7/fJ2YQ63kDbsfbp5G0P8jYg3p23fB1vbKNkT8tffif5C9oUP+DCn8f0w+fKX+VMfX2CppM8Bd/piQnufWGRhicfTJCm11fo+AJdu/1gVO/06gT3frBYx5fqBvXvdHEHdYYyXHk7K9H9/fS78gYbMipNX5+g7eT7GWxjuUmOvpC8NbryBnM+PU+kSfjTdRnkaXGSu76a3HmCLZ2ep6ZO6kn9Zmzg/i42u/JUU1s53TypV15KLW/NHWxfOt5yu4fzNta02XDlrc7Sx2rbPmnjJb1bQvi5ti0d5N3t9wzl8hxae7+cT/t1qlzWJPcy/S1q5LH3yzqZSI9Ss5RMdjrKpvLlMB9WXqvKnM/g3qrHO6GHHJseLOU7+tx1yY73geOVVp0+OFrR6IF0cdqxSmsH35loxipBWZaluMvSppOF77d2rBomC/NTlrYukwXlOt67+anhfedxg/Bb5CoLPI2yYiKOcdsZR65uv4919BnR181s7tuoCNpIIfSEPozznPKU1FVv7auv8QX2z3UP1Q3lCNJUcB+w3Y/sPqF0ZSf1Tb/2bX83pJ0U64g2UsG9fCwfe/E2kbLxYzPY/h4lbRTe9u4wf1ec8jm+4bqrPXbKNh800bUr2nVyn1m5bZ9Osws/x+bivpMfNhu3vX7qt6R9fmjjaOVHlWPT09ss4Uquh5/EdtDi5EvGxNIW5HfOpR2QZjD3QWMNXuLTdO2C+QeofYUrJF5m3/fCPYGvStpUSaO9u6RlmzYOkrY349jJfL79HPVRkPGOjPbPUY+mzdl80KY=
*/