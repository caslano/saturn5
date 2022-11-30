// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_UTILS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_UTILS_HPP_INCLUDED

#include <boost/property_tree/detail/ptree_utils.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>
#include <string>
#include <algorithm>
#include <locale>

namespace boost { namespace property_tree { namespace xml_parser
{

    template<class Str>
    Str condense(const Str &s)
    {
        typedef typename Str::value_type Ch;
        Str r;
        std::locale loc;
        bool space = false;
        typename Str::const_iterator end = s.end();
        for (typename Str::const_iterator it = s.begin();
             it != end; ++it)
        {
            if (isspace(*it, loc) || *it == Ch('\n'))
            {
                if (!space)
                    r += Ch(' '), space = true;
            }
            else
                r += *it, space = false;
        }
        return r;
    }


    template<class Str>
    Str encode_char_entities(const Str &s)
    {
        // Don't do anything for empty strings.
        if(s.empty()) return s;

        typedef typename Str::value_type Ch;

        Str r;
        // To properly round-trip spaces and not uglify the XML beyond
        // recognition, we have to encode them IF the text contains only spaces.
        Str sp(1, Ch(' '));
        if(s.find_first_not_of(sp) == Str::npos) {
            // The first will suffice.
            r = detail::widen<Str>("&#32;");
            r += Str(s.size() - 1, Ch(' '));
        } else {
            typename Str::const_iterator end = s.end();
            for (typename Str::const_iterator it = s.begin(); it != end; ++it)
            {
                switch (*it)
                {
                    case Ch('<'): r += detail::widen<Str>("&lt;"); break;
                    case Ch('>'): r += detail::widen<Str>("&gt;"); break;
                    case Ch('&'): r += detail::widen<Str>("&amp;"); break;
                    case Ch('"'): r += detail::widen<Str>("&quot;"); break;
                    case Ch('\''): r += detail::widen<Str>("&apos;"); break;
                    default: r += *it; break;
                }
            }
        }
        return r;
    }

    template<class Str>
    Str decode_char_entities(const Str &s)
    {
        typedef typename Str::value_type Ch;
        Str r;
        typename Str::const_iterator end = s.end();
        for (typename Str::const_iterator it = s.begin(); it != end; ++it)
        {
            if (*it == Ch('&'))
            {
                typename Str::const_iterator semicolon = std::find(it + 1, end, Ch(';'));
                if (semicolon == end)
                    BOOST_PROPERTY_TREE_THROW(xml_parser_error("invalid character entity", "", 0));
                Str ent(it + 1, semicolon);
                if (ent == detail::widen<Str>("lt")) r += Ch('<');
                else if (ent == detail::widen<Str>("gt")) r += Ch('>');
                else if (ent == detail::widen<Str>("amp")) r += Ch('&');
                else if (ent == detail::widen<Str>("quot")) r += Ch('"');
                else if (ent == detail::widen<Str>("apos")) r += Ch('\'');
                else
                    BOOST_PROPERTY_TREE_THROW(xml_parser_error("invalid character entity", "", 0));
                it = semicolon;
            }
            else
                r += *it;
        }
        return r;
    }

    template<class Str>
    const Str &xmldecl()
    {
        static Str s = detail::widen<Str>("<?xml>");
        return s;
    }

    template<class Str>
    const Str &xmlattr()
    {
        static Str s = detail::widen<Str>("<xmlattr>");
        return s;
    }

    template<class Str>
    const Str &xmlcomment()
    {
        static Str s = detail::widen<Str>("<xmlcomment>");
        return s;
    }

    template<class Str>
    const Str &xmltext()
    {
        static Str s = detail::widen<Str>("<xmltext>");
        return s;
    }

} } }

#endif

/* xml_parser_utils.hpp
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
*/