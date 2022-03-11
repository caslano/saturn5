//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_MULTI_BUFFER_HPP
#define BOOST_BEAST_IMPL_MULTI_BUFFER_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/config/workaround.hpp>
#include <boost/core/exchange.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <exception>
#include <iterator>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

/*  These diagrams illustrate the layout and state variables.

1   Input and output contained entirely in one element:

    0                           out_
    |<------+-----------+--------------------------------+----->|
          in_pos_    out_pos_                         out_end_


2   Output contained in first and second elements:

                 out_
    |<------+-----------+------>|   |<-------------------+----->|
          in_pos_    out_pos_                         out_end_


3   Output contained in the second element:

                                                  out_
    |<------+------------------>|   |<----+--------------+----->|
          in_pos_                      out_pos_       out_end_


4   Output contained in second and third elements:

                                 out_
    |<------+------->|   |<-------+------>|   |<---------+----->|
          in_pos_               out_pos_              out_end_


5   Input sequence is empty:

                 out_
    |<------+------------------>|   |<-------------------+----->|
         out_pos_                                     out_end_
          in_pos_

6   Output sequence is empty:

                                                    out_
    |<------+------------------>|   |<------+------------------>|
          in_pos_                        out_pos_
                                         out_end_


7   The end of output can point to the end of an element.
    But out_pos_ should never point to the end:

                                                    out_
    |<------+------------------>|   |<------+------------------>|
          in_pos_                        out_pos_            out_end_


8   When the input sequence entirely fills the last element and
    the output sequence is empty, out_ will point to the end of
    the list of buffers, and out_pos_ and out_end_ will be 0:


    |<------+------------------>|   out_     == list_.end()
          in_pos_                   out_pos_ == 0
                                    out_end_ == 0
*/

//------------------------------------------------------------------------------

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# pragma warning (push)
# pragma warning (disable: 4521) // multiple copy constructors specified
# pragma warning (disable: 4522) // multiple assignment operators specified
#endif

template<class Allocator>
template<bool isMutable>
class basic_multi_buffer<Allocator>::subrange
{
    basic_multi_buffer const* b_;
    const_iter begin_;
    const_iter end_;
    size_type begin_pos_;   // offset in begin_
    size_type last_pos_;    // offset in std::prev(end_)

    friend class basic_multi_buffer;

    subrange(
        basic_multi_buffer const& b,
        size_type pos,
        size_type n) noexcept
        : b_(&b)
    {
        auto const set_empty = [&]
        {
            begin_ = b_->list_.end();
            end_ = b_->list_.end();
            begin_pos_ = 0;
            last_pos_ = 0;
        };

        // VFALCO Handle this trivial case of
        // pos larger than total size, otherwise
        // the addition to pos can overflow.
        //if(pos >= b_->in_size_)
        // skip unused prefix
        pos = pos + b_->in_pos_;

        // iterate the buffers
        auto it = b_->list_.begin();

        // is the list empty?
        if(it == b_->list_.end())
        {
            set_empty();
            return;
        }
        
        // is the requested size zero?
        if(n == 0)
        {
            set_empty();
            return;
        }


        // get last buffer and its size
        auto const last =
            std::prev(b_->list_.end());
        auto const last_end =
            [&]
            {
                if(b_->out_end_ == 0)
                    return last->size();
                return b_->out_end_;
            }();

        // only one buffer in list?
        if(it == last)
        {
            if(pos >= last_end)
            {
                set_empty();
                return;
            }

            begin_ = it;
            begin_pos_ = pos;
            end_ = std::next(it);
            if(n > last_end - pos)
                last_pos_ = last_end;
            else
                last_pos_ = pos + n;
            return;
        }

        for(;;)
        {
            // is pos in this buffer?
            if(pos < it->size())
            {
                begin_ = it;
                begin_pos_ = pos;

                // does this buffer satisfy n?
                auto const avail =
                    it->size() - pos;
                if(n <= avail)
                {
                    end_ = ++it;
                    last_pos_ = pos + n;
                    return;
                }

                n -= avail;
                ++it;
                break;
            }

            pos -= it->size();
            ++it;

            // did we reach the last buffer?
            if(it == last)
            {
                // is pos past the end?
                if(pos >= last_end)
                {
                    set_empty();
                    return;
                }

                // satisfy the request
                begin_ = it;
                begin_pos_ = pos;
                end_ = std::next(it);
                if(n < last_end - pos)
                    last_pos_ = pos + n;
                else
                    last_pos_ = last_end;
                return;
            }
        }

        // find pos+n
        for(;;)
        {
            if(it == last)
            {
                end_ = ++it;
                if(n >= last_end)
                    last_pos_ = last_end;
                else
                    last_pos_ = n;
                return;
            }
            if(n <= it->size())
            {
                end_ = ++it;
                last_pos_ = n;
                return;
            }
            
            n -= it->size();
            ++it;
        }
    }

public:
    using value_type = typename
        std::conditional<
            isMutable,
            net::mutable_buffer,
            net::const_buffer>::type;

