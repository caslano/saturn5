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
vBBURBiNsf20EotwK7KQ+L6ERnFuj+RfCOG33LwauXbfz5yXlzyrRqpy6SBw3JIBqCCNci/oVnrwjWoSdSFUBvdVFi3K0PBQl2l2c55fdyG/mLfYlkOcWwkPkm1vyD/UNPUhYhqYwQfqYPuS2VmZ7RzPBlJJ58cNhXFCezcJPMFIrrPILkHHr4WWzSApslLtp5hGrrsOfa9H1751FmR3wiyZ9N1o1lgT4ITe2LM24nGmloQDd5Jz1IS0ao9VkZQNiDHf7VXZs0P3dSieXRXhKHOI+NRA1mpar1gR0L9t6P0JlyYtolXKEgKziHgCeKlVbMvIxAk/BTmn66CW509oXlHgLuHRufmgTAN/DB5GlD8t33abtV91Tx74o+EAERdNQw4+sWvsYC4SROHMKt/1JE0QZumbRq4LjLk1uuOxTPo4Jl6xE8sN5LMm1Nqf0AX92nzhxXWl/0SIe7d4oAx1ptdxpBHKHa91Lf7+3i157eqTYy/WQctuR0dM5nIdnXw0hK8bcEFSTYDSwdy8uHm8dlpa27oTKx3BIwWUO7fn82LOVef1J7NK9MXe3A==
*/