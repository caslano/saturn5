//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_OBJECT_HPP
#define BOOST_JSON_OBJECT_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/kind.hpp>
#include <boost/json/pilfer.hpp>
#include <boost/json/storage_ptr.hpp>
#include <boost/json/string_view.hpp>
#include <boost/json/detail/object.hpp>
#include <boost/json/detail/value.hpp>
#include <cstdlib>
#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <utility>

BOOST_JSON_NS_BEGIN

class value;
class value_ref;
class key_value_pair;

/** A dynamically sized associative container of JSON key/value pairs.

    This is an associative container whose elements
    are key/value pairs with unique keys.
\n
    The elements are stored contiguously; iterators are
    ordinary pointers, allowing random access pointer
    arithmetic for retrieving elements.
    In addition, the container maintains an internal
    index to speed up find operations, reducing the
    average complexity for most lookups and insertions.
\n
    Reallocations are usually costly operations in terms of
    performance, as elements are copied and the internal
    index must be rebuilt. The @ref reserve function can
    be used to eliminate reallocations if the number of
    elements is known beforehand.

    @par Allocators

    All elements stored in the container, and their
    children if any, will use the same memory resource that
    was used to construct the container.

    @par Thread Safety

    Non-const member functions may not be called
    concurrently with any other member functions.

    @par Satisfies
        <a href="https://en.cppreference.com/w/cpp/named_req/ContiguousContainer"><em>ContiguousContainer</em></a>,
        <a href="https://en.cppreference.com/w/cpp/named_req/ReversibleContainer"><em>ReversibleContainer</em></a>, and
        <a href="https://en.cppreference.com/w/cpp/named_req/SequenceContainer"><em>SequenceContainer</em></a>.
*/
class object
{
    struct table;
    class revert_construct;
    class revert_insert;
    friend class value;
    friend class object_test;
    using access = detail::access;
    using index_t = std::uint32_t;
    static index_t constexpr null_index_ =
        std::uint32_t(-1);

    storage_ptr sp_;            // must come first
    kind k_ = kind::object;     // must come second
    table* t_;

    BOOST_JSON_DECL
    static table empty_;

    template<class T>
    using is_inputit = typename std::enable_if<
        std::is_constructible<key_value_pair,
        typename std::iterator_traits<T>::value_type
            >::value>::type;

    BOOST_JSON_DECL
    explicit
    object(detail::unchecked_object&& uo);

public:
    /** The type of _Allocator_ returned by @ref get_allocator

        This type is a @ref polymorphic_allocator.
    */
#ifdef BOOST_JSON_DOCS
    // VFALCO doc toolchain renders this incorrectly
    using allocator_type = __see_below__;
#else
    using allocator_type = polymorphic_allocator<value>;
#endif

    /** The type of keys.

        The function @ref string::max_size returns the
        maximum allowed size of strings used as keys.
    */
    using key_type = string_view;

    /// The type of mapped values
    using mapped_type = value;

    /// The element type
    using value_type = key_value_pair;

    /// The type used to represent unsigned integers
    using size_type = std::size_t;

    /// The type used to represent signed integers
    using difference_type = std::ptrdiff_t;

    /// A reference to an element
    using reference = value_type&;

    /// A const reference to an element
    using const_reference = value_type const&;

    /// A pointer to an element
    using pointer = value_type*;

    /// A const pointer to an element
    using const_pointer = value_type const*;

    /// A random access iterator to an element
    using iterator = value_type*;

    /// A const random access iterator to an element
    using const_iterator = value_type const*;

    /// A reverse random access iterator to an element
    using reverse_iterator =
        std::reverse_iterator<iterator>;

    /// A const reverse random access iterator to an element
    using const_reverse_iterator =
        std::reverse_iterator<const_iterator>;

    //------------------------------------------------------

