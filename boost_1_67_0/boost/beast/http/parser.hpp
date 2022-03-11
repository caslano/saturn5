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