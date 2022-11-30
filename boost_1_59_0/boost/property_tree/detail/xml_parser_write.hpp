// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2013 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_WRITE_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_WRITE_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/xml_parser_utils.hpp>
#include <string>
#include <ostream>
#include <iomanip>

namespace boost { namespace property_tree { namespace xml_parser
{
    template<class Str>
    void write_xml_indent(std::basic_ostream<typename Str::value_type> &stream,
          int indent,
          const xml_writer_settings<Str> & settings
          )
    {
        stream << std::basic_string<typename Str::value_type>(indent * settings.indent_count, settings.indent_char);
    }

    template<class Str>
    void write_xml_comment(std::basic_ostream<typename Str::value_type> &stream,
                           const Str &s,
                           int indent,
                           bool separate_line,
                           const xml_writer_settings<Str> & settings
                           )
    {
        typedef typename Str::value_type Ch;
        if (separate_line)
            write_xml_indent(stream,indent,settings);
        stream << Ch('<') << Ch('!') << Ch('-') << Ch('-');
        stream << s;
        stream << Ch('-') << Ch('-') << Ch('>');
        if (separate_line)
            stream << Ch('\n');
    }

    template<class Str>
    void write_xml_text(std::basic_ostream<typename Str::value_type> &stream,
                        const Str &s,
                        int indent, 
                        bool separate_line,
                        const xml_writer_settings<Str> & settings
                        )
    {
        typedef typename Str::value_type Ch;
        if (separate_line)
            write_xml_indent(stream,indent,settings);
        stream << encode_char_entities(s);
        if (separate_line)
            stream << Ch('\n');
    }

    template<class Ptree>
    void write_xml_element(std::basic_ostream<typename Ptree::key_type::value_type> &stream,
                           const typename Ptree::key_type &key,
                           const Ptree &pt,
                           int indent,
                           const xml_writer_settings<typename Ptree::key_type> & settings)
    {
        typedef typename Ptree::key_type::value_type Ch;
        typedef typename Ptree::key_type Str;
        typedef typename Ptree::const_iterator It;

        bool want_pretty = settings.indent_count > 0;
        // Find if elements present
        bool has_elements = false;
        bool has_attrs_only = pt.data().empty();
        for (It it = pt.begin(), end = pt.end(); it != end; ++it)
        {
            if (it->first != xmlattr<Str>() )
            {
                has_attrs_only = false;
                if (it->first != xmltext<Str>())
                {
                    has_elements = true;
                    break;
                }
            }
        }

        // Write element
        if (pt.data().empty() && pt.empty())    // Empty key
        {
            if (indent >= 0)
            {
                write_xml_indent(stream,indent,settings);
                stream << Ch('<') << key << 
                          Ch('/') << Ch('>');
                if (want_pretty)
                    stream << Ch('\n');
            }
        }
        else    // Nonempty key
        {
            // Write opening tag, attributes and data
            if (indent >= 0)
            {
                // Write opening brace and key
                write_xml_indent(stream,indent,settings);
                stream << Ch('<') << key;

                // Write attributes
                if (optional<const Ptree &> attribs = pt.get_child_optional(xmlattr<Str>()))
                    for (It it = attribs.get().begin(); it != attribs.get().end(); ++it)
                        stream << Ch(' ') << it->first << Ch('=')
                               << Ch('"')
                               << encode_char_entities(
                                    it->second.template get_value<Str>())
                               << Ch('"');

                if ( has_attrs_only )
                {
                    // Write closing brace
                    stream << Ch('/') << Ch('>');
                    if (want_pretty)
                        stream << Ch('\n');
                }
                else
                {
                    // Write closing brace
                    stream << Ch('>');

                    // Break line if needed and if we want pretty-printing
                    if (has_elements && want_pretty)
                        stream << Ch('\n');
                }
            }

            // Write data text, if present
            if (!pt.data().empty())
                write_xml_text(stream,
                    pt.template get_value<Str>(),
                    indent + 1, has_elements && want_pretty, settings);

            // Write elements, comments and texts
            for (It it = pt.begin(); it != pt.end(); ++it)
            {
                if (it->first == xmlattr<Str>())
                    continue;
                else if (it->first == xmlcomment<Str>())
                    write_xml_comment(stream,
                        it->second.template get_value<Str>(),
                        indent + 1, want_pretty, settings);
                else if (it->first == xmltext<Str>())
                    write_xml_text(stream,
                        it->second.template get_value<Str>(),
                        indent + 1, has_elements && want_pretty, settings);
                else
                    write_xml_element(stream, it->first, it->second,
                        indent + 1, settings);
            }

            // Write closing tag
            if (indent >= 0 && !has_attrs_only)
            {
                if (has_elements)
                    write_xml_indent(stream,indent,settings);
                stream << Ch('<') << Ch('/') << key << Ch('>');
                if (want_pretty)
                    stream << Ch('\n');
            }

        }
    }

    template<class Ptree>
    void write_xml_internal(std::basic_ostream<typename Ptree::key_type::value_type> &stream, 
                            const Ptree &pt,
                            const std::string &filename,
                            const xml_writer_settings<typename Ptree::key_type> & settings)
    {
        typedef typename Ptree::key_type Str;
        stream  << detail::widen<Str>("<?xml version=\"1.0\" encoding=\"")
                << settings.encoding
                << detail::widen<Str>("\"?>\n");
        write_xml_element(stream, Str(), pt, -1, settings);
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(xml_parser_error("write error", filename, 0));
    }

} } }

#endif

/* xml_parser_write.hpp
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
*/