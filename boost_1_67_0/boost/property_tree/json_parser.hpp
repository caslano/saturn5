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