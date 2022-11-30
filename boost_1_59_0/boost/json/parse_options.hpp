//
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_PARSE_OPTIONS_HPP
#define BOOST_JSON_PARSE_OPTIONS_HPP

#include <boost/json/detail/config.hpp>

BOOST_JSON_NS_BEGIN

/** Parser options

    This structure is used for specifying
    maximum parsing depth, and whether
    to allow various non-standard extensions.
    Default-constructed options set maximum
    parsing depth to 32 and specify that only
    standard JSON is allowed,

    @see
        @ref basic_parser,
        @ref parser.
*/
struct parse_options
{
    /** Maximum nesting level of arrays and objects.

        This specifies the maximum number of nested
        structures allowed while parsing a JSON. If
        this limit is exceeded during a parse, an
        error is returned.

        @see
            @ref basic_parser,
            @ref stream_parser.
    */
    std::size_t max_depth = 32;

    /** Non-standard extension option

        Allow C and C++ style comments to appear
        anywhere that whitespace is permissible.

        @see
            @ref basic_parser,
            @ref stream_parser.
    */
    bool allow_comments = false;

    /** Non-standard extension option

        Allow a trailing comma to appear after
        the last element of any array or object.

        @see
            @ref basic_parser,
            @ref stream_parser.
    */
    bool allow_trailing_commas = false;

    /** Non-standard extension option

        Allow invalid UTF-8 sequnces to appear
        in keys and strings.

        @note This increases parsing performance.

        @see
            @ref basic_parser,
            @ref stream_parser.
    */
    bool allow_invalid_utf8 = false;
};

BOOST_JSON_NS_END

#endif

/* parse_options.hpp
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
*/