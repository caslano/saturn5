// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_XML_PARSER_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_XML_PARSER_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/xml_parser_write.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>
#include <boost/property_tree/detail/xml_parser_flags.hpp>
#include <boost/property_tree/detail/xml_parser_read_rapidxml.hpp>

#include <fstream>
#include <string>
#include <locale>

namespace boost { namespace property_tree { namespace xml_parser
{

    /**
     * Reads XML from an input stream and translates it to property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @note XML attributes are placed under keys named @c \<xmlattr\>.
     * @throw xml_parser_error In case of error deserializing the property tree.
     * @param stream Stream from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     * @param flags Flags controlling the behaviour of the parser.
     *              The following flags are supported:
     * @li @c no_concat_text -- Prevents concatenation of text nodes into
     *                          datastring of property tree.  Puts them in
     *                          separate @c \<xmltext\> strings instead.
     * @li @c no_comments -- Skip XML comments.
     * @li @c trim_whitespace -- Trim leading and trailing whitespace from text,
     *                           and collapse sequences of whitespace.
     */
    template<class Ptree>
    void read_xml(std::basic_istream<
                      typename Ptree::key_type::value_type
                  > &stream,
                  Ptree &pt,
                  int flags = 0)
    {
        read_xml_internal(stream, pt, flags, std::string());
    }

    /**
     * Reads XML from a file using the given locale and translates it to
     * property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @note XML attributes are placed under keys named @c \<xmlattr\>.
     * @throw xml_parser_error In case of error deserializing the property tree.
     * @param filename The file from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     * @param flags Flags controlling the bahviour of the parser.
     *              The following flags are supported:
     * @li @c no_concat_text -- Prevents concatenation of text nodes into
     *                          datastring of property tree.  Puts them in
     *                          separate @c \<xmltext\> strings instead.
     * @li @c no_comments -- Skip XML comments.
     * @param loc The locale to use when reading in the file contents.
     */
    template<class Ptree>
    void read_xml(const std::string &filename,
                  Ptree &pt,
                  int flags = 0,
                  const std::locale &loc = std::locale())
    {
        BOOST_ASSERT(validate_flags(flags));
        std::basic_ifstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(xml_parser_error(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        read_xml_internal(stream, pt, flags, filename);
    }

    /**
     * Translates the property tree to XML and writes it the given output
     * stream.
     * @throw xml_parser_error In case of error translating the property tree to
     *                         XML or writing to the output stream.
     * @param stream The stream to which to write the XML representation of the 
     *               property tree.
     * @param pt The property tree to tranlsate to XML and output.
     * @param settings The settings to use when writing out the property tree as
     *                 XML.
     */
    template<class Ptree>
    void write_xml(std::basic_ostream<
                       typename Ptree::key_type::value_type
                   > &stream,
                   const Ptree &pt,
                   const xml_writer_settings<
                       typename Ptree::key_type
                   > & settings = xml_writer_settings<
                                    typename Ptree::key_type>() )
    {
        write_xml_internal(stream, pt, std::string(), settings);
    }

    /**
     * Translates the property tree to XML and writes it the given file.
     * @throw xml_parser_error In case of error translating the property tree to
     *                         XML or writing to the output stream.
     * @param filename The file to which to write the XML representation of the 
     *                 property tree.
     * @param pt The property tree to tranlsate to XML and output.
     * @param loc The locale to use when writing the output to file.
     * @param settings The settings to use when writing out the property tree as
     *                 XML.
     */
    template<class Ptree>
    void write_xml(const std::string &filename,
                   const Ptree &pt,
                   const std::locale &loc = std::locale(),
                   const xml_writer_settings<
                       typename Ptree::key_type
                   > & settings = xml_writer_settings<typename Ptree::key_type>())
    {
        std::basic_ofstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(xml_parser_error(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        write_xml_internal(stream, pt, filename, settings);
    }

} } }

namespace boost { namespace property_tree
{
    using xml_parser::read_xml;
    using xml_parser::write_xml;
    using xml_parser::xml_parser_error;

    using xml_parser::xml_writer_settings;
    using xml_parser::xml_writer_make_settings;
} }

#endif

/* xml_parser.hpp
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
*/