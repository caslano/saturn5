//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_PARSER_HPP
#define BOOST_JSON_PARSER_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/basic_parser.hpp>
#include <boost/json/storage_ptr.hpp>
#include <boost/json/value.hpp>
#include <boost/json/detail/handler.hpp>
#include <type_traits>
#include <cstddef>

BOOST_JSON_NS_BEGIN

//----------------------------------------------------------

/** A DOM parser for JSON contained in a single buffer.

    This class is used to parse a JSON contained in a
    single character buffer, into a @ref value container.

    @par Usage

    To use the parser first construct it, then optionally
    call @ref reset to specify a @ref storage_ptr to use
    for the resulting @ref value. Then call @ref write
    to parse a character buffer containing a complete
    JSON. If the parse is successful, call @ref release
    to take ownership of the value:
    @code
    parser p;                                       // construct a parser
    size_t n = p.write( "[1,2,3]" );                // parse a complete JSON
    assert( n == 7 );                               // all characters consumed
    value jv = p.release();                         // take ownership of the value
    @endcode

    @par Extra Data

    When the character buffer provided as input contains
    additional data that is not part of the complete
    JSON, an error is returned. The @ref write_some
    function is an alternative which allows the parse
    to finish early, without consuming all the characters
    in the buffer. This allows parsing of a buffer
    containing multiple individual JSONs or containing
    different protocol data:
    @code
    parser p;                                       // construct a parser
    size_t n = p.write_some( "[1,2,3] null" );      // parse a complete JSON
    assert( n == 8 );                               // only some characters consumed
    value jv = p.release();                         // take ownership of the value
    @endcode

    @par Temporary Storage

    The parser may dynamically allocate temporary
    storage as needed to accommodate the nesting level
    of the JSON being parsed. Temporary storage is
    first obtained from an optional, caller-owned
    buffer specified upon construction. When that
    is exhausted, the next allocation uses the
    @ref memory_resource passed to the constructor; if
    no such argument is specified, the default memory
    resource is used. Temporary storage is freed only
    when the parser is destroyed; The performance of
    parsing multiple JSONs may be improved by reusing
    the same parser instance.
\n
    It is important to note that the @ref memory_resource
    supplied upon construction is used for temporary
    storage only, and not for allocating the elements
    which make up the parsed value. That other memory
    resource is optionally supplied in each call
    to @ref reset.

    @par Duplicate Keys

    If there are object elements with duplicate keys;
    that is, if multiple elements in an object have
    keys that compare equal, only the last equivalent
    element will be inserted.

    @par Non-Standard JSON

    The @ref parse_options structure optionally
    provided upon construction is used to customize
    some parameters of the parser, including which
    non-standard JSON extensions should be allowed.
    A default-constructed parse options allows only
    standard JSON.

    @par Thread Safety

    Distinct instances may be accessed concurrently.
    Non-const member functions of a shared instance
    may not be called concurrently with any other
    member functions of that instance.

    @see
        @ref parse,
        @ref parse_options,
        @ref stream_parser.
*/
class parser
{
    basic_parser<detail::handler> p_;

public:
    /// Copy constructor (deleted)
    parser(
        parser const&) = delete;

    /// Copy assignment (deleted)
    parser& operator=(
        parser const&) = delete;

    /** Destructor.

        All dynamically allocated memory, including
        any incomplete parsing results, is freed.

        @par Complexity
        Linear in the size of partial results

        @par Exception Safety
        No-throw guarantee.
    */
    ~parser() = default;

    /** Constructor.

        This constructs a new parser which first uses
        the caller-owned storage pointed to by `buffer`
        for temporary storage, falling back to the memory
        resource `sp` if needed. The parser will use the
        specified parsing options.
    \n
        The parsed value will use the default memory
        resource for storage. To use a different resource,
        call @ref reset after construction.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp The memory resource to use for
        temporary storage after `buffer` is exhausted.

        @param opt The parsing options to use.

        @param buffer A pointer to valid memory of at least
        `size` bytes for the parser to use for temporary storage.
        Ownership is not transferred, the caller is responsible
        for ensuring the lifetime of the memory pointed to by
        `buffer` extends until the parser is destroyed.

        @param size The number of valid bytes in `buffer`.
    */
    BOOST_JSON_DECL
    parser(
        storage_ptr sp,
        parse_options const& opt,
        unsigned char* buffer,
        std::size_t size) noexcept;

