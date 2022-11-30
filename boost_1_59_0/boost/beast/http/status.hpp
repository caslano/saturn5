//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_STATUS_HPP
#define BOOST_BEAST_HTTP_STATUS_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string.hpp>
#include <iosfwd>

namespace boost {
namespace beast {
namespace http {

enum class status : unsigned
{
    /** An unknown status-code.

        This value indicates that the value for the status code
        is not in the list of commonly recognized status codes.
        Callers interested in the exactly value should use the
        interface which provides the raw integer.
    */
    unknown = 0,

    continue_                           = 100,

    /** Switching Protocols

        This status indicates that a request to switch to a new
        protocol was accepted and applied by the server. A successful
        response to a WebSocket Upgrade HTTP request will have this
        code.
    */
    switching_protocols                 = 101,

    processing                          = 102,

    ok                                  = 200,
    created                             = 201,
    accepted                            = 202,
    non_authoritative_information       = 203,
    no_content                          = 204,
    reset_content                       = 205,
    partial_content                     = 206,
    multi_status                        = 207,
    already_reported                    = 208,
    im_used                             = 226,

    multiple_choices                    = 300,
    moved_permanently                   = 301,
    found                               = 302,
    see_other                           = 303,
    not_modified                        = 304,
    use_proxy                           = 305,
    temporary_redirect                  = 307,
    permanent_redirect                  = 308,

    bad_request                         = 400,
    unauthorized                        = 401,
    payment_required                    = 402,
    forbidden                           = 403,
    not_found                           = 404,
    method_not_allowed                  = 405,
    not_acceptable                      = 406,
    proxy_authentication_required       = 407,
    request_timeout                     = 408,
    conflict                            = 409,
    gone                                = 410,
    length_required                     = 411,
    precondition_failed                 = 412,
    payload_too_large                   = 413,
    uri_too_long                        = 414,
    unsupported_media_type              = 415,
    range_not_satisfiable               = 416,
    expectation_failed                  = 417,
    misdirected_request                 = 421,
    unprocessable_entity                = 422,
    locked                              = 423,
    failed_dependency                   = 424,
    upgrade_required                    = 426,
    precondition_required               = 428,
    too_many_requests                   = 429,
    request_header_fields_too_large     = 431,
    connection_closed_without_response  = 444,
    unavailable_for_legal_reasons       = 451,
    client_closed_request               = 499,

    internal_server_error               = 500,
    not_implemented                     = 501,
    bad_gateway                         = 502,
    service_unavailable                 = 503,
    gateway_timeout                     = 504,
    http_version_not_supported          = 505,
    variant_also_negotiates             = 506,
    insufficient_storage                = 507,
    loop_detected                       = 508,
    not_extended                        = 510,
    network_authentication_required     = 511,
    network_connect_timeout_error       = 599
};

/** Represents the class of a status-code.
*/
enum class status_class : unsigned
{
    /// Unknown status-class
    unknown = 0,

    /// The request was received, continuing processing.
    informational = 1,

    /// The request was successfully received, understood, and accepted.
    successful = 2,

    /// Further action needs to be taken in order to complete the request.
    redirection = 3,

    /// The request contains bad syntax or cannot be fulfilled.
    client_error = 4,

    /// The server failed to fulfill an apparently valid request.
    server_error = 5,
};

/** Converts the integer to a known status-code.

    If the integer does not match a known status code,
    @ref status::unknown is returned.
*/
BOOST_BEAST_DECL
status
int_to_status(unsigned v);

/** Convert an integer to a status_class.

    @param v The integer representing a status code.

    @return The status class. If the integer does not match
    a known status class, @ref status_class::unknown is returned.
*/
BOOST_BEAST_DECL
status_class
to_status_class(unsigned v);

/** Convert a status_code to a status_class.

    @param v The status code to convert.

    @return The status class.
*/
BOOST_BEAST_DECL
status_class
to_status_class(status v);

/** Returns the obsolete reason-phrase text for a status code.

    @param v The status code to use.
*/
BOOST_BEAST_DECL
string_view
obsolete_reason(status v);

/// Outputs the standard reason phrase of a status code to a stream.
BOOST_BEAST_DECL
std::ostream&
operator<<(std::ostream&, status);

} // http
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/impl/status.ipp>
#endif

#endif

/* status.hpp
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
*/