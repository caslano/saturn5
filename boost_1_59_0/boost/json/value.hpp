//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_VALUE_HPP
#define BOOST_JSON_VALUE_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/array.hpp>
#include <boost/json/kind.hpp>
#include <boost/json/object.hpp>
#include <boost/json/pilfer.hpp>
#include <boost/json/storage_ptr.hpp>
#include <boost/json/string.hpp>
#include <boost/json/string_view.hpp>
#include <boost/json/value_ref.hpp>
#include <boost/json/detail/except.hpp>
#include <boost/json/detail/value.hpp>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <iosfwd>
#include <limits>
#include <new>
#include <type_traits>
#include <utility>

BOOST_JSON_NS_BEGIN

//----------------------------------------------------------

/** The type used to represent any JSON value

    This is a
    <a href="https://en.cppreference.com/w/cpp/concepts/regular"><em>Regular</em></a>.
    <em>Regular</em>
    type which works like
    a variant of the basic JSON data types: array,
    object, string, number, boolean, and null.

    @par Thread Safety

    Distinct instances may be accessed concurrently.
    Non-const member functions of a shared instance
    may not be called concurrently with any other
    member functions of that instance.
*/
class value
{
#ifndef BOOST_JSON_DOCS
    using scalar = detail::scalar;

    union
    {
        storage_ptr sp_; // must come first
        array       arr_;
        object      obj_;
        string      str_;
        scalar      sca_;
    };
#endif

    struct init_iter;

#ifndef BOOST_JSON_DOCS
    // VFALCO doc toolchain incorrectly treats this as public
    friend struct detail::access;
#endif

    explicit
    value(
        detail::unchecked_array&& ua)
        : arr_(std::move(ua))
    {
    }

    explicit
    value(
        detail::unchecked_object&& uo)
        : obj_(std::move(uo))
    {
    }

    value(
        detail::key_t const&,
        string_view s,
        storage_ptr sp)
        : str_(detail::key_t{}, s, std::move(sp))
    {
    }

    value(
        detail::key_t const&,
        string_view s1,
        string_view s2,
        storage_ptr sp)
        : str_(detail::key_t{}, s1, s2, std::move(sp))
    {
    }

    inline bool is_scalar() const noexcept
    {
        return sca_.k < json::kind::string;
    }

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

    /** Destructor.

        The value and all of its contents are destroyed.
        Any dynamically allocated memory that was allocated
        internally is freed.

        @par Complexity
        Constant, or linear in size for array or object.

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    ~value() noexcept;

    /** Default constructor.

        The constructed value is null,
        using the default memory resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    value() noexcept
        : sca_()
    {
    }

    /** Constructor.

        The constructed value is null,
        using the specified @ref memory_resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    explicit
    value(storage_ptr sp) noexcept
        : sca_(std::move(sp))
    {
    }

    /** Pilfer constructor.

        The value is constructed by acquiring ownership
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
    value(pilfered<value> other) noexcept
    {
        relocate(this, other.get());
        ::new(&other.get().sca_) scalar();
    }

    /** Copy constructor.

        The value is constructed with a copy of the
        contents of `other`, using the same
        memory resource as `other`.

        @par Complexity
        Linear in the size of `other`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The value to copy.
    */
    value(value const& other)
        : value(other, other.storage())
    {
    }

    /** Copy constructor

        The value is constructed with a copy of the
        contents of `other`, using the
        specified memory resource.

        @par Complexity
        Linear in the size of `other`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The value to copy.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    BOOST_JSON_DECL
    value(
        value const& other,
        storage_ptr sp);

    /** Move constructor

        The value is constructed by acquiring ownership of
        the contents of `other` and shared ownership of
        `other`'s memory resource.

        @note

        After construction, the moved-from value becomes a
        null value with its current storage pointer.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The value to move.
    */
    BOOST_JSON_DECL
    value(value&& other) noexcept;

    /** Move constructor

        The value is constructed with the contents of
        `other` by move semantics, using the specified
        memory resource:

        @li If `*other.storage() == *sp`, ownership of
        the underlying memory is transferred in constant
        time, with no possibility of exceptions.
        After construction, the moved-from value becomes
        a null value with its current storage pointer.

        @li If `*other.storage() != *sp`, an
        element-wise copy is performed if
        `other.is_structured() == true`, which may throw.
        In this case, the moved-from value is not
        changed.

        @par Complexity
        Constant or linear in the size of `other`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The value to move.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    BOOST_JSON_DECL
    value(
        value&& other,
        storage_ptr sp);

    //------------------------------------------------------
    //
    // Conversion
    //
    //------------------------------------------------------

    /** Construct a null.

        A null value is a monostate.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        std::nullptr_t,
        storage_ptr sp = {}) noexcept
        : sca_(std::move(sp))
    {
    }

    /** Construct a bool.

        This constructs a `bool` value using
        the specified memory resource.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param b The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
#ifdef BOOST_JSON_DOCS
    value(
        bool b,
        storage_ptr sp = {}) noexcept;
#else
    template<class Bool
        ,class = typename std::enable_if<
            std::is_same<Bool, bool>::value>::type
    >
    value(
        Bool b,
        storage_ptr sp = {}) noexcept
        : sca_(b, std::move(sp))
    {
    }
#endif

    /** Construct a `std::int64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param i The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        signed char i,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::int64_t>(
            i), std::move(sp))
    {
    }

    /** Construct a `std::int64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param i The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        short i,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::int64_t>(
            i), std::move(sp))
    {
    }

    /** Construct a `std::int64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param i The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        int i,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::int64_t>(i),
            std::move(sp))
    {
    }

    /** Construct a `std::int64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param i The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        long i,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::int64_t>(i),
            std::move(sp))
    {
    }

    /** Construct a `std::int64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param i The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        long long i,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::int64_t>(i),
            std::move(sp))
    {
    }

    /** Construct a `std::uint64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param u The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        unsigned char u,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::uint64_t>(
            u), std::move(sp))
    {
    }

    /** Construct a `std::uint64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param u The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        unsigned short u,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::uint64_t>(u),
            std::move(sp))
    {
    }

    /** Construct a `std::uint64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param u The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        unsigned int u,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::uint64_t>(u),
            std::move(sp))
    {
    }

    /** Construct a `std::uint64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param u The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        unsigned long u,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::uint64_t>(u),
            std::move(sp))
    {
    }

    /** Construct a `std::uint64_t`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param u The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        unsigned long long u,
        storage_ptr sp = {}) noexcept
        : sca_(static_cast<std::uint64_t>(u),
            std::move(sp))
    {
    }

    /** Construct a `double`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param d The initial value.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        double d,
        storage_ptr sp = {}) noexcept
        : sca_(d, std::move(sp))
    {
    }

    /** Construct a @ref string.

        The string is constructed with a copy of the
        string view `s`, using the specified memory resource.

        @par Complexity
        Linear in `s.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param s The string view to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        string_view s,
        storage_ptr sp = {})
        : str_(s, std::move(sp))
    {
    }

    /** Construct a @ref string.

        The string is constructed with a copy of the
        null-terminated string `s`, using the specified
        memory resource.

        @par Complexity
        Linear in `std::strlen(s)`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param s The null-terminated string to construct
        with.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        char const* s,
        storage_ptr sp = {})
        : str_(s, std::move(sp))
    {
    }

    /** Construct a @ref string.

        The value is constructed from `other`, using the
        same memory resource. To transfer ownership, use `std::move`:

        @par Example
        @code
        string str = "The Boost C++ Library Collection";

        // transfer ownership
        value jv( std::move(str) );

        assert( str.empty() );
        assert( *str.storage() == *jv.storage() );
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The string to construct with.
    */
    value(
        string other) noexcept
        : str_(std::move(other))
    {
    }

