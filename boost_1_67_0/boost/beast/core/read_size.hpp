//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_READ_SIZE_HELPER_HPP
#define BOOST_BEAST_READ_SIZE_HELPER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace beast {

/** Returns a natural read size.

    This function inspects the capacity, size, and maximum
    size of the dynamic buffer. Then it computes a natural
    read size given the passed-in upper limit. It favors
    a read size that does not require a reallocation, subject
    to a reasonable minimum to avoid tiny reads.

    @param buffer The dynamic buffer to inspect.

    @param max_size An upper limit on the returned value.

    @note If the buffer is already at its maximum size, zero
    is returned.
*/
template<class DynamicBuffer>
std::size_t
read_size(DynamicBuffer& buffer, std::size_t max_size);

/** Returns a natural read size or throw if the buffer is full.

    This function inspects the capacity, size, and maximum
    size of the dynamic buffer. Then it computes a natural
    read size given the passed-in upper limit. It favors
    a read size that does not require a reallocation, subject
    to a reasonable minimum to avoid tiny reads.

    @param buffer The dynamic buffer to inspect.

    @param max_size An upper limit on the returned value.

    @throws std::length_error if `max_size > 0` and the buffer
    is full.
*/
template<class DynamicBuffer>
std::size_t
read_size_or_throw(DynamicBuffer& buffer,
    std::size_t max_size);

} // beast
} // boost

#include <boost/beast/core/impl/read_size.hpp>

#endif

/* read_size.hpp
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
*/