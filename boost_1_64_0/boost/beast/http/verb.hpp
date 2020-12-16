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
cst6Wtb4Ws09qHxp1vSW1h4ayn6nHmwKr4MtYaxcVyPYGzaGg2BTOBu2gI/DVvBJeAM8BKfDE/AO+A6cCS/C9vBn2AHqnLsTtMNeMBj2huPhcDhR3NNhHzhT4i2EA+DdcDB8DA6DT0i6QzAZvgD7wlfgKHgSpsL3YRr8CKbDs3A0/BZmwKK0tzEwGI6FFeA4GA6zYR2YA2PgBNgcToQJcBLsAm+DA+EUmAinwgw4DeZCrkXWdzLHIPghaW7rOw0S+7OhsCIcBsNhGqwJb4YxMBE2E/94OAJ2gCNhIkyB6XAUnARvgdMkvrR7GUswFvHS7tuJHVUH2BB2hE1gFzlfV9gWdoP9YHc4APaHybAXzIG94TzYB66Q8G/geetdW40T1Plb8/cZaZ+j5fozYG2YBevDcbABPAs7w2zYA+bCJDgeZsPJcr2IWp9uBtwF74B74Ey4D86Fh+A8+DpcCk+LPeTn8B54Aa6AP8J7YXnjvRuGwVUwAt4Ha8HVsB5cCxvCdfBG+AAcDDfCYfBBOBI+DNPgI3AMfAzmwyfgRvgMfBTuh0/CA/BpeAg+J3aNX8Cj8AI8ATXq8y1YDJ6CJeF7MAK+D6vC07A6VOthwQ9hA7gUtoObYRf4MRwAP4E3w09hBnwcToZ74SJ4Fq6GR+AW+CLcAV+Cu+AEue/R5juavF+mIUZ/FiH3/Z9iZ3le2vvXsDH8BraH38GR8BJMg9/DLPgDnAt/hEvgL/BuqPHcrQIB0h8Xk36rONwPS8D3YQg8AyvA8zAUarIeVRhE1H2OhLVgVRgLq8MWsAa8Hv5kPIfwZzhA1tMaCcPhaFgJToKl4GxYWvq3MnAJ/Bfplkm6PNuV93jvVTcQu8Er2wxeK3tBJ1vBa2on6GYf+KttA53sAq9oE5hRN/CqbQKvhT3gNbUF9GEHmFe3cOsgrSTebuQEcgEJqodtIBKP9KvntwX0H/89xx+k/x/RrOm10/8Hl3TW/5O15tD/BxVC/38w30n/P4ICN2taKP2/Oc9zzNfef/lXsfdf/hX2/sv/bXv/mbrpCLuPfbwcZaXiCqebJv5lddOEu+7llX9l3fSEfA/dNPlcYS+v/D9PNx0r+8PNkzULoNJNH7vXrEufummJ08z6VrDoSsPd1/aUXs5XnZLGde8uu0ozwPayXtTnmgWksdYsyMCtqTSDbcf0AF/6ZElTz5pD/EG5E23H9UCV5nMv83plVb6dbZv0SA99cSVpAz+rfIbZhnM/v9OWsAtLdWkf7Eik0qdz9e10b/uNlFpFuNOeN48qd3Wf+shwlV+CbQOzge76xgzit0PKRDkYDI155LLQ8AuxdJCF/SZT9ItGmZzcJ3Cb+sZvVlrrC1hrFcwiXPSITU2/wys91zmYvtJTtzhxpatusY/lbqHSXMDtolvEL8uK0/h3W+MgUNYNuB0po8bHsj/KavOZ8K1rPK7ijHbXNUraEGl7nnrzcyq8k4e+sXzU1enlLqdvPCPXda/0m3PkujTrui6rbySeq74x1JGOeQrd5zPVUMW5WWvtpm8MvcrrupK+Mai4REZKIS2RdMOmrqAfyxqfm+OtH5M47bz+rnVzCq9u7KFBHe4LlD007KWMvTOKlixVsq7xR0lvv43Sx89UeVzn5bdR7GhUeF1lW1CCesKLZ9pRL9GFvt/mb4DvfXPzSzkSrwlg3AqXQLV+wVKznnzqZSVOfa229PcvK3dWQAXO8Kz+trbP1larZ2cMah+rVQ2IMW1+fOlrJb9osbVgvkC5hwaEq11NStq7YMgWKvq+k8uU/tR+G/tLVbY11Mlb6bh87IcmedeyfjOeV+7xAZU0u0990Ksqzq0BZbQi6P9KOMVT/YY=
*/