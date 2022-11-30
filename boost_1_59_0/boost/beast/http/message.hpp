//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_MESSAGE_HPP
#define BOOST_BEAST_HTTP_MESSAGE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/http/fields.hpp>
#include <boost/beast/http/verb.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/mp11/integer_sequence.hpp>
#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** A container for an HTTP request or response header.

    This container is derived from the `Fields` template type.
    To understand all of the members of this class it is necessary
    to view the declaration for the `Fields` type. When using
    the default fields container, those declarations are in
    @ref fields.

    Newly constructed header objects have version set to
    HTTP/1.1. Newly constructed response objects also have
    result code set to @ref status::ok.

    A `header` includes the start-line and header-fields.
*/
#if BOOST_BEAST_DOXYGEN
template<bool isRequest, class Fields = fields>
class header : public Fields

#else
template<bool isRequest, class Fields = fields>
class header;

template<class Fields>
class header<true, Fields> : public Fields
#endif
{
public:
    static_assert(is_fields<Fields>::value,
        "Fields type requirements not met");

    /// Indicates if the header is a request or response.
#if BOOST_BEAST_DOXYGEN
    using is_request = std::integral_constant<bool, isRequest>;
#else
    using is_request = std::true_type;
#endif

    /// The type representing the fields.
    using fields_type = Fields;

    /// Constructor
    header() = default;

    /// Constructor
    header(header&&) = default;

    /// Constructor
    header(header const&) = default;

    /// Assignment
    header& operator=(header&&) = default;

    /// Assignment
    header& operator=(header const&) = default;

    /** Return the HTTP-version.

        This holds both the major and minor version numbers,
        using these formulas:
        @code
            unsigned major = version / 10;
            unsigned minor = version % 10;
        @endcode

        Newly constructed headers will use HTTP/1.1 by default.
    */
    unsigned version() const noexcept
    {
        return version_;
    }

    /** Set the HTTP-version.

        This holds both the major and minor version numbers,
        using these formulas:
        @code
            unsigned major = version / 10;
            unsigned minor = version % 10;
        @endcode

        Newly constructed headers will use HTTP/1.1 by default.

        @param value The version number to use
    */
    void version(unsigned value) noexcept
    {
        BOOST_ASSERT(value > 0 && value < 100);
        version_ = value;
    }

    /** Return the request-method verb.

        If the request-method is not one of the recognized verbs,
        @ref verb::unknown is returned. Callers may use @ref method_string
        to retrieve the exact text.

        @note This function is only available when `isRequest == true`.

        @see method_string
    */
    verb
    method() const;

    /** Set the request-method.

        This function will set the method for requests to a known verb.

        @param v The request method verb to set.
        This may not be @ref verb::unknown.

        @throws std::invalid_argument when `v == verb::unknown`.

        @note This function is only available when `isRequest == true`.
    */
    void
    method(verb v);

    /** Return the request-method as a string.

        @note This function is only available when `isRequest == true`.

        @see method
    */
    string_view
    method_string() const;

    /** Set the request-method.

        This function will set the request-method a known verb
        if the string matches, otherwise it will store a copy of
        the passed string.

        @param s A string representing the request-method.

        @note This function is only available when `isRequest == true`.
    */
    void
    method_string(string_view s);

    /** Returns the request-target string.

        The request target string returned is the same string which
        was received from the network or stored. In particular, it will
        contain url-encoded characters and should follow the syntax
        rules for URIs used with HTTP.

        @note This function is only available when `isRequest == true`.
    */
    string_view
    target() const;

    /** Set the request-target string.

        It is the caller's responsibility to ensure that the request
        target string follows the syntax rules for URIs used with
        HTTP. In particular, reserved or special characters must be
        url-encoded. The implementation does not perform syntax checking
        on the passed string.

        @param s A string representing the request-target.

        @note This function is only available when `isRequest == true`.
    */
    void
    target(string_view s);

    // VFALCO Don't rearrange these declarations or
    //        ifdefs, or else the documentation will break.

    /** Constructor

        @param args Arguments forwarded to the `Fields`
        base class constructor.

        @note This constructor participates in overload
        resolution if and only if the first parameter is
        not convertible to @ref header, @ref verb, or
        @ref status.
    */
#if BOOST_BEAST_DOXYGEN
    template<class... Args>
    explicit
    header(Args&&... args);

#else
    template<class Arg1, class... ArgN,
        class = typename std::enable_if<
            ! std::is_convertible<typename
                std::decay<Arg1>::type, header>::value &&
            ! std::is_convertible<typename
                std::decay<Arg1>::type, verb>::value &&
            ! std::is_convertible<typename
                std::decay<Arg1>::type, status>::value
        >::type>
    explicit
    header(Arg1&& arg1, ArgN&&... argn);

private:
    template<bool, class, class>
    friend class message;

    template<class T>
    friend
    void
    swap(header<true, T>& m1, header<true, T>& m2);

    template<class... FieldsArgs>
    header(
        verb method,
        string_view target_,
        unsigned version_value,
        FieldsArgs&&... fields_args)
        : Fields(std::forward<FieldsArgs>(fields_args)...)
        , method_(method)
    {
        version(version_value);
        target(target_);
    }

    unsigned version_ = 11;
    verb method_ = verb::unknown;
};