    /** Destructor.

        The destructor for each element is called if needed,
        any used memory is deallocated, and shared ownership
        of the @ref memory_resource is released.

        @par Complexity
        Constant, or linear in @ref size().

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    ~object() noexcept;

    //------------------------------------------------------

    /** Default constructor.

        The constructed object is empty with zero
        capacity, using the default memory resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    object() noexcept
        : t_(&empty_)
    {
    }

    /** Constructor.

        The constructed object is empty with zero
        capacity, using the specified memory resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    explicit
    object(storage_ptr sp) noexcept
        : sp_(std::move(sp))
        , t_(&empty_)
    {
    }

    /** Constructor.

        The constructed object is empty with capacity
        equal to the specified minimum capacity,
        using the specified memory resource.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param min_capacity The minimum number
        of elements for which capacity is guaranteed
        without a subsequent reallocation.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    BOOST_JSON_DECL
    object(
        std::size_t min_capacity,
        storage_ptr sp = {});

    /** Constructor.

        The object is constructed with the elements
        in the range `{first, last)`, preserving order,
        using the specified memory resource.
        If there are elements with duplicate keys; that
        is, if multiple elements in the range have keys
        that compare equal, only the first equivalent
        element will be inserted.

        @par Constraints
        @code
        std::is_constructible_v<
            key_value_pair,
            std::iterator_traits<InputIt>::value_type>
        @endcode

        @par Complexity
        Linear in `std::distance(first, last)`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param first An input iterator pointing to the
        first element to insert, or pointing to the end
        of the range.

        @param last An input iterator pointing to the end
        of the range.

        @param min_capacity The minimum number
        of elements for which capacity is guaranteed
        without a subsequent reallocation.
        Upon construction, @ref capacity() will be greater
        than or equal to this number.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.

        @tparam InputIt a type satisfying the requirements
        of __InputIterator__.
    */
    template<
        class InputIt
    #ifndef BOOST_JSON_DOCS
        ,class = is_inputit<InputIt>
    #endif
    >
    object(
        InputIt first,
        InputIt last,
        std::size_t min_capacity = 0,
        storage_ptr sp = {})
        : sp_(std::move(sp))
        , t_(&empty_)
    {
        construct(
            first, last,
            min_capacity,
            typename std::iterator_traits<
                InputIt>::iterator_category{});
    }

    /** Move constructor.

        The object is constructed by acquiring ownership of
        the contents of `other` and shared ownership
        of `other`'s memory resource.

        @note

        After construction, the moved-from object behaves
        as if newly constructed with its current memory resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The object to move.
    */
    BOOST_JSON_DECL
    object(object&& other) noexcept;

    /** Move constructor.

        The object is constructed with the contents of
        `other` by move semantics, using the specified
        memory resource:

        @li If `*other.storage() == *sp`, ownership of
        the underlying memory is transferred in constant
        time, with no possibility of exceptions.
        After construction, the moved-from object behaves
        as if newly constructed with its current storage
        pointer.

        @li If `*other.storage() != *sp`, an
        element-wise copy is performed, which may throw.
        In this case, the moved-from object is not
        changed.

        @par Complexity
        Constant or linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The object to move.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    BOOST_JSON_DECL
    object(
        object&& other,
        storage_ptr sp);

    /** Pilfer constructor.

        The object is constructed by acquiring ownership
        of the contents of `other` using pilfer semantics.
        This is more efficient than move construction, when
        it is known that the moved-from object will be
        immediately destroyed afterwards.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The value to pilfer. After pilfer
        construction, `other` is not in a usable state
        and may only be destroyed.

        @see @ref pilfer,
            <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0308r0.html">
                Valueless Variants Considered Harmful</a>
    */
    object(pilfered<object> other) noexcept
        : sp_(std::move(other.get().sp_))
        , t_(detail::exchange(
            other.get().t_, &empty_))
    {
    }

    /** Copy constructor.

        The object is constructed with a copy of the
        contents of `other`, using `other`'s memory resource.

        @par Complexity
        Linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The object to copy.
    */
    object(
        object const& other)
        : object(other, other.sp_)
    {
    }

