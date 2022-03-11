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