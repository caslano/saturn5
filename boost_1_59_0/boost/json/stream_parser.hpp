//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_STREAM_PARSER_HPP
#define BOOST_JSON_STREAM_PARSER_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/basic_parser.hpp>
#include <boost/json/parse_options.hpp>
#include <boost/json/storage_ptr.hpp>
#include <boost/json/value.hpp>
#include <boost/json/detail/handler.hpp>
#include <type_traits>
#include <cstddef>

BOOST_JSON_NS_BEGIN

//----------------------------------------------------------

/** A DOM parser for JSON contained in multiple buffers.

    This class is used to parse a JSON contained in a
    series of one or more character buffers, into a
    @ref value container. It implements a
    <a href="https://en.wikipedia.org/wiki/Streaming_algorithm">
        <em>streaming algorithm</em></a>, allowing these
    parsing strategies:

    @li Parse a JSON file a piece at a time.

    @li Parse incoming JSON as it arrives,
        one buffer at a time.

    @li Parse with bounded resource consumption
        per cycle.

    @par Usage

    To use the parser first construct it, then optionally
    call @ref reset to specify a @ref storage_ptr to use
    for the resulting @ref value. Then call @ref write
    one or more times to parse a single, complete JSON.
    Call @ref done to determine if the parse has completed.
    To indicate there are no more buffers, call @ref finish.
    If the parse is successful, call @ref release to take
    ownership of the value:

    @code
    stream_parser p;                                // construct a parser
    p.write( "[1,2" );                              // parse some of a JSON
    p.write( ",3,4]" );                             // parse the rest of the JSON
    assert( p.done() );                             // we have a complete JSON
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
    stream_parser p;                                // construct a parser
    std::size_t n;                                  // number of characters used
    n = p.write_some( "[1,2" );                     // parse some of a JSON
    assert( n == 4 );                               // all characters consumed
    n = p.write_some( ",3,4] null" );               // parse the remainder of the JSON
    assert( n == 6 );                               // only some characters consumed
    assert( p.done() );                             // we have a complete JSON
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
        @ref parser,
        @ref parse_options,
*/
class stream_parser
{
    basic_parser<detail::handler> p_;

public:
    /// Copy constructor (deleted)
    stream_parser(
        stream_parser const&) = delete;

    /// Copy assignment (deleted)
    stream_parser& operator=(
        stream_parser const&) = delete;

