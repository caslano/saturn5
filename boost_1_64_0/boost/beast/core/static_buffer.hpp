//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STATIC_BUFFER_HPP
#define BOOST_BEAST_STATIC_BUFFER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/buffers_pair.hpp>
#include <boost/asio/buffer.hpp>
#include <cstddef>

namespace boost {
namespace beast {

/** A dynamic buffer providing a fixed size, circular buffer.

    A dynamic buffer encapsulates memory storage that may be
    automatically resized as required, where the memory is
    divided into two regions: readable bytes followed by
    writable bytes. These memory regions are internal to
    the dynamic buffer, but direct access to the elements
    is provided to permit them to be efficiently used with
    I/O operations.

    Objects of this type meet the requirements of <em>DynamicBuffer</em>
    and have the following additional properties:

    @li A mutable buffer sequence representing the readable
    bytes is returned by @ref data when `this` is non-const.

    @li Buffer sequences representing the readable and writable
    bytes, returned by @ref data and @ref prepare, may have
    length up to two.

    @li All operations execute in constant time.

    @li Ownership of the underlying storage belongs to the
    derived class.

    @note Variables are usually declared using the template class
    @ref static_buffer; however, to reduce the number of template
    instantiations, objects should be passed `static_buffer_base&`.

    @see static_buffer
*/
class static_buffer_base
{
    char* begin_;
    std::size_t in_off_ = 0;
    std::size_t in_size_ = 0;
    std::size_t out_size_ = 0;
    std::size_t capacity_;

    static_buffer_base(static_buffer_base const& other) = delete;
    static_buffer_base& operator=(static_buffer_base const&) = delete;

public:
    /** Constructor

        This creates a dynamic buffer using the provided storage area.

        @param p A pointer to valid storage of at least `n` bytes.

        @param size The number of valid bytes pointed to by `p`.
    */
    BOOST_BEAST_DECL
    static_buffer_base(void* p, std::size_t size) noexcept;

    /** Clear the readable and writable bytes to zero.

        This function causes the readable and writable bytes
        to become empty. The capacity is not changed.

        Buffer sequences previously obtained using @ref data or
        @ref prepare become invalid.

        @esafe

        No-throw guarantee.
    */
    BOOST_BEAST_DECL
    void
    clear() noexcept;

    //--------------------------------------------------------------------------

#if BOOST_BEAST_DOXYGEN
    /// The ConstBufferSequence used to represent the readable bytes.
    using const_buffers_type = __implementation_defined__;

    /// The MutableBufferSequence used to represent the writable bytes.
    using mutable_buffers_type = __implementation_defined__;
#else
    using const_buffers_type   = detail::buffers_pair<false>;

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
    using mutable_data_type    = detail::buffers_pair<true>;
#endif

    using mutable_buffers_type = detail::buffers_pair<true>;
#endif

