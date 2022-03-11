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