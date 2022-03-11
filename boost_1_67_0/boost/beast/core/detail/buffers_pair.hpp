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