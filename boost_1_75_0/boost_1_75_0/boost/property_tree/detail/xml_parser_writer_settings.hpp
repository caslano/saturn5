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
FKBPQejzzv3YbBsatx24D8RIINbvigcEQCDEqsC8KCAWIRCLaDyUP4znpuwm0pk7mhLF/sk9yRawzkw2hOVyl9KBSduuiO3P4z4piJbKlj4Gu4WMsjICiuAfZOC/TrQCYU8LwV5E8Dnkb9T166JKOxqRdjTSrgDmK1cemcQBTiO4iIT56Cbdu8rMMRR3xj1xXDWsU7iJh3ZG1MY8n8YakwONQf0Z1hja0KrBxqxFfoU15gHUF22Exvzpe9aYNLQL6pSPIcGmBfAtqBAa9Rpr1MuDxoTW5Rrerh5ol0Pd/WTzjR5uwBlKH8CrkfV8dmeYPXLGtJbVZ03oPA08j3IP3SjcxT1WZU0afySghCbnOCPOdd2hGCqaLXZ+lw5VWflFxEh/B/fHgN9ToxfkVtTDr3HIN1kc8m1pDrkJMPvf1DPmbeVskr18B9r1+g53UnCPwHU3zpsOWgSPqnDi6JOxfSTeP2fVks198OzjHjt69nBPEXqe5p58dVllJ4i4tg5sthg82bMI4KFB6CkN4tazep5fxEjoqT8LkedXfEB6aXkKYdkcxLI5dBMp6qgfJNIZqyCTShfUs6QPRaILWAVu0SLGHMBzQ9xX3/ptaOoeCq1aBxiavMr4GCIWObi1fsE+bhltmd4BHwoqoPjsJluuH+9AOVfRmlPHLowE/QwfPOc1jRXBlDduxu7F26GLTbRD/z83h3Z9JzJD00R0
*/