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