    class const_iterator;

    subrange() = delete;
#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
    subrange(subrange const& other)
        : b_(other.b_)
        , begin_(other.begin_)
        , end_(other.end_)
        , begin_pos_(other.begin_pos_)
        , last_pos_(other.last_pos_)
    {
    }

    subrange& operator=(subrange const& other)
    {
        b_ = other.b_;
        begin_ = other.begin_;
        end_ = other.end_;
        begin_pos_ = other.begin_pos_;
        last_pos_ = other.last_pos_;
        return *this;
    }
#else
    subrange(subrange const&) = default;
    subrange& operator=(subrange const&) = default;
#endif

    template<
        bool isMutable_ = isMutable,
        class = typename std::enable_if<! isMutable_>::type>
    subrange(
        subrange<true> const& other) noexcept
        : b_(other.b_)
        , begin_(other.begin_)
        , end_(other.end_)
        , begin_pos_(other.begin_pos_)
        , last_pos_(other.last_pos_)
   {
    }

    template<
        bool isMutable_ = isMutable,
        class = typename std::enable_if<! isMutable_>::type>
    subrange& operator=(
        subrange<true> const& other) noexcept
    {
        b_ = other.b_;
        begin_ = other.begin_;
        end_ = other.end_;
        begin_pos_ = other.begin_pos_;
        last_pos_ = other.last_pos_;
        return *this;
    }

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    std::size_t
    buffer_bytes() const noexcept
    {
        return b_->size();
    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# pragma warning (pop)
#endif

//------------------------------------------------------------------------------

template<class Allocator>
template<bool isMutable>
class
    basic_multi_buffer<Allocator>::
    subrange<isMutable>::
    const_iterator
{
    friend class subrange;

    subrange const* sr_ = nullptr;
    typename list_type::const_iterator it_;

    const_iterator(
        subrange const& sr, typename
        list_type::const_iterator const& it) noexcept
        : sr_(&sr)
        , it_(it)
    {
    }

public:
    using value_type =
        typename subrange::value_type;
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
    operator==(
        const_iterator const& other) const noexcept
    {
        return sr_ == other.sr_ && it_ == other.it_;
    }

    bool
    operator!=(
        const_iterator const& other) const noexcept
    {
        return !(*this == other);
    }

    reference
    operator*() const noexcept
    {
        value_type result;
        BOOST_ASSERT(sr_->last_pos_ != 0);
        if(it_ == std::prev(sr_->end_))
            result = {
                it_->data(), sr_->last_pos_ };
        else
            result = {
                it_->data(), it_->size() };
        if(it_ == sr_->begin_)
            result += sr_->begin_pos_;
        return result;
    }

    pointer
    operator->() const = delete;

    const_iterator&
    operator++() noexcept
    {
        ++it_;
        return *this;
    }

    const_iterator
    operator++(int) noexcept
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    const_iterator&
    operator--() noexcept
    {
        --it_;
        return *this;
    }

    const_iterator
    operator--(int) noexcept
    {
        auto temp = *this;
        --(*this);
        return temp;
    }
};

//------------------------------------------------------------------------------

template<class Allocator>
template<bool isMutable>
auto
basic_multi_buffer<Allocator>::
subrange<isMutable>::
begin() const noexcept ->
    const_iterator
{
    return const_iterator(
        *this, begin_);
}

template<class Allocator>
template<bool isMutable>
auto
basic_multi_buffer<Allocator>::
subrange<isMutable>::
end() const noexcept ->
    const_iterator
{
    return const_iterator(
        *this, end_);
}

//------------------------------------------------------------------------------

template<class Allocator>
basic_multi_buffer<Allocator>::
~basic_multi_buffer()
{
    destroy(list_);
}

template<class Allocator>
basic_multi_buffer<Allocator>::
basic_multi_buffer() noexcept(default_nothrow)
    : max_(alloc_traits::max_size(this->get()))
    , out_(list_.end())
{
}

template<class Allocator>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
    std::size_t limit) noexcept(default_nothrow)
    : max_(limit)
    , out_(list_.end())
{
}

template<class Allocator>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
    Allocator const& alloc) noexcept
    : boost::empty_value<Allocator>(
        boost::empty_init_t(), alloc)
    , max_(alloc_traits::max_size(this->get()))
    , out_(list_.end())
{
}

