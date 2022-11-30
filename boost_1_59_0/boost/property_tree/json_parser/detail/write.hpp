// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_WRITE_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_WRITE_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/next_prior.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <string>
#include <ostream>
#include <iomanip>

namespace boost { namespace property_tree { namespace json_parser
{

    // Create necessary escape sequences from illegal characters
    template<class Ch>
    std::basic_string<Ch> create_escapes(const std::basic_string<Ch> &s)
    {
        std::basic_string<Ch> result;
        typename std::basic_string<Ch>::const_iterator b = s.begin();
        typename std::basic_string<Ch>::const_iterator e = s.end();
        while (b != e)
        {
            typedef typename make_unsigned<Ch>::type UCh;
            UCh c(*b);
            // This assumes an ASCII superset. But so does everything in PTree.
            // We escape everything outside ASCII, because this code can't
            // handle high unicode characters.
            if (c == 0x20 || c == 0x21 || (c >= 0x23 && c <= 0x2E) ||
                (c >= 0x30 && c <= 0x5B) || (c >= 0x5D && c <= 0xFF))
                result += *b;
            else if (*b == Ch('\b')) result += Ch('\\'), result += Ch('b');
            else if (*b == Ch('\f')) result += Ch('\\'), result += Ch('f');
            else if (*b == Ch('\n')) result += Ch('\\'), result += Ch('n');
            else if (*b == Ch('\r')) result += Ch('\\'), result += Ch('r');
            else if (*b == Ch('\t')) result += Ch('\\'), result += Ch('t');
            else if (*b == Ch('/')) result += Ch('\\'), result += Ch('/');
            else if (*b == Ch('"'))  result += Ch('\\'), result += Ch('"');
            else if (*b == Ch('\\')) result += Ch('\\'), result += Ch('\\');
            else
            {
                const char *hexdigits = "0123456789ABCDEF";
                unsigned long u = (std::min)(static_cast<unsigned long>(
                                                 static_cast<UCh>(*b)),
                                             0xFFFFul);
                unsigned long d1 = u / 4096; u -= d1 * 4096;
                unsigned long d2 = u / 256; u -= d2 * 256;
                unsigned long d3 = u / 16; u -= d3 * 16;
                unsigned long d4 = u;
                result += Ch('\\'); result += Ch('u');
                result += Ch(hexdigits[d1]); result += Ch(hexdigits[d2]);
                result += Ch(hexdigits[d3]); result += Ch(hexdigits[d4]);
            }
            ++b;
        }
        return result;
    }

    template<class Ptree>
    void write_json_helper(std::basic_ostream<typename Ptree::key_type::value_type> &stream, 
                           const Ptree &pt,
                           int indent, bool pretty)
    {

        typedef typename Ptree::key_type::value_type Ch;
        typedef typename std::basic_string<Ch> Str;

        // Value or object or array
        if (indent > 0 && pt.empty())
        {
            // Write value
            Str data = create_escapes(pt.template get_value<Str>());
            stream << Ch('"') << data << Ch('"');

        }
        else if (indent > 0 && pt.count(Str()) == pt.size())
        {
            // Write array
            stream << Ch('[');
            if (pretty) stream << Ch('\n');
            typename Ptree::const_iterator it = pt.begin();
            for (; it != pt.end(); ++it)
            {
                if (pretty) stream << Str(4 * (indent + 1), Ch(' '));
                write_json_helper(stream, it->second, indent + 1, pretty);
                if (boost::next(it) != pt.end())
                    stream << Ch(',');
                if (pretty) stream << Ch('\n');
            }
            if (pretty) stream << Str(4 * indent, Ch(' '));
            stream << Ch(']');

        }
        else
        {
            // Write object
            stream << Ch('{');
            if (pretty) stream << Ch('\n');
            typename Ptree::const_iterator it = pt.begin();
            for (; it != pt.end(); ++it)
            {
                if (pretty) stream << Str(4 * (indent + 1), Ch(' '));
                stream << Ch('"') << create_escapes(it->first) << Ch('"') << Ch(':');
                if (pretty) stream << Ch(' ');
                write_json_helper(stream, it->second, indent + 1, pretty);
                if (boost::next(it) != pt.end())
                    stream << Ch(',');
                if (pretty) stream << Ch('\n');
            }
            if (pretty) stream << Str(4 * indent, Ch(' '));
            stream << Ch('}');
        }

    }

    // Verify if ptree does not contain information that cannot be written to json
    template<class Ptree>
    bool verify_json(const Ptree &pt, int depth)
    {

        typedef typename Ptree::key_type::value_type Ch;
        typedef typename std::basic_string<Ch> Str;

        // Root ptree cannot have data
        if (depth == 0 && !pt.template get_value<Str>().empty())
            return false;
        
        // Ptree cannot have both children and data
        if (!pt.template get_value<Str>().empty() && !pt.empty())
            return false;

        // Check children
        typename Ptree::const_iterator it = pt.begin();
        for (; it != pt.end(); ++it)
            if (!verify_json(it->second, depth + 1))
                return false;

        // Success
        return true;

    }
    
    // Write ptree to json stream
    template<class Ptree>
    void write_json_internal(std::basic_ostream<typename Ptree::key_type::value_type> &stream, 
                             const Ptree &pt,
                             const std::string &filename,
                             bool pretty)
    {
        if (!verify_json(pt, 0))
            BOOST_PROPERTY_TREE_THROW(json_parser_error("ptree contains data that cannot be represented in JSON format", filename, 0));
        write_json_helper(stream, pt, 0, pretty);
        stream << std::endl;
        if (!stream.good())
            BOOST_PROPERTY_TREE_THROW(json_parser_error("write error", filename, 0));
    }

} } }

#endif

/* write.hpp
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
*/