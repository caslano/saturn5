//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_FLAT_STATIC_BUFFER_HPP
#define BOOST_BEAST_FLAT_STATIC_BUFFER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/asio/buffer.hpp>
#include <algorithm>
#include <cstddef>
#include <cstring>

namespace boost {
namespace beast {

/** A dynamic buffer using a fixed size internal buffer.

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
    bytes, returned by @ref data and @ref prepare, will have
    length one.

    @li Ownership of the underlying storage belongs to the
    derived class.

    @note Variables are usually declared using the template class
    @ref flat_static_buffer; however, to reduce the number of template
    instantiations, objects should be passed `flat_static_buffer_base&`.

    @see flat_static_buffer
*/
class flat_static_buffer_base
{
    char* begin_;
    char* in_;
    char* out_;
    char* last_;
    char* end_;

    flat_static_buffer_base(
        flat_static_buffer_base const& other) = delete;
    flat_static_buffer_base& operator=(
        flat_static_buffer_base const&) = delete;

public:
    /** Constructor

        This creates a dynamic buffer using the provided storage area.

        @param p A pointer to valid storage of at least `n` bytes.

        @param n The number of valid bytes pointed to by `p`.
    */
    flat_static_buffer_base(
        void* p, std::size_t n) noexcept
    {
        reset(p, n);
    }

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

    /// The ConstBufferSequence used to represent the readable bytes.
    using const_buffers_type = net::const_buffer;

    /// The MutableBufferSequence used to represent the writable bytes.
    using mutable_buffers_type = net::mutable_buffer;

    /// Returns the number of readable bytes.
    std::size_t
    size() const noexcept
    {
        return out_ - in_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can ever be held.
    std::size_t
    max_size() const noexcept
    {
        return dist(begin_, end_);
    }

    /// Return the maximum number of bytes, both readable and writable, that can be held without requiring an allocation.
    std::size_t
    capacity() const noexcept
    {
        return max_size();
    }

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    data() const noexcept
    {
        return {in_, dist(in_, out_)};
    }

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    cdata() const noexcept
    {
        return data();
    }

    /// Returns a mutable buffer sequence representing the readable bytes
    mutable_buffers_type
    data() noexcept
    {
        return {in_, dist(in_, out_)};
    }

    /** Returns a mutable buffer sequence representing writable bytes.
    
        Returns a mutable buffer sequence representing the writable
        bytes containing exactly `n` bytes of storage.

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
    void
    commit(std::size_t n) noexcept
    {
        out_ += (std::min<std::size_t>)(n, last_ - out_);
    }

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

protected:
    /** Constructor

        The buffer will be in an undefined state. It is necessary
        for the derived class to call @ref reset with a pointer
        and size in order to initialize the object.
    */
    flat_static_buffer_base() = default;

    /** Reset the pointed-to buffer.

        This function resets the internal state to the buffer provided.
        All input and output sequences are invalidated. This function
        allows the derived class to construct its members before
        initializing the static buffer.

        @param p A pointer to valid storage of at least `n` bytes.

        @param n The number of valid bytes pointed to by `p`.

        @esafe

        No-throw guarantee.
    */
    BOOST_BEAST_DECL
    void
    reset(void* p, std::size_t n) noexcept;

private:
    static
    std::size_t
    dist(char const* first, char const* last) noexcept
    {
        return static_cast<std::size_t>(last - first);
    }
};

//------------------------------------------------------------------------------

/** A <em>DynamicBuffer</em> with a fixed size internal buffer.

    Buffer sequences returned by @ref data and @ref prepare
    will always be of length one.
    This implements a dynamic buffer using no memory allocations.

    @tparam N The number of bytes in the internal buffer.

    @note To reduce the number of template instantiations when passing
    objects of this type in a deduced context, the signature of the
    receiving function should use @ref flat_static_buffer_base instead.

    @see flat_static_buffer_base
*/
template<std::size_t N>
class flat_static_buffer : public flat_static_buffer_base
{
    char buf_[N];

public:
    /// Constructor
    flat_static_buffer(flat_static_buffer const&);

    /// Constructor
    flat_static_buffer()
        : flat_static_buffer_base(buf_, N)
    {
    }

    /// Assignment
    flat_static_buffer& operator=(flat_static_buffer const&);

    /// Returns the @ref flat_static_buffer_base portion of this object
    flat_static_buffer_base&
    base()
    {
        return *this;
    }

    /// Returns the @ref flat_static_buffer_base portion of this object
    flat_static_buffer_base const&
    base() const
    {
        return *this;
    }

    /// Return the maximum sum of the input and output sequence sizes.
    std::size_t constexpr
    max_size() const
    {
        return N;
    }

    /// Return the maximum sum of input and output sizes that can be held without an allocation.
    std::size_t constexpr
    capacity() const
    {
        return N;
    }
};

} // beast
} // boost

#include <boost/beast/core/impl/flat_static_buffer.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/flat_static_buffer.ipp>
#endif

#endif
/* flat_static_buffer.hpp
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
*/