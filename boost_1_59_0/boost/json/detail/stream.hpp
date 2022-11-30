//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_STREAM_HPP
#define BOOST_JSON_DETAIL_STREAM_HPP

BOOST_JSON_NS_BEGIN
namespace detail {

class const_stream
{
    friend class local_const_stream;

    char const* p_;
    char const* end_;

public:
    const_stream() = default;
    const_stream(
        const_stream const&) = default;

    const_stream(
        char const* data,
        std::size_t size) noexcept
        : p_(data)
        , end_(data + size)
    {
    }

    size_t
    used(char const* begin) const noexcept
    {
        return static_cast<
            size_t>(p_ - begin);
    }

    size_t
    remain() const noexcept
    {
        return end_ - p_;
    }

    char const*
    data() const noexcept
    {
        return p_;
    }

    operator bool() const noexcept
    {
        return p_ < end_;
    }

    // unchecked
    char
    operator*() const noexcept
    {
        BOOST_ASSERT(p_ < end_);
        return *p_;
    }

    // unchecked
    const_stream&
    operator++() noexcept
    {
        BOOST_ASSERT(p_ < end_);
        ++p_;
        return *this;
    }

    void
    skip(std::size_t n) noexcept
    {
        BOOST_ASSERT(n <= remain());
        p_ += n;
    }

    void
    skip_to(const char* p) noexcept
    {
        BOOST_ASSERT(p <= end_ && p >= p_);
        p_ = p;
    }
};

class local_const_stream
    : public const_stream
{
    const_stream& src_;

public:
    explicit
    local_const_stream(
        const_stream& src) noexcept
        : const_stream(src)
        , src_(src)
    {
    }

    ~local_const_stream()
    {
        src_.p_ = p_;
    }

    void
    clip(std::size_t n) noexcept
    {
        if(static_cast<std::size_t>(
            src_.end_ - p_) > n)
            end_ = p_ + n;
        else
            end_ = src_.end_;
    }
};

class const_stream_wrapper
{
    const char*& p_;
    const char* const end_;

    friend class clipped_const_stream;
public:
    const_stream_wrapper(
        const char*& p,
        const char* end)
        : p_(p)
        , end_(end)
    {
    }

    void operator++() noexcept
    {
        ++p_;
    }

    void operator+=(std::size_t n) noexcept
    {
        p_ += n;
    }

    void operator=(const char* p) noexcept
    {
        p_ = p;
    }

    char operator*() const noexcept
    {
        return *p_;
    }

    operator bool() const noexcept
    {
        return p_ < end_;
    }

    const char* begin() const noexcept
    {
        return p_;
    }

    const char* end() const noexcept
    {
        return end_;
    }

    std::size_t remain() const noexcept
    {
        return end_ - p_;
    }

    std::size_t remain(const char* p) const noexcept
    {
        return end_ - p;
    }

    std::size_t used(const char* p) const noexcept
    {
        return p_ - p;
    }
};

class clipped_const_stream
    : public const_stream_wrapper
{
    const char* clip_;

public:
    clipped_const_stream(
        const char*& p,
        const char* end)
        : const_stream_wrapper(p, end)
        , clip_(end)
    {
    }

    void operator=(const char* p)
    {
        p_ = p;
    }

    const char* end() const noexcept
    {
        return clip_;
    }

    operator bool() const noexcept
    {
        return p_ < clip_;
    }

    std::size_t remain() const noexcept
    {
        return clip_ - p_;
    }

    std::size_t remain(const char* p) const noexcept
    {
        return clip_ - p;
    }

    void
    clip(std::size_t n) noexcept
    {
        if(static_cast<std::size_t>(
            end_ - p_) > n)
            clip_ = p_ + n;
        else
            clip_ = end_;
    }
};

//--------------------------------------

class stream
{
    friend class local_stream;

    char* p_;
    char* end_;

public:
    stream(
        stream const&) = default;

    stream(
        char* data,
        std::size_t size) noexcept
        : p_(data)
        , end_(data + size)
    {
    }

    size_t
    used(char* begin) const noexcept
    {
        return static_cast<
            size_t>(p_ - begin);
    }

    size_t
    remain() const noexcept
    {
        return end_ - p_;
    }

    char*
    data() noexcept
    {
        return p_;
    }

    operator bool() const noexcept
    {
        return p_ < end_;
    }

    // unchecked
    char&
    operator*() noexcept
    {
        BOOST_ASSERT(p_ < end_);
        return *p_;
    }

    // unchecked
    stream&
    operator++() noexcept
    {
        BOOST_ASSERT(p_ < end_);
        ++p_;
        return *this;
    }

    // unchecked
    void
    append(
        char const* src,
        std::size_t n) noexcept
    {
        BOOST_ASSERT(remain() >= n);
        std::memcpy(p_, src, n);
        p_ += n;
    }

    // unchecked
    void
    append(char c) noexcept
    {
        BOOST_ASSERT(p_ < end_);
        *p_++ = c;
    }

    void
    advance(std::size_t n) noexcept
    {
        BOOST_ASSERT(remain() >= n);
        p_ += n;
    }
};

class local_stream
    : public stream
{
    stream& src_;

public:
    explicit
    local_stream(
        stream& src)
        : stream(src)
        , src_(src)
    {
    }

    ~local_stream()
    {
        src_.p_ = p_;
    }
};

} // detail
BOOST_JSON_NS_END

#endif

/* stream.hpp
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
*/