    /** Construct a @ref string.

        The value is copy constructed from `other`,
        using the specified memory resource.

        @par Complexity
        Linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The string to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        string const& other,
        storage_ptr sp)
        : str_(
            other,
            std::move(sp))
    {
    }

    /** Construct a @ref string.

        The value is move constructed from `other`,
        using the specified memory resource.

        @par Complexity
        Constant or linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The string to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        string&& other,
        storage_ptr sp)
        : str_(
            std::move(other),
            std::move(sp))
    {
    }

    /** Construct a @ref string.

        This is the fastest way to construct
        an empty string, using the specified
        memory resource. The variable @ref string_kind
        may be passed as the first parameter
        to select this overload:

        @par Example
        @code
        // Construct an empty string

        value jv( string_kind );
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.

        @see @ref string_kind
    */
    value(
        string_kind_t,
        storage_ptr sp = {}) noexcept
        : str_(std::move(sp))
    {
    }

    /** Construct an @ref array.

        The value is constructed from `other`, using the
        same memory resource. To transfer ownership, use `std::move`:

        @par Example
        @code
        array arr( {1, 2, 3, 4, 5} );

        // transfer ownership
        value jv( std::move(arr) );

        assert( arr.empty() );
        assert( *arr.storage() == *jv.storage() );
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The array to construct with.
    */
    value(array other) noexcept
        : arr_(std::move(other))
    {
    }

    /** Construct an @ref array.

        The value is copy constructed from `other`,
        using the specified memory resource.

        @par Complexity
        Linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The array to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        array const& other,
        storage_ptr sp)
        : arr_(
            other,
            std::move(sp))
    {
    }

    /** Construct an @ref array.

        The value is move-constructed from `other`,
        using the specified memory resource.

        @par Complexity
        Constant or linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The array to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        array&& other,
        storage_ptr sp)
        : arr_(
            std::move(other),
            std::move(sp))
    {
    }

    /** Construct an @ref array.

        This is the fastest way to construct
        an empty array, using the specified
        memory resource. The variable @ref array_kind
        may be passed as the first parameter
        to select this overload:

        @par Example
        @code
        // Construct an empty array

        value jv( array_kind );
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.

        @see @ref array_kind
    */
    value(
        array_kind_t,
        storage_ptr sp = {}) noexcept
        : arr_(std::move(sp))
    {
    }

    /** Construct an @ref object.

        The value is constructed from `other`, using the
        same memory resource. To transfer ownership, use `std::move`:

        @par Example
        @code
        object obj( {{"a",1}, {"b",2}, {"c"},3}} );

        // transfer ownership
        value jv( std::move(obj) );

        assert( obj.empty() );
        assert( *obj.storage() == *jv.storage() );
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The object to construct with.
    */
    value(object other) noexcept
        : obj_(std::move(other))
    {
    }

    /** Construct an @ref object.

        The value is copy constructed from `other`,
        using the specified memory resource.

        @par Complexity
        Linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The object to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        object const& other,
        storage_ptr sp)
        : obj_(
            other,
            std::move(sp))
    {
    }

    /** Construct an @ref object.

        The value is move constructed from `other`,
        using the specified memory resource.

        @par Complexity
        Constant or linear in `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The object to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    value(
        object&& other,
        storage_ptr sp)
        : obj_(
            std::move(other),
            std::move(sp))
    {
    }

    /** Construct an @ref object.

        This is the fastest way to construct
        an empty object, using the specified
        memory resource. The variable @ref object_kind
        may be passed as the first parameter
        to select this overload:

        @par Example
        @code
        // Construct an empty object

        value jv( object_kind );
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.

        @see @ref object_kind
    */
    value(
        object_kind_t,
        storage_ptr sp = {}) noexcept
        : obj_(std::move(sp))
    {
    }

    /** Construct from an initializer-list

        If the initializer list consists of key/value
        pairs, an @ref object is created. Otherwise
        an @ref array is created. The contents of the
        initializer list are copied to the newly constructed
        value using the specified memory resource.

        @par Complexity
        Linear in `init.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param init The initializer list to construct from.

        @param sp A pointer to the @ref memory_resource
        to use. The container will acquire shared
        ownership of the memory resource.
    */
    BOOST_JSON_DECL
    value(
        std::initializer_list<value_ref> init,
        storage_ptr sp = {});

    //------------------------------------------------------
    //
    // Assignment
    //
    //------------------------------------------------------

    /** Copy assignment.

        The contents of the value are replaced with an
        element-wise copy of the contents of `other`.

        @par Complexity
        Linear in the size of `*this` plus `other`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The value to copy.
    */
    BOOST_JSON_DECL
    value&
    operator=(value const& other);

    /** Move assignment.

        The contents of the value are replaced with the
        contents of `other` using move semantics:

        @li If `*other.storage() == *sp`, ownership of
        the underlying memory is transferred in constant
        time, with no possibility of exceptions.
        After assignment, the moved-from value becomes
        a null with its current storage pointer.

        @li If `*other.storage() != *sp`, an
        element-wise copy is performed if
        `other.is_structured() == true`, which may throw.
        In this case, the moved-from value is not
        changed.

        @par Complexity
        Constant, or linear in
        `this->size()` plus `other.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The value to assign from.
    */
    BOOST_JSON_DECL
    value&
    operator=(value&& other);

    /** Assignment.

        Replace `*this` with the value formed by
        constructing from `init` and `this->storage()`.
        If the initializer list consists of key/value
        pairs, the resulting @ref object is assigned.
        Otherwise an @ref array is assigned. The contents
        of the initializer list are moved to `*this`
        using the existing memory resource.

        @par Complexity
        Linear in `init.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param init The initializer list to assign from.
    */
    BOOST_JSON_DECL
    value&
    operator=(
        std::initializer_list<value_ref> init);

    /** Assignment.

        Replace `*this` with null.

        @par Exception Safety
        No-throw guarantee.

        @par Complexity
        Linear in the size of `*this`.
    */
    value&
    operator=(std::nullptr_t) noexcept
    {
        if(is_scalar())
        {
            sca_.k = json::kind::null;
        }
        else
        {
            ::new(&sca_) scalar(
                destroy());
        }
        return *this;
    }

    /** Assignment.

        Replace `*this` with `b`.

        @par Exception Safety
        No-throw guarantee.

        @par Complexity
        Linear in the size of `*this`.

        @param b The new value.
    */
#ifdef BOOST_JSON_DOCS
    value& operator=(bool b) noexcept;
#else
    template<class Bool
        ,class = typename std::enable_if<
            std::is_same<Bool, bool>::value>::type
    >
    value& operator=(Bool b) noexcept
    {
        if(is_scalar())
        {
            sca_.b = b;
            sca_.k = json::kind::bool_;
        }
        else
        {
            ::new(&sca_) scalar(
                b, destroy());
        }
        return *this;
    }
#endif

    /** Assignment.

        Replace `*this` with `i`.

        @par Exception Safety
        No-throw guarantee.

        @par Complexity
        Linear in the size of `*this`.

        @param i The new value.
    */
    /** @{ */
    value& operator=(signed char i) noexcept
    {
        return operator=(
            static_cast<long long>(i));
    }

    value& operator=(short i) noexcept
    {
        return operator=(
            static_cast<long long>(i));
    }