    /** Constructor.

        This constructs a new parser which uses the default
        memory resource for temporary storage, and accepts
        only strict JSON.
    \n
        The parsed value will use the default memory
        resource for storage. To use a different resource,
        call @ref reset after construction.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    parser() noexcept
        : parser({}, {})
    {
    }

    /** Constructor.

        This constructs a new parser which uses the
        specified memory resource for temporary storage,
        and is configured to use the specified parsing
        options.
    \n
        The parsed value will use the default memory
        resource for storage. To use a different resource,
        call @ref reset after construction.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp The memory resource to use for temporary storage.

        @param opt The parsing options to use.
    */
    BOOST_JSON_DECL
    parser(
        storage_ptr sp,
        parse_options const& opt) noexcept;

    /** Constructor.

        This constructs a new parser which uses the
        specified memory resource for temporary storage,
        and accepts only strict JSON.
    \n
        The parsed value will use the default memory
        resource for storage. To use a different resource,
        call @ref reset after construction.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp The memory resource to use for temporary storage.
    */
    explicit
    parser(storage_ptr sp) noexcept
        : parser(std::move(sp), {})
    {
    }

    /** Constructor.

        This constructs a new parser which first uses the
        caller-owned storage `buffer` for temporary storage,
        falling back to the memory resource `sp` if needed.
        The parser will use the specified parsing options.
    \n
        The parsed value will use the default memory
        resource for storage. To use a different resource,
        call @ref reset after construction.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp The memory resource to use for
        temporary storage after `buffer` is exhausted.

        @param opt The parsing options to use.

        @param buffer A buffer for the parser to use for
        temporary storage. Ownership is not transferred,
        the caller is responsible for ensuring the lifetime
        of `buffer` extends until the parser is destroyed.
    */
    template<std::size_t N>
    parser(
        storage_ptr sp,
        parse_options const& opt,
        unsigned char(&buffer)[N]) noexcept
        : parser(std::move(sp),
            opt, &buffer[0], N)
    {
    }

#if defined(__cpp_lib_byte) || defined(BOOST_JSON_DOCS)
    /** Constructor.

        This constructs a new parser which first uses
        the caller-owned storage pointed to by `buffer`
        for temporary storage, falling back to the memory
        resource `sp` if needed. The parser will use the
        specified parsing options.
    \n
        The parsed value will use the default memory
        resource for storage. To use a different resource,
        call @ref reset after construction.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp The memory resource to use for
        temporary storage after `buffer` is exhausted.

        @param opt The parsing options to use.

        @param buffer A pointer to valid memory of at least
        `size` bytes for the parser to use for temporary storage.
        Ownership is not transferred, the caller is responsible
        for ensuring the lifetime of the memory pointed to by
        `buffer` extends until the parser is destroyed.

        @param size The number of valid bytes in `buffer`.
    */
    parser(
        storage_ptr sp,
        parse_options const& opt,
        std::byte* buffer,
        std::size_t size) noexcept
        : parser(sp, opt, reinterpret_cast<
            unsigned char*>(buffer), size)
    {
    }

    /** Constructor.

        This constructs a new parser which first uses the
        caller-owned storage `buffer` for temporary storage,
        falling back to the memory resource `sp` if needed.
        The parser will use the specified parsing options.
    \n
        The parsed value will use the default memory
        resource for storage. To use a different resource,
        call @ref reset after construction.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param sp The memory resource to use for
        temporary storage after `buffer` is exhausted.

        @param opt The parsing options to use.

        @param buffer A buffer for the parser to use for
        temporary storage. Ownership is not transferred,
        the caller is responsible for ensuring the lifetime
        of `buffer` extends until the parser is destroyed.
    */
    template<std::size_t N>
    parser(
        storage_ptr sp,
        parse_options const& opt,
        std::byte(&buffer)[N]) noexcept
        : parser(std::move(sp),
            opt, &buffer[0], N)
    {
    }
#endif

#ifndef BOOST_JSON_DOCS
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    parser(
        storage_ptr sp,
        parse_options const& opt,
        unsigned char(&buffer)[N],
        std::size_t n) noexcept
        : parser(std::move(sp),
            opt, &buffer[0], n)
    {
        // If this goes off, check your parameters
        // closely, chances are you passed an array
        // thinking it was a pointer.
        BOOST_ASSERT(n <= N);
    }

#ifdef __cpp_lib_byte
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    parser(
        storage_ptr sp,
        parse_options const& opt,
        std::byte(&buffer)[N], std::size_t n) noexcept
        : parser(std::move(sp),
            opt, &buffer[0], n)
    {
        // If this goes off, check your parameters
        // closely, chances are you passed an array
        // thinking it was a pointer.
        BOOST_ASSERT(n <= N);
    }
#endif
#endif

