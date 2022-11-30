//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_FLAT_BUFFER_HPP
#define BOOST_BEAST_FLAT_BUFFER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/allocator.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/core/empty_value.hpp>
#include <limits>
#include <memory>
#include <type_traits>

namespace boost {
namespace beast {

/** A dynamic buffer providing buffer sequences of length one.

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

    @li A configurable maximum buffer size may be set upon
    construction. Attempts to exceed the buffer size will throw
    `std::length_error`.

    @li Buffer sequences representing the readable and writable
    bytes, returned by @ref data and @ref prepare, will have
    length one.

    Upon construction, a maximum size for the buffer may be
    specified. If this limit is exceeded, the `std::length_error`
    exception will be thrown.

    @note This class is designed for use with algorithms that
    take dynamic buffers as parameters, and are optimized
    for the case where the input sequence or output sequence
    is stored in a single contiguous buffer.
*/
template<class Allocator>
class basic_flat_buffer
#if ! BOOST_BEAST_DOXYGEN
    : private boost::empty_value<
        typename detail::allocator_traits<Allocator>::
            template rebind_alloc<char>>
#endif
{
    template<class OtherAlloc>
    friend class basic_flat_buffer;

    using base_alloc_type = typename
        detail::allocator_traits<Allocator>::
            template rebind_alloc<char>;

    static bool constexpr default_nothrow =
        std::is_nothrow_default_constructible<Allocator>::value;

    using alloc_traits =
        beast::detail::allocator_traits<base_alloc_type>;

    using pocma = typename
        alloc_traits::propagate_on_container_move_assignment;

    using pocca = typename
        alloc_traits::propagate_on_container_copy_assignment;

    static
    std::size_t
    dist(char const* first, char const* last) noexcept
    {
        return static_cast<std::size_t>(last - first);
    }

    char* begin_;
    char* in_;
    char* out_;
    char* last_;
    char* end_;
    std::size_t max_;

public:
    /// The type of allocator used.
    using allocator_type = Allocator;

    /// Destructor
    ~basic_flat_buffer();

    /** Constructor

        After construction, @ref capacity will return zero, and
        @ref max_size will return the largest value which may
        be passed to the allocator's `allocate` function.
    */
    basic_flat_buffer() noexcept(default_nothrow);

    /** Constructor

        After construction, @ref capacity will return zero, and
        @ref max_size will return the specified value of `limit`.

        @param limit The desired maximum size.
    */
    explicit
    basic_flat_buffer(
        std::size_t limit) noexcept(default_nothrow);

    /** Constructor

        After construction, @ref capacity will return zero, and
        @ref max_size will return the largest value which may
        be passed to the allocator's `allocate` function.

        @param alloc The allocator to use for the object.

        @esafe

        No-throw guarantee.
    */
    explicit
    basic_flat_buffer(Allocator const& alloc) noexcept;

    /** Constructor

        After construction, @ref capacity will return zero, and
        @ref max_size will return the specified value of `limit`.

        @param limit The desired maximum size.

        @param alloc The allocator to use for the object.

        @esafe

        No-throw guarantee.
    */
    basic_flat_buffer(
        std::size_t limit,
        Allocator const& alloc) noexcept;

    /** Move Constructor

        The container is constructed with the contents of `other`
        using move semantics. The maximum size will be the same
        as the moved-from object.

        Buffer sequences previously obtained from `other` using
        @ref data or @ref prepare remain valid after the move.

        @param other The object to move from. After the move, the
        moved-from object will have zero capacity, zero readable
        bytes, and zero writable bytes.

        @esafe

        No-throw guarantee.
    */
    basic_flat_buffer(basic_flat_buffer&& other) noexcept;

    /** Move Constructor

        Using `alloc` as the allocator for the new container, the
        contents of `other` are moved. If `alloc != other.get_allocator()`,
        this results in a copy. The maximum size will be the same
        as the moved-from object.

        Buffer sequences previously obtained from `other` using
        @ref data or @ref prepare become invalid after the move.

        @param other The object to move from. After the move,
        the moved-from object will have zero capacity, zero readable
        bytes, and zero writable bytes.

        @param alloc The allocator to use for the object.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of `alloc`.
    */
    basic_flat_buffer(
        basic_flat_buffer&& other,
        Allocator const& alloc);

    /** Copy Constructor

        This container is constructed with the contents of `other`
        using copy semantics. The maximum size will be the same
        as the copied object.

        @param other The object to copy from.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of the allocator.
    */
    basic_flat_buffer(basic_flat_buffer const& other);

    /** Copy Constructor

        This container is constructed with the contents of `other`
        using copy semantics and the specified allocator. The maximum
        size will be the same as the copied object.

        @param other The object to copy from.

        @param alloc The allocator to use for the object.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of `alloc`.
    */
    basic_flat_buffer(
        basic_flat_buffer const& other,
        Allocator const& alloc);

    /** Copy Constructor

        This container is constructed with the contents of `other`
        using copy semantics. The maximum size will be the same
        as the copied object.

        @param other The object to copy from.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of the allocator.
    */
    template<class OtherAlloc>
    basic_flat_buffer(
        basic_flat_buffer<OtherAlloc> const& other)
            noexcept(default_nothrow);

    /** Copy Constructor

        This container is constructed with the contents of `other`
        using copy semantics. The maximum size will be the same
        as the copied object.

        @param other The object to copy from.

        @param alloc The allocator to use for the object.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of `alloc`.
    */
    template<class OtherAlloc>
    basic_flat_buffer(
        basic_flat_buffer<OtherAlloc> const& other,
        Allocator const& alloc);

    /** Move Assignment

        The container is assigned with the contents of `other`
        using move semantics. The maximum size will be the same
        as the moved-from object.

        Buffer sequences previously obtained from `other` using
        @ref data or @ref prepare remain valid after the move.

        @param other The object to move from. After the move,
        the moved-from object will have zero capacity, zero readable
        bytes, and zero writable bytes.

        @esafe

        No-throw guarantee.
    */
    basic_flat_buffer&
    operator=(basic_flat_buffer&& other) noexcept;

    /** Copy Assignment

        The container is assigned with the contents of `other`
        using copy semantics. The maximum size will be the same
        as the copied object.

        After the copy, `this` will have zero writable bytes.

        @param other The object to copy from.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of the allocator.
    */
    basic_flat_buffer&
    operator=(basic_flat_buffer const& other);

    /** Copy assignment

        The container is assigned with the contents of `other`
        using copy semantics. The maximum size will be the same
        as the copied object.

        After the copy, `this` will have zero writable bytes.

        @param other The object to copy from.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of the allocator.
    */
    template<class OtherAlloc>
    basic_flat_buffer&
    operator=(basic_flat_buffer<OtherAlloc> const& other);

    /// Returns a copy of the allocator used.
    allocator_type
    get_allocator() const
    {
        return this->get();
    }

    /** Set the maximum allowed capacity

        This function changes the currently configured upper limit
        on capacity to the specified value.

        @param n The maximum number of bytes ever allowed for capacity.

        @esafe

        No-throw guarantee.
    */
    void
    max_size(std::size_t n) noexcept
    {
        max_ = n;
    }

    /** Guarantee a minimum capacity

        This function adjusts the internal storage (if necessary)
        to guarantee space for at least `n` bytes.

        Buffer sequences previously obtained using @ref data or
        @ref prepare become invalid.

        @param n The minimum number of byte for the new capacity.
        If this value is greater than the maximum size, then the
        maximum size will be adjusted upwards to this value.

        @esafe

        Basic guarantee.

        @throws std::length_error if n is larger than the maximum
        allocation size of the allocator.
    */
    void
    reserve(std::size_t n);

    /** Request the removal of unused capacity.

        This function attempts to reduce @ref capacity()
        to @ref size(), which may not succeed.

        @esafe

        No-throw guarantee.
    */
    void
    shrink_to_fit() noexcept;

    /** Set the size of the readable and writable bytes to zero.

        This clears the buffer without changing capacity.
        Buffer sequences previously obtained using @ref data or
        @ref prepare become invalid.

        @esafe

        No-throw guarantee.
    */
    void
    clear() noexcept;

    /// Exchange two dynamic buffers
    template<class Alloc>
    friend
    void
    swap(
        basic_flat_buffer<Alloc>&,
        basic_flat_buffer<Alloc>&);

    //--------------------------------------------------------------------------

    /// The ConstBufferSequence used to represent the readable bytes.
    using const_buffers_type = net::const_buffer;

    /// The MutableBufferSequence used to represent the writable bytes.
    using mutable_buffers_type = net::mutable_buffer;

    /// Returns the number of readable bytes.
    std::size_t
    size() const noexcept
    {
        return dist(in_, out_);
    }

    /// Return the maximum number of bytes, both readable and writable, that can ever be held.
    std::size_t
    max_size() const noexcept
    {
        return max_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can be held without requiring an allocation.
    std::size_t
    capacity() const noexcept
    {
        return dist(begin_, end_);
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
        bytes containing exactly `n` bytes of storage. Memory may be
        reallocated as needed.

        All buffers sequences previously obtained using
        @ref data or @ref prepare become invalid.

        @param n The desired number of bytes in the returned buffer
        sequence.

        @throws std::length_error if `size() + n` exceeds either
        `max_size()` or the allocator's maximum allocation size.

        @esafe

        Strong guarantee.
    */
    mutable_buffers_type
    prepare(std::size_t n);

    /** Append writable bytes to the readable bytes.

        Appends n bytes from the start of the writable bytes to the
        end of the readable bytes. The remainder of the writable bytes
        are discarded. If n is greater than the number of writable
        bytes, all writable bytes are appended to the readable bytes.

        All buffers sequences previously obtained using
        @ref data or @ref prepare become invalid.

        @param n The number of bytes to append. If this number
        is greater than the number of writable bytes, all
        writable bytes are appended.

        @esafe

        No-throw guarantee.
    */
    void
    commit(std::size_t n) noexcept
    {
        out_ += (std::min)(n, dist(out_, last_));
    }

    /** Remove bytes from beginning of the readable bytes.

        Removes n bytes from the beginning of the readable bytes.

        All buffers sequences previously obtained using
        @ref data or @ref prepare become invalid.

        @param n The number of bytes to remove. If this number
        is greater than the number of readable bytes, all
        readable bytes are removed.

        @esafe

        No-throw guarantee.
    */
    void
    consume(std::size_t n) noexcept;

private:
    template<class OtherAlloc>
    void copy_from(basic_flat_buffer<OtherAlloc> const& other);
    void move_assign(basic_flat_buffer&, std::true_type);
    void move_assign(basic_flat_buffer&, std::false_type);
    void copy_assign(basic_flat_buffer const&, std::true_type);
    void copy_assign(basic_flat_buffer const&, std::false_type);
    void swap(basic_flat_buffer&);
    void swap(basic_flat_buffer&, std::true_type);
    void swap(basic_flat_buffer&, std::false_type);
    char* alloc(std::size_t n);
};

/// A flat buffer which uses the default allocator.
using flat_buffer =
    basic_flat_buffer<std::allocator<char>>;

} // beast
} // boost

#include <boost/beast/core/impl/flat_buffer.hpp>

#endif

/* flat_buffer.hpp
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
*/