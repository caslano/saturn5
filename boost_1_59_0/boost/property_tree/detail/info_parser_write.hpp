// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_WRITE_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_WRITE_HPP_INCLUDED

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/detail/info_parser_utils.hpp"
#include <string>

namespace boost { namespace property_tree { namespace info_parser
{
    template<class Ch>
    void write_info_indent(std::basic_ostream<Ch> &stream,
          int indent,
          const info_writer_settings<Ch> &settings
          )
    {
        stream << std::basic_string<Ch>(indent * settings.indent_count, settings.indent_char);
    }
    
    // Create necessary escape sequences from illegal characters
    template<class Ch>
    std::basic_string<Ch> create_escapes(const std::basic_string<Ch> &s)
    {
        std::basic_string<Ch> result;
        typename std::basic_string<Ch>::const_iterator b = s.begin();
        typename std::basic_string<Ch>::const_iterator e = s.end();
        while (b != e)
        {
            if (*b == Ch('\0')) result += Ch('\\'), result += Ch('0');
            else if (*b == Ch('\a')) result += Ch('\\'), result += Ch('a');
            else if (*b == Ch('\b')) result += Ch('\\'), result += Ch('b');
            else if (*b == Ch('\f')) result += Ch('\\'), result += Ch('f');
            else if (*b == Ch('\n')) result += Ch('\\'), result += Ch('n');
            else if (*b == Ch('\r')) result += Ch('\\'), result += Ch('r');
            else if (*b == Ch('\v')) result += Ch('\\'), result += Ch('v');
            else if (*b == Ch('"')) result += Ch('\\'), result += Ch('"');
            else if (*b == Ch('\\')) result += Ch('\\'), result += Ch('\\');
            else
                result += *b;
            ++b;
        }
        return result;
    }

    template<class Ch>
    bool is_simple_key(const std::basic_string<Ch> &key)
    {
        const static std::basic_string<Ch> chars = convert_chtype<Ch, char>(" \t{};\n\"");
        return !key.empty() && key.find_first_of(chars) == key.npos;
    }
    
    template<class Ch>
    bool is_simple_data(const std::basic_string<Ch> &data)
    {
        const static std::basic_string<Ch> chars = convert_chtype<Ch, char>(" \t{};\n\"");
        return !data.empty() && data.find_first_of(chars) == data.npos;
    }

    template<class Ptree>
    void write_info_helper(std::basic_ostream<typename Ptree::key_type::value_type> &stream, 
                           const Ptree &pt, 
                           int indent,
                           const info_writer_settings<typename Ptree::key_type::value_type> &settings)
    {

        // Character type
        typedef typename Ptree::key_type::value_type Ch;
        
        // Write data
        if (indent >= 0)
        {
            if (!pt.data().empty())
            {
                std::basic_string<Ch> data = create_escapes(pt.template get_value<std::basic_string<Ch> >());
                if (is_simple_data(data))
                    stream << Ch(' ') << data << Ch('\n');
                else
                    stream << Ch(' ') << Ch('\"') << data << Ch('\"') << Ch('\n');
            }
            else if (pt.empty())
                stream << Ch(' ') << Ch('\"') << Ch('\"') << Ch('\n');
            else
                stream << Ch('\n');
        }
        
        // Write keys
        if (!pt.empty())
        {
            
            // Open brace
            if (indent >= 0)
            {
                write_info_indent( stream, indent, settings);
                stream << Ch('{') << Ch('\n');
            }
            
            // Write keys
            typename Ptree::const_iterator it = pt.begin();
            for (; it != pt.end(); ++it)
            {

                // Output key
                std::basic_string<Ch> key = create_escapes(it->first);
                write_info_indent( stream, indent+1, settings);
                if (is_simple_key(key))
                    stream << key;
                else
                    stream << Ch('\"') << key << Ch('\"');

                // Output data and children  
                write_info_helper(stream, it->second, indent + 1, settings);

            }
            
            // Close brace
            if (indent >= 0)
            {
                write_info_indent( stream, indent, settings);
                stream << Ch('}') << Ch('\n');
            }

        }
    }

    // Write ptree to info stream
    template<class Ptree>
    void write_info_internal(std::basic_ostream<typename Ptree::key_type::value_type> &stream, 
                             const Ptree &pt,
                             const std::string &filename,
                             const info_writer_settings<typename Ptree::key_type::value_type> &settings)
    {
        write_info_helper(stream, pt, -1, settings);
        if (!stream.good())
            BOOST_PROPERTY_TREE_THROW(info_parser_error("write error", filename, 0));
    }

} } }

#endif

/* info_parser_write.hpp
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
*/