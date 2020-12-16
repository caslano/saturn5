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
PE/fKe3QbkPml8Ar5P6kILvE3oYY33P5E/I+9RQcB5+R/oln4anwb/BMuFH6J16AF8IXYSXcDB+GL8FH4Vb4ItwGX4KvwNfga3AXfAt+DN+DP8J34c/iTrLuG0yH/5T3sk9gf7hb3s8+h7PhXlgEv5T3rasNmUMh80XUfGhkqaT3LvR6wLstu/AeOATeK++Rq+AIeJ/ch/thPnxQ0rsGXgIfglfCP8Gr4Vr4AFwHN8D1Ep9SQ+YEwC8lPs2RPInP+dG++78AHg/L4HS4EFo6i2ERXAJvgZfAangR/Ie4t8NyuANWyHv8WnssXcbqc+TbyHvlut/w+9kR7oPd4bewD/weHg/3w5HwBzgW/gjHw1jsz4A/yfvKv+B58Ge4GBr4XwEi4FUwEl4Lo+B1En4lbArvt9Thw3L+a1htyLgt7CjltTWywu5nRq8XbAkzYCt4IoyHI2ACnAxPhxVwhsTjTLgMniXxmAlvh9nwZXiu9AvlwQ/gXPgJLIB7YSG0nnOKnX5EGTuF3YK8R5pNaA9gBLTOx8F42BQmw2YwRc53hS1gBgG20XGyB4lpHmN0Q7KQmcgSZAWyFtmC7Eai6FxJRYYhM5BypApZg2xCPkKswdAOyBBkOlKKVCKrkY1ILXIASaaDZiAyFSlFqpC1yBZkN+K/p+N4brC9r2M58tTIKLW/405k9YPRQfd53HVGdMBej5vQde/3GDOoSdA9H2eScXWED7b3Y/lMzr8fpd0DMqpVTEj7QO4mLnmZXA/ZRHpy/kTc3ojy7A+Z3CrmsPaITKRDMWdA/XtFToLu/SKTKZz+e0amc678rGi1d2Qv4jIeKUCuRtYgW5A9SFx8jJGOTEKKkEpkLbINqUPi6YDLQKYj5cgKZD2yHdmHJCZQHpAZyBLkZmQDsgs5gHQ4hnKHzESWIrcjTyG1iJFIuUSykJnIUqQaqUFqEaMN/kgWkoNUILcjTyG1yAGkQxL2kRnIEuRmZAOyE9mPJLYlfm3D+2aGj/ARPsJH+Agf4eO/sv9fXuHc/LJyawPAI9z/z9rLa3MqfZL2Hi2yCf+Lshb8o8j7CfQZvdzckHXmx6hry3znpmoOLd/+5DrzO9H1ruuer9zVMp/dmRMqc3RF37Wu+7nKvco1v744z/19Q7bYk/mjEr6z0l+o9MsKL8w/NMe2TPnfJPOubf0BSn9XgjMf3FoBofUppuoTEx3T833ze0q3sLi06JBuhp9ugejedIzBIXOXZT73xUpvqf+3684351XKP99IstZssfIign4lciWy4oamEXFtYuy53CPaqXVX1LosCaJbgUdndOPiitV528Zqzida55t3j2vekndAbKh+ATs8bivLd7Sl/xW94uTQ5xg3VXOHVd47c4y7IjI3V+YY2/N1VR46c4wXqnMqn5xvBMgL9xxzdS/fU+fUPVffCDym7hHxPca7P0J1lKGO/tLn0BP5c2fyZptfuR1bOD+3yMkj//nlop/kfGtxunK3D1IWpeyKf7CyN9XlHyzPE2HONu83wdx/8je0PMiApMH73UyQ+53ld7+dfSuUrvRZyrcVlXLfKoLet+x8rhN476R836vCFMu9tG1009078U9z6uldyp0ReC8lL1Yq/0vk3trhOwW9t23hK8p/nGGX8VHxvnIenfDL3l+rnG5R12bsto/P/YW4u/bxlttE2bNukKvcdkdn6it+9/9XfBlhaMut6Ldz7lWhcif7t3FOXs1R/klOXkwVt6uNoT04svvk1Ge/Mpcje68xxqHK3HQ4w1qfJFiaVZELSLezXthGFeb4iBJ6OLcil5jNjc1I54jmcm9su92C3ouJjn97Z92LJ5X7HfN8UnIPoxwpst5C+qs=
*/