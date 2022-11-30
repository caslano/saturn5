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
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
*/