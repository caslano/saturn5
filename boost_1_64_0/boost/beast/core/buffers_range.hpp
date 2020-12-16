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
AL4JdNBtpXegg/ReZXoHmd5PmN7rTO81pvc609tp8jK9fmy3GLP+rG884IsFDgT2AaZSHtOB2cBBwNF059I9GTiY7TwEOAeYBZxH91LgUOBvgZnAPwKHA4NsLr4o4DDzfnTz3DjuyUf+WG793DjIBMotzwEp5/3AaOAe9rN2UDnjP8r4vYG7GL+3DfcF9gHGAxOAZwITgWOBScDxwGTgDOAw4GypM1d/HAg0y5UKrAKmAeuAKcBmujcC04GbgYOAW5nOlcAhwD3ADOBD9Ge+uYcc36/85Ptt2tD9NTAe+A7wTBmbXPl+j7Z0UdfSHp8Azwb+DrgQ+EfgEuBRYCXwA5498gdgE90twD8BLwJ+CLyE6WwFfsTzHj8G3kd/5pt7rzFm+Mn3Ceb7c+b778z3P5jvL5hvm82V72jg2UDIiOQ7DLgEGA6sBEYA1wBDgU10twB7AC8CRgK3MJ2vAR3A+4FRrPdoVd/ct8x9z975ngS+WOBUYB/gNGAicCFwAHA6MBM4i/IzGzgVeA5wFnAOcA6wAFhk+rM8hSzPXOBKpncecB7wOHA+8DPgAuDfgcXA4TbwMd/7g7gnk3tVzXwXm/JPvcArwZcO3A4cDbwWOAl4HXAK8AagyX8T5fUWyumtwMuAtwG/AfwW8JvA24E3AncC7wbeAXwJeCfwx8B7gG8A7wf+AbiH+XwQ+AnwIaCZ2XZgBHAvsBfwEWA8cB8wEfgYcBjQEeSaJ0UBzwH2BK4E7kd4A/AJYCPwKeBm4NPANuB3gd8CHgDeBXwW+DTwB0CQ8QLwJ8CXgIeBLwPfBv4Q+A7wFeDvgD8C/hH4Y+A/gAeBBur2J8Bg4GvAUODrwBjgIaAT+AZwIPBnwEzgm8Bs4C+AOcBfAicCjwBnAX8NLAK+C9wAfA94IfA3wEuAvwVuA74PvAr4B+DtwD8CdwGPAu8FfgC8H/gn4B7gh8BHgMeAjwGPA58AfgJ8A/gp8DDwL8CPgCeATsjRZ8AU4F+Bo4B/A44Dfg6cAPw7cBLwH8A84BfAmUAjCP0VGAw8B2i2/2JgBNwVwB7A1cAbbdpzqCrwcyibz6ExfA6N5XNoPJ9DucDRdOfSPRk4gc+hiXwOTQXOo3spcBKfQ5P5HJrC59BUPofyzPvRzecv9wMhDT/P3xjw9QbGcR4cDxwEdHL+24fz3wSmtx/UxvQyWO446rnIUMTxZhXQCawBDgOutvGcVeA4YD1wLnAdcAGwGbiE4eXA84HnA1uAFwI3Aq9g+DeAFwIflvKgPwAvBb4HvBx4ArgVaM7xrgCmAhGP9cE9HcBkUI1XfRzmc/lNHon3c477v+CZWW8B+/I5ZqZn3iuP6b3D+k0GHmV6ixn/XD43ljN+Oc/cqgCmAVfQdvz5fO5t4nOvATgf2AhcClwPPI/hG4C1wM085/gS+m/lecdXAeuA19J/B7AeuJfub9P9FN0HgFU877ga+ArPUz7E8MN0v003+wH3NMh+CZ9+gLYWeUDZRB4m02b+PGAWsIRnjJ3D52ghn6OzgTOAc4CzgCCph3xgMXAKzzOeClwBnAZsAKLuZHwvBu5j+pyPce8A5NXPfOwKtvs2oJ3nAPcGXqm9fzYwfoSf98+rGP9qYDiwjfHyTV7Gm+yn/13Lc3WvAyYDr+cZbDcARwNvBOaabqZXDjrI9GYzvR7AYqZ3MeWtlfJ6CdPdAhzI84lzgJcBx9B9Ft0zyKfOw13D82t5X/19sKfGV9RFvoYu8rV1ka+9i3wHu8CXBzpGvvGsV/085BFs35FAkDEKCBL3OLqt++XVMZ1A7+XMRxv51vtpx5vZjrfwjL7bgCnAb/G+t/Nc753AxcA7gNXAO9kP7uI=
*/