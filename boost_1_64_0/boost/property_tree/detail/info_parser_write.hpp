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
L4yyQuSE58ywRtEjzCPGWCL/kcaeYVaIPMoxwEUWGJ7yufYhn40/xliwRO5jzRNWy9yPFDc4f1+fETebf4nfN5VjbXittiR+1pw1zwsuuAd8I3U5Hs6Kk6x4LcffuGu9mb57viRGb+w48Tuph8Qdf0doRRx6ps+Yb6If+B2pwekb+xz/ku8oiAV+r8jwd9UpreQN6hLzcs1/Rlil5KbmHeOJ3xXPmMeL5L3QsXkz48EF5tkienPHIBOsUJBnTLjIArm3kIchZojcUh10JH6GVpxjg6O30l82/Q79aXFADPLtY383s1ocZo6sW1sLOM8UG+TfxjxilHUKbmt7vyt+gg6Px1gmq8AaSx9TrJN/O33iPGcd67G7aPONfHfC4+2vGCt/32qJCa+vUHhXx57f83tCHKjx3YqYMfV4jk2idzP2zLFNrFi5zJFzd/OYUTY4cg/9YpW8e5onDHMx/NnpFY8LS4yj+/Yd4gSrFJjrx2+ifV6fNJce7fkI2fdSH8PMk3NvZTLGOkcP2Q8sUXDYmDHBFkfuo71Fie8Wusfu8SzbFN/XPvux76GJc2xTckSfmGSLovup64vmrzjJFtEjQXD0/uoS86y7FzxeJPcBxoAJtig8qi+MsUjeA7WLYVYpfpD5+FjfYxLnyD6mT4yxyDaFUfuUWdYpKjW/mGSTQ2X2L4vkliuPcTYojtmWKSIV5i4d2cZT3PK3nBfEbfq+4HirNH5MuUe9KhZWycs0O8SqpTPHJtEaaxhL5NWa34yywaE684d5cuq1iWFm2ORQgzazyBZFjfIwzCKRJvuBkwwzR4f1fkM8Erct8+Q82Pjid/T5uTL9YoltZp/tfv71zYXn+H66OCiOJqK/LbwkLpn/eTcw71lrurqPynz/9IbmNyNPDbxntd6Jg/7G/3nra/ch90atK/Vv1A5pefdwnz/xM+DikJ/fGhEnfuF7WGzex3cI/K3IWb+7aCGRz99PPMEQM2xT9CvfWWKYebYo3HA/jdGEa1kilLPk8dl7qpvWEvWwStYVymedOOdZVmfkiO8u+PtWjyb4te9tsWHbPNt0ezxBvTxnmWGNfOtrNYNMs/pr7fO3t1qZYI2C39qOCeUukzsQBJPaN2adH/T6kOezRBK/F5A547XB6a9bY6Tnb9qe80yzPGoNfL28h7WVYWYpTPwdCPGS9Tzb+OUa/3X5S35nbCi8vzKlrXi98JD6vbZInr+BeJwO6TPOE0durvzz1jz6mGGDomdZ3xhjkexny8MFZtii8DnOLYyxTv4F510usEjwXOddBphnh9jzrPnMscmR51ufmWadksEgOMlFFsl9gTIYZp6cF3rOMHNkv8gawwVmCIaMFaeZYp1h/Z0n6w+usTjPNNsUbdknvqO5ftR3gHaMHaNsUvx336Fj8oH29YOMl8dblPzD67R6fZuotEHqP6SNXh9+uXb801w45jVxQtziosdrlATWTmbIvpo1IuqerjjKGsVXt9aQ6++Dn+Aia+SXycectCJ/0yz7GtYbBlkmL+I45wKzbFB8TWuOvxt43t/MP+L4zBv1fVSPH31Jv82hGSY8XiHvR74byyA7ecZXPGTdH76+41qcZYMjPzGGLJC1Zixz7XexI8t+o/gGxtzzOebLA/cBHe8UvNZ3dyn0d0xPM8ZQ4jpczFs3pg+wbojnCW7nWueYfc0g016LPN81LkdWjT1TFP3A42XfQRNn6f6KeU786Y6lr0pjkh1iS+pjmcjXHGcMMM/qO6xrX3dssLN77el66bHWEc8XWV8zdt8wblxgiR1m/W3jat9ZHvmm8SD4lroZZZ28b8vTq7/iBOsUrTiXMsk21d8x5syyw9HvWsv8LMA=
*/