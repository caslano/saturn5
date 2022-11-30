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
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
*/