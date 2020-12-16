//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_OSTREAM_HPP
#define BOOST_BEAST_DETAIL_OSTREAM_HPP

#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/throw_exception.hpp>
#include <boost/asio/buffer.hpp>
#include <memory>
#include <ostream>
#include <streambuf>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

struct basic_streambuf_movable_helper :
    std::basic_streambuf<char, std::char_traits<char>>
{
    basic_streambuf_movable_helper(
        basic_streambuf_movable_helper&&) = default;
};

using basic_streambuf_movable =
    std::is_move_constructible<basic_streambuf_movable_helper>;

template<class DynamicBuffer,
    class CharT, class Traits, bool isMovable>
class ostream_buffer;

//------------------------------------------------------------------------------

template<class DynamicBuffer, class CharT, class Traits>
class ostream_buffer
        <DynamicBuffer, CharT, Traits, true> final
    : public std::basic_streambuf<CharT, Traits>
{
    using int_type = typename
        std::basic_streambuf<CharT, Traits>::int_type;

    using traits_type = typename
        std::basic_streambuf<CharT, Traits>::traits_type;

    DynamicBuffer& b_;

public:
    ostream_buffer(ostream_buffer&&) = default;
    ostream_buffer(ostream_buffer const&) = delete;

    ~ostream_buffer() noexcept
    {
        sync();
    }

    explicit
    ostream_buffer(DynamicBuffer& b)
        : b_(b)
    {
        b_.prepare(0);
    }

    int_type
    overflow(int_type ch) override
    {
        BOOST_ASSERT(! Traits::eq_int_type(
            ch, Traits::eof()));
        sync();

        static std::size_t constexpr max_size = 65536;
        auto const max_prepare = std::min<std::size_t>(
            std::max<std::size_t>(
                512, b_.capacity() - b_.size()),
            std::min<std::size_t>(
                max_size, b_.max_size() - b_.size()));
        if(max_prepare == 0)
            return Traits::eof();
        auto const bs = b_.prepare(max_prepare);
        auto const b = buffers_front(bs);
        auto const p = static_cast<CharT*>(b.data());
        this->setp(p, p + b.size() / sizeof(CharT));

        BOOST_ASSERT(b_.capacity() > b_.size());
        return this->sputc(
            Traits::to_char_type(ch));
    }

    int
    sync() override
    {
        b_.commit(
            (this->pptr() - this->pbase()) *
            sizeof(CharT));
        this->setp(nullptr, nullptr);
        return 0;
    }
};

//------------------------------------------------------------------------------

// This nonsense is all to work around a glitch in libstdc++
// where std::basic_streambuf copy constructor is private:
// https://github.com/gcc-mirror/gcc/blob/gcc-4_8-branch/libstdc%2B%2B-v3/include/std/streambuf#L799

template<class DynamicBuffer, class CharT, class Traits>
class ostream_buffer
        <DynamicBuffer, CharT, Traits, false>
    : public std::basic_streambuf<CharT, Traits>
{
    using int_type = typename
        std::basic_streambuf<CharT, Traits>::int_type;

    using traits_type = typename
        std::basic_streambuf<CharT, Traits>::traits_type;

    DynamicBuffer& b_;

public:
    ostream_buffer(ostream_buffer&&) = delete;
    ostream_buffer(ostream_buffer const&) = delete;

    ~ostream_buffer() noexcept
    {
        sync();
    }

    explicit
    ostream_buffer(DynamicBuffer& b)
        : b_(b)
    {
    }

    int_type
    overflow(int_type ch) override
    {
        BOOST_ASSERT(! Traits::eq_int_type(
            ch, Traits::eof()));
        sync();

        static std::size_t constexpr max_size = 65536;
        auto const max_prepare = std::min<std::size_t>(
            std::max<std::size_t>(
                512, b_.capacity() - b_.size()),
            std::min<std::size_t>(
                max_size, b_.max_size() - b_.size()));
        if(max_prepare == 0)
            return Traits::eof();
        auto const bs = b_.prepare(max_prepare);
        auto const b = buffers_front(bs);
        auto const p = static_cast<CharT*>(b.data());
        this->setp(p, p + b.size() / sizeof(CharT));

        BOOST_ASSERT(b_.capacity() > b_.size());
        return this->sputc(
            Traits::to_char_type(ch));
    }

    int
    sync() override
    {
        b_.commit(
            (this->pptr() - this->pbase()) *
            sizeof(CharT));
        this->setp(nullptr, nullptr);
        return 0;
    }
};

//------------------------------------------------------------------------------

template<class DynamicBuffer,
    class CharT, class Traits, bool isMovable>
class ostream_helper;

template<class DynamicBuffer, class CharT, class Traits>
class ostream_helper<
        DynamicBuffer, CharT, Traits, true>
    : public std::basic_ostream<CharT, Traits>
{
    ostream_buffer<
        DynamicBuffer, CharT, Traits, true> osb_;

public:
    explicit
    ostream_helper(DynamicBuffer& b);

    ostream_helper(ostream_helper&& other);
};

template<class DynamicBuffer, class CharT, class Traits>
ostream_helper<DynamicBuffer, CharT, Traits, true>::
ostream_helper(DynamicBuffer& b)
    : std::basic_ostream<CharT, Traits>(&this->osb_)
    , osb_(b)
{
}

template<class DynamicBuffer, class CharT, class Traits>
ostream_helper<DynamicBuffer, CharT, Traits, true>::
ostream_helper(ostream_helper&& other)
    : std::basic_ostream<CharT, Traits>(&osb_)
    , osb_(std::move(other.osb_))
{
}

// This work-around is for libstdc++ versions that
// don't have a movable std::basic_streambuf

