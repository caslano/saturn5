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
79eFjHQVjMf/oOVZapwPOEqZ8SAWh4+RYV96B0Pgg6bQ6kLjwLKrl+XLZEEw6xH/uEprRCyFnilIb5MMMxmYs97MrRpunnIMXLRtQIqqHppllvAlPV6AkXORvWF/if3etFBBTn4zMhpR63vW4mV+/G0lOWOgWWE+5F2dOClYLivxkFarl38QponNqPnjREjz8HMwg0Mv6PTVRF8SxUNLU1Rou0E1y0RBB3stYzOrG2QBlP2CbckjVfKALqUhsNFkNQofrjjZVV7/ckF0XFPGubKhkRP+6Pq3i4/77AYmAVZUDph4ifWLupFOQ82zbMqyJAZgeaSNCK/KBjOgzf+lhAjXV7uOZqIBu0CLl4FVquFBhsDm1EG4dx0j2kgjeRo92Gn3M7rMp1LxJAb36BY4H1Wl7qY44/Tk3UP+d7y7KyuCT87gGQg02akPe5dlPAL/Ry7tj6C2RlfZPI9FMAXLeb9EiYbHFZdBpxspZOLMv4KKdub+eCWTl7pXVGidj6RgMP4nbLbL3XJo2pz1YKGHacJDAzHkVtr/6ZR0BaThCtIHGJ9JTlnq5RT0Yg==
*/