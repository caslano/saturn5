//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_FLAT_BUFFER_HPP
#define BOOST_BEAST_IMPL_FLAT_BUFFER_HPP

#include <boost/core/exchange.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <memory>
#include <stdexcept>

namespace boost {
namespace beast {

/*  Layout:

      begin_     in_          out_        last_      end_
        |<------->|<---------->|<---------->|<------->|
                  |  readable  |  writable  |
*/

template<class Allocator>
basic_flat_buffer<Allocator>::
~basic_flat_buffer()
{
    if(! begin_)
        return;
    alloc_traits::deallocate(
        this->get(), begin_, capacity());
}

template<class Allocator>
basic_flat_buffer<Allocator>::
basic_flat_buffer() noexcept(default_nothrow)
    : begin_(nullptr)
    , in_(nullptr)
    , out_(nullptr)
    , last_(nullptr)
    , end_(nullptr)
    , max_(alloc_traits::max_size(
        this->get()))
{
}

template<class Allocator>
basic_flat_buffer<Allocator>::
basic_flat_buffer(
    std::size_t limit) noexcept(default_nothrow)
    : begin_(nullptr)
    , in_(nullptr)
    , out_(nullptr)
    , last_(nullptr)
    , end_(nullptr)
    , max_(limit)
{
}

template<class Allocator>
basic_flat_buffer<Allocator>::
basic_flat_buffer(Allocator const& alloc) noexcept
    : boost::empty_value<base_alloc_type>(
        boost::empty_init_t{}, alloc)
    , begin_(nullptr)
    , in_(nullptr)
    , out_(nullptr)
    , last_(nullptr)
    , end_(nullptr)
    , max_(alloc_traits::max_size(
        this->get()))
{
}

template<class Allocator>
basic_flat_buffer<Allocator>::
basic_flat_buffer(
    std::size_t limit,
    Allocator const& alloc) noexcept
    : boost::empty_value<base_alloc_type>(
        boost::empty_init_t{}, alloc)
    , begin_(nullptr)
    , in_(nullptr)
    , out_(nullptr)
    , last_(nullptr)
    , end_(nullptr)
    , max_(limit)
{
}

template<class Allocator>
basic_flat_buffer<Allocator>::
basic_flat_buffer(basic_flat_buffer&& other) noexcept
    : boost::empty_value<base_alloc_type>(
        boost::empty_init_t{}, std::move(other.get()))
    , begin_(boost::exchange(other.begin_, nullptr))
    , in_(boost::exchange(other.in_, nullptr))
    , out_(boost::exchange(other.out_, nullptr))
    , last_(boost::exchange(other.last_, nullptr))
    , end_(boost::exchange(other.end_, nullptr))
    , max_(other.max_)
{
}

template<class Allocator>
basic_flat_buffer<Allocator>::
basic_flat_buffer(
    basic_flat_buffer&& other,
    Allocator const& alloc)
    : boost::empty_value<base_alloc_type>(
        boost::empty_init_t{}, alloc)
{
    if(this->get() != other.get())
    {
        begin_ = nullptr;
        in_ = nullptr;
        out_ = nullptr;
        last_ = nullptr;
        end_ = nullptr;
        max_ = other.max_;
        copy_from(other);
        return;
    }

    begin_ = other.begin_;
    in_ = other.in_;
    out_ = other.out_;
    last_ = other.out_; // invalidate
    end_ = other.end_;
    max_ = other.max_;
    BOOST_ASSERT(
        alloc_traits::max_size(this->get()) ==
        alloc_traits::max_size(other.get()));
    other.begin_ = nullptr;
    other.in_ = nullptr;
    other.out_ = nullptr;
    other.last_ = nullptr;
    other.end_ = nullptr;
}

template<class Allocator>
basic_flat_buffer<Allocator>::
basic_flat_buffer(basic_flat_buffer const& other)
    : boost::empty_value<base_alloc_type>(boost::empty_init_t{},
        alloc_traits::select_on_container_copy_construction(
            other.get()))
    , begin_(nullptr)
    , in_(nullptr)
    , out_(nullptr)
    , last_(nullptr)
    , end_(nullptr)
    , max_(other.max_)
{
    copy_from(other);
}

template<class Allocator>
basic_flat_buffer<Allocator>::
basic_flat_buffer(
    basic_flat_buffer const& other,
    Allocator const& alloc)
    : boost::empty_value<base_alloc_type>(
        boost::empty_init_t{}, alloc)
    , begin_(nullptr)
    , in_(nullptr)
    , out_(nullptr)
    , last_(nullptr)
    , end_(nullptr)
    , max_(other.max_)
{
    copy_from(other);
}

template<class Allocator>
template<class OtherAlloc>
basic_flat_buffer<Allocator>::
basic_flat_buffer(
    basic_flat_buffer<OtherAlloc> const& other)
        noexcept(default_nothrow)
    : begin_(nullptr)
    , in_(nullptr)
    , out_(nullptr)
    , last_(nullptr)
    , end_(nullptr)
    , max_(other.max_)
{
    copy_from(other);
}

template<class Allocator>
template<class OtherAlloc>
basic_flat_buffer<Allocator>::
basic_flat_buffer(
    basic_flat_buffer<OtherAlloc> const& other,
    Allocator const& alloc)
    : boost::empty_value<base_alloc_type>(
        boost::empty_init_t{}, alloc)
    , begin_(nullptr)
    , in_(nullptr)
    , out_(nullptr)
    , last_(nullptr)
    , end_(nullptr)
    , max_(other.max_)
{
    copy_from(other);
}

template<class Allocator>
auto
basic_flat_buffer<Allocator>::
operator=(basic_flat_buffer&& other) noexcept ->
    basic_flat_buffer&
{
    if(this == &other)
        return *this;
    move_assign(other, pocma{});
    return *this;
}

template<class Allocator>
auto
basic_flat_buffer<Allocator>::
operator=(basic_flat_buffer const& other) ->
    basic_flat_buffer&
{
    if(this == &other)
        return *this;
    copy_assign(other, pocca{});
    return *this;
}

template<class Allocator>
template<class OtherAlloc>
auto
basic_flat_buffer<Allocator>::
operator=(
    basic_flat_buffer<OtherAlloc> const& other) ->
    basic_flat_buffer&
{
    copy_from(other);
    return *this;
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
reserve(std::size_t n)
{
    if(max_ < n)
        max_ = n;
    if(n > capacity())
        prepare(n - size());
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
shrink_to_fit() noexcept
{
    auto const len = size();

    if(len == capacity())
        return;

    char* p;
    if(len > 0)
    {
        BOOST_ASSERT(begin_);
        BOOST_ASSERT(in_);
#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
            p = alloc(len);
#ifndef BOOST_NO_EXCEPTIONS
        }
        catch(std::exception const&)
        {
            // request could not be fulfilled,
            // squelch the exception
            return;
        }
#endif
        std::memcpy(p, in_, len);
    }
    else
    {
        p = nullptr;
    }
    alloc_traits::deallocate(
        this->get(), begin_, this->capacity());
    begin_ = p;
    in_ = begin_;
    out_ = begin_ + len;
    last_ = out_;
    end_ = out_;
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
clear() noexcept
{
    in_ = begin_;
    out_ = begin_;
    last_ = begin_;
}

//------------------------------------------------------------------------------

template<class Allocator>
auto
basic_flat_buffer<Allocator>::
prepare(std::size_t n) ->
    mutable_buffers_type
{
    auto const len = size();
    if(len > max_ || n > (max_ - len))
        BOOST_THROW_EXCEPTION(std::length_error{
            "basic_flat_buffer too long"});
    if(n <= dist(out_, end_))
    {
        // existing capacity is sufficient
        last_ = out_ + n;
        return{out_, n};
    }
    if(n <= capacity() - len)
    {
        // after a memmove,
        // existing capacity is sufficient
        if(len > 0)
        {
            BOOST_ASSERT(begin_);
            BOOST_ASSERT(in_);
            std::memmove(begin_, in_, len);
        }
        in_ = begin_;
        out_ = in_ + len;
        last_ = out_ + n;
        return {out_, n};
    }
    // allocate a new buffer
    auto const new_size = (std::min<std::size_t>)(
        max_,
        (std::max<std::size_t>)(2 * len, len + n));
    auto const p = alloc(new_size);
    if(begin_)
    {
        BOOST_ASSERT(p);
        BOOST_ASSERT(in_);
        std::memcpy(p, in_, len);
        alloc_traits::deallocate(
            this->get(), begin_, capacity());
    }
    begin_ = p;
    in_ = begin_;
    out_ = in_ + len;
    last_ = out_ + n;
    end_ = begin_ + new_size;
    return {out_, n};
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
consume(std::size_t n) noexcept
{
    if(n >= dist(in_, out_))
    {
        in_ = begin_;
        out_ = begin_;
        return;
    }
    in_ += n;
}

//------------------------------------------------------------------------------

template<class Allocator>
template<class OtherAlloc>
void
basic_flat_buffer<Allocator>::
copy_from(
    basic_flat_buffer<OtherAlloc> const& other)
{
    std::size_t const n = other.size();
    if(n == 0 || n > capacity())
    {
        if(begin_ != nullptr)
        {
            alloc_traits::deallocate(
                this->get(), begin_,
                this->capacity());
            begin_ = nullptr;
            in_ = nullptr;
            out_ = nullptr;
            last_ = nullptr;
            end_ = nullptr;
        }
        if(n == 0)
            return;
        begin_ = alloc(n);
        in_ = begin_;
        out_ = begin_ + n;
        last_ = begin_ + n;
        end_ = begin_ + n;
    }
    in_ = begin_;
    out_ = begin_ + n;
    last_ = begin_ + n;
    if(begin_)
    {
        BOOST_ASSERT(other.begin_);
        std::memcpy(begin_, other.in_, n);
    }
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
move_assign(basic_flat_buffer& other, std::true_type)
{
    clear();
    shrink_to_fit();
    this->get() = std::move(other.get());
    begin_ = other.begin_;
    in_ = other.in_;
    out_ = other.out_;
    last_ = out_;
    end_ = other.end_;
    max_ = other.max_;
    other.begin_ = nullptr;
    other.in_ = nullptr;
    other.out_ = nullptr;
    other.last_ = nullptr;
    other.end_ = nullptr;
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
move_assign(basic_flat_buffer& other, std::false_type)
{
    if(this->get() != other.get())
    {
        copy_from(other);
    }
    else
    {
        move_assign(other, std::true_type{});
    }
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
copy_assign(basic_flat_buffer const& other, std::true_type)
{
    max_ = other.max_;
    this->get() = other.get();
    copy_from(other);
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
copy_assign(basic_flat_buffer const& other, std::false_type)
{
    clear();
    shrink_to_fit();
    max_ = other.max_;
    copy_from(other);
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
swap(basic_flat_buffer& other)
{
    swap(other, typename
        alloc_traits::propagate_on_container_swap{});
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
swap(basic_flat_buffer& other, std::true_type)
{
    using std::swap;
    swap(this->get(), other.get());
    swap(max_, other.max_);
    swap(begin_, other.begin_);
    swap(in_, other.in_);
    swap(out_, other.out_);
    last_ = this->out_;
    other.last_ = other.out_;
    swap(end_, other.end_);
}

template<class Allocator>
void
basic_flat_buffer<Allocator>::
swap(basic_flat_buffer& other, std::false_type)
{
    BOOST_ASSERT(this->get() == other.get());
    using std::swap;
    swap(max_, other.max_);
    swap(begin_, other.begin_);
    swap(in_, other.in_);
    swap(out_, other.out_);
    last_ = this->out_;
    other.last_ = other.out_;
    swap(end_, other.end_);
}

template<class Allocator>
void
swap(
    basic_flat_buffer<Allocator>& lhs,
    basic_flat_buffer<Allocator>& rhs)
{
    lhs.swap(rhs);
}

template<class Allocator>
char*
basic_flat_buffer<Allocator>::
alloc(std::size_t n)
{
    if(n > alloc_traits::max_size(this->get()))
        BOOST_THROW_EXCEPTION(std::length_error(
            "A basic_flat_buffer exceeded the allocator's maximum size"));
    return alloc_traits::allocate(this->get(), n);
}

} // beast
} // boost

#endif

/* flat_buffer.hpp
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
*/