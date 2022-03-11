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