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
h2v+mvjnzvm72lf6V1v80wF++auq8KfiN8pfdYU/xrrRxK4E52MkiYWGPDPxCGm0jsigzozflY1k4pwrGYxgPMeTkdQePAuYOVjnYG7vk+fm7tA5G847v3Fh+yWVT06NTaSzpDfq78bxOl+d/iTNLdpfDfd9+OvxpLr4dviJZL4fh58raTKmuzWMS7iJOh9hyZ+WwL+YfI68Ef77O6oA+69vsLt3AM9gn1+enUP+/pb+LtET
*/