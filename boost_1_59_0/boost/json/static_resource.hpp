//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_STATIC_RESOURCE_HPP
#define BOOST_JSON_STATIC_RESOURCE_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/memory_resource.hpp>
#include <cstddef>

BOOST_JSON_NS_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4275) // non dll-interface class used as base for dll-interface class
#endif

//----------------------------------------------------------

/** A resource using a caller-owned buffer, with a trivial deallocate

    This memory resource is a special-purpose resource
    that releases allocated memory only when the resource
    is destroyed (or when @ref release is called).
    It has a trivial deallocate function; that is, the
    metafunction @ref is_deallocate_trivial returns `true`.
\n
    The resource is constructed from a caller-owned buffer
    from which subsequent calls to allocate are apportioned.
    When a memory request cannot be satisfied from the
    free bytes remaining in the buffer, the allocation
    request fails with the exception `std::bad_alloc`.
\n
    @par Example

    This parses a JSON into a value which uses a local
    stack buffer, then prints the result.

    @code

    unsigned char buf[ 4000 ];
    static_resource mr( buf );

    // Parse the string, using our memory resource
    value const jv = parse( "[1,2,3]", &mr );

    // Print the JSON
    std::cout << jv;

    @endcode

    @par Thread Safety
    Members of the same instance may not be
    called concurrently.

    @see
        https://en.wikipedia.org/wiki/Region-based_memory_management
*/
class BOOST_JSON_CLASS_DECL
    static_resource final
    : public memory_resource
{
    void* p_;
    std::size_t n_;
    std::size_t size_;

public:
    /// Copy constructor (deleted)
    static_resource(
        static_resource const&) = delete;

    /// Copy assignment (deleted)
    static_resource& operator=(
        static_resource const&) = delete;

    /** Destructor

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    ~static_resource() noexcept;

    /** Constructor

        This constructs the resource to use the specified
        buffer for subsequent calls to allocate. When the
        buffer is exhausted, allocate will throw
        `std::bad_alloc`.

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
    */
    /** @{ */
    static_resource(
        unsigned char* buffer,
        std::size_t size) noexcept;

#if defined(__cpp_lib_byte) || defined(BOOST_JSON_DOCS)
    static_resource(
        std::byte* buffer,
        std::size_t size) noexcept
        : static_resource(reinterpret_cast<
            unsigned char*>(buffer), size)
    {
    }
#endif
    /** @} */

    /** Constructor

        This constructs the resource to use the specified
        buffer for subsequent calls to allocate. When the
        buffer is exhausted, allocate will throw
        `std::bad_alloc`.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param buffer The buffer to use.
        Ownership is not transferred; the caller is
        responsible for ensuring that the lifetime of
        the buffer extends until the resource is destroyed.
    */
    /** @{ */
    template<std::size_t N>
    explicit
    static_resource(
        unsigned char(&buffer)[N]) noexcept
        : static_resource(&buffer[0], N)
    {
    }

#if defined(__cpp_lib_byte) || defined(BOOST_JSON_DOCS)
    template<std::size_t N>
    explicit
    static_resource(
        std::byte(&buffer)[N]) noexcept
        : static_resource(&buffer[0], N)
    {
    }
#endif
    /** @} */

#ifndef BOOST_JSON_DOCS
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    static_resource(
        unsigned char(&buffer)[N], std::size_t n) noexcept
        : static_resource(&buffer[0], n)
    {
        // If this goes off, check your parameters
        // closely, chances are you passed an array
        // thinking it was a pointer.
        BOOST_ASSERT(n <= N);
    }

#ifdef __cpp_lib_byte
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    static_resource(
        std::byte(&buffer)[N], std::size_t n) noexcept
        : static_resource(&buffer[0], n)
    {
        // If this goes off, check your parameters
        // closely, chances are you passed an array
        // thinking it was a pointer.
        BOOST_ASSERT(n <= N);
    }
#endif
#endif

    /** Release all allocated memory.

        This function resets the buffer provided upon
        construction so that all of the valid bytes are
        available for subsequent allocation.

        @par Complexity
        Constant

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
        memory_resource const& mr
            ) const noexcept override;
#endif
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

template<>
struct is_deallocate_trivial<
    static_resource>
{
    static constexpr bool value = true;
};

BOOST_JSON_NS_END

#endif

/* static_resource.hpp
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
*/