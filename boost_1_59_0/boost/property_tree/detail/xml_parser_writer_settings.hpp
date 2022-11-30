// ----------------------------------------------------------------------------
// Copyright (C) 2002-2007 Marcin Kalicinski
// Copyright (C) 2007 Alexey Baskakov
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_WRITER_SETTINGS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_WRITER_SETTINGS_HPP_INCLUDED

#include <string>
#include <boost/property_tree/detail/ptree_utils.hpp>

namespace boost { namespace property_tree { namespace xml_parser
{

    // Naively convert narrow string to another character type
    template<class Str>
    Str widen(const char *text)
    {
        typedef typename Str::value_type Ch;
        Str result;
        while (*text)
        {
            result += Ch(*text);
            ++text;
        }
        return result;
    }

    //! Xml writer settings. The default settings lead to no pretty printing.
    template<class Str>
    class xml_writer_settings
    {
        typedef typename Str::value_type Ch;
    public:
        xml_writer_settings(Ch inchar = Ch(' '),
                typename Str::size_type incount = 0,
                const Str &enc = widen<Str>("utf-8"))
            : indent_char(inchar)
            , indent_count(incount)
            , encoding(enc)
        {
        }

        Ch indent_char;
        typename Str::size_type indent_count;
        Str encoding;
    };

    template <class Str>
    xml_writer_settings<Str> xml_writer_make_settings(typename Str::value_type indent_char = (typename Str::value_type)(' '),
        typename Str::size_type indent_count = 0,
        const Str &encoding = widen<Str>("utf-8"))
    {
        return xml_writer_settings<Str>(indent_char, indent_count, encoding);
    }

} } }

#endif

/* xml_parser_writer_settings.hpp
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
*/