    /** Copy constructor.

        The object is constructed with a copy of the
        contents of `other`, using the specified memory resource.

        @par Complexity
        Linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The object to copy.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    BOOST_JSON_DECL
    object(
        object const& other,
        storage_ptr sp);

    /** Construct from initializer-list.

        The object is constructed with a copy of the values
        in the initializer-list in order, using the
        specified memory resource.
        If there are elements with duplicate keys; that
        is, if multiple elements in the range have keys
        that compare equal, only the first equivalent
        element will be inserted.

        @par Complexity
        Linear in `init.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param init The initializer list to insert.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    object(
        std::initializer_list<
            std::pair<string_view, value_ref>> init,
        storage_ptr sp = {})
        : object(init, 0, std::move(sp))
    {
    }

    /** Construct from initializer-list.

        Storage for at least `min_capacity` elements is
        reserved, and then
        the object is constructed with a copy of the values
        in the initializer-list in order, using the
        specified memory resource.
        If there are elements with duplicate keys; that
        is, if multiple elements in the range have keys
        that compare equal, only the first equivalent
        element will be inserted.

        @par Complexity
        Linear in `init.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param init The initializer list to insert.

        @param min_capacity The minimum number
        of elements for which capacity is guaranteed
        without a subsequent reallocation.
        Upon construction, @ref capacity() will be greater
        than or equal to this number.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    BOOST_JSON_DECL
    object(
        std::initializer_list<
            std::pair<string_view, value_ref>> init,
        std::size_t min_capacity,
        storage_ptr sp = {});

    //------------------------------------------------------
    //
    // Assignment
    //
    //------------------------------------------------------

    /** Copy assignment.

        The contents of the object are replaced with an
        element-wise copy of `other`.

        @par Complexity
        Linear in @ref size() plus `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The object to copy.
    */
    BOOST_JSON_DECL
    object&
    operator=(object const& other);

    /** Move assignment.

        The contents of the object are replaced with the
        contents of `other` using move semantics:

        @li If `*other.storage() == *sp`, ownership of
        the underlying memory is transferred in constant
        time, with no possibility of exceptions.
        After assignment, the moved-from object behaves
        as if newly constructed with its current storage
        pointer.

        @li If `*other.storage() != *sp`, an
        element-wise copy is performed, which may throw.
        In this case, the moved-from object is not
        changed.

        @par Complexity
        Constant or linear in @ref size() plus `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The object to move.
    */
    BOOST_JSON_DECL
    object&
    operator=(object&& other);

    /** Assignment.

        Replaces the contents with the contents of an
        initializer list.

        @par Complexity
        Linear in @ref size() plus
        average case linear in `init.size()`,
        worst case quadratic in `init.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param init The initializer list to copy.
    */
    BOOST_JSON_DECL
    object&
    operator=(std::initializer_list<
        std::pair<string_view, value_ref>> init);

    //------------------------------------------------------

