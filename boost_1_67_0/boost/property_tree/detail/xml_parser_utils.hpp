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