    /** Reset the parser for a new JSON.

        This function is used to reset the parser to
        prepare it for parsing a new complete JSON.
        Any previous partial results are destroyed.

        @par Complexity
        Constant or linear in the size of any previous
        partial parsing results.

        @par Exception Safety
        No-throw guarantee.

        @param sp A pointer to the @ref memory_resource
        to use for the resulting @ref value. The parser
        will acquire shared ownership.
    */
    BOOST_JSON_DECL
    void
    reset(storage_ptr sp = {}) noexcept;

    /** Parse a buffer containing a complete JSON.

        This function parses a complete JSON contained
        in the specified character buffer. Additional
        characters past the end of the complete JSON
        are ignored. The function returns the actual
        number of characters parsed, which may be less
        than the size of the input. This allows parsing
        of a buffer containing multiple individual JSONs
        or containing different protocol data:

        @par Example
        @code
        parser p;                                       // construct a parser
        size_t n = p.write_some( "[1,2,3] null" );      // parse a complete JSON
        assert( n == 8 );                               // only some characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters consumed from
        the buffer.

        @param data A pointer to a buffer of `size`
        characters to parse.

        @param size The number of characters pointed to
        by `data`.

        @param ec Set to the error, if any occurred.
    */
/** @{ */
    BOOST_JSON_DECL
    std::size_t
    write_some(
        char const* data,
        std::size_t size,
        error_code& ec);

    BOOST_JSON_DECL
    std::size_t
    write_some(
        char const* data,
        std::size_t size,
        std::error_code& ec);
/** @} */

    /** Parse a buffer containing a complete JSON.

        This function parses a complete JSON contained
        in the specified character buffer. Additional
        characters past the end of the complete JSON
        are ignored. The function returns the actual
        number of characters parsed, which may be less
        than the size of the input. This allows parsing
        of a buffer containing multiple individual JSONs
        or containing different protocol data:

        @par Example
        @code
        parser p;                                       // construct a parser
        size_t n = p.write_some( "[1,2,3] null" );      // parse a complete JSON
        assert( n == 8 );                               // only some characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters consumed from
        the buffer.

        @param data A pointer to a buffer of `size`
        characters to parse.

        @param size The number of characters pointed to
        by `data`.

        @throw system_error Thrown on error.
    */
    BOOST_JSON_DECL
    std::size_t
    write_some(
        char const* data,
        std::size_t size);

    /** Parse a buffer containing a complete JSON.

        This function parses a complete JSON contained
        in the specified character buffer. Additional
        characters past the end of the complete JSON
        are ignored. The function returns the actual
        number of characters parsed, which may be less
        than the size of the input. This allows parsing
        of a buffer containing multiple individual JSONs
        or containing different protocol data:

        @par Example
        @code
        parser p;                                       // construct a parser
        size_t n = p.write_some( "[1,2,3] null" );      // parse a complete JSON
        assert( n == 8 );                               // only some characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters consumed from
        the buffer.

        @param s The character string to parse.

        @param ec Set to the error, if any occurred.
    */
/** @{ */
    std::size_t
    write_some(
        string_view s,
        error_code& ec)
    {
        return write_some(
            s.data(), s.size(), ec);
    }

    std::size_t
    write_some(
        string_view s,
        std::error_code& ec)
    {
        return write_some(
            s.data(), s.size(), ec);
    }
/** @} */