    /** Return the associated @ref memory_resource

        This returns the @ref memory_resource used by
        the container.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    storage_ptr const&
    storage() const noexcept
    {
        return sp_;
    }

    /** Return the associated @ref memory_resource

        This function returns an instance of
        @ref polymorphic_allocator constructed from the
        associated @ref memory_resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    allocator_type
    get_allocator() const noexcept
    {
        return sp_.get();
    }

    //------------------------------------------------------
    //
    // Iterators
    //
    //------------------------------------------------------

    /** Return an iterator to the first element.

        If the container is empty, @ref end() is returned.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    iterator
    begin() noexcept;

    /** Return a const iterator to the first element.

        If the container is empty, @ref end() is returned.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    const_iterator
    begin() const noexcept;

    /** Return a const iterator to the first element.

        If the container is empty, @ref cend() is returned.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    const_iterator
    cbegin() const noexcept;

    /** Return an iterator to the element following the last element.

        The element acts as a placeholder; attempting
        to access it results in undefined behavior.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    iterator
    end() noexcept;

    /** Return a const iterator to the element following the last element.

        The element acts as a placeholder; attempting
        to access it results in undefined behavior.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    const_iterator
    end() const noexcept;

    /** Return a const iterator to the element following the last element.

        The element acts as a placeholder; attempting
        to access it results in undefined behavior.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    const_iterator
    cend() const noexcept;

    /** Return a reverse iterator to the first element of the reversed container.

        The pointed-to element corresponds to the
        last element of the non-reversed container.
        If the container is empty, @ref rend() is returned.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    reverse_iterator
    rbegin() noexcept;

    /** Return a const reverse iterator to the first element of the reversed container.

        The pointed-to element corresponds to the
        last element of the non-reversed container.
        If the container is empty, @ref rend() is returned.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    const_reverse_iterator
    rbegin() const noexcept;

    /** Return a const reverse iterator to the first element of the reversed container.

        The pointed-to element corresponds to the
        last element of the non-reversed container.
        If the container is empty, @ref crend() is returned.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    const_reverse_iterator
    crbegin() const noexcept;

    /** Return a reverse iterator to the element following the last element of the reversed container.

        The pointed-to element corresponds to the element
        preceding the first element of the non-reversed container.
        This element acts as a placeholder, attempting
        to access it results in undefined behavior.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    reverse_iterator
    rend() noexcept;

    /** Return a const reverse iterator to the element following the last element of the reversed container.

        The pointed-to element corresponds to the element
        preceding the first element of the non-reversed container.
        This element acts as a placeholder, attempting
        to access it results in undefined behavior.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    const_reverse_iterator
    rend() const noexcept;

    /** Return a const reverse iterator to the element following the last element of the reversed container.

        The pointed-to element corresponds to the element
        preceding the first element of the non-reversed container.
        This element acts as a placeholder, attempting
        to access it results in undefined behavior.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    const_reverse_iterator
    crend() const noexcept;

    //------------------------------------------------------
    //
    // Capacity
    //
    //------------------------------------------------------

    /** Return whether there are no elements.

        Returns `true` if there are no elements in
        the container, i.e. @ref size() returns 0.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    bool
    empty() const noexcept;

    /** Return the number of elements.

        This returns the number of elements in the container.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    std::size_t
    size() const noexcept;

    /** Return the maximum number of elements any object can hold

        The maximum is an implementation-defined number dependent
        on system or library implementation. This value is a
        theoretical limit; at runtime, the actual maximum size
        may be less due to resource limits.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    static
    constexpr
    std::size_t
    max_size() noexcept;

    /** Return the number of elements that can be held in currently allocated memory

        This number may be larger than the value returned
        by @ref size().

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    inline
    std::size_t
    capacity() const noexcept;

    /** Increase the capacity to at least a certain amount.

        This increases the @ref capacity() to a value
        that is greater than or equal to `new_capacity`.
        If `new_capacity > capacity()`, new memory is
        allocated. Otherwise, the call has no effect.
        The number of elements and therefore the
        @ref size() of the container is not changed.
    \n
        If new memory is allocated, all iterators
        including any past-the-end iterators, and all
        references to the elements are invalidated.
        Otherwise, no iterators or references are
        invalidated.

        @par Complexity
        Constant or average case linear in
        @ref size(), worst case quadratic.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param new_capacity The new minimum capacity.

        @throw std::length_error `new_capacity > max_size()`
    */
    void
    reserve(std::size_t new_capacity)
    {
        if(new_capacity <= capacity())
            return;
        rehash(new_capacity);
    }

    //------------------------------------------------------
    //
    // Modifiers
    //
    //------------------------------------------------------

    /** Erase all elements.

        Erases all elements from the container without
        changing the capacity.
        After this call, @ref size() returns zero.
        All references, pointers, and iterators are
        invalidated.

        @par Complexity
        Linear in @ref size().

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    void
    clear() noexcept;

    /** Insert elements.

        Inserts `p`, from which @ref value_type must
        be constructible.

        @par Constraints
        @code
        std::is_constructible_v<value_type, P>
        @endcode

        @par Complexity
        Average case amortized constant,
        worst case linear in @ref size().

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param p The value to insert.

        @throw std::length_error key is too long.

        @throw std::length_error @ref size() >= max_size().

        @return A pair where `first` is an iterator
        to the existing or inserted element, and `second`
        is `true` if the insertion took place or `false` if
        the assignment took place.
    */
    template<class P
#ifndef BOOST_JSON_DOCS
        ,class = typename std::enable_if<
            std::is_constructible<key_value_pair,
                P, storage_ptr>::value>::type
#endif
    >
    std::pair<iterator, bool>
    insert(P&& p);

