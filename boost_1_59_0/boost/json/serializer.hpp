//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_SERIALIZER_HPP
#define BOOST_JSON_SERIALIZER_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/value.hpp>
#include <boost/json/detail/format.hpp>
#include <boost/json/detail/stack.hpp>
#include <boost/json/detail/stream.hpp>

BOOST_JSON_NS_BEGIN

/** A serializer for JSON.

    This class traverses an instance of a library
    type and emits serialized JSON text by filling
    in one or more caller-provided buffers. To use,
    declare a variable and call @ref reset with
    a pointer to the variable you want to serialize.
    Then call @ref read over and over until
    @ref done returns `true`.

    @par Example

    This demonstrates how the serializer may
    be used to print a JSON value to an output
    stream.

    @code

    void print( std::ostream& os, value const& jv)
    {
        serializer sr;
        sr.reset( &jv );
        while( ! sr.done() )
        {
            char buf[ 4000 ];
            os << sr.read( buf );
        }
    }

    @endcode

    @par Thread Safety

    The same instance may not be accessed concurrently.
*/
class serializer
{
    enum class state : char;
    // VFALCO Too many streams
    using stream = detail::stream;
    using const_stream = detail::const_stream;
    using local_stream = detail::local_stream;
    using local_const_stream =
        detail::local_const_stream;

    using fn_t = bool (serializer::*)(stream&);

#ifndef BOOST_JSON_DOCS
    union
    {
        value const* pv_;
        array const* pa_;
        object const* po_;
    };
#endif
    fn_t fn0_ = &serializer::write_null<true>;
    fn_t fn1_ = &serializer::write_null<false>;
    value const* jv_ = nullptr;
    detail::stack st_;
    const_stream cs0_;
    char buf_[detail::max_number_chars + 1];
    bool done_ = false;

    inline bool suspend(state st);
    inline bool suspend(
        state st, array::const_iterator it, array const* pa);
    inline bool suspend(
        state st, object::const_iterator it, object const* po);
    template<bool StackEmpty> bool write_null   (stream& ss);
    template<bool StackEmpty> bool write_true   (stream& ss);
    template<bool StackEmpty> bool write_false  (stream& ss);
    template<bool StackEmpty> bool write_string (stream& ss);
    template<bool StackEmpty> bool write_number (stream& ss);
    template<bool StackEmpty> bool write_array  (stream& ss);
    template<bool StackEmpty> bool write_object (stream& ss);
    template<bool StackEmpty> bool write_value  (stream& ss);
    inline string_view read_some(char* dest, std::size_t size);

public:
    /// Move constructor (deleted)
    serializer(serializer&&) = delete;

    /** Destructor

        All temporary storage is deallocated.

        @par Complexity
        Constant

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    ~serializer() noexcept;

    /** Default constructor

        This constructs a serializer with no value.
        The value may be set later by calling @ref reset.
        If serialization is attempted with no value,
        the output is as if a null value is serialized.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    BOOST_JSON_DECL
    serializer() noexcept;

    /** Returns `true` if the serialization is complete

        This function returns `true` when all of the
        characters in the serialized representation of
        the value have been read.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    done() const noexcept
    {
        return done_;
    }

    /** Reset the serializer for a new element

        This function prepares the serializer to emit
        a new serialized JSON representing `*p`.
        Any internally allocated memory is
        preserved and re-used for the new output.

        @param p A pointer to the element to serialize.
        Ownership is not transferred; The caller is
        responsible for ensuring that the lifetime of
        `*p` extends until it is no longer needed.
    */
    /** @{ */
    BOOST_JSON_DECL
    void
    reset(value const* p) noexcept;

    BOOST_JSON_DECL
    void
    reset(array const* p) noexcept;

    BOOST_JSON_DECL
    void
    reset(object const* p) noexcept;

    BOOST_JSON_DECL
    void
    reset(string const* p) noexcept;
    /** @} */

    /** Reset the serializer for a new string

        This function prepares the serializer to emit
        a new serialized JSON representing the string.
        Any internally allocated memory is
        preserved and re-used for the new output.

        @param sv The characters representing the string.
        Ownership is not transferred; The caller is
        responsible for ensuring that the lifetime of
        the characters reference by `sv` extends
        until it is no longer needed.
    */
    BOOST_JSON_DECL
    void
    reset(string_view sv) noexcept;

    /** Read the next buffer of serialized JSON

        This function attempts to fill the caller
        provided buffer starting at `dest` with
        up to `size` characters of the serialized
        JSON that represents the value. If the
        buffer is not large enough, multiple calls
        may be required.
\n
        If serialization completes during this call;
        that is, that all of the characters belonging
        to the serialized value have been written to
        caller-provided buffers, the function
        @ref done will return `true`.

        @par Preconditions
        `this->done() == true`

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @return A @ref string_view containing the
        characters written, which may be less than
        `size`.

        @param dest A pointer to valid memory of at
        least `size` bytes.

        @param size The maximum number of characters
        to write to the memory pointed to by `dest`.
    */
    BOOST_JSON_DECL
    string_view
    read(char* dest, std::size_t size);

    /** Read the next buffer of serialized JSON

        This function allows reading into a
        character array, with a deduced maximum size.

        @par Preconditions
        `this->done() == true`

        @par Effects
        @code
        return this->read( dest, N );
        @endcode

        @par Complexity
        Linear in `N`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.

        @return A @ref string_view containing the
        characters written, which may be less than
        `size`.

        @param dest The character array to write to.
    */
    template<std::size_t N>
    string_view
    read(char(&dest)[N])
    {
        return read(dest, N);
    }

#ifndef BOOST_JSON_DOCS
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    string_view
    read(char(&dest)[N], std::size_t n)
    {
        // If this goes off, check your parameters
        // closely, chances are you passed an array
        // thinking it was a pointer.
        BOOST_ASSERT(n <= N);
        return read(dest, n);
    }
#endif
};

BOOST_JSON_NS_END

#endif

/* serializer.hpp
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
*/