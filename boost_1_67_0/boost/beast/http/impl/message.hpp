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