    /** Insert elements.

        The elements in the range `{first, last)` whose
        keys are unique are inserted one at a time, in order.
        If there are elements with duplicate keys; that
        is, if multiple elements in the range have keys
        that compare equal, only the first equivalent
        element will be inserted.

        @par Precondition
        `first` and `last` are not iterators into `*this`.

        @par Constraints
        @code
        std::is_constructible_v<value_type, std::iterator_traits<InputIt>::value_type>
        @endcode

        @par Complexity
        Linear in `std::distance(first, last)`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param first An input iterator pointing to the first
        element to insert, or pointing to the end of the range.

        @param last An input iterator pointing to the end
        of the range.

        @tparam InputIt a type satisfying the requirements
        of __InputIterator__.
    */
    template<
        class InputIt
    #ifndef BOOST_JSON_DOCS
        ,class = is_inputit<InputIt>
    #endif
    >
    void
    insert(InputIt first, InputIt last)
    {
        insert(first, last, typename
            std::iterator_traits<InputIt
                >::iterator_category{});
    }

    /** Insert elements.

        The elements in the initializer list whose
        keys are unique are inserted one at a time, in order.
        If there are elements with duplicate keys; that
        is, if multiple elements in the range have keys
        that compare equal, only the first equivalent
        element will be inserted.

        @par Complexity
        Linear in `init.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param init The initializer list to insert
    */
    BOOST_JSON_DECL
    void
    insert(std::initializer_list<
        std::pair<string_view, value_ref>> init);

    /** Insert an element or assign to the current element if the key already exists.

        If the key equivalent to `key` already exists in the
        container. assigns `std::forward<M>(obj)` to the
        `mapped type` corresponding to the key. Otherwise,
        inserts the new value at the end as if by insert,
        constructing it from
        `value_type(key, std::forward<M>(obj))`.

        If the insertion occurs and results in a rehashing
        of the container, all iterators are invalidated.
        Otherwise, iterators are not affected.
        References are not invalidated.
        Rehashing occurs only if the new number of elements
        is greater than @ref capacity().

        @par Complexity
        Amortized constant on average, worst case linear in @ref size().

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @return A `std::pair` where `first` is an iterator
        to the existing or inserted element, and `second`
        is `true` if the insertion took place or `false` if
        the assignment took place.

        @param key The key used for lookup and insertion

        @param m The value to insert or assign

        @throw std::length_error if key is too long
    */
    template<class M>
    std::pair<iterator, bool>
    insert_or_assign(
        string_view key, M&& m);

    /** Construct an element in-place.

        Inserts a new element into the container constructed
        in-place with the given argument if there is no
        element with the key in the container.
        The element is inserted after all the existing
        elements.

        If the insertion occurs and results in a rehashing
        of the container, all iterators are invalidated.
        Otherwise, iterators are not affected.
        References are not invalidated.
        Rehashing occurs only if the new number of elements
        is greater than @ref capacity().

        @par Complexity
        Amortized constant on average, worst case linear in @ref size().

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @return A `std::pair` where `first` is an iterator
        to the existing or inserted element, and `second`
        is `true` if the insertion took place or `false` if
        the assignment took place.

        @param key The key used for lookup and insertion

        @param arg The argument used to construct the value.
        This will be passed as `std::forward<Arg>(arg)` to
        the @ref value constructor.

        @throw std::length_error if key is too long
    */
    template<class Arg>
    std::pair<iterator, bool>
    emplace(string_view key, Arg&& arg);

    /** Erase an element

        Remove the element pointed to by `pos`, which must
        be valid and dereferenceable. Thus the @ref end()
        iterator (which is valid but cannot be dereferenced)
        cannot be used as a value for `pos`.
        References and iterators to the erased element are
        invalidated. Other iterators and references are not
        invalidated.

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        No-throw guarantee.

        @return An iterator following the last removed element.

        @param pos An iterator pointing to the element to be
        removed.
    */
    BOOST_JSON_DECL
    iterator
    erase(const_iterator pos) noexcept;