    value& operator=(int i) noexcept
    {
        return operator=(
            static_cast<long long>(i));
    }

    value& operator=(long i) noexcept
    {
        return operator=(
            static_cast<long long>(i));
    }

    value& operator=(long long i) noexcept
    {
        if(is_scalar())
        {
            sca_.i = i;
            sca_.k = json::kind::int64;
        }
        else
        {
            ::new(&sca_) scalar(static_cast<
                std::int64_t>(i), destroy());
        }
        return *this;
    }
    /** @} */

    /** Assignment.

        Replace `*this` with `i`.

        @par Exception Safety
        No-throw guarantee.

        @par Complexity
        Linear in the size of `*this`.

        @param u The new value.
    */
    /** @{ */
    value& operator=(unsigned char u) noexcept
    {
        return operator=(static_cast<
            unsigned long long>(u));
    }

    value& operator=(unsigned short u) noexcept
    {
        return operator=(static_cast<
            unsigned long long>(u));
    }

    value& operator=(unsigned int u) noexcept
    {
        return operator=(static_cast<
            unsigned long long>(u));
    }

    value& operator=(unsigned long u) noexcept
    {
        return operator=(static_cast<
            unsigned long long>(u));
    }

    value& operator=(unsigned long long u) noexcept
    {
        if(is_scalar())
        {
            sca_.u = u;
            sca_.k = json::kind::uint64;
        }
        else
        {
            ::new(&sca_) scalar(static_cast<
                std::uint64_t>(u), destroy());
        }
        return *this;
    }
    /** @} */

    /** Assignment.

        Replace `*this` with `d`.

        @par Exception Safety
        No-throw guarantee.

        @par Complexity
        Linear in the size of `*this`.

        @param d The new value.
    */
    value& operator=(double d) noexcept
    {
        if(is_scalar())
        {
            sca_.d = d;
            sca_.k = json::kind::double_;
        }
        else
        {
            ::new(&sca_) scalar(
                d, destroy());
        }
        return *this;
    }

    /** Assignment.

        Replace `*this` with a copy of the string `s`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @par Complexity
        Linear in the sum of sizes of `*this` and `s`

        @param s The new string.
    */
    /** @{ */
    BOOST_JSON_DECL value& operator=(string_view s);
    BOOST_JSON_DECL value& operator=(char const* s);
    BOOST_JSON_DECL value& operator=(string const& s);
    /** @} */

    /** Assignment.

        The contents of the value are replaced with the
        contents of `s` using move semantics:

        @li If `*other.storage() == *this->storage()`,
        ownership of the underlying memory is transferred
        in constant time, with no possibility of exceptions.
        After assignment, the moved-from string becomes
        empty with its current storage pointer.

        @li If `*other.storage() != *this->storage()`, an
        element-wise copy is performed, which may throw.
        In this case, the moved-from string is not
        changed.

        @par Complexity
        Constant, or linear in the size of `*this` plus `s.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param s The string to move-assign from.
    */
    BOOST_JSON_DECL value& operator=(string&& s);

    /** Assignment.

        Replace `*this` with a copy of the array `arr`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @par Complexity
        Linear in the sum of sizes of `*this` and `arr`

        @param arr The new array.
    */
    BOOST_JSON_DECL value& operator=(array const& arr);

    /** Assignment.

        The contents of the value are replaced with the
        contents of `arr` using move semantics:

        @li If `*arr.storage() == *this->storage()`,
        ownership of the underlying memory is transferred
        in constant time, with no possibility of exceptions.
        After assignment, the moved-from array becomes
        empty with its current storage pointer.

        @li If `*arr.storage() != *this->storage()`, an
        element-wise copy is performed, which may throw.
        In this case, the moved-from array is not
        changed.

        @par Complexity
        Constant, or linear in the size of `*this` plus `arr.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param arr The array to move-assign from.
    */
    BOOST_JSON_DECL value& operator=(array&& arr);

    /** Assignment.

        Replace `*this` with a copy of the obect `obj`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @par Complexity
        Linear in the sum of sizes of `*this` and `obj`

        @param obj The new object.
    */
    BOOST_JSON_DECL value& operator=(object const& obj);

    /** Assignment.

        The contents of the value are replaced with the
        contents of `obj` using move semantics:

        @li If `*obj.storage() == *this->storage()`,
        ownership of the underlying memory is transferred
        in constant time, with no possibility of exceptions.
        After assignment, the moved-from object becomes
        empty with its current storage pointer.

        @li If `*obj.storage() != *this->storage()`, an
        element-wise copy is performed, which may throw.
        In this case, the moved-from object is not
        changed.

        @par Complexity
        Constant, or linear in the size of `*this` plus `obj.size()`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param obj The object to move-assign from.
    */
    BOOST_JSON_DECL value& operator=(object&& obj);

    //------------------------------------------------------
    //
    // Modifiers
    //
    //------------------------------------------------------

    /** Change the kind to null, discarding the previous contents.

        The value is replaced with a null,
        destroying the previous contents.

        @par Complexity
        Linear in the size of `*this`.

        @par Exception Safety
        No-throw guarantee.
    */
    void
    emplace_null() noexcept
    {
        *this = nullptr;
    }

    /** Return a reference to a `bool`, changing the kind and replacing the contents.

        The value is replaced with a `bool`
        initialized to `false`, destroying the
        previous contents.

        @par Complexity
        Linear in the size of `*this`.

        @par Exception Safety
        No-throw guarantee.
    */
    bool&
    emplace_bool() noexcept
    {
        *this = false;
        return sca_.b;
    }

    /** Return a reference to a `std::int64_t`, changing the kind and replacing the contents.

        The value is replaced with a `std::int64_t`
        initialized to zero, destroying the
        previous contents.

        @par Complexity
        Linear in the size of `*this`.

        @par Exception Safety
        No-throw guarantee.
    */
    std::int64_t&
    emplace_int64() noexcept
    {
        *this = std::int64_t{};
        return sca_.i;
    }

    /** Return a reference to a `std::uint64_t`, changing the kind and replacing the contents.

        The value is replaced with a `std::uint64_t`
        initialized to zero, destroying the
        previous contents.

        @par Complexity
        Linear in the size of `*this`.

        @par Exception Safety
        No-throw guarantee.
    */
    std::uint64_t&
    emplace_uint64() noexcept
    {
        *this = std::uint64_t{};
        return sca_.u;
    }

    /** Return a reference to a `double`, changing the kind and replacing the contents.

        The value is replaced with a `double`
        initialized to zero, destroying the
        previous contents.

        @par Complexity
        Linear in the size of `*this`.

        @par Exception Safety
        No-throw guarantee.
    */
    double&
    emplace_double() noexcept
    {
        *this = double{};
        return sca_.d;
    }

