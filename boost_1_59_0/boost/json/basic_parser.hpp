//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_BASIC_PARSER_HPP
#define BOOST_JSON_BASIC_PARSER_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/detail/except.hpp>
#include <boost/json/error.hpp>
#include <boost/json/kind.hpp>
#include <boost/json/parse_options.hpp>
#include <boost/json/detail/stack.hpp>
#include <boost/json/detail/stream.hpp>
#include <boost/json/detail/utf8.hpp>

/*  VFALCO NOTE

    This file is in the detail namespace because it
    is not allowed to be included directly by users,
    who should be including <boost/json/basic_parser.hpp>
    instead, which provides the member function definitions.

    The source code is arranged this way to keep compile
    times down.
*/

BOOST_JSON_NS_BEGIN

/** An incremental SAX parser for serialized JSON.

    This implements a SAX-style parser, invoking a
    caller-supplied handler with each parsing event.
    To use, first declare a variable of type
    `basic_parser<T>` where `T` meets the handler
    requirements specified below. Then call
    @ref write_some one or more times with the input,
    setting `more = false` on the final buffer.
    The parsing events are realized through member
    function calls on the handler, which exists
    as a data member of the parser.
\n
    The parser may dynamically allocate intermediate
    storage as needed to accommodate the nesting level
    of the input JSON. On subsequent invocations, the
    parser can cheaply re-use this memory, improving
    performance. This storage is freed when the
    parser is destroyed

    @par Usage

    To get the declaration and function definitions
    for this class it is necessary to include this
    file instead:
    @code
    #include <boost/json/basic_parser_impl.hpp>
    @endcode

    Users who wish to parse JSON into the DOM container
    @ref value will not use this class directly; instead
    they will create an instance of @ref parser or
    @ref stream_parser and use that instead. Alternatively,
    they may call the function @ref parse. This class is
    designed for users who wish to perform custom actions
    instead of building a @ref value. For example, to
    produce a DOM from an external library.
\n
    @note

    By default, only conforming JSON using UTF-8
    encoding is accepted. However, select non-compliant
    syntax can be allowed by construction using a
    @ref parse_options set to desired values.

    @par Handler

    The handler provided must be implemented as an
    object of class type which defines each of the
    required event member functions below. The event
    functions return a `bool` where `true` indicates
    success, and `false` indicates failure. If the
    member function returns `false`, it must set
    the error code to a suitable value. This error
    code will be returned by the write function to
    the caller.
\n
    Handlers are required to declare the maximum
    limits on various elements. If these limits
    are exceeded during parsing, then parsing
    fails with an error.
\n
    The following declaration meets the parser's
    handler requirements:

    @code
    struct handler
    {
        /// The maximum number of elements allowed in an array
        static constexpr std::size_t max_array_size = -1;

        /// The maximum number of elements allowed in an object
        static constexpr std::size_t max_object_size = -1;

        /// The maximum number of characters allowed in a string
        static constexpr std::size_t max_string_size = -1;

        /// The maximum number of characters allowed in a key
        static constexpr std::size_t max_key_size = -1;

        /// Called once when the JSON parsing begins.
        ///
        /// @return `true` on success.
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_document_begin( error_code& ec );

        /// Called when the JSON parsing is done.
        ///
        /// @return `true` on success.
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_document_end( error_code& ec );

        /// Called when the beginning of an array is encountered.
        ///
        /// @return `true` on success.
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_array_begin( error_code& ec );

        /// Called when the end of the current array is encountered.
        ///
        /// @return `true` on success.
        /// @param n The number of elements in the array.
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_array_end( std::size_t n, error_code& ec );

        /// Called when the beginning of an object is encountered.
        ///
        /// @return `true` on success.
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_object_begin( error_code& ec );

        /// Called when the end of the current object is encountered.
        ///
        /// @return `true` on success.
        /// @param n The number of elements in the object.
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_object_end( std::size_t n, error_code& ec );

        /// Called with characters corresponding to part of the current string.
        ///
        /// @return `true` on success.
        /// @param s The partial characters
        /// @param n The total size of the string thus far
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_string_part( string_view s, std::size_t n, error_code& ec );

        /// Called with the last characters corresponding to the current string.
        ///
        /// @return `true` on success.
        /// @param s The remaining characters
        /// @param n The total size of the string
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_string( string_view s, std::size_t n, error_code& ec );

        /// Called with characters corresponding to part of the current key.
        ///
        /// @return `true` on success.
        /// @param s The partial characters
        /// @param n The total size of the key thus far
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_key_part( string_view s, std::size_t n, error_code& ec );

        /// Called with the last characters corresponding to the current key.
        ///
        /// @return `true` on success.
        /// @param s The remaining characters
        /// @param n The total size of the key
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_key( string_view s, std::size_t n, error_code& ec );

        /// Called with the characters corresponding to part of the current number.
        ///
        /// @return `true` on success.
        /// @param s The partial characters
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_number_part( string_view s, error_code& ec );

        /// Called when a signed integer is parsed.
        ///
        /// @return `true` on success.
        /// @param i The value
        /// @param s The remaining characters
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_int64( int64_t i, string_view s, error_code& ec );

        /// Called when an unsigend integer is parsed.
        ///
        /// @return `true` on success.
        /// @param u The value
        /// @param s The remaining characters
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_uint64( uint64_t u, string_view s, error_code& ec );

        /// Called when a double is parsed.
        ///
        /// @return `true` on success.
        /// @param d The value
        /// @param s The remaining characters
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_double( double d, string_view s, error_code& ec );

        /// Called when a boolean is parsed.
        ///
        /// @return `true` on success.
        /// @param b The value
        /// @param s The remaining characters
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_bool( bool b, error_code& ec );

        /// Called when a null is parsed.
        ///
        /// @return `true` on success.
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_null( error_code& ec );

        /// Called with characters corresponding to part of the current comment.
        ///
        /// @return `true` on success.
        /// @param s The partial characters.
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_comment_part( string_view s, error_code& ec );

        /// Called with the last characters corresponding to the current comment.
        ///
        /// @return `true` on success.
        /// @param s The remaining characters
        /// @param ec Set to the error, if any occurred.
        ///
        bool on_comment( string_view s, error_code& ec );
    };
    @endcode

    @see
        @ref parse,
        @ref stream_parser.

    @headerfile <boost/json/basic_parser.hpp>
*/
template<class Handler>
class basic_parser
{
    enum class state : char
    {
        doc1,  doc2,  doc3, doc4,
        com1,  com2,  com3, com4,
        nul1,  nul2,  nul3,
        tru1,  tru2,  tru3,
        fal1,  fal2,  fal3,  fal4,
        str1,  str2,  str3,  str4,
        str5,  str6,  str7,  str8,
        sur1,  sur2,  sur3,
        sur4,  sur5,  sur6,
        obj1,  obj2,  obj3,  obj4,
        obj5,  obj6,  obj7,  obj8,
        obj9,  obj10, obj11,
        arr1,  arr2,  arr3,
        arr4,  arr5,  arr6,
        num1,  num2,  num3,  num4,
        num5,  num6,  num7,  num8,
        exp1,  exp2,  exp3,
        val1,  val2
    };

