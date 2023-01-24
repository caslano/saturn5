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
I8WRg4TuWGnCJtGLcF74E/Ry+A1CLVwP0gbuxq+owRQaGFQZDDNGliAqY3Stnq+321v++79+VmKkyDLIfINsumJ1fnUchaIMx2npLZizFnRXosJU8zRl105X4LNa8eMEUTW5YppKFypLcarA9Phgs0SOtw5ysoQvUIpwGX/0EyMSY/5gwEoCcc/M/T0Y+0B6InCuT5XptH6R93OO5Htrmzzl63l9CzaO5rvpWqLv6y7BiNYUyp+mLRRNX6xApV4eMFefzSZ+jJk2t970RgSKddIsziCxsVQ+3/b2DqNxhlV5kMkM289lDxo4uOeMyXhem4ZSr3Ly1QDNxCdt0laPUgplqK8ZmBKMkLu83pGMV6Zmi2GsFSsTIUrjqo9HSf7r6H0gftroXfbycOgh2AyIcJ8jVjNAFkLIxlu5PEqzJxOg+Fdvm3CRCF0yDTMbYwxsE6TQxp/W6OSyv5b5enSZwvmVbaCcGSs1+K29OlOI0syp5/hvkELDmaQp82TK41xLFGygtKCHsdTSDwToChUihMFh66a3GI58T/qy/xxOFgIr/j2+QtxQYsj5ODvwWExFozgVGS3l25QAYC0ipV5fohEDnr8ShLdJEOlWdn6t+Nz7Ic63CYsDqH6mLccKog3/DkZxfM+ptz/+FRnMnrd7e+npdJAhdAzfFihI40Hfrc1GkmcKFlv4mrkLF/9ZQp3d6LJ4+dfHAnp6d46i
*/