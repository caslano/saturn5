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