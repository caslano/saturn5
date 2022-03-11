//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_MULTI_BUFFER_HPP
#define BOOST_BEAST_MULTI_BUFFER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/allocator.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/type_traits/type_with_alignment.hpp>
#include <iterator>
#include <limits>
#include <memory>
#include <type_traits>

namespace boost {
namespace beast {

/** A dynamic buffer providing sequences of variable length.

    A dynamic buffer encapsulates memory storage that may be
    automatically resized as required, where the memory is
    divided into two regions: readable bytes followed by
    writable bytes. These memory regions are internal to
    the dynamic buffer, but direct access to the elements
    is provided to permit them to be efficiently used with
    I/O operations.

    The implementation uses a sequence of one or more byte
    arrays of varying sizes to represent the readable and
    writable bytes. Additional byte array objects are
    appended to the sequence to accommodate changes in the
    desired size. The behavior and implementation of this
    container is most similar to `std::deque`.

    Objects of this type meet the requirements of <em>DynamicBuffer</em>
    and have the following additional properties:

    @li A mutable buffer sequence representing the readable
    bytes is returned by @ref data when `this` is non-const.

    @li Buffer sequences representing the readable and writable
    bytes, returned by @ref data and @ref prepare, may have
    length greater than one.

    @li A configurable maximum size may be set upon construction
    and adjusted afterwards. Calls to @ref prepare that would
    exceed this size will throw `std::length_error`.

    @li Sequences previously obtained using @ref data remain
    valid after calls to @ref prepare or @ref commit.

    @tparam Allocator The allocator to use for managing memory.
*/
template<class Allocator>
class basic_multi_buffer
#if ! BOOST_BEAST_DOXYGEN
    : private boost::empty_value<Allocator>
#endif
{
    // Fancy pointers are not supported
    static_assert(std::is_pointer<typename
        std::allocator_traits<Allocator>::pointer>::value,
        "Allocator must use regular pointers");

    static bool constexpr default_nothrow =
        std::is_nothrow_default_constructible<Allocator>::value;

    // Storage for the list of buffers representing the input
    // and output sequences. The allocation for each element
    // contains `element` followed by raw storage bytes.
    class element
        : public boost::intrusive::list_base_hook<
            boost::intrusive::link_mode<
                boost::intrusive::normal_link>>
    {
        using size_type = typename
            detail::allocator_traits<Allocator>::size_type;

        size_type const size_;

    public:
        element(element const&) = delete;

        explicit
        element(size_type n) noexcept
            : size_(n)
        {
        }

        size_type
        size() const noexcept
        {
            return size_;
        }

        char*
        data() const noexcept
        {
            return const_cast<char*>(
                reinterpret_cast<char const*>(this + 1));
        }
    };

    template<bool>
    class subrange;

    using size_type = typename
        detail::allocator_traits<Allocator>::size_type;

    using align_type = typename
        boost::type_with_alignment<alignof(element)>::type;

    using rebind_type = typename
        beast::detail::allocator_traits<Allocator>::
            template rebind_alloc<align_type>;

    using alloc_traits =
        beast::detail::allocator_traits<rebind_type>;

    using list_type = typename boost::intrusive::make_list<
        element, boost::intrusive::constant_time_size<true>>::type;

    using iter = typename list_type::iterator;

    using const_iter = typename list_type::const_iterator;

    using pocma = typename
        alloc_traits::propagate_on_container_move_assignment;

    using pocca = typename
        alloc_traits::propagate_on_container_copy_assignment;

    static_assert(std::is_base_of<std::bidirectional_iterator_tag,
        typename std::iterator_traits<iter>::iterator_category>::value,
            "BidirectionalIterator type requirements not met");

    static_assert(std::is_base_of<std::bidirectional_iterator_tag,
        typename std::iterator_traits<const_iter>::iterator_category>::value,
            "BidirectionalIterator type requirements not met");

    std::size_t max_;
    list_type list_;        // list of allocated buffers
    iter out_;              // element that contains out_pos_
    size_type in_size_ = 0; // size of the input sequence
    size_type in_pos_ = 0;  // input offset in list_.front()
    size_type out_pos_ = 0; // output offset in *out_
    size_type out_end_ = 0; // output end offset in list_.back()

public:
#if BOOST_BEAST_DOXYGEN
    /// The ConstBufferSequence used to represent the readable bytes.
    using const_buffers_type = __implementation_defined__;

    /// The MutableBufferSequence used to represent the writable bytes.
    using mutable_buffers_type = __implementation_defined__;
#else
    using const_buffers_type = subrange<false>;

    using mutable_buffers_type = subrange<true>;

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
    using mutable_data_type = subrange<true>;
#endif

#endif

    /// The type of allocator used.
    using allocator_type = Allocator;

    /// Destructor
    ~basic_multi_buffer();

    /** Constructor

        After construction, @ref capacity will return zero, and
        @ref max_size will return the largest value which may
        be passed to the allocator's `allocate` function.
    */
    basic_multi_buffer() noexcept(default_nothrow);

    /** Constructor

        After construction, @ref capacity will return zero, and
        @ref max_size will return the specified value of `limit`.

        @param limit The desired maximum size.
    */
    explicit
    basic_multi_buffer(
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
    basic_multi_buffer(Allocator const& alloc) noexcept;

    /** Constructor

        After construction, @ref capacity will return zero, and
        @ref max_size will return the specified value of `limit`.

        @param limit The desired maximum size.

        @param alloc The allocator to use for the object.

        @esafe

        No-throw guarantee.
    */
    basic_multi_buffer(
        std::size_t limit, Allocator const& alloc) noexcept;

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
    basic_multi_buffer(basic_multi_buffer&& other) noexcept;

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
    basic_multi_buffer(
        basic_multi_buffer&& other,
        Allocator const& alloc);

    /** Copy Constructor

        This container is constructed with the contents of `other`
        using copy semantics. The maximum size will be the same
        as the copied object.

        @param other The object to copy from.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of the allocator.
    */
    basic_multi_buffer(basic_multi_buffer const& other);

    /** Copy Constructor

        This container is constructed with the contents of `other`
        using copy semantics and the specified allocator. The maximum
        size will be the same as the copied object.

        @param other The object to copy from.

        @param alloc The allocator to use for the object.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of `alloc`.
    */
    basic_multi_buffer(basic_multi_buffer const& other,
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
    basic_multi_buffer(basic_multi_buffer<
        OtherAlloc> const& other);

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
    basic_multi_buffer(
        basic_multi_buffer<OtherAlloc> const& other,
        allocator_type const& alloc);

    /** Move Assignment

        The container is assigned with the contents of `other`
        using move semantics. The maximum size will be the same
        as the moved-from object.

        Buffer sequences previously obtained from `other` using
        @ref data or @ref prepare remain valid after the move.

        @param other The object to move from. After the move,
        the moved-from object will have zero capacity, zero readable
        bytes, and zero writable bytes.
    */
    basic_multi_buffer&
    operator=(basic_multi_buffer&& other);

    /** Copy Assignment

        The container is assigned with the contents of `other`
        using copy semantics. The maximum size will be the same
        as the copied object.

        After the copy, `this` will have zero writable bytes.

        @param other The object to copy from.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of the allocator.
    */
    basic_multi_buffer& operator=(
        basic_multi_buffer const& other);

    /** Copy Assignment

        The container is assigned with the contents of `other`
        using copy semantics. The maximum size will be the same
        as the copied object.

        After the copy, `this` will have zero writable bytes.

        @param other The object to copy from.

        @throws std::length_error if `other.size()` exceeds the
        maximum allocation size of the allocator.
    */
    template<class OtherAlloc>
    basic_multi_buffer& operator=(
        basic_multi_buffer<OtherAlloc> const& other);

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

        Buffer sequences previously obtained using @ref data remain
        valid, while buffer sequences previously obtained using
        @ref prepare become invalid.

        @param n The minimum number of byte for the new capacity.
        If this value is greater than the maximum size, then the
        maximum size will be adjusted upwards to this value.

        @throws std::length_error if n is larger than the maximum
        allocation size of the allocator.

        @esafe

        Strong guarantee.
    */
    void
    reserve(std::size_t n);

    /** Reallocate the buffer to fit the readable bytes exactly.

        Buffer sequences previously obtained using @ref data or
        @ref prepare become invalid.

        @esafe

        Strong guarantee.
    */
    void
    shrink_to_fit();

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
        basic_multi_buffer<Alloc>& lhs,
        basic_multi_buffer<Alloc>& rhs) noexcept;

    //--------------------------------------------------------------------------

    /// Returns the number of readable bytes.
    size_type
    size() const noexcept
    {
        return in_size_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can ever be held.
    size_type
    max_size() const noexcept
    {
        return max_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can be held without requiring an allocation.
    std::size_t
    capacity() const noexcept;

    /** Returns a constant buffer sequence representing the readable bytes

        @note The sequence may contain multiple contiguous memory regions.
    */
    const_buffers_type
    data() const noexcept;

    /** Returns a constant buffer sequence representing the readable bytes

        @note The sequence may contain multiple contiguous memory regions.
    */
    const_buffers_type
    cdata() const noexcept
    {
        return data();
    }

    /** Returns a mutable buffer sequence representing the readable bytes.

        @note The sequence may contain multiple contiguous memory regions.
    */
    mutable_buffers_type
    data() noexcept;

    /** Returns a mutable buffer sequence representing writable bytes.
    
        Returns a mutable buffer sequence representing the writable
        bytes containing exactly `n` bytes of storage. Memory may be
        reallocated as needed.

        All buffer sequences previously obtained using @ref prepare are
        invalidated. Buffer sequences previously obtained using @ref data
        remain valid.

        @param n The desired number of bytes in the returned buffer
        sequence.

        @throws std::length_error if `size() + n` exceeds `max_size()`.

        @esafe

        Strong guarantee.
    */
    mutable_buffers_type
    prepare(size_type n);

    /** Append writable bytes to the readable bytes.

        Appends n bytes from the start of the writable bytes to the
        end of the readable bytes. The remainder of the writable bytes
        are discarded. If n is greater than the number of writable
        bytes, all writable bytes are appended to the readable bytes.

        All buffer sequences previously obtained using @ref prepare are
        invalidated. Buffer sequences previously obtained using @ref data
        remain valid.

        @param n The number of bytes to append. If this number
        is greater than the number of writable bytes, all
        writable bytes are appended.

        @esafe

        No-throw guarantee.
    */
    void
    commit(size_type n) noexcept;

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
    void
    consume(size_type n) noexcept;

private:
    template<class OtherAlloc>
    friend class basic_multi_buffer;

    template<class OtherAlloc>
    void copy_from(basic_multi_buffer<OtherAlloc> const&);
    void move_assign(basic_multi_buffer& other, std::false_type);
    void move_assign(basic_multi_buffer& other, std::true_type) noexcept;
    void copy_assign(basic_multi_buffer const& other, std::false_type);
    void copy_assign(basic_multi_buffer const& other, std::true_type);
    void swap(basic_multi_buffer&) noexcept;
    void swap(basic_multi_buffer&, std::true_type) noexcept;
    void swap(basic_multi_buffer&, std::false_type) noexcept;
    void destroy(list_type& list) noexcept;
    void destroy(const_iter it);
    void destroy(element& e);
    element& alloc(std::size_t size);
    void debug_check() const;
};

/// A typical multi buffer
using multi_buffer = basic_multi_buffer<std::allocator<char>>;

} // beast
} // boost

#include <boost/beast/core/impl/multi_buffer.hpp>

#endif
/* multi_buffer.hpp
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
*/