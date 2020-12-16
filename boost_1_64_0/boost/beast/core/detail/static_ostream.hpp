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
wBW4AlfgClyBqzOuztj/z4XPDtn/f6Np//9q7vFeyHXpycCuvZRyf6rXXefKnaeVlheWedbmz/e3uUT6iXqt/Q7x93NFm9fNF1QXm2zSMc1Q8c+F/1Lxj5I01cp/n1WJTjNc/Evhv8Ljd/mdycz1+dskPoXr8970E0znSS/Jxy20LS3aw5FZxVjav7lL0ijXLNVNFas0hsOa3mdG+HMIHamyVHmz/RuUAdLR5zzfI+l/V8PUwQxzqV0l7fkqUhXLPdfFSVmkHFncDwA546pa4vaxJfaB5Le/XV7mNe1Dlck2VbzQDHAs+85Y294edPVJKAUSxHAfQd94jz8W/iuBk+GPi/LYGJsS32xj7CJle02OEpnuHFUD3Fv28YZE3Sj3VgNgbkzWyeuNNQfTOnkswjboPQVsNwxvAFbb7NP5zOd8aNpXIq2njiO4Jg9ZG2F6/X3137j+/nets9uv+zud2bnt199Hy/p7xH2bPnn9+OdWvHnQa2lvXLv8E+ezYO33Cfzz1uvtz1jt2HX8NYrjGsfxGrOdF9pHGQ6M57pTH2AJ7aIcRDsoFcB+tCeTRDs7/YGXAVOAN3J97VbgjsDHuM72LNfJXuQ627tcZ/uA62rf0G5MAso0CjgOOAY4ETgWOBm4E7AkuG3rLDyrgest1jMaBsBZ113szmJwPIeBZy+0fR2G5yz4nKVgf46CeX3mSa7RmM5MMJ2V4Lxec7r/mo35XIQW1294BgLPP3Bay/E956DldZ0T4PzOM+AaT/hkp3We9p1dYD6vgOs/ckbBV5P/+tkELZxLgLWh1s8jaMv6UFvPHTCvGWXCec8YqIXzPVugCfiOgXC+a0kx2c3rSeOzzWcGWM8LWBtYLwpcgStwBa4OuzpF/68spfV/tdX6//Um/f8z6v/HUf9fAJxnfOf8sdb/Z+PO1P4d9X/ST9P6/9PiH+eKNn9jhW3Wzfo/01D/3xf+m8WfK2mqbb6zytVpJus5gyfEv7Oj/r9G4rOo/3vTZ7VL/18rafq4chXOFlOZWoeO+8QI/0R06OnqGH7TaFyVZdDaJc9MpZznBSTfYa4sdQTDwL3keQfexSvbPS/wg+S3v11ejvMCaUIzwJGnCZgXiGhlXiCRcwMzTXMDB/7FuYENn7RtboDfmLFNmeYGuv61uQHaXuY3C1J/gfmCf/B8wWKZL1g5ZPmYMyKevGKv8Lp9jj5m2ozAfEFb5gs+UxwHOe7XwPXB73dM8wVDaU91FO2gjqE91ZmcNziY8wZLgEncx9yf+4STud87BXgl5wtu4XxBHecLngQO5v7vVGA95w3e5rzBt9yPu5n7bo3CjgYO4bzBdGAmMJf7hfO4X7gAOB64ALhrYF4hMK8QmFfolHmFzKsC8wqBK3AFrv/f1Tn6f1FhWQfp/9eY9P+P+A3fzvzuejTcL3ghq/2wWf/HnS36f3iM/7f5dwr9IM4HeNNHO9keYnxvia/Stoao55viTfq4/j77PolL0fYg3sCLZ2Pvtn+TjfI72/Mxn3/FMJRLdL8MnzPbjG83BwETgVFpKINVZnvw23SLvCgf0k7V8xhjPhK7WkL/YpT1jLMcTT9JRXNeI0Pox+D+3RjmUvtJ2CsIuU3yOUryKTpY9GDaNxghNBvVVWocZe3Nezeeu+dS9UKzH97PQ0EVwjry5FXGvKYjXZrQfaBWMa+ZOq/xktd0ndc8lYZewrzYHkr1PMQcpOsndNu5mm0kMC/aSGhQynxmV/UCcBXNeaNUSfuxWoX7etOn+6SHzmM6P67cyEDuHQv/Ykl/vU6b6ZO2UdJyLoa2+Wzmi/TZSpslv3AVK36vDOarAQiDDLQ9si97e9rtMuR7KN3u0Z4=
*/