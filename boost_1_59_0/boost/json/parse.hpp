//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_PARSE_HPP
#define BOOST_JSON_PARSE_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/error.hpp>
#include <boost/json/parse_options.hpp>
#include <boost/json/storage_ptr.hpp>
#include <boost/json/string_view.hpp>
#include <boost/json/value.hpp>

BOOST_JSON_NS_BEGIN

/** Return parsed JSON as a @ref value.

    This function parses an entire string in one
    step to produce a complete JSON object, returned
    as a @ref value. If the buffer does not contain a
    complete serialized JSON, an error occurs. In this
    case the returned value will be null, using the
    default memory resource.

    @par Complexity
    Linear in `s.size()`.

    @par Exception Safety
    Strong guarantee.
    Calls to `memory_resource::allocate` may throw.

    @return A value representing the parsed JSON,
    or a null if any error occurred.

    @param s The string to parse.

    @param ec Set to the error, if any occurred.

    @param sp The memory resource that the new value and all
    of its elements will use. If this parameter is omitted,
    the default memory resource is used.

    @param opt The options for the parser. If this parameter
    is omitted, the parser will accept only standard JSON.

    @see
        @ref parse_options,
        @ref stream_parser.
*/
/** @{ */
BOOST_JSON_DECL
value
parse(
    string_view s,
    error_code& ec,
    storage_ptr sp = {},
    parse_options const& opt = {});

BOOST_JSON_DECL
value
parse(
    string_view s,
    std::error_code& ec,
    storage_ptr sp = {},
    parse_options const& opt = {});
/** @} */

/** Parse a string of JSON into a @ref value.

    This function parses an entire string in one
    step to produce a complete JSON object, returned
    as a @ref value. If the buffer does not contain a
    complete serialized JSON, an exception is thrown.

    @par Complexity
    Linear in `s.size()`.

    @par Exception Safety
    Strong guarantee.
    Calls to `memory_resource::allocate` may throw.

    @return A value representing the parsed
    JSON upon success.

    @param s The string to parse.

    @param sp The memory resource that the new value and all
    of its elements will use. If this parameter is omitted,
    the default memory resource is used.

    @param opt The options for the parser. If this parameter
    is omitted, the parser will accept only standard JSON.

    @throw system_error Thrown on failure.

    @see
        @ref parse_options,
        @ref stream_parser.
*/
BOOST_JSON_DECL
value
parse(
    string_view s,
    storage_ptr sp = {},
    parse_options const& opt = {});

BOOST_JSON_NS_END

#endif

/* parse.hpp
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
*/