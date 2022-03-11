//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_BASIC_PARSER_HPP
#define BOOST_BEAST_HTTP_BASIC_PARSER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/http/field.hpp>
#include <boost/beast/http/verb.hpp>
#include <boost/beast/http/detail/basic_parser.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <boost/assert.hpp>
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A parser for decoding HTTP/1 wire format messages.

    This parser is designed to efficiently parse messages in the
    HTTP/1 wire format. It allocates no memory when input is
    presented as a single contiguous buffer, and uses minimal
    state. It will handle chunked encoding and it understands
    the semantics of the Connection, Content-Length, and Upgrade
    fields.
    The parser is optimized for the case where the input buffer
    sequence consists of a single contiguous buffer. The
    @ref beast::basic_flat_buffer class is provided, which guarantees
    that the input sequence of the stream buffer will be represented
    by exactly one contiguous buffer. To ensure the optimum performance
    of the parser, use @ref beast::basic_flat_buffer with HTTP algorithms
    such as @ref read, @ref read_some, @ref async_read, and @ref async_read_some.
    Alternatively, the caller may use custom techniques to ensure that
    the structured portion of the HTTP message (header or chunk header)
    is contained in a linear buffer.

    The interface to the parser uses virtual member functions.
    To use this class, derive your type from @ref basic_parser. When
    bytes are presented, the implementation will make a series of zero
    or more calls to virtual functions, which the derived class must
    implement.

    Every virtual function must be provided by the derived class,
    or else a compilation error will be generated. The implementation
    will make sure that `ec` is clear before each virtual function
    is invoked. If a virtual function sets an error, it is propagated
    out of the parser to the caller.

    @tparam isRequest A `bool` indicating whether the parser will be
    presented with request or response message.

    @note If the parser encounters a field value with obs-fold
    longer than 4 kilobytes in length, an error is generated.
