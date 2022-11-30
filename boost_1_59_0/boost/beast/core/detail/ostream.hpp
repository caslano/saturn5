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
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
*/