template<class T>
class ostream_helper_base
{
protected:
    std::unique_ptr<T> member;

    ostream_helper_base(
        ostream_helper_base&&) = default;

    explicit
    ostream_helper_base(T* t)
        : member(t)
    {
    }
};

template<class DynamicBuffer, class CharT, class Traits>
class ostream_helper<
        DynamicBuffer, CharT, Traits, false>
    : private ostream_helper_base<ostream_buffer<
        DynamicBuffer, CharT, Traits, false>>
    , public std::basic_ostream<CharT, Traits>
{
public:
    explicit
    ostream_helper(DynamicBuffer& b)
        : ostream_helper_base<ostream_buffer<
            DynamicBuffer, CharT, Traits, false>>(
                new ostream_buffer<DynamicBuffer,
                    CharT, Traits, false>(b))
        , std::basic_ostream<CharT, Traits>(
            this->member.get())
    {
    }

    ostream_helper(ostream_helper&& other)
        : ostream_helper_base<ostream_buffer<
            DynamicBuffer, CharT, Traits, false>>(
                std::move(other))
        , std::basic_ostream<CharT, Traits>(
            this->member.get())
    {
    }
};

} // detail
} // beast
} // boost

#endif

/* ostream.hpp
9FSTN8fBW0Fezi2XA7U90t9QbzyLjbbf7DbgZnTBBtxrcmYYy8pmA84sB9OOJ3XMOAq1P/RHv2LtR13wGxL3Y1t5FvuChyQPeOfOttu9TeLalUgEDgB+AIpCphs/cK93RXX1tW51L5nf4z4tcm+q2/D7BKhVhbP++eMcYqx/qcZ5nFy/osMT9LqSHeJ+Ee+Tl+t1JemK52PqOGTrOL/pMQ58kbiaMgVaZoTIvCQTM6I+/U3xLZEZR7efP0OX993Q1ANJ3bf5p8ubfvl6nl/yLX4F2k/yIWW1SvHdm2XlX2c0mIbc+rKswoFjxqOPAb+zrGDWzSgjrySC5UD+IXodzWvi/rtaKDPkHspJOxC5BJbtIo/Fd6vaiDT57aQ/PjCwJmJvko/mJnVXR0wf8r5X7oFvONl2O5jHmfci0CDiMfxJDwvOO02gOeuo/mY8U2QWUh/+OIbpfvJ6cXt0+T+c4KMHQSXdOCNQlz/b4EUSL75LMW/zmDf/sUeRxrPwIrTBZpe8wYhUTpG3vLwWXYZbHpknykZ2ajuLtu2MtNr7h8xo97S1hEybJCxkulp6mC6/zlpd0jU6G/7u6SrCE5rmUUOnrbWHafPrrLCve9ra3NPWabraepguv85OMF0RFAoH/Qm87SHShdFVLZfkhEobZSPOOG1+nT0dGzjLVewsg+5KRbt3SVtFecPUEGMg3Vf1C7fklqrkwDoJxjXCdRyCKBierM8SjZE4rlAZqo/xvMHdKVOg4xxvzK+trYS+9HzaCIljhRqM3wSxj0ce//mwXDuRLHyXOde36THIFRI+UNsEVT3oi2jjJGgskaefRZJHPUZJED6mmX3ZPKSH4wnbM2obzylIVhzHgl5PQ38UHlyOMGAU6kxe8ifLPN6RBCu8nOMEI4zz1N/pwlycy/m3+rxjxA+/ctvzpqCfkms485EASrX6F/d8FFWW2e0kAjiH6JdJcMsLw4afUV78NmoAbnnRNnqL+3PcwEiiQeOQl+Mueamz+nBoZ315NWz6rasJ3S9RHrFKvmWMjZ6M4YsD4XxnYLhxLnJFgOeM+g99breMdX33pg1W6ob3c/SDOQOC++cJ2dYfF3108dnhk4003jcsCepCws+8D7fbsZR4bX3n6RD5iXfLTxeeN/Gd5CX+Q8zLPq75KGa7W8XnQLpbXupr+RwImRfKJYh7OdxTxb0s1DOA/MVGf19n2tJi+HK4/escpILZ1nytFJ4IlWFZoUIcs5Cnu4FxYf1g2jkyOjYWEBuFn4h+Qffhu880ieM8Y10C78OzAiZL+AV4G47skl3oM3sOIE3s7zdHsL93jMvTLaVxTnIA6EpQNniaHeUl315KyspyWFYjB0ufb3nrZ/ZTIrNIZeKX5cd4hvnshA/02df7QQZ0GbdU95n30064n2cneA7IGQWzDftuXANDe4Tm+9+P5R799fvfy+KOtcW5H3H+0IpzUKqOcxXvm6pWSLyVpfDsE/QtSN/n6xLv4C4/s6EjlIHoyKbzo9R5pIftHZiL+6dHuui8tMbrH4+nic7L6up1+6AMYgqUSV1tqe7DA+Fdbetpkmbcg37xOh8Sry0fbbRpfxfb+s2gaciHt49LPtbBwqwyn7HyZYTPWMpwbDc9W3/D0bo/KuHRuozfFncYylLyjcu3zjwJvJ+WsKskrhgJkyVBLuc50gYd2+QekUugGydfiruf1F3rXfU04jpo1aHxy3QdWmzUXXmfhU6etXj6zwg+o4o8C8DzYznzZrzmuaQbddEq9zskbUOlLkZ7Oi7XeI+/j6DO4Qc9sVzrdX2NETd05SjnRi76mgxKIM4Eb06USznz5Z31VfcRTDdlxtON0bm4I8/oTIM=
*/