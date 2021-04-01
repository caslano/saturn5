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
klmItCQverSHRg/G8by/NYsyQGvZfTODcNcRc9rgGVUQ8mKHscuvnBKa1pfApC5OWD2a9rn79MYikBzQ+u8ADqwP9BlSWHorRViKQqnYy3BU2NXHFvRnumQd91tF8r+1MUQf6Vu1JfKOvaOXVertsGVpMxsKzKQJ/3O/xaOOWlX3alUa3Zeqmx1MEDGdAg3v2obY+ws/n3HB5C+P7B4qQQRPMEOMzYfT2Su4hUvDApboRs79NFo+cWxDug00KAWQHHRUgsepNxvdFigIrXlWZBCvpanFsKLafvKhtkB5rqx2oeVx/3SocR16P5A95akMa37ntvIxJNF02w9aCFvks+/gNXz2nzfOf9wR4ubVSnd0yxaLfoX2svseMWTcPbCRWY0tF8JBGKgMuyTjfHwtbfalbvebZVpDM0Avqd19mlQkxuwLe4CeKdGKp4JMLIA8P9OkKD7CSZY2OXHzxgNH0Ak1GPNZehMsN9LfbqQAEy6P/0ztHtkUn4GMewRLJE2Q41dzk9wNuqoAbIcwL2OGmWduVO7A9OjzMGLQN4me24Efj3H4ahtUY5gkQA==
*/