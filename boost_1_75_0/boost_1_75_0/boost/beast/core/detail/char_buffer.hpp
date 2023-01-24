//
// Copyright (c) 2019 Damian Jarek(damian.jarek93@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_CHAR_BUFFER_HPP
#define BOOST_BEAST_CORE_DETAIL_CHAR_BUFFER_HPP

#include <boost/config.hpp>
#include <cstddef>
#include <cstring>
#include <cstdint>

namespace boost {
namespace beast {
namespace detail {

template <std::size_t N>
class char_buffer
{
public:
    bool try_push_back(char c)
    {
        if (size_ == N)
            return false;
        buf_[size_++] = c;
        return true;
    }

    bool try_append(char const* first, char const* last)
    {
        std::size_t const n = last - first;
        if (n > N - size_)
            return false;
        std::memmove(&buf_[size_], first, n);
        size_ += n;
        return true;
    }

    void clear() noexcept
    {
        size_ = 0;
    }

    char* data() noexcept
    {
        return buf_;
    }

    char const* data() const noexcept
    {
        return buf_;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    bool empty() const noexcept
    {
        return size_ == 0;
    }

private:
    std::size_t size_= 0;
    char buf_[N];
};

} // detail
} // beast
} // boost

#endif

/* char_buffer.hpp
v17nJmyTv9bFq2r1Tt7xwAl9SlcY0Oh8SznVpHTCO6/eFCm0bo6JPgshSecHiAg9Ggyky86bZJE+r2vcpPL7GQ4svzsSVlUQ3JjYd+ow7GkBqfYH15SphAv3HvlOfODKb11u4GhQN34QezBtbPG9el8YsdSQZt57THJ6Y9ZAMtFvb6TyP2faRW/ephXNqgdwz7lOmk3Cu0Wlv0lq58Bd7gUfLgqQT17i7SVhrv/oushx7QHoEtz32hMUa1k1gAyZsw5H3ILB/FdGV8oI/Fgr/kxQXz/+qyHZ1NkKY7JrzHLjWxjslyT1Jupe7RvsastvMyT8CQv9HRbwoHKPtgWOGhbUIIf1vz0GkbzDipKYzmDC4t3PtYywAujj2+YtUxS/+qHiMzSDBdweVzM5fgNA8cP9jHHB38oD5fB7Acv0IzwZmjttMjwvvnToe+MP60dksdzBWKyoH2f3vj4e/7IP9DsCoEJdp167rmDpjlsoLHuwgCiYwJPoIpi0ubZ7XtpbktdvhXg8GaYND5u44tuk6QGjKDFfgZV1mkDYu8LjN7ewMge0fViZW5YVNMibzl+awHYcMqJ0e3Z7R0LTYsXVT91fl1l1oPiWfCbbmQr7zXfM7cb8QlKX/3If2ZNA+BegWohsR/2MQq7+NlrVhlNuhi6x5JDorLtk/nwpdrYzo/e1Gk2Y3m0/cinxtZohaz3kD1ArK7/DYifXi0Jn
*/