    /** Return a reference to a @ref string, changing the kind and replacing the contents.

        The value is replaced with an empty @ref string
        using the current memory resource, destroying the
        previous contents.

        @par Complexity
        Linear in the size of `*this`.

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    string&
    emplace_string() noexcept;

    /** Return a reference to an @ref array, changing the kind and replacing the contents.

        The value is replaced with an empty @ref array
        using the current memory resource, destroying the
        previous contents.

        @par Complexity
        Linear in the size of `*this`.

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    array&
    emplace_array() noexcept;

    /** Return a reference to an @ref object, changing the kind and replacing the contents.

        The contents are replaced with an empty @ref object
        using the current @ref memory_resource. All
        previously obtained iterators and references
        obtained beforehand are invalidated.

        @par Complexity
        Linear in the size of `*this`.

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    object&
    emplace_object() noexcept;

    /** Swap the given values.

        Exchanges the contents of this value with another
        value. Ownership of the respective @ref memory_resource
        objects is not transferred:

        @li If `*other.storage() == *this->storage()`,
        ownership of the underlying memory is swapped in
        constant time, with no possibility of exceptions.
        All iterators and references remain valid.

        @li If `*other.storage() != *this->storage()`,
        the contents are logically swapped by making copies,
        which can throw. In this case all iterators and
        references are invalidated.

        @par Complexity
        Constant or linear in the sum of the sizes of
        the values.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The value to swap with.
        If `this == &other`, this function call has no effect.
    */
    BOOST_JSON_DECL
    void
    swap(value& other);

    /** Swap the given values.

        Exchanges the contents of value `lhs` with
        another value `rhs`. Ownership of the respective
        @ref memory_resource objects is not transferred.

        @li If `*lhs.storage() == *rhs.storage()`,
        ownership of the underlying memory is swapped in
        constant time, with no possibility of exceptions.
        All iterators and references remain valid.

        @li If `*lhs.storage() != *rhs.storage`,
        the contents are logically swapped by a copy,
        which can throw. In this case all iterators and
        references are invalidated.

        @par Effects
        @code
        lhs.swap( rhs );
        @endcode

        @par Complexity
        Constant or linear in the sum of the sizes of
        the values.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param lhs The value to exchange.

        @param rhs The value to exchange.
        If `&lhs == &rhs`, this function call has no effect.

        @see @ref value::swap
    */
    friend
    void
    swap(value& lhs, value& rhs)
    {
        lhs.swap(rhs);
    }

    //------------------------------------------------------
    //
    // Observers
    //
    //------------------------------------------------------

    /** Returns the kind of this JSON value.

        This function returns the discriminating
        enumeration constant of type @ref json::kind
        corresponding to the underlying representation
        stored in the container.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    json::kind
    kind() const noexcept
    {
        return static_cast<json::kind>(
            static_cast<unsigned char>(
                sca_.k) & 0x3f);
    }

    /** Return `true` if this is an array

        This function is used to determine if the underlying
        representation is a certain kind.

        @par Effects
        @code
        return this->kind() == kind::array;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_array() const noexcept
    {
        return kind() == json::kind::array;
    }

    /** Return `true` if this is an object

        This function is used to determine if the underlying
        representation is a certain kind.

        @par Effects
        @code
        return this->kind() == kind::object;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_object() const noexcept
    {
        return kind() == json::kind::object;
    }

    /** Return `true` if this is a string

        This function is used to determine if the underlying
        representation is a certain kind.

        @par Effects
        @code
        return this->kind() == kind::string;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_string() const noexcept
    {
        return kind() == json::kind::string;
    }

    /** Return `true` if this is a signed integer

        This function is used to determine if the underlying
        representation is a certain kind.

        @par Effects
        @code
        return this->kind() == kind::int64;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_int64() const noexcept
    {
        return kind() == json::kind::int64;
    }

    /** Return `true` if this is a unsigned integer

        This function is used to determine if the underlying
        representation is a certain kind.

        @par Effects
        @code
        return this->kind() == kind::uint64;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_uint64() const noexcept
    {
        return kind() == json::kind::uint64;
    }

    /** Return `true` if this is a double

        This function is used to determine if the underlying
        representation is a certain kind.

        @par Effects
        @code
        return this->kind() == kind::double_;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_double() const noexcept
    {
        return kind() == json::kind::double_;
    }

    /** Return `true` if this is a bool

        This function is used to determine if the underlying
        representation is a certain kind.

        @par Effects
        @code
        return this->kind() == kind::bool_;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_bool() const noexcept
    {
        return kind() == json::kind::bool_;
    }

    /** Returns true if this is a null.

        This function is used to determine if the underlying
        representation is a certain kind.

        @par Effects
        @code
        return this->kind() == kind::null;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_null() const noexcept
    {
        return kind() == json::kind::null;
    }

    /** Returns true if this is an array or object.

        This function returns `true` if
        @ref kind() is either `kind::object` or
        `kind::array`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_structured() const noexcept
    {
        // VFALCO Could use bit 0x20 for this
        return
           kind() == json::kind::object ||
           kind() == json::kind::array;
    }

    /** Returns true if this is not an array or object.

        This function returns `true` if
        @ref kind() is neither `kind::object` nor
        `kind::array`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_primitive() const noexcept
    {
        // VFALCO Could use bit 0x20 for this
        return
           sca_.k != json::kind::object &&
           sca_.k != json::kind::array;
    }

    /** Returns true if this is a number.

        This function returns `true` when
        @ref kind() is one of the following values:
        `kind::int64`, `kind::uint64`, or
        `kind::double_`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    is_number() const noexcept
    {
        // VFALCO Could use bit 0x40 for this
        return
            kind() == json::kind::int64 ||
            kind() == json::kind::uint64 ||
            kind() == json::kind::double_;
    }

    //------------------------------------------------------

    /** Return an @ref array pointer if this is an array, else return `nullptr`

        If `this->kind() == kind::array`, returns a pointer
        to the underlying array. Otherwise, returns `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_array() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    array const*
    if_array() const noexcept
    {
        if(kind() == json::kind::array)
            return &arr_;
        return nullptr;
    }

    /** Return an @ref array pointer if this is an array, else return `nullptr`

        If `this->kind() == kind::array`, returns a pointer
        to the underlying array. Otherwise, returns `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_array() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    array*
    if_array() noexcept
    {
        if(kind() == json::kind::array)
            return &arr_;
        return nullptr;
    }

    /** Return an @ref object pointer if this is an object, else return `nullptr`

        If `this->kind() == kind::object`, returns a pointer
        to the underlying object. Otherwise, returns `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_object() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    object const*
    if_object() const noexcept
    {
        if(kind() == json::kind::object)
            return &obj_;
        return nullptr;
    }

    /** Return an @ref object pointer if this is an object, else return `nullptr`

        If `this->kind() == kind::object`, returns a pointer
        to the underlying object. Otherwise, returns `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_object() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    object*
    if_object() noexcept
    {
        if(kind() == json::kind::object)
            return &obj_;
        return nullptr;
    }

    /** Return a @ref string pointer if this is a string, else return `nullptr`

        If `this->kind() == kind::string`, returns a pointer
        to the underlying object. Otherwise, returns `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_string() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    string const*
    if_string() const noexcept
    {
        if(kind() == json::kind::string)
            return &str_;
        return nullptr;
    }

    /** Return a @ref string pointer if this is a string, else return `nullptr`

        If `this->kind() == kind::string`, returns a pointer
        to the underlying object. Otherwise, returns `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_string() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    string*
    if_string() noexcept
    {
        if(kind() == json::kind::string)
            return &str_;
        return nullptr;
    }

    /** Return an `int64_t` pointer if this is a signed integer, else return `nullptr`

        If `this->kind() == kind::int64`, returns a pointer
        to the underlying integer. Otherwise, returns `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_int64() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    std::int64_t const*
    if_int64() const noexcept
    {
        if(kind() == json::kind::int64)
            return &sca_.i;
        return nullptr;
    }

    /** Return an `int64_t` pointer if this is a signed integer, else return `nullptr`

        If `this->kind() == kind::int64`, returns a pointer
        to the underlying integer. Otherwise, returns `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_int64() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    std::int64_t*
    if_int64() noexcept
    {
        if(kind() == json::kind::int64)
            return &sca_.i;
        return nullptr;
    }

    /** Return a `uint64_t` pointer if this is an unsigned integer, else return `nullptr`

        If `this->kind() == kind::uint64`, returns a pointer
        to the underlying unsigned integer. Otherwise, returns
        `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_uint64() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    std::uint64_t const*
    if_uint64() const noexcept
    {
        if(kind() == json::kind::uint64)
            return &sca_.u;
        return nullptr;
    }

    /** Return a `uint64_t` pointer if this is an unsigned integer, else return `nullptr`

        If `this->kind() == kind::uint64`, returns a pointer
        to the underlying unsigned integer. Otherwise, returns
        `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_uint64() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    std::uint64_t*
    if_uint64() noexcept
    {
        if(kind() == json::kind::uint64)
            return &sca_.u;
        return nullptr;
    }

    /** Return a `double` pointer if this is a double, else return `nullptr`

        If `this->kind() == kind::double_`, returns a pointer
        to the underlying double. Otherwise, returns
        `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_double() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    double const*
    if_double() const noexcept
    {
        if(kind() == json::kind::double_)
            return &sca_.d;
        return nullptr;
    }

    /** Return a `double` pointer if this is a double, else return `nullptr`

        If `this->kind() == kind::double_`, returns a pointer
        to the underlying double. Otherwise, returns
        `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_double() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    double*
    if_double() noexcept
    {
        if(kind() == json::kind::double_)
            return &sca_.d;
        return nullptr;
    }

    /** Return a `bool` pointer if this is a boolean, else return `nullptr`

        If `this->kind() == kind::bool_`, returns a pointer
        to the underlying boolean. Otherwise, returns
        `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_bool() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool const*
    if_bool() const noexcept
    {
        if(kind() == json::kind::bool_)
            return &sca_.b;
        return nullptr;
    }

    /** Return a `bool` pointer if this is a boolean, else return `nullptr`

        If `this->kind() == kind::bool_`, returns a pointer
        to the underlying boolean. Otherwise, returns
        `nullptr`.

        @par Example
        The return value is used in both a boolean context and
        to assign a variable:
        @code
        if( auto p = jv.if_bool() )
            return *p;
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool*
    if_bool() noexcept
    {
        if(kind() == json::kind::bool_)
            return &sca_.b;
        return nullptr;
    }

    //------------------------------------------------------

    /** Return the stored number cast to an arithmetic type.

        This function attempts to return the stored value
        converted to the arithmetic type `T` which may not
        be `bool`:

        @li If `T` is an integral type and the stored
        value is a number which can be losslessly converted,
        the conversion is performed without error and the
        converted number is returned.

        @li If `T` is an integral type and the stored value
        is a number which cannot be losslessly converted,
        then the operation fails with an error.

        @li If `T` is a floating point type and the stored
        value is a number, the conversion is performed
        without error. The converted number is returned,
        with a possible loss of precision.

        @li Otherwise, if the stored value is not a number;
        that is, if `this->is_number()` returns `false`, then
        the operation fails with an error.

        @par Constraints
        @code
        std::is_arithmetic< T >::value && ! std::is_same< T, bool >::value
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @return The converted number.

        @param ec Set to the error, if any occurred.
    */
/** @{ */
    template<class T>
#ifdef BOOST_JSON_DOCS
    T
#else
    typename std::enable_if<
        std::is_arithmetic<T>::value &&
        ! std::is_same<T, bool>::value,
            T>::type
#endif
    to_number(error_code& ec) const noexcept
    {
        error e;
        auto result = to_number<T>(e);
        BOOST_STATIC_CONSTEXPR source_location loc = BOOST_JSON_SOURCE_POS;
        BOOST_JSON_ASSIGN_ERROR_CODE(ec, e, &loc);
        return result;
    }

