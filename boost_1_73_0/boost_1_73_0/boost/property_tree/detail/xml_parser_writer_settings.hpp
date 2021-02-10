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
AgAACgAAAAgALWdKUmS6DNX8AAAAfwEAAB8ACQAAAAAAAQAAAAAAyuo3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1MDhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSiKmsXaMCAADQBQAAHwAJAAAAAAABAAAAAAAM7DcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUwOVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlI4S2qTtAEAAN8CAAAeAAkAAAAAAAEAAAAAAPXuNwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSMqwXzlcCAAD6BgAAHwAJAAAAAAABAAAAAADu8DcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUxMFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKhaAj2tAEAAEYEAAAfAAkAAAAAAAEAAAAAAIvzNwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTExVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlAkNvHxAQAAOQUAAB8ACQAAAAAAAQAAAAAAhfU3AGN1cmwtbWFzdGVyL3Rlc3RzL2Rh
*/