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