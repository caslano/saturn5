//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_RANGE_HPP
#define BOOST_BEAST_BUFFERS_RANGE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/buffers_range_adaptor.hpp>

namespace boost {
namespace beast {

/** Returns an iterable range representing a buffer sequence.

    This function returns an iterable range representing the
    passed buffer sequence. The values obtained when iterating
    the range will be `net::const_buffer`, unless the underlying
    buffer sequence is a <em>MutableBufferSequence</em>, in which case
    the value obtained when iterating will be a `net::mutable_buffer`.

    @par Example

    The following function returns the total number of bytes in
    the specified buffer sequence. A copy of the buffer sequence
    is maintained for the lifetime of the range object:

    @code
    template <class BufferSequence>
    std::size_t buffer_sequence_size (BufferSequence const& buffers)
    {
        std::size_t size = 0;
        for (auto const buffer : buffers_range (buffers))
            size += buffer.size();
        return size;
    }
    @endcode

    @param buffers The buffer sequence to adapt into a range. The
    range object returned from this function will contain a copy
    of the passed buffer sequence.

    @return An object of unspecified type which meets the requirements
    of <em>ConstBufferSequence</em>. If `buffers` is a mutable buffer
    sequence, the returned object will also meet the requirements of
    <em>MutableBufferSequence</em>.

    @see buffers_range_ref
*/
template<class BufferSequence>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::buffers_range_adaptor<BufferSequence>
#endif
buffers_range(BufferSequence const& buffers)
{
    static_assert(
        is_const_buffer_sequence<BufferSequence>::value,
        "BufferSequence type requirements not met");
    return detail::buffers_range_adaptor<
        BufferSequence>(buffers);
}

/** Returns an iterable range representing a buffer sequence.

    This function returns an iterable range representing the
    passed buffer sequence. The values obtained when iterating
    the range will be `net::const_buffer`, unless the underlying
    buffer sequence is a <em>MutableBufferSequence</em>, in which case
    the value obtained when iterating will be a `net::mutable_buffer`.

    @par Example

    The following function returns the total number of bytes in
    the specified buffer sequence. A reference to the original
    buffers is maintained for the lifetime of the range object:

    @code
    template <class BufferSequence>
    std::size_t buffer_sequence_size_ref (BufferSequence const& buffers)
    {
        std::size_t size = 0;
        for (auto const buffer : buffers_range_ref (buffers))
            size += buffer.size();
        return size;
    }
    @endcode

    @param buffers The buffer sequence to adapt into a range. The
    range returned from this function will maintain a reference to
    these buffers. The application is responsible for ensuring that
    the lifetime of the referenced buffers extends until the range
    object is destroyed.

    @return An object of unspecified type which meets the requirements
    of <em>ConstBufferSequence</em>. If `buffers` is a mutable buffer
    sequence, the returned object will also meet the requirements of
    <em>MutableBufferSequence</em>.

    @see buffers_range
*/
template<class BufferSequence>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::buffers_range_adaptor<BufferSequence const&>
#endif
buffers_range_ref(BufferSequence const& buffers)
{
    static_assert(
        is_const_buffer_sequence<BufferSequence>::value,
        "BufferSequence type requirements not met");
    return detail::buffers_range_adaptor<
        BufferSequence const&>(buffers);
}
/** @} */

} // beast
} // boost

#endif

/* buffers_range.hpp
KTpnN1w0RKq2SEKPcPxyCkIeXrbWOfEI9bQhD7MFpMSdw2Co6s05BJZzK6Ri48oXAlWtTWsNSevCf3MiAhAEkg+lxDw7Zecev6E2hj3DP5liwVciESE2deVg6eQiv6sQjYHTGU8W3n+OBdWTdIZ58Mc7+RRFDPbPjnxZGHxZ8GqoxYhH94wFojaTmkzNc24uH2mcUIUMQ5ehaT5lzeKhCPnaI5/LIt4tVkWHyjyJ8ma6V9HRPFkra1uhT+dO1E1rNCmc/EmP7iyiHGDv6JqTpIp8g42PZQIhAZhsWxyZuH4USMRoGZQR1FIpcFtD1lPdl+IwInE5AOr8tBLCokvdvYRDHnkf5Ut9/o7a/oeI0PNUNDLMfv2vrfa6s2ZRDt+i84Tu5YjWHumEdn1aCj/5HaZ2GIUipiYkyypC311oS2CAbNQ9WjztEyHaW7aO8Kc+fuN6Xg+4hZH0Fofc2FDNM2k0IHukrS2PqPhU99efZRvNgDk9evL9VFNdDcD1AnqkIpDRg0JHc7A5uOW0Wzc+F2w+hSITb7/GRNyJ0w8q1PWzIK1IHg1kQD2eZw==
*/