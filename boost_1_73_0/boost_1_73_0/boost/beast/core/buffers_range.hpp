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
ka71iV7vb/3xxGamtpzGAzXzhJUD7eFacrqKozC+bpXlW1yzho2AB3+mI+FKGdfy1x0rcfwwj+P5dj5ZytjwGrqjs88j8RM/BsPBOyDvB4fLFzyupagbipjUDoQ/8AV9V4uyg3z5rIeQzwQsgy1CNNOmBilazqKEYMowx/ZFqY6QM31CJcEMsks82luMZUCJJpsIX3DQ91P5dutbuz3KF6SSg1aOV6mSuNXOH5GVCz+54kqnERCXj9NzhDGtVTuhdJhcbebqK/ourYlrEIylG/OFyV8Y8dMW79zpakxereQntun++/5gYtd7g+FhXgDkk2AvjJmZl858x+DBHh5uNnb1swfO0B6o19W+IAsBgH8vtho0fuVJ40KdPoTQl0dbeqZOVTXaROzp0qx8tlRMRiftsw6tIpW/9MoyoB62zKJeDHt/653m52Cmb50vVchNYr7VtzoZD2mPszRV65Rc1/04HAwnw0H/1BGT87PcpeHf9LghUbZNoCrzRyR63kHcwxc66m9rsMltnN91ao/vGtUyZBlDygjC1GsA0qnFDzPOrgWPIpjtzowV6Lxv7UqC3qDpzAsymwOGGTKbFIChSYp/uYDMlG/XItLbu7mVWp1JXs1YzrbanGPLceu1vkfodbK+u1Ei3EpGOfao
*/