template<class Allocator>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
    std::size_t limit,
    Allocator const& alloc) noexcept
    : boost::empty_value<Allocator>(
        boost::empty_init_t(), alloc)
    , max_(limit)
    , out_(list_.end())
{
}

template<class Allocator>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
    basic_multi_buffer&& other) noexcept
    : boost::empty_value<Allocator>(
        boost::empty_init_t(), std::move(other.get()))
    , max_(other.max_)
    , in_size_(boost::exchange(other.in_size_, 0))
    , in_pos_(boost::exchange(other.in_pos_, 0))
    , out_pos_(boost::exchange(other.out_pos_, 0))
    , out_end_(boost::exchange(other.out_end_, 0))
{
    auto const at_end =
        other.out_ == other.list_.end();
    list_ = std::move(other.list_);
    out_ = at_end ? list_.end() : other.out_;
    other.out_ = other.list_.end();
}

template<class Allocator>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
    basic_multi_buffer&& other,
    Allocator const& alloc)
    : boost::empty_value<Allocator>(
        boost::empty_init_t(), alloc)
    , max_(other.max_)
{
    if(this->get() != other.get())
    {
        out_ = list_.end();
        copy_from(other);
        return;
    }

    auto const at_end =
        other.out_ == other.list_.end();
    list_ = std::move(other.list_);
    out_ = at_end ? list_.end() : other.out_;
    in_size_ = other.in_size_;
    in_pos_ = other.in_pos_;
    out_pos_ = other.out_pos_;
    out_end_ = other.out_end_;
    other.in_size_ = 0;
    other.out_ = other.list_.end();
    other.in_pos_ = 0;
    other.out_pos_ = 0;
    other.out_end_ = 0;
}

template<class Allocator>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
    basic_multi_buffer const& other)
    : boost::empty_value<Allocator>(
        boost::empty_init_t(), alloc_traits::
            select_on_container_copy_construction(
                other.get()))
    , max_(other.max_)
    , out_(list_.end())
{
    copy_from(other);
}

template<class Allocator>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
    basic_multi_buffer const& other,
    Allocator const& alloc)
    : boost::empty_value<Allocator>(
        boost::empty_init_t(), alloc)
    , max_(other.max_)
    , out_(list_.end())
{
    copy_from(other);
}

template<class Allocator>
template<class OtherAlloc>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
        basic_multi_buffer<OtherAlloc> const& other)
    : out_(list_.end())
{
    copy_from(other);
}

template<class Allocator>
template<class OtherAlloc>
basic_multi_buffer<Allocator>::
basic_multi_buffer(
    basic_multi_buffer<OtherAlloc> const& other,
        allocator_type const& alloc)
    : boost::empty_value<Allocator>(
        boost::empty_init_t(), alloc)
    , max_(other.max_)
    , out_(list_.end())
{
    copy_from(other);
}

template<class Allocator>
auto
basic_multi_buffer<Allocator>::
operator=(basic_multi_buffer&& other) ->
    basic_multi_buffer&
{
    if(this == &other)
        return *this;
    clear();
    max_ = other.max_;
    move_assign(other, pocma{});
    return *this;
}

template<class Allocator>
auto
basic_multi_buffer<Allocator>::
operator=(basic_multi_buffer const& other) ->
basic_multi_buffer&
{
    if(this == &other)
        return *this;
    copy_assign(other, pocca{});
    return *this;
}

template<class Allocator>
template<class OtherAlloc>
auto
basic_multi_buffer<Allocator>::
operator=(
    basic_multi_buffer<OtherAlloc> const& other) ->
        basic_multi_buffer&
{
    copy_from(other);
    return *this;
}

//------------------------------------------------------------------------------

template<class Allocator>
std::size_t
basic_multi_buffer<Allocator>::
capacity() const noexcept
{
    auto pos = out_;
    if(pos == list_.end())
        return in_size_;
    auto n = pos->size() - out_pos_;
    while(++pos != list_.end())
        n += pos->size();
    return in_size_ + n;
}

template<class Allocator>
auto
basic_multi_buffer<Allocator>::
data() const noexcept ->
    const_buffers_type
{
    return const_buffers_type(
        *this, 0, in_size_);
}

