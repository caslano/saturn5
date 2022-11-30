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
g1wCi8poAgIWRBSZSnHBNAsO8SGx9MytX9VxudXwH5yNdlUflxN1GaaZAoFwAl5X550HaQJs6jVcXNysjriGYx9QZ6SeLVjFKqdxooZPEiHIWis6jdYywRDMsazmQibLuSLYGAY0CtmygfxRWKrvMMeOGT71arCILoVapwH+bAxUC0SQiDHI7qyG+GfhiJ3mFQQ9kj/b4Tzw4q5gVorL3j7e4Kl0hDFA9qSN7T9aQTzQk140otDB4UuNLI/Q7efLkwrhY9sNjhkqa2uHXzojlPmSVKSRwem1C3cUOVf6dHr8y5WwXDNRWwsJhic7GDZKjwcWylXcsvFz6AFgy2gyvU8OdM25DnOPcnYoQNGWbUCa8cVxAzKsABGHTZCDlfyOELNDVEVJkhWe3H4JwH+QSdioN2j+ZIuTAGe6cK/dwqy1uLg48gwiClkqwN/BMIQU/NyJyg1noxgw0MDU7s1TkwvCkpcruFLKS1J0q9haHFaCEahbDwOAR1IggHeDRPch3JiFVviDsVlI886Y5Et6Lr+CgU3sjutIvqG24nK6TisIq7/oHWOci3XibXPDvO2loq95jvYCksMNkOU+11B1D/iOawiCrBNdERraIdXAD1Zs/g7Z+umK8K6NPBxb0AwGXil17cke63sxJcBOUJs0liGIANSkjgwXg+lEJGd6riX0JoD9vXLgLQH6JUiEvJlB/KnV/99hjMgVv4nTMzNwwpLv7U/PwzIDmYB2Rj9g+fgYRe1cbJ2BzIwyliZO2hx/+5V1GVU97E0ZFQ3NTZ0EBGBNbU3+YWX9b29xNDV0trSz/WbobAqk+sbDwsTEzcTNwsXMzM7FxknPxEbJxERJ/S82O0cgFVD4rwRToKKFnbOdk4WdPVBUhQ0oZ2hsafvPMTWjnJ3Jv0UxMzExszL/baxsLPRM7P8SpehoZ+JibPpX1v8UZfb3Av8W9W912f6trqylramho6Wnqcnf25QFMjOxs3OwMyoAORjFgFxMHEyM8n/7Vf/pZ+VkZpTU/nsayMzGqvtvYez/FvYfVgH+Yz/lf5lJ1NDZ0NrO/N/MHP9mFnZ0FrFz12b628PK/rfp/rW2rbOprbMTkOs/JIg62tn/Dw4JRzsXeyAz+3+clzM1sTT8HwyKho6m/4zYfzAomzrZuTga/1WJ81/Hds7/WJLp30P4b8U4/62YmLuzhMo/nH9pCRXmv///mtLZ0eUvt4DAP9Y2VjF11mb86zSMqqbuzoxSNn8lifzrRfRfL1K6jBoKRj9MjZ3/vlvKhgnI/R8KSNkw/7Xkf5IsQGaW/yRZgcys/0my/bXuP+Q/1/ov3bj+23CZ2po7WwA5uZkZxS2tnU0dGcWt/2r6zdTYzuSfu3Fy/utXNrDuaxdqvI6qwvB8vVuGxqCFX5SUxGR7AHkbKtSKVv6EPxddml4gAfTqq7VrhfELPx7e29/b6/TyfWIEa68geiOLtcv0dyHQ5/prroIritKWerHIFMfKGKXMXaxlT9ePXzvkI6ikBvqlpKEqMqd4vxakYDFQLFRVEXgouQNXTbBgj8I56iS36pZjaq74Cq4opZjpoODyg4njpGUvyeSyLeAVCspH1OjeCJ1H1chBb6GqxuS4ChSSYJTc5WkIvRtxoRhk1Q9HpAzqChqFikVw6k4uafz961kbQqDu7MOHvltzLANAJLCOY6KpQXD+2MNYm21wJ9NyI2mrkcg2Vdz1LoZ7fIv+QbM2Yz9+Ako139m2wIZ2vAqWyOiDkFT/yTsr0pc4q5HfQTcRQXKGV00W4IRkYqC2nMasemMVg1t/+utAw5ophYWiMLC1Ax6PTpYusGKvQi4MO49VPCXLop743Jo1OcMdHz6D2MO3uOmWEMOrv52kenrx0KMBZ2HUaatMvsHMd3xz9jvLtdKHpulHSfHM79x25qWJ6SnS6kCOmPbciCEM3wZNWBK9xtbGnBBOhpaXBfz3tEvvhAeQYecrtO06OTw8T3UlGOweosUlneqftu3nx7b2iz9pVhqd+bXrrX5zOalzNRudkDHFQ559WH5mRos8XBesNQF1KL3bltri8ZovLkO2WvjaRe+hOK+pKGU+hjkjaHVpeAhKMAU9lTvQuOGqxtymHfsygvlzgjIuUbydemMJ3z1fPk9u929fznh1ut87vfAqBQ61Q+vpS6vXwlzCR6nqArfbLwDfi2xaoz2Vfhf1e+cNcFlg+K5sC2+si3LsNekNiK9nmU5YC8pocgiIrlxdtO1sdCz3FB+L3mr/Jvr5s0PFjxKiGEYrnA9Ei11UePanDozp2OCBop9nJ6nYXZ3gJO6dkW7k+ZJa4WHx7v71GiEy2uIbx0AKhMzVW6ebxbf94QeKpOhYX2b/lVubxzGO9sE4Y96n90lyo0+Vs+GuqcfydV+BxenS1xdVwdzTI5WPL4HFd68KU6XrC5buT1Ch24XWv/H0nwHyn5HF/e/I+o+c8J9By6jiYuT8z/F/BDOjiKWzk6Kpo6idjb2d7T/phetvqrK2c1SxNzQ2Zfxm6mppbKosIfJfEflNVPVf8fhf0QoEsrAyMapbmvylWdkZJU0tzS2c/1L/jtevla9LAOJ/pG+AyT+lCfC1DhAFQENCQkFCQENBQcHAQMPCoyPAw8HB46CiIaET4BIREuDi4wPJGCiBJHSk+PhUnNR0TMxsbGxElNz8XCx8DH9LxFcPAAUaQAogBQOgAEBQAKAogK8BABYA5O8D8N8fYKBQf09gIv/PfgAqytcaAB4MAAABgAIAgoCrtX/+LEsy/tWSyaWUxND/1ZTZokn/i1aSnGOL/i9ajOmfaov0tfp/M/9/5ML/E/Zn5WD5/4798f4xJtj/YmkQUDBwCMh/xoAEGQAKCgLxl+G/n0QBRyVmFoYgYTF0+F/H483yCin9X2xNBuvH/zwbapRvUpLtBrTU2OfojjN0OZRKItiWLQojdauQhUFQw3UzMbzj20q195epzr28ZZT0dDwUiOZJNcQ9vidp93aYhYsjyvORJ35XYKTksXMaPbpMOWleEhSTxhaCayQz26uLetA5C1Qa0i8VlanNSUmFnRv32Hgn12X0YCTQWT4MJzXqTuvi/s5uoh8bYmzWmT5efxBQwgSA8AMg9wD/dz7A/P/IB+QMnf+Wbu2/9RPIrPv/yCMkHA09/jdF8r8FJfP/T59wX2PlIIQoNECPAl0DQHqCAJhcton/7+qz/B9yYWYu7v+NuowqcoZOVsD/MKLy/0v+jAH4n1kD8I8noyP/z17A/+q73bVnz/+TAwD2v3MR1v9TaZqN9f90mvi/AGnFKhfwagCAQ0vsXQk4VPvfnzH2NYxI/WtsManMvmRrzKIh+05ZRkSNRhKVK0JSEVmjkGUsZYtISaQotFhCWSISZU2FrO9Rt3u75fbe//O+933u/3k7c35zzvM7v+c3c77fcz7n8/18nmfmz8MqtRRWyDcwzbkUWckV3wG4qJjDN0Dd0n25wjiaDdcB3hwypB3SaGHSGJfGpY32zqUXtvnbVYdt/Hk8XKebda0SBFq3XDIw/1eYjcb/c5KxZimuAGh/j9m8wFHYJ9Dm/PowmEMUwrmE2WJG4n/MzJR4k37JpzEcpjaDhYG+Kw2jBq9enNm0kZlcQ3c3zkrTk3DNM4T56yisujIalqP8XFExtaZIq71ry+YWOeWaSGZ70lmasFkV9uVIgonX8IvCClccibwCvDK000wOp5Yc3VOMKEqzBeCxbdu2bdu2bc8e27Zt22ds27atO/9N+kv6tSvprKqnIp9o9dhd5imO92yLY2670ipSnlp6FrY/qjMPZpPBcds6LC3TJHsWiL5rmOLL8rF42kH+LLk9aNOp7KO6PsujIkDdnsVGRlWGD/MF30qrpB0dyqsLkm9ZvxWFfqhSssdEKR26e6PvAIOSQ95D/Pa20s1lvrr2/qdmDn8Qzn66o6ep6nllpw8QlLUZ6l2zGnG+DdQE78AN5nPbxLCn8vtm/Dl9TJzN6a0tYGAXn0yTt/xa9qAKawqk0sVAgkgBrplbP1tC4pvHDP1iDSnWoCiMhEjBgikAXI2GJNy/D6GRjIYXJBQfT0ElBB0w/6/CsEKDBlN+hHCeBClCbIEo3pECJEGgH8GRBAUsaHENcookjGyyYE6Ck+WZflqyGCHChChQZtAwAYMHSFwIWNjBBAaySvS/g3mQGP1hcGljcnNU6D3NcC0vND9KyL7I3TJoBJLGYOgog3i0+l80AGTY/GtQOhm5fF2QgA4zAYPcIQKGPHqIqTowIGgAX6EsAQNEAA+RKb5teYMEvjn3Ap698719z7Gh8Qz8oP79d1SUcrBm0x8IrNYlj7S7qES/SrA1Bti2LCV0dPSKjZM8db4B190rgMvBQSDd1c6amu0ZQ/y53zNH5jlLAxNzq97L40n1DRdpyfOY0JGXj9DWx8dHXt4e5qamv45VGZ8fC2PdPz1zo7bN+Op6s6CgoKODM1MDAO5NB1De2Bc5PrzHkpN9cYkYzclrMaPkhjfvJ3CjtUpOmwYBsCS++m2E1kT/uZ2+0ulOhGORNPKg6lWOj4K85fhC3u3Clu2ueZjfs3BFz9b/4UdRqrPxLZ/VKIjmouUiuOZxBBsN7DvsPqBwlIVzDgcIZyIfbr8Gv5zXcYtTCigp5Vcr+YjJIUVK6dc6c9EcEfQb+A85EOrLLCjVVWMnNB6wMBGCPiR9+21ICr2xn6ra3CQV9SQEVfutCDTNRR8ybbaMKi8XDOhyvzH6cErptxnDXc53vu9IassitFfSKFGFa8LMojohewcUSOyNdKslP99NstebWpu/saObRHqkOWtnySqwEe3mg4hAOekHHY73Buu90ppnwFTgMzDWi/Frj8qBkeyC8Zk6fliCUi1RfAYmPRt73GqrV+cqA0jPVqHvtIyCmvIDOfMje7oYty3CWC+LRtc78BWuCVi0YuzTmRduFyO3g/DSWLbRE5hUVvxdhTL9Fwa6yCnQzEczn1bx0YnatLDu57Tz4VEtp+RstrnXCcen3TRP4Ka9ewkvZTjHAhLEJ8X9wFdyMNOVnw/CuNFB/oN3AGTRtDwS/we0KoqI6pAimaB35w2MdM+411mlnZE/ToufGwciZ/9JC+dq4dI8Mn2th0fmwNH0rrPQhpFS9vTKlhGzvZWHV5KUcfb0cM3Jx0NJLZ7koxWomBPXEefZOPWqMDWCt/OkPD4OCc+dQ+IiXZZr5UHzfXfHqR2g9FRct+UUm/55Mf3QzEMwr7BivXyjTTUiDeLcuffIk8iQYGHYCX3fES3MzaSinnEFk3fXMgfhLqmresFt8k6tDUZf4w9KWqfv/abQvEbo0FNzXfveTjzUNqN3WIRTQsG32U70wc+T3JjV8E5Z89Snlkg7Vy/UB9yrF618LoenqbeiqGiUWITZ6NrYmom+9prZtCj7ykVRNVwfcyA0z67gzC7NDKIfQft3DQr4Hke7Picc3mPIIYD7Jr6EHLxFCFyM3KdI40D/pX/ECUDSv/e3NxBQkJLg4GIFJmsThd+Xhwzqa6Bzgf5GAEUgYZGByVXgbn8leICePVNv0bQ6XAAoUihEUAkVJ9KzXX2P1H2O//ApX8dKQONEihAlvuydPuOSvWmmBlHTVz/72zp56/MVJGDQ4kR/Rbd/JkX0Gan+a8MBe88YIvA/ZfhvlwMGSLZfgdKCBCyCrLAcAwewJGQAqIuCCimsIF4RYHeu8ADRgwlSuDT+joIKUHpwD8GEKTW0DCneggr0V7g3YIBmlJ0DsLfgJYP7n4bALjQCBpADlARRP7sQgFvoD2KegBFk30PEr4g4WNR3Fw4mEdz3cIIgomMfN5MHzn0Z8eNiwvv52JeLiR8XEz9uxi+NeOgdfOSv1Ry58Am3a1zYZ1Q7OKAv7Y8v0ms8EwkdY1iT/9SIx7w1oiACRYlhPDJYItvoUbsW4odGjJ6VUfUhonuXsuaBJ7VrjevSSpw+Leu1bbEO5TdBAbGLyErgIPE704c+RVGR13Xd87JKDaIaZVyKPXtLdqUutSa9WTM9TeUyxd2ebpqGhdVqZke3uXvu8BLa8LA7R82qKtXa+HI98uLnma3s1ucAexF7CR1Hprv2sfOq+mPYuoxW6lNcc1V2ubdl7k/xNevi57KsV6vU40gtdI5s01mLC3Z6ASVEoUey/Fx20IBBNcTv+fzXk4WfF4s/bfXvLS8WzUne0TxNx4n/nQWBARzAsGdfP4fDE7exLti4KNMH2kjYTXR2ByQQ5YPq4JcgzojsiKw9MC6uzFe5L5vfkkhqP6yl9niQ1SFbWUt2+2QLXTt4NnOM53WhonzO1mTopOhroo3I0t2nN/Oq465FI+SMXXhrB29CDQsV65V3ANf8h0TRtWXmyDhYrSDqdWuP4Kc6fubkkvPiiDzPfxtwoFXdfBrYq9fpbIS9yAAXZa+742lx1V7PP3BNHLme/7lozytf60qq5skLPOJbb/Asaq00G0Id9Sx6eNICmqi85ycySH9NNyMG3Zf8wstiU8FJEhcgWmAlRA8ZRGgAgUoKEDdbsBDhyY4QzmExsGIBzEnwhIoV7jFIEAlFRQoiU1KAAEr2EyWw0OxzL57QT0mCukFqQcDASQKEGlCSwEBGiFkbMlpggYYJJ/6SLZLhgJysggeAQgkaEMoiaIigWoTxQdNTt/tbbBAglvOz2t7Qs+rZ7fGuMtFDrt112DdxAQBBhtOzMlDsBy6l6Z/zgOBJHlHLsnBzPGvEBcmLiZGxEJBtu6CmzYv6+wv67SyZpLvShT2rOpf/dwN9vf9FeCJWRtiQwezzFW1kWKICR0tucYKGEEYjwwaEiNrgarRz+8U9nV3YsK4NfDENP3k4kehOjr5Lbdf0PK5alw473UDXG+wyQUBQGccY3EYNTX5P/qIm5OlFJXwLXpd1uW/ZXEGfh0trvZhRaPNqw9jkMMlRiDQ/vNZinfZ2DZ/9hpqzqYY2zEAPLXjIcVI0KHZZAN00kzOOtEojrtqhkegcMdQToXddp51zmq/ZMhqpXUNflE13u2tQKM76elahPHO7paaqx9OtVJa8vXi1m23Zf8Ef59y0ksMp4KrYfrSMsO6YWniYzzJn/vDg9FMTPGBXsk/b9up0MprMDU/itQsFE8Be9WgisOibWI+BoixYmmV3DHvtUg6p68r379NNp8UHzuu1CNfk9AWnqnDFomhQdfo8/eS7vsy9iI0yega1x9PRKIfWQ8V7dQOjihrGqsBu6yTnA7HnUgR5K7aOT7bNBPnu+RFolk54O24RKVSF9J4RZ3BzfzM4nM5cbeoCqdu486xcXL3J3vxd/ULG/Ga6EVVdriPNPRqsS8K2xK61q0SsOIuDMiEIWjujYXUlKMqNn46RrgND1jFCuYHakO/Qf4W+8Kd3AHjnqHuggUJs/UDtP/oRJcwZtBbo/aH99Eq5D5enyrDRPZ0qPDFB5RgMHh8nLvWF/J77bkwknCXn/opjmmPGIDcivXj9K7QZygOjcfEQBL7U+htK1AKD/WvBkgDuIhF5fXq8JW/CaR3vVgXbWiSixnnzLzZ5nG1UcF5UCU/3asEbjnEqeqFtuhq+XRCbQk8kojb4e+n3kdKKstj9J27XCc8SGOzeVHcomeWNedvl0K/m+EtwMDzNWzmet/+e
*/