//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_MONOTONIC_RESOURCE_HPP
#define BOOST_JSON_MONOTONIC_RESOURCE_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/memory_resource.hpp>
#include <boost/json/storage_ptr.hpp>
#include <cstddef>
#include <utility>

BOOST_JSON_NS_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251) // class needs to have dll-interface to be used by clients of class
#pragma warning(disable: 4275) // non dll-interface class used as base for dll-interface class
#endif

//----------------------------------------------------------

/** A dynamically allocating resource with a trivial deallocate

    This memory resource is a special-purpose resource
    that releases allocated memory only when the resource
    is destroyed (or when @ref release is called).
    It has a trivial deallocate function; that is, the
    metafunction @ref is_deallocate_trivial returns `true`.
\n
    The resource can be constructed with an initial buffer.
    If there is no initial buffer, or if the buffer is
    exhausted, subsequent dynamic allocations are made from
    the system heap. The size of buffers obtained in this
    fashion follow a geometric progression.
\n
    The purpose of this resource is to optimize the use
    case for performing many allocations, followed by
    deallocating everything at once. This is precisely the
    pattern of memory allocation which occurs when parsing:
    allocation is performed for each parsed element, and
    when the the resulting @ref value is no longer needed,
    the entire structure is destroyed. However, it is not
    suited for modifying the value after parsing is
    complete; reallocations waste memory, since the
    older buffer is not reclaimed until the resource
    is destroyed.

    @par Example

    This parses a JSON into a value which uses a local
    stack buffer, then prints the result.

    @code

    unsigned char buf[ 4000 ];
    monotonic_resource mr( buf );

    // Parse the string, using our memory resource
    auto const jv = parse( "[1,2,3]", &mr );

    // Print the JSON
    std::cout << jv;

    @endcode

    @note The total amount of memory dynamically
    allocated is monotonically increasing; That is,
    it never decreases.

    @par Thread Safety
    Members of the same instance may not be
    called concurrently.

    @see
        https://en.wikipedia.org/wiki/Region-based_memory_management
*/
class BOOST_JSON_CLASS_DECL
    monotonic_resource final
    : public memory_resource
{
    struct block;
    struct block_base
    {
        void* p;
        std::size_t avail;
        std::size_t size;
        block_base* next;
    };

    block_base buffer_;
    block_base* head_ = &buffer_;
    std::size_t next_size_ = 1024;
    storage_ptr upstream_;

    static constexpr std::size_t min_size_ = 1024;
    inline static constexpr std::size_t max_size();
    inline static std::size_t round_pow2(
        std::size_t n) noexcept;
    inline static std::size_t next_pow2(
        std::size_t n) noexcept;

public:
    /// Copy constructor (deleted)
    monotonic_resource(
        monotonic_resource const&) = delete;

    /// Copy assignment (deleted)
    monotonic_resource& operator=(
        monotonic_resource const&) = delete;

    /** Destructor

        Deallocates all the memory owned by this resource.

        @par Effects
        @code
        this->release();
        @endcode

        @par Complexity
        Linear in the number of deallocations performed.

        @par Exception Safety
        No-throw guarantee.
    */
    ~monotonic_resource();

    /** Constructor

        This constructs the resource and indicates
        that the first internal dynamic allocation
        shall be at least `initial_size` bytes.
    \n
        This constructor is guaranteed not to perform
        any dynamic allocations.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param initial_size The size of the first
        internal dynamic allocation. If this is lower
        than the implementation-defined lower limit, then
        the lower limit is used instead.

        @param upstream An optional upstream memory resource
        to use for performing internal dynamic allocations.
        If this parameter is omitted, the default resource
        is used.
    */
    explicit
    monotonic_resource(
        std::size_t initial_size = 1024,
        storage_ptr upstream = {}) noexcept;

    /** Constructor

        This constructs the resource and indicates that
        subsequent allocations should use the specified
        caller-owned buffer.
        When this buffer is exhausted, dynamic allocations
        from the upstream resource are made.
    \n
        This constructor is guaranteed not to perform
        any dynamic allocations.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param buffer The buffer to use.
        Ownership is not transferred; the caller is
        responsible for ensuring that the lifetime of
        the buffer extends until the resource is destroyed.

        @param size The number of valid bytes pointed
        to by `buffer`.

        @param upstream An optional upstream memory resource
        to use for performing internal dynamic allocations.
        If this parameter is omitted, the default resource
        is used.
    */
    /** @{ */
    monotonic_resource(
        unsigned char* buffer,
        std::size_t size,
        storage_ptr upstream = {}) noexcept;

#if defined(__cpp_lib_byte) || defined(BOOST_JSON_DOCS)
    monotonic_resource(
        std::byte* buffer,
        std::size_t size,
        storage_ptr upstream) noexcept
        : monotonic_resource(reinterpret_cast<
            unsigned char*>(buffer), size,
                std::move(upstream))
    {
    }
#endif
    /** @} */

    /** Constructor

        This constructs the resource and indicates that
        subsequent allocations should use the specified
        caller-owned buffer.
        When this buffer is exhausted, dynamic allocations
        from the upstream resource are made.
    \n
        This constructor is guaranteed not to perform
        any dynamic allocations.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param buffer The buffer to use.
        Ownership is not transferred; the caller is
        responsible for ensuring that the lifetime of
        the buffer extends until the resource is destroyed.

        @param upstream An optional upstream memory resource
        to use for performing internal dynamic allocations.
        If this parameter is omitted, the default resource
        is used.
    */
    /** @{ */
    template<std::size_t N>
    explicit
    monotonic_resource(
        unsigned char(&buffer)[N],
        storage_ptr upstream = {}) noexcept
        : monotonic_resource(&buffer[0],
            N, std::move(upstream))
    {
    }

#if defined(__cpp_lib_byte) || defined(BOOST_JSON_DOCS)
    template<std::size_t N>
    explicit
    monotonic_resource(
        std::byte(&buffer)[N],
        storage_ptr upstream = {}) noexcept
        : monotonic_resource(&buffer[0],
            N, std::move(upstream))
    {
    }
#endif
    /** @} */

#ifndef BOOST_JSON_DOCS
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    monotonic_resource(
        unsigned char(&buffer)[N],
        std::size_t n,
        storage_ptr upstream = {}) noexcept
        : monotonic_resource(&buffer[0],
            n, std::move(upstream))
    {
        // If this goes off, check your parameters
        // closely, chances are you passed an array
        // thinking it was a pointer.
        BOOST_ASSERT(n <= N);
    }

#ifdef __cpp_lib_byte
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    monotonic_resource(
        std::byte(&buffer)[N],
        std::size_t n,
        storage_ptr upstream = {}) noexcept
        : monotonic_resource(&buffer[0],
            n, std::move(upstream))
    {
        // If this goes off, check your parameters
        // closely, chances are you passed an array
        // thinking it was a pointer.
        BOOST_ASSERT(n <= N);
    }
#endif
#endif

    /** Release all allocated memory.

        This function deallocates all allocated memory.
        If an initial buffer was provided upon construction,
        then all of the bytes will be available again for
        allocation. Allocated memory is deallocated even
        if deallocate has not been called for some of
        the allocated blocks.

        @par Complexity
        Linear in the number of deallocations performed.

        @par Exception Safety
        No-throw guarantee.
    */
    void
    release() noexcept;

protected:
#ifndef BOOST_JSON_DOCS
    void*
    do_allocate(
        std::size_t n,
        std::size_t align) override;

    void
    do_deallocate(
        void* p,
        std::size_t n,
        std::size_t align) override;

    bool
    do_is_equal(
        memory_resource const& mr) const noexcept override;
#endif
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

template<>
struct is_deallocate_trivial<
    monotonic_resource>
{
    static constexpr bool value = true;
};

BOOST_JSON_NS_END

#endif

/* monotonic_resource.hpp
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
*/