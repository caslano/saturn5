//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_BUFFER_HPP
#define BOOST_JSON_DETAIL_BUFFER_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/string_view.hpp>
#include <cstring>

BOOST_JSON_NS_BEGIN
namespace detail {

// A simple string-like temporary static buffer
template<std::size_t N>
class buffer
{
public:
    using size_type = std::size_t;

    buffer() = default;

    bool
    empty() const noexcept
    {
        return size_ == 0;
    }

    string_view
    get() const noexcept
    {
        return {buf_, size_};
    }

    operator string_view() const noexcept
    {
        return get();
    }

    char const*
    data() const noexcept
    {
        return buf_;
    }

    size_type
    size() const noexcept
    {
        return size_;
    }

    size_type
    capacity() const noexcept
    {
        return N - size_;
    }

    size_type
    max_size() const noexcept
    {
        return N;
    }

    void
    clear() noexcept
    {
        size_ = 0;
    }

    void
    push_back(char ch) noexcept
    {
        BOOST_ASSERT(capacity() > 0);
        buf_[size_++] = ch;
    }

    // append an unescaped string
    void
    append(
        char const* s,
        size_type n)
    {
        BOOST_ASSERT(n <= N - size_);
        std::memcpy(buf_ + size_, s, n);
        size_ += n;
    }

    // append valid 32-bit code point as utf8
    void
    append_utf8(
        unsigned long cp) noexcept
    {
        auto dest = buf_ + size_;
        if(cp < 0x80)
        {
            BOOST_ASSERT(size_ <= N - 1);
            dest[0] = static_cast<char>(cp);
            size_ += 1;
            return;
        }

        if(cp < 0x800)
        {
            BOOST_ASSERT(size_ <= N - 2);
            dest[0] = static_cast<char>( (cp >> 6)          | 0xc0);
            dest[1] = static_cast<char>( (cp & 0x3f)        | 0x80);
            size_ += 2;
            return;
        }

        if(cp < 0x10000)
        {
            BOOST_ASSERT(size_ <= N - 3);
            dest[0] = static_cast<char>( (cp >> 12)         | 0xe0);
            dest[1] = static_cast<char>(((cp >> 6) & 0x3f)  | 0x80);
            dest[2] = static_cast<char>( (cp       & 0x3f)  | 0x80);
            size_ += 3;
            return;
        }

        {
            BOOST_ASSERT(size_ <= N - 4);
            dest[0] = static_cast<char>( (cp >> 18)         | 0xf0);
            dest[1] = static_cast<char>(((cp >> 12) & 0x3f) | 0x80);
            dest[2] = static_cast<char>(((cp >> 6)  & 0x3f) | 0x80);
            dest[3] = static_cast<char>( (cp        & 0x3f) | 0x80);
            size_ += 4;
        }
    }
private:
    char buf_[N];
    size_type size_ = 0;
};

} // detail
BOOST_JSON_NS_END

#endif

/* buffer.hpp
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
*/