template<class Allocator>
auto
basic_multi_buffer<Allocator>::
data() noexcept ->
    mutable_buffers_type
{
    return mutable_buffers_type(
        *this, 0, in_size_);
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
reserve(std::size_t n)
{
    // VFALCO The amount needs to be adjusted for
    //        the sizeof(element) plus padding
    if(n > alloc_traits::max_size(this->get()))
        BOOST_THROW_EXCEPTION(std::length_error(
        "A basic_multi_buffer exceeded the allocator's maximum size"));
    std::size_t total = in_size_;
    if(n <= total)
        return;
    if(out_ != list_.end())
    {
        total += out_->size() - out_pos_;
        if(n <= total)
            return;
        for(auto it = out_;;)
        {
            if(++it == list_.end())
                break;
            total += it->size();
            if(n <= total)
                return;
        }
    }
    BOOST_ASSERT(n > total);
    (void)prepare(n - size());
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
shrink_to_fit()
{
    // empty list
    if(list_.empty())
        return;

    // zero readable bytes
    if(in_size_ == 0)
    {
        destroy(list_);
        list_.clear();
        out_ = list_.end();
        in_size_ = 0;
        in_pos_ = 0;
        out_pos_ = 0;
        out_end_ = 0;
    #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
        debug_check();
    #endif
        return;
    }

    // one or more unused output buffers
    if(out_ != list_.end())
    {
        if(out_ != list_.iterator_to(list_.back()))
        {
            // unused list
            list_type extra;
            extra.splice(
                extra.end(),
                list_,
                std::next(out_),
                list_.end());
            destroy(extra);
        #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
            debug_check();
        #endif
        }

        // unused out_
        BOOST_ASSERT(out_ ==
            list_.iterator_to(list_.back()));
        if(out_pos_ == 0)
        {
            BOOST_ASSERT(out_ != list_.begin());
            auto& e = *out_;
            list_.erase(out_);
            out_ = list_.end();
            destroy(e);
            out_end_ = 0;
        #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
            debug_check();
        #endif
        }
    }

    auto const replace =
        [&](iter pos, element& e)
        {
            auto it =
                list_.insert(pos, e);
            auto& e0 = *pos;
            list_.erase(pos);
            destroy(e0);
            return it;
        };

    // partial last buffer
    if(list_.size() > 1 && out_ != list_.end())
    {
        BOOST_ASSERT(out_ ==
            list_.iterator_to(list_.back()));
        BOOST_ASSERT(out_pos_ != 0);
        auto& e = alloc(out_pos_);
        std::memcpy(
            e.data(),
            out_->data(),
            out_pos_);
        replace(out_, e);
        out_ = list_.end();
        out_pos_ = 0;
        out_end_ = 0;
    #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
        debug_check();
    #endif
    }

    // partial first buffer
    if(in_pos_ != 0)
    {
        if(out_ != list_.begin())
        {
            auto const n =
                list_.front().size() - in_pos_;
            auto& e = alloc(n);
            std::memcpy(
                e.data(),
                list_.front().data() + in_pos_,
                n);
            replace(list_.begin(), e);
            in_pos_ = 0;
        }
        else
        {
            BOOST_ASSERT(list_.size() == 1);
            BOOST_ASSERT(out_pos_ > in_pos_);
            auto const n = out_pos_ - in_pos_;
            auto& e = alloc(n);
            std::memcpy(
                e.data(),
                list_.front().data() + in_pos_,
                n);
            replace(list_.begin(), e);
            in_pos_ = 0;
            out_ = list_.end();
        }
    #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
        debug_check();
    #endif
    }
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
clear() noexcept
{
    out_ = list_.begin();
    in_size_ = 0;
    in_pos_ = 0;
    out_pos_ = 0;
    out_end_ = 0;
}

template<class Allocator>
auto
basic_multi_buffer<Allocator>::
prepare(size_type n) ->
    mutable_buffers_type
{
    auto const n0 = n;
    if(in_size_ > max_ || n > (max_ - in_size_))
        BOOST_THROW_EXCEPTION(std::length_error{
            "basic_multi_buffer too long"});
    list_type reuse;
    std::size_t total = in_size_;
    // put all empty buffers on reuse list
    if(out_ != list_.end())
    {
        total += out_->size() - out_pos_;
        if(out_ != list_.iterator_to(list_.back()))
        {
            out_end_ = out_->size();
            reuse.splice(reuse.end(), list_,
                std::next(out_), list_.end());
        #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
            debug_check();
        #endif
        }
        auto const avail = out_->size() - out_pos_;
        if(n > avail)
        {
            out_end_ = out_->size();
            n -= avail;
        }
        else
        {
            out_end_ = out_pos_ + n;
            n = 0;
        }
    #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
        debug_check();
    #endif
    }
    // get space from reuse buffers
    while(n > 0 && ! reuse.empty())
    {
        auto& e = reuse.front();
        reuse.erase(reuse.iterator_to(e));
        list_.push_back(e);
        total += e.size();
        if(n > e.size())
        {
            out_end_ = e.size();
            n -= e.size();
        }
        else
        {
            out_end_ = n;
            n = 0;
        }
    #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
        debug_check();
    #endif
    }
    BOOST_ASSERT(total <= max_);
    if(! reuse.empty() || n > 0)
    {
        destroy(reuse);
        if(n > 0)
        {
            auto const growth_factor = 2.0f;
            auto const size =
                (std::min<std::size_t>)(
                    max_ - total,
                    (std::max<std::size_t>)({
                        static_cast<std::size_t>(
                            in_size_ * growth_factor - in_size_),
                        512,
                        n}));
            auto& e = alloc(size);
            list_.push_back(e);
            if(out_ == list_.end())
                out_ = list_.iterator_to(e);
            out_end_ = n;
        #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
            debug_check();
        #endif
        }
    }
    auto const result =
        mutable_buffers_type(
            *this, in_size_, n0);
    BOOST_ASSERT(
        net::buffer_size(result) == n0);
    return result;
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
commit(size_type n) noexcept
{
    if(list_.empty())
        return;
    if(out_ == list_.end())
        return;
    auto const back =
        list_.iterator_to(list_.back());
    while(out_ != back)
    {
        auto const avail =
            out_->size() - out_pos_;
        if(n < avail)
        {
            out_pos_ += n;
            in_size_ += n;
        #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
            debug_check();
        #endif
            return;
        }
        ++out_;
        n -= avail;
        out_pos_ = 0;
        in_size_ += avail;
    #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
        debug_check();
    #endif
    }

    n = (std::min)(n, out_end_ - out_pos_);
    out_pos_ += n;
    in_size_ += n;
    if(out_pos_ == out_->size())
    {
        ++out_;
        out_pos_ = 0;
        out_end_ = 0;
    }
#if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
    debug_check();
#endif
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
consume(size_type n) noexcept
{
    if(list_.empty())
        return;
    for(;;)
    {
        if(list_.begin() != out_)
        {
            auto const avail =
                list_.front().size() - in_pos_;
            if(n < avail)
            {
                in_size_ -= n;
                in_pos_ += n;
            #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
                debug_check();
            #endif
                break;
            }
            n -= avail;
            in_size_ -= avail;
            in_pos_ = 0;
            auto& e = list_.front();
            list_.erase(list_.iterator_to(e));
            destroy(e);
        #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
            debug_check();
        #endif
        }
        else
        {
            auto const avail = out_pos_ - in_pos_;
            if(n < avail)
            {
                in_size_ -= n;
                in_pos_ += n;
            }
            else
            {
                in_size_ = 0;
                if(out_ != list_.iterator_to(list_.back()) ||
                    out_pos_ != out_end_)
                {
                    in_pos_ = out_pos_;
                }
                else
                {
                    // Input and output sequences are empty, reuse buffer.
                    // Alternatively we could deallocate it.
                    in_pos_ = 0;
                    out_pos_ = 0;
                    out_end_ = 0;
                }
            }
        #if BOOST_BEAST_MULTI_BUFFER_DEBUG_CHECK
            debug_check();
        #endif
            break;
        }
    }
}

template<class Allocator>
template<class OtherAlloc>
void
basic_multi_buffer<Allocator>::
copy_from(basic_multi_buffer<OtherAlloc> const& other)
{
    clear();
    max_ = other.max_;
    if(other.size() == 0)
        return;
    commit(net::buffer_copy(
        prepare(other.size()), other.data()));
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
move_assign(basic_multi_buffer& other, std::true_type) noexcept
{
    this->get() = std::move(other.get());
    auto const at_end =
        other.out_ == other.list_.end();
    list_ = std::move(other.list_);
    out_ = at_end ? list_.end() : other.out_;

    in_size_ = other.in_size_;
    in_pos_ = other.in_pos_;
    out_pos_ = other.out_pos_;
    out_end_ = other.out_end_;
    max_ = other.max_;

    other.in_size_ = 0;
    other.out_ = other.list_.end();
    other.in_pos_ = 0;
    other.out_pos_ = 0;
    other.out_end_ = 0;
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
move_assign(basic_multi_buffer& other, std::false_type)
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
basic_multi_buffer<Allocator>::
copy_assign(
    basic_multi_buffer const& other, std::false_type)
{
    copy_from(other);
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
copy_assign(
    basic_multi_buffer const& other, std::true_type)
{
    clear();
    this->get() = other.get();
    copy_from(other);
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
swap(basic_multi_buffer& other) noexcept
{
    swap(other, typename
        alloc_traits::propagate_on_container_swap{});
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
swap(basic_multi_buffer& other, std::true_type) noexcept
{
    using std::swap;
    auto const at_end0 =
        out_ == list_.end();
    auto const at_end1 =
        other.out_ == other.list_.end();
    swap(this->get(), other.get());
    swap(list_, other.list_);
    swap(out_, other.out_);
    if(at_end1)
        out_ = list_.end();
    if(at_end0)
        other.out_ = other.list_.end();
    swap(in_size_, other.in_size_);
    swap(in_pos_, other.in_pos_);
    swap(out_pos_, other.out_pos_);
    swap(out_end_, other.out_end_);
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
swap(basic_multi_buffer& other, std::false_type) noexcept
{
    BOOST_ASSERT(this->get() == other.get());
    using std::swap;
    auto const at_end0 =
        out_ == list_.end();
    auto const at_end1 =
        other.out_ == other.list_.end();
    swap(list_, other.list_);
    swap(out_, other.out_);
    if(at_end1)
        out_ = list_.end();
    if(at_end0)
        other.out_ = other.list_.end();
    swap(in_size_, other.in_size_);
    swap(in_pos_, other.in_pos_);
    swap(out_pos_, other.out_pos_);
    swap(out_end_, other.out_end_);
}

template<class Allocator>
void
swap(
    basic_multi_buffer<Allocator>& lhs,
    basic_multi_buffer<Allocator>& rhs) noexcept
{
    lhs.swap(rhs);
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
destroy(list_type& list) noexcept
{
    for(auto it = list.begin();
            it != list.end();)
        destroy(*it++);
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
destroy(const_iter it)
{
    auto& e = list_.erase(it);
    destroy(e);
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
destroy(element& e)
{
    auto a = rebind_type{this->get()};
    auto const n =
        (sizeof(element) + e.size() +
            sizeof(align_type) - 1) /
        sizeof(align_type);
    e.~element();
    alloc_traits::deallocate(a,
        reinterpret_cast<align_type*>(&e), n);
}

template<class Allocator>
auto
basic_multi_buffer<Allocator>::
alloc(std::size_t size) ->
    element&
{
    if(size > alloc_traits::max_size(this->get()))
        BOOST_THROW_EXCEPTION(std::length_error(
        "A basic_multi_buffer exceeded the allocator's maximum size"));
    auto a = rebind_type{this->get()};
    auto const p = alloc_traits::allocate(a,
        (sizeof(element) + size + sizeof(align_type) - 1) /
            sizeof(align_type));
    return *(::new(p) element(size));
}

template<class Allocator>
void
basic_multi_buffer<Allocator>::
debug_check() const
{
#ifndef NDEBUG
    BOOST_ASSERT(buffer_bytes(data()) == in_size_);
    if(list_.empty())
    {
        BOOST_ASSERT(in_pos_ == 0);
        BOOST_ASSERT(in_size_ == 0);
        BOOST_ASSERT(out_pos_ == 0);
        BOOST_ASSERT(out_end_ == 0);
        BOOST_ASSERT(out_ == list_.end());
        return;
    }

    auto const& front = list_.front();

    BOOST_ASSERT(in_pos_ < front.size());

    if(out_ == list_.end())
    {
        BOOST_ASSERT(out_pos_ == 0);
        BOOST_ASSERT(out_end_ == 0);
    }
    else
    {
        auto const& out = *out_;
        auto const& back = list_.back();

        BOOST_ASSERT(out_end_ <= back.size());
        BOOST_ASSERT(out_pos_ <  out.size());
        BOOST_ASSERT(&out != &front || out_pos_ >= in_pos_);
        BOOST_ASSERT(&out != &front || out_pos_ - in_pos_ == in_size_);
        BOOST_ASSERT(&out != &back  || out_pos_ <= out_end_);
    }
#endif
}

} // beast
} // boost

#endif

/* multi_buffer.hpp
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
*/