    template<class T>
#ifdef BOOST_JSON_DOCS
    T
#else
    typename std::enable_if<
        std::is_arithmetic<T>::value &&
        ! std::is_same<T, bool>::value,
            T>::type
#endif
    to_number(std::error_code& ec) const noexcept
    {
        error_code jec;
        auto result = to_number<T>(jec);
        ec = jec;
        return result;
    }
/** @} */

    /** Return the stored number cast to an arithmetic type.

        This function attempts to return the stored value
        converted to the arithmetic type `T` which may not
        be `bool`:

        @li If `T` is an integral type and the stored
        value is a number which can be losslessly converted,
        the conversion is performed without error and the
        converted number is returned.

        @li If `T` is an integral type and the stored value
        is a number which cannot be losslessly converted,
        then the operation fails with an error.

        @li If `T` is a floating point type and the stored
        value is a number, the conversion is performed
        without error. The converted number is returned,
        with a possible loss of precision.

        @li Otherwise, if the stored value is not a number;
        that is, if `this->is_number()` returns `false`, then
        the operation fails with an error.

        @par Constraints
        @code
        std::is_arithmetic< T >::value && ! std::is_same< T, bool >::value
        @endcode

        @par Complexity
        Constant.

        @return The converted number.

        @throw system_error on error.
    */
    template<class T>
#ifdef BOOST_JSON_DOCS
    T
#else
    typename std::enable_if<
        std::is_arithmetic<T>::value &&
        ! std::is_same<T, bool>::value,
            T>::type
#endif
    to_number() const
    {
        error_code ec;
        auto result = to_number<T>(ec);
        if(ec)
            detail::throw_system_error(ec, BOOST_JSON_SOURCE_POS);
        return result;
    }

    //------------------------------------------------------
    //
    // Accessors
    //
    //------------------------------------------------------

    /** Return the memory resource associated with the value.

        This returns a pointer to the memory resource
        that was used to construct the value.

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

    /** Return a reference to the underlying `object`, or throw an exception.

        If @ref is_object() is `true`, returns
        a reference to the underlying @ref object,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_object()`
    */
    object&
    as_object()
    {
        if(! is_object())
            detail::throw_invalid_argument(
                "not an object",
                BOOST_JSON_SOURCE_POS);
        return obj_;
    }

    /** Return a reference to the underlying `object`, or throw an exception.

        If @ref is_object() is `true`, returns
        a reference to the underlying @ref object,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_object()`
    */
    object const&
    as_object() const
    {
        if(! is_object())
            detail::throw_invalid_argument(
                "not an object",
                BOOST_JSON_SOURCE_POS);
        return obj_;
    }

    /** Return a reference to the underlying @ref array, or throw an exception.

        If @ref is_array() is `true`, returns
        a reference to the underlying @ref array,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_array()`
    */
    array&
    as_array()
    {
        if(! is_array())
            detail::throw_invalid_argument(
                "array required",
                BOOST_JSON_SOURCE_POS);
        return arr_;
    }

    /** Return a reference to the underlying `array`, or throw an exception.

        If @ref is_array() is `true`, returns
        a reference to the underlying @ref array,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_array()`
    */
    array const&
    as_array() const
    {
        if(! is_array())
            detail::throw_invalid_argument(
                "array required",
                BOOST_JSON_SOURCE_POS);
        return arr_;
    }

    /** Return a reference to the underlying `string`, or throw an exception.

        If @ref is_string() is `true`, returns
        a reference to the underlying @ref string,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_string()`
    */
    string&
    as_string()
    {
        if(! is_string())
            detail::throw_invalid_argument(
                "not a string",
                BOOST_JSON_SOURCE_POS);
        return str_;
    }

