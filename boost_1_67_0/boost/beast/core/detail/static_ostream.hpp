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