    /** Erase an element

        Remove the element which matches `key`, if it exists.
        References and iterators to the erased element are
        invalidated. Other iterators and references are not
        invalidated.

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        No-throw guarantee.

        @return The number of elements removed, which will
        be either 0 or 1.

        @param key The key to match.
    */
    BOOST_JSON_DECL
    std::size_t
    erase(string_view key) noexcept;

    /** Swap two objects.

        Exchanges the contents of this object with another
        object. Ownership of the respective @ref memory_resource
        objects is not transferred.

        @li If `*other.storage() == *this->storage()`,
        ownership of the underlying memory is swapped in
        constant time, with no possibility of exceptions.
        All iterators and references remain valid.

        @li If `*other.storage() != *this->storage()`,
        the contents are logically swapped by making copies,
        which can throw. In this case all iterators and
        references are invalidated.

        @par Complexity
        Constant or linear in @ref size() plus `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The object to swap with.
        If `this == &other`, this function call has no effect.
    */
    BOOST_JSON_DECL
    void
    swap(object& other);

    /** Swap two objects.

        Exchanges the contents of the object `lhs` with
        another object `rhs`. Ownership of the respective
        @ref memory_resource objects is not transferred.

        @li If `*lhs.storage() == *rhs.storage()`,
        ownership of the underlying memory is swapped in
        constant time, with no possibility of exceptions.
        All iterators and references remain valid.

        @li If `*lhs.storage() != *rhs.storage()`,
        the contents are logically swapped by making a copy,
        which can throw. In this case all iterators and
        references are invalidated.

        @par Effects
        @code
        lhs.swap( rhs );
        @endcode

        @par Complexity
        Constant or linear in `lhs.size() + rhs.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param lhs The object to exchange.

        @param rhs The object to exchange.
        If `&lhs == &rhs`, this function call has no effect.

        @see @ref object::swap
    */
    friend
    void
    swap(object& lhs, object& rhs)
    {
        lhs.swap(rhs);
    }

    //------------------------------------------------------
    //
    // Lookup
    //
    //------------------------------------------------------

    /** Access the specified element, with bounds checking.

        Returns a reference to the mapped value of the element
        that matches `key`, otherwise throws.

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        Strong guarantee.

        @return A reference to the mapped value.

        @param key The key of the element to find.

        @throw std::out_of_range if no such element exists.
    */
    inline
    value&
    at(string_view key);

    /** Access the specified element, with bounds checking.

        Returns a constant reference to the mapped value of
        the element that matches `key`, otherwise throws.

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        Strong guarantee.

        @return A reference to the mapped value.

        @param key The key of the element to find.

        @throw std::out_of_range if no such element exists.
    */
    inline
    value const&
    at(string_view key) const;

    /** Access or insert the specified element

        Returns a reference to the value that is mapped
        to a key equivalent to key, performing an insertion
        of a null value if such key does not already exist.
    \n
        If an insertion occurs and results in a rehashing of
        the container, all iterators are invalidated. Otherwise
        iterators are not affected. References are not
        invalidated. Rehashing occurs only if the new
        number of elements is greater than @ref capacity().

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @return A reference to the mapped value.

        @param key The key of the element to find.
    */
    BOOST_JSON_DECL
    value&
    operator[](string_view key);

    /** Count the number of elements with a specific key

        This function returns the count of the number of
        elements match `key`. The only possible return values
        are 0 and 1.

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        No-throw guarantee.

        @param key The key of the element to find.
    */
    BOOST_JSON_DECL
    std::size_t
    count(string_view key) const noexcept;

    /** Find an element with a specific key

        This function returns an iterator to the element
        matching `key` if it exists, otherwise returns
        @ref end().

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        No-throw guarantee.

        @param key The key of the element to find.
    */
    BOOST_JSON_DECL
    iterator
    find(string_view key) noexcept;

    /** Find an element with a specific key

        This function returns a constant iterator to
        the element matching `key` if it exists,
        otherwise returns @ref end().

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        No-throw guarantee.

        @param key The key of the element to find.
    */
    BOOST_JSON_DECL
    const_iterator
    find(string_view key) const noexcept;

    /** Return `true` if the key is found

        This function returns `true` if a key with the
        specified string is found.

        @par Effects
        @code
        return this->find(key) != this->end();
        @endcode

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        No-throw guarantee.

        @param key The key of the element to find.

        @see @ref find
    */
    BOOST_JSON_DECL
    bool
    contains(string_view key) const noexcept;