    /** Return a reference to the underlying `string`, or throw an exception.

        If @ref is_string() is `true`, returns
        a reference to the underlying @ref string,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_string()`
    */
    string const&
    as_string() const
    {
        if(! is_string())
            detail::throw_invalid_argument(
                "not a string",
                BOOST_JSON_SOURCE_POS);
        return str_;
    }

    /** Return a reference to the underlying `std::int64_t`, or throw an exception.

        If @ref is_int64() is `true`, returns
        a reference to the underlying `std::int64_t`,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_int64()`
    */
    std::int64_t&
    as_int64()
    {
        if(! is_int64())
            detail::throw_invalid_argument(
                "not an int64",
                BOOST_JSON_SOURCE_POS);
        return sca_.i;
    }

    /** Return the underlying `std::int64_t`, or throw an exception.

        If @ref is_int64() is `true`, returns
        the underlying `std::int64_t`,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_int64()`
    */
    std::int64_t
    as_int64() const
    {
        if(! is_int64())
            detail::throw_invalid_argument(
                "not an int64",
                BOOST_JSON_SOURCE_POS);
        return sca_.i;
    }

    /** Return a reference to the underlying `std::uint64_t`, or throw an exception.

        If @ref is_uint64() is `true`, returns
        a reference to the underlying `std::uint64_t`,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_uint64()`
    */
    std::uint64_t&
    as_uint64()
    {
        if(! is_uint64())
            detail::throw_invalid_argument(
                "not a uint64",
                BOOST_JSON_SOURCE_POS);
        return sca_.u;
    }

    /** Return the underlying `std::uint64_t`, or throw an exception.

        If @ref is_int64() is `true`, returns
        the underlying `std::uint64_t`,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::length_error `! this->is_uint64()`
    */
    std::uint64_t
    as_uint64() const
    {
        if(! is_uint64())
            detail::throw_invalid_argument(
                "not a uint64",
                BOOST_JSON_SOURCE_POS);
        return sca_.u;
    }

    /** Return a reference to the underlying `double`, or throw an exception.

        If @ref is_double() is `true`, returns
        a reference to the underlying `double`,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_double()`
    */
    double&
    as_double()
    {
        if(! is_double())
            detail::throw_invalid_argument(
                "not a double",
                BOOST_JSON_SOURCE_POS);
        return sca_.d;
    }

    /** Return the underlying `double`, or throw an exception.

        If @ref is_int64() is `true`, returns
        the underlying `double`,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_double()`
    */
    double
    as_double() const
    {
        if(! is_double())
            detail::throw_invalid_argument(
                "not a double",
                BOOST_JSON_SOURCE_POS);
        return sca_.d;
    }

    /** Return a reference to the underlying `bool`, or throw an exception.

        If @ref is_bool() is `true`, returns
        a reference to the underlying `bool`,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_bool()`
    */
    bool&
    as_bool()
    {
        if(! is_bool())
            detail::throw_invalid_argument(
                "bool required",
                BOOST_JSON_SOURCE_POS);
        return sca_.b;
    }

    /** Return the underlying `bool`, or throw an exception.

        If @ref is_bool() is `true`, returns
        the underlying `bool`,
        otherwise throws an exception.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @throw std::invalid_argument `! this->is_bool()`
    */
    bool
    as_bool() const
    {
        if(! is_bool())
            detail::throw_invalid_argument(
                "bool required",
                BOOST_JSON_SOURCE_POS);
        return sca_.b;
    }

    //------------------------------------------------------

    /** Return a reference to the underlying `object`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_object()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    object&
    get_object() noexcept
    {
        BOOST_ASSERT(is_object());
        return obj_;
    }

    /** Return a reference to the underlying `object`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_object()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    object const&
    get_object() const noexcept
    {
        BOOST_ASSERT(is_object());
        return obj_;
    }

    /** Return a reference to the underlying `array`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_array()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    array&
    get_array() noexcept
    {
        BOOST_ASSERT(is_array());
        return arr_;
    }

    /** Return a reference to the underlying `array`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_array()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    array const&
    get_array() const noexcept
    {
        BOOST_ASSERT(is_array());
        return arr_;
    }

    /** Return a reference to the underlying `string`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_string()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    string&
    get_string() noexcept
    {
        BOOST_ASSERT(is_string());
        return str_;
    }

    /** Return a reference to the underlying `string`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_string()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    string const&
    get_string() const noexcept
    {
        BOOST_ASSERT(is_string());
        return str_;
    }

    /** Return a reference to the underlying `std::int64_t`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_int64()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    std::int64_t&
    get_int64() noexcept
    {
        BOOST_ASSERT(is_int64());
        return sca_.i;
    }

    /** Return the underlying `std::int64_t`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_int64()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    std::int64_t
    get_int64() const noexcept
    {
        BOOST_ASSERT(is_int64());
        return sca_.i;
    }

    /** Return a reference to the underlying `std::uint64_t`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_uint64()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    std::uint64_t&
    get_uint64() noexcept
    {
        BOOST_ASSERT(is_uint64());
        return sca_.u;
    }

    /** Return the underlying `std::uint64_t`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_uint64()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    std::uint64_t
    get_uint64() const noexcept
    {
        BOOST_ASSERT(is_uint64());
        return sca_.u;
    }

    /** Return a reference to the underlying `double`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_double()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    double&
    get_double() noexcept
    {
        BOOST_ASSERT(is_double());
        return sca_.d;
    }

    /** Return the underlying `double`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_double()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    double
    get_double() const noexcept
    {
        BOOST_ASSERT(is_double());
        return sca_.d;
    }

    /** Return a reference to the underlying `bool`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_bool()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool&
    get_bool() noexcept
    {
        BOOST_ASSERT(is_bool());
        return sca_.b;
    }

    /** Return the underlying `bool`, without checking.

        This is the fastest way to access the underlying
        representation when the kind is known in advance.

        @par Preconditions

        @code
        this->is_bool()
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    get_bool() const noexcept
    {
        BOOST_ASSERT(is_bool());
        return sca_.b;
    }

    //------------------------------------------------------

    /** Access an element, with bounds checking.

        This function is used to access elements of
        the underlying object, or throw an exception
        if the value is not an object.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @param key The key of the element to find.

        @return `this->as_object().at( key )`.
    */
    value const&
    at(string_view key) const
    {
        return as_object().at(key);
    }

    /** Access an element, with bounds checking.

        This function is used to access elements of
        the underlying array, or throw an exception
        if the value is not an array.

        @par Complexity
        Constant.

        @par Exception Safety
        Strong guarantee.

        @param pos A zero-based array index.

        @return `this->as_array().at( pos )`.
    */
    value const&
    at(std::size_t pos) const
    {
        return as_array().at(pos);
    }

    /** Access an element via JSON Pointer.

        This function is used to access a (potentially nested)
        element of the value using a JSON Pointer string.

        @par Complexity
        Linear in the sizes of `ptr` and underlying array, object, or string.

        @par Exception Safety
        Strong guarantee.

        @param ptr JSON Pointer string.

        @return reference to the element identified by `ptr`.

        @throw system_error if an error occurs.

        @see
        <a href="https://datatracker.ietf.org/doc/html/rfc6901">
            RFC 6901 - JavaScript Object Notation (JSON) Pointer</a>
    */
/** @{ */
    BOOST_JSON_DECL
    value const&
    at_pointer(string_view ptr) const;

    BOOST_JSON_DECL
    value&
    at_pointer(string_view ptr);
/** @} */

