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
mBN6GYp6W99R3t6oznDq71K3Dtjx+IhGxUlKp407zmhXPakEXR6lWLX6GcIYpzWVF6kH3zguokNWuO9/S+eHsN5Bh6OnLMWNP+1n0nePn8fPeoAT4kJugGuQ8wca5ydXDexzCRyCe6XvpziV3VldIhmSKyK52s1zrfqch9MoHHGfLy+iiE4M7bda1fndFC/jJU7U7ZRFXqbyzVkqOUbxO0rmIMwVPfm0rxWLfZLTy51OiGfi25gOlSVmVyFUbd+stT0McMMhxAQY1faKkIn7U3N1H8+lMt7xkdNiixKd7CiZeQznA/JeB2fMMXyQM2Q6VIewol2DdUwROljhU8O8z/oqi1YGxy3eQg3yNqO1MqSqNykZOh+0+h9nct1u3mkXHTVRl3a2KnmWCxgI7qwtoAMlTdDJlUxyOkjTkUadpIhA5zjpIcRa8e7EtCW3m55paJ+h97Ybtay5j/Z1YyQ5Ym8IS9WjqlSbY/U8J9e/MZ8zubiuhAhy5/71s5up2h38th91yxwHu7zyIo1Rs0tQI7SBxejdk9Mq4SKL2qHXzXFkYcLjTIQeO2v6KqvrwU5aZIWHEDcWNtha1+e5nMdhP23jCfHACV1EcEFn2e/5b4e1vDQJOiFM2jjFEgH7Zr7R4Xxdp/d8PiYpznzauLSJDDj0pnp1M4OaVX81WclbyxrXDI2KQq/okrhVIwrOLN8BjWi9Lj+9YctqS4hbTKhKXCdkRMzQEDEut7qmis2TiaxAUn/fQ29WqsdtLpbfKf7urojZupv+dhn1pqOry1PcnXnTgXAp7k64URQuxdzBVKAwLP39ChTTh/8jnaehcUX9dqfBvZKkUeDlR1i45vtV2Hfkatc0rkZvt5bp3RQuYLptIWRH4+6lt1K7gcKld0gpJ6RpH/jiO4UyES69QUrWu/RnXXS1W+P7kyt/LHyxcLeu4pbjcFvGQO4H7KsVjLtqYfsBtrlH2UQjTCLKCXY7lB/el/ySOg+ghB3gsFpO6zsTDBFk6Fy02BSuyrZ52dp7ISFgMPakPqDchoJmWqNZf1+qrMNNpXReweddWsgNbUVhQapN1XUJ/tXLGjhZyhrWu6KBkStCwz56EYNV63lL80QcKmD17a+Bv2yvgatdLW6taPhnry3gYgbyATK8J64LOHK7nTX7IlOv6wmYqBBoylyIGnb+RgIGtuQjbbFyzk0kbHNVl9P1+eUtBEwobdjqxJLnXYtvJeB6+HTOxkfeWnwntyTDX56svp/dFi539n3skPiuU1xq/pc7rL+byrGziRe9prLzh1ubRuL13cDDts0QIMqjbKeh05tfvS80rtB02zg3XkYPQ2tuVDpvexk/9PG1vsv5xVva99Q8v9Nxu4XjWrFsJu5Ix2PxchMZYmER09ZxTCYAdo/wm4fts+l2lGdYwAKnt4z6VTfiFndW56Gh0dwqqwuiOFSAHculse8KVvxPN/RSBH+gzBlTRcVzz5R9Lh9h05LGcVfyRBkVkY5VmtYDU3dmI9yY0zmIlb8QV0AdeFFsfvssfrgwjaCvoMQZnQtMDAnOzAUnjHKdO8iwNjqcziHsbNIqFB/ucwhK7Y5oPGWf5XVxKb9sR0iWJ7Ex5s224iocaiF2fVZ83bbFNyzaaRtZrBzc5h1sD2p8HwRcbofFLpqK8BfHl9hoq7a96r1cj+t70XO5HPlYd5GLJnOE8le4A52bC3x5zFg7RFgCzgNTIEumSr5N3rxX8TLjaYSFLEdWn9MUdjJUbXqd1ZewLUO8nQXxQqwnaJ+mkcPRJKyinQHtARdkW5fQNsipjhf8Jqc1VZYdcMRppaig8C3qOuo9tsXbdzDqLooEQnaqeSAsSlHScB2iVmA=
*/