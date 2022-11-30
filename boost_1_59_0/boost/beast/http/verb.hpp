//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_VERB_HPP
#define BOOST_BEAST_HTTP_VERB_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string.hpp>
#include <iosfwd>

namespace boost {
namespace beast {
namespace http {

/** HTTP request method verbs

    Each verb corresponds to a particular method string
    used in HTTP request messages.
*/
enum class verb
{
    /** An unknown method.

        This value indicates that the request method string is not
        one of the recognized verbs. Callers interested in the method
        should use an interface which returns the original string.
    */
    unknown = 0,

    /// The DELETE method deletes the specified resource
    delete_,

    /** The GET method requests a representation of the specified resource.

        Requests using GET should only retrieve data and should have no other effect.
    */
    get,

    /** The HEAD method asks for a response identical to that of a GET request, but without the response body.
    
        This is useful for retrieving meta-information written in response
        headers, without having to transport the entire content.
    */
    head,

    /** The POST method requests that the server accept the entity enclosed in the request as a new subordinate of the web resource identified by the URI.

        The data POSTed might be, for example, an annotation for existing
        resources; a message for a bulletin board, newsgroup, mailing list,
        or comment thread; a block of data that is the result of submitting
        a web form to a data-handling process; or an item to add to a database
    */
    post,

    /** The PUT method requests that the enclosed entity be stored under the supplied URI.

        If the URI refers to an already existing resource, it is modified;
        if the URI does not point to an existing resource, then the server
        can create the resource with that URI.
    */
    put,

    /** The CONNECT method converts the request connection to a transparent TCP/IP tunnel.

        This is usually to facilitate SSL-encrypted communication (HTTPS)
        through an unencrypted HTTP proxy.
    */
    connect,

    /** The OPTIONS method returns the HTTP methods that the server supports for the specified URL.
    
        This can be used to check the functionality of a web server by requesting
        '*' instead of a specific resource.
    */
    options,

    /** The TRACE method echoes the received request so that a client can see what (if any) changes or additions have been made by intermediate servers.
    */
    trace,

    // WebDAV

    copy,
    lock,
    mkcol,
    move,
    propfind,
    proppatch,
    search,
    unlock,
    bind,
    rebind,
    unbind,
    acl,

    // subversion

    report,
    mkactivity,
    checkout,
    merge,

    // upnp

    msearch,
    notify,
    subscribe,
    unsubscribe,

    // RFC-5789

    patch,
    purge,

    // CalDAV

    mkcalendar,

    // RFC-2068, section 19.6.1.2

    link,
    unlink
};

/** Converts a string to the request method verb.

    If the string does not match a known request method,
    @ref verb::unknown is returned.
*/
BOOST_BEAST_DECL
verb
string_to_verb(string_view s);

/// Returns the text representation of a request method verb.
BOOST_BEAST_DECL
string_view
to_string(verb v);

/// Write the text for a request method verb to an output stream.
inline
std::ostream&
operator<<(std::ostream& os, verb v)
{
    return os << to_string(v);
}

} // http
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/impl/verb.ipp>
#endif

#endif

/* verb.hpp
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
*/