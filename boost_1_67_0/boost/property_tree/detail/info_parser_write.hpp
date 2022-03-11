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