    struct number
    {
        uint64_t mant;
        int bias;
        int exp;
        bool frac;
        bool neg;
    };

    // optimization: must come first
    Handler h_;

    number num_;
    error_code ec_;
    detail::stack st_;
    detail::utf8_sequence seq_;
    unsigned u1_;
    unsigned u2_;
    bool more_; // false for final buffer
    bool done_ = false; // true on complete parse
    bool clean_ = true; // write_some exited cleanly
    const char* end_;
    parse_options opt_;
    // how many levels deeper the parser can go
    std::size_t depth_ = opt_.max_depth;

    inline void reserve();
    inline const char* sentinel();
    inline bool incomplete(
        const detail::const_stream_wrapper& cs);

#ifdef __INTEL_COMPILER
#pragma warning push
#pragma warning disable 2196
#endif

    BOOST_NOINLINE
    inline
    const char*
    suspend_or_fail(state st);

    BOOST_NOINLINE
    inline
    const char*
    suspend_or_fail(
        state st,
        std::size_t n);

    BOOST_NOINLINE
    inline
    const char*
    fail(const char* p) noexcept;

    BOOST_NOINLINE
    inline
    const char*
    fail(
        const char* p,
        error ev,
        source_location const* loc) noexcept;

    BOOST_NOINLINE
    inline
    const char*
    maybe_suspend(
        const char* p,
        state st);

    BOOST_NOINLINE
    inline
    const char*
    maybe_suspend(
        const char* p,
        state st,
        std::size_t n);

