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