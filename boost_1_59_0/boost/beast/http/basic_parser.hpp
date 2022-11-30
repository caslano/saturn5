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
    boost::optional<std::uint64_t>
        body_limit_ =
            boost::optional<std::uint64_t>(
                default_body_limit(is_request{}));   // max payload body
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

        @param v An optional integral value representing the body limit.
        If this is equal to `boost::none`, then the body limit is disabled.
    */
    void
    body_limit(boost::optional<std::uint64_t> v)
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
+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
*/