//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_STORAGE_PTR_HPP
#define BOOST_JSON_STORAGE_PTR_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/memory_resource.hpp>
#include <boost/json/detail/shared_resource.hpp>
#include <boost/json/detail/default_resource.hpp>
#include <cstddef>
#include <new>
#include <type_traits>
#include <utility>

BOOST_JSON_NS_BEGIN

/** A smart pointer to a @ref memory_resource

    This container is used to hold a pointer to a
    memory resource. The pointed-to resource is
    always valid; default-constructed pointers
    use the default memory resource, which calls
    into the standard global system heap.
    Depending on the means of construction, the
    ownership will be either:

    @li Non-owning, when constructing from a raw
    pointer to @ref memory_resource or from a
    @ref polymorphic_allocator. In this case the
    caller is responsible for ensuring that the
    lifetime of the memory resource extends until
    there are no more calls to allocate or
    deallocate.

    @li Owning, when constructing using the function
    @ref make_shared_resource. In this case
    ownership is shared; the lifetime of the memory
    resource extends until the last copy of the
    @ref storage_ptr is destroyed.

    @par Examples

    These statements create a memory resource on the
    stack and construct a pointer from it without
    taking ownership:
    @code
    monotonic_resource mr;                  // Create our memory resource on the stack
    storage_ptr sp( &mr );                  // Construct a non-owning pointer to the resource
    @endcode

    This function creates a pointer to a memory
    resource using shared ownership and returns it.
    The lifetime of the memory resource extends until
    the last copy of the pointer is destroyed:
    @code
    // Create a counted memory resource and return it
    storage_ptr make_storage()
    {
        return make_shared_resource< monotonic_resource >();
    }
    @endcode

    @par Thread Safety

    Instances of this type provide the default level of
    thread safety for all C++ objects. Specifically, it
    conforms to
    <a href="http://eel.is/c++draft/res.on.data.races">
        16.4.6.10 Data race avoidance</a>.

    @see
        @ref make_shared_resource,
        @ref memory_resource,
        @ref polymorphic_allocator
*/
class storage_ptr
{
#ifndef BOOST_JSON_DOCS
    // VFALCO doc toolchain shows this when it shouldn't
    friend struct detail::shared_resource;
#endif
    using shared_resource =
        detail::shared_resource;

    using default_resource =
        detail::default_resource;

    std::uintptr_t i_;

    shared_resource*
    get_shared() const noexcept
    {
        return static_cast<shared_resource*>(
            reinterpret_cast<memory_resource*>(
                i_ & ~3));
    }

    void
    addref() const noexcept
    {
        if(is_shared())
            get_shared()->refs.fetch_add(
                1, std::memory_order_relaxed);
    }

    void
    release() const noexcept
    {
        if(is_shared())
        {
            auto const p = get_shared();
            if(p->refs.fetch_sub(1,
                    std::memory_order_acq_rel) == 1)
                delete p;
        }
    }

    template<class T>
    storage_ptr(
        detail::shared_resource_impl<T>* p) noexcept
        : i_(reinterpret_cast<std::uintptr_t>(
                static_cast<memory_resource*>(p)) + 1 +
            (json::is_deallocate_trivial<T>::value ? 2 : 0))
    {
        BOOST_ASSERT(p);
    }

public:
    /** Destructor

        If the pointer has shared ownership of the
        resource, the shared ownership is released.
        If this is the last owned copy, the memory
        resource is destroyed.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    ~storage_ptr() noexcept
    {
        release();
    }

    /** Constructor

        This constructs a non-owning pointer that refers
        to the default memory resource, which uses the
        standard global system heap to allocate and
        free memory.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    storage_ptr() noexcept
        : i_(0)
    {
    }

    /** Constructor

        This constructs a non-owning pointer that
        points to the memory resource `r`.
        The caller is responsible for maintaining the
        lifetime of the pointed-to @ref memory_resource.

        @par Constraints
        @code
        std::is_convertible< T*, memory_resource* >::value == true
        @endcode

        @par Preconditions
        @code
        r != nullptr
        @endcode

        @par Exception Safety
        No-throw guarantee.

        @param r A pointer to the memory resource to use.
        This may not be null.
    */
    template<class T
#ifndef BOOST_JSON_DOCS
        , class = typename std::enable_if<
            std::is_convertible<T*,
                memory_resource*>::value>::type
#endif
    >
    storage_ptr(T* r) noexcept
        : i_(reinterpret_cast<std::uintptr_t>(
                static_cast<memory_resource *>(r)) +
            (json::is_deallocate_trivial<T>::value ? 2 : 0))
    {
        BOOST_ASSERT(r);
    }

    /** Constructor

        This constructs a non-owning pointer that
        points to the same memory resource as `alloc`,
        obtained by calling `alloc.resource()`.
        The caller is responsible for maintaining the
        lifetime of the pointed-to @ref memory_resource.

        @par Constraints
        @code
        std::is_convertible< T*, memory_resource* >::value == true
        @endcode

        @par Exception Safety
        No-throw guarantee.

        @param alloc A @ref polymorphic_allocator to
        construct from.
    */
    template<class T>
    storage_ptr(
        polymorphic_allocator<T> const& alloc) noexcept
        : i_(reinterpret_cast<std::uintptr_t>(
            alloc.resource()))
    {
    }