    /** Parse a buffer containing a complete JSON.

        This function parses a complete JSON contained
        in the specified character buffer. Additional
        characters past the end of the complete JSON
        are ignored. The function returns the actual
        number of characters parsed, which may be less
        than the size of the input. This allows parsing
        of a buffer containing multiple individual JSONs
        or containing different protocol data:

        @par Example
        @code
        parser p;                                       // construct a parser
        size_t n = p.write_some( "[1,2,3] null" );      // parse a complete JSON
        assert( n == 8 );                               // only some characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters consumed from
        the buffer.

        @param s The character string to parse.

        @throw system_error Thrown on error.
    */
    std::size_t
    write_some(
        string_view s)
    {
        return write_some(
            s.data(), s.size());
    }

    /** Parse a buffer containing a complete JSON.

        This function parses a complete JSON contained
        in the specified character buffer. The entire
        buffer must be consumed; if there are additional
        characters past the end of the complete JSON,
        the parse fails and an error is returned.

        @par Example
        @code
        parser p;                                       // construct a parser
        size_t n = p.write( "[1,2,3]" );                // parse a complete JSON
        assert( n == 7 );                               // all characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters consumed from
        the buffer.

        @param data A pointer to a buffer of `size`
        characters to parse.

        @param size The number of characters pointed to
        by `data`.

        @param ec Set to the error, if any occurred.
    */
/** @{ */
    BOOST_JSON_DECL
    std::size_t
    write(
        char const* data,
        std::size_t size,
        error_code& ec);

    BOOST_JSON_DECL
    std::size_t
    write(
        char const* data,
        std::size_t size,
        std::error_code& ec);
/** @} */

    /** Parse a buffer containing a complete JSON.

        This function parses a complete JSON contained
        in the specified character buffer. The entire
        buffer must be consumed; if there are additional
        characters past the end of the complete JSON,
        the parse fails and an error is returned.

        @par Example
        @code
        parser p;                                       // construct a parser
        size_t n = p.write( "[1,2,3]" );                // parse a complete JSON
        assert( n == 7 );                               // all characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters consumed from
        the buffer.

        @param data A pointer to a buffer of `size`
        characters to parse.

        @param size The number of characters pointed to
        by `data`.

        @throw system_error Thrown on error.
    */
    BOOST_JSON_DECL
    std::size_t
    write(
        char const* data,
        std::size_t size);

    /** Parse a buffer containing a complete JSON.

        This function parses a complete JSON contained
        in the specified character buffer. The entire
        buffer must be consumed; if there are additional
        characters past the end of the complete JSON,
        the parse fails and an error is returned.

        @par Example
        @code
        parser p;                                       // construct a parser
        size_t n = p.write( "[1,2,3]" );                // parse a complete JSON
        assert( n == 7 );                               // all characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters consumed from
        the buffer.

        @param s The character string to parse.

        @param ec Set to the error, if any occurred.
    */
/** @{ */
    std::size_t
    write(
        string_view s,
        error_code& ec)
    {
        return write(
            s.data(), s.size(), ec);
    }

    std::size_t
    write(
        string_view s,
        std::error_code& ec)
    {
        return write(
            s.data(), s.size(), ec);
    }
/** @} */

    /** Parse a buffer containing a complete JSON.

        This function parses a complete JSON contained
        in the specified character buffer. The entire
        buffer must be consumed; if there are additional
        characters past the end of the complete JSON,
        the parse fails and an error is returned.

        @par Example
        @code
        parser p;                                       // construct a parser
        size_t n = p.write( "[1,2,3]" );                // parse a complete JSON
        assert( n == 7 );                               // all characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters consumed from
        the buffer.

        @param s The character string to parse.

        @throw system_error Thrown on error.
    */
    std::size_t
    write(
        string_view s)
    {
        return write(
            s.data(), s.size());
    }

    /** Return the parsed JSON as a @ref value.

        This returns the parsed value, or throws
        an exception if the parsing is incomplete or
        failed. It is necessary to call @ref reset
        after calling this function in order to parse
        another JSON.

        @par Complexity
        Constant.

        @return The parsed value. Ownership of this
        value is transferred to the caller.

        @throw system_error Thrown on failure.
    */
    BOOST_JSON_DECL
    value
    release();
};

BOOST_JSON_NS_END

#endif

/* parser.hpp
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
*/