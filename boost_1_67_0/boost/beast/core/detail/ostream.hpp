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