/** A container for an HTTP request or response header.

    A `header` includes the start-line and header-fields.
*/
template<class Fields>
class header<false, Fields> : public Fields
{
public:
    static_assert(is_fields<Fields>::value,
        "Fields type requirements not met");

    /// Indicates if the header is a request or response.
    using is_request = std::false_type;

    /// The type representing the fields.
    using fields_type = Fields;

    /// Constructor.
    header() = default;

    /// Constructor
    header(header&&) = default;

    /// Constructor
    header(header const&) = default;

    /// Assignment
    header& operator=(header&&) = default;

    /// Assignment
    header& operator=(header const&) = default;

    /** Constructor

        @param args Arguments forwarded to the `Fields`
        base class constructor.

        @note This constructor participates in overload
        resolution if and only if the first parameter is
        not convertible to @ref header, @ref verb, or
        @ref status.
    */
    template<class Arg1, class... ArgN,
        class = typename std::enable_if<
            ! std::is_convertible<typename
                std::decay<Arg1>::type, header>::value &&
            ! std::is_convertible<typename
                std::decay<Arg1>::type, verb>::value &&
            ! std::is_convertible<typename
                std::decay<Arg1>::type, status>::value
        >::type>
    explicit
    header(Arg1&& arg1, ArgN&&... argn);

    /** Return the HTTP-version.

        This holds both the major and minor version numbers,
        using these formulas:
        @code
            unsigned major = version / 10;
            unsigned minor = version % 10;
        @endcode

        Newly constructed headers will use HTTP/1.1 by default.
    */
    unsigned version() const noexcept
    {
        return version_;
    }

    /** Set the HTTP-version.

        This holds both the major and minor version numbers,
        using these formulas:
        @code
            unsigned major = version / 10;
            unsigned minor = version % 10;
        @endcode

        Newly constructed headers will use HTTP/1.1 by default.

        @param value The version number to use
    */
    void version(unsigned value) noexcept
    {
        BOOST_ASSERT(value > 0 && value < 100);
        version_ = value;
    }
#endif

    /** The response status-code result.

        If the actual status code is not a known code, this
        function returns @ref status::unknown. Use @ref result_int
        to return the raw status code as a number.

        @note This member is only available when `isRequest == false`.
    */
    status
    result() const;

    /** Set the response status-code.

        @param v The code to set.

        @note This member is only available when `isRequest == false`.
    */
    void
    result(status v);

