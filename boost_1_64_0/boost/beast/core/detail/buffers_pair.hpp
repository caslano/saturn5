//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BUFFERS_PAIR_HPP
#define BOOST_BEAST_DETAIL_BUFFERS_PAIR_HPP

#include <boost/asio/buffer.hpp>
#include <boost/assert.hpp>
#include <boost/config/workaround.hpp>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# pragma warning (push)
# pragma warning (disable: 4521) // multiple copy constructors specified
# pragma warning (disable: 4522) // multiple assignment operators specified
#endif

template<bool isMutable>
class buffers_pair
{
public:
    // VFALCO: This type is public otherwise
    //         asio::buffers_iterator won't compile.
    using value_type = typename
        std::conditional<isMutable,
            net::mutable_buffer,
            net::const_buffer>::type;

    using const_iterator = value_type const*;

    buffers_pair() = default;

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
    buffers_pair(buffers_pair const& other)
        : buffers_pair(
            *other.begin(), *(other.begin() + 1))
    {
    }

    buffers_pair&
    operator=(buffers_pair const& other)
    {
        b_[0] = *other.begin();
        b_[1] = *(other.begin() + 1);
        return *this;
    }
#else
    buffers_pair(buffers_pair const& other) = default;
    buffers_pair& operator=(buffers_pair const& other) = default;
#endif

    template<
        bool isMutable_ = isMutable,
        class = typename std::enable_if<
            ! isMutable_>::type>
    buffers_pair(buffers_pair<true> const& other)
        : buffers_pair(
            *other.begin(), *(other.begin() + 1))
    {
    }

    template<
        bool isMutable_ = isMutable,
        class = typename std::enable_if<
            ! isMutable_>::type>
    buffers_pair&
    operator=(buffers_pair<true> const& other)
    {
        b_[0] = *other.begin();
        b_[1] = *(other.begin() + 1);
        return *this;
    }

    buffers_pair(value_type b0, value_type b1)
        : b_{b0, b1}
    {
    }

    const_iterator
    begin() const noexcept
    {
        return &b_[0];
    }

    const_iterator
    end() const noexcept
    {
        if(b_[1].size() > 0)
            return &b_[2];
        return &b_[1];
    }

private:
    value_type b_[2];
};

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# pragma warning (pop)
#endif

} // detail
} // beast
} // boost

#endif

/* buffers_pair.hpp
AvwcvPXTffuc4nLd5zS5e5x9DsPE6G/4DbGvo91Q+Tlsh7rvmVup+x4dfhPt5EdevX1PqT4rfIX4vQO7p++p0Pc+twfeKf5lKlJ1R62do+99LhT3ON4fbajkKyUNazzuOmO9zxH++2gPyJ8qcmb8jwr/JWhJiboOrxe31syDTxzs++aaxdP7amcI/4Ez7h9mfVvuLfev77l67+lA7o/cxbP7MxjRlaBp2GBQK3mqKS1fWIwjy0qXz1DVpeVAfjfka9/0m2Ybv138pwf8dp9guT2yfVrsA7Rs68Qe4fu9sj5fYbqsN/I6mn6vlPk28R+q2qn4gN/rHvFPgl900++VdfkT4Znq/73q8nwm/oaWzWaxjz3jflXWG++FF/nqvaSdQOPkzdvWv+uQuzDF2a12c+KuHe8dzrXe1yr9rpgc3tdao/i3m+MHxX37LvKfx/0LGdQvDwf24D2iy3mP6C28R3QD7w09xn0mX/N+UJu5Dw8Yx3s2O/OezQTgZOpB6xW/Y/Ypnr24Oz17fal/jgW2AMYBM4Adee9rJ+A1wM7A+cB4YA2wC+997cb7NrsDNwOTgL+iPvYVYG/gh9yH8A2wH+8PTQH2BQ4ADgAOBA4GpgIvBA4GlgDTgJQn2zq/FT95TgMLvx/R586nHt/JI8hXcx9QAbAP9/mkAQv51m8p77Ocw31Bc7kvaB7wSsYTC6yBbuQeUB3oAOhkSFcSMiETMiED89+a/8+fNXNY2r99D6A5/+9rmf+7OP9vdP99UnuBX/bDPrPL9VjcnbJnNO73dp5l/s8wF+u3xI6I/QHD8g5XlYv8EzT/RP2mV6PYt9GOVYJppr2niuFYCGNrnAR2lejxko7jApOH4/vKwpLioqqyYvc9FcngTZ5q8hTxfTFPmK8kjmmw3yb+tUr8dbrJyptvvIhR6H0/7KSEX294yt1f+M9XYtfhW1jePmKafIuo3nNmVuIur5pnuVNjmOTlCiOGeftIwm0x6lStji/VL769fDcsWc7TF1neNEIanrfEOIexSfyLjVjDPSdKEv+FejwdA8wQngg9v4imfFLgFsf5xCZxa0TLy1ZP+4yfyySecoR7S/L4qOE9X1tZsJDv6MyH/7fif5P4P5SiIDFXqXs+NRrjad4BLum8CDe8HwL3OXR/QtwnCm97foN3itsrGH93E94S7of7jbhfrGIkXolA13G8xCluPmV6gHGY436HlV/iFbcmMpC33SzvWim0G+sc6w0pb5Ru/8fd34d+v+8PYo+jv287ZD2lWuc9LSX9DVInKIN//vXZ1yTeS5CvaIK8rZbNt9XMucImy7uInjn9VqXfO6ty8dxhnekn4fht0n2Xng/q71HiqNdxyDel33Z0iRu/Bd5/hfYMtyKTR+SKNgI72ojf3GVRgZxru+0915ob71rRuO2F6FMP1h5wz1G2er4V9nGK+b1H6XlCzVCO7e/h2H4z91j+lmP7I8A+QLt8y3IWRfYat+cYP55j+yuB5wILgYOALo7xl3GMfxMwHXg38HzgHmAGcC9wODDKMvaOvjE05g6ZkAmZkAmZkAmZkPlfNf+Z+X9x4UyZ/f/7+v/eljusq22cT/FOjB2gz8z5/xQ9/zdT1rP/wHN/8nPuMgX2x8Weo5rM/amLf1r87xT7BB3+nIB6umztX65a6blikczPYhTH9DLG76jdHKBUceui59bHJY5Cy3yqzGfe+634t9H6n1fFPsDKb0ajdWx7xX+sZZ515juxeU9Jk7lVunVuRbdMP51aG3dYzoOK3O9Fsx73sx5bMLEI0GdIo9a6joP2ML+88ow6PuvcarvMrfYOO36wddVjyV9fGNGi2ztfPqwU39livUj70ek=
*/