    BOOST_NOINLINE
    inline
    const char*
    maybe_suspend(
        const char* p,
        state st,
        const number& num);

    BOOST_NOINLINE
    inline
    const char*
    suspend(
        const char* p,
        state st);

    BOOST_NOINLINE
    inline
    const char*
    suspend(
        const char* p,
        state st,
        const number& num);

#ifdef __INTEL_COMPILER
#pragma warning pop
#endif

    template<bool StackEmpty_/*, bool Terminal_*/>
    const char* parse_comment(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        /*std::integral_constant<bool, Terminal_>*/ bool terminal);

    template<bool StackEmpty_>
    const char* parse_document(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty);

    template<bool StackEmpty_, bool AllowComments_/*,
        bool AllowTrailing_, bool AllowBadUTF8_*/>
    const char* parse_value(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        std::integral_constant<bool, AllowComments_> allow_comments,
        /*std::integral_constant<bool, AllowTrailing_>*/ bool allow_trailing,
        /*std::integral_constant<bool, AllowBadUTF8_>*/ bool allow_bad_utf8);

    template<bool StackEmpty_, bool AllowComments_/*,
        bool AllowTrailing_, bool AllowBadUTF8_*/>
    const char* resume_value(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        std::integral_constant<bool, AllowComments_> allow_comments,
        /*std::integral_constant<bool, AllowTrailing_>*/ bool allow_trailing,
        /*std::integral_constant<bool, AllowBadUTF8_>*/ bool allow_bad_utf8);

    template<bool StackEmpty_, bool AllowComments_/*,
        bool AllowTrailing_, bool AllowBadUTF8_*/>
    const char* parse_object(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        std::integral_constant<bool, AllowComments_> allow_comments,
        /*std::integral_constant<bool, AllowTrailing_>*/ bool allow_trailing,
        /*std::integral_constant<bool, AllowBadUTF8_>*/ bool allow_bad_utf8);

    template<bool StackEmpty_, bool AllowComments_/*,
        bool AllowTrailing_, bool AllowBadUTF8_*/>
    const char* parse_array(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        std::integral_constant<bool, AllowComments_> allow_comments,
        /*std::integral_constant<bool, AllowTrailing_>*/ bool allow_trailing,
        /*std::integral_constant<bool, AllowBadUTF8_>*/ bool allow_bad_utf8);

    template<bool StackEmpty_>
    const char* parse_null(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty);

    template<bool StackEmpty_>
    const char* parse_true(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty);

    template<bool StackEmpty_>
    const char* parse_false(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty);

    template<bool StackEmpty_, bool IsKey_/*,
        bool AllowBadUTF8_*/>
    const char* parse_string(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        std::integral_constant<bool, IsKey_> is_key,
        /*std::integral_constant<bool, AllowBadUTF8_>*/ bool allow_bad_utf8);

    template<bool StackEmpty_, char First_>
    const char* parse_number(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        std::integral_constant<char, First_> first);

    template<bool StackEmpty_, bool IsKey_/*,
        bool AllowBadUTF8_*/>
    const char* parse_unescaped(const char* p,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        std::integral_constant<bool, IsKey_> is_key,
        /*std::integral_constant<bool, AllowBadUTF8_>*/ bool allow_bad_utf8);

    template<bool StackEmpty_/*, bool IsKey_,
        bool AllowBadUTF8_*/>
    const char* parse_escaped(
        const char* p,
        std::size_t total,
        std::integral_constant<bool, StackEmpty_> stack_empty,
        /*std::integral_constant<bool, IsKey_>*/ bool is_key,
        /*std::integral_constant<bool, AllowBadUTF8_>*/ bool allow_bad_utf8);

    // intentionally private
    std::size_t
    depth() const noexcept
    {
        return opt_.max_depth - depth_;
    }

public:
    /// Copy constructor (deleted)
    basic_parser(
        basic_parser const&) = delete;

    /// Copy assignment (deleted)
    basic_parser& operator=(
        basic_parser const&) = delete;

    /** Destructor.

        All dynamically allocated internal memory is freed.

        @par Effects
        @code
        this->handler().~Handler()
        @endcode

        @par Complexity
        Same as `~Handler()`.

        @par Exception Safety
        Same as `~Handler()`.
    */
    ~basic_parser() = default;