    /** Set the response status-code as an integer.

        This sets the status code to the exact number passed in.
        If the number does not correspond to one of the known
        status codes, the function @ref result will return
        @ref status::unknown. Use @ref result_int to obtain the
        original raw status-code.

        @param v The status-code integer to set.

        @throws std::invalid_argument if `v > 999`.
    */
    void
    result(unsigned v);

    /** The response status-code expressed as an integer.

        This returns the raw status code as an integer, even
        when that code is not in the list of known status codes.

        @note This member is only available when `isRequest == false`.
    */
    unsigned
    result_int() const;

    /** Return the response reason-phrase.

        The reason-phrase is obsolete as of rfc7230.

        @note This function is only available when `isRequest == false`.
    */
    string_view
    reason() const;

    /** Set the response reason-phrase (deprecated)

        This function sets a custom reason-phrase to a copy of
        the string passed in. Normally it is not necessary to set
        the reason phrase on an outgoing response object; the
        implementation will automatically use the standard reason
        text for the corresponding status code.

        To clear a previously set custom phrase, pass an empty
        string. This will restore the default standard reason text
        based on the status code used when serializing.

        The reason-phrase is obsolete as of rfc7230.

        @param s The string to use for the reason-phrase.

        @note This function is only available when `isRequest == false`.
    */
    void
    reason(string_view s);

private:
#if ! BOOST_BEAST_DOXYGEN
    template<bool, class, class>
    friend class message;

    template<class T>
    friend
    void
    swap(header<false, T>& m1, header<false, T>& m2);

    template<class... FieldsArgs>
    header(
        status result,
        unsigned version_value,
        FieldsArgs&&... fields_args)
        : Fields(std::forward<FieldsArgs>(fields_args)...)
        , result_(result)
    {
        version(version_value);
    }

    unsigned version_ = 11;
    status result_ = status::ok;
#endif
};

/// A typical HTTP request header
template<class Fields = fields>
using request_header = header<true, Fields>;

/// A typical HTTP response header
template<class Fields = fields>
using response_header = header<false, Fields>;

#if defined(BOOST_MSVC)
// Workaround for MSVC bug with private base classes
namespace detail {
template<class T>
using value_type_t = typename T::value_type;
} // detail
#endif

/** A container for a complete HTTP message.

    This container is derived from the `Fields` template type.
    To understand all of the members of this class it is necessary
    to view the declaration for the `Fields` type. When using
    the default fields container, those declarations are in
    @ref fields.

    A message can be a request or response, depending on the
    `isRequest` template argument value. Requests and responses
    have different types; functions may be overloaded based on
    the type if desired.

    The `Body` template argument type determines the model used
    to read or write the content body of the message.

    Newly constructed messages objects have version set to
    HTTP/1.1. Newly constructed response objects also have
    result code set to @ref status::ok.

    @tparam isRequest `true` if this represents a request,
    or `false` if this represents a response. Some class data
    members are conditionally present depending on this value.

    @tparam Body A type meeting the requirements of Body.

    @tparam Fields The type of container used to hold the
    field value pairs.
*/
template<bool isRequest, class Body, class Fields = fields>
class message
    : public header<isRequest, Fields>
#if ! BOOST_BEAST_DOXYGEN
    , boost::empty_value<
        typename Body::value_type>
