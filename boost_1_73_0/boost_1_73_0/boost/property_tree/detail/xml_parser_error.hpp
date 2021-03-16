// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace xml_parser
{

    //! Xml parser error
    class xml_parser_error: public file_parser_error
    {
    public:
        xml_parser_error(const std::string &msg,
                         const std::string &file,
                         unsigned long l):
            file_parser_error(msg, file, l)
        {
        }
    };

} } }

#endif

/* xml_parser_error.hpp
zvHk8x1x5UCxHQ/K8MU6vlUmCPhncdYT0F7x5MlWH7bCSTTNtGD8xuJKByuXFYMn5ImA1VbMVPsF3K61AibfphVzO5XvMYi+/47LiLrPQMT3OebM6T6Y619bc32TUxZ5z1C98h/L93P4qV6y+K6xqWYmRIHlm+cY6QySVzTosc1U67HY0bPGJ8uCa6XzSBVr8a2th+yEPJnQjt/YeCSVfWN8jeEk3+co2i7KMLo56/Ip4l4Tw7vCP0zGH8w46cQ=
*/