    /** Return a pointer to the value if the key is found, or null

        This function searches for a value with the given
        key, and returns a pointer to it if found. Otherwise
        it returns null.

        @par Example
        @code
        if( auto p = obj.if_contains( "key" ) )
            std::cout << *p;
        @endcode

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        No-throw guarantee.

        @param key The key of the element to find.

        @see @ref find
    */
    BOOST_JSON_DECL
    value const*
    if_contains(string_view key) const noexcept;

    /** Return a pointer to the value if the key is found, or null

        This function searches for a value with the given
        key, and returns a pointer to it if found. Otherwise
        it returns null.

        @par Example
        @code
        if( auto p = obj.if_contains( "key" ) )
            std::cout << *p;
        @endcode

        @par Complexity
        Constant on average, worst case linear in @ref size().

        @par Exception Safety
        No-throw guarantee.

        @param key The key of the element to find.

        @see @ref find
    */
    BOOST_JSON_DECL
    value*
    if_contains(string_view key) noexcept;

    /** Return `true` if two objects are equal.

        Objects are equal when their sizes are the same,
        and when for each key in `lhs` there is a matching
        key in `rhs` with the same value.

        @par Complexity
        Constant, or linear (worst case quadratic) in `lhs.size()`.

        @par Exception Safety
        No-throw guarantee.
    */
    // inline friend speeds up overload resolution
    friend
    bool
    operator==(
        object const& lhs,
        object const& rhs) noexcept
    {
        return lhs.equal(rhs);
    }

    /** Return `true` if two objects are not equal.

        Objects are equal when their sizes are the same,
        and when for each key in `lhs` there is a matching
        key in `rhs` with the same value.

        @par Complexity
        Constant, or linear (worst case quadratic) in `lhs.size()`.

        @par Exception Safety
        No-throw guarantee.
    */
    // inline friend speeds up overload resolution
    friend
    bool
    operator!=(
        object const& lhs,
        object const& rhs) noexcept
    {
        return ! (lhs == rhs);
    }

private:
    template<class CharRange>
    friend
    std::pair<key_value_pair*, std::size_t>
    detail::find_in_object(
        object const& obj,
        CharRange key) noexcept;

    template<class InputIt>
    void
    construct(
        InputIt first,
        InputIt last,
        std::size_t min_capacity,
        std::input_iterator_tag);

    template<class InputIt>
    void
    construct(
        InputIt first,
        InputIt last,
        std::size_t min_capacity,
        std::forward_iterator_tag);

    template<class InputIt>
    void
    insert(
        InputIt first,
        InputIt last,
        std::input_iterator_tag);

    template<class InputIt>
    void
    insert(
        InputIt first,
        InputIt last,
        std::forward_iterator_tag);

    BOOST_JSON_DECL
    std::pair<iterator, bool>
    insert_impl(
        pilfered<key_value_pair> p);

    BOOST_JSON_DECL
    key_value_pair*
    insert_impl(
        pilfered<key_value_pair> p,
        std::size_t hash);

    BOOST_JSON_DECL
    void
    rehash(std::size_t new_capacity);

    BOOST_JSON_DECL
    bool
    equal(object const& other) const noexcept;

    inline
    std::size_t
    growth(
        std::size_t new_size) const;

    inline
    void
    remove(
        index_t& head,
        key_value_pair& p) noexcept;

    inline
    void
    destroy() noexcept;

    inline
    void
    destroy(
        key_value_pair* first,
        key_value_pair* last) noexcept;
};

BOOST_JSON_NS_END

// std::hash specialization
#ifndef BOOST_JSON_DOCS
namespace std {
template <>
struct hash< ::boost::json::object > {
    BOOST_JSON_DECL
    std::size_t
    operator()(::boost::json::object const& jo) const noexcept;
};
} // std
#endif


// Must be included here for this file to stand alone
#include <boost/json/value.hpp>

// includes are at the bottom of <boost/json/value.hpp>

#endif

/* object.hpp
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
*/