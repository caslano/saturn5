//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_MESSAGE_HPP
#define BOOST_BEAST_HTTP_IMPL_MESSAGE_HPP

#include <boost/beast/core/error.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace boost {
namespace beast {
namespace http {

template<class Fields>
template<class Arg1, class... ArgN, class>
header<true, Fields>::
header(Arg1&& arg1, ArgN&&... argn)
    : Fields(std::forward<Arg1>(arg1),
        std::forward<ArgN>(argn)...)
{
}

template<class Fields>
verb
header<true, Fields>::
method() const
{
    return method_;
}

template<class Fields>
void
header<true, Fields>::
method(verb v)
{
    if(v == verb::unknown)
        BOOST_THROW_EXCEPTION(
            std::invalid_argument{"unknown method"});
    method_ = v;
    this->set_method_impl({});
}

template<class Fields>
string_view
header<true, Fields>::
method_string() const
{
    if(method_ != verb::unknown)
        return to_string(method_);
    return this->get_method_impl();
}

template<class Fields>
void
header<true, Fields>::
method_string(string_view s)
{
    method_ = string_to_verb(s);
    if(method_ != verb::unknown)
        this->set_method_impl({});
    else
        this->set_method_impl(s);
}

template<class Fields>
string_view
header<true, Fields>::
target() const
{
    return this->get_target_impl();
}

template<class Fields>
void
header<true, Fields>::
target(string_view s)
{
    this->set_target_impl(s);
}

template<class Fields>
void
swap(
    header<true, Fields>& h1,
    header<true, Fields>& h2)
{
    using std::swap;
    swap(
        static_cast<Fields&>(h1),
        static_cast<Fields&>(h2));
    swap(h1.version_, h2.version_);
    swap(h1.method_, h2.method_);
}

//------------------------------------------------------------------------------

template<class Fields>
template<class Arg1, class... ArgN, class>
header<false, Fields>::
header(Arg1&& arg1, ArgN&&... argn)
    : Fields(std::forward<Arg1>(arg1),
        std::forward<ArgN>(argn)...)
{
}

template<class Fields>
status
header<false, Fields>::
result() const
{
    return int_to_status(
        static_cast<int>(result_));
}

template<class Fields>
void
header<false, Fields>::
result(status v)
{
    result_ = v;
}

template<class Fields>
void
header<false, Fields>::
result(unsigned v)
{
    if(v > 999)
        BOOST_THROW_EXCEPTION(
            std::invalid_argument{
                "invalid status-code"});
    result_ = static_cast<status>(v);
}

template<class Fields>
unsigned
header<false, Fields>::
result_int() const
{
    return static_cast<unsigned>(result_);
}

template<class Fields>
string_view
header<false, Fields>::
reason() const
{
    auto const s = this->get_reason_impl();
    if(! s.empty())
        return s;
    return obsolete_reason(result_);
}

template<class Fields>
void
header<false, Fields>::
reason(string_view s)
{
    this->set_reason_impl(s);
}

template<class Fields>
void
swap(
    header<false, Fields>& h1,
    header<false, Fields>& h2)
{
    using std::swap;
    swap(
        static_cast<Fields&>(h1),
        static_cast<Fields&>(h2));
    swap(h1.version_, h2.version_);
    swap(h1.result_, h2.result_);
}

//------------------------------------------------------------------------------

template<bool isRequest, class Body, class Fields>
template<class... BodyArgs>
message<isRequest, Body, Fields>::
message(header_type&& h, BodyArgs&&... body_args)
    : header_type(std::move(h))
    , boost::empty_value<
        typename Body::value_type>(boost::empty_init_t(),
            std::forward<BodyArgs>(body_args)...)
{
}

template<bool isRequest, class Body, class Fields>
template<class... BodyArgs>
message<isRequest, Body, Fields>::
message(header_type const& h, BodyArgs&&... body_args)
    : header_type(h)
    , boost::empty_value<
        typename Body::value_type>(boost::empty_init_t(),
            std::forward<BodyArgs>(body_args)...)
{
}

template<bool isRequest, class Body, class Fields>
template<class Version, class>
message<isRequest, Body, Fields>::
message(verb method, string_view target, Version version)
    : header_type(method, target, version)
{
}

template<bool isRequest, class Body, class Fields>
template<class Version, class BodyArg, class>
message<isRequest, Body, Fields>::
message(verb method, string_view target,
        Version version, BodyArg&& body_arg)
    : header_type(method, target, version)
    , boost::empty_value<
        typename Body::value_type>(boost::empty_init_t(),
            std::forward<BodyArg>(body_arg))
{
}

template<bool isRequest, class Body, class Fields>
template<class Version, class BodyArg, class FieldsArg, class>
message<isRequest, Body, Fields>::
message(
    verb method, string_view target, Version version,
    BodyArg&& body_arg,
    FieldsArg&& fields_arg)
    : header_type(method, target, version,
        std::forward<FieldsArg>(fields_arg))
    , boost::empty_value<
        typename Body::value_type>(boost::empty_init_t(),
            std::forward<BodyArg>(body_arg))
{
}

template<bool isRequest, class Body, class Fields>
template<class Version, class>
message<isRequest, Body, Fields>::
message(status result, Version version)
    : header_type(result, version)
{
}

template<bool isRequest, class Body, class Fields>
template<class Version, class BodyArg, class>
message<isRequest, Body, Fields>::
message(status result, Version version,
    BodyArg&& body_arg)
    : header_type(result, version)
    , boost::empty_value<
        typename Body::value_type>(boost::empty_init_t(),
            std::forward<BodyArg>(body_arg))
{
}

template<bool isRequest, class Body, class Fields>
template<class Version, class BodyArg, class FieldsArg, class>
message<isRequest, Body, Fields>::
message(status result, Version version,
    BodyArg&& body_arg, FieldsArg&& fields_arg)
    : header_type(result, version,
        std::forward<FieldsArg>(fields_arg))
    , boost::empty_value<
        typename Body::value_type>(boost::empty_init_t(),
            std::forward<BodyArg>(body_arg))
{
}

template<bool isRequest, class Body, class Fields>
message<isRequest, Body, Fields>::
message(std::piecewise_construct_t)
{
}

template<bool isRequest, class Body, class Fields>
template<class... BodyArgs>
message<isRequest, Body, Fields>::
message(std::piecewise_construct_t,
        std::tuple<BodyArgs...> body_args)
    : message(std::piecewise_construct,
        body_args,
        mp11::make_index_sequence<
            sizeof...(BodyArgs)>{})
{
}

template<bool isRequest, class Body, class Fields>
template<class... BodyArgs, class... FieldsArgs>
message<isRequest, Body, Fields>::
message(std::piecewise_construct_t,
    std::tuple<BodyArgs...> body_args,
    std::tuple<FieldsArgs...> fields_args)
    : message(std::piecewise_construct,
        body_args,
        fields_args,
        mp11::make_index_sequence<
            sizeof...(BodyArgs)>{},
        mp11::make_index_sequence<
            sizeof...(FieldsArgs)>{})
{
}

template<bool isRequest, class Body, class Fields>
void
message<isRequest, Body, Fields>::
chunked(bool value)
{
    this->set_chunked_impl(value);
    this->set_content_length_impl(boost::none);
}

template<bool isRequest, class Body, class Fields>
void
message<isRequest, Body, Fields>::
content_length(
    boost::optional<std::uint64_t> const& value)
{
    this->set_content_length_impl(value);
    this->set_chunked_impl(false);
}

template<bool isRequest, class Body, class Fields>
boost::optional<std::uint64_t>
message<isRequest, Body, Fields>::
payload_size() const
{
    return payload_size(detail::is_body_sized<Body>{});
}

template<bool isRequest, class Body, class Fields>
bool
message<isRequest, Body, Fields>::
need_eof(std::false_type) const
{
    // VFALCO Do we need a way to let the caller say "the body is intentionally skipped"?
    if( this->result() == status::no_content ||
        this->result() == status::not_modified ||
        to_status_class(this->result()) ==
            status_class::informational ||
        has_content_length() ||
        chunked())
        return ! keep_alive();
    return true;
}

template<bool isRequest, class Body, class Fields>
void
message<isRequest, Body, Fields>::
prepare_payload(std::true_type)
{
    auto const n = payload_size();
    if(this->method() == verb::trace && (! n || *n > 0))
        BOOST_THROW_EXCEPTION(std::invalid_argument{
            "invalid request body"});
    if(n)
    {
        if(*n > 0 ||
            this->method() == verb::options ||
            this->method() == verb::put ||
            this->method() == verb::post)
        {
            this->content_length(n);
        }
        else
        {
            this->chunked(false);
        }
    }
    else if(this->version() == 11)
    {
        this->chunked(true);
    }
    else
    {
        this->chunked(false);
    }
}

template<bool isRequest, class Body, class Fields>
void
message<isRequest, Body, Fields>::
prepare_payload(std::false_type)
{
    auto const n = payload_size();
    if( (! n || *n > 0) && (
        (status_class(this->result()) == status_class::informational ||
        this->result() == status::no_content ||
        this->result() == status::not_modified)))
    {
        // The response body MUST be empty for this case
        BOOST_THROW_EXCEPTION(std::invalid_argument{
            "invalid response body"});
    }
    if(n)
        this->content_length(n);
    else if(this->version() == 11)
        this->chunked(true);
    else
        this->chunked(false);
}

//------------------------------------------------------------------------------

template<bool isRequest, class Body, class Fields>
void
swap(
    message<isRequest, Body, Fields>& m1,
    message<isRequest, Body, Fields>& m2)
{
    using std::swap;
    swap(
        static_cast<header<isRequest, Fields>&>(m1),
        static_cast<header<isRequest, Fields>&>(m2));
    swap(m1.body(), m2.body());
}

} // http
} // beast
} // boost

#endif

/* message.hpp
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
*/