    /** Access an element via JSON Pointer.

        This function is used to access a (potentially nested)
        element of the value using a JSON Pointer string.

        @par Complexity
        Linear in the sizes of `ptr` and underlying array, object, or string.

        @par Exception Safety
        No-throw guarantee.

        @param ptr JSON Pointer string.

        @param ec Set to the error, if any occurred.

        @return pointer to the element identified by `ptr`.

        @see
        <a href="https://datatracker.ietf.org/doc/html/rfc6901">
            RFC 6901 - JavaScript Object Notation (JSON) Pointer</a>
    */
/** @{ */
    BOOST_JSON_DECL
    value const*
    find_pointer(string_view ptr, error_code& ec) const noexcept;

    BOOST_JSON_DECL
    value*
    find_pointer(string_view ptr, error_code& ec) noexcept;

    BOOST_JSON_DECL
    value const*
    find_pointer(string_view ptr, std::error_code& ec) const noexcept;

    BOOST_JSON_DECL
    value*
    find_pointer(string_view ptr, std::error_code& ec) noexcept;
/** @} */

    /** Return `true` if two values are equal.

        Two values are equal when they are the
        same kind and their referenced values
        are equal, or when they are both integral
        types and their integral representations
        are equal.

        @par Complexity
        Constant or linear in the size of
        the array, object, or string.

        @par Exception Safety
        No-throw guarantee.
    */
    // inline friend speeds up overload resolution
    friend
    bool
    operator==(
        value const& lhs,
        value const& rhs) noexcept
    {
        return lhs.equal(rhs);
    }

    /** Return `true` if two values are not equal.

        Two values are equal when they are the
        same kind and their referenced values
        are equal, or when they are both integral
        types and their integral representations
        are equal.

        @par Complexity
        Constant or linear in the size of
        the array, object, or string.

        @par Exception Safety
        No-throw guarantee.
    */
    friend
    bool
    operator!=(
        value const& lhs,
        value const& rhs) noexcept
    {
        return ! (lhs == rhs);
    }

private:
    static
    void
    relocate(
        value* dest,
        value const& src) noexcept
    {
        std::memcpy(
            static_cast<void*>(dest),
            &src,
            sizeof(src));
    }

    BOOST_JSON_DECL
    storage_ptr
    destroy() noexcept;

    BOOST_JSON_DECL
    bool
    equal(value const& other) const noexcept;

    template<class T>
    auto
    to_number(error& e) const noexcept ->
        typename std::enable_if<
            std::is_signed<T>::value &&
            ! std::is_floating_point<T>::value,
                T>::type
    {
        if(sca_.k == json::kind::int64)
        {
            auto const i = sca_.i;
            if( i >= (std::numeric_limits<T>::min)() &&
                i <= (std::numeric_limits<T>::max)())
            {
                e = {};
                return static_cast<T>(i);
            }
            e = error::not_exact;
        }
        else if(sca_.k == json::kind::uint64)
        {
            auto const u = sca_.u;
            if(u <= static_cast<std::uint64_t>((
                std::numeric_limits<T>::max)()))
            {
                e = {};
                return static_cast<T>(u);
            }
            e = error::not_exact;
        }
        else if(sca_.k == json::kind::double_)
        {
            auto const d = sca_.d;
            if( d >= static_cast<double>(
                    (detail::to_number_limit<T>::min)()) &&
                d <= static_cast<double>(
                    (detail::to_number_limit<T>::max)()) &&
                static_cast<T>(d) == d)
            {
                e = {};
                return static_cast<T>(d);
            }
            e = error::not_exact;
        }
        else
        {
            e = error::not_number;
        }
        return T{};
    }

    template<class T>
    auto
    to_number(error& e) const noexcept ->
        typename std::enable_if<
            std::is_unsigned<T>::value &&
            ! std::is_same<T, bool>::value,
                T>::type
    {
        if(sca_.k == json::kind::int64)
        {
            auto const i = sca_.i;
            if( i >= 0 && static_cast<std::uint64_t>(i) <=
                (std::numeric_limits<T>::max)())
            {
                e = {};
                return static_cast<T>(i);
            }
            e = error::not_exact;
        }
        else if(sca_.k == json::kind::uint64)
        {
            auto const u = sca_.u;
            if(u <= (std::numeric_limits<T>::max)())
            {
                e = {};
                return static_cast<T>(u);
            }
            e = error::not_exact;
        }
        else if(sca_.k == json::kind::double_)
        {
            auto const d = sca_.d;
            if( d >= 0 &&
                d <= (detail::to_number_limit<T>::max)() &&
                static_cast<T>(d) == d)
            {
                e = {};
                return static_cast<T>(d);
            }
            e = error::not_exact;
        }
        else
        {
            e = error::not_number;
        }
        return T{};
    }

    template<class T>
    auto
    to_number(error& e) const noexcept ->
        typename std::enable_if<
            std::is_floating_point<
                T>::value, T>::type
    {
        if(sca_.k == json::kind::int64)
        {
            e = {};
            return static_cast<T>(sca_.i);
        }
        if(sca_.k == json::kind::uint64)
        {
            e = {};
            return static_cast<T>(sca_.u);
        }
        if(sca_.k == json::kind::double_)
        {
            e = {};
            return static_cast<T>(sca_.d);
        }
        e = error::not_number;
        return {};
    }
};

// Make sure things are as big as we think they should be
#if BOOST_JSON_ARCH == 64
BOOST_STATIC_ASSERT(sizeof(value) == 24);
#elif BOOST_JSON_ARCH == 32
BOOST_STATIC_ASSERT(sizeof(value) == 16);
#else
# error Unknown architecture
#endif

//----------------------------------------------------------

/** A key/value pair.

    This is the type of element used by the @ref object
    container.
*/
class key_value_pair
{
#ifndef BOOST_JSON_DOCS
    friend struct detail::access;
    using access = detail::access;
#endif

    BOOST_JSON_DECL
    static char const empty_[1];

    inline
    key_value_pair(
        pilfered<json::value> k,
        pilfered<json::value> v) noexcept;

public:
    /// Copy assignment (deleted).
    key_value_pair&
    operator=(key_value_pair const&) = delete;

    /** Destructor.

        The value is destroyed and all internally
        allocated memory is freed.
    */
    ~key_value_pair() noexcept
    {
        auto const& sp = value_.storage();
        if(sp.is_not_shared_and_deallocate_is_trivial())
            return;
        if(key_ == empty_)
            return;
        sp->deallocate(const_cast<char*>(key_),
            len_ + 1, alignof(char));
    }

    /** Copy constructor.

        This constructs a key/value pair with a
        copy of another key/value pair, using
        the same memory resource as `other`.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The key/value pair to copy.
    */
    key_value_pair(
        key_value_pair const& other)
        : key_value_pair(other,
            other.storage())
    {
    }

    /** Copy constructor.

        This constructs a key/value pair with a
        copy of another key/value pair, using
        the specified memory resource.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param other The key/value pair to copy.

        @param sp A pointer to the @ref memory_resource
        to use. The element will acquire shared
        ownership of the memory resource.
    */
    BOOST_JSON_DECL
    key_value_pair(
        key_value_pair const& other,
        storage_ptr sp);

    /** Move constructor.

        The pair is constructed by acquiring
        ownership of the contents of `other` and
        shared ownership of `other`'s memory resource.

        @note

        After construction, the moved-from pair holds an
        empty key, and a null value with its current
        storage pointer.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param other The pair to move.
    */
    key_value_pair(
        key_value_pair&& other) noexcept
        : value_(std::move(other.value_))
        , key_(detail::exchange(
            other.key_, empty_))
        , len_(detail::exchange(
            other.len_, 0))
    {
    }