    /** Destructor.

        All dynamically allocated memory, including
        any incomplete parsing results, is freed.

        @par Complexity
        Linear in the size of partial results

        @par Exception Safety
        No-throw guarantee.
    */
    ~stream_parser() = default;

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
    stream_parser(
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
    stream_parser() noexcept
        : stream_parser({}, {})
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
    stream_parser(
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
    stream_parser(storage_ptr sp) noexcept
        : stream_parser(std::move(sp), {})
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
    stream_parser(
        storage_ptr sp,
        parse_options const& opt,
        unsigned char(&buffer)[N]) noexcept
        : stream_parser(std::move(sp),
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
    stream_parser(
        storage_ptr sp,
        parse_options const& opt,
        std::byte* buffer,
        std::size_t size) noexcept
        : stream_parser(sp, opt, reinterpret_cast<
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
    stream_parser(
        storage_ptr sp,
        parse_options const& opt,
        std::byte(&buffer)[N]) noexcept
        : stream_parser(std::move(sp),
            opt, &buffer[0], N)
    {
    }
#endif

#ifndef BOOST_JSON_DOCS
    // Safety net for accidental buffer overflows
    template<std::size_t N>
    stream_parser(
        storage_ptr sp,
        parse_options const& opt,
        unsigned char(&buffer)[N],
        std::size_t n) noexcept
        : stream_parser(std::move(sp),
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
    stream_parser(
        storage_ptr sp,
        parse_options const& opt,
        std::byte(&buffer)[N], std::size_t n) noexcept
        : stream_parser(std::move(sp),
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

    /** Return true if a complete JSON has been parsed.

        This function returns `true` when all of these
        conditions are met:

        @li A complete serialized JSON has been
            presented to the parser, and

        @li No error has occurred since the parser
            was constructed, or since the last call
            to @ref reset,

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    bool
    done() const noexcept
    {
        return p_.done();
    }

    /** Parse a buffer containing all or part of a complete JSON.

        This function parses JSON contained in the
        specified character buffer. If parsing completes,
        any additional characters past the end of the
        complete JSON are ignored. The function returns the
        actual number of characters parsed, which may be
        less than the size of the input. This allows parsing
        of a buffer containing multiple individual JSONs or
        containing different protocol data.

        @par Example
        @code
        stream_parser p;                                // construct a parser
        std::size_t n;                                  // number of characters used
        n = p.write_some( "[1,2" );                     // parse the first part of the JSON
        assert( n == 4 );                               // all characters consumed
        n = p.write_some( "3,4] null" );                // parse the rest of the JSON
        assert( n == 5 );                               // only some characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @note

        To indicate there are no more character buffers,
        such as when @ref done returns `false` after
        writing, call @ref finish.

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

    /** Parse a buffer containing all or part of a complete JSON.

        This function parses JSON contained in the
        specified character buffer. If parsing completes,
        any additional characters past the end of the
        complete JSON are ignored. The function returns the
        actual number of characters parsed, which may be
        less than the size of the input. This allows parsing
        of a buffer containing multiple individual JSONs or
        containing different protocol data.

        @par Example
        @code
        stream_parser p;                                // construct a parser
        std::size_t n;                                  // number of characters used
        n = p.write_some( "[1,2" );                     // parse the first part of the JSON
        assert( n == 4 );                               // all characters consumed
        n = p.write_some( "3,4] null" );                // parse the rest of the JSON
        assert( n == 5 );                               // only some characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @note

        To indicate there are no more character buffers,
        such as when @ref done returns `false` after
        writing, call @ref finish.

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

    /** Parse a buffer containing all or part of a complete JSON.

        This function parses JSON contained in the
        specified character buffer. If parsing completes,
        any additional characters past the end of the
        complete JSON are ignored. The function returns the
        actual number of characters parsed, which may be
        less than the size of the input. This allows parsing
        of a buffer containing multiple individual JSONs or
        containing different protocol data.

        @par Example
        @code
        stream_parser p;                                // construct a parser
        std::size_t n;                                  // number of characters used
        n = p.write_some( "[1,2" );                     // parse the first part of the JSON
        assert( n == 4 );                               // all characters consumed
        n = p.write_some( "3,4] null" );                // parse the rest of the JSON
        assert( n == 5 );                               // only some characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @note

        To indicate there are no more character buffers,
        such as when @ref done returns `false` after
        writing, call @ref finish.

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

    /** Parse a buffer containing all or part of a complete JSON.

        This function parses JSON contained in the
        specified character buffer. If parsing completes,
        any additional characters past the end of the
        complete JSON are ignored. The function returns the
        actual number of characters parsed, which may be
        less than the size of the input. This allows parsing
        of a buffer containing multiple individual JSONs or
        containing different protocol data.

        @par Example
        @code
        stream_parser p;                                // construct a parser
        std::size_t n;                                  // number of characters used
        n = p.write_some( "[1,2" );                     // parse the first part of the JSON
        assert( n == 4 );                               // all characters consumed
        n = p.write_some( "3,4] null" );                // parse the rest of the JSON
        assert( n == 5 );                               // only some characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @note

        To indicate there are no more character buffers,
        such as when @ref done returns `false` after
        writing, call @ref finish.

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

    /** Parse a buffer containing all or part of a complete JSON.

        This function parses a all or part of a JSON
        contained in the specified character buffer. The
        entire buffer must be consumed; if there are
        additional characters past the end of the complete
        JSON, the parse fails and an error is returned.

        @par Example
        @code
        stream_parser p;                                // construct a parser
        std::size_t n;                                  // number of characters used
        n = p.write( "[1,2" );                          // parse some of the JSON
        assert( n == 4 );                               // all characters consumed
        n = p.write( "3,4]" );                          // parse the rest of the JSON
        assert( n == 4 );                               // all characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @note

        To indicate there are no more character buffers,
        such as when @ref done returns `false` after
        writing, call @ref finish.

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

    /** Parse a buffer containing all or part of a complete JSON.

        This function parses a all or part of a JSON
        contained in the specified character buffer. The
        entire buffer must be consumed; if there are
        additional characters past the end of the complete
        JSON, the parse fails and an error is returned.

        @par Example
        @code
        stream_parser p;                                // construct a parser
        std::size_t n;                                  // number of characters used
        n = p.write( "[1,2" );                          // parse some of the JSON
        assert( n == 4 );                               // all characters consumed
        n = p.write( "3,4]" );                          // parse the rest of the JSON
        assert( n == 4 );                               // all characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @note

        To indicate there are no more character buffers,
        such as when @ref done returns `false` after
        writing, call @ref finish.

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

    /** Parse a buffer containing all or part of a complete JSON.

        This function parses a all or part of a JSON
        contained in the specified character buffer. The
        entire buffer must be consumed; if there are
        additional characters past the end of the complete
        JSON, the parse fails and an error is returned.

        @par Example
        @code
        stream_parser p;                                // construct a parser
        std::size_t n;                                  // number of characters used
        n = p.write( "[1,2" );                          // parse some of the JSON
        assert( n == 4 );                               // all characters consumed
        n = p.write( "3,4]" );                          // parse the rest of the JSON
        assert( n == 4 );                               // all characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @note

        To indicate there are no more character buffers,
        such as when @ref done returns `false` after
        writing, call @ref finish.

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

    /** Parse a buffer containing all or part of a complete JSON.

        This function parses a all or part of a JSON
        contained in the specified character buffer. The
        entire buffer must be consumed; if there are
        additional characters past the end of the complete
        JSON, the parse fails and an error is returned.

        @par Example
        @code
        stream_parser p;                                // construct a parser
        std::size_t n;                                  // number of characters used
        n = p.write( "[1,2" );                          // parse some of the JSON
        assert( n == 4 );                               // all characters consumed
        n = p.write( "3,4]" );                          // parse the rest of the JSON
        assert( n == 4 );                               // all characters consumed
        value jv = p.release();                         // take ownership of the value
        @endcode

        @note

        To indicate there are no more character buffers,
        such as when @ref done returns `false` after
        writing, call @ref finish.

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

    /** Indicate the end of JSON input.

        This function is used to indicate that there
        are no more character buffers in the current
        JSON being parsed. If ther resulting JSON is
        incomplete, the error is set to indicate a
        parsing failure.

        @par Example
        In the code below, @ref finish is called to
        indicate there are no more digits in the
        resulting number:
        @code
        stream_parser p;                                // construct a parser
        p.write( "3." );                                // write the first part of the number
        p.write( "14" );                                // write the second part of the number
        assert( ! p.done() );                           // there could be more digits
        p.finish();                                     // indicate the end of the JSON input
        assert( p.done() );                             // now we are finished
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @param ec Set to the error, if any occurred.
    */
/** @{ */
    BOOST_JSON_DECL
    void
    finish(error_code& ec);

    BOOST_JSON_DECL
    void
    finish(std::error_code& ec);
/** @} */

    /** Indicate the end of JSON input.

        This function is used to indicate that there
        are no more character buffers in the current
        JSON being parsed. If ther resulting JSON is
        incomplete, the error is set to indicate a
        parsing failure.

        @par Example
        In the code below, @ref finish is called to
        indicate there are no more digits in the
        resulting number:
        @code
        stream_parser p;                                // construct a parser
        p.write( "3." );                                // write the first part of the number
        p.write( "14" );                                // write the second part of the number
        assert( ! p.done() );                           // there could be more digits
        p.finish();                                     // indicate the end of the JSON input
        assert( p.done() );                             // now we are finished
        value jv = p.release();                         // take ownership of the value
        @endcode

        @par Complexity
        Constant.

        @par Exception Safety
        Basic guarantee.
        Calls to `memory_resource::allocate` may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @throw system_error Thrown on error.
    */
    BOOST_JSON_DECL
    void
    finish();

    /** Return the parsed JSON as a @ref value.

        This returns the parsed value, or throws
        an exception if the parsing is incomplete or
        failed. It is necessary to call @ref reset
        after calling this function in order to parse
        another JSON.

        @par Effects
        @code
        if( ! this->done() )
            this->finish();
        @endcode
        @note

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

/* stream_parser.hpp
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
*/