#endif
{
public:
    /// The base class used to hold the header portion of the message.
    using header_type = header<isRequest, Fields>;

    /** The type providing the body traits.

        The @ref message::body member will be of type `body_type::value_type`.
    */
    using body_type = Body;

    /// Constructor
    message() = default;

    /// Constructor
    message(message&&) = default;

    /// Constructor
    message(message const&) = default;

    /// Assignment
    message& operator=(message&&) = default;

    /// Assignment
    message& operator=(message const&) = default;

    /** Constructor

        @param h The header to move construct from.

        @param body_args Optional arguments forwarded
        to the `body` constructor.
    */
    template<class... BodyArgs>
    explicit
    message(header_type&& h, BodyArgs&&... body_args);

    /** Constructor.

        @param h The header to copy construct from.

        @param body_args Optional arguments forwarded
        to the `body` constructor.
    */
    template<class... BodyArgs>
    explicit
    message(header_type const& h, BodyArgs&&... body_args);

    /** Constructor

        @param method The request-method to use.

        @param target The request-target.

        @param version The HTTP-version.

        @note This function is only available when `isRequest == true`.
    */
#if BOOST_BEAST_DOXYGEN
    message(verb method, string_view target, unsigned version);
#else
    template<class Version,
        class = typename std::enable_if<isRequest &&
            std::is_convertible<Version, unsigned>::value>::type>
    message(verb method, string_view target, Version version);
#endif

    /** Constructor

        @param method The request-method to use.

        @param target The request-target.

        @param version The HTTP-version.

        @param body_arg An argument forwarded to the `body` constructor.

        @note This function is only available when `isRequest == true`.
    */
#if BOOST_BEAST_DOXYGEN
    template<class BodyArg>
    message(verb method, string_view target,
        unsigned version, BodyArg&& body_arg);
#else
    template<class Version, class BodyArg,
        class = typename std::enable_if<isRequest &&
            std::is_convertible<Version, unsigned>::value>::type>
    message(verb method, string_view target,
        Version version, BodyArg&& body_arg);
#endif

    /** Constructor

        @param method The request-method to use.

        @param target The request-target.

        @param version The HTTP-version.

        @param body_arg An argument forwarded to the `body` constructor.

        @param fields_arg An argument forwarded to the `Fields` constructor.

        @note This function is only available when `isRequest == true`.
    */
#if BOOST_BEAST_DOXYGEN
    template<class BodyArg, class FieldsArg>
    message(verb method, string_view target, unsigned version,
        BodyArg&& body_arg, FieldsArg&& fields_arg);
#else
    template<class Version, class BodyArg, class FieldsArg,
        class = typename std::enable_if<isRequest &&
            std::is_convertible<Version, unsigned>::value>::type>
    message(verb method, string_view target, Version version,
        BodyArg&& body_arg, FieldsArg&& fields_arg);
#endif

    /** Constructor

        @param result The status-code for the response.

        @param version The HTTP-version.

        @note This member is only available when `isRequest == false`.
    */
#if BOOST_BEAST_DOXYGEN
    message(status result, unsigned version);
#else
    template<class Version,
        class = typename std::enable_if<! isRequest &&
           std::is_convertible<Version, unsigned>::value>::type>
    message(status result, Version version);
#endif

    /** Constructor

        @param result The status-code for the response.

        @param version The HTTP-version.

        @param body_arg An argument forwarded to the `body` constructor.

        @note This member is only available when `isRequest == false`.
    */
#if BOOST_BEAST_DOXYGEN
    template<class BodyArg>
    message(status result, unsigned version, BodyArg&& body_arg);
#else
    template<class Version, class BodyArg,
        class = typename std::enable_if<! isRequest &&
           std::is_convertible<Version, unsigned>::value>::type>
    message(status result, Version version, BodyArg&& body_arg);
#endif

    /** Constructor

        @param result The status-code for the response.

        @param version The HTTP-version.

        @param body_arg An argument forwarded to the `body` constructor.

        @param fields_arg An argument forwarded to the `Fields` base class constructor.

        @note This member is only available when `isRequest == false`.
    */
#if BOOST_BEAST_DOXYGEN
    template<class BodyArg, class FieldsArg>
    message(status result, unsigned version,
        BodyArg&& body_arg, FieldsArg&& fields_arg);
#else
    template<class Version, class BodyArg, class FieldsArg,
        class = typename std::enable_if<! isRequest &&
           std::is_convertible<Version, unsigned>::value>::type>
    message(status result, Version version,
        BodyArg&& body_arg, FieldsArg&& fields_arg);
#endif

    /** Constructor

        The header and body are default-constructed.
    */
    explicit
    message(std::piecewise_construct_t);

    /** Construct a message.

        @param body_args A tuple forwarded as a parameter
        pack to the body constructor.
    */
    template<class... BodyArgs>
    message(std::piecewise_construct_t,
        std::tuple<BodyArgs...> body_args);

    /** Construct a message.

        @param body_args A tuple forwarded as a parameter
        pack to the body constructor.

        @param fields_args A tuple forwarded as a parameter
        pack to the `Fields` constructor.
    */
    template<class... BodyArgs, class... FieldsArgs>
    message(std::piecewise_construct_t,
        std::tuple<BodyArgs...> body_args,
        std::tuple<FieldsArgs...> fields_args);

    /// Returns the header portion of the message
    header_type const&
    base() const
    {
        return *this;
    }

    /// Returns the header portion of the message
    header_type&
    base()
    {
        return *this;
    }

    /// Returns `true` if the chunked Transfer-Encoding is specified
    bool
    chunked() const
    {
        return this->get_chunked_impl();
    }

    /** Set or clear the chunked Transfer-Encoding

        This function will set or remove the "chunked" transfer
        encoding as the last item in the list of encodings in the
        field.

        If the result of removing the chunked token results in an
        empty string, the field is erased.

        The Content-Length field is erased unconditionally.
    */
    void
    chunked(bool value);

    /** Returns `true` if the Content-Length field is present.

        This function inspects the fields and returns `true` if
        the Content-Length field is present. The properties of the
        body are not checked, this only looks for the field.
    */
    bool
    has_content_length() const
    {
        return this->has_content_length_impl();
    }

    /** Set or clear the Content-Length field

        This function adjusts the Content-Length field as follows:

        @li If `value` specifies a value, the Content-Length field
          is set to the value. Otherwise

        @li The Content-Length field is erased.

        If "chunked" token appears as the last item in the
        Transfer-Encoding field it is unconditionally removed.

        @param value The value to set for Content-Length.
    */
    void
    content_length(boost::optional<std::uint64_t> const& value);

    /** Returns `true` if the message semantics indicate keep-alive

        The value depends on the version in the message, which must
        be set to the final value before this function is called or
        else the return value is unreliable.
    */
    bool
    keep_alive() const
    {
        return this->get_keep_alive_impl(this->version());
    }

    /** Set the keep-alive message semantic option

        This function adjusts the Connection field to indicate
        whether or not the connection should be kept open after
        the corresponding response. The result depends on the
        version set on the message, which must be set to the
        final value before making this call.

        @param value `true` if the connection should persist.
    */
    void
    keep_alive(bool value)
    {
        this->set_keep_alive_impl(this->version(), value);
    }

    /** Returns `true` if the message semantics require an end of file.

        For HTTP requests, this function returns the logical
        NOT of a call to @ref keep_alive.

        For HTTP responses, this function returns the logical NOT
        of a call to @ref keep_alive if any of the following are true:

        @li @ref has_content_length would return `true`

        @li @ref chunked would return `true`

        @li @ref result returns @ref status::no_content

        @li @ref result returns @ref status::not_modified

        @li @ref result returns any informational status class (100 to 199)

        Otherwise, the function returns `true`.

        @see https://tools.ietf.org/html/rfc7230#section-3.3
    */
    bool
    need_eof() const
    {
        return need_eof(typename header_type::is_request{});
    }

    /** Returns the payload size of the body in octets if possible.

        This function invokes the <em>Body</em> algorithm to measure
        the number of octets in the serialized body container. If
        there is no body, this will return zero. Otherwise, if the
        body exists but is not known ahead of time, `boost::none`
        is returned (usually indicating that a chunked Transfer-Encoding
        will be used).

        @note The value of the Content-Length field in the message
        is not inspected.
    */
    boost::optional<std::uint64_t>
    payload_size() const;

    /** Prepare the message payload fields for the body.

        This function will adjust the Content-Length and
        Transfer-Encoding field values based on the properties
        of the body.

        @par Example
        @code
        request<string_body> req{verb::post, "/"};
        req.set(field::user_agent, "Beast");
        req.body() = "Hello, world!";
        req.prepare_payload();
        @endcode
    */
    void
    prepare_payload()
    {
        prepare_payload(typename header_type::is_request{});
    }

    /// Returns the body
#if BOOST_BEAST_DOXYGEN || ! defined(BOOST_MSVC)
    typename body_type::value_type&
#else
    detail::value_type_t<Body>&
#endif
    body()& noexcept
    {
        return this->boost::empty_value<
            typename Body::value_type>::get();
    }

    /// Returns the body
#if BOOST_BEAST_DOXYGEN || ! defined(BOOST_MSVC)
    typename body_type::value_type&&
#else
    detail::value_type_t<Body>&&
#endif
    body()&& noexcept
    {
        return std::move(
            this->boost::empty_value<
                typename Body::value_type>::get());
    }

    /// Returns the body
#if BOOST_BEAST_DOXYGEN || ! defined(BOOST_MSVC)
    typename body_type::value_type const&
#else
    detail::value_type_t<Body> const&
#endif
    body() const& noexcept
    {
        return this->boost::empty_value<
            typename Body::value_type>::get();
    }

private:
    static_assert(is_body<Body>::value,
        "Body type requirements not met");

    template<
        class... BodyArgs,
        std::size_t... IBodyArgs>
    message(
        std::piecewise_construct_t,
        std::tuple<BodyArgs...>& body_args,
        mp11::index_sequence<IBodyArgs...>)
        : boost::empty_value<
            typename Body::value_type>(boost::empty_init_t(),
                std::forward<BodyArgs>(
                std::get<IBodyArgs>(body_args))...)
    {
        boost::ignore_unused(body_args);
    }

    template<
        class... BodyArgs,
        class... FieldsArgs,
        std::size_t... IBodyArgs,
        std::size_t... IFieldsArgs>
    message(
        std::piecewise_construct_t,
        std::tuple<BodyArgs...>& body_args,
        std::tuple<FieldsArgs...>& fields_args,
        mp11::index_sequence<IBodyArgs...>,
        mp11::index_sequence<IFieldsArgs...>)
        : header_type(std::forward<FieldsArgs>(
            std::get<IFieldsArgs>(fields_args))...)
        , boost::empty_value<
            typename Body::value_type>(boost::empty_init_t(),
                std::forward<BodyArgs>(
                std::get<IBodyArgs>(body_args))...)
    {
        boost::ignore_unused(body_args);
        boost::ignore_unused(fields_args);
    }

    bool
    need_eof(std::true_type) const
    {
        return ! keep_alive();
    }

    bool
    need_eof(std::false_type) const;

    boost::optional<std::uint64_t>
    payload_size(std::true_type) const
    {
        return Body::size(this->body());
    }

    boost::optional<std::uint64_t>
    payload_size(std::false_type) const
    {
        return boost::none;
    }

    void
    prepare_payload(std::true_type);

    void
    prepare_payload(std::false_type);
};

/// A typical HTTP request
template<class Body, class Fields = fields>
using request = message<true, Body, Fields>;

/// A typical HTTP response
template<class Body, class Fields = fields>
using response = message<false, Body, Fields>;

//------------------------------------------------------------------------------

#if BOOST_BEAST_DOXYGEN
/** Swap two header objects.

    @par Requirements
    `Fields` is @b Swappable.
*/
template<bool isRequest, class Fields>
void
swap(
    header<isRequest, Fields>& m1,
    header<isRequest, Fields>& m2);
#endif

/** Swap two message objects.

    @par Requirements:
    `Body::value_type` and `Fields` are @b Swappable.
*/
template<bool isRequest, class Body, class Fields>
void
swap(
    message<isRequest, Body, Fields>& m1,
    message<isRequest, Body, Fields>& m2);

} // http
} // beast
} // boost

#include <boost/beast/http/impl/message.hpp>

#endif

/* message.hpp
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
*/