    /** Pilfer constructor.

        The pair is constructed by acquiring ownership
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
    key_value_pair(
        pilfered<key_value_pair> other) noexcept
        : value_(pilfer(other.get().value_))
        , key_(detail::exchange(
            other.get().key_, empty_))
        , len_(detail::exchange(
            other.get().len_, 0))
    {
    }

    /** Constructor.

        This constructs a key/value pair.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param key The key string to use.

        @param args Optional arguments forwarded to
        the @ref value constructor.
    */
    template<class... Args>
    explicit
    key_value_pair(
        string_view key,
        Args&&... args)
        : value_(std::forward<Args>(args)...)
    {
        if(key.size() > string::max_size())
            detail::throw_length_error(
                "key too large",
                BOOST_JSON_SOURCE_POS);
        auto s = reinterpret_cast<
            char*>(value_.storage()->
                allocate(key.size() + 1, alignof(char)));
        std::memcpy(s, key.data(), key.size());
        s[key.size()] = 0;
        key_ = s;
        len_ = static_cast<
            std::uint32_t>(key.size());
    }

    /** Constructor.

        This constructs a key/value pair. A
        copy of the specified value is made,
        using the specified memory resource.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param p A `std::pair` with the key
            string and @ref value to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The element will acquire shared
        ownership of the memory resource.
    */
    explicit
    key_value_pair(
        std::pair<
            string_view,
            json::value> const& p,
        storage_ptr sp = {})
        : key_value_pair(
            p.first,
            p.second,
            std::move(sp))
    {
    }

    /** Constructor.

        This constructs a key/value pair.
        Ownership of the specified value is
        transferred by move construction.

        @par Exception Safety
        Strong guarantee.
        Calls to `memory_resource::allocate` may throw.

        @param p A `std::pair` with the key
            string and @ref value to construct with.

        @param sp A pointer to the @ref memory_resource
        to use. The element will acquire shared
        ownership of the memory resource.
    */
    explicit
    key_value_pair(
        std::pair<
            string_view,
            json::value>&& p,
        storage_ptr sp = {})
        : key_value_pair(
            p.first,
            std::move(p).second,
            std::move(sp))
    {
    }

    /** Return the associated memory resource.

        This returns a pointer to the memory
        resource used to construct the value.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    storage_ptr const&
    storage() const noexcept
    {
        return value_.storage();
    }

    /** Return the key of this element.

        After construction, the key may
        not be modified.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    string_view const
    key() const noexcept
    {
        return { key_, len_ };
    }

    /** Return the key of this element as a null-terminated string.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    char const*
    key_c_str() const noexcept
    {
        return key_;
    }

    /** Return the value of this element.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    json::value const&
    value() const noexcept
    {
        return value_;
    }

    /** Return the value of this element.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    json::value&
    value() noexcept
    {
        return value_;
    }

private:
    json::value value_;
    char const* key_;
    std::uint32_t len_;
    std::uint32_t next_;
};

//----------------------------------------------------------

#ifdef BOOST_JSON_DOCS

/** Tuple-like element access.

    This overload permits the key and value
    of a `key_value_pair` to be accessed
    by index. For example:

    @code

    key_value_pair kvp("num", 42);

    string_view key = get<0>(kvp);
    value& jv = get<1>(kvp);

    @endcode

    @par Structured Bindings

    When using C++17 or greater, objects of type
    @ref key_value_pair may be used to initialize
    structured bindings:

    @code

    key_value_pair kvp("num", 42);

    auto& [key, value] = kvp;

    @endcode

    Depending on the value of `I`, the return type will be:

    @li `string_view const` if `I == 0`, or

    @li `value&`, `value const&`, or `value&&` if `I == 1`.

    Any other value for `I` is ill-formed.

    @tparam I The element index to access.

    @par Constraints

    `std::is_same_v< std::remove_cvref_t<T>, key_value_pair >`

    @return `kvp.key()` if `I == 0`, or `kvp.value()`
    if `I == 1`.

    @param kvp The @ref key_value_pair object
    to access.
*/
template<
    std::size_t I,
    class T>
__see_below__
get(T&& kvp) noexcept;

#else

template<std::size_t I>
auto
get(key_value_pair const&) noexcept ->
    typename std::conditional<I == 0,
        string_view const,
        value const&>::type
{
    static_assert(I == 0,
        "key_value_pair index out of range");
}

template<std::size_t I>
auto
get(key_value_pair&) noexcept ->
    typename std::conditional<I == 0,
        string_view const,
        value&>::type
{
    static_assert(I == 0,
        "key_value_pair index out of range");
}

template<std::size_t I>
auto
get(key_value_pair&&) noexcept ->
    typename std::conditional<I == 0,
        string_view const,
        value&&>::type
{
    static_assert(I == 0,
        "key_value_pair index out of range");
}

/** Extracts a key_value_pair's key using tuple-like interface
*/
template<>
inline
string_view const
get<0>(key_value_pair const& kvp) noexcept
{
    return kvp.key();
}

/** Extracts a key_value_pair's key using tuple-like interface
*/
template<>
inline
string_view const
get<0>(key_value_pair& kvp) noexcept
{
    return kvp.key();
}

/** Extracts a key_value_pair's key using tuple-like interface
*/
template<>
inline
string_view const
get<0>(key_value_pair&& kvp) noexcept
{
    return kvp.key();
}

/** Extracts a key_value_pair's value using tuple-like interface
*/
template<>
inline
value const&
get<1>(key_value_pair const& kvp) noexcept
{
    return kvp.value();
}

/** Extracts a key_value_pair's value using tuple-like interface
*/
template<>
inline
value&
get<1>(key_value_pair& kvp) noexcept
{
    return kvp.value();
}

/** Extracts a key_value_pair's value using tuple-like interface
*/
template<>
inline
value&&
get<1>(key_value_pair&& kvp) noexcept
{
    return std::move(kvp.value());
}

#endif

BOOST_JSON_NS_END

#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wmismatched-tags"
#endif

#ifndef BOOST_JSON_DOCS

namespace std {

/** Tuple-like size access for key_value_pair
*/
template<>
struct tuple_size< ::boost::json::key_value_pair >
    : std::integral_constant<std::size_t, 2>
{
};

/** Tuple-like access for the key type of key_value_pair
*/
template<>
struct tuple_element<0, ::boost::json::key_value_pair>
{
    using type = ::boost::json::string_view const;
};

/** Tuple-like access for the value type of key_value_pair
*/
template<>
struct tuple_element<1, ::boost::json::key_value_pair>
{
    using type = ::boost::json::value&;
};

/** Tuple-like access for the value type of key_value_pair
*/
template<>
struct tuple_element<1, ::boost::json::key_value_pair const>
{
    using type = ::boost::json::value const&;
};

} // std

#endif

// std::hash specialization
#ifndef BOOST_JSON_DOCS
namespace std {
template <>
struct hash< ::boost::json::value > {
    BOOST_JSON_DECL
    std::size_t
    operator()(::boost::json::value const& jv) const noexcept;
};
} // std
#endif


#ifdef __clang__
# pragma clang diagnostic pop
#endif

// These are here because value, array,
// and object form cyclic references.

#include <boost/json/detail/impl/array.hpp>
#include <boost/json/impl/array.hpp>
#include <boost/json/impl/object.hpp>

// These must come after array and object
#include <boost/json/impl/value_ref.hpp>

#endif

/* value.hpp
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
*/