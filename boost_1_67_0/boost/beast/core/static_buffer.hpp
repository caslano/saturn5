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
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
*/