*/
template<bool isRequest>
class basic_parser
    : private detail::basic_parser_base
{
    std::uint64_t body_limit_ =
        default_body_limit(is_request{});   // max payload body
    std::uint64_t len_ = 0;                 // size of chunk or body
    std::uint64_t len0_ = 0;                // content length if known
    std::unique_ptr<char[]> buf_;           // temp storage
    std::size_t buf_len_ = 0;               // size of buf_
    std::size_t skip_ = 0;                  // resume search here
    std::uint32_t header_limit_ = 8192;     // max header size
    unsigned short status_ = 0;             // response status
    state state_ = state::nothing_yet;      // initial state
    unsigned f_ = 0;                        // flags

    // limit on the size of the stack flat buffer
    static std::size_t constexpr max_stack_buffer = 8192;

    // Message will be complete after reading header
    static unsigned constexpr flagSkipBody              = 1<<  0;

    // Consume input buffers across semantic boundaries
    static unsigned constexpr flagEager                 = 1<<  1;

    // The parser has read at least one byte
    static unsigned constexpr flagGotSome               = 1<<  2;

    // Message semantics indicate a body is expected.
    // cleared if flagSkipBody set
    //
    static unsigned constexpr flagHasBody               = 1<<  3;

    static unsigned constexpr flagHTTP11                = 1<<  4;
    static unsigned constexpr flagNeedEOF               = 1<<  5;
    static unsigned constexpr flagExpectCRLF            = 1<<  6;
    static unsigned constexpr flagConnectionClose       = 1<<  7;
    static unsigned constexpr flagConnectionUpgrade     = 1<<  8;
    static unsigned constexpr flagConnectionKeepAlive   = 1<<  9;
    static unsigned constexpr flagContentLength         = 1<< 10;
    static unsigned constexpr flagChunked               = 1<< 11;
    static unsigned constexpr flagUpgrade               = 1<< 12;
    static unsigned constexpr flagFinalChunk            = 1<< 13;

    static constexpr
    std::uint64_t
    default_body_limit(std::true_type)
    {
        // limit for requests
        return 1 * 1024 * 1024; // 1MB
    }

    static constexpr
    std::uint64_t
    default_body_limit(std::false_type)
    {
        // limit for responses
        return 8 * 1024 * 1024; // 8MB
    }

    template<bool OtherIsRequest>
    friend class basic_parser;

    friend class basic_parser_test;

protected:
    /// Default constructor
    basic_parser() = default;

    /** Move constructor

        @note

        After the move, the only valid operation on the
        moved-from object is destruction.
    */
    basic_parser(basic_parser &&) = default;

    /// Move assignment
    basic_parser& operator=(basic_parser &&) = default;

public:
    /// `true` if this parser parses requests, `false` for responses.
    using is_request =
        std::integral_constant<bool, isRequest>;

    /// Destructor
    virtual ~basic_parser() = default;

    /// Copy constructor
    basic_parser(basic_parser const&) = delete;

    /// Copy assignment
    basic_parser& operator=(basic_parser const&) = delete;

    /// Returns `true` if the parser has received at least one byte of input.
    bool
    got_some() const
    {
        return state_ != state::nothing_yet;
    }

    /** Returns `true` if the message is complete.

        The message is complete after the full header is prduced
        and one of the following is true:

        @li The skip body option was set.

        @li The semantics of the message indicate there is no body.

        @li The semantics of the message indicate a body is expected,
        and the entire body was parsed.
    */
    bool
    is_done() const
    {
        return state_ == state::complete;
    }

    /** Returns `true` if a the parser has produced the full header.
    */
    bool
    is_header_done() const
    {
        return state_ > state::fields;
    }

    /** Returns `true` if the message is an upgrade message.

        @note The return value is undefined unless
        @ref is_header_done would return `true`.
    */
    bool
    upgrade() const
    {
        return (f_ & flagConnectionUpgrade) != 0;
    }

    /** Returns `true` if the last value for Transfer-Encoding is "chunked".

        @note The return value is undefined unless
        @ref is_header_done would return `true`.
    */
    bool
    chunked() const
    {
        return (f_ & flagChunked) != 0;
    }

    /** Returns `true` if the message has keep-alive connection semantics.

        This function always returns `false` if @ref need_eof would return
        `false`.

        @note The return value is undefined unless
        @ref is_header_done would return `true`.
    */
    bool
    keep_alive() const;

    /** Returns the optional value of Content-Length if known.

        @note The return value is undefined unless
        @ref is_header_done would return `true`.
    */
    boost::optional<std::uint64_t>
    content_length() const;

    /** Returns the remaining content length if known

        If the message header specifies a Content-Length,
        the return value will be the number of bytes remaining
        in the payload body have not yet been parsed.

        @note The return value is undefined unless
              @ref is_header_done would return `true`.
    */
    boost::optional<std::uint64_t>
    content_length_remaining() const;

    /** Returns `true` if the message semantics require an end of file.

        Depending on the contents of the header, the parser may
        require and end of file notification to know where the end
        of the body lies. If this function returns `true` it will be
        necessary to call @ref put_eof when there will never be additional
        data from the input.
    */
    bool
    need_eof() const
    {
        return (f_ & flagNeedEOF) != 0;
    }

    /** Set the limit on the payload body.

        This function sets the maximum allowed size of the payload body,
        before any encodings except chunked have been removed. Depending
        on the message semantics, one of these cases will apply:

        @li The Content-Length is specified and exceeds the limit. In
        this case the result @ref error::body_limit is returned
        immediately after the header is parsed.

        @li The Content-Length is unspecified and the chunked encoding
        is not specified as the last encoding. In this case the end of
        message is determined by the end of file indicator on the
        associated stream or input source. If a sufficient number of
        body payload octets are presented to the parser to exceed the
        configured limit, the parse fails with the result
        @ref error::body_limit

        @li The Transfer-Encoding specifies the chunked encoding as the
        last encoding. In this case, when the number of payload body
        octets produced by removing the chunked encoding  exceeds
        the configured limit, the parse fails with the result
        @ref error::body_limit.
        
        Setting the limit after any body octets have been parsed
        results in undefined behavior.

        The default limit is 1MB for requests and 8MB for responses.

        @param v The payload body limit to set
    */
    void
    body_limit(std::uint64_t v)
    {
        body_limit_ = v;
    }

    /** Set a limit on the total size of the header.

        This function sets the maximum allowed size of the header
        including all field name, value, and delimiter characters
        and also including the CRLF sequences in the serialized
        input. If the end of the header is not found within the
        limit of the header size, the error @ref error::header_limit
        is returned by @ref put.

        Setting the limit after any header octets have been parsed
        results in undefined behavior.
    */
    void
    header_limit(std::uint32_t v)
    {
        header_limit_ = v;
    }

    /// Returns `true` if the eager parse option is set.
    bool
    eager() const
    {
        return (f_ & flagEager) != 0;
    }

    /** Set the eager parse option.

        Normally the parser returns after successfully parsing a structured
        element (header, chunk header, or chunk body) even if there are octets
        remaining in the input. This is necessary when attempting to parse the
        header first, or when the caller wants to inspect information which may
        be invalidated by subsequent parsing, such as a chunk extension. The
        `eager` option controls whether the parser keeps going after parsing
        structured element if there are octets remaining in the buffer and no
        error occurs. This option is automatically set or cleared during certain
        stream operations to improve performance with no change in functionality.

        The default setting is `false`.

        @param v `true` to set the eager parse option or `false` to disable it.
    */
    void
    eager(bool v)
    {
        if(v)
            f_ |= flagEager;
        else
            f_ &= ~flagEager;
    }

    /// Returns `true` if the skip parse option is set.
    bool
    skip() const
    {
        return (f_ & flagSkipBody) != 0;
    }

    /** Set the skip parse option.

        This option controls whether or not the parser expects to see an HTTP
        body, regardless of the presence or absence of certain fields such as
        Content-Length or a chunked Transfer-Encoding. Depending on the request,
        some responses do not carry a body. For example, a 200 response to a
        CONNECT request from a tunneling proxy, or a response to a HEAD request.
        In these cases, callers may use this function inform the parser that
        no body is expected. The parser will consider the message complete
        after the header has been received.

        @param v `true` to set the skip body option or `false` to disable it.

        @note This function must called before any bytes are processed.
    */
    void
    skip(bool v);

    /** Write a buffer sequence to the parser.

        This function attempts to incrementally parse the HTTP
        message data stored in the caller provided buffers. Upon
        success, a positive return value indicates that the parser
        made forward progress, consuming that number of
        bytes.

        In some cases there may be an insufficient number of octets
        in the input buffer in order to make forward progress. This
        is indicated by the code @ref error::need_more. When
        this happens, the caller should place additional bytes into
        the buffer sequence and call @ref put again.

        The error code @ref error::need_more is special. When this
        error is returned, a subsequent call to @ref put may succeed
        if the buffers have been updated. Otherwise, upon error
        the parser may not be restarted.

        @param buffers An object meeting the requirements of
        <em>ConstBufferSequence</em> that represents the next chunk of
        message data. If the length of this buffer sequence is
        one, the implementation will not allocate additional memory.
        The class @ref beast::basic_flat_buffer is provided as one way to
        meet this requirement

        @param ec Set to the error, if any occurred.

        @return The number of octets consumed in the buffer
        sequence. The caller should remove these octets even if the
        error is set.
    */
    template<class ConstBufferSequence>
    std::size_t
    put(ConstBufferSequence const& buffers, error_code& ec);

#if ! BOOST_BEAST_DOXYGEN
    std::size_t
    put(net::const_buffer buffer,
        error_code& ec);
#endif

    /** Inform the parser that the end of stream was reached.

        In certain cases, HTTP needs to know where the end of
        the stream is. For example, sometimes servers send
        responses without Content-Length and expect the client
        to consume input (for the body) until EOF. Callbacks
        and errors will still be processed as usual.

        This is typically called when a read from the
        underlying stream object sets the error code to
        `net::error::eof`.

        @note Only valid after parsing a complete header.

        @param ec Set to the error, if any occurred. 
    */
    void
    put_eof(error_code& ec);

protected:
    /** Called after receiving the request-line.

        This virtual function is invoked after receiving a request-line
        when parsing HTTP requests.
        It can only be called when `isRequest == true`.

        @param method The verb enumeration. If the method string is not
        one of the predefined strings, this value will be @ref verb::unknown.

        @param method_str The unmodified string representing the verb.

        @param target The request-target.

        @param version The HTTP-version. This will be 10 for HTTP/1.0,
        and 11 for HTTP/1.1.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.
    */
    virtual
    void
    on_request_impl(
        verb method,
        string_view method_str,
        string_view target,
        int version,
        error_code& ec) = 0;

    /** Called after receiving the status-line.

        This virtual function is invoked after receiving a status-line
        when parsing HTTP responses.
        It can only be called when `isRequest == false`.

        @param code The numeric status code.

        @param reason The reason-phrase. Note that this value is
        now obsolete, and only provided for historical or diagnostic
        purposes.

        @param version The HTTP-version. This will be 10 for HTTP/1.0,
        and 11 for HTTP/1.1.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.
    */
    virtual
    void
    on_response_impl(
        int code,
        string_view reason,
        int version,
        error_code& ec) = 0;

    /** Called once for each complete field in the HTTP header.

        This virtual function is invoked for each field that is received
        while parsing an HTTP message.

        @param name The known field enum value. If the name of the field
        is not recognized, this value will be @ref field::unknown.

        @param name_string The exact name of the field as received from
        the input, represented as a string.

        @param value A string holding the value of the field.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.
    */
    virtual
    void
    on_field_impl(
        field name,
        string_view name_string,
        string_view value,
        error_code& ec) = 0;

    /** Called once after the complete HTTP header is received.

        This virtual function is invoked once, after the complete HTTP
        header is received while parsing a message.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.
    */
    virtual
    void
    on_header_impl(error_code& ec) = 0;

    /** Called once before the body is processed.

        This virtual function is invoked once, before the content body is
        processed (but after the complete header is received).

        @param content_length A value representing the content length in
        bytes if the length is known (this can include a zero length).
        Otherwise, the value will be `boost::none`.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.
    */
    virtual
    void
    on_body_init_impl(
        boost::optional<std::uint64_t> const& content_length,
        error_code& ec) = 0;

    /** Called each time additional data is received representing the content body.

        This virtual function is invoked for each piece of the body which is
        received while parsing of a message. This function is only used when
        no chunked transfer encoding is present.

        @param body A string holding the additional body contents. This may
        contain nulls or unprintable characters.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.

        @see on_chunk_body_impl
    */
    virtual
    std::size_t
    on_body_impl(
        string_view body,
        error_code& ec) = 0;

    /** Called each time a new chunk header of a chunk encoded body is received.

        This function is invoked each time a new chunk header is received.
        The function is only used when the chunked transfer encoding is present.

        @param size The size of this chunk, in bytes.

        @param extensions A string containing the entire chunk extensions.
        This may be empty, indicating no extensions are present.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.
    */
    virtual
    void
    on_chunk_header_impl(
        std::uint64_t size,
        string_view extensions,
        error_code& ec) = 0;

    /** Called each time additional data is received representing part of a body chunk.

        This virtual function is invoked for each piece of the body which is
        received while parsing of a message. This function is only used when
        no chunked transfer encoding is present.

        @param remain The number of bytes remaining in this chunk. This includes
        the contents of passed `body`. If this value is zero, then this represents
        the final chunk.

        @param body A string holding the additional body contents. This may
        contain nulls or unprintable characters.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.

        @return This function should return the number of bytes actually consumed
        from the `body` value. Any bytes that are not consumed on this call
        will be presented in a subsequent call.

        @see on_body_impl
    */
    virtual
    std::size_t
    on_chunk_body_impl(
        std::uint64_t remain,
        string_view body,
        error_code& ec) = 0;

    /** Called once when the complete message is received.

        This virtual function is invoked once, after successfully parsing
        a complete HTTP message.

        @param ec An output parameter which the function may set to indicate
        an error. The error will be clear before this function is invoked.
    */
    virtual
    void
    on_finish_impl(error_code& ec) = 0;

private:

    boost::optional<std::uint64_t>
    content_length_unchecked() const;

    template<class ConstBufferSequence>
    std::size_t
    put_from_stack(
        std::size_t size,
        ConstBufferSequence const& buffers,
        error_code& ec);

    void
    maybe_need_more(
        char const* p, std::size_t n,
            error_code& ec);

    void
    parse_start_line(
        char const*& p, char const* last,
            error_code& ec, std::true_type);

    void
    parse_start_line(
        char const*& p, char const* last,
            error_code& ec, std::false_type);

    void
    parse_fields(
        char const*& p, char const* last,
            error_code& ec);

    void
    finish_header(
        error_code& ec, std::true_type);

    void
    finish_header(
        error_code& ec, std::false_type);

    void
    parse_body(char const*& p,
        std::size_t n, error_code& ec);

    void
    parse_body_to_eof(char const*& p,
        std::size_t n, error_code& ec);

    void
    parse_chunk_header(char const*& p,
        std::size_t n, error_code& ec);

    void
    parse_chunk_body(char const*& p,
        std::size_t n, error_code& ec);

    void
    do_field(field f,
        string_view value, error_code& ec);
};

} // http
} // beast
} // boost

#include <boost/beast/http/impl/basic_parser.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/impl/basic_parser.ipp>
#endif

#endif

/* basic_parser.hpp
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
*/