    /** Move constructor

        This function constructs a pointer that
        points to the same memory resource as `other`,
        with the same ownership:

        @li If `other` is non-owning, then `*this`
        will be be non-owning.

        @li If `other` has shared ownership, then
        ownership will be transferred to `*this`.

        After construction, `other` will point
        to the default memory resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The pointer to construct from.
    */
    storage_ptr(
        storage_ptr&& other) noexcept
        : i_(detail::exchange(other.i_, 0))
    {
    }

    /** Copy constructor

        This function constructs a pointer that
        points to the same memory resource as `other`,
        with the same ownership:

        @li If `other` is non-owning, then `*this`
        will be be non-owning.

        @li If `other` has shared ownership, then
        `*this` will acquire shared ownership.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The pointer to construct from.
    */
    storage_ptr(
        storage_ptr const& other) noexcept
        : i_(other.i_)
    {
        addref();
    }

    /** Move assignment

        This function assigns a pointer that
        points to the same memory resource as `other`,
        with the same ownership:

        @li If `other` is non-owning, then `*this`
        will be be non-owning.

        @li If `other` has shared ownership, then
        ownership will be transferred to `*this`.

        After assignment, `other` will point
        to the default memory resource.
        If `*this` previously had shared ownership,
        it is released before the function returns.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The storage pointer to move.
    */
    storage_ptr&
    operator=(
        storage_ptr&& other) noexcept
    {
        release();
        i_ = detail::exchange(other.i_, 0);
        return *this;
    }

    /** Copy assignment.

        This function assigns a pointer that
        points to the same memory resource as `other`,
        with the same ownership:

        @li If `other` is non-owning, then `*this`
        will be be non-owning.

        @li If `other` has shared ownership, then
        `*this` will acquire shared ownership.

        If `*this` previously had shared ownership,
        it is released before the function returns.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The storage pointer to copy.
    */
    storage_ptr&
    operator=(
        storage_ptr const& other) noexcept
    {
        other.addref();
        release();
        i_ = other.i_;
        return *this;
    }

    /** Return `true` if ownership of the memory resource is shared.

        This function returns true for memory resources
        created using @ref make_shared_resource.
    */
    bool
    is_shared() const noexcept
    {
        return (i_ & 1) != 0;
    }

    /** Return `true` if calling `deallocate` on the memory resource has no effect.

        This function is used to determine if the deallocate
        function of the pointed to memory resource is trivial.
        The value of @ref is_deallocate_trivial is evaluated
        and saved when the memory resource is constructed
        and the type is known, before the type is erased.
    */
    bool
    is_deallocate_trivial() const noexcept
    {
        return (i_ & 2) != 0;
    }

    /** Return `true` if ownership of the memory resource is not shared and deallocate is trivial.

        This function is used to determine if calls to deallocate
        can effectively be skipped.

        @par Effects
        Returns `! this->is_shared() && this->is_deallocate_trivial()`
    */
    bool
    is_not_shared_and_deallocate_is_trivial() const noexcept
    {
        return (i_ & 3) == 2;
    }

    /** Return a pointer to the memory resource.

        This function returns a pointer to the
        referenced @ref memory_resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    memory_resource*
    get() const noexcept
    {
        if(i_ != 0)
            return reinterpret_cast<
                memory_resource*>(i_ & ~3);
        return default_resource::get();
    }

    /** Return a pointer to the memory resource.

        This function returns a pointer to the
        referenced @ref memory_resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    memory_resource*
    operator->() const noexcept
    {
        return get();
    }

    /** Return a reference to the memory resource.

        This function returns a reference to the
        pointed-to @ref memory_resource.

        @par Complexity

        Constant.

        @par Exception Safety

        No-throw guarantee.
    */
    memory_resource&
    operator*() const noexcept
    {
        return *get();
    }

    template<class U, class... Args>
    friend
    storage_ptr
    make_shared_resource(Args&&... args);
};

#if defined(_MSC_VER)
# pragma warning( push )
# if !defined(__clang__) && _MSC_VER <= 1900
#  pragma warning( disable : 4702 )
# endif
#endif
/** Return shared ownership of a new, dynamically allocated memory resource.

    This function dynamically allocates a new memory resource
    as if by `operator new` that uses shared ownership. The
    lifetime of the memory resource will be extended until
    the last @ref storage_ptr which points to it is destroyed.

    @par Mandates
    @code
    std::is_base_of< memory_resource, T >::value == true
    @endcode

    @par Complexity
    Same as `new T( std::forward<Args>(args)... )`.

    @par Exception Safety
    Strong guarantee.

    @tparam T The type of memory resource to create.

    @param args Parameters forwarded to the constructor of `T`.
*/
template<class T, class... Args>
storage_ptr
make_shared_resource(Args&&... args)
{
    // If this generates an error, it means that
    // `T` is not a memory resource.
    BOOST_STATIC_ASSERT(
        std::is_base_of<
            memory_resource, T>::value);
    return storage_ptr(new
        detail::shared_resource_impl<T>(
            std::forward<Args>(args)...));
}
#if defined(_MSC_VER)
# pragma warning( pop )
#endif

/** Return true if two storage pointers point to the same memory resource.

    This function returns `true` if the @ref memory_resource
    objects pointed to by `lhs` and `rhs` have the
    same address.
*/
inline
bool
operator==(
    storage_ptr const& lhs,
    storage_ptr const& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

/** Return true if two storage pointers point to different memory resources.

    This function returns `true` if the @ref memory_resource
    objects pointed to by `lhs` and `rhs` have different
    addresses.
*/
inline
bool
operator!=(
    storage_ptr const& lhs,
    storage_ptr const& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

BOOST_JSON_NS_END

#endif

/* storage_ptr.hpp
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
*/