    /** Constructor.

        This function constructs the parser with
        the specified options, with any additional
        arguments forwarded to the handler's constructor.

        @par Complexity
        Same as `Handler( std::forward< Args >( args )... )`.

        @par Exception Safety
        Same as `Handler( std::forward< Args >( args )... )`.

        @param opt Configuration settings for the parser.
        If this structure is default constructed, the
        parser will accept only standard JSON.

        @param args Optional additional arguments
        forwarded to the handler's constructor.

        @see parse_options
    */
    template<class... Args>
    explicit
    basic_parser(
        parse_options const& opt,
        Args&&... args);

    /** Return a reference to the handler.

        This function provides access to the constructed
        instance of the handler owned by the parser.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    Handler&
    handler() noexcept
    {
        return h_;
    }

    /** Return a reference to the handler.

        This function provides access to the constructed
        instance of the handler owned by the parser.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    Handler const&
    handler() const noexcept
    {
        return h_;
    }

    /** Return the last error.

        This returns the last error code which
        was generated in the most recent call
        to @ref write_some.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    error_code
    last_error() const noexcept
    {
        return ec_;
    }

    /** Return true if a complete JSON has been parsed.

        This function returns `true` when all of these
        conditions are met:

        @li A complete serialized JSON has been
            presented to the parser, and

        @li No error or exception has occurred since the
            parser was constructed, or since the last call
            to @ref reset,

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

    /** Reset the state, to parse a new document.

        This function discards the current parsing
        state, to prepare for parsing a new document.
        Dynamically allocated temporary memory used
        by the implementation is not deallocated.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.
    */
    void
    reset() noexcept;

    /** Indicate a parsing failure.

        This changes the state of the parser to indicate
        that the parse has failed. A parser implementation
        can use this to fail the parser if needed due to
        external inputs.

        @note

        If `!ec`, the stored error code is unspecified.

        @par Complexity
        Constant.

        @par Exception Safety
        No-throw guarantee.

        @param ec The error code to set. If the code does
        not indicate failure, an implementation-defined
        error code that indicates failure will be stored
        instead.
    */
    void
    fail(error_code ec) noexcept;

    /** Parse some of an input string as JSON, incrementally.

        This function parses the JSON in the specified
        buffer, calling the handler to emit each SAX
        parsing event. The parse proceeds from the
        current state, which is at the beginning of a
        new JSON or in the middle of the current JSON
        if any characters were already parsed.
    \n
        The characters in the buffer are processed
        starting from the beginning, until one of the
        following conditions is met:

        @li All of the characters in the buffer
        have been parsed, or

        @li Some of the characters in the buffer
        have been parsed and the JSON is complete, or

        @li A parsing error occurs.

        The supplied buffer does not need to contain the
        entire JSON. Subsequent calls can provide more
        serialized data, allowing JSON to be processed
        incrementally. The end of the serialized JSON
        can be indicated by passing `more = false`.

        @par Complexity
        Linear in `size`.

        @par Exception Safety
        Basic guarantee.
        Calls to the handler may throw.
        Upon error or exception, subsequent calls will
        fail until @ref reset is called to parse a new JSON.

        @return The number of characters successfully
        parsed, which may be smaller than `size`.

        @param more `true` if there are possibly more
        buffers in the current JSON, otherwise `false`.

        @param data A pointer to a buffer of `size`
        characters to parse.

        @param size The number of characters pointed to
        by `data`.

        @param ec Set to the error, if any occurred.
    */
/** @{ */
    std::size_t
    write_some(
        bool more,
        char const* data,
        std::size_t size,
        error_code& ec);

    std::size_t
    write_some(
        bool more,
        char const* data,
        std::size_t size,
        std::error_code& ec);
/** @} */
};

BOOST_JSON_NS_END

#endif

