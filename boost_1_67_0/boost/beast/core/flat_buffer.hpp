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

    using mutable_data_type = net::mutable_buffer;

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