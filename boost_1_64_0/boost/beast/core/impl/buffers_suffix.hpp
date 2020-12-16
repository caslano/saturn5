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
Pr/SQl8c4fkTSH8Anz+Rz59kofdHoD+I9JNJfzDpD7HQN0bgfwbpq8l/Dfn3W7/TLtO/PwNJP4jPH0y6IoRm0hWSLhE4mnRbsd8dBswA5gPzgVvzPRgBLABuA9yRcdUfX6YbjwLJT3+OR7cAXhjwr9muX83FC50+NZUfTbsPzXb8Z44Y2jGfmWt2QQCOxqTbZIS4rcL9ZM4DLkKgX0ytT0ynP8y178cZx6JMqz/MdQhNuCf+MPP1PjCvz3f3e7kYtGX0e7kO8ecQT9k6sr/L4tvg1xRIf5dWP5f0cal8W9KvJdJP6Abflu37taQ/S/qydPiv/JO+K8N9VdJPJXjqQx+VVv+UaxEcPimVP8op9EPZhNB6X6KxFiHv/kRjLEI9whUIyxDWImQ/kGgUIlQgNCEsRliBEPdgopGPUIwwD6EFYQWC8RDKQhiNUIVwIcIShLcR1plpD6O9IlQhzENoQXgOYTVCj6Xwf4lQjDAXYRHCMoSVCHGPgBahCGE2whUISxFWIiQ9mmgMQZiCMA+hBaEVYR1C3mOQC6EKoQlhMcIKhKTHE40RCFMQjkWY/3jMj2bsil2xK3bFrn/H9Rf5/8Paf+f9/+GcfznvvPlVOf+/FvfrzQP4kEl8A77bz1A2CYtpcGquOQ4CNgB3MH3VnKHW2UfNwRahiTX78KxC7q9V+4dHyTp+3zPN/CO9XHsn/UTlB6GHpPd2XavfR+UfJ/FJiKdI/j28oT2bdSVV9fI8scnsJem7eIN2n2slniX0Raq8UtqFIuUs7utmefQHJOXlm2tbwedxz3S8xI8W+v1VeWPU2fbbni1niyNutdGsspyJShqeiZqGe8wrtoIN1fVSVhXu3yrPqvKo8/4dtNmkzU2wnxl5oLneK/kO9wZpCxy0uTZa+ljjGfnrJN8ERVtop5VzxrtzH5Vh6pK6OUH4vduj0wW+KMFkaI/NAMk/xBvaR17Js/ExNyT1MhM78FOVje+2cq+UcdSalD/aWr4piKRnAYdJ+Vug7lg+2lYdbVQqwO/FUt5srMtkB3RiP+cvoBPys0bkHybtIg9xr5Q9yZuB/C9kB8o23VDiDymryFYWjsZGs86gHL9JWQne7T3POGWR8uX8aCl/oWdv4xB5foKpa4RRaRLkbNH+CJtawoxs3LP/LXRZwETuwW9p50z6Jp5Jb+7XzjlbnQEttjCruV+b+/Hl3lq7fYzcAxH3MJvvJu1o1D3zfaCNnsdqa1wl97LVvcC7kMHz7nMT7OeQDlD3pMoD+dQ+6UA9Z/FsUtQP7rF+HLa/PVCGYADElv31TcxJwGA/J3b1/lm+QH+JlHbthmznpydyDoK2VJua+uoJ3lX5sMErKcMD2BOz3fjlvRSGabdEGpSg+gvLOajgm+k5RoY6R5U8M0+RKiPbYqM4s7y2ctqcYJ5K5rHayn/QL3q7Lb/USYDvDNv54AFeWSc8g5X8hZ0LTp6c/ns2CJ1FvwXCcoSdzL0tOl36ZlRW6/VJuuHqt+gkiT9k0a/QU79mfvYBPLv+BOZ3q4+ewGMl/TGJV6jnDXGvH+5rnCN5LpL4/opmINNxiq/Y02ziVn+W3xjSsb9u9rqfX9rDRCkvi3FVvuTfWezJobNphpRTSF3uIvcbKvGf6vuvl+ddZvRFm0kw15z7Yb0Z4SOEjxE+QQj2QUXeyH1QoVf6IGk/jd7wNgXbO7YT1A/vNXnD29l8r3s7gz6c7Uy1350H81nT7O/xPBqc7sr3eAezLCxSN4Z8/tY5+gltPaPtkW5ou3svuQfFLgd9QNxC26o1eSG7xCUxu0TaJa5/+8Ndxf5w5af+xwt3vHBF2pidsib/fF2O/kzE6zYz7197+2U=
*/