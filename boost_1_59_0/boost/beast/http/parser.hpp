//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_PARSER_HPP
#define BOOST_BEAST_HTTP_PARSER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/http/basic_parser.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** An HTTP/1 parser for producing a message.

    This class uses the basic HTTP/1 wire format parser to convert
    a series of octets into a @ref message using the @ref basic_fields
    container to represent the fields.

    @tparam isRequest Indicates whether a request or response
    will be parsed.

    @tparam Body The type used to represent the body. This must
    meet the requirements of <em>Body</em>.

    @tparam Allocator The type of allocator used with the
    @ref basic_fields container.

    @note A new instance of the parser is required for each message.
*/
template<
    bool isRequest,
    class Body,
    class Allocator = std::allocator<char>>
class parser
    : public basic_parser<isRequest>
{
    static_assert(is_body<Body>::value,
        "Body type requirements not met");

    static_assert(is_body_reader<Body>::value,
        "BodyReader type requirements not met");

    template<bool, class, class>
    friend class parser;

    message<isRequest, Body, basic_fields<Allocator>> m_;
    typename Body::reader rd_;
    bool rd_inited_ = false;
    bool used_ = false;

    std::function<void(
        std::uint64_t,
        string_view,
        error_code&)> cb_h_;

    std::function<std::size_t(
        std::uint64_t,
        string_view,
        error_code&)> cb_b_;

public:
    /// The type of message returned by the parser
    using value_type =
        message<isRequest, Body, basic_fields<Allocator>>;

    /// Destructor
    ~parser() = default;

    /// Constructor (disallowed)
    parser(parser const&) = delete;

    /// Assignment (disallowed)
    parser& operator=(parser const&) = delete;

    /// Constructor (disallowed)
    parser(parser&& other) = delete;

    /// Constructor
    parser();

    /** Constructor

        @param args Optional arguments forwarded to the 
        @ref http::message constructor.

        @note This function participates in overload
        resolution only if the first argument is not a
        @ref parser.
    */
#if BOOST_BEAST_DOXYGEN
    template<class... Args>
    explicit
    parser(Args&&... args);
#else
    template<class Arg1, class... ArgN,
        class = typename std::enable_if<
            ! detail::is_parser<typename
                std::decay<Arg1>::type>::value>::type>
    explicit
    parser(Arg1&& arg1, ArgN&&... argn);
#endif

    /** Construct a parser from another parser, changing the Body type.

        This constructs a new parser by move constructing the
        header from another parser with a different body type. The
        constructed-from parser must not have any parsed body octets or
        initialized <em>BodyReader</em>, otherwise an exception is generated.

        @par Example
        @code
        // Deferred body type commitment
        request_parser<empty_body> req0;
        ...
        request_parser<string_body> req{std::move(req0)};
        @endcode

        If an exception is thrown, the state of the constructed-from
        parser is undefined.

        @param parser The other parser to construct from. After
        this call returns, the constructed-from parser may only
        be destroyed.

        @param args Optional arguments forwarded to the message
        constructor.

        @throws std::invalid_argument Thrown when the constructed-from
        parser has already initialized a body reader.

        @note This function participates in overload resolution only
        if the other parser uses a different body type.
    */
#if BOOST_BEAST_DOXYGEN
    template<class OtherBody, class... Args>
#else
    template<class OtherBody, class... Args,
        class = typename std::enable_if<
            ! std::is_same<Body, OtherBody>::value>::type>
#endif
    explicit
    parser(parser<isRequest, OtherBody,
        Allocator>&& parser, Args&&... args);

    /** Returns the parsed message.

        Depending on the parser's progress,
        parts of this object may be incomplete.
    */
    value_type const&
    get() const
    {
        return m_;
    }

    /** Returns the parsed message.

        Depending on the parser's progress,
        parts of this object may be incomplete.
    */
    value_type&
    get()
    {
        return m_;
    }

    /** Returns ownership of the parsed message.

        Ownership is transferred to the caller.
        Depending on the parser's progress,
        parts of this object may be incomplete.

        @par Requires

        @ref value_type is @b MoveConstructible
    */
    value_type
    release()
    {
        static_assert(std::is_move_constructible<decltype(m_)>::value,
            "MoveConstructible requirements not met");
        return std::move(m_);
    }

    /** Set a callback to be invoked on each chunk header.

        The callback will be invoked once for every chunk in the message
        payload, as well as once for the last chunk. The invocation 
        happens after the chunk header is available but before any body
        octets have been parsed.

        The extensions are provided in raw, validated form, use
        @ref chunk_extensions::parse to parse the extensions into a
        structured container for easier access.
        The implementation type-erases the callback without requiring
        a dynamic allocation. For this reason, the callback object is
        passed by a non-constant reference.

        @par Example
        @code
        auto callback =
            [](std::uint64_t size, string_view extensions, error_code& ec)
            {
                //...
            };
        parser.on_chunk_header(callback);
        @endcode

        @param cb The function to set, which must be invocable with
        this equivalent signature:
        @code
        void
        on_chunk_header(
            std::uint64_t size,         // Size of the chunk, zero for the last chunk
            string_view extensions,     // The chunk-extensions in raw form
            error_code& ec);            // May be set by the callback to indicate an error
        @endcode
    */
    template<class Callback>
    void
    on_chunk_header(Callback& cb)
    {
        // Callback may not be constant, caller is responsible for
        // managing the lifetime of the callback. Copies are not made.
        BOOST_STATIC_ASSERT(! std::is_const<Callback>::value);

        // Can't set the callback after receiving any chunk data!
        BOOST_ASSERT(! rd_inited_);

        cb_h_ = std::ref(cb);
    }

    /** Set a callback to be invoked on chunk body data

        The provided function object will be invoked one or more times
        to provide buffers corresponding to the chunk body for the current
        chunk. The callback receives the number of octets remaining in this
        chunk body including the octets in the buffer provided.

        The callback must return the number of octets actually consumed.
        Any octets not consumed will be presented again in a subsequent
        invocation of the callback.
        The implementation type-erases the callback without requiring
        a dynamic allocation. For this reason, the callback object is
        passed by a non-constant reference.

        @par Example
        @code
        auto callback =
            [](std::uint64_t remain, string_view body, error_code& ec)
            {
                //...
            };
        parser.on_chunk_body(callback);
        @endcode

        @param cb The function to set, which must be invocable with
        this equivalent signature:
        @code
        std::size_t
        on_chunk_header(
            std::uint64_t remain,       // Octets remaining in this chunk, includes `body`
            string_view body,           // A buffer holding some or all of the remainder of the chunk body
            error_code& ec);            // May be set by the callback to indicate an error
        @endcode
        */
    template<class Callback>
    void
    on_chunk_body(Callback& cb)
    {
        // Callback may not be constant, caller is responsible for
        // managing the lifetime of the callback. Copies are not made.
        BOOST_STATIC_ASSERT(! std::is_const<Callback>::value);

        // Can't set the callback after receiving any chunk data!
        BOOST_ASSERT(! rd_inited_);

        cb_b_ = std::ref(cb);
    }

private:
    parser(std::true_type);
    parser(std::false_type);

    template<class OtherBody, class... Args,
        class = typename std::enable_if<
            ! std::is_same<Body, OtherBody>::value>::type>
    parser(
        std::true_type,
        parser<isRequest, OtherBody, Allocator>&& parser,
        Args&&... args);

    template<class OtherBody, class... Args,
        class = typename std::enable_if<
            ! std::is_same<Body, OtherBody>::value>::type>
    parser(
        std::false_type,
        parser<isRequest, OtherBody, Allocator>&& parser,
        Args&&... args);

    template<class Arg1, class... ArgN,
        class = typename std::enable_if<
            ! detail::is_parser<typename
                std::decay<Arg1>::type>::value>::type>
    explicit
    parser(Arg1&& arg1, std::true_type, ArgN&&... argn);

    template<class Arg1, class... ArgN,
        class = typename std::enable_if<
            ! detail::is_parser<typename
                std::decay<Arg1>::type>::value>::type>
    explicit
    parser(Arg1&& arg1, std::false_type, ArgN&&... argn);

    void
    on_request_impl(
        verb method,
        string_view method_str,
        string_view target,
        int version,
        error_code& ec,
        std::true_type)
    {
        // If this assert goes off, it means you tried to re-use a
        // parser after it was done reading a message. This is not
        // allowed, you need to create a new parser for each message.
        // The easiest way to do that is to store the parser in
        // an optional object.

        BOOST_ASSERT(! used_);
        if(used_)
        {
            ec = error::stale_parser;
            return;
        }
        used_ = true;

        m_.target(target);
        if(method != verb::unknown)
            m_.method(method);
        else
            m_.method_string(method_str);
        m_.version(version);
    }

    void
    on_request_impl(
        verb, string_view, string_view,
        int, error_code&, std::false_type)
    {
    }

    void
    on_request_impl(
        verb method,
        string_view method_str,
        string_view target,
        int version,
        error_code& ec) override
    {
        this->on_request_impl(
            method, method_str, target, version, ec,
            std::integral_constant<bool, isRequest>{});
    }

    void
    on_response_impl(
        int code,
        string_view reason,
        int version,
        error_code& ec,
        std::true_type)
    {
        // If this assert goes off, it means you tried to re-use a
        // parser after it was done reading a message. This is not
        // allowed, you need to create a new parser for each message.
        // The easiest way to do that is to store the parser in
        // an optional object.

        BOOST_ASSERT(! used_);
        if(used_)
        {
            ec = error::stale_parser;
            return;
        }
        used_ = true;

        m_.result(code);
        m_.version(version);
        m_.reason(reason);
    }

    void
    on_response_impl(
        int, string_view, int,
        error_code&, std::false_type)
    {
    }

    void
    on_response_impl(
        int code,
        string_view reason,
        int version,
        error_code& ec) override
    {
        this->on_response_impl(
            code, reason, version, ec,
            std::integral_constant<bool, ! isRequest>{});
    }

    void
    on_field_impl(
        field name,
        string_view name_string,
        string_view value,
        error_code&) override
    {
        m_.insert(name, name_string, value);
    }

    void
    on_header_impl(error_code& ec) override
    {
        ec = {};
    }

    void
    on_body_init_impl(
        boost::optional<std::uint64_t> const& content_length,
        error_code& ec) override
    {
        rd_.init(content_length, ec);
        rd_inited_ = true;
    }

    std::size_t
    on_body_impl(
        string_view body,
        error_code& ec) override
    {
        return rd_.put(net::buffer(
            body.data(), body.size()), ec);
    }

    void
    on_chunk_header_impl(
        std::uint64_t size,
        string_view extensions,
        error_code& ec) override
    {
        if(cb_h_)
            return cb_h_(size, extensions, ec);
    }

    std::size_t
    on_chunk_body_impl(
        std::uint64_t remain,
        string_view body,
        error_code& ec) override
    {
        if(cb_b_)
            return cb_b_(remain, body, ec);
        return rd_.put(net::buffer(
            body.data(), body.size()), ec);
    }

    void
    on_finish_impl(
        error_code& ec) override
    {
        rd_.finish(ec);
    }
};

/// An HTTP/1 parser for producing a request message.
template<class Body, class Allocator = std::allocator<char>>
using request_parser = parser<true, Body, Allocator>;

/// An HTTP/1 parser for producing a response message.
template<class Body, class Allocator = std::allocator<char>>
using response_parser = parser<false, Body, Allocator>;

} // http
} // beast
} // boost

#include <boost/beast/http/impl/parser.hpp>

#endif

/* parser.hpp
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
*/