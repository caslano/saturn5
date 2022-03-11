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

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
    /// Change the number of readable and writable bytes to zero.
    void
    reset() noexcept
    {
        clear();
    }
#elif ! BOOST_BEAST_DOXYGEN
    template<std::size_t I = 0>
    void
    reset() noexcept
    {
        static_assert(I != 0,
            BOOST_BEAST_DEPRECATION_STRING);
    }
#endif

    //--------------------------------------------------------------------------

    /// The ConstBufferSequence used to represent the readable bytes.
    using const_buffers_type = net::const_buffer;

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
    using mutable_data_type = net::mutable_buffer;
#endif

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