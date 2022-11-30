//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STATIC_OSTREAM_HPP
#define BOOST_BEAST_DETAIL_STATIC_OSTREAM_HPP

#include <locale>
#include <ostream>
#include <streambuf>

namespace boost {
namespace beast {
namespace detail {

// http://www.mr-edd.co.uk/blog/beginners_guide_streambuf

class static_ostream_buffer
    : public std::basic_streambuf<char>
{
    using CharT = char;
    using Traits = std::char_traits<CharT>;
    using int_type = typename
        std::basic_streambuf<CharT, Traits>::int_type;
    using traits_type = typename
        std::basic_streambuf<CharT, Traits>::traits_type;

    char* data_;
    std::size_t size_;
    std::size_t len_ = 0;
    std::string s_;

public:
    static_ostream_buffer(static_ostream_buffer&&) = delete;
    static_ostream_buffer(static_ostream_buffer const&) = delete;

    static_ostream_buffer(char* data, std::size_t size)
        : data_(data)
        , size_(size)
    {
        this->setp(data_, data_ + size - 1);
    }

    ~static_ostream_buffer() noexcept
    {
    }

    string_view
    str() const
    {
        if(! s_.empty())
            return {s_.data(), len_};
        return {data_, len_};
    }

    int_type
    overflow(int_type ch) override
    {
        if(! Traits::eq_int_type(ch, Traits::eof()))
        {
            Traits::assign(*this->pptr(),
                static_cast<CharT>(ch));
            flush(1);
            prepare();
            return ch;
        }
        flush();
        return traits_type::eof();
    }

    int
    sync() override
    {
        flush();
        prepare();
        return 0;
    }

private:
    void
    prepare()
    {
        static auto const growth_factor = 1.5;

        if(len_ < size_ - 1)
        {
            this->setp(
                data_ + len_, data_ + size_ - 2);
            return;
        }
        if(s_.empty())
        {
            s_.resize(static_cast<std::size_t>(
                growth_factor * len_));
            Traits::copy(&s_[0], data_, len_);
        }
        else
        {
            s_.resize(static_cast<std::size_t>(
                growth_factor * len_));
        }
        this->setp(&s_[len_], &s_[len_] +
            s_.size() - len_ - 1);
    }

    void
    flush(int extra = 0)
    {
        len_ += static_cast<std::size_t>(
            this->pptr() - this->pbase() + extra);
    }
};

class static_ostream : public std::basic_ostream<char>
{
    static_ostream_buffer osb_;

public:
    static_ostream(char* data, std::size_t size)
        : std::basic_ostream<char>(&this->osb_)
        , osb_(data, size)
    {
        imbue(std::locale::classic());
    }

    string_view
    str() const
    {
        return osb_.str();
    }
};

} // detail
} // beast
} // boost

#endif

/* static_ostream.hpp
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
*/