/* basic_parser.hpp
Guq0DKNN39tVH7S75Sv3zr6l8zj0OjPMyyMpvTB5JiVmWCvW3Oz+fvLFlKY+26H6RiQ44enEeW+QHxb9q975Iuu//xI5mdd+7CQfFpbZCAczZ3QekHa1APtY85B29bDAmGtccnx1mvmHDjVpPjGCUTMkaEGDINtpW7pfvGPlSmJP0g69coBCHoRDrKmtoIpLMMyZR32xYu7yvQLbNMR2Iokd1itrPaZaNQVUSrmtd9ExIRgAESzu00x0nblfbEurQdINKNDOJN3sPWwKn2+/cYS/WichCxBxqbKpYTTgFLjgbPVsyWY16gKgAGd3DRoLZX/H8pz9EZvUgzGgEAT096Ohpe0ZmA+xCZj6AMp2J/+5FzHLawlvwk9o1/IQgNxJmKcoMtCoMwHoNnZcc3zyuR6+AXrQl3iXJD9hJMDA/eLPi5OgAFfLoa3+zVZco6w8LY7NQpDIFCleLQOqpcp+2QK1o3sUugJSd4cTjgdyMMk5QALRAs2U3sfDA3Wz75SD5c70jq3SgLY/uwpJA3LyBi0xmZjotIaoE+UXrUO1vDDWNq9mC9Qd38zt0wqES9fcOEWKN6OHIBRAMtRUVSc5HQDrhARtbaWSMmHJEW1QADI6Kc/F7Zod1ieygf4Q2KBn19pd2uELb0SOtb0j7CV0o5cRQ4DqMODIWEQ+KyEDYQD0FZkMSHSB+jidpvOTaOuD3jWtV4sEkS1Q2Xlh27Phl2+YGFJncoHpCiy1/xAGmIIZ35qRmBoWgpFEHpJKDap/dK9xhvyZgDf7v12xVLdeYKZ4YgMQNNg4gTwDeIJqeJOc5hEsAEAA/qLwK3vSXYGhhFYYG9t/GvQ7XTgROWGBt7L3NxGgA+KNgT6F1pD+gvyg+x6hm8ZSg9kA3l+3Hz3YRJCOHv6IfTgAAOCiAhlgDPpE1b/zZaUoJFwlw6mum2kP50vST5zfcvvU3avNQHKRC1ygo2/8/8gZViNgQBPMEaWxKDoAvZsXOPElsjHjB2Pjko2Vv00KfvsE3tgpPwS6v3ZUiDJDiS0eb7Im7BsmWk2xjrxKLnlyKfc/OVbVplHAN86lC5YyHK83sjDd0reGRQtoaJFmkro3lYbq5R0vUELQbBU+YMDke/is86lo4mTrcJb5bK94rTM3Jr6uhDxN2BU+1/1XqXntWTtM+mgpnIFZ0q9c3kC02aW1NM3qsEPDBcD9AfyFpAAB/H/92EkLIahECJYzSxj5SThcoVdtj64o5My6uG/lSf/VScIP5TOu57F4z6KjbWsPjYtIYfX5X+6xVoqvTRefpPIoNTDEBZUV08vZIaE4JqSCu2yiW5IN2IlJqO4BzbtzqsgLvrMzgY4XP0hvu2iP3e4ImArZhiASsSMG5OoF/7fQt8oeQjEtTZbkuyBD+PBKsSE78s9VBRHVRVKyT2GIMkgpNxLlBmwhIS1oRKGt2U+Hj1a4w8VnM6tA5IW5XjLpKaXwDniyKtNy5blCmcRG6CuR5Pe3T4c4J6gLi4CADA8XefvMdp/PXKmXrn3wueduTe36wQoaSGr3pAVQwYlHY6DrYKwofmxrEj+WTFo/nvq2G/ea0bMwyZ9ftFnYprDx6lc00996uVOGG24ExIuzXw3LvX3q3yrL4j0unbh796aAso1QveAc6GmCxx7FwK6Xj0O9931JqtF9E4Zlq0NqlQYLWSoR6UF+BngvQKK8DKrUp298aPoQNZg3Akmu73ILPkrrJed9zsEajf9VBlLBGXoy2r/yRPEhQmmkDXEWypmPV5n9y8I/4m7zMkqSr2FxoinlW74/rwuyS7BW15L0vjps/YWd6pms4D6UwNCfuS3AcUz9UPUmi64AaGiJqeoVGKvyONEQtGb2R7Jo7BA9XsULKDxnKIAsCBUqGxnXL6BwSb4ybXmqHhgLW+lbfW4kJnhpRyXnLD+5fOJoi7oQBSvRtkjxNwfLd48bofK4tDCpw78k4PmFpZ5019Wj920uMYy6naHGtQoK7k4jOG7v6nsWHZjkfdHD/yG2ZaBnib7eOpejQrYzk/EtUIsPmdshLQpOlCLgzFmWQtFCPsX7P7UU9fSWKKOlYc858oVYPnOFrI05wRTmSRXu7bW4WI40yB4CfseLtp661rMSPQ42Ujn34rDmqFwtXYygGa2LjHb7WDlO7dJmGIZTrV09rP9o0GPXm+GLy485Issvuc0Lfs1Ta/XpINGnkeecIo0FcQBGZhJvVm1XdNkjwqPAZXxMu4c7bAg2k+fP98tVsgrgExAb2tW54UHW2fMVEBmOD/XtDIR8a2BlgDTFADQoDYL9B18y1FpdBohh7UPGTZJJKNn8wA1WjfDICUwGc6njYotPvvIo8QybggJP+GsvgIxF3+Lg2tUyfJFth64qGyzv5OcCG7vMLJLTXbK3ZnjjXzO/m0DZjzaTU3KZXFxGTV9HLbf4A4usz/ndFnZ/UtbpBSQH94Y9rNgb1OtUbnhD6NfAAzFLcnMtfYQ/R4ODPYXTTO7hxyadVgjqkUGJufd4j2DpSCifJgfQih2nQuWng8AALNHdMgAm9bnvMyIEVcZFaAGv7tPS1cU9DPOLvlM9CSf/op7iTain5lDloU8awJKNQ1Wqdm2lReo0UtAa2CJIUZNA9x/7EyMNtZoRZDdW2l4JadxdpCezhLT9W6CyGSfumN208QKr3hInyVnBMQ4zo0s8Zcf1GHWuLWRBThg6/uIO4OHVPxP+zCrAhm7eWdcKmMwhhqoSmAZV3uYEAHE9dB2MmJvvEVbw3p5UROIs2XLOjGQiFRiEaHFnQuBKxxl7VmUCd5sBxZW9HvyW2Hre4f7evEI37XoRjDAkKicIl3CK77Okpak8+ZFb+ARpfKBI53uJRAbNl/AtxO87u3SZI2odiU9U2CuoBmx1AHNV013tNfh5fo3gb5uPLq05cZGz10bOKwQh28lyoTYZ/8a4FjYkELY0HkgTOG9xAsLQ42hEDMQNA3GClXEz3N5x60bTaAdDIhV5HaSuNzrr/0o/uT18TZcGdkx28X4ToToJNGDyv0P2pandjJ0nTnWdoBuG3IpXUuK5VMz/CVNm7l5Mc51p5e7WsvxKPjNcN90A2MJdnbMMTUllgIzyhAPl8Ayji8ZxuoSM5/JcCkRiwaH2VPHYUWnPfXFeFCexdJt59Nh0j9vSkH58cCyDoq6yiJf2J2DqvNrRDfU9/+Ygpc9Ui/ZWG7pFBbCMeC/ENDp8r2MSz3oDCi34cvGlx/c/EkjoOgGJBmHJuP6OFjll5ZUfEGoi2an+qpSvvH14uPjQz4U+E4cHXIMLlHRElloQvxfvUAJoFJ/x2YHriTFC4iPj+hLFPdxZ8Av0Zr0KHuZcdHmSkZ1S8g5Kl62NjTxKCzMJrYtatx16NZNdy8YODsgUmrPJh1SMQ7d1MAAPWCKTcZw8qopGoLYReioPZ2QNCNXJRyMygHE5SSZUHN/YQ6B6olMtRBzGf5K4HxvBRWGCryUX7CWPd61KXZC6odRg6VZanL+FOqrzsKxvcJMV1XekK0gkA7hnrcJ3K54PeeM6ceHw8BJjTAmmgOFyRMobIUfx6BYlX7lqRle14q4ljVDp0lYi6QpzIBKYTmHuOAjawzwhCQxxPeWACY3SWYsRhfcxLPKsebI5Tej1K5r3HhVJb/0PnIBjf/o+CWbydcL6TKmH4cH7v3vRknPJeb7Bbfr9wcMoNTrTnqteVZyUfbu8FCPz7lsCULkWg6cj5Pm/G6MrtwBMvIJCUCUQoV+4LlWlE8cj8B4UmjXJ2a/4nBiUZbJZZFz4GhAAAGc3bpX/o7gHFnyffr/jt84EywB0IRpU3aWJR0SoUKQhIVElK0lQQ0ICEoWGCBsYD5s4JNSIz+v4rzLnumYyOuwfT3ydS2E69dI0vS6eQp6jlQtlymNUtVJl5kZERpqVaj2Uc/OYmMbOtSRQYimwoK0V8aDQTYCqCsKLrGC6bR5e5W7xsB66SAQLioNssk1IwD4T0qyDHMSi45jtYrHnXY+AzoPUhBYwWM5j3yRjx9X5xk0+A7rMzuFJsmYh0qXVVUeIVs/bsVgLD882pxZQESRZ0TktO5DbC4z/jHQpDmAlQDShSBCCBxSAhgDPgADgLBiGCgUg2cIoIMNtYjDExQwAIja//Pp8gAFX2lKaaMK2+L945k8CvO9k4xFojZG9c6InRegRfrnjOhSEJ0AD6gAAAT4BngglpkJW//toy19D5O1mBBk9B69pL0HRw7Vo6lVdiyanoLTIeAaW6aFbyDGoJsPAuvn364C9vfd46C++ITODUwhkfkxyRtR/gDCnvsv7kNZv54Nntyj1E+t0X6e2Hnc9IzTbl0qAy0AYhW7u8y1Y1ScQsps0ihLsVReXrIbfmyhHxSMpW07XvgMWOmiuykqhQCuIVUPRGE2r5awtIp+v8O9tc3cnUH15cLt3QAP4+rpMBplvSzTe1h36Oys88JgPGY56CRFg4/VZlhI8RFVUJrG76fFE78xiTYR9Cos1F5WoEW/WsHWtsQwIpJt9MwFQdf27VUrAGwBguxPgkl3HuwkP/2kFjXAwim5h2mAAKy6GS7fdsEmQ4L3AmA45D9a1F6QSNqMeeKEpFSS1sHXseoCaLMEAfL+/lZlaU0IhGlTdqY0CR5EEhYlt6WBYQgSgWFQI7Pld3/UhDpZ+lUWculc3ROQIA7UsjzVyA/fGlWiieRh7KXuSmnFJxd3G5nVdjjcOdPVg97DXqrWc88cngBMXFPWQ231CytvQby8qckvfenKGGtOpBVUICiiqaHLMmxRh1JQ5LVOqnQ3rwU+Nlh3iScFqhuZgg14TZdMKPw0WAZ0pYZXh8WEuzv7kp7WA+51CKuEd7QdXhQeSS07PHztdgwXBN0xhnIUDoDOgA0AgYtqgemtalq1yl97bornQbu4KZqR7bAKiQAmTZsrAqQisUp+DaNjSdKH7WbPizdKNFEnhn1OXoqsJ1sgAhVaqY0VLTtw6RUzF4VvPlTy8PZwS3Qjje1gtva5cfFXyUsV0+ZVxpsUEqjhDxECkxDvvySrPB7ap8mGYPCEaFLWaGIhQkJgoMTgJUag3F2CrF0myuBKACdicShROORSLMLaJMfJd5ABe2um6p8Dp1cmufsMkbYIk6rmzHysqca++Qto4ViSCZyL35s/i/5rW/xh8Bsv3EeBExbkLtvehHQvrwjwUhSlG1XQkUiua7Pu3CkX7WG+eq1RvBRMqaApELDpRPxslTqOweq8NSZPfph1sYqxlQqrczVy6nE+mDIQNn/r/2vh/J2vfBUpyYQdY0VJi4bs/5NfGsvQgDCCGohUAjWQQRTVgHQLbCiWPU5HebuM0SyUGoKGiW5HvZrlrLIj4go190ME+YAuv1XVk31VcEp8vCal8ME5p9RgkAST0VaupttIQo5VVHpsMvY9dx0F1NB21Nntp9jKkV7MLgBKE1ioojZu2edB7F8QAAAENAZ4IKaZCVv/kKx0eAX4zzunSNRhZMRFdPONh43hOWDxh6hscTPeaH9DR7XrZaZPGdvXSmjtkPAol89cWYGOIn8XbrWNMibKMT6hoqYKsaUBbTTqLC3SaqAYotPbCZ3cqpsDbww9aCsRgogzNwDCXMb+Jj5fCjfUHfnkCDdvwwd48p4NNLUvAUIIYIMMHzaMQO5W8OfMZHDkifPTn2vvvMZHJZy+AQ4z1nppfVtS24e0aq8NL38cnNA5OS5s1d1q8dhJthF96gW3o6w3/vYCh4OahpKx8hAr+adgAAAMAABhtsW9hhk6ILv+aPY7Lm64W2VS4Z4meVFP70HO/HIHvO6r0K71mZkMLTREP0EAhGlS1lptiY6CUKDFAIjelWqmkJQZaiLaLlU0YYgDs6RCNSlZiCADkrrfQ7JtAXl8h+0PfBVmQ/gnhQj+TvCvfHkeEvVVozExfNyT7RMjC424drnaVoFBGXv3j8mqd7zC4PrXFvieymlnFJy6y7OV2iz6IGfSzIcnrbs7Olvhsn+ffXeFEsoscRPOyDZLIpZURk1NlHPT26uEt42zafSAGmmiWBvA0wsnEui/PXV0rb1ojdjm+8bNu/Fxya7t2o7yJmkoWSkQLykRsgJjb5ONS2GNcUTsJShS2S5CD6F72pU7wAJOxwcyhAVAKqg4aBoXKpowxAHTuf7p444wDWqzd+Iwsg0iMoDwT6k/mvKxgJQ8nhLXDF/GIKH8AAxYZQPCkxRP4FYgWlT+MgD4hGhTdoZFlo8EQojScNg2VGTqkImLoULFcL46vfMOdNg0/TPNvIXwMpJ2T61EBsDVEdpOMMNlS1hpRUiBlm/rc3tlI6nU0sE9xTJU6i8XyeknHh1PHyGHX2QA/eGn7mhnOy9IflmYbZSKW6cQMnnpO6aXlzWaN0Cval1cgpQBEYaGavINKvAx3JPGoKLP4Cs6WZr+bVhmrb53Pz7TTocHDR9zViRQ98lj0GWYJSARGcZSjLLHAEg6lOOnfKy5Z4dHcaHw6j6+cqulz0+ztsjiLVKRNhNHTq3PpSSooQXUi/E7OPAeE0ACjDDqv3Qxi2Q+7Y0ve7HZzywxHx8AlxLBlm3NGW1vgi2hwnGKWjRJ2RjGMNgABlkiMMHTMMjMna62rNsv61JscNR8/6QAAAQgBnggtpkJW//UQLyh6ZMwXZ+nBoIL7QO3V9QPQAwqlHzP+ZpVY+KRjOOsDKs8OSrt0N4ayAf/XBinTMtBLJPL8nnsnxbn2xA2nSs2GkI2j59jAW2UsKLbglDXD+UniXo2SUAlLcPNiK0SZ3+Akhz3nleauOPG1t7ulxvAdDv8czycMFoMaCXRn/+Esalp7OP2lmdqbe3ZBB4ZV73GICcrlmsa+y/f/CkNlqjvYIIRB+0nw3zR9lU1pyivOvBzD3ZPskXmE3TsbnjH0GL0eHLcPtcEKa8i04MctcNglRop8ZTzJ9JAgc0qFRaaJUH5uhscmKj1eIiWLr9IK9Cl3a008tutoNWQ40JAhGlTVkgjIoVlgdCZBDEQKhUGwGtytCokrLME/Du9Swz1ZIGJaDdADgI40ux2IasCLARMem/k8x/nDzxqBKXa0E2a0qOQ8JnA7qhhbc+JIpBZsLByfVPt1Nfsr7k8jh6i4qrkvkN7NlUTsF6PyK5+0u5KopORo2kEoLi0iLiU6I32DPlMApYL9GsRyZHIuNB6JhugXh/V7fVjjRujm4h+dqH+DLCKamWzvvO6u962DNISU7SFn8ar68D7xvjDZTp5D5uJO/pEuyXVyT03wv4xqonHeJRMDJMKPW4AYKE6IKidwiiKjVnOYaSR7MbjAc7QDvcq9FJPOCEn064rq/Nxwuar6QUdfdTnngEifaAQhNUCboiJDjUlKAFHrTGWEaymSOaPHfeKNJTu8AzkhGhTFoZNjo0FYqEAbsrG1SKlTWGqSVADiNZOy1w30HkSTwc2NthcraYVZPYHgjoCtMiVEcA91H0Sf0RcSAdp4OxOCIdB8xpe4HAFhR1pD6l2JGfMnFvh+qJjR9jtyeqtznkwpgL4Y5nHvtWDrkesdBLqoMpZPTFkg/0D8sKnnLmXJSd+HzDOFZVgmN++P5r1fHSSvPNpCWrHReqLNF+vDTEhIjxqdQF61WQg7DAKk9EhhpgQVOZp1NOwhnw6G
*/