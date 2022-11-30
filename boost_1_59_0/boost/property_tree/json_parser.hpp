// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2015 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_JSON_PARSER_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_JSON_PARSER_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser/error.hpp>
#include <boost/property_tree/json_parser/detail/read.hpp>
#include <boost/property_tree/json_parser/detail/write.hpp>

#include <fstream>
#include <string>
#include <locale>

namespace boost { namespace property_tree { namespace json_parser
{

    /**
     * Read JSON from a the given stream and translate it to a property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @note Items of JSON arrays are translated into ptree keys with empty
     *       names. Members of objects are translated into named keys.
     * @note JSON data can be a string, a numeric value, or one of literals
     *       "null", "true" and "false". During parse, any of the above is
     *       copied verbatim into ptree data string.
     * @throw json_parser_error In case of error deserializing the property
     *                          tree.
     * @param stream Stream from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     */
    template<class Ptree>
    void read_json(std::basic_istream<
                       typename Ptree::key_type::value_type
                   > &stream,
                   Ptree &pt)
    {
        detail::read_json_internal(stream, pt, std::string());
    }

    /**
     * Read JSON from a the given file and translate it to a property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @note Items of JSON arrays are translated into ptree keys with empty
     *       names. Members of objects are translated into named keys.
     * @note JSON data can be a string, a numeric value, or one of literals
     *       "null", "true" and "false". During parse, any of the above is
     *       copied verbatim into ptree data string.
     * @throw json_parser_error In case of error deserializing the property
     *                          tree.
     * @param filename Name of file from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     * @param loc The locale to use when reading in the file contents.
     */
    template<class Ptree>
    void read_json(const std::string &filename,
                   Ptree &pt,
                   const std::locale &loc = std::locale())
    {
        std::basic_ifstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(json_parser_error(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        detail::read_json_internal(stream, pt, filename);
    }

    /**
     * Translates the property tree to JSON and writes it the given output
     * stream.
     * @note Any property tree key containing only unnamed subkeys will be
     *       rendered as JSON arrays.
     * @pre @e pt cannot contain keys that have both subkeys and non-empty data.
     * @throw json_parser_error In case of error translating the property tree
     *                          to JSON or writing to the output stream.
     * @param stream The stream to which to write the JSON representation of the
     *               property tree.
     * @param pt The property tree to tranlsate to JSON and output.
     * @param pretty Whether to pretty-print. Defaults to true for backward
     *               compatibility.
     */
    template<class Ptree>
    void write_json(std::basic_ostream<
                        typename Ptree::key_type::value_type
                    > &stream,
                    const Ptree &pt,
                    bool pretty = true)
    {
        write_json_internal(stream, pt, std::string(), pretty);
    }

    /**
     * Translates the property tree to JSON and writes it the given file.
     * @note Any property tree key containing only unnamed subkeys will be
     *       rendered as JSON arrays.
     * @pre @e pt cannot contain keys that have both subkeys and non-empty data.
     * @throw json_parser_error In case of error translating the property tree
     *                          to JSON or writing to the file.
     * @param filename The name of the file to which to write the JSON
     *                 representation of the property tree.
     * @param pt The property tree to translate to JSON and output.
     * @param loc The locale to use when writing out to the output file.
     * @param pretty Whether to pretty-print. Defaults to true and last place
     *               for backward compatibility.
     */
    template<class Ptree>
    void write_json(const std::string &filename,
                    const Ptree &pt,
                    const std::locale &loc = std::locale(),
                    bool pretty = true)
    {
        std::basic_ofstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(json_parser_error(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        write_json_internal(stream, pt, filename, pretty);
    }

} } }

namespace boost { namespace property_tree
{
    using json_parser::read_json;
    using json_parser::write_json;
    using json_parser::json_parser_error;
} }

#endif

/* json_parser.hpp
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
*/