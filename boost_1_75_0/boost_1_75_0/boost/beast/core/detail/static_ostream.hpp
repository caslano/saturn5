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
iQaFjA3lXjbEeyn5g3WD51S5468u9HOh/r6mU1DJ7zYVHQELNY75KuLz7egiezOu73iY5DJL0FASSdKZn5AXrwyTat0+u+VgRJ/enYM1idevrdgzT+6VgWTdUVaRpUDJj6+df2MxX3xWubWo7CAEExr3rxf+bYiaZWBm9+QWmRe9JxzYl8HlO785GnA9aKLTx1ALxd1fccsg6KLY+reeSGAUJDiOF1JjM0ToYrZZB0eVVFF7g3Xo8e3tI7C1QfvHs6N0DP1uUDw3CFKQkqOZ2gy1obYxp2nIVzasgbBtGdjfn1+wsusnyqU5HaRNo+EGNc72u8QDCu67sZulDCcifAE12jZyt6xQTL2wcfrPBvyAb7+jCw8VT5T5c34R7drMHGAnZb7oebcWXHj4XYZX3S1iAoRpfsF3wvwKl88hk6P56yAmjWSF7a/9+uUSgG2VbyBlumj+naYmWhwCSgBZ3WPAAa6bcWHjvvoG1fZLlUwlFV3su2rLYm8VzHJw7Uotjdr2YO02+wim5iJV+iDHyxf7kLucWNUkC809DT5tFaGDMw0DCrlCZjW+XOW8858WsdLkFHwV/5b4K/xT4j8KrsqrfWSI2ovTspVL40lsyLhFYqHYoJ7nyGz2CAy1hrWbyyDgQLm9D57NtsT44HiSQ3hH8GfJXCBueSxRSt2U/066ZrjKmv4DzwC4DlEV2B7g7z9hnaaL0Jl3RNPc
*/