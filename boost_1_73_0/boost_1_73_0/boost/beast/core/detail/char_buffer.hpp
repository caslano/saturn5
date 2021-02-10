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
Iyw+I7gS2NGT6LT1un0QNclBZI4/69pmWkvz1Icfe0aBG33NOsnO1/sMtZ+FfK7jbH43nf8dGgbT6RMrHRtvwO+1ZW7hjRcjhdl7IS7CwJKXa8wgY12mYABBLh/hKdrLFrLcCMWkyc+a8p10eN5M4GNmh+BSNOXOcTvwSVxh+39eu/RuOiN3smpQboIkVWpSu9zzRFLmEU+utXVHt420GDudw8E3205wSu8NhWiaPOseOvQzhfsCDejVtCHLFDLCpEtWaAbsmZIW6KrHSaAhzoHiJn8QUCY8ajzsNJHTZV7NNm6oreaZZ+q+nS9X/7yD5qCBWcOCXO0OTrn/bfiqYHD8vPV8JG4Gq0FQlVJDw7LipiYtPdHRgUCgLrJuj2jihxg3Kwg6D6eDxbtR3Sf8weOIshVo96bU0ofQBQiDbK3HTwoXiDDwKrdos9xJRS3tSES9Wi2nZO3UZMYUsJz8a0QdHndUacmb03Vnt5g6a1FPDVEHbIW36CxT+f3ZwY7eMwN7tMFrDhods/E74dQj+zkAZoCYcwi7bnqOlZ8h4MIZYryWkgepLP6pNgnN8oRyCj+Je7a5qsUONxJUhw1y3G/q26AlFvDTG+fDKJz/0q1s/mpE+FpFlxJMjjKu28wTbxvBqlsOdHUbzkaZ
*/