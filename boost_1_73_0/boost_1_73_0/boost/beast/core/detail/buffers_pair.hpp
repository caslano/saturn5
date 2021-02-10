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
4ShzrrRv+/24MjnQ9xMd2368Sb+XudU2k0uAWIk70qUjp6myMiDeGdBKJyrlOwjBYllFubJZsEODUEXS14aszHP2BTslbQ1b0qKhJ+BtVAKxcnyzurAcap3p1YON4JG9pJUpEAg8YFOiQXNAVZFI4zf7zDchGk49wd8tzQ5vQroAGGoPFzRZtCkSVtmALibLP+bnS7oYnp0NZ8tLmo9pOLtkZ58msxOUXiGYIXlbGmkR3JBalbmSSRPz5139VusXVcR5lUg6tC5Rupcd7a9xReuy8nq/S4cno8XxEWP9yB1KVhXXedNyqQHDyHe8PF2gSOZGGkZMh/2NEeKBnAqTPnblmG3+aRHqWFhHcSYMddlRIVZygPXxZDqiLgykWA1a9wM2Fk7FCPq3DB2t7sJ0bZSTBzdaJdSNqjSVJth85tv2pVjJVRS0vjfJtYM6VKfFoB7h7OrK0Ts6eLzc2cAjUunBM+x6cdS48blBjbpodlk0FKGYDBmsMRv8fc8EAVLee+DXNlQE1F5H7c7A734cpMnISIc2phevBhwvxWxWPAmxKJ67vfA8BkxYHfu+tTVseNxnMGg42wcIEPetVksVIF+owvNe03V8fjalLnfKoHmLdcIaYwffkpm60sN511DUhjQZP1SRKtoBp8CJ
*/