    /// Returns the number of readable bytes.
    std::size_t
    size() const noexcept
    {
        return in_size_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can ever be held.
    std::size_t
    max_size() const noexcept
    {
        return capacity_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can be held without requiring an allocation.
    std::size_t
    capacity() const noexcept
    {
        return capacity_;
    }

    /// Returns a constant buffer sequence representing the readable bytes
    BOOST_BEAST_DECL
    const_buffers_type
    data() const noexcept;

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    cdata() const noexcept
    {
        return data();
    }

    /// Returns a mutable buffer sequence representing the readable bytes
    BOOST_BEAST_DECL
    mutable_buffers_type
    data() noexcept;

    /** Returns a mutable buffer sequence representing writable bytes.

        Returns a mutable buffer sequence representing the writable
        bytes containing exactly `n` bytes of storage. Memory may be
        reallocated as needed.

        All buffers sequences previously obtained using
        @ref data or @ref prepare are invalidated.

        @param n The desired number of bytes in the returned buffer
        sequence.

        @throws std::length_error if `size() + n` exceeds `max_size()`.

        @esafe

        Strong guarantee.
    */
    BOOST_BEAST_DECL
    mutable_buffers_type
    prepare(std::size_t n);

    /** Append writable bytes to the readable bytes.

        Appends n bytes from the start of the writable bytes to the
        end of the readable bytes. The remainder of the writable bytes
        are discarded. If n is greater than the number of writable
        bytes, all writable bytes are appended to the readable bytes.

        All buffers sequences previously obtained using
        @ref data or @ref prepare are invalidated.

        @param n The number of bytes to append. If this number
        is greater than the number of writable bytes, all
        writable bytes are appended.

        @esafe

        No-throw guarantee.
    */
    BOOST_BEAST_DECL
    void
    commit(std::size_t n) noexcept;

    /** Remove bytes from beginning of the readable bytes.

        Removes n bytes from the beginning of the readable bytes.

        All buffers sequences previously obtained using
        @ref data or @ref prepare are invalidated.

        @param n The number of bytes to remove. If this number
        is greater than the number of readable bytes, all
        readable bytes are removed.

        @esafe

        No-throw guarantee.
    */
    BOOST_BEAST_DECL
    void
    consume(std::size_t n) noexcept;
};

//------------------------------------------------------------------------------

/** A dynamic buffer providing a fixed size, circular buffer.

    A dynamic buffer encapsulates memory storage that may be
    automatically resized as required, where the memory is
    divided into two regions: readable bytes followed by
    writable bytes. These memory regions are internal to
    the dynamic buffer, but direct access to the elements
    is provided to permit them to be efficiently used with
    I/O operations.

    Objects of this type meet the requirements of <em>DynamicBuffer</em>
    and have the following additional properties:

    @li A mutable buffer sequence representing the readable
    bytes is returned by @ref data when `this` is non-const.

    @li Buffer sequences representing the readable and writable
    bytes, returned by @ref data and @ref prepare, may have
    length up to two.

    @li All operations execute in constant time.

    @tparam N The number of bytes in the internal buffer.

    @note To reduce the number of template instantiations when passing
    objects of this type in a deduced context, the signature of the
    receiving function should use @ref static_buffer_base instead.

    @see static_buffer_base
*/
template<std::size_t N>
class static_buffer : public static_buffer_base
{
    char buf_[N];

public:
    /// Constructor
    static_buffer() noexcept
        : static_buffer_base(buf_, N)
    {
    }

    /// Constructor
    static_buffer(static_buffer const&) noexcept;

    /// Assignment
    static_buffer& operator=(static_buffer const&) noexcept;

    /// Returns the @ref static_buffer_base portion of this object
    static_buffer_base&
    base() noexcept
    {
        return *this;
    }

    /// Returns the @ref static_buffer_base portion of this object
    static_buffer_base const&
    base() const noexcept
    {
        return *this;
    }

    /// Return the maximum sum of the input and output sequence sizes.
    std::size_t constexpr
    max_size() const noexcept
    {
        return N;
    }

    /// Return the maximum sum of input and output sizes that can be held without an allocation.
    std::size_t constexpr
    capacity() const noexcept
    {
        return N;
    }
};

} // beast
} // boost

#include <boost/beast/core/impl/static_buffer.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/static_buffer.ipp>
#endif

#endif

/* static_buffer.hpp
mR9fSl87TzvbDTInHXJTWuTZcedja+U3OzO/57cvVeJfuJNx/425b776wzcrzs++v2WjZ5ZPCBQ7NdyvGHRzs+Lony9/sXG/n9c6828Y2S6R9JGH5i2/0GbcgftmDX968f6nMFHLnSxzyTfmvtvk63feb7l+/tgPO8Y2QJ+U5+54eNvghf5+/x6U1uvxvD/2wi/z9zJXvfDe4eD19ywoHfrO31OzJ7Q7A7s+mYN/vjxqY6cjeRcWfLV1371bW+5EeqlP/sncxd9UtH/1zZU3NIs92/ul/96c+gdph8n7524NezviseH3npuU8+24h2uuQ6jp3NzkT1l4bRZwHgLPMuZYQ/qrxJnPMt7HOeVhoIP+iV35SivJV8Z8v2K+naZ8ZcwX4Z1P5uJ1eGb1NcCNpnwHK8mXy3z3MN88U74zldTzNtYzhfVMNZ/xXEm+65lvNPONMeXT9tnnS2e+LOabZsoXVkm+cubbzXzPAV02oVHMN4D5zDahC5AuAngvsAVtndtQFxIHXAzsTtvnrTq+L5wOf47QLMahJSGUIOxGOIOQgvvbEczz9fMIYZirRyH0QEhEyEEoQViNUI5w0GNOH815/SyEJQjbEfYiHEM4w/l+gy5IhzAWIR2hCOEYdQDN4mCTiNAPYSJCDoJZL/AWwucIFxBCu6IchLEI8xCWIxxBeAvhY4TzCP7d8DwElx6hCGERQhlCOcIRhLcQtO5Ih9AWoR/CPJO+4STCGYTzCMGGDSVCP4QchFIPXURYT7QXQhxCCkI+QglCKcLH0FGEpgZpPRDGIcxD2IpwAuECQtQUnw7Dd/1/Xldh/p8+JfPyzP8fhhCNd+3RtJhb31EfunC3OYTxeGy1yzGf+WGYJFw8cyP/R86pOe5HWRfHdQkOu/GJ3fjBbtxiP654u5Zx/2ho/ReSe/R4eUBATJ87W9zY1G4caDdutB8fbpTxYa+ZD/9y/vhPbzvw2IFpI5cub2Q3jrIbp1358eQ9fsb9R257xb/O4n892Xr3262jtwwfYDeerPl4z258fsJh3L8+KuPvd0/MjPGbmRky7y8Zb2K/lNz//YNnXx2Ukf3wgq/nTNnVekeA3XjedjzM8SH5kvx90GNcMpPjklkcl7wA3K1rVY4hjpjGEUUcS5y+yuOJctOY4sIljCvSTWOLJyoZX7T9EWOMFI4zlldjrDHSZrzxrceYI8Fi3DHYN67wXb7Ld/ku3+W7fJfv8l1X+boK8/+0nIJLn/9HaqHXfIa51JlMYy6EYuHDKnlqseFAR3QDm026gU3UDURxLbcJws2YwyY4dQM3J91405gxI5PTUOG8wgzbNW2mj7K0Sx2h4ptc0jq1sp+kze8kzvvwriabx5rbNr4q8/ioC/NTBn8dEdNk2jNNirt+0e3Kr7dYz7Nrvn5S2fy4t8a25zeOIx+jKdT5jHXoi6EJbfOak84Bpk8J8rJ/K5kSVG0buOrav632ze98l+/yXb7Ld/ku3+W7fJfv8l3/Q5c/wpQrOv+/9Ll/Cy1U1u73ytzfsC29KzmtuLBoRq7Y3IpuYCgm4Acl3mVIm5ufw7hExB2TuIIMc2QE4oYh7qTEGQbuEqGe1/a0cT8NWZS1c8aU4kzRN6w3nUOYTiOEeQjNibc0gP3Ybrf9tmifAprRm3UOhU59AG1V35Y8IzCnrUM9hKuca0nrWsyzBq1b2teOUOnjtAjurz0j9Ei8V0PYqNXztLNVPgnelHRjML8OlrKSVFltSKtne9nihvNcgJOSfgL2nflJnmxVRhRpVYacN9IP8ZscTnt/vzi48q/V2K9xYGRoLT+nPa7LPjco3PheY+R7tUrGjUD1vdR+2T/Lc3pWa4/rRX0=
*/